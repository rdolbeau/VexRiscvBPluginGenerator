SRCXX=gen_plugin.cpp unparse.cpp
OBJXX=$(SRCXX:.cpp=.o)
DEPXX=$(SRCXX:.cpp=.d)
OBJ=inst_par.o inst_lex.o


LEX=flex
YACC=bison -d #--report-file=bison.log --report=all


CXX=g++
CXXFLAGS=-O2

all: gen_plugin

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

gen_plugin: $(OBJXX) $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

inst_par.h: inst_par.o

inst_par.o: inst_par.y
	$(YACC) -o $(<:%.y=%.c) $<
	$(CC) $(CFLAGS) $(<:%.y=%.c) -c -o $@

inst_lex.o: inst_lex.l inst_par.h
	$(LEX) -o $(<:%.l=%.c) $< 
	$(CC) $(CFLAGS) $(<:%.l=%.c) -c -o $@

%.d: %.cpp
	$(CXX) -MM $< -o $@

clean:
	rm -f $(OBJXX) $(OBJ) gen_plugin

veryclean:
	rm -f $(OBJXX) $(OBJ) gen_plugin *~ inst_lex.c inst_par.c *.d

ultraclean:
	rm -f $(OBJXX) $(OBJ) gen_plugin *~ inst_lex.c inst_par.c *.d *.scala

BitManipZbpPlugin.scala: gen_plugin data_bitmanip.txt
	./gen_plugin BitManipZbp data_bitmanip.txt Zbp >| $@

BitManipAllPlugin.scala: gen_plugin data_bitmanip.txt
	./gen_plugin BitManipAll data_bitmanip.txt '*' >| $@

RDAESPlugin.scala: gen_plugin data_aes.txt
	./gen_plugin RDAES data_aes.txt Zrdaes >| $@

scala: BitManipZbpPlugin.scala BitManipAllPlugin.scala RDAESPlugin.scala


include $(DEPXX)