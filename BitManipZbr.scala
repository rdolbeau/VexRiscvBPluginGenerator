// WARNING: this is auto-generated code!
// See https://github.com/rdolbeau/VexRiscvBPluginGenerator/
package vexriscv.plugin
import spinal.core._
import vexriscv.{Stageable, DecoderService, VexRiscv}
object BitManipZbrPlugin {
	object BitManipZbrCtrlCRC32xEnum extends SpinalEnum(binarySequential) {
		 val CTRL_CRC32xdotB, CTRL_CRC32xdotH, CTRL_CRC32xdotW = newElement()
	}
	object BitManipZbrCtrlEnum extends SpinalEnum(binarySequential) {
		 val CTRL_CRC32x = newElement()
	}
	object BitManipZbrCtrlCRC32x extends Stageable(BitManipZbrCtrlCRC32xEnum())
	object BitManipZbrCtrl extends Stageable(BitManipZbrCtrlEnum())
// Prologue

	def fun_crc32xdotb(rs1: Bits, isC : Bool) : Bits = {
	   val p = ((isC === True) ? (B"32'x82F63B78") | (B"32'xEDB88320"))
	   var x = rs1
	   for (i <- 0 to 7) {
	   	   x = (x |>> 1) ^ ((x(0) === True) ? (p) | (B"32'x00000000"))
	   }
	   val r = x
	   r // return value
	}
	def fun_crc32xdoth(rs1: Bits, isC : Bool) : Bits = {
	   val p = ((isC === True) ? (B"32'x82F63B78") | (B"32'xEDB88320"))
	   var x = rs1
	   for (i <- 0 to 15) {
	   	   x = (x |>> 1) ^ ((x(0) === True) ? (p) | (B"32'x00000000"))
	   }
	   val r = x
	   r // return value
	}
	def fun_crc32xdotw(rs1: Bits, isC : Bool) : Bits = {
	   val p = ((isC === True) ? (B"32'x82F63B78") | (B"32'xEDB88320"))
	   var x = rs1
	   for (i <- 0 to 31) {
	   	   x = (x |>> 1) ^ ((x(0) === True) ? (p) | (B"32'x00000000"))
	   }
	   val r = x
	   r // return value
	}

// End prologue
} // object Plugin
class BitManipZbrPlugin(earlyInjection : Boolean = true) extends Plugin[VexRiscv] {
	import BitManipZbrPlugin._
	object IS_BitManipZbr extends Stageable(Bool)
	object BitManipZbr_FINAL_OUTPUT extends Stageable(Bits(32 bits))
	override def setup(pipeline: VexRiscv): Unit = {
		import pipeline.config._
		val immediateActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.IMI,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> Bool(earlyInjection),
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			IS_BitManipZbr -> True
			)
		val binaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> Bool(earlyInjection),
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			RS2_USE -> True,
			IS_BitManipZbr -> True
			)
		val unaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> Bool(earlyInjection),
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			IS_BitManipZbr -> True
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
			IS_BitManipZbr -> True
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
			IS_BitManipZbr -> True
			)
		def CRC32xdotB_KEY = M"01100001-000-----001-----0010011"
		def CRC32xdotH_KEY = M"01100001-001-----001-----0010011"
		def CRC32xdotW_KEY = M"01100001-010-----001-----0010011"
		val decoderService = pipeline.service(classOf[DecoderService])
		decoderService.addDefault(IS_BitManipZbr, False)
		decoderService.add(List(
			CRC32xdotB_KEY	-> (unaryActions ++ List(BitManipZbrCtrl -> BitManipZbrCtrlEnum.CTRL_CRC32x, BitManipZbrCtrlCRC32x -> BitManipZbrCtrlCRC32xEnum.CTRL_CRC32xdotB)),
			CRC32xdotH_KEY	-> (unaryActions ++ List(BitManipZbrCtrl -> BitManipZbrCtrlEnum.CTRL_CRC32x, BitManipZbrCtrlCRC32x -> BitManipZbrCtrlCRC32xEnum.CTRL_CRC32xdotH)),
			CRC32xdotW_KEY	-> (unaryActions ++ List(BitManipZbrCtrl -> BitManipZbrCtrlEnum.CTRL_CRC32x, BitManipZbrCtrlCRC32x -> BitManipZbrCtrlCRC32xEnum.CTRL_CRC32xdotW))
		))
	} // override def setup
	override def build(pipeline: VexRiscv): Unit = {
		import pipeline._
		import pipeline.config._
		execute plug new Area{
			import execute._
			val val_CRC32x = input(BitManipZbrCtrlCRC32x).mux(
				BitManipZbrCtrlCRC32xEnum.CTRL_CRC32xdotB -> fun_crc32xdotb(input(SRC1), input(INSTRUCTION)(23)).asBits,
				BitManipZbrCtrlCRC32xEnum.CTRL_CRC32xdotH -> fun_crc32xdoth(input(SRC1), input(INSTRUCTION)(23)).asBits,
				BitManipZbrCtrlCRC32xEnum.CTRL_CRC32xdotW -> fun_crc32xdotw(input(SRC1), input(INSTRUCTION)(23)).asBits
			) // mux CRC32x
			insert(BitManipZbr_FINAL_OUTPUT) := val_CRC32x.asBits
		} // execute plug newArea
		val injectionStage = if(earlyInjection) execute else memory
		injectionStage plug new Area {
			import injectionStage._
			when (arbitration.isValid && input(IS_BitManipZbr)) {
				output(REGFILE_WRITE_DATA) := input(BitManipZbr_FINAL_OUTPUT)
			} // when input is
		} // injectionStage plug newArea
	} // override def build
} // class Plugin
