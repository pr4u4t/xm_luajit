/*
 * This file is part of the nxlog log collector tool.
 * See the file LICENSE in the source root for licensing terms.
 * Website: http://nxlog.org
 * Author: Paul pr4u4t Ciejka <pawel.ciejka@gmail.com>
 */

#include "xm_luajit.h"


static void nx_register_lua(lua_State* l, const char* name,luaL_Reg* metatbl,){
    luaL_newmetatable(xmconf->L, name); //MODULE_MTBL
    
    lua_pushstring(xmconf->L, "__index");
    lua_pushvalue(xmconf->L, -2); 
    lua_settable(xmconf->L, -3); 
    
    luaL_openlib(xmconf->L, NULL, metatbl, 0); //ModuleCtx_index_tbl
}

static void xm_luajit_config(nx_module_t *module){
    nx_xm_luajit_conf_t *xmconf;
    const nx_directive_t *curr;

    xmconf = apr_pcalloc(module->pool, sizeof(nx_xm_luajit_conf_t));
    module->config = xmconf;

    if(!(xmconf->fields = apr_table_make(module->pool,10))){
        throw_msg("failed to initialize configuration table");
    }

    for (curr = module->directives; curr != NULL; curr = curr->next){
        if ( nx_module_common_keyword(curr->directive) == TRUE ){
            continue;
        }

        if ( strcasecmp(curr->directive, "init_by_lua") == 0 ){
            if(xmconf->init_by_lua == NULL){
                xmconf->init_by_lua = apr_pstrdup(module->pool, curr->args);
                log_debug("init_by_lua: %s", xmconf->init_by_lua);
            }else{
                nx_conf_error(curr, "init_by_lua is already defined");
            }
            
            continue;
        }
        
        if ( strcasecmp(curr->directive, "start_by_lua") == 0 ){
            if(xmconf->start_by_lua == NULL){
                xmconf->start_by_lua = apr_pstrdup(module->pool, curr->args);
                log_debug("start_by_lua: %s", xmconf->start_by_lua);
            }else{
                nx_conf_error(curr, "start_by_lua is already defined");
            }
            
            continue;
        }
        
        if ( strcasecmp(curr->directive, "stop_by_lua") == 0 ){
            if(xmconf->stop_by_lua == NULL){
                xmconf->stop_by_lua = apr_pstrdup(module->pool, curr->args);
                log_debug("stop_by_lua: %s", xmconf->stop_by_lua);
            }else{
                nx_conf_error(curr, "init_by_lua is already defined");
            }
            continue;
        }
        
        if ( strcasecmp(curr->directive, "shutdown_by_lua") == 0 ){
            if(xmconf->shutdown_by_lua == NULL){
                xmconf->shutdown_by_lua = apr_pstrdup(module->pool, curr->args);
                log_debug("shutdown_by_lua: %s", modconf->shutdown_by_lua);
            }else{
                nx_conf_error(curr, "shutdown_by_lua is already defined");
            }
            continue;
        }
        
        if ( strcasecmp(curr->directive, "event_by_lua") == 0 ){
            if(xmconf->event_by_lua == NULL){
                xmconf->event_by_lua = apr_pstrdup(module->pool, curr->args);
                log_debug("event_by_lua: %s", modconf->event_by_lua);
            }else{
                nx_conf_error(curr, "event_by_lua is already defined");
            }
            continue;
        }
        
        apr_table_set(xmconf->fields,curr->directive,curr->args);

    }
}

static void  xm_luajit_init(nx_module_t *module){
    nx_xm_luajit_conf_t *xmconf;
    xmconf = (nx_xm_luajit_conf_t*) module->config;
    nx_lua_udata_t *umod;

    xmconf->L = luaL_newstate();

    log_debug("module init created new lua state %x",xmconf->L);

    luaL_openlibs(xmconf->L);

    nx_register_lua(xmconf->L, LOG_DATA_MTBL,LogData_index_tbl);

    nx_register_lua(xmconf->L, LOG_FIELD_MTBL,Field_index_tbl);

    nx_register_lua(xmconf->L, MODULE_MTBL,ModuleCtx_index_tbl);
    
    if(!(umod = lua_newuserdata(xmconf->L, sizeof(nx_lua_udata_t)))){
       throw_msg("failed to initalize lua nxlog connection");
    }

    umod->data = module;
    
    lua_setglobal(xmconf->L, "module");
    
    lua_getglobal(xmconf->L, "module");
    luaL_getmetatable(xmconf->L, MODULE_MTBL);
    lua_setmetatable(xmconf->L, -2);

    luaL_loadfile(xmconf->L, "data/script.lua");

    int error = lua_pcall(xmconf->L, 0, 1, 0);
    log_debug("PCALL: %d\r\n",error);
    //log_debug("%s",lua_gettop(xmconf->L));
    log_debug("%s",lua_tostring(xmconf->L, -1) );
    log_debug("lua script finished with: %d",0);
}

static void xm_laujit_start(nx_module_t *module){
    nx_xm_luajit_conf_t *xmconf;
    nx_event_t *event;

    ASSERT(module->config != NULL);

    xmconf = (nx_xm_luajit_conf_t *) module->config;
  
    ASSERT(xmconf->event == NULL);
    event = nx_event_new();
    event->module = module;
    event->delayed = FALSE;
    event->type = NX_EVENT_MODULE_SPECIFIC;
    event->priority = module->priority;
    nx_event_add(event);
    xmconf->event = event;
}



static void xm_luajit_stop(nx_module_t *module){
    nx_xm_luajit_conf_t *xmconf;

    ASSERT(module != NULL);
    ASSERT(module->config != NULL);
    xmconf = (nx_xm_luajit_conf_t *) module->config;

    if ( xmconf->event != NULL ){
        nx_event_remove(xmconf->event);
        nx_event_free(xmconf->event);
        xmconf->event = NULL;
    }
}


static void xm_luajit_event(nx_module_t *module, nx_event_t *event){
    nx_xm_luajit_conf_t *xmconf;
    ASSERT(event != NULL);
    ASSERT(module != NULL);
    ASSERT(module->config != NULL);
    
    xmconf = (nx_xm_luajit_conf_t *) module->config;
    
    
    
    //
    xmconf->event = NULL;
    //nx_panic("invalid event type: %d", event->type);
    
}

static void xm_luajit_shutdown(nx_module_t *module){

    nx_xm_luajit_conf_t *xmconf;
    xmconf = (nx_xm_luajit_conf_t*) module->config;

    log_debug("module shutdown closing lua state %x",xmconf->L);

    if(xmconf->L){
        lua_close(xmconf->L);
        xmconf->L = NULL;
    }
}

extern nx_module_exports_t nx_module_exports_xm_luajit;

NX_MODULE_DECLARATION nx_xm_luajit_module =
{
    NX_MODULE_API_VERSION,
    NX_MODULE_TYPE_EXTENSION,
    NULL,			        // capabilities
    xm_luajit_config,		// config
    xm_laujit_start,		// start
    xm_luajit_stop, 		// stop
    NULL,			        // pause
    NULL,			        // resume
    xm_luajit_init,		 	// init
    xm_luajit_shutdown,     // shutdown
    xm_luajit_event,	    // event
    NULL,                   // info
    &nx_module_exports_xm_luajit //exports
};
