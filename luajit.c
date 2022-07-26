#include "luajit.h"
#include "xm_luajit.h"

//extern nx_module_exports_t nx_module_exports_xm_luajit;


static int l_nx_logdata_append_field_value(lua_State *l){
    nx_lua_udata_t *ulog;
    const char *key;
    nx_lua_udata_t *uval;

    ulog = luaL_checkudata(l, 1, LOG_DATA_MTBL);
    luaL_argcheck(l, (ulog != NULL) && (ulog->data != NULL), 1, "valid nx_logdata_t expected");

    key = luaL_checkstring(l, 2);
    luaL_argcheck(l, key != NULL, 2 , "valid `string` expected");

    uval = luaL_checkudata(l, 3, VALUE_MTBL);
    luaL_argcheck(l, (uval != NULL) && (uval->data != NULL), 3, "valid `nx_value_t` expected");

    nx_logdata_append_field_value(ulog->data, key, uval->data);

    return TRUE;
}

static int l_nx_logdata_set_field_value(lua_State *l){
    const char *key;
    nx_lua_udata_t* uval;
    nx_lua_udata_t* ulog;

    ulog = luaL_checkudata(l, 1, LOG_DATA_MTBL);
    luaL_argcheck(l,(ulog != NULL) && (ulog->data != NULL), 1, "valid nx_logdata_t expected");

    key = luaL_checkstring(l, 2);
    luaL_argcheck(l, key != NULL, 2 , "valid `string` expected");

    uval = luaL_checkudata(l, 3, VALUE_MTBL);
    luaL_argcheck(l, (uval != NULL) && (uval->data != NULL) , 3, "valid `nx_value_t` expected");

    nx_logdata_set_field_value(ulog->data, key, uval->data);

    return TRUE;
}

static int l_nx_logdata_set_field(lua_State *l){
    nx_lua_udata_t *ufield;
    nx_lua_udata_t *ulog;

    ulog = luaL_checkudata(l, 1, LOG_DATA_MTBL);
    luaL_argcheck(l,(ulog != NULL) && (ulog->data != NULL), 1, "valid nx_logdata_t expected");

    ufield = luaL_checkudata(l, 2, LOG_FIELD_MTBL);
    luaL_argcheck(l, (ufield != NULL) && (ufield->data != NULL) , 3, "valid `nx_logdata_field_t` expected");

    nx_logdata_set_field(ulog->data, ufield->data);

    return TRUE;
}

static int l_nx_logdata_rename_field(lua_State *l){
    nx_lua_udata_t *ulog;
    const char *old;
    const char *new;

    ulog = luaL_checkudata(l, 1, LOG_DATA_MTBL);
    luaL_argcheck(l, (ulog != NULL) && (ulog->data != NULL), 1, "valid nx_logdata_t expected");

    old = luaL_checkstring(l, 2);
    luaL_argcheck(l, old != NULL, 2 , "valid `string` expected");

    new = luaL_checkstring(l, 3);
    luaL_argcheck(l, new != NULL, 3 , "valid `string` expected");

    nx_logdata_rename_field(ulog->data,old,new);

    return TRUE;
}

static int l_nx_logdata_get_field_value(lua_State *l){
    const char *key;
    nx_lua_udata_t *uval;
    nx_lua_udata_t *ulog;

    ulog = luaL_checkudata(l, 1, LOG_DATA_MTBL);
    luaL_argcheck(l,(ulog != NULL) && (ulog->data != NULL), 1, "valid nx_logdata_t expected");

    key = luaL_checkstring(l, 2);
    luaL_argcheck(l, key != NULL, 2 , "valid `string` expected");

    uval = luaL_checkudata(l, 1, LOG_DATA_MTBL);
    luaL_argcheck(l,(uval != NULL) && (uval->data != NULL), 1, "valid nx_value_t expected");

    lua_pushnumber(l, nx_logdata_get_field_value(ulog->data,key,uval->data));

    return TRUE;
}

static int l_nx_logdata_get_field(lua_State *l){
    const nx_logdata_t *logdata;
    const char *key;

    if(!(logdata = luaL_checkudata(l,1,LOG_DATA_MTBL))){
        return FALSE;
    }

    if(!(key = luaL_checkstring(l, 2))){
        return FALSE;
    }

    //nx_logdata_field_t *
    //push user data and metatable
    nx_logdata_get_field(logdata,key);

    return TRUE;
}

