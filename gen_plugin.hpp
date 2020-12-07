/*
 * Copyright (c) 2020 Romain Dolbeau <romain.dolbeau@european-processor-initiative.eu>
 * MIT License
 * See the LICENSE file at the top level of this software distribution for details.
 */

#ifndef __GEN_PLUGIN_HP__
#define __GEN_PLUGIN_HP__

#ifdef __cplusplus
extern "C" {
#endif
	void add_inst0(const char* name, const char* opname, const char* key, const char* group);
	void add_inst1(const char* name, const char* opname, const char* key, const char* group, const char* e1);
	void add_inst2(const char* name, const char* opname, const char* key, const char* group, const char* e1, const char* e2);
	void add_inst3(const char* name, const char* opname, const char* key, const char* group, const char* e1, const char* e2, const char *e3);
	void add_inst4(const char* name, const char* opname, const char* key, const char* group, const char* e1, const char* e2, const char *e3, const char *e4);      
	void add_inst5(const char* name, const char* opname, const char* key, const char* group, const char* e1, const char* e2, const char *e3, const char *e4, const char *e5);
	void add_sem(const char* name, const char* sem);
	void add_prol(const char *prol);
	void add_extra(const char *extra);
#ifdef __cplusplus
}
#endif

#endif // __GEN_PLUGIN_HP__
