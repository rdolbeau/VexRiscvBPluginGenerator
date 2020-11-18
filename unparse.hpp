/*
 * Copyright (c) 2020 Romain Dolbeau <romain.dolbeau@european-processor-initiative.eu>
 * MIT License
 * See the LICENSE file at the top level of this software distribution for details.
 */

#ifndef __UNPARSE_HPP__
#define __UNPARSE_HPP__

void unparse(std::ostream& output,
	     const std::string prefix,
	     const std::set<const instruction*> instructions,
	     std::map<std::string,std::string> semantics,
	     std::vector<std::string> prologues);

#endif // __UNPARSE_HPP__
