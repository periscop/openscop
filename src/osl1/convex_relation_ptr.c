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


#include <stdlib.h>

#include "../include/osl1/convex_relation_ptr.h"


// Create & destroy

/**
 * \brief Return a new osl1_convex_relation_ptr_t
 * \return a new osl1_convex_relation_ptr_t
 */
osl1_convex_relation_ptr_t osl1_convex_relation_ptr_create() {
  return NULL;
}

/**
 * \brief Destroy an osl1_convex_relation_ptr_t
 * \param[in] convex_relation_ptr An osl1_convex_relation_ptr_t
 */
void osl1_convex_relation_ptr_destroy(
                              osl1_convex_relation_ptr_t* convex_relation_ptr) {
  *convex_relation_ptr = NULL;
}

/**
 * \brief Reset an osl1_convex_relation_ptr_t
 * \param[in] convex_relation_ptr An osl1_convex_relation_ptr_t
 */
void osl1_convex_relation_ptr_reset(
                              osl1_convex_relation_ptr_t* convex_relation_ptr) {
  *convex_relation_ptr = NULL;
}

// Output

/**
 * \brief Print an osl1_convex_relation_ptr_t in a file with indentation
 * \param[in] file                A C file
 * \param[in] convex_relation_ptr An osl1_convex_relation_ptr_t
 * \param[in] indent              Indentation (number of spaces)
 */
void osl1_convex_relation_ptr_fprinti(FILE* file,
                    const osl1_convex_relation_ptr_t* const convex_relation_ptr,
                    const unsigned int indent) {
  gho_fprinti(file, indent);
  fprintf(file, "%p", (void*)*convex_relation_ptr);
}

/**
 * \brief Print an osl1_convex_relation_ptr_t in a file
 * \param[in] file                A C file
 * \param[in] convex_relation_ptr An osl1_convex_relation_ptr_t
 */
void osl1_convex_relation_ptr_fprint(FILE* file,
                  const osl1_convex_relation_ptr_t* const convex_relation_ptr) {
  osl1_convex_relation_ptr_fprinti(file, convex_relation_ptr, 0);
}

/**
 * \brief Print an osl1_convex_relation_ptr_t in stdout
 * \param[in] convex_relation_ptr An osl1_convex_relation_ptr_t
 */
void osl1_convex_relation_ptr_print(
                  const osl1_convex_relation_ptr_t* const convex_relation_ptr) {
  osl1_convex_relation_ptr_fprint(stdout, convex_relation_ptr);
}

/**
 * \brief Print an osl1_convex_relation_ptr_t in a C string with indentation
 * \param[in] c_str               A C string
 * \param[in] convex_relation_ptr An osl1_convex_relation_ptr_t
 * \param[in] indent              Indentation (number of spaces)
 */
void osl1_convex_relation_ptr_sprinti(char** c_str,
                    const osl1_convex_relation_ptr_t* const convex_relation_ptr,
                    const unsigned int indent) {
  gho_sprinti(c_str, indent);
  char tmp[sizeof(void*) * CHAR_BIT + 1] = { '\0' };
  sprintf(tmp, "%p", (void*)*convex_relation_ptr);
  gho_c_str_add(c_str, tmp);
}

/**
 * \brief Print an osl1_convex_relation_ptr_t in a C string
 * \param[in] c_str               A C string
 * \param[in] convex_relation_ptr An osl1_convex_relation_ptr_t
 */
void osl1_convex_relation_ptr_sprint(char** c_str,
                  const osl1_convex_relation_ptr_t* const convex_relation_ptr) {
  osl1_convex_relation_ptr_sprinti(c_str, convex_relation_ptr, 0);
}

// Copy & comparisons

/**
 * \brief Copy an osl1_convex_relation_ptr
 * \param[in] convex_relation_ptr An osl1_convex_relation_ptr
 * \return the osl1_convex_relation_ptr copied
 */
osl1_convex_relation_ptr_t osl1_convex_relation_ptr_copy(
                  const osl1_convex_relation_ptr_t* const convex_relation_ptr) {
  return *convex_relation_ptr;
}

/**
 * \brief Copy an osl1_convex_relation_ptr
 * \param[in] convex_relation_ptr An osl1_convex_relation_ptr
 * \param[in] copy A pointer on an not initialized osl1_convex_relation_ptr
 * \warning Do not use this function, use osl1_convex_relation_ptr_copy
 */
void osl1_convex_relation_ptr_copy_(
                    const osl1_convex_relation_ptr_t* const convex_relation_ptr,
                    osl1_convex_relation_ptr_t* copy) {
  *copy = *convex_relation_ptr;
}

/**
 * \brief Equality between two osl1_convex_relation_ptr
 * \param[in] a An osl1_convex_relation_ptr
 * \param[in] b An osl1_convex_relation_ptr
 * \return true if the osl1_convex_relation_ptr are equals, false otherwise
 */
bool osl1_convex_relation_ptr_equal(const osl1_convex_relation_ptr_t* const a,
                                const osl1_convex_relation_ptr_t* const b) {
  return *a == *b;
}

// Conversion

/**
 * \brief Convert an osl1_convex_relation_ptr into A gho_string
 * \param[in] convex_relation_ptr An osl1_convex_relation_ptr
 * \return the gho_string from the osl1_convex_relation_ptr
 */
gho_string_t osl1_convex_relation_ptr_to_string(
                  const osl1_convex_relation_ptr_t* const convex_relation_ptr) {
  gho_string_t r = gho_string_create();
  osl1_convex_relation_ptr_sprint(&r.c_str, convex_relation_ptr);
  return r;
}
