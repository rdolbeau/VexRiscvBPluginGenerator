// WARNING: this is auto-generated code!
// See https://github.com/rdolbeau/VexRiscvBPluginGenerator/
package vexriscv.plugin
import spinal.core._
import vexriscv.{Stageable, DecoderService, VexRiscv}
object CryptoZknePlugin {
	object CryptoZkneCtrlaes0Enum extends SpinalEnum(binarySequential) {
		 val CTRL_aes32esmi0, CTRL_aes32esmi1, CTRL_aes32esmi2, CTRL_aes32esmi3 = newElement()
	}
	object CryptoZkneCtrlaes1Enum extends SpinalEnum(binarySequential) {
		 val CTRL_aes32esi0, CTRL_aes32esi1, CTRL_aes32esi2, CTRL_aes32esi3 = newElement()
	}
	object CryptoZkneCtrlEnum extends SpinalEnum(binarySequential) {
		 val CTRL_aes0, CTRL_aes1 = newElement()
	}
	object CryptoZkneCtrlaes0 extends Stageable(CryptoZkneCtrlaes0Enum())
	object CryptoZkneCtrlaes1 extends Stageable(CryptoZkneCtrlaes1Enum())
	object CryptoZkneCtrl extends Stageable(CryptoZkneCtrlEnum())
// Prologue

