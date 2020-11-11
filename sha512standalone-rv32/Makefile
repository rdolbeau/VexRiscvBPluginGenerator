SRCs=blocks.c try-anything.c
OBJs=$(SRCs:.c=.o)
SCLIBS=cpucycles.o kernelrandombytes.o

COMPDIR=/home/dolbeau/LITEX/riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-linux-ubuntu14
ALTCOMPDIR=/opt/riscv64b

CC=$(COMPDIR)/bin/riscv64-unknown-elf-gcc
ALTCC=$(ALTCOMPDIR)/bin/riscv64-unknown-elf-gcc
CC=$(ALTCC)
CXX=$(COMPDIR)/bin/riscv64-unknown-elf-g++
STRIP=$(COMPDIR)/bin/riscv64-unknown-elf-strip
NEWOPT=-march=rv32imab -mabi=ilp32 -I. -O3 -DRV32ZKNH #-fno-vectorize #-DUSE_EPI_CUSTOM
OPT=-march=rv32ima -mabi=ilp32 -I. -O3 #-fno-vectorize #-DUSE_EPI_CUSTOM
#NEWOPT=$(OPT)

all: sha512 sha512_small

clean:
	rm -f $(OBJs) try.o try_small.o blocks.o sha512 sha512_small blocks.S

%.o: %.c
	$(CC) $(NEWOPT) $< -c -o $@

try.o: try.c
	$(CC) $(NEWOPT) $< -c -o $@

try_small.o: try.c
	$(CC) $(NEWOPT) $< -c -o $@ -DSMALL

blocks.S: blocks.c
	$(CC) $(NEWOPT) $< -S -o $@

blocks.o: blocks.S
	$(CC) $(NEWOPT) $< -c -o $@

sha512: $(OBJs) blocks.o try.o $(SCLIBS)
	$(CXX) $(OPT) $^ -o $@

sha512_small: $(OBJs) blocks.o try_small.o $(SCLIBS)
	$(CXX) $(OPT) $^ -o $@

kernelrandombytes.o: random.cpp
	$(CXX) $(OPT) $< -c -o $@

cpucycles.o: riscv.c
	$(CC) $< -march=rv32ima -mabi=ilp32 -I. -O1 -c -o $@
