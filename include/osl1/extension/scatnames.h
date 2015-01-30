// Copyright © 2014-2015 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#ifndef OSL1_EXTENSION_SCATNAMES_H
#define OSL1_EXTENSION_SCATNAMES_H

#include <stdio.h>
#include <stdbool.h>

#include <gho/string.h>
#include <gho/any.h>
#include <gho/vector/string.h>


#if defined(__cplusplus)
extern "C"
{
#endif


/**
 * \brief osl1_extension_scatnames_t stores names of output dimensions
 *        of scattering
 */
typedef struct {
  
  /// \brief Names of output dimensions of scattering
  gho_vector_string_t scatnames;
  
} osl1_extension_scatnames_t;

// Create & destroy
osl1_extension_scatnames_t osl1_extension_scatnames_create();
void osl1_extension_scatnames_destroy(osl1_extension_scatnames_t* scatnames);
void osl1_extension_scatnames_reset(osl1_extension_scatnames_t* scatnames);

// Output
void osl1_extension_scatnames_fprinti(FILE* file,
                              const osl1_extension_scatnames_t* const scatnames,
                              const unsigned int indent);
void osl1_extension_scatnames_fprint(FILE* file,
                            const osl1_extension_scatnames_t* const scatnames);
void osl1_extension_scatnames_print(
                            const osl1_extension_scatnames_t* const scatnames);
void osl1_extension_scatnames_sprinti(char** c_str,
                              const osl1_extension_scatnames_t* const scatnames,
                              const unsigned int indent);
void osl1_extension_scatnames_sprint(char** c_str,
                            const osl1_extension_scatnames_t* const scatnames);

// Input
osl1_extension_scatnames_t osl1_extension_scatnames_fread(FILE* file);
osl1_extension_scatnames_t osl1_extension_scatnames_sread(const char** c_str);

// Copy & comparisons
osl1_extension_scatnames_t osl1_extension_scatnames_copy(
                            const osl1_extension_scatnames_t* const scatnames);
void osl1_extension_scatnames_copy_(
                              const osl1_extension_scatnames_t* const scatnames,
                              osl1_extension_scatnames_t* copy);
bool osl1_extension_scatnames_equal(const osl1_extension_scatnames_t* const a,
                                    const osl1_extension_scatnames_t* const b);

// Conversion
gho_string_t osl1_extension_scatnames_to_string(
                            const osl1_extension_scatnames_t* const scatnames);
gho_any_t osl1_extension_scatnames_to_any(
                            const osl1_extension_scatnames_t* const scatnames);

#if defined(__cplusplus)
}
#endif

#endif
