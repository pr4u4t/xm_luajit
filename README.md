NXLog lua(jit) extension
Designed as a 'game changer' of preparing input, output and extension modules.
Module exports `global module` variable that may be used to log from module, 
create new log data and manipulate it. Every module C function has its corresponding 
function in lua:
NXLog module C		   Lua equivalent
* xm_luajit_init 	-> init_by_lua
* xm_luajit_start	-> start_by_lua
* xm_luajit_stop	-> stop_by_lua
* xm_luajit_shutdown	-> shutdown_by_lua
* xm_luajit_event	-> event_by_lua

Specifying configuration directives like init_by_lua, start_by_lua and so on Lua scripts
could be attached to to module functions. This enables preparing modules in pure lua handling all
NXLog functionalities. 

