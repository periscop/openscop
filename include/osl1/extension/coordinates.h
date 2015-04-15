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


#ifndef OSL1_EXTENSION_COORDINATES_H
#define OSL1_EXTENSION_COORDINATES_H

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#include <gho/string.h>
#include <gho/any.h>


/**
 * \brief osl1_extension_coordinates_t stores informations about coordinates of a scop
 */
typedef struct {
  
  /// \brief Filename
  gho_string_t filename;
  
  /// \brief Starting line of the scop
  size_t line_start;
  
  /// \brief Ending line of the scop
  size_t line_end;
  
  /// \brief Starting column of the scop
  size_t column_start;
  
  /// \brief Ending column of the scop
  size_t column_end;
  
  /// \brief Indentation
  size_t indent;
  
} osl1_extension_coordinates_t;


#if defined(__cplusplus)
extern "C"
{
#endif

// Create & destroy
osl1_extension_coordinates_t osl1_extension_coordinates_create();
void osl1_extension_coordinates_destroy(osl1_extension_coordinates_t* scop);
void osl1_extension_coordinates_reset(osl1_extension_coordinates_t* scop);

// Output
void osl1_extension_coordinates_fprinti(FILE* file,
                                 const osl1_extension_coordinates_t* const scop,
                                 const unsigned int indent);
void osl1_extension_coordinates_fprint(FILE* file,
                               const osl1_extension_coordinates_t* const scop);
void osl1_extension_coordinates_print(
                               const osl1_extension_coordinates_t* const scop);
void osl1_extension_coordinates_sprinti(char** c_str,
                                 const osl1_extension_coordinates_t* const scop,
                                 const unsigned int indent);
void osl1_extension_coordinates_sprint(char** c_str,
                               const osl1_extension_coordinates_t* const scop);

// Input
osl1_extension_coordinates_t osl1_extension_coordinates_fread(FILE* file);
osl1_extension_coordinates_t osl1_extension_coordinates_sread(
                                                           const char** c_str);

// Copy & comparisons
osl1_extension_coordinates_t osl1_extension_coordinates_copy(
                               const osl1_extension_coordinates_t* const scop);
void osl1_extension_coordinates_copy_(
                                 const osl1_extension_coordinates_t* const scop,
                                 osl1_extension_coordinates_t* copy);
bool osl1_extension_coordinates_equal(
                                  const osl1_extension_coordinates_t* const a,
                                  const osl1_extension_coordinates_t* const b);

// Conversion
gho_string_t osl1_extension_coordinates_to_string(
                               const osl1_extension_coordinates_t* const scop);

#if defined(__cplusplus)
}
#endif


// Conversion
static inline
gho_any_t osl1_extension_coordinates_to_any(
                        const osl1_extension_coordinates_t* const coordinates);


#include "../implementation/extension/coordinates.h"

#endif
