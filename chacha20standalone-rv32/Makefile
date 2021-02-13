SRCs=api.c try-anything.c
OBJs=$(SRCs:.c=.o)
SCLIBS=cpucycles.o kernelrandombytes.o

COMPDIR=~dolbeau2/LITEX/buildroot-rv32/output/host
ALTCOMPDIR=/opt/riscv64b

CC=$(COMPDIR)/bin/riscv32-buildroot-linux-gnu-gcc
ALTCC=$(ALTCOMPDIR)/bin/riscv64-unknown-elf-gcc
CXX=$(COMPDIR)/bin/riscv32-buildroot-linux-gnu-g++
STRIP=$(COMPDIR)/bin/riscv32-buildroot-linux-gnu-strip
NEWOPT=-march=rv32imab -mabi=ilp32 -I. -I.. -O3 -DRV32B #-fno-vectorize #-DUSE_EPI_CUSTOM
OPT=-march=rv32ima -mabi=ilp32 -I. -I.. -O3 #-fno-vectorize #-DUSE_EPI_CUSTOM
#ALTCC=$(CC)
#NEWOPT=$(OPT)

all: chacha20 chacha20_small

clean:
	rm -f $(OBJs) *.S try.o try_small.o chacha.o chacha20 chacha20_small chacha20_small_var chacha.s chacha_var.s

%.o: %.c
	$(CC) $(OPT) $< -c -o $@

try.o: try.c
	$(CC) $(OPT) $< -c -o $@

try_small.o: try.c
	$(CC) $(OPT) $< -c -o $@ -DSMALL

chacha.S: chacha.c
	$(ALTCC) $(NEWOPT) $< -S -o $@

chacha.o: chacha.S
	$(ALTCC) $(NEWOPT) $< -c -o $@

chacha20: $(OBJs) chacha.o try.o $(SCLIBS)
	$(CXX) $(OPT) $^ -o $@

chacha20_small: $(OBJs) chacha.o try_small.o $(SCLIBS)
	$(CXX) $(OPT) $^ -o $@

strip:
	$(STRIP) chacha20 chacha20_small

kernelrandombytes.o: random.cpp
	$(CXX) $(OPT) $< -c -o $@

cpucycles.o: riscv.c
	$(CC) $< -march=rv32ima -mabi=ilp32 -I. -O1 -c -o $@