        // massive MUX implementing FT0
	def fun_aes_raw(in:Bits) : Bits = {
	    val x = in(7 downto 0)
	    val r = (x).mux(
				B"8'x00" -> B"24'xa563c6",
				B"8'x01" -> B"24'x847cf8",
				B"8'x02" -> B"24'x9977ee",
				B"8'x03" -> B"24'x8d7bf6",
				B"8'x04" -> B"24'x0df2ff",
				B"8'x05" -> B"24'xbd6bd6",
				B"8'x06" -> B"24'xb16fde",
				B"8'x07" -> B"24'x54c591",
				B"8'x08" -> B"24'x503060",
				B"8'x09" -> B"24'x030102",
				B"8'x0a" -> B"24'xa967ce",
				B"8'x0b" -> B"24'x7d2b56",
				B"8'x0c" -> B"24'x19fee7",
				B"8'x0d" -> B"24'x62d7b5",
				B"8'x0e" -> B"24'xe6ab4d",
				B"8'x0f" -> B"24'x9a76ec",
				B"8'x10" -> B"24'x45ca8f",
				B"8'x11" -> B"24'x9d821f",
				B"8'x12" -> B"24'x40c989",
				B"8'x13" -> B"24'x877dfa",
				B"8'x14" -> B"24'x15faef",
				B"8'x15" -> B"24'xeb59b2",
				B"8'x16" -> B"24'xc9478e",
				B"8'x17" -> B"24'x0bf0fb",
				B"8'x18" -> B"24'xecad41",
				B"8'x19" -> B"24'x67d4b3",
				B"8'x1a" -> B"24'xfda25f",
				B"8'x1b" -> B"24'xeaaf45",
				B"8'x1c" -> B"24'xbf9c23",
				B"8'x1d" -> B"24'xf7a453",
				B"8'x1e" -> B"24'x9672e4",
				B"8'x1f" -> B"24'x5bc09b",
				B"8'x20" -> B"24'xc2b775",
				B"8'x21" -> B"24'x1cfde1",
				B"8'x22" -> B"24'xae933d",
				B"8'x23" -> B"24'x6a264c",
				B"8'x24" -> B"24'x5a366c",
				B"8'x25" -> B"24'x413f7e",
				B"8'x26" -> B"24'x02f7f5",
				B"8'x27" -> B"24'x4fcc83",
				B"8'x28" -> B"24'x5c3468",
				B"8'x29" -> B"24'xf4a551",
				B"8'x2a" -> B"24'x34e5d1",
				B"8'x2b" -> B"24'x08f1f9",
				B"8'x2c" -> B"24'x9371e2",
				B"8'x2d" -> B"24'x73d8ab",
				B"8'x2e" -> B"24'x533162",
				B"8'x2f" -> B"24'x3f152a",
				B"8'x30" -> B"24'x0c0408",
				B"8'x31" -> B"24'x52c795",
				B"8'x32" -> B"24'x652346",
				B"8'x33" -> B"24'x5ec39d",
				B"8'x34" -> B"24'x281830",
				B"8'x35" -> B"24'xa19637",
				B"8'x36" -> B"24'x0f050a",
				B"8'x37" -> B"24'xb59a2f",
				B"8'x38" -> B"24'x09070e",
				B"8'x39" -> B"24'x361224",
				B"8'x3a" -> B"24'x9b801b",
				B"8'x3b" -> B"24'x3de2df",
				B"8'x3c" -> B"24'x26ebcd",
				B"8'x3d" -> B"24'x69274e",
				B"8'x3e" -> B"24'xcdb27f",
				B"8'x3f" -> B"24'x9f75ea",
				B"8'x40" -> B"24'x1b0912",
				B"8'x41" -> B"24'x9e831d",
				B"8'x42" -> B"24'x742c58",
				B"8'x43" -> B"24'x2e1a34",
				B"8'x44" -> B"24'x2d1b36",
				B"8'x45" -> B"24'xb26edc",
				B"8'x46" -> B"24'xee5ab4",
				B"8'x47" -> B"24'xfba05b",
				B"8'x48" -> B"24'xf652a4",
				B"8'x49" -> B"24'x4d3b76",
				B"8'x4a" -> B"24'x61d6b7",
				B"8'x4b" -> B"24'xceb37d",
				B"8'x4c" -> B"24'x7b2952",
				B"8'x4d" -> B"24'x3ee3dd",
				B"8'x4e" -> B"24'x712f5e",
				B"8'x4f" -> B"24'x978413",
				B"8'x50" -> B"24'xf553a6",
				B"8'x51" -> B"24'x68d1b9",
				B"8'x52" -> B"24'x000000",
				B"8'x53" -> B"24'x2cedc1",
				B"8'x54" -> B"24'x602040",
				B"8'x55" -> B"24'x1ffce3",
				B"8'x56" -> B"24'xc8b179",
				B"8'x57" -> B"24'xed5bb6",
				B"8'x58" -> B"24'xbe6ad4",
				B"8'x59" -> B"24'x46cb8d",
				B"8'x5a" -> B"24'xd9be67",
				B"8'x5b" -> B"24'x4b3972",
				B"8'x5c" -> B"24'xde4a94",
				B"8'x5d" -> B"24'xd44c98",
				B"8'x5e" -> B"24'xe858b0",
				B"8'x5f" -> B"24'x4acf85",
				B"8'x60" -> B"24'x6bd0bb",
				B"8'x61" -> B"24'x2aefc5",
				B"8'x62" -> B"24'xe5aa4f",
				B"8'x63" -> B"24'x16fbed",
				B"8'x64" -> B"24'xc54386",
				B"8'x65" -> B"24'xd74d9a",
				B"8'x66" -> B"24'x553366",
				B"8'x67" -> B"24'x948511",
				B"8'x68" -> B"24'xcf458a",
				B"8'x69" -> B"24'x10f9e9",
				B"8'x6a" -> B"24'x060204",
				B"8'x6b" -> B"24'x817ffe",
				B"8'x6c" -> B"24'xf050a0",
				B"8'x6d" -> B"24'x443c78",
				B"8'x6e" -> B"24'xba9f25",
				B"8'x6f" -> B"24'xe3a84b",
				B"8'x70" -> B"24'xf351a2",
				B"8'x71" -> B"24'xfea35d",
				B"8'x72" -> B"24'xc04080",
				B"8'x73" -> B"24'x8a8f05",
				B"8'x74" -> B"24'xad923f",
				B"8'x75" -> B"24'xbc9d21",
				B"8'x76" -> B"24'x483870",
				B"8'x77" -> B"24'x04f5f1",
				B"8'x78" -> B"24'xdfbc63",
				B"8'x79" -> B"24'xc1b677",
				B"8'x7a" -> B"24'x75daaf",
				B"8'x7b" -> B"24'x632142",
				B"8'x7c" -> B"24'x301020",
				B"8'x7d" -> B"24'x1affe5",
				B"8'x7e" -> B"24'x0ef3fd",
				B"8'x7f" -> B"24'x6dd2bf",
				B"8'x80" -> B"24'x4ccd81",
				B"8'x81" -> B"24'x140c18",
				B"8'x82" -> B"24'x351326",
				B"8'x83" -> B"24'x2fecc3",
				B"8'x84" -> B"24'xe15fbe",
				B"8'x85" -> B"24'xa29735",
				B"8'x86" -> B"24'xcc4488",
				B"8'x87" -> B"24'x39172e",
				B"8'x88" -> B"24'x57c493",
				B"8'x89" -> B"24'xf2a755",
				B"8'x8a" -> B"24'x827efc",
				B"8'x8b" -> B"24'x473d7a",
				B"8'x8c" -> B"24'xac64c8",
				B"8'x8d" -> B"24'xe75dba",
				B"8'x8e" -> B"24'x2b1932",
				B"8'x8f" -> B"24'x9573e6",
				B"8'x90" -> B"24'xa060c0",
				B"8'x91" -> B"24'x988119",
				B"8'x92" -> B"24'xd14f9e",
				B"8'x93" -> B"24'x7fdca3",
				B"8'x94" -> B"24'x662244",
				B"8'x95" -> B"24'x7e2a54",
				B"8'x96" -> B"24'xab903b",
				B"8'x97" -> B"24'x83880b",
				B"8'x98" -> B"24'xca468c",
				B"8'x99" -> B"24'x29eec7",
				B"8'x9a" -> B"24'xd3b86b",
				B"8'x9b" -> B"24'x3c1428",
				B"8'x9c" -> B"24'x79dea7",
				B"8'x9d" -> B"24'xe25ebc",
				B"8'x9e" -> B"24'x1d0b16",
				B"8'x9f" -> B"24'x76dbad",
				B"8'xa0" -> B"24'x3be0db",
				B"8'xa1" -> B"24'x563264",
				B"8'xa2" -> B"24'x4e3a74",
				B"8'xa3" -> B"24'x1e0a14",
				B"8'xa4" -> B"24'xdb4992",
				B"8'xa5" -> B"24'x0a060c",
				B"8'xa6" -> B"24'x6c2448",
				B"8'xa7" -> B"24'xe45cb8",
				B"8'xa8" -> B"24'x5dc29f",
				B"8'xa9" -> B"24'x6ed3bd",
				B"8'xaa" -> B"24'xefac43",
				B"8'xab" -> B"24'xa662c4",
				B"8'xac" -> B"24'xa89139",
				B"8'xad" -> B"24'xa49531",
				B"8'xae" -> B"24'x37e4d3",
				B"8'xaf" -> B"24'x8b79f2",
				B"8'xb0" -> B"24'x32e7d5",
				B"8'xb1" -> B"24'x43c88b",
				B"8'xb2" -> B"24'x59376e",
				B"8'xb3" -> B"24'xb76dda",
				B"8'xb4" -> B"24'x8c8d01",
				B"8'xb5" -> B"24'x64d5b1",
				B"8'xb6" -> B"24'xd24e9c",
				B"8'xb7" -> B"24'xe0a949",
				B"8'xb8" -> B"24'xb46cd8",
				B"8'xb9" -> B"24'xfa56ac",
				B"8'xba" -> B"24'x07f4f3",
				B"8'xbb" -> B"24'x25eacf",
				B"8'xbc" -> B"24'xaf65ca",
				B"8'xbd" -> B"24'x8e7af4",
				B"8'xbe" -> B"24'xe9ae47",
				B"8'xbf" -> B"24'x180810",
				B"8'xc0" -> B"24'xd5ba6f",
				B"8'xc1" -> B"24'x8878f0",
				B"8'xc2" -> B"24'x6f254a",
				B"8'xc3" -> B"24'x722e5c",
				B"8'xc4" -> B"24'x241c38",
				B"8'xc5" -> B"24'xf1a657",
				B"8'xc6" -> B"24'xc7b473",
				B"8'xc7" -> B"24'x51c697",
				B"8'xc8" -> B"24'x23e8cb",
				B"8'xc9" -> B"24'x7cdda1",
				B"8'xca" -> B"24'x9c74e8",
				B"8'xcb" -> B"24'x211f3e",
				B"8'xcc" -> B"24'xdd4b96",
				B"8'xcd" -> B"24'xdcbd61",
				B"8'xce" -> B"24'x868b0d",
				B"8'xcf" -> B"24'x858a0f",
				B"8'xd0" -> B"24'x9070e0",
				B"8'xd1" -> B"24'x423e7c",
				B"8'xd2" -> B"24'xc4b571",
				B"8'xd3" -> B"24'xaa66cc",
				B"8'xd4" -> B"24'xd84890",
				B"8'xd5" -> B"24'x050306",
				B"8'xd6" -> B"24'x01f6f7",
				B"8'xd7" -> B"24'x120e1c",
				B"8'xd8" -> B"24'xa361c2",
				B"8'xd9" -> B"24'x5f356a",
				B"8'xda" -> B"24'xf957ae",
				B"8'xdb" -> B"24'xd0b969",
				B"8'xdc" -> B"24'x918617",
				B"8'xdd" -> B"24'x58c199",
				B"8'xde" -> B"24'x271d3a",
				B"8'xdf" -> B"24'xb99e27",
				B"8'xe0" -> B"24'x38e1d9",
				B"8'xe1" -> B"24'x13f8eb",
				B"8'xe2" -> B"24'xb3982b",
				B"8'xe3" -> B"24'x331122",
				B"8'xe4" -> B"24'xbb69d2",
				B"8'xe5" -> B"24'x70d9a9",
				B"8'xe6" -> B"24'x898e07",
				B"8'xe7" -> B"24'xa79433",
				B"8'xe8" -> B"24'xb69b2d",
				B"8'xe9" -> B"24'x221e3c",
				B"8'xea" -> B"24'x928715",
				B"8'xeb" -> B"24'x20e9c9",
				B"8'xec" -> B"24'x49ce87",
				B"8'xed" -> B"24'xff55aa",
				B"8'xee" -> B"24'x782850",
				B"8'xef" -> B"24'x7adfa5",
				B"8'xf0" -> B"24'x8f8c03",
				B"8'xf1" -> B"24'xf8a159",
				B"8'xf2" -> B"24'x808909",
				B"8'xf3" -> B"24'x170d1a",
				B"8'xf4" -> B"24'xdabf65",
				B"8'xf5" -> B"24'x31e6d7",
				B"8'xf6" -> B"24'xc64284",
				B"8'xf7" -> B"24'xb868d0",
				B"8'xf8" -> B"24'xc34182",
				B"8'xf9" -> B"24'xb09929",
				B"8'xfa" -> B"24'x772d5a",
				B"8'xfb" -> B"24'x110f1e",
				B"8'xfc" -> B"24'xcbb07b",
				B"8'xfd" -> B"24'xfc54a8",
				B"8'xfe" -> B"24'xd6bb6d",
				B"8'xff" -> B"24'x3a162c")
		r // return value;
	}

