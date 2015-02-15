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


#ifndef OSL1_SCOP_H
#define OSL1_SCOP_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

#include <gho/string.h>
#include <gho/any.h>
#include <gho/vector/string.h>
#include <gho/vector/any.h>

#include "relation.h"
#include "vector/statement.h"
#include "extension.h"


#if defined(__cplusplus)
extern "C"
{
#endif


/**
 * \brief TODO osl1_scop_t
 */
typedef struct {
  
  /// \brief Costraints on parameters
  osl1_relation_t context;
  
  /// \brief Parameters
  gho_vector_string_t parameters;
  
  /// \brief Statements
  osl1_vector_statement_t statements;
  
  /// \brief Extensions
  gho_vector_any_t extensions;
  
} osl1_scop_t;

// Create & destroy
osl1_scop_t osl1_scop_create();
void osl1_scop_destroy(osl1_scop_t* scop);
void osl1_scop_erase(osl1_scop_t* scop);

// Output
void osl1_scop_fprinti(FILE* file, const osl1_scop_t* const scop,
                       const unsigned int indent);
void osl1_scop_fprint(FILE* file, const osl1_scop_t* const scop);
void osl1_scop_print(const osl1_scop_t* const scop);
void osl1_scop_sprinti(char** c_str, const osl1_scop_t* const scop,
                       const unsigned int indent);
void osl1_scop_sprint(char** c_str, const osl1_scop_t* const scop);
// Input
osl1_scop_t osl1_scop_fread(FILE* file);
osl1_scop_t osl1_scop_sread(const char** c_str);

// Copy & comparisons
osl1_scop_t osl1_scop_copy(const osl1_scop_t* const scop);
void osl1_scop_copy_(const osl1_scop_t* const scop, osl1_scop_t* copy);
bool osl1_scop_equal(const osl1_scop_t* const a, const osl1_scop_t* const b);

// Conversion
gho_string_t osl1_scop_to_string(const osl1_scop_t* const scop);
gho_any_t osl1_scop_to_any(const osl1_scop_t* const scop);

#include "print.h"

#if defined(__cplusplus)
}
#endif

#endif
