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


#include "../include/osl1/extension.h"


// Get

/**
 * \brief Get a pointer on asked extension
 * \param[in] type Extension type
 * \param[in] extensions A gho_vector_any_t
 * \return the pointer on asked extension, NULL if not found
 */
void* osl1_get_extension_ptr(gho_type_t const type,
                             gho_vector_any_t* extensions) {
  for (size_t i = 0; i < extensions->size; ++i) {
    if (extensions->array[i].type == type) { return extensions->array[i].any; }
  }
  
  return NULL;
}

/**
 * \brief Get a pointer on asked extension (const access)
 * \param[in] type Extension type
 * \param[in] extensions A gho_vector_any_t
 * \return the pointer on asked extension (const access), NULL if not found
 */
const void* osl1_get_extension_cptr(gho_type_t const type,
                                    const gho_vector_any_t* const extensions) {
  for (size_t i = 0; i < extensions->size; ++i) {
    if (extensions->array[i].type == type) { return extensions->array[i].any; }
  }
  
  return NULL;
}

// Output

/**
 * \brief Print extensions in a file with indentation
 * \param[in] file       A C file
 * \param[in] extensions An gho_vector_any_t
 * \param[in] indent     Indentation (number of spaces)
 */
void osl1_extensions_fprinti_openscop(FILE* file,
                                      const gho_vector_any_t* const extensions,
                                      const unsigned int indent) {
  for (size_t i = 0; i < extensions->size; ++i) {
    gho_any_fprinti(file, &extensions->array[i], indent);
    if (i != extensions->size - 1) { gho_c_str_fprint(file, "\n\n"); }
  }
}

/**
 * \brief Print extensions in a C string with indentation
 * \param[in] c_str      A C string
 * \param[in] extensions An gho_vector_any_t
 * \param[in] indent     Indentation (number of spaces)
 */
void osl1_extensions_sprinti_openscop(char** c_str,
                                      const gho_vector_any_t* const extensions,
                                      const unsigned int indent) {
  for (size_t i = 0; i < extensions->size; ++i) {
    gho_any_sprinti(c_str, &extensions->array[i], indent);
    if (i != extensions->size - 1) { gho_c_str_sprint(c_str, "\n\n"); }
  }
}
