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


#ifndef OSL1_PRINT_RELATION_H
#define OSL1_PRINT_RELATION_H

#include <stdio.h>

#include "../relation.h"
#include "../vector/relation.h"
#include "../statement.h"
#include "../scop.h"


// Relation
static inline
void osl1_relation_fprinti_openscop(FILE* file,
                                    const osl1_relation_t* const relation,
                                    const unsigned int indent,
                                    const osl1_scop_t* const scop,
                                    const osl1_statement_t* const statement);
static inline
void osl1_relation_sprinti_openscop(char** c_str,
                                    const osl1_relation_t* const relation,
                                    const unsigned int indent,
                                    const osl1_scop_t* const scop,
                                    const osl1_statement_t* const statement);

// Vector of relations
static inline
void osl1_vector_relation_fprinti_openscop(FILE* file,
                                  const osl1_vector_relation_t* const relations,
                                  const unsigned int indent,
                                  const osl1_scop_t* const scop,
                                  const osl1_statement_t* const statement);
static inline
void osl1_vector_relation_sprinti_openscop(char** c_str,
                                  const osl1_vector_relation_t* const relations,
                                  const unsigned int indent,
                                  const osl1_scop_t* const scop,
                                  const osl1_statement_t* const statement);

#endif