	def fun_aesx_0(rs1: Bits, rs2: Bits) : Bits = {
	    val idx = rs1(7 downto 0)
	    val r = fun_aes_raw(idx)
	    (r(23 downto 8) ## r(15 downto 0)) ^ rs2 // return value
	}
	def fun_aesx_1(rs1: Bits, rs2: Bits) : Bits = {
	    val idx = rs1(15 downto 8)
	    val r = fun_aes_raw(idx)
	    (r(15 downto 8) ## r(15 downto 0) ## r(23 downto 16)) ^ rs2 // return value
	}
	def fun_aesx_2(rs1: Bits, rs2: Bits) : Bits = {
	    val idx = rs1(23 downto 16)
	    val r = fun_aes_raw(idx)
	    (r(15 downto 0) ## r(23 downto 8)) ^ rs2 // return value
	}
	def fun_aesx_3(rs1: Bits, rs2: Bits) : Bits = {
	    val idx = rs1(31 downto 24)
	    val r = fun_aes_raw(idx)
	    (r(7 downto 0) ## r(23 downto 8) ## r(15 downto 8)) ^ rs2 // return value
	}

	def fun_aesxnm_0(rs1: Bits, rs2: Bits) : Bits = {
	    val idx = rs1(7 downto 0)
	    val r = fun_aes_raw(idx)
	    (r(15 downto 8).resize(32)       ) ^ rs2 // return value
	}
	def fun_aesxnm_1(rs1: Bits, rs2: Bits) : Bits = {
	    val idx = rs1(15 downto 8)
	    val r = fun_aes_raw(idx)
	    (r(15 downto 8).resize(32) |<<  8) ^ rs2 // return value
	}
	def fun_aesxnm_2(rs1: Bits, rs2: Bits) : Bits = {
	    val idx = rs1(23 downto 16)
	    val r = fun_aes_raw(idx)
	    (r(15 downto 8).resize(32) |<< 16) ^ rs2 // return value
	}
	def fun_aesxnm_3(rs1: Bits, rs2: Bits) : Bits = {
	    val idx = rs1(31 downto 24)
	    val r = fun_aes_raw(idx)
	    (r(15 downto 8).resize(32) |<< 24) ^ rs2 // return value
	}

// End prologue
} // object Plugin
class CryptoZknePlugin extends Plugin[VexRiscv] {
	import CryptoZknePlugin._
	object IS_CryptoZkne extends Stageable(Bool)
	override def setup(pipeline: VexRiscv): Unit = {
		import pipeline.config._
		val immediateActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.IMI,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> True,
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			IS_CryptoZkne -> True
			)
		val binaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> True,
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			RS2_USE -> True,
			IS_CryptoZkne -> True
			)
		val unaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> True,
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			IS_CryptoZkne -> True
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
			IS_CryptoZkne -> True
			)
		def aes32esmi0_KEY = M"0011011----------000-----0110011"
		def aes32esmi1_KEY = M"0111011----------000-----0110011"
		def aes32esmi2_KEY = M"1011011----------000-----0110011"
		def aes32esmi3_KEY = M"1111011----------000-----0110011"
		def aes32esi0_KEY = M"0011001----------000-----0110011"
		def aes32esi1_KEY = M"0111001----------000-----0110011"
		def aes32esi2_KEY = M"1011001----------000-----0110011"
		def aes32esi3_KEY = M"1111001----------000-----0110011"
		val decoderService = pipeline.service(classOf[DecoderService])
		decoderService.addDefault(IS_CryptoZkne, False)
		decoderService.add(List(
			aes32esmi0_KEY	-> (binaryActions ++ List(CryptoZkneCtrl -> CryptoZkneCtrlEnum.CTRL_aes0, CryptoZkneCtrlaes0 -> CryptoZkneCtrlaes0Enum.CTRL_aes32esmi0)),
			aes32esmi1_KEY	-> (binaryActions ++ List(CryptoZkneCtrl -> CryptoZkneCtrlEnum.CTRL_aes0, CryptoZkneCtrlaes0 -> CryptoZkneCtrlaes0Enum.CTRL_aes32esmi1)),
			aes32esmi2_KEY	-> (binaryActions ++ List(CryptoZkneCtrl -> CryptoZkneCtrlEnum.CTRL_aes0, CryptoZkneCtrlaes0 -> CryptoZkneCtrlaes0Enum.CTRL_aes32esmi2)),
			aes32esmi3_KEY	-> (binaryActions ++ List(CryptoZkneCtrl -> CryptoZkneCtrlEnum.CTRL_aes0, CryptoZkneCtrlaes0 -> CryptoZkneCtrlaes0Enum.CTRL_aes32esmi3)),
			aes32esi0_KEY	-> (binaryActions ++ List(CryptoZkneCtrl -> CryptoZkneCtrlEnum.CTRL_aes1, CryptoZkneCtrlaes1 -> CryptoZkneCtrlaes1Enum.CTRL_aes32esi0)),
			aes32esi1_KEY	-> (binaryActions ++ List(CryptoZkneCtrl -> CryptoZkneCtrlEnum.CTRL_aes1, CryptoZkneCtrlaes1 -> CryptoZkneCtrlaes1Enum.CTRL_aes32esi1)),
			aes32esi2_KEY	-> (binaryActions ++ List(CryptoZkneCtrl -> CryptoZkneCtrlEnum.CTRL_aes1, CryptoZkneCtrlaes1 -> CryptoZkneCtrlaes1Enum.CTRL_aes32esi2)),
			aes32esi3_KEY	-> (binaryActions ++ List(CryptoZkneCtrl -> CryptoZkneCtrlEnum.CTRL_aes1, CryptoZkneCtrlaes1 -> CryptoZkneCtrlaes1Enum.CTRL_aes32esi3))
		))
	} // override def setup
	override def build(pipeline: VexRiscv): Unit = {
		import pipeline._
		import pipeline.config._
		execute plug new Area{
			import execute._
			val val_aes0 = input(CryptoZkneCtrlaes0).mux(
				CryptoZkneCtrlaes0Enum.CTRL_aes32esmi0 -> fun_aesx_0(input(SRC2), input(SRC1)),
				CryptoZkneCtrlaes0Enum.CTRL_aes32esmi1 -> fun_aesx_1(input(SRC2), input(SRC1)),
				CryptoZkneCtrlaes0Enum.CTRL_aes32esmi2 -> fun_aesx_2(input(SRC2), input(SRC1)),
				CryptoZkneCtrlaes0Enum.CTRL_aes32esmi3 -> fun_aesx_3(input(SRC2), input(SRC1))
			) // mux aes0
			val val_aes1 = input(CryptoZkneCtrlaes1).mux(
				CryptoZkneCtrlaes1Enum.CTRL_aes32esi0 -> fun_aesxnm_0(input(SRC2), input(SRC1)),
				CryptoZkneCtrlaes1Enum.CTRL_aes32esi1 -> fun_aesxnm_1(input(SRC2), input(SRC1)),
				CryptoZkneCtrlaes1Enum.CTRL_aes32esi2 -> fun_aesxnm_2(input(SRC2), input(SRC1)),
				CryptoZkneCtrlaes1Enum.CTRL_aes32esi3 -> fun_aesxnm_3(input(SRC2), input(SRC1))
			) // mux aes1
			when (input(IS_CryptoZkne)) {
				execute.output(REGFILE_WRITE_DATA) := input(CryptoZkneCtrl).mux(
					CryptoZkneCtrlEnum.CTRL_aes0 -> val_aes0.asBits,
					CryptoZkneCtrlEnum.CTRL_aes1 -> val_aes1.asBits
				) // primary mux 
			} // when input is 
		} // execute plug newArea
	} // override def build
} // class Plugin
