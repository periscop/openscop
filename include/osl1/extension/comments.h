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


#ifndef OSL1_EXTENSION_COMMENTS_H
#define OSL1_EXTENSION_COMMENTS_H

#include <stdio.h>
#include <stdbool.h>

#include <gho/string.h>
#include <gho/any.h>
#include <gho/vector/string.h>


/**
 * \brief osl1_extension_comments_t stores first comments of the source code
 */
typedef struct {
  
  /// \brief First comments of the source code
  gho_vector_string_t comments;
  
} osl1_extension_comments_t;


#if defined(__cplusplus)
extern "C"
{
#endif

// Create & destroy
osl1_extension_comments_t osl1_extension_comments_create();
void osl1_extension_comments_destroy(osl1_extension_comments_t* comments);
void osl1_extension_comments_reset(osl1_extension_comments_t* comments);

// Output
void osl1_extension_comments_fprinti(FILE* file,
                                const osl1_extension_comments_t* const comments,
                                const unsigned int indent);
void osl1_extension_comments_fprint(FILE* file,
                              const osl1_extension_comments_t* const comments);
void osl1_extension_comments_print(
                              const osl1_extension_comments_t* const comments);
void osl1_extension_comments_sprinti(char** c_str,
                                const osl1_extension_comments_t* const comments,
                                const unsigned int indent);
void osl1_extension_comments_sprint(char** c_str,
                              const osl1_extension_comments_t* const comments);

// Input
osl1_extension_comments_t osl1_extension_comments_fread(FILE* file);
osl1_extension_comments_t osl1_extension_comments_sread(const char** c_str);

// Copy & comparisons
osl1_extension_comments_t osl1_extension_comments_copy(
                              const osl1_extension_comments_t* const comments);
void osl1_extension_comments_copy_(
                                const osl1_extension_comments_t* const comments,
                                osl1_extension_comments_t* copy);
bool osl1_extension_comments_equal(const osl1_extension_comments_t* const a,
                                   const osl1_extension_comments_t* const b);

// Conversion
gho_string_t osl1_extension_comments_to_string(
                              const osl1_extension_comments_t* const comments);

// Extract
osl1_extension_comments_t osl1_extension_comments_extract(FILE* file,
                                                      const size_t line_start);

#if defined(__cplusplus)
}
#endif


// Conversion
static inline
gho_any_t osl1_extension_comments_to_any(
                              const osl1_extension_comments_t* const comments);


#include "../implementation/extension/comments.h"

#endif
