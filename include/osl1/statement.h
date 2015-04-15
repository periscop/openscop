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


#ifndef OSL1_STATEMENT_H
#define OSL1_STATEMENT_H

#include <stdio.h>
#include <stdbool.h>

#include <gho/string.h>
#include <gho/any.h>
#include <gho/vector/any.h>

#include "relation.h"
#include "vector/relation.h"


/**
 * \brief osl1_statement_t describes a SCoP statement
 *        (domain, scattering, accesses)
 */
typedef struct {
  
  /// \brief Id
  size_t id;
  
  /// \brief Iteration domain
  osl1_relation_t domain;
  
  /// \brief Scattering (mapping)
  osl1_relation_t scattering;
  
  /// \brief Accesses (read)
  osl1_vector_relation_t accesses_read;
  
  /// \brief Accesses (write)
  osl1_vector_relation_t accesses_write;
  
  /// \brief Extensions
  gho_vector_any_t extensions;
  
} osl1_statement_t;


// Create & destroy
static inline
osl1_statement_t osl1_statement_create();
static inline
void osl1_statement_destroy(osl1_statement_t* statement);
static inline
void osl1_statement_erase(osl1_statement_t* statement);

// Output
static inline
void osl1_statement_fprinti(FILE* file,
                            const osl1_statement_t* const statement,
                            const unsigned int indent);
static inline
void osl1_statement_fprint(FILE* file,
                           const osl1_statement_t* const statement);
static inline
void osl1_statement_print(const osl1_statement_t* const statement);
static inline
void osl1_statement_sprinti(char** c_str,
                            const osl1_statement_t* const statement,
                            const unsigned int indent);
static inline
void osl1_statement_sprint(char** c_str,
                           const osl1_statement_t* const statement);
// Input
static inline
osl1_statement_t osl1_statement_fread(FILE* file);
static inline
osl1_statement_t osl1_statement_sread(const char** c_str);

// Copy & comparisons
static inline
osl1_statement_t osl1_statement_copy(const osl1_statement_t* const statement);
static inline
void osl1_statement_copy_(const osl1_statement_t* const statement,
                          osl1_statement_t* copy);
static inline
bool osl1_statement_equal(const osl1_statement_t* const a,
                          const osl1_statement_t* const b);

// Conversion
static inline
gho_string_t osl1_statement_to_string(const osl1_statement_t* const statement);
static inline
gho_any_t osl1_statement_to_any(const osl1_statement_t* const statement);


#include "implementation/statement.h"

#endif
