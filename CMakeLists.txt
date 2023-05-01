cmake_minimum_required(VERSION 3.13)

project(default_arm7 LANGUAGES C CXX ASM)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${NDS_ROOT}" CACHE PATH "" FORCE)
endif()

option(ENABLE_LOG    "Enable relaying debug messages to ARM9")
option(ENABLE_BLKDEV "Enable DLDI & DSi SD/eMMC driver")
option(ENABLE_WLMGR  "Enable wireless driver")
option(ENABLE_SOUND  "Enable basic sound driver")
option(ENABLE_MAXMOD "Enable Maxmod")

add_executable(${PROJECT_NAME})

if(CATNIP_PRESET)
	set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "ds7_${CATNIP_PRESET}")
endif()

dkp_target_generate_symbol_list(${PROJECT_NAME})

target_compile_options(${PROJECT_NAME} PRIVATE
	-Wall
)

target_link_options(${PROJECT_NAME} PRIVATE
	-Wl,--section-start,.main=0x02ff0000
)

target_sources(${PROJECT_NAME} PRIVATE
	arm7_main.c
)

if(ENABLE_LOG)
	target_compile_definitions(${PROJECT_NAME} PRIVATE ENABLE_LOG)
endif()

if(ENABLE_BLKDEV)
	target_compile_definitions(${PROJECT_NAME} PRIVATE ENABLE_BLKDEV)
endif()

if(ENABLE_WLMGR)
	target_compile_definitions(${PROJECT_NAME} PRIVATE ENABLE_WLMGR)
endif()

if(ENABLE_SOUND)
	target_compile_definitions(${PROJECT_NAME} PRIVATE ENABLE_SOUND)
endif()

if(ENABLE_MAXMOD)
	if(NOT ENABLE_SOUND)
		message(FATAL_ERROR "ENABLE_SOUND is required for ENABLE_MAXMOD")
	endif()

	target_compile_definitions(${PROJECT_NAME} PRIVATE ENABLE_MAXMOD)
	target_link_libraries(${PROJECT_NAME} PRIVATE mm7)
endif()

include(GNUInstallDirs)
install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
