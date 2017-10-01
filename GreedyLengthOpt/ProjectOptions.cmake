include(PrecompiledHeader.cmake)

set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(CMAKE_SUPPRESS_REGENERATION TRUE)
set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELEASE "")
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "")

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

function(set_precompiled_header)
		if(MSVC)
			set(FILENAME "stdafx.h")
			set(SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/stdafx.cpp")
			set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/Yu\"${FILENAME}\" /DUSE_PRECOMPILED_HEADERS")
			set_source_files_properties(${SOURCE} PROPERTIES COMPILE_FLAGS "/Yc")
		elseif(MINGW)			
			add_precompiled_header(${PROJECT_NAME} stdafx.h FORCEINCLUDE)
		endif()
endfunction(set_precompiled_header)

function(set_source_non_precompiled_header filename)
		set_source_files_properties("${filename}" PROPERTIES COMPILE_FLAGS "/Y-")
endfunction(set_source_non_precompiled_header)

function(set_project_compile_flags)
		if(MSVC)
			set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_DEBUG "/INCREMENTAL /DEBUG:FASTLINK /SUBSYSTEM:WINDOWS /SAFESEH:NO")
			set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELEASE "/INCREMENTAL:NO /DEBUG /SUBSYSTEM:WINDOWS /SAFESEH:NO /MAP")
		elseif(MINGW)		
		endif()
endfunction(set_project_compile_flags)

function(set_project_compile_options_debugrelease)
	if(MSVC)
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
		target_compile_options(${PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:${COMPILEOPT_DEBUG}>)
		target_compile_options(${PROJECT_NAME} PUBLIC $<$<CONFIG:Release>:${COMPILEOPT_RELEASE}>)
	elseif(MINGW)	
	list(APPEND COMPILEOPT_DEBUG
			-g           	# Produce debugging symbols
			-mthreads
			-fmessage-length=0
			-fexceptions
			-fident
			-std=gnu++14
			-Wno-deprecated-declarations
		)
		list(APPEND COMPILEOPT_RELEASE
		    -O2
			-mthreads
			-fmessage-length=0
			-fexceptions
			-fident
			-std=gnu++14
			-Wno-deprecated-declarations
		)
		target_compile_options(${PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:${COMPILEOPT_DEBUG}>)
		target_compile_options(${PROJECT_NAME} PUBLIC $<$<CONFIG:Release>:${COMPILEOPT_RELEASE}>)
	endif()
endfunction(set_project_compile_options_debugrelease)

function(set_project_compile_options)
	if(MSVC)
		list(APPEND COMPILEOPT
			/Gy			  	# Enable function level linking
			/Yu			  	# Use preocompiled headers
			/FR			  	# Enable browse information
			/Zm800			# Precompiled header memory allocation limit
			/GR				# #Enable run type information
		)		
		target_compile_options(${PROJECT_NAME} PUBLIC  ${COMPILEOPT})	
	elseif(MINGW)	
	
	endif()
	set_project_compile_options_debugrelease()
endfunction(set_project_compile_options)

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
	target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:${COMPILER_DEFINES_DEBUG}>)
	target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:Release>:${COMPILER_DEFINES_RELEASE}>)
endfunction(set_project_processor_definitions)

function(set_project_definitions)
	add_definitions(-DUNICODE -D_UNICODE) #Unicode character set

	if(MSVC)
		add_definitions(/Zi)  #Program database
		add_definitions(/MP)  #Multi process compilation
	endif()
	
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
						RUNTIME_OUTPUT_NAME_DEBUG ${RuntimeOutputNameDebug}
						RUNTIME_OUTPUT_DIRECTORY_DEBUG "${RootDir}/bin")
					  
	set_target_properties(${PROJECT_NAME} PROPERTIES 
						RUNTIME_OUTPUT_NAME_RELEASE ${PROJECT_NAME}
						RUNTIME_OUTPUT_DIRECTORY_RELEASE "${RootDir}/bin")
endfunction(set_project_bin_properties)

function(set_project_bin_lib_properties LibDirPath)
	set_project_bin_properties("${RootDir}/bin")
	set(LibraryOutputNameDebug "${PROJECT_NAME}D")
	set(LibraryOutputNameRelease "${PROJECT_NAME}")
	
	set_target_properties(${PROJECT_NAME} PROPERTIES 
						ARCHIVE_OUTPUT_NAME_DEBUG ${LibraryOutputNameDebug}
						ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${LibDirPath})   #Import Library path
					  
	set_target_properties(${PROJECT_NAME} PROPERTIES 
						ARCHIVE_OUTPUT_NAME_RELEASE ${LibraryOutputNameRelease} 
						ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LibDirPath}) #Import Library path
endfunction(set_project_bin_lib_properties)
