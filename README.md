# B plugin generator for VexRiscv

## This repostory

This is a quick'n'dirty plugin generator to add a subset of the [B](https://github.com/riscv/riscv-bitmanip) extension to the [VexRiscv](https://github.com/SpinalHDL/VexRiscv) core.

The generated plugin is for RV32 only. It doesn't yet support all instructions; missing instructions are:

* all instructions ending in 'W', as they are RV64-only
* BMAT*, as they are RV64-only
* CLMUL*
* BDEP/BEXT/BFP
* CRC32*
* Three-operands instrutioncs (CMIX, CMOV, FS[RL]*)

There is no support for 'partial' instruction - implementing only a subset of the functionality of one instruction. So `grev` is supported, but `rev8` alone isn't. Subextension are defined without 'partial' instructions - so Zbb doesn't have `rev8` or `orc.B`.

This has received limited testing in a [Linux-on-Litex-VexRiscv](https://github.com/litex-hub/linux-on-litex-vexriscv) SoC. YMMV.

Also, the implementations of the instructions in SpinalHDL are written for tuncitonality, and not tuned or optimized in any way for performance/area/... (file usage.txt has some numbers).

## How to use

There shouldn't be any dependency beyond gcc,  g++, flex and bison. Instructions are defined in `data_bitmanip.txt`, look at the header of that file for the format - it should be fairly easy to add custom instructions if needed (as long as they are register-register, register-immediate, or unary and execute in one cycle).

The tool need an extension name, the data  file and the list of instructions and/or sub-extension to support in the plugin:

```
./gen_plugin BitManipZbpZba data_bitmanip.txt Zba Zbb GORC GREV > BitManipZbbZba.scala
```

Will generate a plugin supporting Zbb (using the full version of `grev` and `gorc`) and Zba. You can use a star to say 'all supported instructions':

```
./gen_plugin BitManipAll data_bitmanip.txt '*' > BitManipAllPlugin.scala
```
