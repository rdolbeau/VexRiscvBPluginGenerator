# B/K/... plugin generator for VexRiscv

**beware** This is targeting the bitmanip extension (B) on an intermediate draft from January 20, 2021, so opcodes and subsets might be not match the current version of B. Ditto for K, this is targeting version 0.9.2. Both may require feature patch to VexRiscv, see below. Packed SIMD (P) stuff is missing a lot of feature and targets 0.92.

## This repository

This is a quick'n'dirty plugin generator to add a subset of the [B](https://github.com/riscv/riscv-bitmanip) extension to the [VexRiscv](https://github.com/SpinalHDL/VexRiscv) core.

The generated plugin is for RV32 only. It doesn't yet support all B instructions; missing instructions are:

* all instructions ending in 'W', as they are RV64-only
* BMAT*, as they are RV64-only
* Three-operands instructions (CMIX, CMOV, FS[RL]*); they are available but need a VexRiscv patch to support the third input (all VexRiscv patch are available on https://github.com/rdolbeau/VexRiscv/tree/three_operands)

There is support for partial instructions (rev8, zext.h, orc.b) so that the default plugins generated for Zba, Zbb and Zbc should be feature-complete. To get everything without conflicts, use:
`new BitManipZbaPlugin, new BitManipZbbZbpPlugin, new BitManipZbcPlugin, new BitManipZbe2cyclesPlugin, new BitManipBFPOnlyPlugin, new BitManipZbsPlugin, new BitManipZbtPlugin,`

This has received limited testing in a [Linux-on-Litex-VexRiscv](https://github.com/litex-hub/linux-on-litex-vexriscv) SoC. YMMV. SMP mode was tested as well.

Also, the implementations of the instructions in SpinalHDL are written for tuncitonality, and not tuned or optimized in any way for performance/area/... (file usage.txt has some numbers).

A separate data file include prototype support for RV32Zkn[ed] (AES encryption/decryption instructions) and RV32Zknh (SHA hash instructions) from the [K ("crypto")](https://github.com/riscv/riscv-crypto) extension draft 0.9.2. There is also support for SM3 and SM4 acceleration (collectively Zks).

There's also some experimental support for some [P ("packed SIMD")](https://github.com/riscv/riscv-p-spec) instructions. It requires even more patches to VexRiscv, first to use a third input sourced from the destination register (so not R4 format like B's ternaries), and second to enable Zp64 instructions that write to two registers (x(2n) and x(2n+1)).

## How to use

There shouldn't be any dependency beyond gcc,  g++, flex and bison. Instructions are defined in `data_bitmanip.txt`, look at the header of that file for the format - it should be fairly easy to add custom instructions if needed (as long as they are register-register, register-immediate, or unary and execute in one cycle).

The tool need an extension name, the data  file and the list of instructions and/or sub-extension to support in the plugin:

```
./gen_plugin -n BitManipZbpZba -i data_bitmanip.txt -I Zba -I Zbb -I GORC -I GREV > BitManipZbbZba.scala
```

Will generate a plugin supporting Zbb (using the full version of `grev` and `gorc`) and Zba. You can use a star to say 'all supported instructions':

```
./gen_plugin -n BitManipAll -i data_bitmanip.txt -I '*' > BitManipAllPlugin.scala
```

The plugin(s) can then be instantiated in the core definition. A way to test all of this is the [LiteX](https://github.com/enjoy-digital/litex/) SoC generator. There is a project to ease the generation of the SoC and associated software, [Linux-on-Litex-Vexriscv](https://github.com/litex-hub/linux-on-litex-vexriscv). This is what is used for the development of the new instructions.

## Test codes

test_b.c is a small synthetic test for RV32IMAB Linux, to check B instructions with various test patterns. See in the file on how to use it.

`chacha20standalone-rv32` is a stand-alone code extracted from the [Supercop](http://bench.cr.yp.to/supercop.html) benchmark (similar to https://github.com/rdolbeau/EPI-test-codes-vector/), from `crypto_stream`. It should give the same results (checksums) as the version in Supercop, and can be compiled for RV32IMA or RV32IMAB. From B, they mostly rely on the rotation instructions (although the B toolchain also generates other instructions, in particular those from Zba).

`aes256ctrstandalone-rv32` and `aes256gcmv1standalone-rv32` are stand-alone codes extracted from the [Supercop](http://bench.cr.yp.to/supercop.html) benchmark, from `crypto_stream` and `crypto_aead` respectively. They should give the same results (checksums) as the version in Supercop, and require `Zkne` (AES encryption instructions) in addition to some of B. `aes256gcmv1standalone-rv32` also requires `clmul[h]`.

`sha256standalone-rv32` and `sha512standalone-rv32` are stand-alone codes extracted from the [Supercop](http://bench.cr.yp.to/supercop.html) benchmark, from `crypto_hashblocks`. They should give the same results (checksums) as the version in Supercop, and require `Zknh` (SHA hash instructions) in addition to some of B.

`aes256encrypt-rv32` and `aes256decrypt-rv32` are on the same line, from `crypto_core`.

`aeadaes256ocbtaglen128v1-rv32` is on the same line, from `crypto_aead`.

# Acknowledgements

This work has partly been done as part of the European Processor Initiative project.

The European Processor Initiative (EPI) (FPA: 800928) has received funding from the Europe
an Union's Horizon 2020 research and innovation programme under grant agreement EPI-SGA1: 
826647
