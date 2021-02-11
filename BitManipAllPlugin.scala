// WARNING: this is auto-generated code!
// See https://github.com/rdolbeau/VexRiscvBPluginGenerator/
package vexriscv.plugin
import spinal.core._
import vexriscv.{Stageable, DecoderService, VexRiscv}
object BitManipAllPlugin {
	object BitManipAllCtrlbitwiseEnum extends SpinalEnum(binarySequential) {
		 val CTRL_ANDN, CTRL_ORN, CTRL_XNOR = newElement()
	}
	object BitManipAllCtrlshiftEnum extends SpinalEnum(binarySequential) {
		 val CTRL_SLO, CTRL_SRO = newElement()
	}
	object BitManipAllCtrlrotationEnum extends SpinalEnum(binarySequential) {
		 val CTRL_ROL, CTRL_ROR = newElement()
	}
	object BitManipAllCtrlsh_addEnum extends SpinalEnum(binarySequential) {
		 val CTRL_SH1ADD, CTRL_SH2ADD, CTRL_SH3ADD = newElement()
	}
	object BitManipAllCtrlsinglebitEnum extends SpinalEnum(binarySequential) {
		 val CTRL_BCLR, CTRL_BEXT, CTRL_BINV, CTRL_BSET = newElement()
	}
	object BitManipAllCtrlgrevrocEnum extends SpinalEnum(binarySequential) {
		 val CTRL_GORC, CTRL_GREV = newElement()
	}
	object BitManipAllCtrlminmaxEnum extends SpinalEnum(binarySequential) {
		 val CTRL_MAX, CTRL_MAXU, CTRL_MIN, CTRL_MINU = newElement()
	}
	object BitManipAllCtrlshuffleEnum extends SpinalEnum(binarySequential) {
		 val CTRL_SHFL, CTRL_UNSHFL = newElement()
	}
	object BitManipAllCtrlpackEnum extends SpinalEnum(binarySequential) {
		 val CTRL_PACK, CTRL_PACKH, CTRL_PACKU = newElement()
	}
	object BitManipAllCtrlxpermEnum extends SpinalEnum(binarySequential) {
		 val CTRL_XPERMdotB, CTRL_XPERMdotH, CTRL_XPERMdotN = newElement()
	}
	object BitManipAllCtrlgrevorcEnum extends SpinalEnum(binarySequential) {
		 val CTRL_GORC, CTRL_GREV = newElement()
	}
	object BitManipAllCtrlcountzeroesEnum extends SpinalEnum(binarySequential) {
		 val CTRL_CLZ, CTRL_CPOP, CTRL_CTZ = newElement()
	}
	object BitManipAllCtrlsignextendEnum extends SpinalEnum(binarySequential) {
		 val CTRL_SEXTdotB, CTRL_SEXTdotH = newElement()
	}
	object BitManipAllCtrlternaryEnum extends SpinalEnum(binarySequential) {
		 val CTRL_CMIX, CTRL_CMOV, CTRL_FSL, CTRL_FSR = newElement()
	}
	object BitManipAllCtrlEnum extends SpinalEnum(binarySequential) {
		 val CTRL_bitwise, CTRL_shift, CTRL_rotation, CTRL_sh_add, CTRL_singlebit, CTRL_grevroc, CTRL_minmax, CTRL_shuffle, CTRL_pack, CTRL_BFP, CTRL_xperm, CTRL_grevorc, CTRL_countzeroes, CTRL_signextend, CTRL_ternary = newElement()
	}
	object BitManipAllCtrlbitwise extends Stageable(BitManipAllCtrlbitwiseEnum())
	object BitManipAllCtrlshift extends Stageable(BitManipAllCtrlshiftEnum())
	object BitManipAllCtrlrotation extends Stageable(BitManipAllCtrlrotationEnum())
	object BitManipAllCtrlsh_add extends Stageable(BitManipAllCtrlsh_addEnum())
	object BitManipAllCtrlsinglebit extends Stageable(BitManipAllCtrlsinglebitEnum())
	object BitManipAllCtrlgrevroc extends Stageable(BitManipAllCtrlgrevrocEnum())
	object BitManipAllCtrlminmax extends Stageable(BitManipAllCtrlminmaxEnum())
	object BitManipAllCtrlshuffle extends Stageable(BitManipAllCtrlshuffleEnum())
	object BitManipAllCtrlpack extends Stageable(BitManipAllCtrlpackEnum())
	object BitManipAllCtrlxperm extends Stageable(BitManipAllCtrlxpermEnum())
	object BitManipAllCtrlgrevorc extends Stageable(BitManipAllCtrlgrevorcEnum())
	object BitManipAllCtrlcountzeroes extends Stageable(BitManipAllCtrlcountzeroesEnum())
	object BitManipAllCtrlsignextend extends Stageable(BitManipAllCtrlsignextendEnum())
	object BitManipAllCtrlternary extends Stageable(BitManipAllCtrlternaryEnum())
	object BitManipAllCtrl extends Stageable(BitManipAllCtrlEnum())
// Prologue

