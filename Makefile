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
	./gen_plugin -n BitManipZbp -i data_bitmanip.txt -I Zbp >| $@

BitManipAllPlugin.scala: gen_plugin data_bitmanip.txt
	./gen_plugin -n BitManipAll -i data_bitmanip.txt -I '*' >| $@

CryptoZknePlugin.scala: gen_plugin data_aes.txt
	./gen_plugin -n CryptoZkne -i data_aes.txt -I '*' >| $@

BitManipZbc.scala: gen_plugin data_clmul.txt
	./gen_plugin -n BitManipZbc -i data_clmul.txt -I Zbc >| $@

CryptoZknh.scala: gen_plugin data_sha.txt
	./gen_plugin -n CryptoZknh -i data_sha.txt -I '*' >| $@

PDataProcess.scala: gen_plugin data_Zpn.txt
	./gen_plugin -n PDataProcess -i data_Zpn.txt -I Zpn >| $@

PSlowDataProcess.scala: gen_plugin data_Zpn_2cycles.txt
	./gen_plugin -n PSlowDataProcess -i data_Zpn_2cycles.txt -I Zpn >| $@

P64DataProcess.scala: gen_plugin data_Zp64.txt
	./gen_plugin -w -n P64DataProcess -i data_Zp64.txt -I '*' >| $@


scala: BitManipZbpPlugin.scala BitManipAllPlugin.scala CryptoZknePlugin.scala BitManipZbc.scala CryptoZknh.scala

include $(DEPXX)
