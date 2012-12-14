cmake_minimum_required(VERSION 2.6)


set(PACKAGE_VERSION "0.8.4")
set(top_srcdir "${CMAKE_CURRENT_SOURCE_DIR}")


# User's settings - C Flags

# 	set(release "TRUE")
	set(release "FALSE")

	# Release
	if (release)
		set(CMAKE_C_FLAGS "-O3")
	# Debug # valgrind --show-reachable=yes --leak-check=full -v exe
	else()
		set(CMAKE_C_FLAGS "-O0 -g3")
	endif()

# User's settings - General C Flags
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -std=c99")


# Build doxygen
	find_package(Doxygen)
	if(DOXYGEN_FOUND)
		configure_file("doc/Doxyfile.in" "Doxyfile")
		add_custom_target(
			doc
			${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
			WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
			COMMENT "Generating API documentation with Doxygen" VERBATIM
		)
	endif()


# GMP
	message(STATUS "---")
	find_library(gmp_LIB gmp)
	if (gmp_LIB)
		message (STATUS "Library gmp found =) ${gmp_LIB}")
	else()
		message(FATAL_ERROR "Library gmp not found :(")
	endif()

# files .c
	file(
		GLOB_RECURSE
		sources
		source/*
	)

# Include directories (to use #include <> instead of #include "")

	# include/osl/scop.h
	configure_file("include/osl/scop.h.in" "include/osl/scop.h")
	include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")
	# osl
	set(osl_INCLUDE "./include")
	message(STATUS "Include osl = ${osl_INCLUDE}")
	include_directories("${osl_INCLUDE}")


# Compiler log
	message(STATUS "---")
	message(STATUS "C compiler = ${CMAKE_C_COMPILER}")
	if (release)
		message(STATUS "Mode Release")
	else()
		message(STATUS "Mode Debug")
	endif()
	message(STATUS "C flags    = ${CMAKE_C_FLAGS}")


# Library
	add_library(
		osl
		SHARED
		${sources}
	)
	target_link_libraries(osl ${gmp_LIB})
	get_property(osl_lib_location TARGET osl PROPERTY LOCATION)


# Executables & tests

	enable_testing()

	message(STATUS "---") # osl_test

	set(exe "osl_test")
	message(STATUS "Add executable tests/${exe}")
	add_executable(${exe} "tests/${exe}.c")
	target_link_libraries(${exe} ${osl_lib_location})
	add_test(${exe} "${exe}")

	message(STATUS "---")


# Install

	install(TARGETS osl LIBRARY DESTINATION lib)
	install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN "*.h")
	install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include/" DESTINATION include FILES_MATCHING PATTERN "*.h")
	install(FILES osl-config.cmake DESTINATION lib/osl)


# Little help

	message(STATUS "You can execute:")
	message(STATUS "    make         # To compile osl library")
	message(STATUS "    make test    # To execute tests")
	message(STATUS "    make install # To install library, include and CMake module")
	message(STATUS "                 # If you need root access:")
	message(STATUS "                 #     sudo make install")
	message(STATUS "                 #     su -c \"make install\"")
	message(STATUS "    make doc     # To generate the Doxygen")

	message(STATUS "---")
