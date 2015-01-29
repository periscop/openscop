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

# OSL1_FOUND       - System has OpenScop 1 library
# OSL1_INCLUDE_DIR - The OpenScop 1 include directory
# OSL1_LIBRARY     - Library needed to use OpenScop 1


find_library(OSL1_LIBRARY osl1)
find_file(OSL1_INCLUDE_DIR "osl1/osl.h")

if (OSL1_LIBRARY AND OSL1_INCLUDE_DIR)
	
	string(REPLACE "/osl1/osl.h" "" OSL1_INCLUDE_DIR ${OSL1_INCLUDE_DIR})
	
	set(OSL1_FOUND "TRUE")
	
	include_directories(${OSL1_INCLUDE_DIR})
	
	message(STATUS "Library OpenScop 1 found =) ${OSL1_INCLUDE_DIR} | ${OSL1_LIBRARY}")
	
else()
	
	set(OSL1_FOUND "FALSE")
	
	message(STATUS "Library OpenScop 1 not found :(")
	
endif()
