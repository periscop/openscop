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


#include <gho/char.h>

#include "../../include/osl1/extension/unknown.h"
#include "../../include/osl1/input.h"


// Create & destroy

/**
 * \brief Return a new osl1_extension_unknown
 * \return a new osl1_extension_unknown
 */
osl1_extension_unknown_t osl1_extension_unknown_create() {
  osl1_extension_unknown_t unknown;
  unknown.mark = gho_string_create();
  unknown.extension = gho_string_create();
  return unknown;
}

/**
 * \brief Return a new osl1_extension_unknown with a mark
 * \param[in] mark A mark
 * \return a new osl1_extension_unknown
 */
osl1_extension_unknown_t osl1_extension_unknown_create_with_mark(
                                               const gho_string_t* const mark) {
  osl1_extension_unknown_t unknown = osl1_extension_unknown_create();
  gho_string_add(&unknown.mark, mark);
  if (unknown.mark.c_str[0] == '<') { gho_string_remove(&unknown.mark, 0); }
  if (unknown.mark.c_str[gho_string_size(&unknown.mark) - 1] == '>') {
    gho_string_remove_last(&unknown.mark);
  }
  return unknown;
}

/**
 * \brief Destroy an osl1_extension_unknown
 * \param[in] unknown An osl1_extension_unknown
 */
void osl1_extension_unknown_destroy(osl1_extension_unknown_t* unknown) {
  gho_string_destroy(&unknown->mark);
  gho_string_destroy(&unknown->extension);
}

/**
 * \brief Reset an osl1_extension_unknown
 * \param[in] unknown An osl1_extension_unknown
 */
void osl1_extension_unknown_reset(osl1_extension_unknown_t* unknown) {
  osl1_extension_unknown_destroy(unknown);
  *unknown = osl1_extension_unknown_create();
}

// Output

/**
 * \brief Print an osl1_extension_unknown in a file with indentation
 * \param[in] file    A C file
 * \param[in] unknown An osl1_extension_unknown
 * \param[in] indent  Indentation (number of spaces)
 */
void osl1_extension_unknown_fprinti(FILE* file,
                                  const osl1_extension_unknown_t* const unknown,
                                  const unsigned int indent) {
  gho_c_str_fprinti(file, "# Unknown extension\n", indent);
  gho_c_str_fprinti(file, "<", indent);
  gho_string_fprint(file, &unknown->mark);
  gho_c_str_fprint(file, ">\n");
  
  gho_string_fprint(file, &unknown->extension);
  
  gho_c_str_fprinti(file, "</", indent);
  gho_string_fprint(file, &unknown->mark);
  gho_c_str_fprint(file, ">");
}

/**
 * \brief Print an osl1_extension_unknown in a file
 * \param[in] file    A C file
 * \param[in] unknown An osl1_extension_unknown
 */
void osl1_extension_unknown_fprint(FILE* file,
                                const osl1_extension_unknown_t* const unknown) {
  osl1_extension_unknown_fprinti(file, unknown, 0);
}

/**
 * \brief Print an osl1_extension_unknown in stdout
 * \param[in] unknown An osl1_extension_unknown
 */
void osl1_extension_unknown_print(
                                const osl1_extension_unknown_t* const unknown) {
  osl1_extension_unknown_fprint(stdout, unknown);
}

/**
 * \brief Print an osl1_extension_unknown in a C string with indentation
 * \param[in] c_str   A C string
 * \param[in] unknown An osl1_extension_unknown
 * \param[in] indent  Indentation (number of spaces)
 */
void osl1_extension_unknown_sprinti(char** c_str,
                                  const osl1_extension_unknown_t* const unknown,
                                  const unsigned int indent) {
  gho_c_str_sprinti(c_str, "# Unknown extension\n", indent);
  gho_c_str_sprinti(c_str, "<", indent);
  gho_string_sprint(c_str, &unknown->mark);
  gho_c_str_sprint(c_str, ">\n");
  
  gho_string_sprint(c_str, &unknown->extension);
  
  gho_c_str_sprinti(c_str, "</", indent);
  gho_string_sprint(c_str, &unknown->mark);
  gho_c_str_sprint(c_str, ">");
}

/**
 * \brief Print an osl1_extension_unknown in a C string
 * \param[in] c_str   A C string
 * \param[in] unknown An osl1_extension_unknown
 */
void osl1_extension_unknown_sprint(char** c_str,
                                const osl1_extension_unknown_t* const unknown) {
  osl1_extension_unknown_sprinti(c_str, unknown, 0);
}

// Input