static int l_nx_logdata_delete_field(lua_State *l){
    nx_lua_udata_t *ulog;
    const char *key;

    ulog = luaL_checkudata(l, 1, LOG_DATA_MTBL);
    luaL_argcheck(l,(ulog != NULL) && (ulog->data != NULL), 1, "valid nx_logdata_t expected");

    key = luaL_checkstring(l, 2);
    luaL_argcheck(l, key != NULL, 2 , "valid `string` expected");

    lua_pushnumber(l, nx_logdata_delete_field(ulog->data,key));

    return TRUE;
}

static int l_nx_logdata_set_datetime(lua_State *l){
    nx_lua_udata_t *ulog;
    const char *key;
    apr_time_t datetime;

    ulog = luaL_checkudata(l, 1, LOG_DATA_MTBL);
    luaL_argcheck(l,(ulog != NULL) && (ulog->data != NULL), 1, "valid nx_logdata_t expected");

    key = luaL_checkstring(l, 2);
    luaL_argcheck(l, key != NULL, 2 , "valid `string` expected");

    datetime = luaL_checknumber(l, 3);
    luaL_argcheck(l, datetime != 0, 3 , "valid `string` expected");

    nx_logdata_set_datetime(ulog->data,key,datetime);

    return TRUE;
}

static int l_nx_logdata_set_string(lua_State *l){
    nx_lua_udata_t *ulog;
    const char *key;
    const char *value;

    ulog = luaL_checkudata(l, 1, LOG_DATA_MTBL);
    luaL_argcheck(l,(ulog != NULL) && (ulog->data != NULL), 1, "valid nx_logdata_t expected");

    key = luaL_checkstring(l, 2);
    luaL_argcheck(l, key != NULL, 2 , "valid `string` expected");

    value = luaL_checkstring(l, 3);
    luaL_argcheck(l, value != NULL, 3 , "valid `string` expected");

    nx_logdata_set_string(ulog->data,key,value);

    return TRUE;
}

static int l_nx_logdata_set_integer(lua_State *l){
    nx_lua_udata_t *ulog;
    const char *key;
    int64_t value;

    ulog = luaL_checkudata(l, 1, LOG_DATA_MTBL);
    luaL_argcheck(l,(ulog != NULL) && (ulog->data != NULL), 1, "valid nx_logdata_t expected");

    key = luaL_checkstring(l, 2);
    luaL_argcheck(l, key != NULL, 2 , "valid `string` expected");

    value = luaL_checknumber(l, 3);

    nx_logdata_set_integer(ulog->data,key,value);

    return TRUE;
}

static int l_nx_logdata_set_binary(lua_State *l){
    nx_lua_udata_t *ulog;
    const char *key;
    const char *value;
    unsigned int len;

    ulog = luaL_checkudata(l, 1, LOG_DATA_MTBL);
    luaL_argcheck(l,(ulog != NULL) && (ulog->data != NULL), 1, "valid nx_logdata_t expected");

    key = luaL_checkstring(l, 2);
    luaL_argcheck(l, key != NULL, 2 , "valid `string` expected");

    value = luaL_checkstring(l, 3);
    luaL_argcheck(l, value != NULL, 3 , "valid `string` expected");

    len = luaL_checknumber(l, 4);

    nx_logdata_set_binary(ulog->data,key,value,len);

    return TRUE;
}

static int l_nx_logdata_set_boolean(lua_State *l){
    nx_lua_udata_t *ulog;
    const char *key;
    int value;

    ulog = luaL_checkudata(l, 1, LOG_DATA_MTBL);
    luaL_argcheck(l,(ulog != NULL) && (ulog->data != NULL), 1, "valid nx_logdata_t expected");

    key = luaL_checkstring(l, 2);
    luaL_argcheck(l, key != NULL, 2 , "valid `string` expected");

    value = luaL_checknumber(l, 3);

    nx_logdata_set_boolean(ulog->data,key,value);

    return TRUE;
}

static int l_nx_logdata_dump_fields(lua_State *l){
    nx_lua_udata_t* ulog;

    ulog = luaL_checkudata(l, 1, LOG_DATA_MTBL);
    luaL_argcheck(l,(ulog != NULL) && (ulog->data != NULL), 1, "valid nx_logdata_t expected");

    nx_logdata_dump_fields(ulog->data);

    return TRUE;
}

static int l_nx_log_debug(lua_State *l){
    const char* msg;

    msg = luaL_checkstring(l, 2);
    luaL_argcheck(l, msg != NULL, 2 , "valid `string` expected");

    log_debug(msg);

    return TRUE;
}

