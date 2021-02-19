SRCs=encrypt.c try-anything.c verify.c
OBJs=$(SRCs:.c=.o)
SCLIBS=cpucycles.o kernelrandombytes.o

include ../r5.mk

R5IMA_OPT+=-I..
R5B_OPT+=-I.. -DRV32B -DRV32K

all: aes256gcmv1 aes256gcmv1_small

clean:
	rm -f $(OBJs) *.S try.o try_small.o encrypt.o aes256gcmv1 aes256gcmv1_small

%.o: %.c
	$(R5IMA_GCC) $(R5IMA_OPT) $< -c -o $@

try.o: try.c
	$(R5IMA_GCC) $(R5IMA_OPT) $< -c -o $@

try_small.o: try.c
	$(R5IMA_GCC) $(R5IMA_OPT) $< -c -o $@ -DSMALL

encrypt.S: encrypt.c
	$(R5B_GCC) $(R5B_OPT) $< -S -o $@

encrypt.o: encrypt.S
	$(R5B_GCC) $(R5B_OPT) $< -c -o $@

aes256gcmv1: $(OBJs) encrypt.o try.o $(SCLIBS)
	$(R5IMA_GXX) $(R5IMA_OPT) $^ -o $@

aes256gcmv1_small: $(OBJs) encrypt.o try_small.o $(SCLIBS)
	$(R5IMA_GXX) $(R5IMA_OPT) $^ -o $@

kernelrandombytes.o: random.cpp
	$(R5IMA_GXX) $(R5IMA_OPT) $< -c -o $@

cpucycles.o: riscv.c
	$(R5IMA_GCC) $< -march=rv32ima -mabi=ilp32 -I. -O1 -c -o $@
