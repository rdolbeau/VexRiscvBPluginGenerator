SRCs=encrypt.c try-anything.c verify.c
OBJs=$(SRCs:.c=.o)
SCLIBS=cpucycles.o kernelrandombytes.o

COMPDIR=/home/dolbeau/LITEX/riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-linux-ubuntu14
ALTCOMPDIR=/opt/riscv64b

CC=$(COMPDIR)/bin/riscv64-unknown-elf-gcc
ALTCC=$(ALTCOMPDIR)/bin/riscv64-unknown-elf-gcc
CC=$(ALTCC)
CXX=$(COMPDIR)/bin/riscv64-unknown-elf-g++
STRIP=$(COMPDIR)/bin/riscv64-unknown-elf-strip
NEWOPT=-march=rv32imab -mabi=ilp32 -I. -O3 -DRV32B #-fno-vectorize #-DUSE_EPI_CUSTOM
OPT=-march=rv32ima -mabi=ilp32 -I. -O3 #-fno-vectorize #-DUSE_EPI_CUSTOM
#NEWOPT=$(OPT)

all: aes256gcmv1 aes256gcmv1_small

clean:
	rm -f $(OBJs) try.o try_small.o encrypt.o aes256gcmv1 aes256gcmv1_small

%.o: %.c
	$(CC) $(NEWOPT) $< -c -o $@

try.o: try.c
	$(CC) $(NEWOPT) $< -c -o $@

try_small.o: try.c
	$(CC) $(NEWOPT) $< -c -o $@ -DSMALL

encrypt.S: encrypt.c
	$(CC) $(NEWOPT) $< -S -o $@

encrypt.o: encrypt.S
	$(CC) $(NEWOPT) $< -c -o $@

aes256gcmv1: $(OBJs) encrypt.o try.o $(SCLIBS)
	$(CXX) $(OPT) $^ -o $@

aes256gcmv1_small: $(OBJs) encrypt.o try_small.o $(SCLIBS)
	$(CXX) $(OPT) $^ -o $@

kernelrandombytes.o: random.cpp
	$(CXX) $(OPT) $< -c -o $@

cpucycles.o: riscv.c
	$(CC) $< -march=rv32ima -mabi=ilp32 -I. -O1 -c -o $@
