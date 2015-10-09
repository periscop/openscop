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


#ifndef OSL1_BETA_H
#define OSL1_BETA_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include <gho/type.h>
#include <gho/string.h>

#include "scop.h"
#include "vector/convex_relation_ptr.h"


// osl1_beta_element_t

#if defined(__cplusplus)
extern "C" {
#endif

void osl1_beta_element_fprinti(FILE* file, const size_t* const i,
                               const unsigned int indent);
void osl1_beta_element_fprint(FILE* file, const size_t* const i);
void osl1_beta_element_print(const size_t* const i);
void osl1_beta_element_sprinti(char** c_str, const size_t* const i,
                               const unsigned int indent);
void osl1_beta_element_sprint(char** c_str, const size_t* const i);

size_t osl1_beta_element_fread(FILE* file);
size_t osl1_beta_element_sread(const char** c_str);

gho_string_t osl1_beta_element_to_string(const size_t* const i);

#if defined(__cplusplus)
}
#endif

/// @brief beta element: * value
#define osl1_beta_element_star SIZE_MAX


// osl1_beta

#define gho_vector_T osl1_beta
#define gho_vector_T_t osl1_beta_t

#define T_t size_t

#define gho_type_vector_T GHO_TYPE_OSL_BETA

// T gho_T_create();
#define gho_T_create gho_size_t_create

/// void gho_T_destroy(T* t);
#define gho_T_destroy gho_size_t_destroy

// void gho_T_fprint(FILE* file, const T* const t);
#define gho_T_fprint osl1_beta_element_fprint

// void gho_T_sprint(char** c_str, const T* const t);
#define gho_T_sprint osl1_beta_element_sprint

// T gho_T_fread(FILE* file);
#define gho_T_fread osl1_beta_element_fread

// T gho_T_sread(char**);
#define gho_T_sread osl1_beta_element_sread

// T gho_T_copy(const T* const t);
#define gho_T_copy gho_size_t_copy

// bool gho_T_equal(const T* const a, const T* const b);
#define gho_T_equal gho_size_t_equal

// int gho_T_compare(const T* const a, const T* const b);
//#define gho_T_compare gho_size_t_compare

#include <gho/vector_T.h>


// osl1_beta functions

#if defined(__cplusplus)
extern "C" {
#endif

// Beta value & Beta prefix
size_t osl1_get_beta_value(const osl1_convex_relation_t* const convex_relation,
                           const size_t i);
void osl1_set_beta_value(osl1_convex_relation_t* convex_relation,
                         const size_t i, const size_t new_value);
bool osl1_same_beta_prefix(const osl1_beta_t* const beta,
                           const osl1_beta_t* const beta_prefix);
void osl1_beta_to_beta_prefix(osl1_beta_t* beta);

#if defined(__cplusplus)
}
#endif

#endif
