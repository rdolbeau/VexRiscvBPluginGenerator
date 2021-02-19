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

## Zbe unimplemented, b(de)compress are missing and pack[h] are in Zbf anyway

BitManipZbf.scala: gen_plugin data_bitmanip.txt
	./gen_plugin -n BitManipZbf -i data_bitmanip.txt -I Zbf >| $@

## Needed to include Zbf with Zbp, as pack[h] are in both
BitManipBFPonly.scala: gen_plugin data_bitmanip.txt
	./gen_plugin -n BitManipBFPOnly -i data_bitmanip.txt -I BFP >| $@

## Zbm unimplemented, RV64 only

## includes both Zbb & Zbp to avoid redudancies as there is overlap
## and Zpb has full version instructions with partial implementation
## in Zbb
## Should not be included along Zbb
BitManipZbbZbp.scala: gen_plugin data_bitmanip.txt
	./gen_plugin -n BitManipZbbZbp -i data_bitmanip.txt -I Zbb -I Zbp >| $@

## Zbr unimplemented, crc32* are missing

BitManipZbs.scala: gen_plugin data_bitmanip.txt
	./gen_plugin -n BitManipZbs -i data_bitmanip.txt -I Zbs >| $@

BitManipZbt.scala: gen_plugin data_bitmanip.txt
	./gen_plugin -n BitManipZbt -i data_bitmanip.txt -I Zbt >| $@

## Still missing rev.b (special case of grevi), [un]zip (special cases of [un]shfl)
CryptoZkb.scala: gen_plugin data_bitmanip.txt data_bitmanip_ZbbOnly.txt
	./gen_plugin -n BitManipZkb -i data_bitmanip.txt -i data_bitmanip_ZbbOnly.txt -I Zkb >| $@

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

PDataProcess.scala: gen_plugin data_Zpn.txt
	./gen_plugin -n PDataProcess -i data_Zpn.txt -I Zpn >| $@

PSlowDataProcess.scala: gen_plugin data_Zpn_2cycles.txt
	./gen_plugin -n PSlowDataProcess -i data_Zpn_2cycles.txt -I Zpn >| $@

P64DataProcess.scala: gen_plugin data_Zp64.txt
	./gen_plugin -w -n P64DataProcess -i data_Zp64.txt -I '*' >| $@

B: BitManipZba.scala BitManipZbb.scala BitManipZbc.scala BitManipZbf.scala BitManipBFPonly.scala BitManipZbbZbp.scala BitManipZbs.scala BitManipZbt.scala

P: PDataProcess.scala PSlowDataProcess.scala P64DataProcess.scala

Z: CryptoZkg.scala CryptoZknd.scala CryptoZkne.scala CryptoZknh.scala CryptoZks.scala

scala: B P Z

include $(DEPXX)

## B Toolchain so we get some automatic B generation
R5B_TOOLCHAIN=/opt/riscv64b/
R5B_GCC=$(R5B_TOOLCHAIN)/bin/riscv64-unknown-elf-gcc
R5B_OPT=-Os -march=rv32imab -mabi=ilp32 -I.
## Buildroot toolchain for linking and hacing up-to-date libraries and systems calls
R5IMA_TOOLCHAIN=/home/dolbeau2/LITEX/buildroot-rv32/output/host
R5IMA_GCC=$(R5IMA_TOOLCHAIN)/bin/riscv32-buildroot-linux-gnu-gcc
R5IMA_OPT=-Os -march=rv32ima -mabi=ilp32 -I.
R5IMA_STRIP=$(R5IMA_TOOLCHAIN)/riscv32-buildroot-linux-gnu-strip

NEWINST_H=new_instructions_support_b.h new_instructions_support.h new_instructions_support_k.h new_instructions_support_p.h

tests: test_b test_p

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

## avoid builtin rule for .o
.SUFFIXES:
SUFFIXES :=
%.o:
