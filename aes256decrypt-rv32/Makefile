SRCs=core.c try-anything.c
OBJs=$(SRCs:.c=.o)
SCLIBS=cpucycles.o kernelrandombytes.o

include ../r5.mk

R5IMA_OPT+=-I..
R5B_OPT+=-I.. -DRV32B -DRV32K

all: aes256decrypt aes256decrypt_small

clean:
	rm -f $(OBJs) *.S try.o try_small.o core.o aes256decrypt aes256decrypt_small

%.o: %.c
	$(R5IMA_GCC) $(R5IMA_OPT) $< -c -o $@

try.o: try.c
	$(R5IMA_GCC) $(R5IMA_OPT) $< -c -o $@

try_small.o: try.c
	$(R5IMA_GCC) $(R5IMA_OPT) $< -c -o $@ -DSMALL

core.S: core.c
	$(R5B_GCC) $(R5B_OPT) $< -S -o $@

core.o: core.S
	$(R5B_GCC) $(R5B_OPT) $< -c -o $@

aes256decrypt: $(OBJs) core.o try.o $(SCLIBS)
	$(R5IMA_GXX) $(R5IMA_OPT) $^ -o $@

aes256decrypt_small: $(OBJs) core.o try_small.o $(SCLIBS)
	$(R5IMA_GXX) $(R5IMA_OPT) $^ -o $@

kernelrandombytes.o: random.cpp
	$(R5IMA_GXX) $(R5IMA_OPT) $< -c -o $@

cpucycles.o: riscv.c
	$(R5IMA_GCC) $< -march=rv32ima -mabi=ilp32 -I. -O1 -c -o $@
