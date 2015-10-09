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


#ifndef OSL1_PRINT_STATEMENT_H
#define OSL1_PRINT_STATEMENT_H

#include <stdio.h>

#include "../statement.h"
#include "../vector/statement.h"
#include "../scop.h"


// Statement
static inline
void osl1_statement_fprinti_openscop(FILE* file,
                                     const osl1_statement_t* const statement,
                                     const unsigned int indent,
                                     const osl1_scop_t* const scop);
static inline
void osl1_statement_sprinti_openscop(char** c_str,
                                     const osl1_statement_t* const statement,
                                     const unsigned int indent,
                                     const osl1_scop_t* const scop);

// Vector of statements
static inline
void osl1_vector_statement_fprinti_openscop(FILE* file,
                                const osl1_vector_statement_t* const statements,
                                const unsigned int indent,
                                const osl1_scop_t* const scop);
static inline
void osl1_vector_statement_sprinti_openscop(char** c_str,
                                const osl1_vector_statement_t* const statements,
                                const unsigned int indent,
                                const osl1_scop_t* const scop);

#endif
