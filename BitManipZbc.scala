// WARNING: this is auto-generated code!
// See https://github.com/rdolbeau/VexRiscvBPluginGenerator/
package vexriscv.plugin
import spinal.core._
import vexriscv.{Stageable, DecoderService, VexRiscv}
object BitManipZbcPlugin {
	object BitManipZbcCtrlEnum extends SpinalEnum(binarySequential) {
		 val CTRL_CLMUL, CTRL_CLMULR, CTRL_CLMULH = newElement()
	}
	object BitManipZbcCtrl extends Stageable(BitManipZbcCtrlEnum())
// Prologue

	def fun_clmul(rs1:Bits, rs2:Bits) : Bits = {
		val x0 = (((rs2 & B"32'x00000001") =/= B"32'x00000000") ? (rs1 |<< 0) | (B"32'x00000000"))
		val x1 = (((rs2 & B"32'x00000002") =/= B"32'x00000000") ? (rs1 |<< 1) | (B"32'x00000000"))
		val x2 = (((rs2 & B"32'x00000004") =/= B"32'x00000000") ? (rs1 |<< 2) | (B"32'x00000000"))
		val x3 = (((rs2 & B"32'x00000008") =/= B"32'x00000000") ? (rs1 |<< 3) | (B"32'x00000000"))
		val x4 = (((rs2 & B"32'x00000010") =/= B"32'x00000000") ? (rs1 |<< 4) | (B"32'x00000000"))
		val x5 = (((rs2 & B"32'x00000020") =/= B"32'x00000000") ? (rs1 |<< 5) | (B"32'x00000000"))
		val x6 = (((rs2 & B"32'x00000040") =/= B"32'x00000000") ? (rs1 |<< 6) | (B"32'x00000000"))
		val x7 = (((rs2 & B"32'x00000080") =/= B"32'x00000000") ? (rs1 |<< 7) | (B"32'x00000000"))
		val x8 = (((rs2 & B"32'x00000100") =/= B"32'x00000000") ? (rs1 |<< 8) | (B"32'x00000000"))
		val x9 = (((rs2 & B"32'x00000200") =/= B"32'x00000000") ? (rs1 |<< 9) | (B"32'x00000000"))
		val x10 = (((rs2 & B"32'x00000400") =/= B"32'x00000000") ? (rs1 |<< 10) | (B"32'x00000000"))
		val x11 = (((rs2 & B"32'x00000800") =/= B"32'x00000000") ? (rs1 |<< 11) | (B"32'x00000000"))
		val x12 = (((rs2 & B"32'x00001000") =/= B"32'x00000000") ? (rs1 |<< 12) | (B"32'x00000000"))
		val x13 = (((rs2 & B"32'x00002000") =/= B"32'x00000000") ? (rs1 |<< 13) | (B"32'x00000000"))
		val x14 = (((rs2 & B"32'x00004000") =/= B"32'x00000000") ? (rs1 |<< 14) | (B"32'x00000000"))
		val x15 = (((rs2 & B"32'x00008000") =/= B"32'x00000000") ? (rs1 |<< 15) | (B"32'x00000000"))
		val x16 = (((rs2 & B"32'x00010000") =/= B"32'x00000000") ? (rs1 |<< 16) | (B"32'x00000000"))
		val x17 = (((rs2 & B"32'x00020000") =/= B"32'x00000000") ? (rs1 |<< 17) | (B"32'x00000000"))
		val x18 = (((rs2 & B"32'x00040000") =/= B"32'x00000000") ? (rs1 |<< 18) | (B"32'x00000000"))
		val x19 = (((rs2 & B"32'x00080000") =/= B"32'x00000000") ? (rs1 |<< 19) | (B"32'x00000000"))
		val x20 = (((rs2 & B"32'x00100000") =/= B"32'x00000000") ? (rs1 |<< 20) | (B"32'x00000000"))
		val x21 = (((rs2 & B"32'x00200000") =/= B"32'x00000000") ? (rs1 |<< 21) | (B"32'x00000000"))
		val x22 = (((rs2 & B"32'x00400000") =/= B"32'x00000000") ? (rs1 |<< 22) | (B"32'x00000000"))
		val x23 = (((rs2 & B"32'x00800000") =/= B"32'x00000000") ? (rs1 |<< 23) | (B"32'x00000000"))
		val x24 = (((rs2 & B"32'x01000000") =/= B"32'x00000000") ? (rs1 |<< 24) | (B"32'x00000000"))
		val x25 = (((rs2 & B"32'x02000000") =/= B"32'x00000000") ? (rs1 |<< 25) | (B"32'x00000000"))
		val x26 = (((rs2 & B"32'x04000000") =/= B"32'x00000000") ? (rs1 |<< 26) | (B"32'x00000000"))
		val x27 = (((rs2 & B"32'x08000000") =/= B"32'x00000000") ? (rs1 |<< 27) | (B"32'x00000000"))
		val x28 = (((rs2 & B"32'x10000000") =/= B"32'x00000000") ? (rs1 |<< 28) | (B"32'x00000000"))
		val x29 = (((rs2 & B"32'x20000000") =/= B"32'x00000000") ? (rs1 |<< 29) | (B"32'x00000000"))
		val x30 = (((rs2 & B"32'x40000000") =/= B"32'x00000000") ? (rs1 |<< 30) | (B"32'x00000000"))
		val x31 = (((rs2 & B"32'x80000000") =/= B"32'x00000000") ? (rs1 |<< 31) | (B"32'x00000000"))
		x0 ^ x1 ^ x2 ^ x3 ^ x4 ^ x5 ^ x6 ^ x7 ^ x8 ^ x9 ^ x10 ^ x11 ^ x12 ^ x13 ^ x14 ^ x15 ^ x16 ^ x17 ^ x18 ^ x19 ^ x20 ^ x21 ^ x22 ^ x23 ^ x24 ^ x25 ^ x26 ^ x27 ^ x28 ^ x29 ^ x30 ^ x31 // return value	
	}

