add_library(luajit STATIC
			luajit.c
)

add_library(xm_luajit MODULE
	expr-xm_luajit-funcproc.c
	xm_luajit.c
	xm_luajit_funcproc_cb.c
)

target_compile_options(luajit PUBLIC ${APR_INCLUDES})
target_compile_options(xm_luajit PUBLIC ${APR_INCLUDES})
target_link_libraries(xm_luajit PUBLIC nx)
target_link_libraries(xm_luajit PUBLIC luajit)
target_link_libraries(xm_luajit PUBLIC ${LIBLJ})

target_compile_options(xm_luajit PUBLIC -DDLL_EXPORT)

target_include_directories(xm_luajit PUBLIC ${CMAKE_SOURCE_DIR}/src/common)
target_include_directories(luajit PUBLIC ${CMAKE_SOURCE_DIR}/src/common)

add_custom_command(OUTPUT expr-xm_luajit-funcproc.c
				   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMAND ${CMAKE_SOURCE_DIR}/src/utils/codegen.pl ${CMAKE_CURRENT_SOURCE_DIR}/xm_luajit-api.xml ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS xm_luajit  DESTINATION ""
						 RUNTIME DESTINATION ""
						 LIBRARY DESTINATION "modules/extension"
						 ARCHIVE DESTINATION "lib"
)
