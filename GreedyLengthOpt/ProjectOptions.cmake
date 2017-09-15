set(CMAKE_CONFIGURATION_TYPES UnicodeDebug UnicodeRelease)
set(CMAKE_SUPPRESS_REGENERATION TRUE)
set(CMAKE_CXX_FLAGS_UNICODEDEBUG "")
set(CMAKE_CXX_FLAGS_UNICODERELEASE "")
set(CMAKE_SHARED_LINKER_FLAGS_UNICODEDEBUG "")
set(CMAKE_SHARED_LINKER_FLAGS_UNICODERELEASE "")

get_filename_component(RootDir "${CMAKE_CURRENT_LIST_DIR}" PATH)

function(include_dir relativePath)
	include_directories("${RootDir}/${relativePath}")
endfunction(include_dir)

function(link_dir relativePath)
	link_directories("${RootDir}/${relativePath}")
endfunction(link_dir)

function(include_root_dir)
	include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
endfunction(include_root_dir)

function(set_project_dll_mode LibDirPath)
	file(GLOB_RECURSE sources "*.cpp" "*.h" "*.c" "*.rc" "*.bmp" "*.cur" "*ico")
	set(root ${CMAKE_CURRENT_SOURCE_DIR})
	source_group(TREE ${root} FILES ${sources})
	list(REMOVE_ITEM sources "${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/${CMAKE_VERSION}/CompilerIdCXX/CMakeCXXCompilerId.cpp")
	list(REMOVE_ITEM sources "${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/${CMAKE_VERSION}/CompilerIdC/CMakeCCompilerId.c")
	source_group("" FILES ${sources})
	add_library	(${PROJECT_NAME} SHARED ${sources})
	include_root_dir()
	set_project_bin_lib_properties("${LibDirPath}")
	set_project_compile_options()
	set_project_definitions()
	set_project_compile_flags()
	set_project_processor_definitions()
	set_precompiled_header()
endfunction(set_project_dll_mode)

function(set_project_dll_mode_nobrowser LibDirPath)
	file(GLOB_RECURSE sources "*.cpp" "*.h" "*.c" "*.rc" "*.bmp" "*.cur" "*ico")
	set(root ${CMAKE_CURRENT_SOURCE_DIR})
	source_group(TREE ${root} FILES ${sources})
	list(REMOVE_ITEM sources "${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/${CMAKE_VERSION}/CompilerIdCXX/CMakeCXXCompilerId.cpp")
	list(REMOVE_ITEM sources "${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/${CMAKE_VERSION}/CompilerIdC/CMakeCCompilerId.c")
	source_group("" FILES ${sources})
	add_library	(${PROJECT_NAME} SHARED ${sources})
	include_root_dir()
	set_project_bin_lib_properties("${LibDirPath}")
	set_project_compile_options_nobrowserinfo()
	set_project_definitions()
	set_project_compile_flags()
	set_project_processor_definitions()
	set_precompiled_header()
endfunction(set_project_dll_mode_nobrowser)

function(set_project_lib_mode)
	file(GLOB_RECURSE sources "*.cpp" "*.h" "*.c" "*.rc" "*.bmp" "*.cur" "*ico")
	set(root ${CMAKE_CURRENT_SOURCE_DIR})
	source_group(TREE ${root} FILES ${sources})
	list(REMOVE_ITEM sources "${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/${CMAKE_VERSION}/CompilerIdCXX/CMakeCXXCompilerId.cpp")
	list(REMOVE_ITEM sources "${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/${CMAKE_VERSION}/CompilerIdC/CMakeCCompilerId.c")
	source_group("" FILES ${sources})
	add_library	(${PROJECT_NAME} ${sources})
	include_root_dir()
	set_project_definitions()
	set_project_compile_flags()
	set_project_processor_definitions()
endfunction(set_project_lib_mode)

function(set_project_exe_mode)
	file(GLOB_RECURSE sources "*.cpp" "*.h" "*.c" "*.rc" "*.bmp" "*.cur" "*ico")
	set(root ${CMAKE_CURRENT_SOURCE_DIR})
	source_group(TREE ${root} FILES ${sources})
	list(REMOVE_ITEM sources "${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/${CMAKE_VERSION}/CompilerIdCXX/CMakeCXXCompilerId.cpp")
	list(REMOVE_ITEM sources "${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/${CMAKE_VERSION}/CompilerIdC/CMakeCCompilerId.c")
	source_group("" FILES ${sources})
	add_executable(${PROJECT_NAME} ${sources})
	include_root_dir()
	set_project_compile_options()
	set_project_definitions()
	set_project_compile_flags()
	set_project_processor_definitions()
	set_precompiled_header()
endfunction(set_project_exe_mode)

function(set_project_exe_mode_nobrowser)
	file(GLOB_RECURSE sources "*.cpp" "*.h" "*.c" "*.rc" "*.bmp" "*.cur" "*ico")
	set(root ${CMAKE_CURRENT_SOURCE_DIR})
	source_group(TREE ${root} FILES ${sources})
	list(REMOVE_ITEM sources "${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/${CMAKE_VERSION}/CompilerIdCXX/CMakeCXXCompilerId.cpp")
	list(REMOVE_ITEM sources "${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/${CMAKE_VERSION}/CompilerIdC/CMakeCCompilerId.c")
	source_group("" FILES ${sources})
	add_executable(${PROJECT_NAME} ${sources})
	include_root_dir()
	set_project_compile_options_nobrowserinfo()
	set_project_definitions()
	set_project_compile_flags()
	set_project_processor_definitions()
	set_precompiled_header()
endfunction(set_project_exe_mode_nobrowser)