	def fun_clmulr(rs1:Bits, rs2:Bits) : Bits = {
		val x0 = (((rs2 & B"32'x00000001") =/= B"32'x00000000") ? (rs1 |>> 31) | (B"32'x00000000"))
		val x1 = (((rs2 & B"32'x00000002") =/= B"32'x00000000") ? (rs1 |>> 30) | (B"32'x00000000"))
		val x2 = (((rs2 & B"32'x00000004") =/= B"32'x00000000") ? (rs1 |>> 29) | (B"32'x00000000"))
		val x3 = (((rs2 & B"32'x00000008") =/= B"32'x00000000") ? (rs1 |>> 28) | (B"32'x00000000"))
		val x4 = (((rs2 & B"32'x00000010") =/= B"32'x00000000") ? (rs1 |>> 27) | (B"32'x00000000"))
		val x5 = (((rs2 & B"32'x00000020") =/= B"32'x00000000") ? (rs1 |>> 26) | (B"32'x00000000"))
		val x6 = (((rs2 & B"32'x00000040") =/= B"32'x00000000") ? (rs1 |>> 25) | (B"32'x00000000"))
		val x7 = (((rs2 & B"32'x00000080") =/= B"32'x00000000") ? (rs1 |>> 24) | (B"32'x00000000"))
		val x8 = (((rs2 & B"32'x00000100") =/= B"32'x00000000") ? (rs1 |>> 23) | (B"32'x00000000"))
		val x9 = (((rs2 & B"32'x00000200") =/= B"32'x00000000") ? (rs1 |>> 22) | (B"32'x00000000"))
		val x10 = (((rs2 & B"32'x00000400") =/= B"32'x00000000") ? (rs1 |>> 21) | (B"32'x00000000"))
		val x11 = (((rs2 & B"32'x00000800") =/= B"32'x00000000") ? (rs1 |>> 20) | (B"32'x00000000"))
		val x12 = (((rs2 & B"32'x00001000") =/= B"32'x00000000") ? (rs1 |>> 19) | (B"32'x00000000"))
		val x13 = (((rs2 & B"32'x00002000") =/= B"32'x00000000") ? (rs1 |>> 18) | (B"32'x00000000"))
		val x14 = (((rs2 & B"32'x00004000") =/= B"32'x00000000") ? (rs1 |>> 17) | (B"32'x00000000"))
		val x15 = (((rs2 & B"32'x00008000") =/= B"32'x00000000") ? (rs1 |>> 16) | (B"32'x00000000"))
		val x16 = (((rs2 & B"32'x00010000") =/= B"32'x00000000") ? (rs1 |>> 15) | (B"32'x00000000"))
		val x17 = (((rs2 & B"32'x00020000") =/= B"32'x00000000") ? (rs1 |>> 14) | (B"32'x00000000"))
		val x18 = (((rs2 & B"32'x00040000") =/= B"32'x00000000") ? (rs1 |>> 13) | (B"32'x00000000"))
		val x19 = (((rs2 & B"32'x00080000") =/= B"32'x00000000") ? (rs1 |>> 12) | (B"32'x00000000"))
		val x20 = (((rs2 & B"32'x00100000") =/= B"32'x00000000") ? (rs1 |>> 11) | (B"32'x00000000"))
		val x21 = (((rs2 & B"32'x00200000") =/= B"32'x00000000") ? (rs1 |>> 10) | (B"32'x00000000"))
		val x22 = (((rs2 & B"32'x00400000") =/= B"32'x00000000") ? (rs1 |>> 9) | (B"32'x00000000"))
		val x23 = (((rs2 & B"32'x00800000") =/= B"32'x00000000") ? (rs1 |>> 8) | (B"32'x00000000"))
		val x24 = (((rs2 & B"32'x01000000") =/= B"32'x00000000") ? (rs1 |>> 7) | (B"32'x00000000"))
		val x25 = (((rs2 & B"32'x02000000") =/= B"32'x00000000") ? (rs1 |>> 6) | (B"32'x00000000"))
		val x26 = (((rs2 & B"32'x04000000") =/= B"32'x00000000") ? (rs1 |>> 5) | (B"32'x00000000"))
		val x27 = (((rs2 & B"32'x08000000") =/= B"32'x00000000") ? (rs1 |>> 4) | (B"32'x00000000"))
		val x28 = (((rs2 & B"32'x10000000") =/= B"32'x00000000") ? (rs1 |>> 3) | (B"32'x00000000"))
		val x29 = (((rs2 & B"32'x20000000") =/= B"32'x00000000") ? (rs1 |>> 2) | (B"32'x00000000"))
		val x30 = (((rs2 & B"32'x40000000") =/= B"32'x00000000") ? (rs1 |>> 1) | (B"32'x00000000"))
		val x31 = (((rs2 & B"32'x80000000") =/= B"32'x00000000") ? (rs1 |>> 0) | (B"32'x00000000"))
		x0 ^ x1 ^ x2 ^ x3 ^ x4 ^ x5 ^ x6 ^ x7 ^ x8 ^ x9 ^ x10 ^ x11 ^ x12 ^ x13 ^ x14 ^ x15 ^ x16 ^ x17 ^ x18 ^ x19 ^ x20 ^ x21 ^ x22 ^ x23 ^ x24 ^ x25 ^ x26 ^ x27 ^ x28 ^ x29 ^ x30 ^ x31 // return value	
	}
	def fun_clmulh(rs1:Bits, rs2:Bits) : Bits = {
		val r = fun_clmulr(rs1, rs2) |>> 1
		r // return value
	}

// End prologue
} // object Plugin
class BitManipZbcPlugin(earlyInjection : Boolean = true) extends Plugin[VexRiscv] {
	import BitManipZbcPlugin._
	object IS_BitManipZbc extends Stageable(Bool)
	object BitManipZbc_FINAL_OUTPUT extends Stageable(Bits(32 bits))
	override def setup(pipeline: VexRiscv): Unit = {
		import pipeline.config._
		val immediateActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.IMI,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> Bool(earlyInjection),
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			IS_BitManipZbc -> True
			)
		val binaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> Bool(earlyInjection),
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			RS2_USE -> True,
			IS_BitManipZbc -> True
			)
		val unaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> Bool(earlyInjection),
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			IS_BitManipZbc -> True
			)
		val ternaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.RS,
			SRC3_CTRL                -> Src3CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> Bool(earlyInjection),
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			RS2_USE -> True,
			RS3_USE -> True,
			IS_BitManipZbc -> True
			)
		val immTernaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.IMI,
			SRC3_CTRL                -> Src3CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> Bool(earlyInjection),
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			RS3_USE -> True,
			IS_BitManipZbc -> True
			)
		def CLMUL_KEY = M"0000101----------001-----0110011"
		def CLMULR_KEY = M"0000101----------010-----0110011"
		def CLMULH_KEY = M"0000101----------011-----0110011"
		val decoderService = pipeline.service(classOf[DecoderService])
		decoderService.addDefault(IS_BitManipZbc, False)
		decoderService.add(List(
			CLMUL_KEY	-> (binaryActions ++ List(BitManipZbcCtrl -> BitManipZbcCtrlEnum.CTRL_CLMUL)),
			CLMULR_KEY	-> (binaryActions ++ List(BitManipZbcCtrl -> BitManipZbcCtrlEnum.CTRL_CLMULR)),
			CLMULH_KEY	-> (binaryActions ++ List(BitManipZbcCtrl -> BitManipZbcCtrlEnum.CTRL_CLMULH))
		))
	} // override def setup
	override def build(pipeline: VexRiscv): Unit = {
		import pipeline._
		import pipeline.config._
		execute plug new Area{
			import execute._
			insert(BitManipZbc_FINAL_OUTPUT) := input(BitManipZbcCtrl).mux(
				BitManipZbcCtrlEnum.CTRL_CLMUL -> fun_clmul(input(SRC1),input(SRC2)).asBits,
				BitManipZbcCtrlEnum.CTRL_CLMULR -> fun_clmulr(input(SRC1),input(SRC2)).asBits,
				BitManipZbcCtrlEnum.CTRL_CLMULH -> fun_clmulh(input(SRC1),input(SRC2)).asBits
			) // primary mux
		} // execute plug newArea
		val injectionStage = if(earlyInjection) execute else memory
		injectionStage plug new Area {
			import injectionStage._
			when (arbitration.isValid && input(IS_BitManipZbc)) {
				output(REGFILE_WRITE_DATA) := input(BitManipZbc_FINAL_OUTPUT)
			} // when input is
		} // injectionStage plug newArea
	} // override def build
} // class Plugin
