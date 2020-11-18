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

#include "unparse.hpp"

#include "gen_plugin.hpp"

#include <cstring>

// yucc
extern "C" {
#include "inst_par.h"
extern FILE *yyin, *yyout;
extern int yydebug;
}

std::set<const instruction*> instructions;
std::map<std::string, std::string> semantics;
std::vector<std::string> prologues;

void add_inst0(const char* name, const char* opname, const char* key, const char* group) {
	instruction* i = new instruction(name, opname, key, group);
	instructions.insert(i);
}
void add_inst1(const char* name, const char* opname, const char* key, const char* group, const char* e1) {
	instruction* i = new instruction(name, opname, key, group);
	i->addExt(e1);
	instructions.insert(i);
}
void add_inst2(const char* name, const char* opname, const char* key, const char* group, const char* e1, const char* e2) {
	instruction* i = new instruction(name, opname, key, group);
	i->addExt(e1);
	i->addExt(e2);
	instructions.insert(i);
}
void add_inst3(const char* name, const char* opname, const char* key, const char* group, const char* e1, const char* e2, const char *e3) {
	instruction* i = new instruction(name, opname, key, group);
	i->addExt(e1);
	i->addExt(e2);
	i->addExt(e3);
	instructions.insert(i);
}
void add_inst4(const char* name, const char* opname, const char* key, const char* group, const char* e1, const char* e2, const char *e3, const char *e4) {
	instruction* i = new instruction(name, opname, key, group);
	i->addExt(e1);
	i->addExt(e2);
	i->addExt(e3);
	i->addExt(e4);
	instructions.insert(i);
}
void add_sem(const char* name, const char* sem) {
	semantics[std::string(name)] = std::string(sem);
}
void add_prol(const char *prol) {
	prologues.push_back(std::string(prol));
}


int main(int argc, char **argv) {

// 	std::set<const instruction*> instructions;
// 	std::map<std::string, std::string> semantics;

// 	instruction* andn = new instruction("andn", "andn", "0100000----------111-----0110011", "bitwise", false);
// 	instruction* xnor = new instruction("xnor", "xnor", "0100000----------100-----0110011", "bitwise", false);

// 	instruction* ror  = new instruction("ror" , "ror" , "0110000----------101-----0110011", "rotation", false);
// 	instruction* rori = new instruction("rori", "ror" , "01100------------101-----0010011", "rotation", true);

// 	semantics["andn"] = "(input(SRC1) & ~input(SRC2)";
// 	semantics["xnor"] = "(input(SRC1) ^ ~input(SRC2)";
// 	semantics["ror"] = "input(SRC1).rotateRight((input(SRC2)&31)(4 downto 0).asUInt)";

// 	instructions.insert(andn);
// 	instructions.insert(xnor);
// 	instructions.insert(ror);
// 	instructions.insert(rori);

	if (argc > 2) {
		FILE *myfile;
		myfile = fopen(argv[2], "r");
		if (!myfile) {
			fprintf(stderr, "no file\n");
			return -1;
		}
		yyin = myfile;
		do {
			yyparse();
		} while (!feof(yyin));
		fclose(myfile);
	} else {
		std::cerr << "Should have a datafile as second argument" << std::endl;
		exit(-1);
	}
	
	
 	std::set<const instruction*> filtered_instructions;

	for (const instruction* inst : instructions) {
		if (inst->isWord())
			continue;
		if (semantics[inst->opname] == "")
			continue;
		bool addinst = false;
		for (int i = 3 ; i < argc; i++) {
			if (inst->match(argv[i]) || (strncmp(argv[i], "*", 1)==0)) {
// 				printf("%s is in %s\n", inst->name.c_str(), argv[i]);
				addinst = true;
			} else {
// 				printf("%s is NOT in %s\n", inst->name.c_str(), argv[i]);
			}
		}
		if (addinst)
			filtered_instructions.insert(inst);
		//printf("adding %s\n", inst->name.c_str());
	}

	unparse(std::cout, argv[1], filtered_instructions, semantics, prologues);

	return 0;
}
