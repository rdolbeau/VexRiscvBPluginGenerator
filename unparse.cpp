/*
 * Copyright (c) 2020 Romain Dolbeau <romain.dolbeau@european-processor-initiative.eu>
 * MIT License
 * See the LICENSE file at the top level of this software distribution for details.
 */

#include <iostream>
#include <set>
#include <map>
#include <vector>

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
	     std::vector<std::string> prologues,
	     std::vector<std::string> extras) {
	std::set<group*>* groups = createGroups(instructions);

	output << "// WARNING: this is auto-generated code!" << std::endl;
	output << "// See https://github.com/rdolbeau/VexRiscvBPluginGenerator/" << std::endl;
	output << "package vexriscv.plugin" << std::endl;
	output << "import spinal.core._" << std::endl;
	output << "import vexriscv.{Stageable, DecoderService, VexRiscv}" << std::endl;

	output << "object " << prefix << "Plugin {" << std::endl;

	// objects for second-level MUXes
	for (group* g : *groups) {
		if (g->opnames.size() > 1) {
		output << '\t' << "object " << prefix << "Ctrl" << g->name << "Enum extends SpinalEnum(binarySequential) {" << std::endl;
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
	output << '\t' << "object " << prefix << "Ctrl"  << "Enum extends SpinalEnum(binarySequential) {" << std::endl;
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
			output << '\t' << "object " << prefix << "Ctrl" << g->name << " extends Stageable(" << prefix << "Ctrl" << g->name << "Enum())" << std::endl;
	}
	output << '\t' << "object " << prefix << "Ctrl" << " extends Stageable(" << prefix << "Ctrl" << "Enum())" << std::endl;

	output << "// Prologue" << std::endl;
	for (std::string prologue : prologues)
	  output << prologue << std::endl;
	output << "// End prologue" << std::endl;

	output << "} // object Plugin" << std::endl;

	output << "class " << prefix << "Plugin extends Plugin[VexRiscv] {" << std::endl;
	output << '\t' << "import " << prefix << "Plugin._" << std::endl;
	output << '\t' << "object IS_" << prefix << " extends Stageable(Bool)" << std::endl;
	
	output << '\t' << "override def setup(pipeline: VexRiscv): Unit = {" << std::endl;
	output << '\t' << '\t' << "import pipeline.config._" << std::endl;
	
	// define standard actions
	output << '\t' << '\t' << "val immediateActions = List[(Stageable[_ <: BaseType],Any)](" << std::endl;
	output << '\t' << '\t' << "\tSRC1_CTRL                -> Src1CtrlEnum.RS," << std::endl;
	output << '\t' << '\t' << "\tSRC2_CTRL                -> Src2CtrlEnum.IMI," << std::endl;
	output << '\t' << '\t' << "\tREGFILE_WRITE_VALID      -> True," << std::endl;
	output << '\t' << '\t' << "\tBYPASSABLE_EXECUTE_STAGE -> True," << std::endl;
	output << '\t' << '\t' << "\tBYPASSABLE_MEMORY_STAGE  -> True," << std::endl;
	output << '\t' << '\t' << "\tRS1_USE -> True," << std::endl;
	output << '\t' << '\t' << "\tIS_" << prefix << " -> True" << std::endl;
	output << '\t' << '\t' << "\t)" << std::endl;
	
	output << '\t' << '\t' << "val binaryActions = List[(Stageable[_ <: BaseType],Any)](" << std::endl;
	output << '\t' << '\t' << "\tSRC1_CTRL                -> Src1CtrlEnum.RS," << std::endl;
	output << '\t' << '\t' << "\tSRC2_CTRL                -> Src2CtrlEnum.RS," << std::endl;
	output << '\t' << '\t' << "\tREGFILE_WRITE_VALID      -> True," << std::endl;
	output << '\t' << '\t' << "\tBYPASSABLE_EXECUTE_STAGE -> True," << std::endl;
	output << '\t' << '\t' << "\tBYPASSABLE_MEMORY_STAGE  -> True," << std::endl;
	output << '\t' << '\t' << "\tRS1_USE -> True," << std::endl;
	output << '\t' << '\t' << "\tRS2_USE -> True," << std::endl;
	output << '\t' << '\t' << "\tIS_" << prefix << " -> True" << std::endl;
	output << '\t' << '\t' << "\t)" << std::endl;
	
	output << '\t' << '\t' << "val unaryActions = List[(Stageable[_ <: BaseType],Any)](" << std::endl;
	output << '\t' << '\t' << "\tSRC1_CTRL                -> Src1CtrlEnum.RS," << std::endl;
	output << '\t' << '\t' << "\tREGFILE_WRITE_VALID      -> True," << std::endl;
	output << '\t' << '\t' << "\tBYPASSABLE_EXECUTE_STAGE -> True," << std::endl;
	output << '\t' << '\t' << "\tBYPASSABLE_MEMORY_STAGE  -> True," << std::endl;
	output << '\t' << '\t' << "\tRS1_USE -> True," << std::endl;
	output << '\t' << '\t' << "\tIS_" << prefix << " -> True" << std::endl;
	output << '\t' << '\t' << "\t)" << std::endl;

	// inst keys
	for (const instruction* inst : instructions) {
		output << '\t' << '\t' << "def " << inst->keyName() << " = M\"" << inst->key << "\"" << std::endl;
	}
	
	output << '\t' << '\t' << "val decoderService = pipeline.service(classOf[DecoderService])" << std::endl;
	output << '\t' << '\t' << "decoderService.addDefault(IS_" << prefix << ", False)" << std::endl;

	// add actions
	output << '\t' << '\t' << "decoderService.add(List(" << std::endl;
	//	for (const group* g : *groups) {
	for (auto it = groups->begin() ; it != groups->end() ; it++) {
		group* g = *it;
		for (auto it2 = g->instructions.begin() ; it2 != g->instructions.end() ; it2++) {
			const instruction* inst = *it2;
			std::string control;
			if (g->opnames.size() > 1)
				control = prefix + "Ctrl -> " + prefix + "CtrlEnum." + g->ctrlName() +  ", " + prefix + "Ctrl" + g->name + " -> " + prefix + "Ctrl" + g->name + "Enum.CTRL_" + inst->opname;
			else
				control = prefix + "Ctrl -> " + prefix + "CtrlEnum.CTRL_" + inst->opname;
			if (!inst->isImm()) {
				if (semantics[inst->opname].find("SRC2") != std::string::npos)
					output << '\t' << '\t' << "\t" << inst->keyName() << "\t-> (binaryActions ++ List("<< control << "))";
				else
					output << '\t' << '\t' << "\t" << inst->keyName() << "\t-> (unaryActions ++ List("<< control << "))";
			} else {
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
	
	output << '\t' << '\t' << "execute plug new Area{" << std::endl;
	output << '\t' << '\t' << '\t' << "import execute._" << std::endl;

	// 2nd level MUXes
	for (const group* g : *groups) {
		if (g->opnames.size() > 1) {
		output << '\t' << '\t' << '\t' << "val val_" << g->name << " = input("<< prefix << "Ctrl" << g->name << ").mux(" << std::endl;
		for (auto it = g->opnames.begin() ; it != g->opnames.end() ; it++) {
			std::string opname = *it;
			output << '\t' << '\t' << '\t' << '\t' << prefix << "Ctrl" << g->name << "Enum.CTRL_" << opname << " -> " << semantics[opname];
			if (std::next(it, 1) == g->opnames.end())
				output << std::endl;
			else
				output << "," << std::endl;
		}
		output << '\t' << '\t' << '\t' << ") // mux " << g->name << std::endl;
		}
	}

	// conditional last level mux
	output << '\t' << '\t' << '\t' << "when (input(IS_" << prefix << ")) {" << std::endl;
	output << '\t' << '\t' << '\t' << '\t' << "execute.output(REGFILE_WRITE_DATA) := input(" << prefix << "Ctrl" << ").mux(" << std::endl;
	for (auto it = groups->begin() ; it != groups->end() ; it++) {
		group* g = *it;
		if (g->opnames.size() > 1) {
			output << '\t' << '\t' << '\t' << '\t' << '\t' << prefix << "CtrlEnum." << g->ctrlName() << " -> val_" << g->name << ".asBits";
		} else {
			output << '\t' << '\t' << '\t' << '\t' << '\t' << prefix << "CtrlEnum.CTRL_" << (*g->opnames.begin()) << " -> " << semantics[*g->opnames.begin()] << ".asBits";
		}
		if (std::next(it, 1) == groups->end())
			output << std::endl;
		else
			output << "," << std::endl;
	}
	output << '\t' << '\t' << '\t' << '\t' << ") // primary mux " << std::endl;
	output << '\t' << '\t' << '\t' << "} // when input is " << std::endl;
	
	output << '\t' << '\t' << "} // execute plug newArea" << std::endl;
	output << '\t' << "} // override def build" << std::endl;
	output << "} // class Plugin" << std::endl;
}
