SRCs=encrypt.c try-anything.c verify.c
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

all: aes256gcmv1 aes256gcmv1_small

clean:
	rm -f $(OBJs) *.S try.o try_small.o encrypt.o aes256gcmv1 aes256gcmv1_small

%.o: %.c
	$(CC) $(OPT) $< -c -o $@

try.o: try.c
	$(CC) $(OPT) $< -c -o $@

try_small.o: try.c
	$(CC) $(OPT) $< -c -o $@ -DSMALL

encrypt.S: encrypt.c
	$(ALTCC) $(NEWOPT) $< -S -o $@

encrypt.o: encrypt.S
	$(ALTCC) $(NEWOPT) $< -c -o $@

aes256gcmv1: $(OBJs) encrypt.o try.o $(SCLIBS)
	$(CXX) $(OPT) $^ -o $@

aes256gcmv1_small: $(OBJs) encrypt.o try_small.o $(SCLIBS)
	$(CXX) $(OPT) $^ -o $@

kernelrandombytes.o: random.cpp
	$(CXX) $(OPT) $< -c -o $@

cpucycles.o: riscv.c
	$(CC) $< -march=rv32ima -mabi=ilp32 -I. -O1 -c -o $@
