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

#include <gho/int/int.h>

#include "../../include/osl1/extension/body.h"
#include "../../include/osl1/input.h"


// Create & destroy

/**
 * \brief Return a new osl1_extension_body
 * \return a new osl1_extension_body
 */
osl1_extension_body_t osl1_extension_body_create() {
  osl1_extension_body_t body;
  body.expression = gho_string_create();
  body.original_iterators = gho_vector_string_create();
  body.accesses = gho_vector_start_and_size_create();
  return body;
}

/**
 * \brief Destroy an osl1_extension_body
 * \param[in] body An osl1_extension_body
 */
void osl1_extension_body_destroy(osl1_extension_body_t* body) {
  gho_string_destroy(&body->expression);
  gho_vector_string_destroy(&body->original_iterators);
  gho_vector_start_and_size_destroy(&body->accesses);
}

/**
 * \brief Reset an osl1_extension_body
 * \param[in] body An osl1_extension_body
 */
void osl1_extension_body_reset(osl1_extension_body_t* body) {
  osl1_extension_body_destroy(body);
  *body = osl1_extension_body_create();
}

// Output

/**
 * \brief Print an osl1_extension_body in a file with indentation
 * \param[in] file   A C file
 * \param[in] body   An osl1_extension_body
 * \param[in] indent Indentation (number of spaces)
 */
void osl1_extension_body_fprinti(FILE* file,
                                 const osl1_extension_body_t* const body,
                                 const unsigned int indent) {
  gho_c_str_fprinti(file, "<body>\n", indent);
  
  gho_c_str_fprint(file, "# Number of original iterators\n");
  gho_size_t_fprinti(file, &body->original_iterators.size, indent);
  gho_c_str_fprint(file, "\n");
  
  gho_c_str_fprint(file, "# Original iterators\n");
  gho_fprinti(file, indent);
  for (size_t i = 0; i < body->original_iterators.size; ++i) {
    gho_string_fprint(file, &body->original_iterators.array[i]);
    gho_c_str_fprint(file, " ");
  }
  gho_c_str_fprint(file, "\n");
  
  gho_c_str_fprint(file, "# Expression\n");
  gho_string_fprinti(file, &body->expression, indent);
  gho_c_str_fprint(file, "\n");
  
  gho_c_str_fprint(file, "# Accesses\n");
  gho_c_str_fprint(file, "# TODO\n");
  //gho_vector_start_and_size_fprinti(file, &body->accesses, indent);
  //gho_c_str_fprint(file, "\n"); // TODO
  
  gho_c_str_fprinti(file, "</body>\n", indent);
}

/**
 * \brief Print an osl1_extension_body in a file
 * \param[in] file A C file
 * \param[in] body An osl1_extension_body
 */
void osl1_extension_body_fprint(FILE* file,
                                const osl1_extension_body_t* const body) {
  osl1_extension_body_fprinti(file, body, 0);
}

/**
 * \brief Print an osl1_extension_body in stdout
 * \param[in] body An osl1_extension_body
 */
void osl1_extension_body_print(const osl1_extension_body_t* const body) {
  osl1_extension_body_fprint(stdout, body);
}

/**
 * \brief Print an osl1_extension_body in a C string with indentation
 * \param[in] c_str  A C string
 * \param[in] body   An osl1_extension_body
 * \param[in] indent Indentation (number of spaces)
 */
void osl1_extension_body_sprinti(char** c_str,
                                 const osl1_extension_body_t* const body,
                                 const unsigned int indent) {
  gho_c_str_sprinti(c_str, "<body>\n", indent);
  
  gho_c_str_sprint(c_str, "# Number of original iterators\n");
  gho_size_t_sprinti(c_str, &body->original_iterators.size, indent);
  gho_c_str_sprint(c_str, "\n");
  
  gho_c_str_sprint(c_str, "# Original iterators\n");
  gho_sprinti(c_str, indent);
  for (size_t i = 0; i < body->original_iterators.size; ++i) {
    gho_string_sprint(c_str, &body->original_iterators.array[i]);
    gho_c_str_sprint(c_str, " ");
  }
  gho_c_str_sprint(c_str, "\n");
  
  gho_c_str_sprint(c_str, "# Expression\n");
  gho_string_sprinti(c_str, &body->expression, indent);
  gho_c_str_sprint(c_str, "\n");
  
  gho_c_str_sprint(c_str, "# Accesses\n");
  gho_c_str_sprint(c_str, "# TODO\n");
  //gho_vector_start_and_size_sprinti(c_str, &body->accesses, indent);
  //gho_c_str_sprint(c_str, "\n"); // TODO
  
  gho_c_str_sprinti(c_str, "</body>\n", indent);
}

/**
 * \brief Print an osl1_extension_body in a C string
 * \param[in] c_str A C string
 * \param[in] body  An osl1_extension_body
 */
void osl1_extension_body_sprint(char** c_str,
                                const osl1_extension_body_t* const body) {
  osl1_extension_body_sprinti(c_str, body, 0);
}

// Input

/**
 * \brief Read an osl1_extension_body from a file
 * \param[in] file A C file
 * \return the osl1_extension_body read
 */
