SRCs=riscv32.c try-anything.c
OBJs=$(SRCs:.c=.o)
SCLIBS=cpucycles.o kernelrandombytes.o

COMPDIR=~dolbeau2/LITEX/buildroot-rv32/output/host
ALTCOMPDIR=/opt/riscv64b

CC=$(COMPDIR)/bin/riscv32-buildroot-linux-gnu-gcc
ALTCC=$(ALTCOMPDIR)/bin/riscv64-unknown-elf-gcc
CXX=$(COMPDIR)/bin/riscv32-buildroot-linux-gnu-g++
STRIP=$(COMPDIR)/bin/riscv32-buildroot-linux-gnu-strip
NEWOPT=-march=rv32imab -mabi=ilp32 -I. -O3 -DRV32B #-fno-vectorize #-DUSE_EPI_CUSTOM
OPT=-march=rv32ima -mabi=ilp32 -I. -O3 #-fno-vectorize #-DUSE_EPI_CUSTOM
#ALTCC=$(CC)
#NEWOPT=$(OPT)

all: aes256ctr aes256ctr_small

clean:
	rm -f $(OBJs) *.S try.o try_small.o riscv32.o aes256ctr aes256ctr_small

%.o: %.c
	$(CC) $(OPT) $< -c -o $@

try.o: try.c
	$(CC) $(OPT) $< -c -o $@

try_small.o: try.c
	$(CC) $(OPT) $< -c -o $@ -DSMALL

riscv32.S: riscv32.c
	$(ALTCC) $(NEWOPT) $< -S -o $@

riscv32.o: riscv32.S
	$(ALTCC) $(NEWOPT) $< -c -o $@

aes256ctr: $(OBJs) riscv32.o try.o $(SCLIBS)
	$(CXX) $(OPT) $^ -o $@

aes256ctr_small: $(OBJs) riscv32.o try_small.o $(SCLIBS)
	$(CXX) $(OPT) $^ -o $@

kernelrandombytes.o: random.cpp
	$(CXX) $(OPT) $< -c -o $@

cpucycles.o: riscv.c
	$(CC) $< -march=rv32ima -mabi=ilp32 -I. -O1 -c -o $@
