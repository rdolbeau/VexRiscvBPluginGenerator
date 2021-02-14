/*
 * Copyright (c) 2020 Romain Dolbeau <romain.dolbeau@european-processor-initiative.eu>
 * MIT License
 * See the LICENSE file at the top level of this software distribution for details.
 */

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>

#include "inst.hpp"
#include "group.hpp"
#include "unparse.hpp"

std::set<group*>* createGroups(const std::set<const instruction*> instructions) {
	std::set<group*>* groups = new std::set<group*>();

	for (const instruction* inst : instructions) {
		bool done = false;
		for (group* g : *groups) {
			if (g->match(inst)) {
				g->add(inst);
				done = true;
			}
		}
		if (!done) {
			group* g = new group(inst->group);
			g->add(inst);
			groups->insert(g);
		}
	}

	return groups;
}


void unparse(std::ostream& output,
	     const std::string prefix,
	     const std::set<const instruction*> instructions,
	     std::map<std::string,std::string> semantics,
	     std::map<std::string,int> em_widths,
	     std::map<std::string,std::string> mem_semantics,
	     std::vector<std::string> prologues,
	     std::vector<std::string> extras,
	     bool wide) {
	std::set<group*>* groups = createGroups(instructions);

	const std::string ctrlString = prefix + "Ctrl";
	const std::string ctrlEnumString = prefix + "CtrlEnum";
	const std::string outputString = prefix + "_FINAL_OUTPUT";
	const std::string isString = "IS_" + prefix;
	const bool two_cycles = em_widths.size() > 0;
	const std::string bypassableExecuteString = two_cycles ? "False" : "Bool(earlyInjection)";

	output << "// WARNING: this is auto-generated code!" << std::endl;
	output << "// See https://github.com/rdolbeau/VexRiscvBPluginGenerator/" << std::endl;
	output << "package vexriscv.plugin" << std::endl;
	output << "import spinal.core._" << std::endl;
	output << "import vexriscv.{Stageable, DecoderService, VexRiscv}" << std::endl;

	output << "object " << prefix << "Plugin {" << std::endl;

	// objects for second-level MUXes
	for (group* g : *groups) {
		if (g->opnames.size() > 1) {
		output << '\t' << "object " << ctrlString << g->name << "Enum extends SpinalEnum(binarySequential) {" << std::endl;
		output << '\t' << '\t' << " val ";
		bool comma = false;
		for (std::string opname : g->opnames) {
			if (comma) output << ", ";
			output << "CTRL_" << opname;
			comma = true;
		}
		output << " = newElement()" << std::endl;
		output << '\t' << "}" << std::endl;
		}
	}

	// object for first-level MUX
	output << '\t' << "object " << ctrlEnumString << " extends SpinalEnum(binarySequential) {" << std::endl;
	output << '\t' << '\t' << " val ";
	bool comma = false;
	for (group* g : *groups) {
		if (comma) output << ", ";
		if (g->opnames.size() > 1)
			output << g->ctrlName();
		else
			output << "CTRL_" << (*g->opnames.begin());
		comma = true;
	}
	output << " = newElement()" << std::endl;
	output << '\t' << "}" << std::endl;

	// Stageable objects
	
	for (group* g : *groups) {
		if (g->opnames.size() > 1)
			output << '\t' << "object " << ctrlString << g->name << " extends Stageable(" << ctrlString << g->name << "Enum())" << std::endl;
	}
	output << '\t' << "object " << ctrlString << " extends Stageable(" << ctrlString << "Enum())" << std::endl;

	output << "// Prologue" << std::endl;
	for (std::string prologue : prologues)
	  output << prologue << std::endl;
	output << "// End prologue" << std::endl;

	output << "} // object Plugin" << std::endl;

	// Plugin class
	output << "class " << prefix << "Plugin"; if (!two_cycles) output << "(earlyInjection : Boolean = true)"; output << " extends Plugin[VexRiscv] {" << std::endl;
	output << '\t' << "import " << prefix << "Plugin._" << std::endl;
	output << '\t' << "object " << isString << " extends Stageable(Bool)" << std::endl;
	output << '\t' << "object " << outputString << " extends Stageable(Bits(" << (wide ? 64 : 32) << " bits))" << std::endl;

	if (two_cycles) {
		for (auto const& pair : em_widths) {
			std::string regName = prefix + "_INTERMEDIATE_" + pair.first + "" + std::to_string(pair.second);
			output << '\t' << "object " << regName << " extends Stageable(Bits(" << pair.second << " bits))" << std::endl;
		}
	}
	
	output << '\t' << "override def setup(pipeline: VexRiscv): Unit = {" << std::endl;
	output << '\t' << '\t' << "import pipeline.config._" << std::endl;
	
	// define standard actions
	output << '\t' << '\t' << "val immediateActions = List[(Stageable[_ <: BaseType],Any)](" << std::endl;
	output << '\t' << '\t' << "\tSRC1_CTRL                -> Src1CtrlEnum.RS," << std::endl;
	output << '\t' << '\t' << "\tSRC2_CTRL                -> Src2CtrlEnum.IMI," << std::endl;
	output << '\t' << '\t' << "\tREGFILE_WRITE_VALID      -> True," << std::endl;
	if (wide) output << '\t' << '\t' << "\tREGFILE_WRITE_VALID_ODD  -> True," << std::endl;
	output << '\t' << '\t' << "\tBYPASSABLE_EXECUTE_STAGE -> " << bypassableExecuteString << "," << std::endl;
	output << '\t' << '\t' << "\tBYPASSABLE_MEMORY_STAGE  -> True," << std::endl;
	output << '\t' << '\t' << "\tRS1_USE -> True," << std::endl;
	output << '\t' << '\t' << "\t" << isString << " -> True" << std::endl;
	output << '\t' << '\t' << "\t)" << std::endl;
	
	output << '\t' << '\t' << "val binaryActions = List[(Stageable[_ <: BaseType],Any)](" << std::endl;
	output << '\t' << '\t' << "\tSRC1_CTRL                -> Src1CtrlEnum.RS," << std::endl;
	output << '\t' << '\t' << "\tSRC2_CTRL                -> Src2CtrlEnum.RS," << std::endl;
	output << '\t' << '\t' << "\tREGFILE_WRITE_VALID      -> True," << std::endl;
	if (wide) output << '\t' << '\t' << "\tREGFILE_WRITE_VALID_ODD  -> True," << std::endl;
	output << '\t' << '\t' << "\tBYPASSABLE_EXECUTE_STAGE -> " << bypassableExecuteString << "," << std::endl;
	output << '\t' << '\t' << "\tBYPASSABLE_MEMORY_STAGE  -> True," << std::endl;
	output << '\t' << '\t' << "\tRS1_USE -> True," << std::endl;
	output << '\t' << '\t' << "\tRS2_USE -> True," << std::endl;
	output << '\t' << '\t' << "\t" << isString << " -> True" << std::endl;
	output << '\t' << '\t' << "\t)" << std::endl;
	
	output << '\t' << '\t' << "val unaryActions = List[(Stageable[_ <: BaseType],Any)](" << std::endl;
	output << '\t' << '\t' << "\tSRC1_CTRL                -> Src1CtrlEnum.RS," << std::endl;
	output << '\t' << '\t' << "\tREGFILE_WRITE_VALID      -> True," << std::endl;
	if (wide) output << '\t' << '\t' << "\tREGFILE_WRITE_VALID_ODD  -> True," << std::endl;
	output << '\t' << '\t' << "\tBYPASSABLE_EXECUTE_STAGE -> " << bypassableExecuteString << "," << std::endl;
	output << '\t' << '\t' << "\tBYPASSABLE_MEMORY_STAGE  -> True," << std::endl;
	output << '\t' << '\t' << "\tRS1_USE -> True," << std::endl;
	output << '\t' << '\t' << "\t" << isString << " -> True" << std::endl;
	output << '\t' << '\t' << "\t)" << std::endl;
 
	output << '\t' << '\t' << "val ternaryActions = List[(Stageable[_ <: BaseType],Any)](" << std::endl;
	output << '\t' << '\t' << "\tSRC1_CTRL                -> Src1CtrlEnum.RS," << std::endl;
	output << '\t' << '\t' << "\tSRC2_CTRL                -> Src2CtrlEnum.RS," << std::endl;
	output << '\t' << '\t' << "\tSRC3_CTRL                -> Src3CtrlEnum.RS," << std::endl;
	output << '\t' << '\t' << "\tREGFILE_WRITE_VALID      -> True," << std::endl;
	if (wide) output << '\t' << '\t' << "\tREGFILE_WRITE_VALID_ODD  -> True," << std::endl;
	output << '\t' << '\t' << "\tBYPASSABLE_EXECUTE_STAGE -> " << bypassableExecuteString << "," << std::endl;
	output << '\t' << '\t' << "\tBYPASSABLE_MEMORY_STAGE  -> True," << std::endl;
	output << '\t' << '\t' << "\tRS1_USE -> True," << std::endl;
	output << '\t' << '\t' << "\tRS2_USE -> True," << std::endl;
	output << '\t' << '\t' << "\tRS3_USE -> True," << std::endl;
	output << '\t' << '\t' << "\t" << isString << " -> True" << std::endl;
	output << '\t' << '\t' << "\t)" << std::endl;
 
	output << '\t' << '\t' << "val immTernaryActions = List[(Stageable[_ <: BaseType],Any)](" << std::endl;
	output << '\t' << '\t' << "\tSRC1_CTRL                -> Src1CtrlEnum.RS," << std::endl;
	output << '\t' << '\t' << "\tSRC2_CTRL                -> Src2CtrlEnum.IMI," << std::endl;
	output << '\t' << '\t' << "\tSRC3_CTRL                -> Src3CtrlEnum.RS," << std::endl;
	output << '\t' << '\t' << "\tREGFILE_WRITE_VALID      -> True," << std::endl;
	if (wide) output << '\t' << '\t' << "\tREGFILE_WRITE_VALID_ODD  -> True," << std::endl;
	output << '\t' << '\t' << "\tBYPASSABLE_EXECUTE_STAGE -> " << bypassableExecuteString << "," << std::endl;
	output << '\t' << '\t' << "\tBYPASSABLE_MEMORY_STAGE  -> True," << std::endl;
	output << '\t' << '\t' << "\tRS1_USE -> True," << std::endl;
	output << '\t' << '\t' << "\tRS3_USE -> True," << std::endl;
	output << '\t' << '\t' << "\t" << isString << " -> True" << std::endl;
	output << '\t' << '\t' << "\t)" << std::endl;

	// inst keys
	for (const instruction* inst : instructions) {
		output << '\t' << '\t' << "def " << inst->keyName() << " = M\"" << inst->key << "\"" << std::endl;
	}
	
	output << '\t' << '\t' << "val decoderService = pipeline.service(classOf[DecoderService])" << std::endl;
	output << '\t' << '\t' << "decoderService.addDefault(" << isString << ", False)" << std::endl;

	// add actions
	output << '\t' << '\t' << "decoderService.add(List(" << std::endl;
	//	for (const group* g : *groups) {
	for (auto it = groups->begin() ; it != groups->end() ; it++) {
		group* g = *it;
		for (auto it2 = g->instructions.begin() ; it2 != g->instructions.end() ; it2++) {
			const instruction* inst = *it2;
			const std::string nameCtrlString = ctrlString + g->name;
			const std::string nameCtrlEnumString = ctrlString + g->name + "Enum";
			std::string control;
			if (g->opnames.size() > 1)
				control = ctrlString + " -> " + ctrlEnumString + "." + g->ctrlName() +  ", " + nameCtrlString + " -> " + nameCtrlEnumString + ".CTRL_" + inst->opname;
			else
				control = ctrlString + " -> " + ctrlEnumString + ".CTRL_" + inst->opname;
			if (!inst->isImm()) {
				if (semantics[inst->opname].find("SRC2") != std::string::npos)
				  if (semantics[inst->opname].find("SRC3") != std::string::npos)
				    output << '\t' << '\t' << "\t" << inst->keyName() << "\t-> (ternaryActions ++ List("<< control << "))";
				  else
				    output << '\t' << '\t' << "\t" << inst->keyName() << "\t-> (binaryActions ++ List("<< control << "))";
				else
				  output << '\t' << '\t' << "\t" << inst->keyName() << "\t-> (unaryActions ++ List("<< control << "))";
			} else {
				if (semantics[inst->opname].find("SRC3") != std::string::npos)
					output << '\t' << '\t' << "\t" << inst->keyName() << "\t-> (immTernaryActions ++ List("<< control << "))";
				else
					output << '\t' << '\t' << "\t" << inst->keyName() << "\t-> (immediateActions ++ List("<< control << "))";
			}
			if ((std::next(it,1) == groups->end()) && (std::next(it2,1) == g->instructions.end()))
				output << std::endl;
			else
				output << "," << std::endl;
		}
	}
	output << '\t' << '\t' << "))" << std::endl;
	output << '\t' << "} // override def setup" << std::endl;

	output << '\t' << "override def build(pipeline: VexRiscv): Unit = {" << std::endl;
	output << '\t' << '\t' << "import pipeline._" << std::endl;
	output << '\t' << '\t' << "import pipeline.config._" << std::endl;

	if (extras.size()>0) {
	  output << "// Extra" << std::endl;
	  for (std::string extra : extras)
	    output << extra << std::endl;
	  output << "// End Extra" << std::endl;
	}

	if (!two_cycles) {
	output << '\t' << '\t' << "execute plug new Area{" << std::endl;
	output << '\t' << '\t' << '\t' << "import execute._" << std::endl;

	// 2nd level MUXes
	for (const group* g : *groups) {
		if (g->opnames.size() > 1) {
		output << '\t' << '\t' << '\t' << "val val_" << g->name << " = input("<< ctrlString << g->name << ").mux(" << std::endl;
		for (auto it = g->opnames.begin() ; it != g->opnames.end() ; it++) {
			std::string opname = *it;
			output << '\t' << '\t' << '\t' << '\t' << ctrlString << g->name << "Enum.CTRL_" << opname << " -> " << semantics[opname];
			if (std::next(it, 1) == g->opnames.end())
				output << std::endl;
			else
				output << "," << std::endl;
		}
		output << '\t' << '\t' << '\t' << ") // mux " << g->name << std::endl;
		}
	}

	// conditional last level mux
	output << '\t' << '\t' << '\t' << "insert(" << outputString << ") := input(" << ctrlString << ").mux(" << std::endl;
	for (auto it = groups->begin() ; it != groups->end() ; it++) {
		group* g = *it;
		if (g->opnames.size() > 1) {
			output << '\t' << '\t' << '\t' << '\t' << ctrlEnumString << "." << g->ctrlName() << " -> val_" << g->name << ".asBits";
		} else {
			output << '\t' << '\t' << '\t' << '\t' << ctrlEnumString << ".CTRL_" << (*g->opnames.begin()) << " -> " << semantics[*g->opnames.begin()] << ".asBits";
		}
		if (std::next(it, 1) == groups->end())
			output << std::endl;
		else
			output << "," << std::endl;
	}
	output << '\t' << '\t' << '\t' << ") // primary mux" << std::endl;
	output << '\t' << '\t' << "} // execute plug newArea" << std::endl;

	output << '\t' << '\t' << "val injectionStage = if(earlyInjection) execute else memory" << std::endl;
	output << '\t' << '\t' << "injectionStage plug new Area {" << std::endl;
	output << '\t' << '\t' << '\t' << "import injectionStage._" << std::endl;
	output << '\t' << '\t' << '\t' << "when (arbitration.isValid && input(" << isString << ")) {" << std::endl;
	if (wide) {
		output << '\t' << '\t' << '\t' << '\t' << "output(REGFILE_WRITE_DATA) := input(" << outputString << ")(31 downto 0)" << std::endl;
		output << '\t' << '\t' << '\t' << '\t' << "output(REGFILE_WRITE_DATA_ODD) := input(" << outputString << ")(63 downto 32)" << std::endl;
	} else {
		output << '\t' << '\t' << '\t' << '\t' << "output(REGFILE_WRITE_DATA) := input(" << outputString << ")" << std::endl;
	}
	output << '\t' << '\t' << '\t' << "} // when input is" << std::endl;
	output << '\t' << '\t' << "} // injectionStage plug newArea" << std::endl;
	} else { // two-cycles
	output << '\t' << '\t' << "execute plug new Area{" << std::endl;
	output << '\t' << '\t' << '\t' << "import execute._" << std::endl;
	for (auto const& pair : em_widths) {
		std::string regName = prefix + "_INTERMEDIATE_" + pair.first + "" + std::to_string(pair.second);
		output << '\t' << '\t' << '\t' << "insert(" << regName << ") := " << semantics[pair.first] << ".asBits" << std::endl;
	}
	output << '\t' << '\t' << "} // execute plug newArea" << std::endl;
	output << '\t' << '\t' << "memory plug new Area{" << std::endl;
	output << '\t' << '\t' << '\t' << "import memory._" << std::endl;
	// 2nd level MUXes
	for (const group* g : *groups) {
		if (g->opnames.size() > 1) {
		output << '\t' << '\t' << '\t' << "val val_" << g->name << " = input("<< ctrlString << g->name << ").mux(" << std::endl;
		for (auto it = g->opnames.begin() ; it != g->opnames.end() ; it++) {
			std::string opname = *it;
			std::string semantic = semantics[opname];
			std::string regName = prefix + "_INTERMEDIATE_" + opname + "" + std::to_string(em_widths[opname]);
			output << '\t' << '\t' << '\t' << '\t' << ctrlString << g->name << "Enum.CTRL_" << opname << " -> " << mem_semantics[opname] << "(input(" << regName << ")).asBits";
			if (std::next(it, 1) == g->opnames.end())
				output << std::endl;
			else
				output << "," << std::endl;
		}
		output << '\t' << '\t' << '\t' << ") // mux " << g->name << std::endl;
		}
	}
	// conditional last level mux
	output << '\t' << '\t' << '\t' << "when (arbitration.isValid && input(" << isString << ")) {" << std::endl;
	output << '\t' << '\t' << '\t' << '\t' << "output(REGFILE_WRITE_DATA) := input(" << ctrlString << ").mux(" << std::endl;
	for (auto it = groups->begin() ; it != groups->end() ; it++) {
		group* g = *it;
		if (g->opnames.size() > 1) {
			output << '\t' << '\t' << '\t' << '\t' <<'\t' << ctrlEnumString << "." << g->ctrlName() << " -> val_" << g->name << ".asBits";
		} else {
			std::string opname = *g->opnames.begin();
			std::string regName = prefix + "_INTERMEDIATE_" + opname + "" + std::to_string(em_widths[opname]);
			output << '\t' << '\t' << '\t' << '\t' << '\t' << ctrlEnumString << ".CTRL_" << opname << " -> " << mem_semantics[opname] << "(input(" << regName << ")).asBits(31 downto 0)";
		}
		if (std::next(it, 1) == groups->end())
			output << std::endl;
		else
			output << "," << std::endl;
	}
	output << '\t' << '\t' << '\t' << '\t' << ") // primary mux" << std::endl;
	if (wide) {
	output << '\t' << '\t' << '\t' << '\t' << "output(REGFILE_WRITE_DATA_ODD) := input(" << ctrlString << ").mux(" << std::endl;
	for (auto it = groups->begin() ; it != groups->end() ; it++) {
		group* g = *it;
		if (g->opnames.size() > 1) {
			output << '\t' << '\t' << '\t' << '\t' <<'\t' << ctrlEnumString << "." << g->ctrlName() << " -> val_" << g->name << ".asBits";
		} else {
			std::string opname = *g->opnames.begin();
			std::string regName = prefix + "_INTERMEDIATE_" + opname + "" + std::to_string(em_widths[opname]);
			output << '\t' << '\t' << '\t' << '\t' << '\t' << ctrlEnumString << ".CTRL_" << opname << " -> " << mem_semantics[opname] << "(input(" << regName << ")).asBits(63 downto 32)";
		}
		if (std::next(it, 1) == groups->end())
			output << std::endl;
		else
			output << "," << std::endl;
	}
	}
	output << '\t' << '\t' << '\t' << '\t' << ") // primary mux" << std::endl;
	output << '\t' << '\t' << '\t' << "} // when input is" << std::endl;
	output << '\t' << '\t' << "} // memory plug newArea" << std::endl;
	}
	output << '\t' << "} // override def build" << std::endl;
	output << "} // class Plugin" << std::endl;
}
