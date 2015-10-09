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


#ifndef OSL1_OSL_TO_OSL1_H
#define OSL1_OSL_TO_OSL1_H

#include "scop.h"
#include "vector/scop.h"

#include "../osl/osl.h"


// osl to osl1

static inline
osl1_vector_scop_t osl_to_osl1(const osl_scop_t* const scop_osl);
static inline
osl1_scop_t osl_to_osl1_scop(const osl_scop_t* const scop_osl);
static inline
osl1_vector_statement_t osl_to_osl1_statement(
                                   const osl_statement_t* const statement_osl);
static inline
gho_vector_any_t osl_to_osl1_extensions(
                                    const osl_generic_t* const extensions_osl);
static inline
osl1_relation_t osl_to_osl1_relation(const osl_relation_t* const relation_osl);


#include "implementation/osl_to_osl1.h"

#endif
