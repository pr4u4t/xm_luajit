#ifndef __LUAJIT_H
#define __LUAJIT_H

#include <apr_lib.h>

#include <luajit-2.1/lua.h>
#include <luajit-2.1/lualib.h>
#include <luajit-2.1/lauxlib.h>

#include "../../../common/module.h"
#include "../../../common/error_debug.h"

#define LOG_DATA_MTBL   "LogData"
#define MODULE_MTBL     "Module"
#define LOG_FIELD_MTBL  "LogField"

#define VALUE_MTBL      "Value"

#define nx_luaL_newlib(L,T,S) (lua_createtable(L, 0, S), luaL_setfuncs(L,T,0))

#define NX_LOGMODULE NX_LOGMODULE_MODULE

typedef struct nx_lua_udata_t{
    void* data;
} nx_lua_udata_t;

extern luaL_Reg LogData_index_tbl[];

extern luaL_Reg ModuleCtx_index_tbl[];

extern luaL_Reg Field_index_tbl[];

#endif
