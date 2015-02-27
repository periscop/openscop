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


#ifndef OSL1_EXTENSION_BODY_H
#define OSL1_EXTENSION_BODY_H

#include <stdio.h>
#include <stdbool.h>

#include <gho/string.h>
#include <gho/any.h>
#include <gho/vector/string.h>
#include <gho/vector/start_and_size.h>


#if defined(__cplusplus)
extern "C"
{
#endif


/**
 * \brief osl1_extension_body_t stores informations about one statement
 */
typedef struct {
  
  /// \brief Expression
  gho_string_t expression;
  
  /// \brief Names of original iterators
  gho_vector_string_t original_iterators;
  
  /// \brief Accesses
  gho_vector_start_and_size_t accesses;
  
} osl1_extension_body_t;

// Create & destroy
osl1_extension_body_t osl1_extension_body_create();
void osl1_extension_body_destroy(osl1_extension_body_t* body);
void osl1_extension_body_reset(osl1_extension_body_t* body);

// Output
void osl1_extension_body_fprinti(FILE* file,
                                 const osl1_extension_body_t* const body,
                                 const unsigned int indent);
void osl1_extension_body_fprint(FILE* file,
                                const osl1_extension_body_t* const body);
void osl1_extension_body_print(const osl1_extension_body_t* const body);
void osl1_extension_body_sprinti(char** c_str,
                                 const osl1_extension_body_t* const body,
                                 const unsigned int indent);
void osl1_extension_body_sprint(char** c_str,
                                const osl1_extension_body_t* const body);

// Input
osl1_extension_body_t osl1_extension_body_fread(FILE* file);
osl1_extension_body_t osl1_extension_body_sread(const char** c_str);

// Copy & comparisons
osl1_extension_body_t osl1_extension_body_copy(
                                      const osl1_extension_body_t* const body);
void osl1_extension_body_copy_(const osl1_extension_body_t* const body,
                               osl1_extension_body_t* copy);
bool osl1_extension_body_equal(const osl1_extension_body_t* const a,
                               const osl1_extension_body_t* const b);

// Conversion
gho_string_t osl1_extension_body_to_string(
                                      const osl1_extension_body_t* const body);
gho_any_t osl1_extension_body_to_any(const osl1_extension_body_t* const body);

#if defined(__cplusplus)
}
#endif

#endif
