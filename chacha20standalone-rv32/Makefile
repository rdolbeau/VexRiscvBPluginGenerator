SRCs=api.c try-anything.c
OBJs=$(SRCs:.c=.o)
SCLIBS=cpucycles.o kernelrandombytes.o

include ../r5.mk

R5IMA_OPT+=-I..
R5B_OPT+=-I.. -DRV32B -DRV32K

all: chacha20 chacha20_small

clean:
	rm -f $(OBJs) *.S try.o try_small.o chacha.o chacha20 chacha20_small chacha20_small_var chacha.s chacha_var.s

%.o: %.c
	$(R5IMA_GCC) $(R5IMA_OPT) $< -c -o $@

try.o: try.c
	$(R5IMA_GCC) $(R5IMA_OPT) $< -c -o $@

try_small.o: try.c
	$(R5IMA_GCC) $(R5IMA_OPT) $< -c -o $@ -DSMALL

chacha.S: chacha.c
	$(R5B_GCC) $(R5B_OPT) $< -S -o $@

chacha.o: chacha.S
	$(R5B_GCC) $(R5B_OPT) $< -c -o $@

chacha20: $(OBJs) chacha.o try.o $(SCLIBS)
	$(R5IMA_GXX) $(R5IMA_OPT) $^ -o $@

chacha20_small: $(OBJs) chacha.o try_small.o $(SCLIBS)
	$(R5IMA_GXX) $(R5IMA_OPT) $^ -o $@

strip:
	$(STRIP) chacha20 chacha20_small

kernelrandombytes.o: random.cpp
	$(R5IMA_GXX) $(R5IMA_OPT) $< -c -o $@

cpucycles.o: riscv.c
	$(R5IMA_GCC) $< -march=rv32ima -mabi=ilp32 -I. -O1 -c -o $@


chacha_XAR.S: chacha.c
	$(R5B_GCC) $(R5B_OPT) -DENABLE_XAR $< -S -o $@

chacha_XAR.o: chacha_XAR.S
	$(R5B_GCC) $(R5B_OPT) -DENABLE_XAR $< -c -o $@

chacha20_XAR: $(OBJs) chacha_XAR.o try.o $(SCLIBS)
	$(R5IMA_GXX) $(R5IMA_OPT) $^ -o $@

chacha20_XAR_small: $(OBJs) chacha_XAR.o try_small.o $(SCLIBS)
	$(R5IMA_GXX) $(R5IMA_OPT) $^ -o $@


chacha_CHACHA.S: chacha.c
	$(R5B_GCC) $(R5B_OPT) -O3 -DENABLE_CHACHA $< -S -o $@

chacha_CHACHA.o: chacha_CHACHA.S
	$(R5B_GCC) $(R5B_OPT) -O3 -DENABLE_CHACHA $< -c -o $@

chacha20_CHACHA: $(OBJs) chacha_CHACHA.o try.o $(SCLIBS)
	$(R5IMA_GXX) $(R5IMA_OPT) $^ -o $@

chacha20_CHACHA_small: $(OBJs) chacha_CHACHA.o try_small.o $(SCLIBS)
	$(R5IMA_GXX) $(R5IMA_OPT) $^ -o $@