   // function implementing the semantic of 32-bits generalized reverse
   def fun_grev( a:Bits, b:Bits ) : Bits = {
       val x1  = ((b&B"32'x00000001")===B"32'x00000001") ? (((a  & B"32'x55555555") |<< 1) | ((a  & B"32'xAAAAAAAA") |>> 1)) | a
       val x2  = ((b&B"32'x00000002")===B"32'x00000002") ? (((x1 & B"32'x33333333") |<< 2) | ((x1 & B"32'xCCCCCCCC") |>> 2)) | x1
       val x4  = ((b&B"32'x00000004")===B"32'x00000004") ? (((x2 & B"32'x0F0F0F0F") |<< 4) | ((x2 & B"32'xF0F0F0F0") |>> 4)) | x2
       val x8  = ((b&B"32'x00000008")===B"32'x00000008") ? (((x4 & B"32'x00FF00FF") |<< 8) | ((x4 & B"32'xFF00FF00") |>> 8)) | x4
       val x16 = ((b&B"32'x00000010")===B"32'x00000010") ? (((x8 & B"32'x0000FFFF") |<<16) | ((x8 & B"32'xFFFF0000") |>>16)) | x8
       x16 // return value
   }
   // function implementing the semantic of 32-bits generalized OR-combine
   def fun_gorc( a:Bits, b:Bits ) : Bits = {
       val x1  = ((b&B"32'x00000001")===B"32'x00000001") ? (a  | ((a  & B"32'x55555555") |<< 1) | ((a  & B"32'xAAAAAAAA") |>> 1)) | a
       val x2  = ((b&B"32'x00000002")===B"32'x00000002") ? (x1 | ((x1 & B"32'x33333333") |<< 2) | ((x1 & B"32'xCCCCCCCC") |>> 2)) | x1
       val x4  = ((b&B"32'x00000004")===B"32'x00000004") ? (x2 | ((x2 & B"32'x0F0F0F0F") |<< 4) | ((x2 & B"32'xF0F0F0F0") |>> 4)) | x2
       val x8  = ((b&B"32'x00000008")===B"32'x00000008") ? (x4 | ((x4 & B"32'x00FF00FF") |<< 8) | ((x4 & B"32'xFF00FF00") |>> 8)) | x4
       val x16 = ((b&B"32'x00000010")===B"32'x00000010") ? (x8 | ((x8 & B"32'x0000FFFF") |<<16) | ((x8 & B"32'xFFFF0000") |>>16)) | x8
       x16 // return value
   }

   // helper function for the implementation of the generalized shuffles
   def fun_shuffle32_stage(src:Bits, maskL:Bits, maskR:Bits, N:Int) : Bits = {
       val x = src & ~(maskL | maskR)
       val x2 = x | ((src |<< N) & maskL) | ((src |>> N) & maskR);
       x2 // return value
   }
   // function implementing the semantic of 32-bits generalized shuffle
   def fun_shfl32(a:Bits, b:Bits) : Bits = {
       val x = a;
       val x1 = ((b&B"32'x00000008")===B"32'x00000008") ? fun_shuffle32_stage(x , B"32'x00FF0000", B"32'x0000FF00", 8) | x;
       val x2 = ((b&B"32'x00000004")===B"32'x00000004") ? fun_shuffle32_stage(x1, B"32'x0F000F00", B"32'x00F000F0", 4) | x1;
       val x3 = ((b&B"32'x00000002")===B"32'x00000002") ? fun_shuffle32_stage(x2, B"32'x30303030", B"32'x0C0C0C0C", 2) | x2;
       val x4 = ((b&B"32'x00000001")===B"32'x00000001") ? fun_shuffle32_stage(x3, B"32'x44444444", B"32'x22222222", 1) | x3;
       x4 // return value
   }
   // function implementing the semantic of 32-bits generalized unshuffle
   def fun_unshfl32(a:Bits, b:Bits) : Bits = {
      val x = a;
      val x1 = ((b&B"32'x00000001")===B"32'x00000001") ? fun_shuffle32_stage(x , B"32'x44444444", B"32'x22222222", 1) | x;
      val x2 = ((b&B"32'x00000002")===B"32'x00000002") ? fun_shuffle32_stage(x1, B"32'x30303030", B"32'x0C0C0C0C", 2) | x1;
      val x3 = ((b&B"32'x00000004")===B"32'x00000004") ? fun_shuffle32_stage(x2, B"32'x0F000F00", B"32'x00F000F0", 4) | x2;
      val x4 = ((b&B"32'x00000008")===B"32'x00000008") ? fun_shuffle32_stage(x3, B"32'x00FF0000", B"32'x0000FF00", 8) | x3;
      x4 // return value
   }


