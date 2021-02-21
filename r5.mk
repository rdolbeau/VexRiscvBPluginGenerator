## B Toolchain so we get some automatic B generation
R5B_TOOLCHAIN=/opt/riscv64b/
R5B_GCC=$(R5B_TOOLCHAIN)/bin/riscv64-unknown-elf-gcc
R5B_OPT=-Os -march=rv32imab -mabi=ilp32 -I.

## Buildroot toolchain for linking and having up-to-date libraries and systems calls
## Requires enabling C++ in buildroot with e.g.
## # BR2_INSTALL_LIBSTDCPP=y
## # BR2_TOOLCHAIN_BUILDROOT_CXX=y
R5IMA_TOOLCHAIN=/home/dolbeau2/LITEX/buildroot-rv32/output/host
R5IMA_GCC=$(R5IMA_TOOLCHAIN)/bin/riscv32-buildroot-linux-gnu-gcc
R5IMA_GXX=$(R5IMA_TOOLCHAIN)/bin/riscv32-buildroot-linux-gnu-g++
R5IMA_OPT=-Os -march=rv32ima -mabi=ilp32 -I.
R5IMA_STRIP=$(R5IMA_TOOLCHAIN)/riscv32-buildroot-linux-gnu-strip