/**
 * \brief Read an osl1_extension_unknown from a file until end mark
 * \param[in] file A C file
 * \param[in] mark A mark
 * \return the osl1_extension_unknown read
 */
osl1_extension_unknown_t osl1_extension_unknown_fread_with_mark(FILE* file,
                                               const gho_string_t* const mark) {
  osl1_extension_unknown_t r = osl1_extension_unknown_create_with_mark(mark);
  
  gho_string_t line_peek = gho_string_peek_line(file);
  while (isspace(line_peek.c_str[0])) {
    gho_string_remove(&line_peek, 0);
  }
  while (
    gho_string_size(&line_peek) <= gho_string_size(mark) ||
    ( line_peek.c_str[0] == '<' && line_peek.c_str[1] == '/' &&
      gho_c_str_equal(line_peek.c_str + 2, mark->c_str + 1) ) == false
  ) {
    gho_string_t line = gho_string_get_line(file);
    gho_string_add(&r.extension, &line);
    gho_string_add_c_str(&r.extension, "\n");
    gho_string_destroy(&line);
    
    gho_string_destroy(&line_peek);
    line_peek = gho_string_peek_line(file);
    while (isspace(line_peek.c_str[0])) {
      gho_string_remove(&line_peek, 0);
    }
  }
  
  gho_string_destroy(&line_peek);
  
  return r;
}

/**
 * \brief Read an osl1_extension_unknown from a C string until end mark
 * \param[in] c_str A C string
 * \param[in] mark  A mark
 * \return the osl1_extension_unknown read
 */
osl1_extension_unknown_t osl1_extension_unknown_sread_with_mark(
                                               const char** c_str,
                                               const gho_string_t* const mark) {
  osl1_extension_unknown_t r = osl1_extension_unknown_create_with_mark(mark);
  
  gho_string_t line_peek = gho_string_peek_line_from_c_str(c_str);
  while (isspace(line_peek.c_str[0])) {
    gho_string_remove(&line_peek, 0);
  }
  while (
    gho_string_size(&line_peek) <= gho_string_size(mark) ||
    ( line_peek.c_str[0] == '<' && line_peek.c_str[1] == '/' &&
      gho_c_str_equal(line_peek.c_str + 2, mark->c_str + 1) ) == false
  ) {
    gho_string_t line = gho_string_get_line_from_c_str(c_str);
    gho_string_add(&r.extension, &line);
    gho_string_add_c_str(&r.extension, "\n");
    gho_string_destroy(&line);
    
    gho_string_destroy(&line_peek);
    line_peek = gho_string_peek_line_from_c_str(c_str);
    while (isspace(line_peek.c_str[0])) {
      gho_string_remove(&line_peek, 0);
    }
  }
  
  gho_string_destroy(&line_peek);
  
  return r;
}

// Copy & comparisons

/**
 * \brief Copy an osl1_extension_unknown
 * \param[in] unknown An osl1_extension_unknown
 * \return the osl1_extension_unknown copied
 */
osl1_extension_unknown_t osl1_extension_unknown_copy(
                                const osl1_extension_unknown_t* const unknown) {
  osl1_extension_unknown_t r;
  osl1_extension_unknown_copy_(unknown, &r);
  return r;
}

/**
 * \brief Copy an osl1_extension_unknown
 * \param[in] unknown An osl1_extension_unknown
 * \param[in] copy A pointer on an not initialized osl1_extension_unknown
 * \warning Do not use this function, use osl1_extension_unknown_copy
 */
void osl1_extension_unknown_copy_(const osl1_extension_unknown_t* const unknown,
                                  osl1_extension_unknown_t* copy) {
  gho_string_copy_(&unknown->mark, &copy->mark);
  gho_string_copy_(&unknown->extension, &copy->extension);
}

/**
 * \brief Equality between two osl1_extension_unknown
 * \param[in] a An osl1_extension_unknown
 * \param[in] b An osl1_extension_unknown
 * \return true if the osl1_extension_unknown are equals, false otherwise
 */
bool osl1_extension_unknown_equal(const osl1_extension_unknown_t* const a,
                                  const osl1_extension_unknown_t* const b) {
  return gho_string_equal(&a->mark, &b->mark) &&
         gho_string_equal(&a->extension, &b->extension);
}

// Conversion

/**
 * \brief Convert an osl1_extension_unknown into a gho_string
 * \param[in] unknown An osl1_extension_unknown
 * \return the gho_string from the osl1_extension_unknown
 */
gho_string_t osl1_extension_unknown_to_string(
                                const osl1_extension_unknown_t* const unknown) {
  gho_string_t s = gho_string_create();
  osl1_extension_unknown_sprint(&s.c_str, unknown);
  return s;
}
