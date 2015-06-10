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


# Try to find the OpenScop library

# OSL_FOUND       - System has OpenScop library
# OSL_INCLUDE_DIR - The OpenScop include directory
# OSL_LIBRARY     - Library needed to use OpenScop


find_library(OSL_LIBRARY osl)
find_file(OSL_INCLUDE_DIR "osl/osl.h")

if (OSL_LIBRARY AND OSL_INCLUDE_DIR)
	
	string(REPLACE "/osl/osl.h" "" OSL_INCLUDE_DIR ${OSL_INCLUDE_DIR})
	
	set(OSL_FOUND "TRUE")
	
	include_directories(${OSL_INCLUDE_DIR})
	
	message(STATUS "Library OpenScop found =) ${OSL_INCLUDE_DIR} | ${OSL_LIBRARY}")
	
else()
	
	set(OSL_FOUND "FALSE")
	
	message(STATUS "Library OpenScop not found :(")
	
endif()

find_package(osl_gmp)
