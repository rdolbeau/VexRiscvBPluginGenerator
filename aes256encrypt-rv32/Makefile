SRCs=core.c try-anything.c
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

all: aes256encrypt aes256encrypt_small

clean:
	rm -f $(OBJs) *.S try.o try_small.o core.o aes256encrypt aes256encrypt_small

%.o: %.c
	$(CC) $(OPT) $< -c -o $@

try.o: try.c
	$(CC) $(OPT) $< -c -o $@

try_small.o: try.c
	$(CC) $(OPT) $< -c -o $@ -DSMALL

core.S: core.c
	$(ALTCC) $(NEWOPT) $< -S -o $@

core.o: core.S
	$(ALTCC) $(NEWOPT) $< -c -o $@

aes256encrypt: $(OBJs) core.o try.o $(SCLIBS)
	$(CXX) $(OPT) $^ -o $@

aes256encrypt_small: $(OBJs) core.o try_small.o $(SCLIBS)
	$(CXX) $(OPT) $^ -o $@

kernelrandombytes.o: random.cpp
	$(CXX) $(OPT) $< -c -o $@

cpucycles.o: riscv.c
	$(CC) $< -march=rv32ima -mabi=ilp32 -I. -O1 -c -o $@