osl1_extension_body_t osl1_extension_body_fread(FILE* file) {
  osl1_skip_comments(file);
  osl1_extension_body_t r = osl1_extension_body_create();
  
  int nb_iterator = gho_int_fread(file);
  osl1_skip_comments(file);
  
  if (nb_iterator > 0) {
    for (size_t i = 0; i < (size_t)nb_iterator; ++i) {
      gho_string_t iterator = gho_string_fread(file);
      gho_vector_string_add(&r.original_iterators, &iterator);
      gho_string_destroy(&iterator);
    }
  }
  osl1_skip_comments(file);
  
  gho_string_t expression = gho_string_get_line(file);
  gho_string_add(&r.expression, &expression);
  gho_string_destroy(&expression);
  osl1_skip_comments(file);
  
  // TODO accesses
  fprintf(stderr, "TODO: osl1_extension_body_fread IS NOT FULLY IMPLEMENTED!\n");
  
  return r;
}

/**
 * \brief Read an osl1_extension_body from a C string
 * \param[in] c_str A C string
 * \return the osl1_extension_body read
 */
osl1_extension_body_t osl1_extension_body_sread(const char** c_str) {
  osl1_skip_comments_from_c_str(c_str);
  osl1_extension_body_t r = osl1_extension_body_create();
  
  int nb_iterator = gho_int_sread(c_str);
  osl1_skip_comments_from_c_str(c_str);
  
  if (nb_iterator > 0) {
    for (size_t i = 0; i < (size_t)nb_iterator; ++i) {
      gho_string_t iterator = gho_string_sread(c_str);
      gho_vector_string_add(&r.original_iterators, &iterator);
      gho_string_destroy(&iterator);
    }
  }
  osl1_skip_comments_from_c_str(c_str);
  
  gho_string_t expression = gho_string_get_line_from_c_str(c_str);
  gho_string_add(&r.expression, &expression);
  gho_string_destroy(&expression);
  osl1_skip_comments_from_c_str(c_str);
  
  // TODO accesses
  fprintf(stderr, "TODO: osl1_extension_body_sread IS NOT FULLY IMPLEMENTED!\n");
  
  return r;
}

// Copy & comparisons

/**
 * \brief Copy an osl1_extension_body
 * \param[in] body An osl1_extension_body
 * \return the osl1_extension_body copied
 */
osl1_extension_body_t osl1_extension_body_copy(
                                      const osl1_extension_body_t* const body) {
  osl1_extension_body_t r;
  osl1_extension_body_copy_(body, &r);
  return r;
}

/**
 * \brief Copy an osl1_extension_body
 * \param[in] body An osl1_extension_body
 * \param[in] copy A pointer on an not initialized osl1_extension_body
 * \warning Do not use this function, use osl1_extension_body_copy
 */
void osl1_extension_body_copy_(const osl1_extension_body_t* const body,
                               osl1_extension_body_t* copy) {
  copy->expression = gho_string_copy(&body->expression);
  copy->original_iterators = gho_vector_string_copy(&body->original_iterators);
  copy->accesses = gho_vector_start_and_size_copy(&body->accesses);
}

/**
 * \brief Equality between two osl1_extension_body
 * \param[in] a An osl1_extension_body
 * \param[in] b An osl1_extension_body
 * \return true if the osl1_extension_body are equals, false otherwise
 */
bool osl1_extension_body_equal(const osl1_extension_body_t* const a,
                               const osl1_extension_body_t* const b) {
  return
    gho_string_equal(&a->expression, &b->expression) &&
    gho_vector_string_equal(&a->original_iterators, &b->original_iterators) &&
    gho_vector_start_and_size_equal(&a->accesses, &b->accesses);
}

// Conversion

/**
 * \brief Convert an osl1_extension_body into a gho_string
 * \param[in] body An osl1_extension_body
 * \return the gho_string from the osl1_extension_body
 */
gho_string_t osl1_extension_body_to_string(
                                      const osl1_extension_body_t* const body) {
  gho_string_t r = gho_string_create();
  osl1_extension_body_sprint(&r.c_str, body);
  return r;
}

/**
 * \brief Convert an osl1_extension_body into a gho_any
 * \param[in] body An osl1_extension_body
 * \return the gho_any from the osl1_extension_body
 */
gho_any_t osl1_extension_body_to_any(const osl1_extension_body_t* const body) {
  gho_any_t r = gho_any_create();
  r.type = GHO_TYPE_OSL_EXTENSION_BODY;
  r.size_of_struct = sizeof(osl1_extension_body_t);
  osl1_extension_body_t* p = gho_alloc(osl1_extension_body_t);
  osl1_extension_body_copy_(body, p);
  r.any = p; p = NULL;
  r.destroy_fct = (gho_destroy_fct_t)osl1_extension_body_destroy;
  r.fprinti_fct = (gho_fprinti_fct_t)osl1_extension_body_fprinti;
  r.sprinti_fct = (gho_sprinti_fct_t)osl1_extension_body_sprinti;
  r.copy_fct = (gho_copy_fct_t)osl1_extension_body_copy_;
  r.equal_fct = (gho_equal_fct_t)osl1_extension_body_equal;
  r.to_string_fct = (gho_to_string_fct_t)osl1_extension_body_to_string;
  return r;
}
