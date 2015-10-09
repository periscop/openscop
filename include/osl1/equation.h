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


#ifndef OSL1_EQUATION_H
#define OSL1_EQUATION_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "convex_relation.h"


#if defined(__cplusplus)
extern "C" {
#endif

bool osl1_is_equation(const osl1_convex_relation_t* const convex_relation,
                      const size_t i);
bool osl1_is_inequation(const osl1_convex_relation_t* const convex_relation,
                        const size_t i);
bool osl1_is_constant_equation(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i);
bool osl1_is_parameter_equation(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i);
bool osl1_is_beta_equation(const osl1_convex_relation_t* const convex_relation,
                           const size_t i);
bool osl1_is_alpha_equation(const osl1_convex_relation_t* const convex_relation,
                            const size_t i);
size_t osl1_get_beta_equation(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t n);

#if defined(__cplusplus)
}
#endif

#endif
