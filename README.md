# B plugin generator for VexRiscv

## This repository

This is a quick'n'dirty plugin generator to add a subset of the [B](https://github.com/riscv/riscv-bitmanip) extension to the [VexRiscv](https://github.com/SpinalHDL/VexRiscv) core.

The generated plugin is for RV32 only. It doesn't yet support all instructions; missing instructions are:

* all instructions ending in 'W', as they are RV64-only
* BMAT*, as they are RV64-only
* CLMUL*
* BDEP/BEXT/BFP
* CRC32*
* Three-operands instructions (CMIX, CMOV, FS[RL]*)

There is no support for 'partial' instruction - implementing only a subset of the functionality of one instruction. So `grev` is supported, but `rev8` alone isn't. Subextension are defined without 'partial' instructions - so Zbb doesn't have `rev8` or `orc.B`.

This has received limited testing in a [Linux-on-Litex-VexRiscv](https://github.com/litex-hub/linux-on-litex-vexriscv) SoC. YMMV. See below for some tests.

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

## Test codes

test_b.c is a small synthetic test for RV32IMAB Linux, to check B instructions with various test patterns. See in the file on how to use it.

[aes256ctrstandalone-rv32] and [chacha20standalone-rv32] are stand-alone codes extracted from the [Supercop](http://bench.cr.yp.to/supercop.html) benchmark (similar to https://github.com/rdolbeau/EPI-test-codes-vector/). They should give the same results (checksum) as the version in Supercop, and can be compiled for RV32IMA or RV32IMAB. From B, they mostly rely on the rotation instructions (although the B toolchain also generates other instructions, in particular those from Zba).