   // this is trying to look like DOI 10.2478/jee-2015-0054
   def fun_clz_NLCi(x:Bits): Bits = {
       val r2 = (~(x(0) | x(1) | x(2) | x(3)))
       val r1 = (~(x(2) | x(3)))
       val r0 = (~(x(3) | (x(1) & ~x(2))))
       val r = r2 ## r1 ## r0
       r // return value
   }
   def fun_clz_BNE(a:Bits) : Bits = {
       val a01 = ~(a(0) & a(1))
       val a23 = ~(a(2) & a(3))

       val a45 = ~(a(4) & a(5))
       val a67 = ~(a(6) & a(7))

       val a0123 = ~(a01 | a23) // also r(2)
       val a4567 = ~(a45 | a67)

       val a56 = ~(a(5) & ~a(6))
       val a024 = (a(0) & a(2) & a(4)) // AND not NAND
       val a13 = ~(a(1) & a(3))
       val a12 = ~(a(1) & ~a(2))
       
       val r3 = ((a0123 & a4567)) // AND not NAND
       val r2 = (a0123)
       val r1 = (~(a01 | (~a23 & a45)))
       val r0 = (~((~((a56) & (a024))) & (~((a13) & (a12) & (a(0))))))

       val r = r3 ## r2 ## r1 ##r0
       
       r // return value
   }
   def fun_clz(in:Bits) : Bits = {
       val nlc7 = fun_clz_NLCi(in(31 downto 28))
       val nlc6 = fun_clz_NLCi(in(27 downto 24))
       val nlc5 = fun_clz_NLCi(in(23 downto 20))
       val nlc4 = fun_clz_NLCi(in(19 downto 16))
       val nlc3 = fun_clz_NLCi(in(15 downto 12))
       val nlc2 = fun_clz_NLCi(in(11 downto  8))
       val nlc1 = fun_clz_NLCi(in( 7 downto  4))
       val nlc0 = fun_clz_NLCi(in( 3 downto  0))
       val a = nlc0(2) ## nlc1(2) ## nlc2(2) ## nlc3(2) ## nlc4(2) ## nlc5(2) ## nlc6(2) ## nlc7(2)
       val bne = fun_clz_BNE(a)
       
      val muxo = (bne(2 downto 0)).mux(
	  B"3'b000" -> nlc7(1 downto 0),
	  B"3'b001" -> nlc6(1 downto 0),
	  B"3'b010" -> nlc5(1 downto 0),
	  B"3'b011" -> nlc4(1 downto 0),
	  B"3'b100" -> nlc3(1 downto 0),
	  B"3'b101" -> nlc2(1 downto 0),
	  B"3'b110" -> nlc1(1 downto 0),
	  B"3'b111" -> nlc0(1 downto 0)
      )
      val r = (bne(3)) ?  B"6'b100000" | (B"1'b0" ## bne(2 downto 0) ## muxo(1 downto 0)) // 6 bits
      
      r.resize(32) // return value
   }
   // For trailing count, count using use leading count on bit-reversed value
   def fun_ctz(in:Bits) : Bits = {
       val inr = in(0) ## in(1) ## in(2) ## in(3) ## in(4) ## in(5) ## in(6) ## in(7) ## in(8) ## in(9) ## in(10) ## in(11) ## in(12) ## in(13) ## in(14) ## in(15) ## in(16) ## in(17) ## in(18) ## in(19) ## in(20) ## in(21) ## in(22) ## in(23) ## in(24) ## in(25) ## in(26) ## in(27) ## in(28) ## in(29) ## in(30) ## in(31)
       fun_clz(inr) // return value
   }

   // naive popcnt
   def fun_popcnt(in:Bits) : Bits = {
       val r = in(0).asBits.resize(6).asUInt + in(1).asBits.resize(6).asUInt + in(2).asBits.resize(6).asUInt + in(3).asBits.resize(6).asUInt +
	       in(4).asBits.resize(6).asUInt + in(5).asBits.resize(6).asUInt + in(6).asBits.resize(6).asUInt + in(7).asBits.resize(6).asUInt +
	       in(8).asBits.resize(6).asUInt + in(9).asBits.resize(6).asUInt + in(10).asBits.resize(6).asUInt + in(11).asBits.resize(6).asUInt +
	       in(12).asBits.resize(6).asUInt + in(13).asBits.resize(6).asUInt + in(14).asBits.resize(6).asUInt + in(15).asBits.resize(6).asUInt +
	       in(16).asBits.resize(6).asUInt + in(17).asBits.resize(6).asUInt + in(18).asBits.resize(6).asUInt + in(19).asBits.resize(6).asUInt +
	       in(20).asBits.resize(6).asUInt + in(21).asBits.resize(6).asUInt + in(22).asBits.resize(6).asUInt + in(23).asBits.resize(6).asUInt +
	       in(24).asBits.resize(6).asUInt + in(25).asBits.resize(6).asUInt + in(26).asBits.resize(6).asUInt + in(27).asBits.resize(6).asUInt +
	       in(28).asBits.resize(6).asUInt + in(29).asBits.resize(6).asUInt + in(30).asBits.resize(6).asUInt + in(31).asBits.resize(6).asUInt

       r.asBits.resize(32) // return value
   }

   //XPERMs
   def fun_xperm_n(rs1:Bits, rs2:Bits) : Bits = {
       val i0 = rs2(3 downto 0).asUInt
       val i1 = rs2(7 downto 4).asUInt
       val i2 = rs2(11 downto 8).asUInt
       val i3 = rs2(15 downto 12).asUInt
       val i4 = rs2(19 downto 16).asUInt
       val i5 = rs2(23 downto 20).asUInt
       val i6 = rs2(27 downto 24).asUInt
       val i7 = rs2(31 downto 28).asUInt
       val r0 = (i0).mux(
          0 -> rs1(3 downto 0),
          1 -> rs1(7 downto 4),
          2 -> rs1(11 downto 8),
          3 -> rs1(15 downto 12),
          4 -> rs1(19 downto 16),
          5 -> rs1(23 downto 20),
          6 -> rs1(27 downto 24),
          7 -> rs1(31 downto 28),
          default -> B"4'b0000"
	  )
       val r1 = (i1).mux(
          0 -> rs1(3 downto 0),
          1 -> rs1(7 downto 4),
          2 -> rs1(11 downto 8),
          3 -> rs1(15 downto 12),
          4 -> rs1(19 downto 16),
          5 -> rs1(23 downto 20),
          6 -> rs1(27 downto 24),
          7 -> rs1(31 downto 28),
          default -> B"4'b0000"
	  )
       val r2 = (i2).mux(
          0 -> rs1(3 downto 0),
          1 -> rs1(7 downto 4),
          2 -> rs1(11 downto 8),
          3 -> rs1(15 downto 12),
          4 -> rs1(19 downto 16),
          5 -> rs1(23 downto 20),
          6 -> rs1(27 downto 24),
          7 -> rs1(31 downto 28),
          default -> B"4'b0000"
	  )
       val r3 = (i3).mux(
          0 -> rs1(3 downto 0),
          1 -> rs1(7 downto 4),
          2 -> rs1(11 downto 8),
          3 -> rs1(15 downto 12),
          4 -> rs1(19 downto 16),
          5 -> rs1(23 downto 20),
          6 -> rs1(27 downto 24),
          7 -> rs1(31 downto 28),
          default -> B"4'b0000"
	  )
       val r4 = (i4).mux(
          0 -> rs1(3 downto 0),
          1 -> rs1(7 downto 4),
          2 -> rs1(11 downto 8),
          3 -> rs1(15 downto 12),
          4 -> rs1(19 downto 16),
          5 -> rs1(23 downto 20),
          6 -> rs1(27 downto 24),
          7 -> rs1(31 downto 28),
          default -> B"4'b0000"
	  )
       val r5 = (i5).mux(
          0 -> rs1(3 downto 0),
          1 -> rs1(7 downto 4),
          2 -> rs1(11 downto 8),
          3 -> rs1(15 downto 12),
          4 -> rs1(19 downto 16),
          5 -> rs1(23 downto 20),
          6 -> rs1(27 downto 24),
          7 -> rs1(31 downto 28),
          default -> B"4'b0000"
	  )
       val r6 = (i6).mux(
          0 -> rs1(3 downto 0),
          1 -> rs1(7 downto 4),
          2 -> rs1(11 downto 8),
          3 -> rs1(15 downto 12),
          4 -> rs1(19 downto 16),
          5 -> rs1(23 downto 20),
          6 -> rs1(27 downto 24),
          7 -> rs1(31 downto 28),
          default -> B"4'b0000"
	  )
       val r7 = (i7).mux(
          0 -> rs1(3 downto 0),
          1 -> rs1(7 downto 4),
          2 -> rs1(11 downto 8),
          3 -> rs1(15 downto 12),
          4 -> rs1(19 downto 16),
          5 -> rs1(23 downto 20),
          6 -> rs1(27 downto 24),
          7 -> rs1(31 downto 28),
          default -> B"4'b0000"
	  )
       r7 ## r6 ## r5 ## r4 ## r3 ## r2 ## r1 ## r0 // return value
   }
   def fun_xperm_b(rs1:Bits, rs2:Bits) : Bits = {
       val i0 = rs2(7 downto 0).asUInt;
       val i1 = rs2(15 downto 8).asUInt;
       val i2 = rs2(23 downto 16).asUInt;
       val i3 = rs2(31 downto 24).asUInt;
       val r0 = (i0).mux(
	   0 -> rs1(7 downto 0),
	   1 -> rs1(15 downto 8),
	   2 -> rs1(23 downto 16),
	   3 -> rs1(31 downto 24),
	   default -> B"8'b00000000"
	   )
       val r1 = (i1).mux(
	   0 -> rs1(7 downto 0),
	   1 -> rs1(15 downto 8),
	   2 -> rs1(23 downto 16),
	   3 -> rs1(31 downto 24),
	   default -> B"8'b00000000"
	   )
       val r2 = (i2).mux(
	   0 -> rs1(7 downto 0),
	   1 -> rs1(15 downto 8),
	   2 -> rs1(23 downto 16),
	   3 -> rs1(31 downto 24),
	   default -> B"8'b00000000"
	   )
       val r3 = (i3).mux(
	   0 -> rs1(7 downto 0),
	   1 -> rs1(15 downto 8),
	   2 -> rs1(23 downto 16),
	   3 -> rs1(31 downto 24),
	   default -> B"8'b00000000"
	   )
       r3 ## r2 ## r1 ## r0 // return value
   }
   def fun_xperm_h(rs1:Bits, rs2:Bits) : Bits = {
       val i0 = rs2(15 downto 0).asUInt;
       val i1 = rs2(31 downto 16).asUInt;
       val r0 = (i0).mux(
	   0 -> rs1(15 downto 0),
	   1 -> rs1(31 downto 16),
	   default -> B"16'x0000"
	   )
       val r1 = (i1).mux(
	   0 -> rs1(15 downto 0),
	   1 -> rs1(31 downto 16),
	   default -> B"16'x0000"
	   )
       r1 ## r0 // return value
   }

   def fun_fsl(rs1:Bits, rs3:Bits, rs2:Bits) : Bits = {
       val rawshamt = (rs2 & B"32'x0000003F").asUInt
       val shamt = (rawshamt >= 32) ? (rawshamt - 32) | (rawshamt)
       val A = (shamt === rawshamt) ? (rs1) | (rs3)
       val B = (shamt === rawshamt) ? (rs3) | (rs1)
       val r = (shamt === 0) ? (A) | ((A |<< shamt) | (B |>> (32-shamt))) 

       r // return value
   }

   def fun_fsr(rs1:Bits, rs3:Bits, rs2:Bits) : Bits = {
       val rawshamt = (rs2 & B"32'x0000003F").asUInt
       val shamt = (rawshamt >= 32) ? (rawshamt - 32) | (rawshamt)
       val A = (shamt === rawshamt) ? (rs1) | (rs3)
       val B = (shamt === rawshamt) ? (rs3) | (rs1)
       val r = (shamt === 0) ? (A) | ((A |>> shamt) | (B |<< (32-shamt))) 

       r // return value
   }

   def fun_bfp(rs1:Bits, rs2:Bits) : Bits = {       
       val off = rs2(20 downto 16).asUInt
       val rawlen = rs2(27 downto 24).asUInt
       val convlen = (rawlen === 0) ? (rawlen+16) | (rawlen)
       val len = ((convlen + off) > 32) ? (32 - off) | (convlen)
       val allones = B"16'xFFFF"
       val lenones = (allones |>> (16-len))
       //val one = B"17'x00001"
       //val lenones = (((one |<< len).asUInt) - 1).asBits;
       val mask = (lenones.resize(32) |<< off);
       val data = (rs2 & lenones.resize(32)) |<< off;
       
       val r = (rs1 & ~mask) | data

       r // return value
   }

// End prologue
} // object Plugin
class BitManipAllPlugin(earlyInjection : Boolean = true) extends Plugin[VexRiscv] {
	import BitManipAllPlugin._
	object IS_BitManipAll extends Stageable(Bool)
	object BitManipAll_FINAL_OUTPUT extends Stageable(Bits(32 bits))
	override def setup(pipeline: VexRiscv): Unit = {
		import pipeline.config._
		val immediateActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.IMI,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> Bool(earlyInjection),
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			IS_BitManipAll -> True
			)
		val binaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			SRC2_CTRL                -> Src2CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> Bool(earlyInjection),
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			RS2_USE -> True,
			IS_BitManipAll -> True
			)
		val unaryActions = List[(Stageable[_ <: BaseType],Any)](
			SRC1_CTRL                -> Src1CtrlEnum.RS,
			REGFILE_WRITE_VALID      -> True,
			BYPASSABLE_EXECUTE_STAGE -> Bool(earlyInjection),
			BYPASSABLE_MEMORY_STAGE  -> True,
			RS1_USE -> True,
			IS_BitManipAll -> True
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
			IS_BitManipAll -> True
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
			IS_BitManipAll -> True
			)
		def ANDN_KEY = M"0100000----------111-----0110011"
		def ORN_KEY = M"0100000----------110-----0110011"
		def XNOR_KEY = M"0100000----------100-----0110011"
		def SLO_KEY = M"0010000----------001-----0110011"
		def SRO_KEY = M"0010000----------101-----0110011"
		def ROL_KEY = M"0110000----------001-----0110011"
		def ROR_KEY = M"0110000----------101-----0110011"
		def SH1ADD_KEY = M"0010000----------010-----0110011"
		def SH2ADD_KEY = M"0010000----------100-----0110011"
		def SH3ADD_KEY = M"0010000----------110-----0110011"
		def BCLR_KEY = M"0100100----------001-----0110011"
		def BSET_KEY = M"0010100----------001-----0110011"
		def BINV_KEY = M"0110100----------001-----0110011"
		def BEXT_KEY = M"0100100----------101-----0110011"
		def GORC_KEY = M"0010100----------101-----0110011"
		def GREV_KEY = M"0110100----------101-----0110011"
		def MIN_KEY = M"0000101----------100-----0110011"
		def MINU_KEY = M"0000101----------101-----0110011"
		def MAX_KEY = M"0000101----------110-----0110011"
		def MAXU_KEY = M"0000101----------111-----0110011"
		def SHFL_KEY = M"0000100----------001-----0110011"
		def UNSHFL_KEY = M"0000100----------101-----0110011"
		def PACK_KEY = M"0000100----------100-----0110011"
		def PACKU_KEY = M"0100100----------100-----0110011"
		def PACKH_KEY = M"0000100----------111-----0110011"
		def BFP_KEY = M"0100100----------111-----0110011"
		def XPERMdotN_KEY = M"0010100----------010-----0110011"
		def XPERMdotB_KEY = M"0010100----------100-----0110011"
		def XPERMdotH_KEY = M"0010100----------110-----0110011"
		def SLOI_KEY = M"00100------------001-----0010011"
		def SROI_KEY = M"00100------------101-----0010011"
		def RORI_KEY = M"01100------------101-----0010011"
		def BCLRI_KEY = M"01001------------001-----0010011"
		def BSETI_KEY = M"00101------------001-----0010011"
		def BINVI_KEY = M"01101------------001-----0010011"
		def BEXTI_KEY = M"01001------------101-----0010011"
		def GORCI_KEY = M"00101------------101-----0010011"
		def GREVI_KEY = M"01101------------101-----0010011"
		def SHFLI_KEY = M"000010-----------001-----0010011"
		def UNSHFLI_KEY = M"000010-----------101-----0010011"
		def CLZ_KEY = M"011000000000-----001-----0010011"
		def CTZ_KEY = M"011000000001-----001-----0010011"
		def CPOP_KEY = M"011000000010-----001-----0010011"
		def SEXTdotB_KEY = M"011000000100-----001-----0010011"
		def SEXTdotH_KEY = M"011000000101-----001-----0010011"
		def CMIX_KEY = M"-----11----------001-----0110011"
		def CMOV_KEY = M"-----11----------101-----0110011"
		def FSL_KEY = M"-----10----------001-----0110011"
		def FSR_KEY = M"-----10----------101-----0110011"
		def FSRI_KEY = M"-----1-----------101-----0010011"
		val decoderService = pipeline.service(classOf[DecoderService])
		decoderService.addDefault(IS_BitManipAll, False)
		decoderService.add(List(
			ANDN_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_bitwise, BitManipAllCtrlbitwise -> BitManipAllCtrlbitwiseEnum.CTRL_ANDN)),
			ORN_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_bitwise, BitManipAllCtrlbitwise -> BitManipAllCtrlbitwiseEnum.CTRL_ORN)),
			XNOR_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_bitwise, BitManipAllCtrlbitwise -> BitManipAllCtrlbitwiseEnum.CTRL_XNOR)),
			SLO_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_shift, BitManipAllCtrlshift -> BitManipAllCtrlshiftEnum.CTRL_SLO)),
			SRO_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_shift, BitManipAllCtrlshift -> BitManipAllCtrlshiftEnum.CTRL_SRO)),
			SLOI_KEY	-> (immediateActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_shift, BitManipAllCtrlshift -> BitManipAllCtrlshiftEnum.CTRL_SLO)),
			SROI_KEY	-> (immediateActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_shift, BitManipAllCtrlshift -> BitManipAllCtrlshiftEnum.CTRL_SRO)),
			ROL_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_rotation, BitManipAllCtrlrotation -> BitManipAllCtrlrotationEnum.CTRL_ROL)),
			ROR_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_rotation, BitManipAllCtrlrotation -> BitManipAllCtrlrotationEnum.CTRL_ROR)),
			RORI_KEY	-> (immediateActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_rotation, BitManipAllCtrlrotation -> BitManipAllCtrlrotationEnum.CTRL_ROR)),
			SH1ADD_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_sh_add, BitManipAllCtrlsh_add -> BitManipAllCtrlsh_addEnum.CTRL_SH1ADD)),
			SH2ADD_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_sh_add, BitManipAllCtrlsh_add -> BitManipAllCtrlsh_addEnum.CTRL_SH2ADD)),
			SH3ADD_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_sh_add, BitManipAllCtrlsh_add -> BitManipAllCtrlsh_addEnum.CTRL_SH3ADD)),
			BCLR_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_singlebit, BitManipAllCtrlsinglebit -> BitManipAllCtrlsinglebitEnum.CTRL_BCLR)),
			BSET_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_singlebit, BitManipAllCtrlsinglebit -> BitManipAllCtrlsinglebitEnum.CTRL_BSET)),
			BINV_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_singlebit, BitManipAllCtrlsinglebit -> BitManipAllCtrlsinglebitEnum.CTRL_BINV)),
			BEXT_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_singlebit, BitManipAllCtrlsinglebit -> BitManipAllCtrlsinglebitEnum.CTRL_BEXT)),
			BCLRI_KEY	-> (immediateActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_singlebit, BitManipAllCtrlsinglebit -> BitManipAllCtrlsinglebitEnum.CTRL_BCLR)),
			BSETI_KEY	-> (immediateActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_singlebit, BitManipAllCtrlsinglebit -> BitManipAllCtrlsinglebitEnum.CTRL_BSET)),
			BINVI_KEY	-> (immediateActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_singlebit, BitManipAllCtrlsinglebit -> BitManipAllCtrlsinglebitEnum.CTRL_BINV)),
			BEXTI_KEY	-> (immediateActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_singlebit, BitManipAllCtrlsinglebit -> BitManipAllCtrlsinglebitEnum.CTRL_BEXT)),
			GORC_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_grevroc, BitManipAllCtrlgrevroc -> BitManipAllCtrlgrevrocEnum.CTRL_GORC)),
			GREV_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_grevroc, BitManipAllCtrlgrevroc -> BitManipAllCtrlgrevrocEnum.CTRL_GREV)),
			MIN_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_minmax, BitManipAllCtrlminmax -> BitManipAllCtrlminmaxEnum.CTRL_MIN)),
			MINU_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_minmax, BitManipAllCtrlminmax -> BitManipAllCtrlminmaxEnum.CTRL_MINU)),
			MAX_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_minmax, BitManipAllCtrlminmax -> BitManipAllCtrlminmaxEnum.CTRL_MAX)),
			MAXU_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_minmax, BitManipAllCtrlminmax -> BitManipAllCtrlminmaxEnum.CTRL_MAXU)),
			SHFL_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_shuffle, BitManipAllCtrlshuffle -> BitManipAllCtrlshuffleEnum.CTRL_SHFL)),
			UNSHFL_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_shuffle, BitManipAllCtrlshuffle -> BitManipAllCtrlshuffleEnum.CTRL_UNSHFL)),
			SHFLI_KEY	-> (immediateActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_shuffle, BitManipAllCtrlshuffle -> BitManipAllCtrlshuffleEnum.CTRL_SHFL)),
			UNSHFLI_KEY	-> (immediateActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_shuffle, BitManipAllCtrlshuffle -> BitManipAllCtrlshuffleEnum.CTRL_UNSHFL)),
			PACK_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_pack, BitManipAllCtrlpack -> BitManipAllCtrlpackEnum.CTRL_PACK)),
			PACKU_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_pack, BitManipAllCtrlpack -> BitManipAllCtrlpackEnum.CTRL_PACKU)),
			PACKH_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_pack, BitManipAllCtrlpack -> BitManipAllCtrlpackEnum.CTRL_PACKH)),
			BFP_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_BFP)),
			XPERMdotN_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_xperm, BitManipAllCtrlxperm -> BitManipAllCtrlxpermEnum.CTRL_XPERMdotN)),
			XPERMdotB_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_xperm, BitManipAllCtrlxperm -> BitManipAllCtrlxpermEnum.CTRL_XPERMdotB)),
			XPERMdotH_KEY	-> (binaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_xperm, BitManipAllCtrlxperm -> BitManipAllCtrlxpermEnum.CTRL_XPERMdotH)),
			GORCI_KEY	-> (immediateActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_grevorc, BitManipAllCtrlgrevorc -> BitManipAllCtrlgrevorcEnum.CTRL_GORC)),
			GREVI_KEY	-> (immediateActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_grevorc, BitManipAllCtrlgrevorc -> BitManipAllCtrlgrevorcEnum.CTRL_GREV)),
			CLZ_KEY	-> (unaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_countzeroes, BitManipAllCtrlcountzeroes -> BitManipAllCtrlcountzeroesEnum.CTRL_CLZ)),
			CTZ_KEY	-> (unaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_countzeroes, BitManipAllCtrlcountzeroes -> BitManipAllCtrlcountzeroesEnum.CTRL_CTZ)),
			CPOP_KEY	-> (unaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_countzeroes, BitManipAllCtrlcountzeroes -> BitManipAllCtrlcountzeroesEnum.CTRL_CPOP)),
			SEXTdotB_KEY	-> (unaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_signextend, BitManipAllCtrlsignextend -> BitManipAllCtrlsignextendEnum.CTRL_SEXTdotB)),
			SEXTdotH_KEY	-> (unaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_signextend, BitManipAllCtrlsignextend -> BitManipAllCtrlsignextendEnum.CTRL_SEXTdotH)),
			CMIX_KEY	-> (ternaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_ternary, BitManipAllCtrlternary -> BitManipAllCtrlternaryEnum.CTRL_CMIX)),
			CMOV_KEY	-> (ternaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_ternary, BitManipAllCtrlternary -> BitManipAllCtrlternaryEnum.CTRL_CMOV)),
			FSL_KEY	-> (ternaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_ternary, BitManipAllCtrlternary -> BitManipAllCtrlternaryEnum.CTRL_FSL)),
			FSR_KEY	-> (ternaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_ternary, BitManipAllCtrlternary -> BitManipAllCtrlternaryEnum.CTRL_FSR)),
			FSRI_KEY	-> (immTernaryActions ++ List(BitManipAllCtrl -> BitManipAllCtrlEnum.CTRL_ternary, BitManipAllCtrlternary -> BitManipAllCtrlternaryEnum.CTRL_FSR))
		))
	} // override def setup
	override def build(pipeline: VexRiscv): Unit = {
		import pipeline._
		import pipeline.config._
		execute plug new Area{
			import execute._
			val val_bitwise = input(BitManipAllCtrlbitwise).mux(
				BitManipAllCtrlbitwiseEnum.CTRL_ANDN -> (input(SRC1) & ~input(SRC2)),
				BitManipAllCtrlbitwiseEnum.CTRL_ORN -> (input(SRC1) | ~input(SRC2)),
				BitManipAllCtrlbitwiseEnum.CTRL_XNOR -> (input(SRC1) ^ ~input(SRC2))
			) // mux bitwise
			val val_shift = input(BitManipAllCtrlshift).mux(
				BitManipAllCtrlshiftEnum.CTRL_SLO -> ~((~input(SRC1)) |<< (input(SRC2)&31).asUInt),
				BitManipAllCtrlshiftEnum.CTRL_SRO -> ~((~input(SRC1)) |>> (input(SRC2)&31).asUInt)
			) // mux shift
			val val_rotation = input(BitManipAllCtrlrotation).mux(
				BitManipAllCtrlrotationEnum.CTRL_ROL -> input(SRC1).rotateLeft((input(SRC2)&31)(4 downto 0).asUInt),
				BitManipAllCtrlrotationEnum.CTRL_ROR -> input(SRC1).rotateRight((input(SRC2)&31)(4 downto 0).asUInt)
			) // mux rotation
			val val_sh_add = input(BitManipAllCtrlsh_add).mux(
				BitManipAllCtrlsh_addEnum.CTRL_SH1ADD -> ((input(SRC1) |<< 1).asUInt + input(SRC2).asUInt),
				BitManipAllCtrlsh_addEnum.CTRL_SH2ADD -> ((input(SRC1) |<< 2).asUInt + input(SRC2).asUInt),
				BitManipAllCtrlsh_addEnum.CTRL_SH3ADD -> ((input(SRC1) |<< 3).asUInt + input(SRC2).asUInt)
			) // mux sh_add
			val val_singlebit = input(BitManipAllCtrlsinglebit).mux(
				BitManipAllCtrlsinglebitEnum.CTRL_BCLR -> (input(SRC1) & ~(B"32'x00000001"|<<((input(SRC2)&31).asUInt))),
				BitManipAllCtrlsinglebitEnum.CTRL_BEXT -> ((input(SRC1) |>> ((input(SRC2)&31).asUInt)) & B"32'x00000001"),
				BitManipAllCtrlsinglebitEnum.CTRL_BINV -> (input(SRC1) ^  (B"32'x00000001"|<<((input(SRC2)&31).asUInt))),
				BitManipAllCtrlsinglebitEnum.CTRL_BSET -> (input(SRC1) |  (B"32'x00000001"|<<((input(SRC2)&31).asUInt)))
			) // mux singlebit
			val val_grevroc = input(BitManipAllCtrlgrevroc).mux(
				BitManipAllCtrlgrevrocEnum.CTRL_GORC -> fun_gorc(input(SRC1), input(SRC2)),
				BitManipAllCtrlgrevrocEnum.CTRL_GREV -> fun_grev(input(SRC1), input(SRC2))
			) // mux grevroc
			val val_minmax = input(BitManipAllCtrlminmax).mux(
				BitManipAllCtrlminmaxEnum.CTRL_MAX -> ((input(SRC1).asSInt > input(SRC2).asSInt) ? input(SRC1) | input(SRC2)),
				BitManipAllCtrlminmaxEnum.CTRL_MAXU -> ((input(SRC1).asUInt > input(SRC2).asUInt) ? input(SRC1) | input(SRC2)),
				BitManipAllCtrlminmaxEnum.CTRL_MIN -> ((input(SRC1).asSInt < input(SRC2).asSInt) ? input(SRC1) | input(SRC2)),
				BitManipAllCtrlminmaxEnum.CTRL_MINU -> ((input(SRC1).asUInt < input(SRC2).asUInt) ? input(SRC1) | input(SRC2))
			) // mux minmax
			val val_shuffle = input(BitManipAllCtrlshuffle).mux(
				BitManipAllCtrlshuffleEnum.CTRL_SHFL -> fun_shfl32(input(SRC1), input(SRC2)),
				BitManipAllCtrlshuffleEnum.CTRL_UNSHFL -> fun_unshfl32(input(SRC1), input(SRC2))
			) // mux shuffle
			val val_pack = input(BitManipAllCtrlpack).mux(
				BitManipAllCtrlpackEnum.CTRL_PACK -> (input(SRC2)(15 downto 0) ## input(SRC1)(15 downto 0)),
				BitManipAllCtrlpackEnum.CTRL_PACKH -> B"16'x0000" ## (input(SRC2)(7 downto 0) ## input(SRC1)(7 downto 0)),
				BitManipAllCtrlpackEnum.CTRL_PACKU -> (input(SRC2)(31 downto 16) ## input(SRC1)(31 downto 16))
			) // mux pack
			val val_xperm = input(BitManipAllCtrlxperm).mux(
				BitManipAllCtrlxpermEnum.CTRL_XPERMdotB -> fun_xperm_b(input(SRC1), input(SRC2)),
				BitManipAllCtrlxpermEnum.CTRL_XPERMdotH -> fun_xperm_h(input(SRC1), input(SRC2)),
				BitManipAllCtrlxpermEnum.CTRL_XPERMdotN -> fun_xperm_n(input(SRC1), input(SRC2))
			) // mux xperm
			val val_grevorc = input(BitManipAllCtrlgrevorc).mux(
				BitManipAllCtrlgrevorcEnum.CTRL_GORC -> fun_gorc(input(SRC1), input(SRC2)),
				BitManipAllCtrlgrevorcEnum.CTRL_GREV -> fun_grev(input(SRC1), input(SRC2))
			) // mux grevorc
			val val_countzeroes = input(BitManipAllCtrlcountzeroes).mux(
				BitManipAllCtrlcountzeroesEnum.CTRL_CLZ -> fun_clz(input(SRC1)),
				BitManipAllCtrlcountzeroesEnum.CTRL_CPOP -> fun_popcnt(input(SRC1)),
				BitManipAllCtrlcountzeroesEnum.CTRL_CTZ -> fun_ctz(input(SRC1))
			) // mux countzeroes
			val val_signextend = input(BitManipAllCtrlsignextend).mux(
				BitManipAllCtrlsignextendEnum.CTRL_SEXTdotB -> (Bits(24 bits).setAllTo(input(SRC1)(7)) ## input(SRC1)(7 downto 0)),
				BitManipAllCtrlsignextendEnum.CTRL_SEXTdotH -> (Bits(16 bits).setAllTo(input(SRC1)(15)) ## input(SRC1)(15 downto 0))
			) // mux signextend
			val val_ternary = input(BitManipAllCtrlternary).mux(
				BitManipAllCtrlternaryEnum.CTRL_CMIX -> ((input(SRC1) & input(SRC2)) | (input(SRC3) & ~input(SRC2))),
				BitManipAllCtrlternaryEnum.CTRL_CMOV -> ((input(SRC2).asUInt =/= 0) ? input(SRC1) | input(SRC3)),
				BitManipAllCtrlternaryEnum.CTRL_FSL -> fun_fsl(input(SRC1), input(SRC3), input(SRC2)),
				BitManipAllCtrlternaryEnum.CTRL_FSR -> fun_fsr(input(SRC1), input(SRC3), input(SRC2))
			) // mux ternary
			insert(BitManipAll_FINAL_OUTPUT) := input(BitManipAllCtrl).mux(
				BitManipAllCtrlEnum.CTRL_bitwise -> val_bitwise.asBits,
				BitManipAllCtrlEnum.CTRL_shift -> val_shift.asBits,
				BitManipAllCtrlEnum.CTRL_rotation -> val_rotation.asBits,
				BitManipAllCtrlEnum.CTRL_sh_add -> val_sh_add.asBits,
				BitManipAllCtrlEnum.CTRL_singlebit -> val_singlebit.asBits,
				BitManipAllCtrlEnum.CTRL_grevroc -> val_grevroc.asBits,
				BitManipAllCtrlEnum.CTRL_minmax -> val_minmax.asBits,
				BitManipAllCtrlEnum.CTRL_shuffle -> val_shuffle.asBits,
				BitManipAllCtrlEnum.CTRL_pack -> val_pack.asBits,
				BitManipAllCtrlEnum.CTRL_BFP -> fun_bfp(input(SRC1), input(SRC2)).asBits,
				BitManipAllCtrlEnum.CTRL_xperm -> val_xperm.asBits,
				BitManipAllCtrlEnum.CTRL_grevorc -> val_grevorc.asBits,
				BitManipAllCtrlEnum.CTRL_countzeroes -> val_countzeroes.asBits,
				BitManipAllCtrlEnum.CTRL_signextend -> val_signextend.asBits,
				BitManipAllCtrlEnum.CTRL_ternary -> val_ternary.asBits
			) // primary mux
		} // execute plug newArea
		val injectionStage = if(earlyInjection) execute else memory
		injectionStage plug new Area {
			import injectionStage._
			when (arbitration.isValid && input(IS_BitManipAll)) {
				output(REGFILE_WRITE_DATA) := input(BitManipAll_FINAL_OUTPUT)
			} // when input is
		} // injectionStage plug newArea
	} // override def build
} // class Plugin
