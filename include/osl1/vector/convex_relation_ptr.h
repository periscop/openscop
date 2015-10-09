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


#ifndef OSL1_VECTOR_CONVEX_RELATION_PTR_H
#define OSL1_VECTOR_CONVEX_RELATION_PTR_H

#include "../convex_relation_ptr.h"


#define gho_vector_T osl1_vector_convex_relation_ptr
#define gho_vector_T_t osl1_vector_convex_relation_ptr_t

#define T_t osl1_convex_relation_ptr_t

#define gho_type_vector_T GHO_TYPE_OSL_VECTOR_RELATION

// T gho_T_create();
#define gho_T_create osl1_convex_relation_ptr_create

/// void gho_T_destroy(T* t);
#define gho_T_destroy osl1_convex_relation_ptr_destroy

// void gho_T_fprint(FILE* file, const T* const t);
#define gho_T_fprint osl1_convex_relation_ptr_fprint

// void gho_T_sprint(char** c_str, const T* const t);
#define gho_T_sprint osl1_convex_relation_ptr_sprint

// T gho_T_copy(const T* const t);
#define gho_T_copy osl1_convex_relation_ptr_copy

// bool gho_T_equal(const T* const a, const T* const b);
#define gho_T_equal osl1_convex_relation_ptr_equal

// int gho_T_compare(const T* const a, const T* const b);
//#define gho_T_compare osl1_convex_relation_ptr_compare

#include <gho/vector_T.h>

#endif
