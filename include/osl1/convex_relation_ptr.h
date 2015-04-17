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


#ifndef OSL1_CONVEX_RELATION_PTR_H
#define OSL1_CONVEX_RELATION_PTR_H

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#include <gho/type.h>
#include <gho/string.h>

#include "convex_relation.h"


/**
 * \brief Pointer to an osl1_convex_relation_t
 */
typedef osl1_convex_relation_t* osl1_convex_relation_ptr_t;


// Create & destroy
osl1_convex_relation_ptr_t osl1_convex_relation_ptr_create();
void osl1_convex_relation_ptr_destroy(
                              osl1_convex_relation_ptr_t* convex_relation_ptr);
void osl1_convex_relation_ptr_reset(
                              osl1_convex_relation_ptr_t* convex_relation_ptr);

// Output
void osl1_convex_relation_ptr_fprinti(FILE* file,
                    const osl1_convex_relation_ptr_t* const convex_relation_ptr,
                    const unsigned int indent);
void osl1_convex_relation_ptr_fprint(FILE* file,
                  const osl1_convex_relation_ptr_t* const convex_relation_ptr);
void osl1_convex_relation_ptr_print(
                  const osl1_convex_relation_ptr_t* const convex_relation_ptr);
void osl1_convex_relation_ptr_sprinti(char** c_str,
                    const osl1_convex_relation_ptr_t* const convex_relation_ptr,
                    const unsigned int indent);
void osl1_convex_relation_ptr_sprint(char** c_str,
                  const osl1_convex_relation_ptr_t* const convex_relation_ptr);

// Copy & comparisons
osl1_convex_relation_ptr_t osl1_convex_relation_ptr_copy(
                  const osl1_convex_relation_ptr_t* const convex_relation_ptr);
void osl1_convex_relation_ptr_copy_(
                    const osl1_convex_relation_ptr_t* const convex_relation_ptr,
                    osl1_convex_relation_ptr_t* copy);
bool osl1_convex_relation_ptr_equal(const osl1_convex_relation_ptr_t* const a,
                                const osl1_convex_relation_ptr_t* const b);

// Conversion
gho_string_t osl1_convex_relation_ptr_to_string(
                  const osl1_convex_relation_ptr_t* const convex_relation_ptr);


#include "implementation/convex_relation_ptr.h"

#endif
