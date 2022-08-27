SRCs=blocks.c try-anything.c
OBJs=$(SRCs:.c=.o)
SCLIBS=cpucycles.o kernelrandombytes.o

include ../r5.mk

R5IMA_OPT+=-I..
R5B_OPT+=-I.. -DRV32B -DRV32K

all: sha256 sha256_small

clean:
	rm -f $(OBJs) *.S try.o try_small.o blocks.o sha256 sha256_small blocks.S

%.o: %.c
	$(R5IMA_GCC) $(R5IMA_OPT) $< -c -o $@

try.o: try.c
	$(R5IMA_GCC) $(R5IMA_OPT) $< -c -o $@

try_small.o: try.c
	$(R5IMA_GCC) $(R5IMA_OPT) $< -c -o $@ -DSMALL

blocks.S: blocks.c
	$(R5B_GCC) $(R5B_OPT) $< -S -o $@

blocks.o: blocks.S
	$(R5B_GCC) $(R5B_OPT) $< -c -o $@

sha256: $(OBJs) blocks.o try.o $(SCLIBS)
	$(R5IMA_GXX) $(R5IMA_OPT) $^ -o $@

sha256_small: $(OBJs) blocks.o try_small.o $(SCLIBS)
	$(R5IMA_GXX) $(R5IMA_OPT) $^ -o $@

kernelrandombytes.o: random.cpp
	$(R5IMA_GXX) $(R5IMA_OPT) $< -c -o $@

cpucycles.o: riscv.c
	$(R5IMA_GCC) $< -march=$(R5ISA) -mabi=$(R5ABI) -I. -O1 -c -o $@
