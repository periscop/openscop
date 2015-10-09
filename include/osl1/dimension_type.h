// Copyright © 2015 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr

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


#ifndef OSL1_DIMENSION_TYPE_H
#define OSL1_DIMENSION_TYPE_H

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#include <gho/type.h>
#include <gho/string.h>
#include <gho/any.h>


/// \brief Alpha or beta (dimension type)
typedef enum osl1_dimension_type {
  
  osl1_dimension_type_unknown,
  osl1_dimension_type_alpha,
  osl1_dimension_type_beta
  
} osl1_dimension_type;


/**
 * \brief Dimension types (alpha, beta, stripmined, parallel, vectorizable)
 */
typedef struct {
  
  /// \brief Alpha or beta
  osl1_dimension_type dimension_type;
  
  /// \brief Is stripmined?
  bool stripmined;
  
  /// \brief Is parallel?
  bool parallel;
  
  /// \brief Is vectorizable?
  bool vectorizable;
  
} osl1_dimension_type_t;


#if defined(__cplusplus)
extern "C"
{
#endif

// Create & destroy
osl1_dimension_type_t osl1_dimension_type_create();
void osl1_dimension_type_destroy(osl1_dimension_type_t* dimension_type);
void osl1_dimension_type_reset(osl1_dimension_type_t* dimension_type);

// Output
void osl1_dimension_type_fprinti(FILE* file,
                              const osl1_dimension_type_t* const dimension_type,
                              const unsigned int indent);
void osl1_dimension_type_fprint(FILE* file,
                            const osl1_dimension_type_t* const dimension_type);
void osl1_dimension_type_print(
                            const osl1_dimension_type_t* const dimension_type);
void osl1_dimension_type_sprinti(char** c_str,
                              const osl1_dimension_type_t* const dimension_type,
                              const unsigned int indent);
void osl1_dimension_type_sprint(char** c_str,
                            const osl1_dimension_type_t* const dimension_type);

// Input
osl1_dimension_type_t osl1_dimension_type_fread(FILE* file);
osl1_dimension_type_t osl1_dimension_type_sread(const char** c_str);

// Copy & comparisons
osl1_dimension_type_t osl1_dimension_type_copy(
                            const osl1_dimension_type_t* const dimension_type);
void osl1_dimension_type_copy_(
                              const osl1_dimension_type_t* const dimension_type,
                              osl1_dimension_type_t* copy);
bool osl1_dimension_type_equal(const osl1_dimension_type_t* const a,
                               const osl1_dimension_type_t* const b);

// Conversion
gho_string_t osl1_dimension_type_to_string(
                            const osl1_dimension_type_t* const dimension_type);

#if defined(__cplusplus)
}
#endif

// Conversion
static inline
gho_any_t osl1_dimension_type_to_any(
                            const osl1_dimension_type_t* const dimension_type);

#include "implementation/dimension_type.h"

#endif