static int l_nx_log_info(lua_State *l){
    const char* msg;

    msg = luaL_checkstring(l, 2);
    luaL_argcheck(l, msg != NULL, 2 , "valid `string` expected");

    log_info(msg);

    return TRUE;
}

static int l_nx_log_error(lua_State *l){
    const char* msg;

    msg = luaL_checkstring(l, 2);
    luaL_argcheck(l, msg != NULL, 2 , "valid `string` expected");

    log_error(msg);

    return TRUE;
}

static int l_nx_module_get_status(lua_State *l){
    nx_lua_udata_t *umod;

    umod = luaL_checkudata(l,1,MODULE_MTBL);
    luaL_argcheck(l, (umod != NULL) && (umod->data != NULL), 1, "valid nx_module_t expected");
    lua_pushnumber(l,nx_module_get_status(umod->data));

    return TRUE;
}

static int l_nx_module_get_config(lua_State *l){
    nx_lua_udata_t *umod;
    const char *key;

    umod = luaL_checkudata(l,1,MODULE_MTBL);
    luaL_argcheck(l, (umod != NULL) && (umod->data != NULL), 1, "valid nx_module_t expected");

    key = luaL_checkstring(l, 2);
    luaL_argcheck(l, key != NULL, 2 , "valid `string` expected");

    lua_pushstring(l,apr_table_get(((nx_xm_luajit_conf_t*)((nx_module_t*)umod->data)->config)->fields,
                                   key));

    return TRUE;
}

static int l_nx_logdata_new(lua_State *l){
    nx_lua_udata_t *udata;

    if(!(udata = lua_newuserdata(l, sizeof(nx_lua_udata_t)))){
        return FALSE;
    }

    if(!(udata->data = nx_logdata_new())){
        return FALSE;
    }

    luaL_getmetatable(l, LOG_DATA_MTBL);
    lua_setmetatable(l, -2);

    return TRUE;
}

static int l_nx_value_new(lua_State *l){
    nx_lua_udata_t *udata;
    nx_value_type_t type;

    if(!(udata = lua_newuserdata(l, sizeof(nx_lua_udata_t)))){
        return FALSE;
    }

    if(!(type = luaL_checknumber(l, 2))){
        return FALSE;
    }

    if(!(udata->data = nx_value_new(type))){
        return FALSE;
    }

    luaL_getmetatable(l, VALUE_MTBL);
    lua_setmetatable(l, -2);

    return TRUE;
}

static int l_nx_logdata_field_new(lua_State *l){
    nx_lua_udata_t *ufield;

    if(!(ufield = lua_newuserdata(l, sizeof(nx_lua_udata_t)))){
        return FALSE;
    }

    if(!(ufield->data = malloc(sizeof(nx_logdata_field_t)))){
        return FALSE;
    }

    luaL_getmetatable(l, LOG_FIELD_MTBL);
    lua_setmetatable(l, -2);

    return TRUE;
}

luaL_Reg LogData_index_tbl[] = {
    { "append_field_value",       l_nx_logdata_append_field_value         },
    { "set_field_value",          l_nx_logdata_set_field_value            },
    { "set_field",                l_nx_logdata_set_field                  },
    { "rename_field",             l_nx_logdata_rename_field               },
    { "get_field_value",          l_nx_logdata_get_field_value            },
    { "get_field",                l_nx_logdata_get_field                  },
    { "delete_field",             l_nx_logdata_delete_field               },
    { "set_datetime",             l_nx_logdata_set_datetime               },
    { "set_string",               l_nx_logdata_set_string                 },
    { "set_integer",              l_nx_logdata_set_integer                },
    { "set_binary",               l_nx_logdata_set_binary                 },
    { "set_boolean",              l_nx_logdata_set_boolean                },
    { "dump_fields",              l_nx_logdata_dump_fields                },
    { NULL,                       NULL                                    }
};

luaL_Reg ModuleCtx_index_tbl[] = {
    { "log_debug",       l_nx_log_debug         },
    { "log_info",        l_nx_log_info          },
    { "log_error",       l_nx_log_error         },
    { "get_status",      l_nx_module_get_status },
    { "logdata_new",     l_nx_logdata_new       },
    { "value_new",       l_nx_value_new         },
    { "field_new",       l_nx_logdata_field_new },
    { "get_config",      l_nx_module_get_config },
    { NULL }
};

luaL_Reg Field_index_tbl[] = {
    { NULL }
};
