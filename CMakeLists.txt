# Copyright © 2015 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


cmake_minimum_required(VERSION 2.6)


# Release / Debug flags

	if (RELEASE STREQUAL "FALSE" OR RELEASE STREQUAL "DEBUG")
		set(RELEASE "FALSE")
	else()
		set(RELEASE "TRUE")
	endif()

	if (RELEASE)
		set(CMAKE_C_FLAGS "-O3 -DNDEBUG -march=native -ffast-math")
	else()
		set(CMAKE_C_FLAGS "-Og -g3")
	endif()

# General C flags
	# General
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -std=c11 -pedantic")
	# Thread support
	if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
	else()
		link_libraries(pthread)
		message(STATUS "Your compiler id \"${CMAKE_C_COMPILER_ID}\" is not GNU, OpenMP is disabled")
	endif()


# Get local directory where .cmake are
	set(FIND_PACKAGE_LOCAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# GMP
	message(STATUS "---")
	find_package(osl_gmp PATHS "${FIND_PACKAGE_LOCAL_PATH}" NO_DEFAULT_PATH)
	if (OSL_GMP_FOUND)
		add_definitions(-DOSL_GMP_IS_HERE)
	endif()

# OpenScop include/osl/scop.h
	configure_file("include/osl/scop.h.in" "include/osl/scop.h")
	include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")

# OpenScop
	message(STATUS "---")
	set(osl_INCLUDE "./include")
	message(STATUS "Include OpenScop = ${osl_INCLUDE}")
	include_directories("${osl_INCLUDE}")


# Build OpenScop doxygen
	message(STATUS "---")
	find_package(Doxygen)
	if (DOXYGEN_FOUND)
		message(STATUS "Doxygen found =) ${DOXYGEN_EXECUTABLE}")
		add_custom_target(
			doxygen
			${DOXYGEN_EXECUTABLE}
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include"
			COMMENT "Generating API documentation with Doxygen" VERBATIM
		)
	else()
		message(STATUS "Doxygen not found :(")
	endif()

# Build documentation
	find_program(texi2pdf_exe texi2pdf)
	if(texi2pdf_exe)
		add_custom_target(
			documentation
			${texi2pdf_exe} ${CMAKE_CURRENT_SOURCE_DIR}/doc/openscop.texi --output=${CMAKE_CURRENT_BINARY_DIR}/openscop.pdf
			WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
			COMMENT "Generating documentation (pdf) (with texi2pdf)" VERBATIM
		)
	else()
		message (STATUS "texi2pdf not found :(")
	endif()


# Compiler log
	message(STATUS "---")
	message(STATUS "C compiler = ${CMAKE_C_COMPILER}")
	if (RELEASE)
		message(STATUS "Release mode")
	else()
		message(STATUS "Debug mode")
	endif()
	message(STATUS "C flags    = ${CMAKE_C_FLAGS}")


# Library OpenScop
	
	file(
		GLOB_RECURSE
		osl_sources
		source/*
	)
	
	# Shared
	add_library(
		osl
		SHARED
		${osl_sources}
	)
	if (OSL_GMP_FOUND)
		target_link_libraries(osl ${OSL_GMP_LIBRARY})
	endif()
	message(STATUS "Add OpenScop library (shared)")
	
	# Static
	add_library(
		osl_static
		STATIC
		${osl_sources}
	)
	set_target_properties(osl_static PROPERTIES OUTPUT_NAME osl)
	if (OSL_GMP_FOUND)
		target_link_libraries(osl_static ${OSL_GMP_LIBRARY})
	endif()
	message(STATUS "Add OpenScop library (static)")


# Library OpenScop 1
	
	file(
		GLOB_RECURSE
		osl1_src
		src/osl1/*
	)
	
	# Shared
	add_library(
		osl1
		SHARED
		${osl1_src}
	)
	if (OSL_GMP_FOUND)
		target_link_libraries(osl1 ${OSL_GMP_LIBRARY})
	endif()
	message(STATUS "Add OpenScop 1 library (shared)")
	
	# Static
	add_library(
		osl1_static
		STATIC
		${osl1_src}
	)
	set_target_properties(osl1_static PROPERTIES OUTPUT_NAME osl1)
	if (OSL_GMP_FOUND)
		target_link_libraries(osl1_static ${OSL_GMP_LIBRARY})
	endif()
	message(STATUS "Add OpenScop 1 library (static)")


# Executables & tests
	
	enable_testing()
	message(STATUS "---")
	
	# Valgrind
	find_program(VALGRIND_EXE NAMES valgrind)
	
	# Tests
	file(
		GLOB_RECURSE
		tests
		tests/*.c
	)
	foreach(test_source ${tests})
	
		# Get test name and source
		string(REPLACE ".c" "" test_name ${test_source})
		string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/tests/osl1/" "test_osl1__" test_name ${test_name})
		string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/tests/" "test_osl__" test_name ${test_name})
		
		message(STATUS "Add test ${test_name}")
		
		# Executable
		add_executable(${test_name} "${test_source}")
		
		# OpenScop
		if ("${test_name}" MATCHES ".*test_osl_.*")
			
			target_link_libraries(${test_name} osl_static)
			
			# Test
			if (${test_name} STREQUAL "test__osl_test")
				foreach (scop ${scops})
					string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/tests/" "" scop_name ${scop})
					message(STATUS "- ${scop_name}")
					add_test("${test_name}__${scop_name}" "${test_name}" "${scop}")
				endforeach()
			else()
				add_test("${test_name}" "${test_name}")
			endif()
		
		# OpenScop 1
		else()
			
			target_link_libraries(${test_name} osl1_static)
		
			# Test
			if (VALGRIND_EXE)
				add_test(${test_name} "${VALGRIND_EXE}" "./${test_name}")
			else()
				add_test(${test_name} "./${test_name}")
			endif()
		
		endif()
		
	endforeach()


# Install
	# Library
	install(TARGETS osl LIBRARY DESTINATION lib)
	install(TARGETS osl_static ARCHIVE DESTINATION lib LIBRARY DESTINATION lib)
	install(TARGETS osl1 LIBRARY DESTINATION lib)
	install(TARGETS osl1_static ARCHIVE DESTINATION lib LIBRARY DESTINATION lib)
	# .h
	install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN "*.h")
	install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include/" DESTINATION include FILES_MATCHING PATTERN "*.h")
	# .cmake
	install(FILES cmake/osl-config.cmake DESTINATION lib/osl)
	install(FILES cmake/osl1-config.cmake DESTINATION lib/osl1)
	install(FILES cmake/osl_gmp-config.cmake DESTINATION lib/osl_gmp)
	# Doxygen
	if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc/doxygen)
		install(DIRECTORY doc/doxygen DESTINATION share/osl)
	endif()
	# Documentation
	if (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/openscop.pdf)
		install(FILES ${CMAKE_CURRENT_BINARY_DIR}/openscop.pdf DESTINATION share/osl)
	endif()


# Little help
	message(STATUS "---")
	message(STATUS "You can execute:")
	message(STATUS "    make               # To compile OpenScop tests")
	message(STATUS "    make test          # To execute tests")
	message(STATUS "    make install       # To install library, include and CMake module")
	message(STATUS "                       # If you need root access:")
	message(STATUS "                       #     sudo make install")
	message(STATUS "                       #     su -c \"make install\"")
	if (DOXYGEN_FOUND)
		message(STATUS "    make doxygen       # To generate the Doxygen")
	endif()
	if (texi2pdf_exe)
		message(STATUS "    make documentation # To generate the documentation")
	endif()

	message(STATUS "---")
