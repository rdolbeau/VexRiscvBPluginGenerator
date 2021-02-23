// WARNING: this is auto-generated code!
// See https://github.com/rdolbeau/VexRiscvBPluginGenerator/
package vexriscv.plugin
import spinal.core._
import vexriscv.{Stageable, DecoderService, VexRiscv}
object BitManipZbe2cyclesPlugin {
	object BitManipZbe2cyclesCtrlbcompressEnum extends SpinalEnum(binarySequential) {
		 val CTRL_BCOMPRESS, CTRL_BDECOMPRESS = newElement()
	}
	object BitManipZbe2cyclesCtrlEnum extends SpinalEnum(binarySequential) {
		 val CTRL_bcompress = newElement()
	}
	object BitManipZbe2cyclesCtrlbcompress extends Stageable(BitManipZbe2cyclesCtrlbcompressEnum())
	object BitManipZbe2cyclesCtrl extends Stageable(BitManipZbe2cyclesCtrlEnum())
// Prologue

   def fun_compress1(rs1:Bits, rs2: Bits) : Bits = {
	   var r = B"16'x0000"
	   var j = (B"5'b00000").asUInt
	   for (i <- 0 to 15) {
	   	   val rs2i = rs2(i).asUInt
	   	   val rs1i = rs2(i) & rs1(i)
	   	   r = r | (rs1i.asBits << j).resize(16)
		   j = j + rs2i
	   }
	   j.asBits.resize(5) ## r ## rs1(31 downto 16) ## rs2(31 downto 16)// return value
   }
   def fun_compress2(x:Bits) : Bits = {
       val rs2 = x(15 downto 0)
	   val rs1 = x(31 downto 16)
	   var r = B"16'x0000" ## x(47 downto 32)
	   var j = x(52 downto 48).asUInt
	   
	   for (i <- 0 to 15) {
	   	   val rs2i = rs2(i).asUInt
	   	   val rs1i = rs2(i) & rs1(i)
	   	   r = r | (rs1i.asBits << j).resize(32)
		   j = j + rs2i
	   }
	   r(31 downto 0) // return value
   }
   def fun_decompress1(rs1:Bits, rs2: Bits) : Bits = {
	   var r = B"16'x0000"
	   var j = (B"5'b00000").asUInt
	   for (i <- 0 to 15) {
	   	   val rs2i = rs2(i).asUInt
	   	   val rs1j = rs2(i) & (rs1 >> j)(0)
	   	   r = r | (rs1j.asBits << i).resize(16)
		   j = j + rs2i
	   }
	   j.asBits.resize(5) ## r ## rs1(31 downto 0) ## rs2(31 downto 16)// return value
   }
   def fun_decompress2(x:Bits) : Bits = {
       val rs2 = x(15 downto 0)
	   val rs1 = x(47 downto 16)
	   var r = B"16'x0000" ## x(63 downto 48)
	   var j = x(68 downto 64).asUInt
	   
	   for (i <- 0 to 15) {
	   	   val rs2i = rs2(i).asUInt
	   	   val rs1j = rs2(i) & (rs1 >> j)(0)
	   	   r = r | (rs1j.asBits << (i+16)).asBits.resize(32)
		   j = j + rs2i
	   }
	   r(31 downto 0) // return value
   }

// End prologue
} // object Plugin
class BitManipZbe2cyclesPlugin(earlyInjection : Boolean = true) extends Plugin[VexRiscv] {
	import BitManipZbe2cyclesPlugin._
	object IS_BitManipZbe2cycles extends Stageable(Bool)
	object BitManipZbe2cycles_FINAL_OUTPUT extends Stageable(Bits(32 bits))
	object BitManipZbe2cycles_INTERMEDIATE_BCOMPRESS53 extends Stageable(Bits(53 bits))
	object BitManipZbe2cycles_INTERMEDIATE_BDECOMPRESS69 extends Stageable(Bits(69 bits))
	override def setup(pipeline: VexRiscv): Unit = {
		import pipeline.config._
		val immediateActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.IMI,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> False,
			BYPASSABLE_MEMORY_STAGE  -> Bool(earlyInjection),
			RS1_USE -> True,
			IS_BitManipZbe2cycles -> True
			)
		val binaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> False,
			BYPASSABLE_MEMORY_STAGE  -> Bool(earlyInjection),
			RS1_USE -> True,
			RS2_USE -> True,
			IS_BitManipZbe2cycles -> True
			)
		val unaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> False,
			BYPASSABLE_MEMORY_STAGE  -> Bool(earlyInjection),
			RS1_USE -> True,
			IS_BitManipZbe2cycles -> True
			)
		val ternaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.RS,
			SRC3_CTRL                -> Src3CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> False,
			BYPASSABLE_MEMORY_STAGE  -> Bool(earlyInjection),
			RS1_USE -> True,
			RS2_USE -> True,
			RS3_USE -> True,
			IS_BitManipZbe2cycles -> True
			)
		val immTernaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.IMI,
			SRC3_CTRL                -> Src3CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> False,
			BYPASSABLE_MEMORY_STAGE  -> Bool(earlyInjection),
			RS1_USE -> True,
			RS3_USE -> True,
			IS_BitManipZbe2cycles -> True
			)
		def BDECOMPRESS_KEY = M"0100100----------110-----0110011"
		def BCOMPRESS_KEY = M"0000100----------110-----0110011"
		val decoderService = pipeline.service(classOf[DecoderService])
		decoderService.addDefault(IS_BitManipZbe2cycles, False)
		decoderService.add(List(
			BDECOMPRESS_KEY	-> (binaryActions ++ List(BitManipZbe2cyclesCtrl -> BitManipZbe2cyclesCtrlEnum.CTRL_bcompress, BitManipZbe2cyclesCtrlbcompress -> BitManipZbe2cyclesCtrlbcompressEnum.CTRL_BDECOMPRESS)),
			BCOMPRESS_KEY	-> (binaryActions ++ List(BitManipZbe2cyclesCtrl -> BitManipZbe2cyclesCtrlEnum.CTRL_bcompress, BitManipZbe2cyclesCtrlbcompress -> BitManipZbe2cyclesCtrlbcompressEnum.CTRL_BCOMPRESS))
		))
	} // override def setup
	override def build(pipeline: VexRiscv): Unit = {
		import pipeline._
		import pipeline.config._
		execute plug new Area{
			import execute._
			insert(BitManipZbe2cycles_INTERMEDIATE_BCOMPRESS53) := fun_compress1(input(SRC1), input(SRC2)).asBits
			insert(BitManipZbe2cycles_INTERMEDIATE_BDECOMPRESS69) := fun_decompress1(input(SRC1), input(SRC2)).asBits
		} // execute plug newArea
		memory plug new Area{
			import memory._
			val val_bcompress = input(BitManipZbe2cyclesCtrlbcompress).mux(
				BitManipZbe2cyclesCtrlbcompressEnum.CTRL_BCOMPRESS -> fun_compress2(input(BitManipZbe2cycles_INTERMEDIATE_BCOMPRESS53)).asBits.asBits,
				BitManipZbe2cyclesCtrlbcompressEnum.CTRL_BDECOMPRESS -> fun_decompress2(input(BitManipZbe2cycles_INTERMEDIATE_BDECOMPRESS69)).asBits.asBits
			) // mux bcompress
			insert(BitManipZbe2cycles_FINAL_OUTPUT) := val_bcompress.asBits
		} // memory plug newArea
		val injectionStage = if(earlyInjection) memory else writeBack
		injectionStage plug new Area {
			import injectionStage._
			when (arbitration.isValid && input(IS_BitManipZbe2cycles)) {
				output(REGFILE_WRITE_DATA) := input(BitManipZbe2cycles_FINAL_OUTPUT)
			} // when input is
		} // injectionStage plug newArea
	} // override def build
} // class Plugin
