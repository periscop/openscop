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


#ifndef OSL1_PRINT_H
#define OSL1_PRINT_H

#include <stdio.h>
#include <stdbool.h>

#include <gho/vector/uint.h>

#include "scop.h"
#include "vector/scop.h"
#include "statement.h"
#include "vector/statement.h"
#include "relation.h"
#include "convex_relation.h"


#if defined(__cplusplus)
extern "C"
{
#endif


// Convex relation index name

gho_string_t osl1_convex_relation_name_column(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t j,
                            const osl1_scop_t* const scop,
                            const osl1_statement_t* const statement);
gho_string_t osl1_convex_relation_name_output_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i_output_dim,
                            const osl1_scop_t* const scop,
                            const osl1_statement_t* const statement);
gho_string_t osl1_convex_relation_name_input_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i_input_dim,
                            const osl1_scop_t* const scop,
                            const osl1_statement_t* const statement);
gho_string_t osl1_convex_relation_name_local_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i_local_dim,
                            const osl1_scop_t* const scop,
                            const osl1_statement_t* const statement);
gho_string_t osl1_convex_relation_name_parameter(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i_parameter,
                            const osl1_scop_t* const scop,
                            const osl1_statement_t* const statement);
void osl1_convex_relation_fprint_name(FILE * file,
                                      const gho_string_t* const name,
                                      const gho_uint column_size);
void osl1_convex_relation_sprint_name(char** c_str,
                                      const gho_string_t* const name,
                                      const gho_uint column_size);
gho_vector_uint_t osl1_convex_relation_column_sizes(
                            const osl1_convex_relation_t* const convex_relation,
                            const osl1_scop_t* const scop,
                            const osl1_statement_t* const statement);

// Convex relation
void osl1_convex_relation_fprinti_openscop(FILE* file,
                            const osl1_convex_relation_t* const convex_relation,
                            const unsigned int indent,
                            const osl1_scop_t* const scop,
                            const osl1_statement_t* const statement);
void osl1_convex_relation_sprinti_openscop(char** c_str,
                            const osl1_convex_relation_t* const convex_relation,
                            const unsigned int indent,
                            const osl1_scop_t* const scop,
                            const osl1_statement_t* const statement);

// Relation
void osl1_relation_fprinti_openscop(FILE* file,
                                    const osl1_relation_t* const relation,
                                    const unsigned int indent,
                                    const osl1_scop_t* const scop,
                                    const osl1_statement_t* const statement);
void osl1_relation_sprinti_openscop(char** c_str,
                                    const osl1_relation_t* const relation,
                                    const unsigned int indent,
                                    const osl1_scop_t* const scop,
                                    const osl1_statement_t* const statement);

// Vector of relations
void osl1_vector_relation_fprinti_openscop(FILE* file,
                                  const osl1_vector_relation_t* const relations,
                                  const unsigned int indent,
                                  const osl1_scop_t* const scop,
                                  const osl1_statement_t* const statement);
void osl1_vector_relation_sprinti_openscop(char** c_str,
                                  const osl1_vector_relation_t* const relations,
                                  const unsigned int indent,
                                  const osl1_scop_t* const scop,
                                  const osl1_statement_t* const statement);

// Statement
void osl1_statement_fprinti_openscop(FILE* file,
                                     const osl1_statement_t* const statement,
                                     const unsigned int indent,
                                     const osl1_scop_t* const scop);
void osl1_statement_sprinti_openscop(char** c_str,
                                     const osl1_statement_t* const statement,
                                     const unsigned int indent,
                                     const osl1_scop_t* const scop);

// Vector of statements
void osl1_vector_statement_fprinti_openscop(FILE* file,
                                const osl1_vector_statement_t* const statements,
                                const unsigned int indent,
                                const osl1_scop_t* const scop);
void osl1_vector_statement_sprinti_openscop(char** c_str,
                                const osl1_vector_statement_t* const statements,
                                const unsigned int indent,
                                const osl1_scop_t* const scop);

// SCoP
void osl1_scop_fprinti_openscop(FILE* file,
                                const osl1_scop_t* const scop,
                                const unsigned int indent);
void osl1_scop_sprinti_openscop(char** c_str,
                                const osl1_scop_t* const scop,
                                const unsigned int indent);

// Vector of SCoP

#if defined(__cplusplus)
}
#endif

#endif
