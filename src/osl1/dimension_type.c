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

#include "../../include/osl1/dimension_type.h"


// Create & destroy

/**
 * \brief Return a new osl1_dimension_type_t
 * \return a new osl1_dimension_type_t
 */
osl1_dimension_type_t osl1_dimension_type_create() {
  osl1_dimension_type_t dimension_type;
  dimension_type.dimension_type = osl1_dimension_type_unknown;
  dimension_type.stripmined = false;
  dimension_type.parallel = false;
  dimension_type.vectorizable = false;
  return dimension_type;
}

/**
 * \brief Destroy an osl1_dimension_type_t
 * \param[in] dimension_type An osl1_dimension_type_t
 */
void osl1_dimension_type_destroy(osl1_dimension_type_t* dimension_type) {
  dimension_type->dimension_type = osl1_dimension_type_unknown;
  dimension_type->stripmined = false;
  dimension_type->parallel = false;
  dimension_type->vectorizable = false;
}

/**
 * \brief Reset an osl1_dimension_type_t
 * \param[in] dimension_type An osl1_dimension_type_t
 */
void osl1_dimension_type_reset(osl1_dimension_type_t* dimension_type) {
  osl1_dimension_type_destroy(dimension_type);
  *dimension_type = osl1_dimension_type_create();
}

// Output

/**
 * \brief Print an osl1_dimension_type_t in a file with indentation
 * \param[in] file           A C file
 * \param[in] dimension_type An osl1_dimension_type_t
 * \param[in] indent         Indentation (number of spaces)
 */
void osl1_dimension_type_fprinti(FILE* file,
                              const osl1_dimension_type_t* const dimension_type,
                              const unsigned int indent) {
  gho_fprinti(file, indent);
  fprintf(file, "{ ");
  if (dimension_type->dimension_type == osl1_dimension_type_alpha) {
    fprintf(file, "alpha");
  }
  else if (dimension_type->dimension_type == osl1_dimension_type_beta) {
    fprintf(file, "beta");
  }
  else {
    fprintf(file, "unknown");
  }
  if (dimension_type->stripmined) {
    fprintf(file, ", stripmined");
  }
  if (dimension_type->parallel) {
    fprintf(file, ", parallel");
  }
  if (dimension_type->vectorizable) {
    fprintf(file, ", vectorizable");
  }
  fprintf(file, " }");
}

/**
 * \brief Print an osl1_dimension_type_t in a file
 * \param[in] file           A C file
 * \param[in] dimension_type An osl1_dimension_type_t
 */
void osl1_dimension_type_fprint(FILE* file,
                  const osl1_dimension_type_t* const dimension_type) {
  osl1_dimension_type_fprinti(file, dimension_type, 0);
}

/**
 * \brief Print an osl1_dimension_type_t in stdout
 * \param[in] dimension_type An osl1_dimension_type_t
 */
void osl1_dimension_type_print(
                  const osl1_dimension_type_t* const dimension_type) {
  osl1_dimension_type_fprint(stdout, dimension_type);
}

/**
 * \brief Print an osl1_dimension_type_t in a C string with indentation
 * \param[in] c_str          A C string
 * \param[in] dimension_type An osl1_dimension_type_t
 * \param[in] indent         Indentation (number of spaces)
 */
void osl1_dimension_type_sprinti(char** c_str,
                    const osl1_dimension_type_t* const dimension_type,
                    const unsigned int indent) {
  gho_sprinti(c_str, indent);
  gho_c_str_sprint(c_str, "{ ");
  if (dimension_type->dimension_type == osl1_dimension_type_alpha) {
    gho_c_str_sprint(c_str, "alpha");
  }
  else if (dimension_type->dimension_type == osl1_dimension_type_beta) {
    gho_c_str_sprint(c_str, "beta");
  }
  else {
    gho_c_str_sprint(c_str, "unknown");
  }
  if (dimension_type->stripmined) {
    gho_c_str_sprint(c_str, ", stripmined");
  }
  if (dimension_type->parallel) {
    gho_c_str_sprint(c_str, ", parallel");
  }
  if (dimension_type->vectorizable) {
    gho_c_str_sprint(c_str, ", vectorizable");
  }
  gho_c_str_sprint(c_str, " }");
}

/**
 * \brief Print an osl1_dimension_type_t in a C string
 * \param[in] c_str          A C string
 * \param[in] dimension_type An osl1_dimension_type_t
 */
void osl1_dimension_type_sprint(char** c_str,
                  const osl1_dimension_type_t* const dimension_type) {
  osl1_dimension_type_sprinti(c_str, dimension_type, 0);
}

// Input

/**
 * \brief Read an osl1_dimension_type_t from a file in OpenScop format
 * \param[in] file A C file
 * \return the osl1_dimension_type_t read
 */
