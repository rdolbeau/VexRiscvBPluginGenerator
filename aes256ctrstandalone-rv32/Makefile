SRCs=riscv32.c try-anything.c
OBJs=$(SRCs:.c=.o)
SCLIBS=cpucycles.o kernelrandombytes.o

include ../r5.mk

R5IMA_OPT+=-I..
R5B_OPT+=-I.. -DRV32B -DRV32K

all: aes256ctr aes256ctr_small

clean:
	rm -f $(OBJs) *.S try.o try_small.o riscv32.o aes256ctr aes256ctr_small

%.o: %.c
	$(R5IMA_GCC) $(R5IMA_OPT) $< -c -o $@

try.o: try.c
	$(R5IMA_GCC) $(R5IMA_OPT) $< -c -o $@

try_small.o: try.c
	$(R5IMA_GCC) $(R5IMA_OPT) $< -c -o $@ -DSMALL

riscv32.S: riscv32.c
	$(R5B_GCC) $(R5B_OPT) $< -S -o $@

riscv32.o: riscv32.S
	$(R5B_GCC) $(R5B_OPT) $< -c -o $@

aes256ctr: $(OBJs) riscv32.o try.o $(SCLIBS)
	$(R5IMA_GXX) $(R5IMA_OPT) $^ -o $@

aes256ctr_small: $(OBJs) riscv32.o try_small.o $(SCLIBS)
	$(R5IMA_GXX) $(R5IMA_OPT) $^ -o $@

kernelrandombytes.o: random.cpp
	$(R5IMA_GXX) $(R5IMA_OPT) $< -c -o $@

cpucycles.o: riscv.c
	$(R5IMA_GCC) $< -march=$(R5ISA) -mabi=$(R5ABI) -I. -O1 -c -o $@
