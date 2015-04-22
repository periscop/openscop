// Copyright © 2014, 2015 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr

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


#ifndef OSL1_BETA_FUNCTIONS_H
#define OSL1_BETA_FUNCTIONS_H

#include "beta.h"
#include "vector/beta.h"


#if defined(__cplusplus)
extern "C" {
#endif

// Extract
osl1_beta_t osl1_extract_beta(
                          const osl1_convex_relation_t* const convex_relation);
osl1_vector_beta_t osl1_extract_betas(const osl1_scop_t* const scop);

// Get from beta
const osl1_convex_relation_t* osl1_get_convex_relation_cptr(
                                                const osl1_scop_t* const scop,
                                                const osl1_beta_t* const beta);
osl1_convex_relation_t* osl1_get_convex_relation_ptr(
                                                osl1_scop_t* scop,
                                                const osl1_beta_t* const beta);
osl1_vector_convex_relation_ptr_t osl1_get_convex_relation_vector_ptr(
                                         osl1_scop_t* scop,
                                         const osl1_beta_t* const beta_prefix);
size_t osl1_nb_statement_beta_prefix(const osl1_scop_t* const scop,
                              const osl1_beta_t* const beta_prefix);
size_t osl1_nb_statement_in_loop(const osl1_scop_t* const scop,
                                      const osl1_beta_t* const beta_prefix);

// Other
size_t osl1_beta_prefix_max_value(const osl1_scop_t* const scop,
                                  const osl1_beta_t* const beta_prefix);

#if defined(__cplusplus)
}
#endif

#endif
