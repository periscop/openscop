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


#ifndef OSL1_DIMENSIONS_H
#define OSL1_DIMENSIONS_H

#include "convex_relation.h"


#if defined(__cplusplus)
extern "C" {
#endif

// Index
bool osl1_is_beta_dim(const osl1_convex_relation_t* const convex_relation,
                      const size_t j);
bool osl1_is_alpha_dim(const osl1_convex_relation_t* const convex_relation,
                       const size_t j);
size_t osl1_alpha_dim_to_output_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i_alpha_dim);

#if defined(__cplusplus)
}
#endif

#endif
