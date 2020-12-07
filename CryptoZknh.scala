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
	object CryptoZknhCtrlsha512sigEnum extends SpinalEnum(binarySequential) {
		 val CTRL_sha512sig0h, CTRL_sha512sig0l, CTRL_sha512sig1h, CTRL_sha512sig1l = newElement()
	}
	object CryptoZknhCtrlsha512sumEnum extends SpinalEnum(binarySequential) {
		 val CTRL_sha512sum0r, CTRL_sha512sum1r = newElement()
	}
	object CryptoZknhCtrlEnum extends SpinalEnum(binarySequential) {
		 val CTRL_sha256sig, CTRL_sha256sum, CTRL_sha512sig, CTRL_sha512sum = newElement()
	}
	object CryptoZknhCtrlsha256sig extends Stageable(CryptoZknhCtrlsha256sigEnum())
	object CryptoZknhCtrlsha256sum extends Stageable(CryptoZknhCtrlsha256sumEnum())
	object CryptoZknhCtrlsha512sig extends Stageable(CryptoZknhCtrlsha512sigEnum())
	object CryptoZknhCtrlsha512sum extends Stageable(CryptoZknhCtrlsha512sumEnum())
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

	def fun_sha512sig0l(rs1:Bits, rs2:Bits) : Bits = {
	    val r = (rs1 |>> 1) ^ (rs1 |>> 7) ^ (rs1 |>> 8) ^ (rs2 |<< 31) ^ (rs2 |<< 25) ^ (rs2 |<< 24)
	    r // return value
	}
	def fun_sha512sig0h(rs1:Bits, rs2:Bits) : Bits = {
	    val r = (rs1 |>> 1) ^ (rs1 |>> 7) ^ (rs1 |>> 8) ^ (rs2 |<< 31)                ^ (rs2 |<< 24)
	    r // return value
	}
	def fun_sha512sig1l(rs1:Bits, rs2:Bits) : Bits = {
	    val r = (rs1 |<< 3) ^ (rs1 |>> 6) ^ (rs1 |>> 19) ^ (rs2 |>> 29) ^ (rs2 |<< 26) ^ (rs2 |<< 13)
	    r // return value
	}
	def fun_sha512sig1h(rs1:Bits, rs2:Bits) : Bits = {
	    val r = (rs1 |<< 3) ^ (rs1 |>> 6) ^ (rs1 |>> 19) ^ (rs2 |>> 29)                ^ (rs2 |<< 13)
	    r // return value
	}
	def fun_sha512sum0r(rs1:Bits, rs2:Bits) : Bits = {
	    val r = (rs1 |<< 25) ^ (rs1 |<< 30) ^ (rs1 |>> 28) ^ (rs2 |>> 7) ^ (rs2 |>> 2) ^ (rs2 |<< 4)
	    r // return value
	}
	def fun_sha512sum1r(rs1:Bits, rs2:Bits) : Bits = {
	    val r = (rs1 |<< 23) ^ (rs1 |>> 14) ^ (rs1 |>> 18) ^ (rs2 |>> 9) ^ (rs2 |<< 18) ^ (rs2 |<< 14)
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
		val ternaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.RS,
			SRC3_CTRL                -> Src2CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> True,
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			RS2_USE -> True,
			RS3_USE -> True,
			IS_CryptoZknh -> True
			)
		val immTernaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.IMI,
			SRC3_CTRL                -> Src2CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> True,
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			RS3_USE -> True,
			IS_CryptoZknh -> True
			)
		def sha256sig0_KEY = M"000100000010-----001-----0010011"
		def sha256sig1_KEY = M"000100000011-----001-----0010011"
		def sha256sum0_KEY = M"000100000000-----001-----0010011"
		def sha256sum1_KEY = M"000100000001-----001-----0010011"
		def sha512sig0l_KEY = M"0101010----------000-----0110011"
		def sha512sig0h_KEY = M"0101110----------000-----0110011"
		def sha512sig1l_KEY = M"0101011----------000-----0110011"
		def sha512sig1h_KEY = M"0101111----------000-----0110011"
		def sha512sum0r_KEY = M"0101000----------000-----0110011"
		def sha512sum1r_KEY = M"0101001----------000-----0110011"
		val decoderService = pipeline.service(classOf[DecoderService])
		decoderService.addDefault(IS_CryptoZknh, False)
		decoderService.add(List(
			sha256sig0_KEY	-> (unaryActions ++ List(CryptoZknhCtrl -> CryptoZknhCtrlEnum.CTRL_sha256sig, CryptoZknhCtrlsha256sig -> CryptoZknhCtrlsha256sigEnum.CTRL_sha256sig0)),
			sha256sig1_KEY	-> (unaryActions ++ List(CryptoZknhCtrl -> CryptoZknhCtrlEnum.CTRL_sha256sig, CryptoZknhCtrlsha256sig -> CryptoZknhCtrlsha256sigEnum.CTRL_sha256sig1)),
			sha256sum0_KEY	-> (unaryActions ++ List(CryptoZknhCtrl -> CryptoZknhCtrlEnum.CTRL_sha256sum, CryptoZknhCtrlsha256sum -> CryptoZknhCtrlsha256sumEnum.CTRL_sha256sum0)),
			sha256sum1_KEY	-> (unaryActions ++ List(CryptoZknhCtrl -> CryptoZknhCtrlEnum.CTRL_sha256sum, CryptoZknhCtrlsha256sum -> CryptoZknhCtrlsha256sumEnum.CTRL_sha256sum1)),
			sha512sig0l_KEY	-> (binaryActions ++ List(CryptoZknhCtrl -> CryptoZknhCtrlEnum.CTRL_sha512sig, CryptoZknhCtrlsha512sig -> CryptoZknhCtrlsha512sigEnum.CTRL_sha512sig0l)),
			sha512sig0h_KEY	-> (binaryActions ++ List(CryptoZknhCtrl -> CryptoZknhCtrlEnum.CTRL_sha512sig, CryptoZknhCtrlsha512sig -> CryptoZknhCtrlsha512sigEnum.CTRL_sha512sig0h)),
			sha512sig1l_KEY	-> (binaryActions ++ List(CryptoZknhCtrl -> CryptoZknhCtrlEnum.CTRL_sha512sig, CryptoZknhCtrlsha512sig -> CryptoZknhCtrlsha512sigEnum.CTRL_sha512sig1l)),
			sha512sig1h_KEY	-> (binaryActions ++ List(CryptoZknhCtrl -> CryptoZknhCtrlEnum.CTRL_sha512sig, CryptoZknhCtrlsha512sig -> CryptoZknhCtrlsha512sigEnum.CTRL_sha512sig1h)),
			sha512sum0r_KEY	-> (binaryActions ++ List(CryptoZknhCtrl -> CryptoZknhCtrlEnum.CTRL_sha512sum, CryptoZknhCtrlsha512sum -> CryptoZknhCtrlsha512sumEnum.CTRL_sha512sum0r)),
			sha512sum1r_KEY	-> (binaryActions ++ List(CryptoZknhCtrl -> CryptoZknhCtrlEnum.CTRL_sha512sum, CryptoZknhCtrlsha512sum -> CryptoZknhCtrlsha512sumEnum.CTRL_sha512sum1r))
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
			val val_sha512sig = input(CryptoZknhCtrlsha512sig).mux(
				CryptoZknhCtrlsha512sigEnum.CTRL_sha512sig0h -> fun_sha512sig0h(input(SRC1),input(SRC2)),
				CryptoZknhCtrlsha512sigEnum.CTRL_sha512sig0l -> fun_sha512sig0l(input(SRC1),input(SRC2)),
				CryptoZknhCtrlsha512sigEnum.CTRL_sha512sig1h -> fun_sha512sig1h(input(SRC1),input(SRC2)),
				CryptoZknhCtrlsha512sigEnum.CTRL_sha512sig1l -> fun_sha512sig1l(input(SRC1),input(SRC2))
			) // mux sha512sig
			val val_sha512sum = input(CryptoZknhCtrlsha512sum).mux(
				CryptoZknhCtrlsha512sumEnum.CTRL_sha512sum0r -> fun_sha512sum0r(input(SRC1),input(SRC2)),
				CryptoZknhCtrlsha512sumEnum.CTRL_sha512sum1r -> fun_sha512sum1r(input(SRC1),input(SRC2))
			) // mux sha512sum
			when (input(IS_CryptoZknh)) {
				execute.output(REGFILE_WRITE_DATA) := input(CryptoZknhCtrl).mux(
					CryptoZknhCtrlEnum.CTRL_sha256sig -> val_sha256sig.asBits,
					CryptoZknhCtrlEnum.CTRL_sha256sum -> val_sha256sum.asBits,
					CryptoZknhCtrlEnum.CTRL_sha512sig -> val_sha512sig.asBits,
					CryptoZknhCtrlEnum.CTRL_sha512sum -> val_sha512sum.asBits
				) // primary mux 
			} // when input is 
		} // execute plug newArea
	} // override def build
} // class Plugin
