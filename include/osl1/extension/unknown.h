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


#ifndef OSL1_EXTENSION_UNKNOWN_H
#define OSL1_EXTENSION_UNKNOWN_H

#include <stdio.h>
#include <stdbool.h>

#include <gho/string.h>
#include <gho/any.h>


#if defined(__cplusplus)
extern "C"
{
#endif


/**
 * \brief osl1_extension_unknown_t stores an unknown extension
 */
typedef struct {
  
  /// \brief Mark
  gho_string_t mark;
  
  /// \brief Extension
  gho_string_t extension;
  
} osl1_extension_unknown_t;


// Create & destroy
osl1_extension_unknown_t osl1_extension_unknown_create();
osl1_extension_unknown_t osl1_extension_unknown_create_with_mark(
                                               const gho_string_t* const mark);
void osl1_extension_unknown_destroy(osl1_extension_unknown_t* unknown);
void osl1_extension_unknown_reset(osl1_extension_unknown_t* unknown);

// Output
void osl1_extension_unknown_fprinti(FILE* file,
                                  const osl1_extension_unknown_t* const unknown,
                                  const unsigned int indent);
void osl1_extension_unknown_fprint(FILE* file,
                                const osl1_extension_unknown_t* const unknown);
void osl1_extension_unknown_print(
                                const osl1_extension_unknown_t* const unknown);
void osl1_extension_unknown_sprinti(char** c_str,
                                  const osl1_extension_unknown_t* const unknown,
                                  const unsigned int indent);
void osl1_extension_unknown_sprint(char** c_str,
                                const osl1_extension_unknown_t* const unknown);

// Input
osl1_extension_unknown_t osl1_extension_unknown_fread_with_mark(FILE* file,
                                               const gho_string_t* const mark);
osl1_extension_unknown_t osl1_extension_unknown_sread_with_mark(
                                               const char** c_str,
                                               const gho_string_t* const mark);

// Copy & comparisons
osl1_extension_unknown_t osl1_extension_unknown_copy(
                                const osl1_extension_unknown_t* const unknown);
void osl1_extension_unknown_copy_(
                                  const osl1_extension_unknown_t* const unknown,
                                  osl1_extension_unknown_t* copy);
bool osl1_extension_unknown_equal(const osl1_extension_unknown_t* const a,
                                  const osl1_extension_unknown_t* const b);

// Conversion
gho_string_t osl1_extension_unknown_to_string(
                                const osl1_extension_unknown_t* const unknown);
gho_any_t osl1_extension_unknown_to_any(
                                const osl1_extension_unknown_t* const unknown);

#if defined(__cplusplus)
}
#endif

#endif
