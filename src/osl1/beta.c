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


#include <stdlib.h>
#include <limits.h>

#include <gho/output.h>
#include <gho/c_str.h>
#include <gho/int/size_t.h>

#include "../../include/osl1/beta.h"
#include "../../include/osl1/equation.h"


// osl1_beta_element_t

/**
 * \brief Print a osl1_beta_element_t (size_t) in a file with indentation
 * \param[in] file   A C file
 * \param[in] i      A osl1_beta_element_t (size_t)
 * \param[in] indent indentation (number of spaces)
 */
void osl1_beta_element_fprinti(FILE* file, const size_t* const i,
                               const unsigned int indent) {
  gho_fprinti(file, indent);
  if (*i == osl1_beta_element_star) { gho_c_str_fprint(file, "*"); }
  else { gho_size_t_fprint(file, i); }
}

/**
 * \brief Print a osl1_beta_element_t (size_t) in a file
 * \param[in] file A C file
 * \param[in] i    A osl1_beta_element_t (size_t)
 */
void osl1_beta_element_fprint(FILE* file, const size_t* const i) {
  osl1_beta_element_fprinti(file, i, 0);
}

/**
 * \brief Print a osl1_beta_element_t (size_t)
 * \param[in] file A C file
 * \param[in] i    A osl1_beta_element_t (size_t)
 */
void osl1_beta_element_print(const size_t* const i) {
  osl1_beta_element_fprint(stdout, i);
}

/**
 * \brief Print a osl1_beta_element_t (size_t) in a C string with indentation
 * \param[in] c_str  A C string
 * \param[in] i      A osl1_beta_element_t (size_t)
 * \param[in] indent indentation (number of spaces)
 */
void osl1_beta_element_sprinti(char** c_str, const size_t* const i,
                               const unsigned int indent) {
  gho_sprinti(c_str, indent);
  if (*i == osl1_beta_element_star) { gho_c_str_sprint(c_str, "*"); }
  else { gho_size_t_sprint(c_str, i); }
}

/**
 * \brief Print a osl1_beta_element_t (size_t) in a C string
 * \param[in] c_str A C string
 * \param[in] i     A osl1_beta_element_t (size_t)
 */
void osl1_beta_element_sprint(char** c_str, const size_t* const i) {
  osl1_beta_element_sprinti(c_str, i, 0);
}

/**
 * @brief Read a osl1_beta_element_t from a file
 * @param[in] file A C file
 * @return the osl1_beta_element_t read
 */
size_t osl1_beta_element_fread(FILE* file) {
  gho_read_whitespace(file);
  if (gho_char_fpeek(file) == '*') {
    gho_char_fread(file); // *
    return osl1_beta_element_star;
  }
  else {
    return gho_size_t_fread(file);
  }
}

/**
 * @brief Read a osl1_beta_element_t from a C string
 * @param[in] c_str A C string
 * @return the osl1_beta_element_t read
 */
size_t osl1_beta_element_sread(const char** c_str) {
  gho_read_whitespace_from_c_str(c_str);
  if (gho_char_speek(c_str) == '*') {
    gho_char_sread(c_str); // *
    return osl1_beta_element_star;
  }
  else {
    return gho_size_t_sread(c_str);
  }
}

/**
 * \brief Convert a osl1_beta_element_t (size_t) into a gho_string
 * \param[in] i A osl1_beta_element_t (size_t)
 * \return the gho_string from the osl1_beta_element_t (size_t)
 */
gho_string_t osl1_beta_element_to_string(const size_t* const i) {
  gho_string_t r = gho_string_create();
  osl1_beta_element_sprint(&r.c_str, i);
  return r;
}


// Beta value & Beta prefix

/**
 * \brief Get the beta value of a beta equation
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i               Row index
 * \pre Equation i of the convex relation is a beta equation
 * \return the beta value of a beta equation
 */
size_t osl1_get_beta_value(const osl1_convex_relation_t* const convex_relation,
                           const size_t i) {
  #ifndef NDEBUG
    if (osl1_is_beta_equation(convex_relation, i) == false) {
      fprintf(stderr, "ERROR: osl1_get_beta_value "
                      "works only on beta equation\n");
      exit(1);
    }
  #endif
  
  const size_t nb_col = osl1_convex_relation_nb_col(convex_relation);
  gho_coperand_t tmp = osl1_convex_relation_cat(convex_relation, i, nb_col - 1);
  return gho_coperand_to_size_t(tmp);
}

/**
 * \brief Set the beta value of a beta equation
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i               Row index
 * \param[in] new_value       New beta value
 * \pre Equation i of the convex relation is a beta equation
 */
void osl1_set_beta_value(osl1_convex_relation_t* convex_relation,
                         const size_t i, const size_t new_value) {
  #ifndef NDEBUG
    if (osl1_is_beta_equation(convex_relation, i) == false) {
      fprintf(stderr, "ERROR: osl1_set_beta_value "
                      "works only on beta equation\n");
      exit(1);
    }
    if (new_value > LLONG_MAX) {
      fprintf(stderr, "ERROR: osl1_set_beta_value: overflow!\n");
      exit(1);
    }
  #endif
  
  const size_t nb_col = osl1_convex_relation_nb_col(convex_relation);
  osl1_convex_relation_set_lli(convex_relation, i, nb_col - 1,
                               (gho_llint)new_value);
}

/**
 * \brief Compare beta with a beta prefix
 * \param[in] beta        A beta
 * \param[in] beta_prefix A beta prefix
 * \return true if the beta prefix and the beta are the same except last value,
 *         false otherwise
 */
bool osl1_same_beta_prefix(const osl1_beta_t* const beta,
                           const osl1_beta_t* const beta_prefix) {
  if (beta_prefix->size == 0 ||
      beta_prefix->array[beta_prefix->size - 1] != osl1_beta_element_star) {
    fprintf(stderr, "ERROR: osl1_same_beta_prefix: "
                    "beta_prefix is not a beta prefix\n");
    exit(1);
  }
  
  if (beta_prefix->size > beta->size) { return false; }
  if (beta->size + 1 == beta_prefix->size) { return false; }
  
  for (size_t i = 0; i < beta_prefix->size - 1; ++i) {
    if (beta->array[i] != beta_prefix->array[i]) { return false; }
  }
  
  return true;
}

/**
 * \brief Beta to beta prefix
 * \param[in] beta        A beta
 * \param[in] beta_prefix A beta prefix
 */
void osl1_beta_to_beta_prefix(osl1_beta_t* beta) {
  if (beta->size == 0) {
    fprintf(stderr, "ERROR: osl1_beta_to_beta_prefix: beta is empty\n");
    exit(1);
  }
  else {
    beta->array[beta->size - 1] = osl1_beta_element_star;
  }
}
