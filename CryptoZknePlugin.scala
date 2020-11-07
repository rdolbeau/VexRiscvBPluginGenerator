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
				B"8'x00" -> B"32'xa56363c6",
				B"8'x01" -> B"32'x847c7cf8",
				B"8'x02" -> B"32'x997777ee",
				B"8'x03" -> B"32'x8d7b7bf6",
				B"8'x04" -> B"32'x0df2f2ff",
				B"8'x05" -> B"32'xbd6b6bd6",
				B"8'x06" -> B"32'xb16f6fde",
				B"8'x07" -> B"32'x54c5c591",
				B"8'x08" -> B"32'x50303060",
				B"8'x09" -> B"32'x03010102",
				B"8'x0a" -> B"32'xa96767ce",
				B"8'x0b" -> B"32'x7d2b2b56",
				B"8'x0c" -> B"32'x19fefee7",
				B"8'x0d" -> B"32'x62d7d7b5",
				B"8'x0e" -> B"32'xe6abab4d",
				B"8'x0f" -> B"32'x9a7676ec",
				B"8'x10" -> B"32'x45caca8f",
				B"8'x11" -> B"32'x9d82821f",
				B"8'x12" -> B"32'x40c9c989",
				B"8'x13" -> B"32'x877d7dfa",
				B"8'x14" -> B"32'x15fafaef",
				B"8'x15" -> B"32'xeb5959b2",
				B"8'x16" -> B"32'xc947478e",
				B"8'x17" -> B"32'x0bf0f0fb",
				B"8'x18" -> B"32'xecadad41",
				B"8'x19" -> B"32'x67d4d4b3",
				B"8'x1a" -> B"32'xfda2a25f",
				B"8'x1b" -> B"32'xeaafaf45",
				B"8'x1c" -> B"32'xbf9c9c23",
				B"8'x1d" -> B"32'xf7a4a453",
				B"8'x1e" -> B"32'x967272e4",
				B"8'x1f" -> B"32'x5bc0c09b",
				B"8'x20" -> B"32'xc2b7b775",
				B"8'x21" -> B"32'x1cfdfde1",
				B"8'x22" -> B"32'xae93933d",
				B"8'x23" -> B"32'x6a26264c",
				B"8'x24" -> B"32'x5a36366c",
				B"8'x25" -> B"32'x413f3f7e",
				B"8'x26" -> B"32'x02f7f7f5",
				B"8'x27" -> B"32'x4fcccc83",
				B"8'x28" -> B"32'x5c343468",
				B"8'x29" -> B"32'xf4a5a551",
				B"8'x2a" -> B"32'x34e5e5d1",
				B"8'x2b" -> B"32'x08f1f1f9",
				B"8'x2c" -> B"32'x937171e2",
				B"8'x2d" -> B"32'x73d8d8ab",
				B"8'x2e" -> B"32'x53313162",
				B"8'x2f" -> B"32'x3f15152a",
				B"8'x30" -> B"32'x0c040408",
				B"8'x31" -> B"32'x52c7c795",
				B"8'x32" -> B"32'x65232346",
				B"8'x33" -> B"32'x5ec3c39d",
				B"8'x34" -> B"32'x28181830",
				B"8'x35" -> B"32'xa1969637",
				B"8'x36" -> B"32'x0f05050a",
				B"8'x37" -> B"32'xb59a9a2f",
				B"8'x38" -> B"32'x0907070e",
				B"8'x39" -> B"32'x36121224",
				B"8'x3a" -> B"32'x9b80801b",
				B"8'x3b" -> B"32'x3de2e2df",
				B"8'x3c" -> B"32'x26ebebcd",
				B"8'x3d" -> B"32'x6927274e",
				B"8'x3e" -> B"32'xcdb2b27f",
				B"8'x3f" -> B"32'x9f7575ea",
				B"8'x40" -> B"32'x1b090912",
				B"8'x41" -> B"32'x9e83831d",
				B"8'x42" -> B"32'x742c2c58",
				B"8'x43" -> B"32'x2e1a1a34",
				B"8'x44" -> B"32'x2d1b1b36",
				B"8'x45" -> B"32'xb26e6edc",
				B"8'x46" -> B"32'xee5a5ab4",
				B"8'x47" -> B"32'xfba0a05b",
				B"8'x48" -> B"32'xf65252a4",
				B"8'x49" -> B"32'x4d3b3b76",
				B"8'x4a" -> B"32'x61d6d6b7",
				B"8'x4b" -> B"32'xceb3b37d",
				B"8'x4c" -> B"32'x7b292952",
				B"8'x4d" -> B"32'x3ee3e3dd",
				B"8'x4e" -> B"32'x712f2f5e",
				B"8'x4f" -> B"32'x97848413",
				B"8'x50" -> B"32'xf55353a6",
				B"8'x51" -> B"32'x68d1d1b9",
				B"8'x52" -> B"32'x00000000",
				B"8'x53" -> B"32'x2cededc1",
				B"8'x54" -> B"32'x60202040",
				B"8'x55" -> B"32'x1ffcfce3",
				B"8'x56" -> B"32'xc8b1b179",
				B"8'x57" -> B"32'xed5b5bb6",
				B"8'x58" -> B"32'xbe6a6ad4",
				B"8'x59" -> B"32'x46cbcb8d",
				B"8'x5a" -> B"32'xd9bebe67",
				B"8'x5b" -> B"32'x4b393972",
				B"8'x5c" -> B"32'xde4a4a94",
				B"8'x5d" -> B"32'xd44c4c98",
				B"8'x5e" -> B"32'xe85858b0",
				B"8'x5f" -> B"32'x4acfcf85",
				B"8'x60" -> B"32'x6bd0d0bb",
				B"8'x61" -> B"32'x2aefefc5",
				B"8'x62" -> B"32'xe5aaaa4f",
				B"8'x63" -> B"32'x16fbfbed",
				B"8'x64" -> B"32'xc5434386",
				B"8'x65" -> B"32'xd74d4d9a",
				B"8'x66" -> B"32'x55333366",
				B"8'x67" -> B"32'x94858511",
				B"8'x68" -> B"32'xcf45458a",
				B"8'x69" -> B"32'x10f9f9e9",
				B"8'x6a" -> B"32'x06020204",
				B"8'x6b" -> B"32'x817f7ffe",
				B"8'x6c" -> B"32'xf05050a0",
				B"8'x6d" -> B"32'x443c3c78",
				B"8'x6e" -> B"32'xba9f9f25",
				B"8'x6f" -> B"32'xe3a8a84b",
				B"8'x70" -> B"32'xf35151a2",
				B"8'x71" -> B"32'xfea3a35d",
				B"8'x72" -> B"32'xc0404080",
				B"8'x73" -> B"32'x8a8f8f05",
				B"8'x74" -> B"32'xad92923f",
				B"8'x75" -> B"32'xbc9d9d21",
				B"8'x76" -> B"32'x48383870",
				B"8'x77" -> B"32'x04f5f5f1",
				B"8'x78" -> B"32'xdfbcbc63",
				B"8'x79" -> B"32'xc1b6b677",
				B"8'x7a" -> B"32'x75dadaaf",
				B"8'x7b" -> B"32'x63212142",
				B"8'x7c" -> B"32'x30101020",
				B"8'x7d" -> B"32'x1affffe5",
				B"8'x7e" -> B"32'x0ef3f3fd",
				B"8'x7f" -> B"32'x6dd2d2bf",
				B"8'x80" -> B"32'x4ccdcd81",
				B"8'x81" -> B"32'x140c0c18",
				B"8'x82" -> B"32'x35131326",
				B"8'x83" -> B"32'x2fececc3",
				B"8'x84" -> B"32'xe15f5fbe",
				B"8'x85" -> B"32'xa2979735",
				B"8'x86" -> B"32'xcc444488",
				B"8'x87" -> B"32'x3917172e",
				B"8'x88" -> B"32'x57c4c493",
				B"8'x89" -> B"32'xf2a7a755",
				B"8'x8a" -> B"32'x827e7efc",
				B"8'x8b" -> B"32'x473d3d7a",
				B"8'x8c" -> B"32'xac6464c8",
				B"8'x8d" -> B"32'xe75d5dba",
				B"8'x8e" -> B"32'x2b191932",
				B"8'x8f" -> B"32'x957373e6",
				B"8'x90" -> B"32'xa06060c0",
				B"8'x91" -> B"32'x98818119",
				B"8'x92" -> B"32'xd14f4f9e",
				B"8'x93" -> B"32'x7fdcdca3",
				B"8'x94" -> B"32'x66222244",
				B"8'x95" -> B"32'x7e2a2a54",
				B"8'x96" -> B"32'xab90903b",
				B"8'x97" -> B"32'x8388880b",
				B"8'x98" -> B"32'xca46468c",
				B"8'x99" -> B"32'x29eeeec7",
				B"8'x9a" -> B"32'xd3b8b86b",
				B"8'x9b" -> B"32'x3c141428",
				B"8'x9c" -> B"32'x79dedea7",
				B"8'x9d" -> B"32'xe25e5ebc",
				B"8'x9e" -> B"32'x1d0b0b16",
				B"8'x9f" -> B"32'x76dbdbad",
				B"8'xa0" -> B"32'x3be0e0db",
				B"8'xa1" -> B"32'x56323264",
				B"8'xa2" -> B"32'x4e3a3a74",
				B"8'xa3" -> B"32'x1e0a0a14",
				B"8'xa4" -> B"32'xdb494992",
				B"8'xa5" -> B"32'x0a06060c",
				B"8'xa6" -> B"32'x6c242448",
				B"8'xa7" -> B"32'xe45c5cb8",
				B"8'xa8" -> B"32'x5dc2c29f",
				B"8'xa9" -> B"32'x6ed3d3bd",
				B"8'xaa" -> B"32'xefacac43",
				B"8'xab" -> B"32'xa66262c4",
				B"8'xac" -> B"32'xa8919139",
				B"8'xad" -> B"32'xa4959531",
				B"8'xae" -> B"32'x37e4e4d3",
				B"8'xaf" -> B"32'x8b7979f2",
				B"8'xb0" -> B"32'x32e7e7d5",
				B"8'xb1" -> B"32'x43c8c88b",
				B"8'xb2" -> B"32'x5937376e",
				B"8'xb3" -> B"32'xb76d6dda",
				B"8'xb4" -> B"32'x8c8d8d01",
				B"8'xb5" -> B"32'x64d5d5b1",
				B"8'xb6" -> B"32'xd24e4e9c",
				B"8'xb7" -> B"32'xe0a9a949",
				B"8'xb8" -> B"32'xb46c6cd8",
				B"8'xb9" -> B"32'xfa5656ac",
				B"8'xba" -> B"32'x07f4f4f3",
				B"8'xbb" -> B"32'x25eaeacf",
				B"8'xbc" -> B"32'xaf6565ca",
				B"8'xbd" -> B"32'x8e7a7af4",
				B"8'xbe" -> B"32'xe9aeae47",
				B"8'xbf" -> B"32'x18080810",
				B"8'xc0" -> B"32'xd5baba6f",
				B"8'xc1" -> B"32'x887878f0",
				B"8'xc2" -> B"32'x6f25254a",
				B"8'xc3" -> B"32'x722e2e5c",
				B"8'xc4" -> B"32'x241c1c38",
				B"8'xc5" -> B"32'xf1a6a657",
				B"8'xc6" -> B"32'xc7b4b473",
				B"8'xc7" -> B"32'x51c6c697",
				B"8'xc8" -> B"32'x23e8e8cb",
				B"8'xc9" -> B"32'x7cdddda1",
				B"8'xca" -> B"32'x9c7474e8",
				B"8'xcb" -> B"32'x211f1f3e",
				B"8'xcc" -> B"32'xdd4b4b96",
				B"8'xcd" -> B"32'xdcbdbd61",
				B"8'xce" -> B"32'x868b8b0d",
				B"8'xcf" -> B"32'x858a8a0f",
				B"8'xd0" -> B"32'x907070e0",
				B"8'xd1" -> B"32'x423e3e7c",
				B"8'xd2" -> B"32'xc4b5b571",
				B"8'xd3" -> B"32'xaa6666cc",
				B"8'xd4" -> B"32'xd8484890",
				B"8'xd5" -> B"32'x05030306",
				B"8'xd6" -> B"32'x01f6f6f7",
				B"8'xd7" -> B"32'x120e0e1c",
				B"8'xd8" -> B"32'xa36161c2",
				B"8'xd9" -> B"32'x5f35356a",
				B"8'xda" -> B"32'xf95757ae",
				B"8'xdb" -> B"32'xd0b9b969",
				B"8'xdc" -> B"32'x91868617",
				B"8'xdd" -> B"32'x58c1c199",
				B"8'xde" -> B"32'x271d1d3a",
				B"8'xdf" -> B"32'xb99e9e27",
				B"8'xe0" -> B"32'x38e1e1d9",
				B"8'xe1" -> B"32'x13f8f8eb",
				B"8'xe2" -> B"32'xb398982b",
				B"8'xe3" -> B"32'x33111122",
				B"8'xe4" -> B"32'xbb6969d2",
				B"8'xe5" -> B"32'x70d9d9a9",
				B"8'xe6" -> B"32'x898e8e07",
				B"8'xe7" -> B"32'xa7949433",
				B"8'xe8" -> B"32'xb69b9b2d",
				B"8'xe9" -> B"32'x221e1e3c",
				B"8'xea" -> B"32'x92878715",
				B"8'xeb" -> B"32'x20e9e9c9",
				B"8'xec" -> B"32'x49cece87",
				B"8'xed" -> B"32'xff5555aa",
				B"8'xee" -> B"32'x78282850",
				B"8'xef" -> B"32'x7adfdfa5",
				B"8'xf0" -> B"32'x8f8c8c03",
				B"8'xf1" -> B"32'xf8a1a159",
				B"8'xf2" -> B"32'x80898909",
				B"8'xf3" -> B"32'x170d0d1a",
				B"8'xf4" -> B"32'xdabfbf65",
				B"8'xf5" -> B"32'x31e6e6d7",
				B"8'xf6" -> B"32'xc6424284",
				B"8'xf7" -> B"32'xb86868d0",
				B"8'xf8" -> B"32'xc3414182",
				B"8'xf9" -> B"32'xb0999929",
				B"8'xfa" -> B"32'x772d2d5a",
				B"8'xfb" -> B"32'x110f0f1e",
				B"8'xfc" -> B"32'xcbb0b07b",
				B"8'xfd" -> B"32'xfc5454a8",
				B"8'xfe" -> B"32'xd6bbbb6d",
				B"8'xff" -> B"32'x3a16162c")
		r // return value;
	}

	def fun_aesx_0(rs1: Bits, rs2: Bits) : Bits = {
	    val idx = rs1(7 downto 0)
	    val r = fun_aes_raw(idx)
	    r ^ rs2 // return value
	}
	def fun_aesx_1(rs1: Bits, rs2: Bits) : Bits = {
	    val idx = rs1(15 downto 8)
	    val r = fun_aes_raw(idx)
	    r.rotateLeft(8) ^ rs2 // return value
	}
	def fun_aesx_2(rs1: Bits, rs2: Bits) : Bits = {
	    val idx = rs1(23 downto 16)
	    val r = fun_aes_raw(idx)
	    r.rotateRight(16) ^ rs2 // return value
	}
	def fun_aesx_3(rs1: Bits, rs2: Bits) : Bits = {
	    val idx = rs1(31 downto 24)
	    val r = fun_aes_raw(idx)
	    r.rotateRight(8) ^ rs2 // return value
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
		def aes32esmi0_KEY = M"0000000----------010-----0101011"
		def aes32esmi1_KEY = M"0100000----------010-----0101011"
		def aes32esmi2_KEY = M"1000000----------010-----0101011"
		def aes32esmi3_KEY = M"1100000----------010-----0101011"
		def aes32esi0_KEY = M"0000001----------010-----0101011"
		def aes32esi1_KEY = M"0100001----------010-----0101011"
		def aes32esi2_KEY = M"1000001----------010-----0101011"
		def aes32esi3_KEY = M"1100001----------010-----0101011"
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