osl1_dimension_type_t osl1_dimension_type_fread(FILE* file) {
  osl1_dimension_type_t r = osl1_dimension_type_create();
  
  gho_read_whitespace(file);
  gho_char_fread(file); // Ignore '{'
  {
    gho_string_t alpha_or_beta = gho_string_fread(file);
    if (gho_string_contains_c_str(&alpha_or_beta, "alpha")) {
      r.dimension_type = osl1_dimension_type_alpha;
    }
    else if (gho_string_contains_c_str(&alpha_or_beta, "beta")) {
      r.dimension_type = osl1_dimension_type_beta;
    }
    gho_string_destroy(&alpha_or_beta);
  }
  gho_read_whitespace(file);
  while (gho_char_fpeek(file) != '}') {
    gho_string_t flag = gho_string_fread(file);
    if (gho_string_contains_c_str(&flag, "stripmined")) {
      r.stripmined = true;
    }
    else if (gho_string_contains_c_str(&flag, "parallel")) {
      r.parallel = true;
    }
    else if (gho_string_contains_c_str(&flag, "vectorizable")) {
      r.vectorizable = true;
    }
    gho_string_destroy(&flag);
    gho_read_whitespace(file);
  }
  gho_read_whitespace(file);
  gho_char_fread(file); // Ignore '}'
  
  return r;
}

/**
 * \brief Read an osl1_dimension_type_t from a C string in OpenScop format
 * \param[in] c_str A C string
 * \return the osl1_dimension_type_t read
 */
osl1_dimension_type_t osl1_dimension_type_sread(const char** c_str) {
  osl1_dimension_type_t r = osl1_dimension_type_create();
  
  gho_read_whitespace_from_c_str(c_str);
  gho_char_sread(c_str); // Ignore '{'
  {
    gho_string_t alpha_or_beta = gho_string_sread(c_str);
    if (gho_string_contains_c_str(&alpha_or_beta, "alpha")) {
      r.dimension_type = osl1_dimension_type_alpha;
    }
    else if (gho_string_contains_c_str(&alpha_or_beta, "beta")) {
      r.dimension_type = osl1_dimension_type_beta;
    }
    gho_string_destroy(&alpha_or_beta);
  }
  gho_read_whitespace_from_c_str(c_str);
  while (gho_char_speek(c_str) != '}') {
    gho_string_t flag = gho_string_sread(c_str);
    if (gho_string_contains_c_str(&flag, "stripmined")) {
      r.stripmined = true;
    }
    else if (gho_string_contains_c_str(&flag, "parallel")) {
      r.parallel = true;
    }
    else if (gho_string_contains_c_str(&flag, "vectorizable")) {
      r.vectorizable = true;
    }
    gho_string_destroy(&flag);
    gho_read_whitespace_from_c_str(c_str);
  }
  gho_read_whitespace_from_c_str(c_str);
  gho_char_sread(c_str); // Ignore '}'
  
  return r;
}

// Copy & comparisons

/**
 * \brief Copy an osl1_dimension_type
 * \param[in] dimension_type An osl1_dimension_type
 * \return the osl1_dimension_type copied
 */
osl1_dimension_type_t osl1_dimension_type_copy(
                  const osl1_dimension_type_t* const dimension_type) {
  return *dimension_type;
}

/**
 * \brief Copy an osl1_dimension_type
 * \param[in] dimension_type An osl1_dimension_type
 * \param[in] copy A pointer on an not initialized osl1_dimension_type
 * \warning Do not use this function, use osl1_dimension_type_copy
 */
void osl1_dimension_type_copy_(
                    const osl1_dimension_type_t* const dimension_type,
                    osl1_dimension_type_t* copy) {
  *copy = *dimension_type;
}

/**
 * \brief Equality between two osl1_dimension_type
 * \param[in] a An osl1_dimension_type
 * \param[in] b An osl1_dimension_type
 * \return true if the osl1_dimension_type are equals, false otherwise
 */
bool osl1_dimension_type_equal(const osl1_dimension_type_t* const a,
                                const osl1_dimension_type_t* const b) {
  return a->dimension_type == b->dimension_type &&
         a->stripmined == b->stripmined &&
         a->parallel == b->parallel &&
         a->vectorizable == b->vectorizable;
}

// Conversion

/**
 * \brief Convert an osl1_dimension_type into A gho_string
 * \param[in] dimension_type An osl1_dimension_type
 * \return the gho_string from the osl1_dimension_type
 */
gho_string_t osl1_dimension_type_to_string(
                  const osl1_dimension_type_t* const dimension_type) {
  gho_string_t r = gho_string_create();
  osl1_dimension_type_sprint(&r.c_str, dimension_type);
  return r;
}
