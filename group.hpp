/*
 * Copyright (c) 2020 Romain Dolbeau <romain.dolbeau@european-processor-initiative.eu>
 * MIT License
 * See the LICENSE file at the top level of this software distribution for details.
 */

#ifndef __GROUP_HPP__
#define __GROUP_HPP__

#include <set>
#include "inst.hpp"

class group {
public:
	const std::string name;
	std::set<const instruction*> instructions;
	std::set<std::string> opnames;

	group(std::string n) : name(n) {
	}

	void add(const instruction *inst) {
		instructions.insert(inst);
		opnames.insert(inst->opname);
	}
	bool match(const instruction *inst) {
		return inst->group.compare(name) == 0;
	}

	bool contains(const instruction *inst) {
		for (const instruction* check : instructions) {
			if (*check == *inst)
				return true;
		}
		return false;
	}

	bool operator ==(const group &b) const {
		return name.compare(b.name) == 0;
	}

	std::string ctrlName() const {
		return "CTRL_" + name;
	}
};
#endif // __GROUP_HPP__
