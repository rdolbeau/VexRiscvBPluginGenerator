// WARNING: this is auto-generated code!
// See https://github.com/rdolbeau/VexRiscvBPluginGenerator/
package vexriscv.plugin
import spinal.core._
import vexriscv.{Stageable, DecoderService, VexRiscv}
object CryptoZksPlugin {
	object CryptoZksCtrlsm3Enum extends SpinalEnum(binarySequential) {
		 val CTRL_SM3P0, CTRL_SM3P1 = newElement()
	}
	object CryptoZksCtrlsm4Enum extends SpinalEnum(binarySequential) {
		 val CTRL_SM4ED, CTRL_SM4KS = newElement()
	}
	object CryptoZksCtrlEnum extends SpinalEnum(binarySequential) {
		 val CTRL_sm3, CTRL_sm4 = newElement()
	}
	object CryptoZksCtrlsm3 extends Stageable(CryptoZksCtrlsm3Enum())
	object CryptoZksCtrlsm4 extends Stageable(CryptoZksCtrlsm4Enum())
	object CryptoZksCtrl extends Stageable(CryptoZksCtrlEnum())
// Prologue

	def fun_sm3p0(rs1: Bits) : Bits = {
		val rs1l9  = rs1(22 downto 0) ## rs1(31 downto 23)
		val rs1l17 = rs1(14 downto 0) ## rs1(31 downto 15)
		val r = rs1 ^ rs1l9 ^ rs1l17
		r // return value
	}
	def fun_sm3p1(rs1: Bits) : Bits = {
		val rs1l15 = rs1(16 downto 0) ## rs1(31 downto 17)
		val rs1l23 = rs1( 8 downto 0) ## rs1(31 downto  9)
		val r = rs1 ^ rs1l15 ^ rs1l23
		r // return value
	}


