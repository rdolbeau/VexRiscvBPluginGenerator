// WARNING: this is auto-generated code!
// See https://github.com/rdolbeau/VexRiscvBPluginGenerator/
package vexriscv.plugin
import spinal.core._
import vexriscv.{Stageable, DecoderService, VexRiscv}
object CryptoZknhPlugin {
	object CryptoZknhCtrlsha256sigEnum extends SpinalEnum(binarySequential) {
		 val CTRL_sha256sig0, CTRL_sha256sig1 = newElement()
	}
	object CryptoZknhCtrlsha256sumEnum extends SpinalEnum(binarySequential) {
		 val CTRL_sha256sum0, CTRL_sha256sum1 = newElement()
	}
	object CryptoZknhCtrlEnum extends SpinalEnum(binarySequential) {
		 val CTRL_sha256sig, CTRL_sha256sum = newElement()
	}
	object CryptoZknhCtrlsha256sig extends Stageable(CryptoZknhCtrlsha256sigEnum())
	object CryptoZknhCtrlsha256sum extends Stageable(CryptoZknhCtrlsha256sumEnum())
	object CryptoZknhCtrl extends Stageable(CryptoZknhCtrlEnum())
// Prologue

 	def fun_sha256sig0(rs1:Bits) : Bits = {
	     val r = rs1.rotateRight(7) ^ rs1.rotateRight(18) ^ (rs1 |>> 3)
	     r // return value
	}
 	def fun_sha256sig1(rs1:Bits) : Bits = {
	     val r = rs1.rotateRight(17) ^ rs1.rotateRight(19) ^ (rs1 |>> 10)
	     r // return value
	}
 	def fun_sha256sum0(rs1:Bits) : Bits = {
	     val r = rs1.rotateRight(2) ^ rs1.rotateRight(13) ^ rs1.rotateRight(22)
	     r // return value
	}
 	def fun_sha256sum1(rs1:Bits) : Bits = {
	     val r = rs1.rotateRight(6) ^ rs1.rotateRight(11) ^ rs1.rotateRight(25)
	     r // return value
	}

// End prologue
} // object Plugin
class CryptoZknhPlugin extends Plugin[VexRiscv] {
	import CryptoZknhPlugin._
	object IS_CryptoZknh extends Stageable(Bool)
	override def setup(pipeline: VexRiscv): Unit = {
		import pipeline.config._
		val immediateActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.IMI,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> True,
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			IS_CryptoZknh -> True
			)
		val binaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> True,
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			RS2_USE -> True,
			IS_CryptoZknh -> True
			)
		val unaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> True,
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			IS_CryptoZknh -> True
			)
		def sha256sig0_KEY = M"000011100000-----111-----0101011"
		def sha256sig1_KEY = M"000011100001-----111-----0101011"
		def sha256sum0_KEY = M"000011100010-----111-----0101011"
		def sha256sum1_KEY = M"000011100011-----111-----0101011"
		val decoderService = pipeline.service(classOf[DecoderService])
		decoderService.addDefault(IS_CryptoZknh, False)
		decoderService.add(List(
			sha256sig0_KEY	-> (unaryActions ++ List(CryptoZknhCtrl -> CryptoZknhCtrlEnum.CTRL_sha256sig, CryptoZknhCtrlsha256sig -> CryptoZknhCtrlsha256sigEnum.CTRL_sha256sig0)),
			sha256sig1_KEY	-> (unaryActions ++ List(CryptoZknhCtrl -> CryptoZknhCtrlEnum.CTRL_sha256sig, CryptoZknhCtrlsha256sig -> CryptoZknhCtrlsha256sigEnum.CTRL_sha256sig1)),
			sha256sum0_KEY	-> (unaryActions ++ List(CryptoZknhCtrl -> CryptoZknhCtrlEnum.CTRL_sha256sum, CryptoZknhCtrlsha256sum -> CryptoZknhCtrlsha256sumEnum.CTRL_sha256sum0)),
			sha256sum1_KEY	-> (unaryActions ++ List(CryptoZknhCtrl -> CryptoZknhCtrlEnum.CTRL_sha256sum, CryptoZknhCtrlsha256sum -> CryptoZknhCtrlsha256sumEnum.CTRL_sha256sum1))
		))
	} // override def setup
	override def build(pipeline: VexRiscv): Unit = {
		import pipeline._
		import pipeline.config._
		execute plug new Area{
			import execute._
			val val_sha256sig = input(CryptoZknhCtrlsha256sig).mux(
				CryptoZknhCtrlsha256sigEnum.CTRL_sha256sig0 -> fun_sha256sig0(input(SRC1)),
				CryptoZknhCtrlsha256sigEnum.CTRL_sha256sig1 -> fun_sha256sig1(input(SRC1))
			) // mux sha256sig
			val val_sha256sum = input(CryptoZknhCtrlsha256sum).mux(
				CryptoZknhCtrlsha256sumEnum.CTRL_sha256sum0 -> fun_sha256sum0(input(SRC1)),
				CryptoZknhCtrlsha256sumEnum.CTRL_sha256sum1 -> fun_sha256sum1(input(SRC1))
			) // mux sha256sum
			when (input(IS_CryptoZknh)) {
				execute.output(REGFILE_WRITE_DATA) := input(CryptoZknhCtrl).mux(
					CryptoZknhCtrlEnum.CTRL_sha256sig -> val_sha256sig.asBits,
					CryptoZknhCtrlEnum.CTRL_sha256sum -> val_sha256sum.asBits
				) // primary mux 
			} // when input is 
		} // execute plug newArea
	} // override def build
} // class Plugin
