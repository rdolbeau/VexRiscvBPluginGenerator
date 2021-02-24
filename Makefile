SRCXX=gen_plugin.cpp unparse.cpp
OBJXX=$(SRCXX:.cpp=.o)
DEPXX=$(SRCXX:.cpp=.d)
OBJ=inst_par.o inst_lex.o
LEX=flex
YACC=bison -d #--report-file=bison.log --report=all
CC=gcc
CFLAGS=-O2
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

## everything in a single plugin. might be overkill. includes SLO/SRO.
BitManipAllPlugin.scala: gen_plugin data_bitmanip.txt data_clmul.txt
	./gen_plugin -n BitManipAll -i data_bitmanip.txt -i data_clmul.txt -I '*' >| $@

BitManipZba.scala: gen_plugin data_bitmanip.txt
	./gen_plugin -n BitManipZba -i data_bitmanip.txt -I Zba >| $@

BitManipZbb.scala: gen_plugin data_bitmanip.txt data_bitmanip_ZbbOnly.txt
	./gen_plugin -n BitManipZbb -i data_bitmanip.txt -i data_bitmanip_ZbbOnly.txt -I Zbb >| $@

BitManipZbc.scala: gen_plugin data_clmul.txt
	./gen_plugin -n BitManipZbc -i data_clmul.txt -I Zbc >| $@

# this is just pack[h], so don't use with Zbp or Zbf
BitManipZbe1cycle.scala: gen_plugin data_bitmanip.txt
	./gen_plugin -n BitManipZbe1cycle -i data_bitmanip.txt -I Zbe >| $@

# b[de]compress, implemented over 2 cycles
BitManipZbe2cycles.scala: gen_plugin data_bitmanip_compress.txt
	./gen_plugin -n BitManipZbe2cycles -i data_bitmanip_compress.txt -I Zbe >| $@

BitManipZbf.scala: gen_plugin data_bitmanip.txt
	./gen_plugin -n BitManipZbf -i data_bitmanip.txt -I Zbf >| $@

## Needed to include Zbf with Zbp, as pack[h] are in both
BitManipBFPonly.scala: gen_plugin data_bitmanip.txt
	./gen_plugin -n BitManipBFPOnly -i data_bitmanip.txt -I BFP >| $@

## Zbm unimplemented, RV64 only

## includes both Zbb & Zbp to avoid redudancies as there is overlap
## and Zpb has full version instructions with partial implementation
## in Zbb
## Should not be included along Zbb or Zbp
BitManipZbbZbp.scala: gen_plugin data_bitmanip.txt
	./gen_plugin -n BitManipZbbZbp -i data_bitmanip.txt -I Zbb -I Zbp >| $@

# stand-alone Zbp
BitManipZbp.scala: gen_plugin data_bitmanip.txt
	./gen_plugin -n BitManipZbp -i data_bitmanip.txt -I Zbp >| $@

## Zbr unimplemented, crc32* are missing

BitManipZbs.scala: gen_plugin data_bitmanip.txt
	./gen_plugin -n BitManipZbs -i data_bitmanip.txt -I Zbs >| $@

BitManipZbt.scala: gen_plugin data_bitmanip.txt
	./gen_plugin -n BitManipZbt -i data_bitmanip.txt -I Zbt >| $@

CryptoZkb.scala: gen_plugin data_bitmanip.txt data_bitmanip_ZbbOnly.txt
	./gen_plugin -n CryptoZkb -i data_bitmanip.txt -i data_bitmanip_ZbbOnly.txt -I Zkb >| $@

## CryptoZkg doesn't require clmulr, so not 100% the same as Zbc
CryptoZkg.scala: gen_plugin data_clmul.txt
	./gen_plugin -n CryptoZkg -i data_clmul.txt -I CLMUL -I CLMULH >| $@

## Full Zkn is Zknd + Zkne + Zknh + Zkg + Zkb
## For Zkb, beware the overlap with a lot of B plugins

CryptoZknd.scala: gen_plugin data_aes.txt
	./gen_plugin -n CryptoZknd -i data_aes.txt -I Zknd >| $@

CryptoZkne.scala: gen_plugin data_aes.txt
	./gen_plugin -n CryptoZkne -i data_aes.txt -I Zkne >| $@

CryptoZknh.scala: gen_plugin data_sha.txt
	./gen_plugin -n CryptoZknh -i data_sha.txt -I '*' >| $@

## Zkr not supported

CryptoZks.scala: gen_plugin data_sm3.txt data_sm4.txt
	./gen_plugin -n CryptoZks -i data_sm3.txt -i data_sm4.txt -I '*' >| $@

CryptoSM3.scala:  gen_plugin data_sm3.txt
	./gen_plugin -n CryptoSM3 -i data_sm3.txt -I '*' >| $@

CryptoSM4.scala:  gen_plugin data_sm4.txt
	./gen_plugin -n CryptoSM4 -i data_sm4.txt -I '*' >| $@

PackedSIMDBase.scala: gen_plugin data_Zpn.txt
	./gen_plugin -n PackedSIMDBase -i data_Zpn.txt -I Zpn >| $@

PackedSIMDSlow.scala: gen_plugin data_Zpn_2cycles.txt
	./gen_plugin -n PackedSIMDSlow -i data_Zpn_2cycles.txt -I Zpn >| $@

PackedSIMDWide.scala: gen_plugin data_Zp64.txt
	./gen_plugin -w -n PackedSIMDWide -i data_Zp64.txt -I '*' >| $@

B: BitManipZba.scala BitManipZbb.scala BitManipZbbZbp.scala BitManipZbc.scala BitManipZbe1cycle.scala BitManipZbe2cycles.scala BitManipZbf.scala BitManipBFPonly.scala BitManipZbp.scala BitManipZbs.scala BitManipZbt.scala

P: PackedSIMDBase.scala PackedSIMDSlow.scala PackedSIMDWide.scala

Z: CryptoZkb.scala CryptoZkg.scala CryptoZknd.scala CryptoZkne.scala CryptoZknh.scala CryptoZks.scala

scala: B P Z

include $(DEPXX)

include r5.mk

NEWINST_H=new_instructions_support_b.h new_instructions_support.h new_instructions_support_k.h new_instructions_support_p.h

tests: test_b test_p test_b.txt test_p.txt

signal.o: signal.c
	$(R5IMA_GCC) $(R5IMA_OPT) -c $< -o $@

test_b.S: test_b.c $(NEWINST_H)
	$(R5B_GCC) $(R5B_OPT) -DCHECK_SIGILL -S $< -o $@

test_p.S: test_p.c
	$(R5B_GCC) $(R5B_OPT) -DCHECK_SIGILL -S $< -o $@

test_b.o: test_b.S $(NEWINST_H)
	$(R5B_GCC) $(R5B_OPT) -DCHECK_SIGILL -c $< -o $@

test_p.o: test_p.S
	$(R5B_GCC) $(R5B_OPT) -DCHECK_SIGILL -c $< -o $@

test_b: test_b.o signal.o
	$(R5IMA_GCC) $(R5IMA_OPT) $^ -o $@

test_p: test_p.o signal.o
	$(R5IMA_GCC) $(R5IMA_OPT) $^ -o $@

test_b.txt: test_b.c
	gcc -I. -O2 $< -o /tmp/a.out && /tmp/a.out | tee $@

test_p.txt: test_p.c
	gcc -I. -O2 $< -o /tmp/a.out && /tmp/a.out | tee $@

## avoid builtin rule for .o
.SUFFIXES:
SUFFIXES :=
%.o:
