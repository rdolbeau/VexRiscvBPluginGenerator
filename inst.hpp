/*
 * Copyright (c) 2020 Romain Dolbeau <romain.dolbeau@european-processor-initiative.eu>
 * MIT License
 * See the LICENSE file at the top level of this software distribution for details.
 */

#ifndef __INST_HPP__
#define __INST_HPP__

#include <string>
#include <set>


class instruction {
public:
	const std::string name;
	const std::string opname;
	const std::string key;
	const std::string group;
	std::set<std::string> extensions;

public:
	instruction(std::string n,
		    std::string o,
		    std::string k,
		    std::string g
		    ) : name(n), opname(o), key(k), group(g) {
	}

	void addExt(std::string e) {
		extensions.insert(e);
	}

	bool operator ==(const instruction &b) const {
		return name.compare(b.name) == 0;
	}

	bool match(const std::string toadd) const {
		if (toadd.compare(name) == 0)
			return true;
		for (const std::string extension : extensions)
			if (toadd.compare(extension) == 0)
				return true;
		
		return false;
	}
	
	bool isWord(void) const {
		return name[name.length()-1] == 'W';
	}
	
	bool isImm(void) const {
		if (isWord())
			return name[name.length()-2] == 'I';
		else
			return name[name.length()-1] == 'I';
	}
	
	std::string ctrlName() const {
		return "CTRL_" + group + "_" + opname;
	}
	std::string keyName() const {
		return name + "_KEY";
	}
};

#endif // __INST_HPP__
