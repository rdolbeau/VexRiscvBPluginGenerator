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

#include <unistd.h>

// yucc
extern "C" {
#include "inst_par.h"
extern FILE *yyin, *yyout;
extern int yydebug;
}

std::set<const instruction*> instructions;
std::map<std::string, std::string> semantics;
std::vector<std::string> prologues;
std::vector<std::string> extras;

void add_inst0(const char* name, const char* opname, const char* key, const char* group) {
	if (strlen(key) != 32) { fprintf(stderr, "For %s / %s: %s isn't 32 characters long\n", name, opname, key); }
	instruction* i = new instruction(name, opname, key, group);
	instructions.insert(i);
}
void add_inst1(const char* name, const char* opname, const char* key, const char* group, const char* e1) {
	if (strlen(key) != 32) { fprintf(stderr, "For %s / %s: %s isn't 32 characters long\n", name, opname, key); }
	instruction* i = new instruction(name, opname, key, group);
	i->addExt(e1);
	instructions.insert(i);
}
void add_inst2(const char* name, const char* opname, const char* key, const char* group, const char* e1, const char* e2) {
	if (strlen(key) != 32) { fprintf(stderr, "For %s / %s: %s isn't 32 characters long\n", name, opname, key); }
	instruction* i = new instruction(name, opname, key, group);
	i->addExt(e1);
	i->addExt(e2);
	instructions.insert(i);
}
void add_inst3(const char* name, const char* opname, const char* key, const char* group, const char* e1, const char* e2, const char *e3) {
	if (strlen(key) != 32) { fprintf(stderr, "For %s / %s: %s isn't 32 characters long\n", name, opname, key); }
	instruction* i = new instruction(name, opname, key, group);
	i->addExt(e1);
	i->addExt(e2);
	i->addExt(e3);
	instructions.insert(i);
}
void add_inst4(const char* name, const char* opname, const char* key, const char* group, const char* e1, const char* e2, const char *e3, const char *e4) {
	if (strlen(key) != 32) { fprintf(stderr, "For %s / %s: %s isn't 32 characters long\n", name, opname, key); }
	instruction* i = new instruction(name, opname, key, group);
	i->addExt(e1);
	i->addExt(e2);
	i->addExt(e3);
	i->addExt(e4);
	instructions.insert(i);
}
void add_inst5(const char* name, const char* opname, const char* key, const char* group, const char* e1, const char* e2, const char *e3, const char *e4, const char *e5) {
	if (strlen(key) != 32) { fprintf(stderr, "For %s / %s: %s isn't 32 characters long\n", name, opname, key); }
	instruction* i = new instruction(name, opname, key, group);
	i->addExt(e1);
	i->addExt(e2);
	i->addExt(e3);
	i->addExt(e4);
	i->addExt(e5);
	instructions.insert(i);
}
void add_sem(const char* name, const char* sem) {
	semantics[std::string(name)] = std::string(sem);
}
void add_prol(const char *prol) {
	prologues.push_back(std::string(prol));
}
void add_extra(const char *extra) {
	extras.push_back(std::string(extra));
}


int main(int argc, char **argv) {
	int c, done = 0, wide = 0;
	extern char *optarg;
	extern int optind, optopt;
	FILE *myfile;
	char *pluginName = NULL;
#define MAX_INSTS 1024
	char* insts[MAX_INSTS];
	int instidx = 0;

	while ((c = getopt(argc, argv, "n:i:I:w")) != -1) {
		switch(c) {
		default:
			fprintf(stderr, "usage: %s [-w] -n <plugin_name> -i <input_file> -I <instructions> \n", argv[0]);
			break;
		case 'i':
			myfile = fopen(optarg, "r");
			if (!myfile) {
				fprintf(stderr, "no file\n");
				return -1;
			}
			yyin = myfile;
			do {
			  yyparse();
			} while (!feof(yyin));
			fclose(myfile);
			done = 1;
			break;
		case 'n':
			pluginName = strndup(optarg, 512);
			break;
		case 'I':
			if (instidx < MAX_INSTS) {
				insts[instidx] = strndup(optarg, 512);
				instidx ++;
			}
			break;
		case 'w':
			wide = 1;
			break;
		}
	}
	if (!done || !pluginName || (instidx == 0)) {
		std::cerr << "Should have at least a plugin name & a datafile & some instructions enabled" << std::endl;
		exit(-1);
	}
	
 	std::set<const instruction*> filtered_instructions;

	for (const instruction* inst : instructions) {
		// if (inst->isWord())
		// 	continue;
		if (semantics[inst->opname] == "")
			continue;
		bool addinst = false;
		for (int i = 0 ; i < instidx; i++) {
			if (inst->match(insts[i]) || (strncmp(insts[i], "*", 1)==0)) {
// 				printf("%s is in %s\n", inst->name.c_str(), insts[i]);
				addinst = true;
			} else {
// 				printf("%s is NOT in %s\n", inst->name.c_str(), insts[i]);
			}
		}
		if (addinst)
			filtered_instructions.insert(inst);
		//printf("adding %s\n", inst->name.c_str());
	}

	unparse(std::cout, pluginName, filtered_instructions, semantics, prologues, extras, wide == 1);

	return 0;
}
