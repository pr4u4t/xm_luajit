/*
 * This file is part of the nxlog log collector tool.
 * See the file LICENSE in the source root for licensing terms.
 * Website: http://nxlog.org
 * Author: Paul pr4u4t Ciejka <pawel.ciejka@gmail.com>
 */

#ifndef __NX_XM_LUAJIT_H
#define __NX_XM_LUAJIT_H

#include "luajit.h"

typedef struct nx_xm_luajit_conf_t{
    nx_event_t *event;
    lua_State*  L;
    apr_table_t *fields;
    const char *init_by_lua;
    const char *start_by_lua;
    const char *stop_by_lua;
    const char *shutdown_by_lua;
    const char *event_by_lua;
} nx_xm_luajit_conf_t;

#endif	/* __NX_XM_LUAJIT_H */