function(set_precompiled_header)
		set(FILENAME "stdafx.h")
		set(SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/stdafx.cpp")
        set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/Yu\"${FILENAME}\" /DUSE_PRECOMPILED_HEADERS")
        set_source_files_properties(${SOURCE} PROPERTIES COMPILE_FLAGS "/Yc")
endfunction(set_precompiled_header)

function(set_source_non_precompiled_header filename)
		set_source_files_properties("${filename}" PROPERTIES COMPILE_FLAGS "/Y-")
endfunction(set_source_non_precompiled_header)

function(set_project_compile_flags)
		set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_UNICODEDEBUG "/INCREMENTAL /DEBUG:FASTLINK /SUBSYSTEM:WINDOWS /SAFESEH:NO")
		set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_UNICODERELEASE "/INCREMENTAL:NO /DEBUG /SUBSYSTEM:WINDOWS /SAFESEH:NO /MAP")
endfunction(set_project_compile_flags)

function(set_project_compile_options_debugrelease)
	list(APPEND COMPILEOPT_DEBUG
		/Od           	# Enable basic run-time checks
		/MDd		  	# Multithreaded debug runtime
	)

	list(APPEND COMPILEOPT_RELEASE
		/O2           	# Optimize for maximum speed
		/MD           	# Multithreaded release runtime
		/Ob1		  	# Inline function expansion
		/GF			  	# Enable string pooling
	)
	
	target_compile_options(${PROJECT_NAME} PUBLIC $<$<CONFIG:UnicodeDebug>:${COMPILEOPT_DEBUG}>)
	target_compile_options(${PROJECT_NAME} PUBLIC $<$<CONFIG:UnicodeRelease>:${COMPILEOPT_RELEASE}>)
endfunction(set_project_compile_options_debugrelease)

function(set_project_compile_options)
	list(APPEND COMPILEOPT
		/Gy			  	# Enable function level linking
		/Yu			  	# Use preocompiled headers
		/FR			  	# Enable browse information
		/Zm800			# Precompiled header memory allocation limit
		/GR				# #Enable run type information
	)
	
	target_compile_options(${PROJECT_NAME} PUBLIC  ${COMPILEOPT})	
	set_project_compile_options_debugrelease()
endfunction(set_project_compile_options)

#Browser infromation is disabled for some projects because of warnings:
#warning BK4504: file vector(179) contains too many references; ignoring further references from this source
#warning BK4503: minor error in .SBR file
function(set_project_compile_options_nobrowserinfo)
	list(APPEND COMPILEOPT
		/Gy			  	# Enable function level linking
		/Yu			  	# Use preocompiled headers
		/Zm800			# Precompiled header memory allocation limit
		/GR				# #Enable run type information
	)
	target_compile_options(${PROJECT_NAME} PUBLIC  ${COMPILEOPT})		
	set_project_compile_options_debugrelease()
endfunction(set_project_compile_options_nobrowserinfo)

function(set_project_processor_definitions)
	list (APPEND COMPILER_DEFINES
		_WINDOWS
	)

	list(APPEND COMPILER_DEFINES_DEBUG
		_DEBUG                    	
	)

	list(APPEND COMPILER_DEFINES_RELEASE
		NDEBUG                  
	)
	
	target_compile_definitions(${PROJECT_NAME} PUBLIC  ${COMPILER_DEFINES})
	target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:UnicodeDebug>:${COMPILER_DEFINES_DEBUG}>)
	target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:UnicodeRelease>:${COMPILER_DEFINES_RELEASE}>)
endfunction(set_project_processor_definitions)

function(set_project_definitions)
	#Unicode character set
	add_definitions(-DUNICODE -D_UNICODE)

	#Program database
	add_definitions(/Zi)

	#Multi process compilation
	add_definitions(/MP)
	
	#64bit define
	IF( "${CMAKE_SIZEOF_VOID_P}" STREQUAL "8" )
		IF( ${WIN32} ) 
			add_definitions(-D_WIN64)
		ENDIF()
		add_definitions(-D__x86_64__)
	ENDIF()
		
endfunction(set_project_definitions)

function(set_project_bin_properties)
	set(RuntimeOutputNameDebug "${PROJECT_NAME}D")
	
	set_target_properties(${PROJECT_NAME} PROPERTIES 
						RUNTIME_OUTPUT_NAME_UNICODEDEBUG ${RuntimeOutputNameDebug}
						RUNTIME_OUTPUT_DIRECTORY_UNICODEDEBUG "${RootDir}/bin")
					  
	set_target_properties(${PROJECT_NAME} PROPERTIES 
						RUNTIME_OUTPUT_NAME_UNICODERELEASE ${PROJECT_NAME}
						RUNTIME_OUTPUT_DIRECTORY_UNICODERELEASE "${RootDir}/bin")
endfunction(set_project_bin_properties)

function(set_project_bin_lib_properties LibDirPath)
	set_project_bin_properties("${RootDir}/bin")
	set(LibraryOutputNameDebug "${PROJECT_NAME}D")
	set(LibraryOutputNameRelease "${PROJECT_NAME}")
	
	set_target_properties(${PROJECT_NAME} PROPERTIES 
						ARCHIVE_OUTPUT_NAME_UNICODEDEBUG ${LibraryOutputNameDebug}
						ARCHIVE_OUTPUT_DIRECTORY_UNICODEDEBUG ${LibDirPath})   #Import Library path
					  
	set_target_properties(${PROJECT_NAME} PROPERTIES 
						ARCHIVE_OUTPUT_NAME_UNICODERELEASE ${LibraryOutputNameRelease} 
						ARCHIVE_OUTPUT_DIRECTORY_UNICODERELEASE ${LibDirPath}) #Import Library path
endfunction(set_project_bin_lib_properties)