        // massive MUX implementing SM4SBOX
	def fun_sm4sbox_raw(in:Bits) : Bits = {
	    val x = in(7 downto 0)
	    val r = (x).mux(
				B"8'x00" -> B"8'xD6",
				B"8'x01" -> B"8'x90",
				B"8'x02" -> B"8'xE9",
				B"8'x03" -> B"8'xFE",
				B"8'x04" -> B"8'xCC",
				B"8'x05" -> B"8'xE1",
				B"8'x06" -> B"8'x3D",
				B"8'x07" -> B"8'xB7",
				B"8'x08" -> B"8'x16",
				B"8'x09" -> B"8'xB6",
				B"8'x0a" -> B"8'x14",
				B"8'x0b" -> B"8'xC2",
				B"8'x0c" -> B"8'x28",
				B"8'x0d" -> B"8'xFB",
				B"8'x0e" -> B"8'x2C",
				B"8'x0f" -> B"8'x05",
				B"8'x10" -> B"8'x2B",
				B"8'x11" -> B"8'x67",
				B"8'x12" -> B"8'x9A",
				B"8'x13" -> B"8'x76",
				B"8'x14" -> B"8'x2A",
				B"8'x15" -> B"8'xBE",
				B"8'x16" -> B"8'x04",
				B"8'x17" -> B"8'xC3",
				B"8'x18" -> B"8'xAA",
				B"8'x19" -> B"8'x44",
				B"8'x1a" -> B"8'x13",
				B"8'x1b" -> B"8'x26",
				B"8'x1c" -> B"8'x49",
				B"8'x1d" -> B"8'x86",
				B"8'x1e" -> B"8'x06",
				B"8'x1f" -> B"8'x99",
				B"8'x20" -> B"8'x9C",
				B"8'x21" -> B"8'x42",
				B"8'x22" -> B"8'x50",
				B"8'x23" -> B"8'xF4",
				B"8'x24" -> B"8'x91",
				B"8'x25" -> B"8'xEF",
				B"8'x26" -> B"8'x98",
				B"8'x27" -> B"8'x7A",
				B"8'x28" -> B"8'x33",
				B"8'x29" -> B"8'x54",
				B"8'x2a" -> B"8'x0B",
				B"8'x2b" -> B"8'x43",
				B"8'x2c" -> B"8'xED",
				B"8'x2d" -> B"8'xCF",
				B"8'x2e" -> B"8'xAC",
				B"8'x2f" -> B"8'x62",
				B"8'x30" -> B"8'xE4",
				B"8'x31" -> B"8'xB3",
				B"8'x32" -> B"8'x1C",
				B"8'x33" -> B"8'xA9",
				B"8'x34" -> B"8'xC9",
				B"8'x35" -> B"8'x08",
				B"8'x36" -> B"8'xE8",
				B"8'x37" -> B"8'x95",
				B"8'x38" -> B"8'x80",
				B"8'x39" -> B"8'xDF",
				B"8'x3a" -> B"8'x94",
				B"8'x3b" -> B"8'xFA",
				B"8'x3c" -> B"8'x75",
				B"8'x3d" -> B"8'x8F",
				B"8'x3e" -> B"8'x3F",
				B"8'x3f" -> B"8'xA6",
				B"8'x40" -> B"8'x47",
				B"8'x41" -> B"8'x07",
				B"8'x42" -> B"8'xA7",
				B"8'x43" -> B"8'xFC",
				B"8'x44" -> B"8'xF3",
				B"8'x45" -> B"8'x73",
				B"8'x46" -> B"8'x17",
				B"8'x47" -> B"8'xBA",
				B"8'x48" -> B"8'x83",
				B"8'x49" -> B"8'x59",
				B"8'x4a" -> B"8'x3C",
				B"8'x4b" -> B"8'x19",
				B"8'x4c" -> B"8'xE6",
				B"8'x4d" -> B"8'x85",
				B"8'x4e" -> B"8'x4F",
				B"8'x4f" -> B"8'xA8",
				B"8'x50" -> B"8'x68",
				B"8'x51" -> B"8'x6B",
				B"8'x52" -> B"8'x81",
				B"8'x53" -> B"8'xB2",
				B"8'x54" -> B"8'x71",
				B"8'x55" -> B"8'x64",
				B"8'x56" -> B"8'xDA",
				B"8'x57" -> B"8'x8B",
				B"8'x58" -> B"8'xF8",
				B"8'x59" -> B"8'xEB",
				B"8'x5a" -> B"8'x0F",
				B"8'x5b" -> B"8'x4B",
				B"8'x5c" -> B"8'x70",
				B"8'x5d" -> B"8'x56",
				B"8'x5e" -> B"8'x9D",
				B"8'x5f" -> B"8'x35",
				B"8'x60" -> B"8'x1E",
				B"8'x61" -> B"8'x24",
				B"8'x62" -> B"8'x0E",
				B"8'x63" -> B"8'x5E",
				B"8'x64" -> B"8'x63",
				B"8'x65" -> B"8'x58",
				B"8'x66" -> B"8'xD1",
				B"8'x67" -> B"8'xA2",
				B"8'x68" -> B"8'x25",
				B"8'x69" -> B"8'x22",
				B"8'x6a" -> B"8'x7C",
				B"8'x6b" -> B"8'x3B",
				B"8'x6c" -> B"8'x01",
				B"8'x6d" -> B"8'x21",
				B"8'x6e" -> B"8'x78",
				B"8'x6f" -> B"8'x87",
				B"8'x70" -> B"8'xD4",
				B"8'x71" -> B"8'x00",
				B"8'x72" -> B"8'x46",
				B"8'x73" -> B"8'x57",
				B"8'x74" -> B"8'x9F",
				B"8'x75" -> B"8'xD3",
				B"8'x76" -> B"8'x27",
				B"8'x77" -> B"8'x52",
				B"8'x78" -> B"8'x4C",
				B"8'x79" -> B"8'x36",
				B"8'x7a" -> B"8'x02",
				B"8'x7b" -> B"8'xE7",
				B"8'x7c" -> B"8'xA0",
				B"8'x7d" -> B"8'xC4",
				B"8'x7e" -> B"8'xC8",
				B"8'x7f" -> B"8'x9E",
				B"8'x80" -> B"8'xEA",
				B"8'x81" -> B"8'xBF",
				B"8'x82" -> B"8'x8A",
				B"8'x83" -> B"8'xD2",
				B"8'x84" -> B"8'x40",
				B"8'x85" -> B"8'xC7",
				B"8'x86" -> B"8'x38",
				B"8'x87" -> B"8'xB5",
				B"8'x88" -> B"8'xA3",
				B"8'x89" -> B"8'xF7",
				B"8'x8a" -> B"8'xF2",
				B"8'x8b" -> B"8'xCE",
				B"8'x8c" -> B"8'xF9",
				B"8'x8d" -> B"8'x61",
				B"8'x8e" -> B"8'x15",
				B"8'x8f" -> B"8'xA1",
				B"8'x90" -> B"8'xE0",
				B"8'x91" -> B"8'xAE",
				B"8'x92" -> B"8'x5D",
				B"8'x93" -> B"8'xA4",
				B"8'x94" -> B"8'x9B",
				B"8'x95" -> B"8'x34",
				B"8'x96" -> B"8'x1A",
				B"8'x97" -> B"8'x55",
				B"8'x98" -> B"8'xAD",
				B"8'x99" -> B"8'x93",
				B"8'x9a" -> B"8'x32",
				B"8'x9b" -> B"8'x30",
				B"8'x9c" -> B"8'xF5",
				B"8'x9d" -> B"8'x8C",
				B"8'x9e" -> B"8'xB1",
				B"8'x9f" -> B"8'xE3",
				B"8'xa0" -> B"8'x1D",
				B"8'xa1" -> B"8'xF6",
				B"8'xa2" -> B"8'xE2",
				B"8'xa3" -> B"8'x2E",
				B"8'xa4" -> B"8'x82",
				B"8'xa5" -> B"8'x66",
				B"8'xa6" -> B"8'xCA",
				B"8'xa7" -> B"8'x60",
				B"8'xa8" -> B"8'xC0",
				B"8'xa9" -> B"8'x29",
				B"8'xaa" -> B"8'x23",
				B"8'xab" -> B"8'xAB",
				B"8'xac" -> B"8'x0D",
				B"8'xad" -> B"8'x53",
				B"8'xae" -> B"8'x4E",
				B"8'xaf" -> B"8'x6F",
				B"8'xb0" -> B"8'xD5",
				B"8'xb1" -> B"8'xDB",
				B"8'xb2" -> B"8'x37",
				B"8'xb3" -> B"8'x45",
				B"8'xb4" -> B"8'xDE",
				B"8'xb5" -> B"8'xFD",
				B"8'xb6" -> B"8'x8E",
				B"8'xb7" -> B"8'x2F",
				B"8'xb8" -> B"8'x03",
				B"8'xb9" -> B"8'xFF",
				B"8'xba" -> B"8'x6A",
				B"8'xbb" -> B"8'x72",
				B"8'xbc" -> B"8'x6D",
				B"8'xbd" -> B"8'x6C",
				B"8'xbe" -> B"8'x5B",
				B"8'xbf" -> B"8'x51",
				B"8'xc0" -> B"8'x8D",
				B"8'xc1" -> B"8'x1B",
				B"8'xc2" -> B"8'xAF",
				B"8'xc3" -> B"8'x92",
				B"8'xc4" -> B"8'xBB",
				B"8'xc5" -> B"8'xDD",
				B"8'xc6" -> B"8'xBC",
				B"8'xc7" -> B"8'x7F",
				B"8'xc8" -> B"8'x11",
				B"8'xc9" -> B"8'xD9",
				B"8'xca" -> B"8'x5C",
				B"8'xcb" -> B"8'x41",
				B"8'xcc" -> B"8'x1F",
				B"8'xcd" -> B"8'x10",
				B"8'xce" -> B"8'x5A",
				B"8'xcf" -> B"8'xD8",
				B"8'xd0" -> B"8'x0A",
				B"8'xd1" -> B"8'xC1",
				B"8'xd2" -> B"8'x31",
				B"8'xd3" -> B"8'x88",
				B"8'xd4" -> B"8'xA5",
				B"8'xd5" -> B"8'xCD",
				B"8'xd6" -> B"8'x7B",
				B"8'xd7" -> B"8'xBD",
				B"8'xd8" -> B"8'x2D",
				B"8'xd9" -> B"8'x74",
				B"8'xda" -> B"8'xD0",
				B"8'xdb" -> B"8'x12",
				B"8'xdc" -> B"8'xB8",
				B"8'xdd" -> B"8'xE5",
				B"8'xde" -> B"8'xB4",
				B"8'xdf" -> B"8'xB0",
				B"8'xe0" -> B"8'x89",
				B"8'xe1" -> B"8'x69",
				B"8'xe2" -> B"8'x97",
				B"8'xe3" -> B"8'x4A",
				B"8'xe4" -> B"8'x0C",
				B"8'xe5" -> B"8'x96",
				B"8'xe6" -> B"8'x77",
				B"8'xe7" -> B"8'x7E",
				B"8'xe8" -> B"8'x65",
				B"8'xe9" -> B"8'xB9",
				B"8'xea" -> B"8'xF1",
				B"8'xeb" -> B"8'x09",
				B"8'xec" -> B"8'xC5",
				B"8'xed" -> B"8'x6E",
				B"8'xee" -> B"8'xC6",
				B"8'xef" -> B"8'x84",
				B"8'xf0" -> B"8'x18",
				B"8'xf1" -> B"8'xF0",
				B"8'xf2" -> B"8'x7D",
				B"8'xf3" -> B"8'xEC",
				B"8'xf4" -> B"8'x3A",
				B"8'xf5" -> B"8'xDC",
				B"8'xf6" -> B"8'x4D",
				B"8'xf7" -> B"8'x20",
				B"8'xf8" -> B"8'x79",
				B"8'xf9" -> B"8'xEE",
				B"8'xfa" -> B"8'x5F",
				B"8'xfb" -> B"8'x3E",
				B"8'xfc" -> B"8'xD7",
				B"8'xfd" -> B"8'xCB",
				B"8'xfe" -> B"8'x39",
				B"8'xff" -> B"8'x48"
		)
		r // return value
	}
	def fun_sm4ed(rs1:Bits, rs2:Bits, sel: Bits) : Bits = {
	    val idx = (sel).mux(
			B"2'b00" -> rs2( 7 downto  0),
			B"2'b01" -> rs2(15 downto  8),
			B"2'b10" -> rs2(23 downto 16),
			B"2'b11" -> rs2(31 downto 24)
			)
	    val x = fun_sm4sbox_raw(idx)
		val y = x.resize(32) ^
		        (x <<  8).resize(32) ^
				(x <<  2).resize(32) ^
			  	(x << 18).resize(32) ^
				((x & B"8'x3F") << 26).resize(32) ^
				((x & B"8'xC0") << 10).resize(32)
		val r = (sel).mux(
			B"2'b00" -> y(31 downto  0),
			B"2'b01" -> y(23 downto  0) ## y(31 downto 24),
			B"2'b10" -> y(15 downto  0) ## y(31 downto 16),
			B"2'b11" -> y( 7 downto  0) ## y(31 downto  8)
			)
		rs1 ^ r // return value
	}
	def fun_sm4ks(rs1:Bits, rs2:Bits, sel: Bits) : Bits = {
	    val idx = (sel).mux(
			B"2'b00" -> rs2( 7 downto  0),
			B"2'b01" -> rs2(15 downto  8),
			B"2'b10" -> rs2(23 downto 16),
			B"2'b11" -> rs2(31 downto 24)
			)
	    val x = fun_sm4sbox_raw(idx)
		val y = x.resize(32) ^
			    ((x & B"8'x07" ) << 29).resize(32) ^
				((x & B"8'xFE" ) <<  7).resize(32) ^
				((x & B"8'x01" ) << 23).resize(32) ^
				((x & B"8'xF8" ) << 13).resize(32)
		val r = (sel).mux(
			B"2'b00" -> y(31 downto  0),
			B"2'b01" -> y(23 downto  0) ## y(31 downto 24),
			B"2'b10" -> y(15 downto  0) ## y(31 downto 16),
			B"2'b11" -> y( 7 downto  0) ## y(31 downto  8)
			)
		rs1 ^ r // return value
	}

// End prologue
} // object Plugin
class CryptoZksPlugin(earlyInjection : Boolean = true) extends Plugin[VexRiscv] {
	import CryptoZksPlugin._
	object IS_CryptoZks extends Stageable(Bool)
	object CryptoZks_FINAL_OUTPUT extends Stageable(Bits(32 bits))
	override def setup(pipeline: VexRiscv): Unit = {
		import pipeline.config._
		val immediateActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.IMI,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> Bool(earlyInjection),
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			IS_CryptoZks -> True
			)
		val binaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> Bool(earlyInjection),
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			RS2_USE -> True,
			IS_CryptoZks -> True
			)
		val unaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> Bool(earlyInjection),
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			IS_CryptoZks -> True
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
			IS_CryptoZks -> True
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
			IS_CryptoZks -> True
			)
		def SM3P0_KEY = M"000100001000-----001-----0010011"
		def SM3P1_KEY = M"000100001001-----001-----0010011"
		def SM4ED_KEY = M"--11000----------000-----0110011"
		def SM4KS_KEY = M"--11010----------000-----0110011"
		val decoderService = pipeline.service(classOf[DecoderService])
		decoderService.addDefault(IS_CryptoZks, False)
		decoderService.add(List(
			SM3P0_KEY	-> (unaryActions ++ List(CryptoZksCtrl -> CryptoZksCtrlEnum.CTRL_sm3, CryptoZksCtrlsm3 -> CryptoZksCtrlsm3Enum.CTRL_SM3P0)),
			SM3P1_KEY	-> (unaryActions ++ List(CryptoZksCtrl -> CryptoZksCtrlEnum.CTRL_sm3, CryptoZksCtrlsm3 -> CryptoZksCtrlsm3Enum.CTRL_SM3P1)),
			SM4ED_KEY	-> (binaryActions ++ List(CryptoZksCtrl -> CryptoZksCtrlEnum.CTRL_sm4, CryptoZksCtrlsm4 -> CryptoZksCtrlsm4Enum.CTRL_SM4ED)),
			SM4KS_KEY	-> (binaryActions ++ List(CryptoZksCtrl -> CryptoZksCtrlEnum.CTRL_sm4, CryptoZksCtrlsm4 -> CryptoZksCtrlsm4Enum.CTRL_SM4KS))
		))
	} // override def setup
	override def build(pipeline: VexRiscv): Unit = {
		import pipeline._
		import pipeline.config._
		execute plug new Area{
			import execute._
			val val_sm3 = input(CryptoZksCtrlsm3).mux(
				CryptoZksCtrlsm3Enum.CTRL_SM3P0 -> fun_sm3p0(input(SRC1)).asBits,
				CryptoZksCtrlsm3Enum.CTRL_SM3P1 -> fun_sm3p1(input(SRC1)).asBits
			) // mux sm3
			val val_sm4 = input(CryptoZksCtrlsm4).mux(
				CryptoZksCtrlsm4Enum.CTRL_SM4ED -> fun_sm4ed(input(SRC1), input(SRC2), input(INSTRUCTION)(31 downto 30)).asBits,
				CryptoZksCtrlsm4Enum.CTRL_SM4KS -> fun_sm4ks(input(SRC1), input(SRC2), input(INSTRUCTION)(31 downto 30)).asBits
			) // mux sm4
			insert(CryptoZks_FINAL_OUTPUT) := input(CryptoZksCtrl).mux(
				CryptoZksCtrlEnum.CTRL_sm3 -> val_sm3.asBits,
				CryptoZksCtrlEnum.CTRL_sm4 -> val_sm4.asBits
			) // primary mux
		} // execute plug newArea
		val injectionStage = if(earlyInjection) execute else memory
		injectionStage plug new Area {
			import injectionStage._
			when (arbitration.isValid && input(IS_CryptoZks)) {
				output(REGFILE_WRITE_DATA) := input(CryptoZks_FINAL_OUTPUT)
			} // when input is
		} // injectionStage plug newArea
	} // override def build
} // class Plugin
