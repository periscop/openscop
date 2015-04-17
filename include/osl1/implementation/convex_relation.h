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

#include <gho/c_str.h>

#include "../input.h"
#include "../extension.h"
#include "../id.h"


// Precision

gho_type_t* osl1_convex_relation_precision();

/**
 * \brief Return int precision used for osl1_convex_relation_t
 * \return int precision used for osl1_convex_relation_t
 */
gho_type_t osl1_convex_relation_get_precision() {
  gho_type_t* precision = osl1_convex_relation_precision();
  if (*precision == 0) {
    #ifdef osl_with_gmp
      *precision = GHO_TYPE_GHO_MPZ_T;
    #else
      *precision = GHO_TYPE_LLINT;
    #endif
  }
  return *precision;
}

/**
 * \brief Set int precision used for osl1_convex_relation_t
 * \param[in] precision gho type of the precision
 */
void osl1_convex_relation_set_precision(const gho_type_t type) {
  *osl1_convex_relation_precision() = type;
}

/**
 * \brief Set int precision used for osl1_convex_relation_t to long int
 */
void osl1_convex_relation_set_precision_lint() {
  osl1_convex_relation_set_precision(GHO_TYPE_LINT);
}

/**
 * \brief Set int precision used for osl1_convex_relation_t to long long int
 */
void osl1_convex_relation_set_precision_llint() {
  osl1_convex_relation_set_precision(GHO_TYPE_LLINT);
}

#ifdef osl_with_gmp

/**
 * \brief Set int precision used for osl1_convex_relation_t to mpz
 */
void osl1_convex_relation_set_precision_mpz() {
  osl1_convex_relation_set_precision(GHO_TYPE_GHO_MPZ_T);
}
#endif


// Create & destroy

/**
 * \brief Return a new osl1_convex_relation
 * \return a new osl1_convex_relation
 */
osl1_convex_relation_t osl1_convex_relation_create() {
  return osl1_convex_relation_create_args(0, 0, 0, 0, 0);
}

/**
 * \brief Return a new osl1_convex_relation
 * \param[in] nb_row        Number of rows
 * \param[in] nb_output_dim Number of ouput dimensions
 * \param[in] nb_input_dim  Number of input dimensions
 * \param[in] nb_local_dim  Number of local dimensions
 * \param[in] nb_parameter  Number of parameters
 * \return a new osl1_convex_relation
 */
osl1_convex_relation_t osl1_convex_relation_create_args(
                                                    size_t const nb_row,
                                                    size_t const nb_output_dim,
                                                    size_t const nb_input_dim,
                                                    size_t const nb_local_dim,
                                                    size_t const nb_parameter) {
  return osl1_convex_relation_create_args_and_int_type(
           nb_row, nb_output_dim, nb_input_dim, nb_local_dim, nb_parameter,
           osl1_convex_relation_get_precision());
}

/**
 * \brief Return a new osl1_convex_relation
 * \param[in] nb_row        Number of rows
 * \param[in] nb_output_dim Number of ouput dimensions
 * \param[in] nb_input_dim  Number of input dimensions
 * \param[in] nb_local_dim  Number of local dimensions
 * \param[in] nb_parameter  Number of parameters
 * \param[in] precision     Precision of osl1_mpint_t used
 * \return a new osl1_convex_relation
 */
osl1_convex_relation_t osl1_convex_relation_create_args_and_int_type(
                                                   size_t const nb_row,
                                                   size_t const nb_output_dim,
                                                   size_t const nb_input_dim,
                                                   size_t const nb_local_dim,
                                                   size_t const nb_parameter,
                                                   gho_type_t const precision) {
  osl1_convex_relation_t convex_relation;
  convex_relation.type = GHO_TYPE_OSL_CONVEX_RELATION;
  convex_relation.id = osl1_convex_relation_new_id();
  
  convex_relation.nb_output_dim = nb_output_dim;
  convex_relation.nb_input_dim = nb_input_dim;
  convex_relation.nb_local_dim = nb_local_dim;
  convex_relation.nb_parameter = nb_parameter;
  
  convex_relation.output_dims_types =
    osl1_vector_dimension_type_create_n(convex_relation.nb_output_dim);
  
  convex_relation.precision = precision;
  
  const size_t nb_col = nb_output_dim + nb_input_dim + nb_local_dim +
                        nb_parameter + 1 + 1;
  
  if (precision == GHO_TYPE_LINT) {
    convex_relation.matrix.li = gho_matrix_lint_create_n_m(nb_row, nb_col);
  }
  else if (precision == GHO_TYPE_LLINT) {
    convex_relation.matrix.lli = gho_matrix_llint_create_n_m(nb_row, nb_col);
  }
  #ifdef osl_with_gmp
  else if (precision == GHO_TYPE_GHO_MPZ_T) {
    convex_relation.matrix.mpz = gho_matrix_mpz_create_n_m(nb_row, nb_col);
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_create_args_and_int_type: "
                    "unknown precision!\n");
    exit(1);
  }
  
  convex_relation.extensions = gho_vector_any_create();
  
  return convex_relation;
}

/**
 * \brief Destroy an osl1_convex_relation
 * \param[in] convex_relation An osl1_convex_relation
 */
void osl1_convex_relation_destroy(osl1_convex_relation_t* convex_relation) {
  gho_size_t_destroy(&convex_relation->nb_output_dim);
  gho_size_t_destroy(&convex_relation->nb_input_dim);
  gho_size_t_destroy(&convex_relation->nb_local_dim);
  gho_size_t_destroy(&convex_relation->nb_parameter);
  
  osl1_vector_dimension_type_destroy(&convex_relation->output_dims_types);
  
  if (convex_relation->precision == GHO_TYPE_LINT) {
    gho_matrix_lint_destroy(&convex_relation->matrix.li);
  }
  else if (convex_relation->precision == GHO_TYPE_LLINT) {
    gho_matrix_llint_destroy(&convex_relation->matrix.lli);
  }
  #ifdef osl_with_gmp
  else if (convex_relation->precision == GHO_TYPE_GHO_MPZ_T) {
    gho_matrix_mpz_destroy(&convex_relation->matrix.mpz);
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_destroy: "
                    "unknown precision!\n");
    exit(1);
  }
  
  gho_vector_any_destroy(&convex_relation->extensions);
}

/**
 * \brief Reset an osl1_convex_relation
 * \param[in] convex_relation An osl1_convex_relation
 */
void osl1_convex_relation_reset(osl1_convex_relation_t* convex_relation) {
  osl1_convex_relation_destroy(convex_relation);
  *convex_relation = osl1_convex_relation_create();
}

// Output

// See "print_convex_relation.h"

// Input

/**
 * \brief Read an osl1_convex_relation from a file in OpenScop format
 * \param[in] file A C file
 * \return the osl1_convex_relation read
 */
osl1_convex_relation_t osl1_convex_relation_fread(FILE* file) {
  
  size_t nb_row = gho_size_t_fread(file);
  size_t nb_column = gho_size_t_fread(file);
  size_t nb_output_dim = gho_size_t_fread(file);
  size_t nb_input_dim = gho_size_t_fread(file);
  size_t nb_local_dim = gho_size_t_fread(file);
  size_t nb_parameter = gho_size_t_fread(file);
  osl1_skip_comments(file);
  
  osl1_convex_relation_t r = osl1_convex_relation_create_args(
    nb_row, nb_output_dim, nb_input_dim, nb_local_dim, nb_parameter);
  
  osl1_vector_dimension_type_destroy(&r.output_dims_types);
  r.output_dims_types = osl1_vector_dimension_type_fread(file);
  
  for (size_t i = 0; i < nb_row; ++i) {
    for (size_t j = 0; j < nb_column; ++j) {
      if (r.precision == GHO_TYPE_LINT) {
        gho_lint_destroy(&r.matrix.li.array[i][j]);
        r.matrix.li.array[i][j] = gho_lint_fread(file);
      }
      else if (r.precision == GHO_TYPE_LLINT) {
        gho_llint_destroy(&r.matrix.lli.array[i][j]);
        r.matrix.lli.array[i][j] = gho_llint_fread(file);
      }
      #ifdef osl_with_gmp
      else if (r.precision == GHO_TYPE_GHO_MPZ_T) {
        gho_mpz_destroy(&r.matrix.mpz.array[i][j]);
        r.matrix.mpz.array[i][j] = gho_mpz_fread(file);
      }
      #endif
      else {
        fprintf(stderr, "ERROR: osl1_convex_relation_fread_openscop: "
                        "unknown precision!\n");
        exit(1);
      }
      osl1_skip_comments(file);
    }
  }
  
  gho_vector_any_destroy(&r.extensions);
  r.extensions = osl1_extensions_fread(file);
  
  return r;
}

/**
 * \brief Read an osl1_convex_relation from a C string in OpenScop format
 * \param[in] c_str A C string
 * \return the osl1_convex_relation read
 */
osl1_convex_relation_t osl1_convex_relation_sread(const char** c_str) {
  
  size_t nb_row = gho_size_t_sread(c_str);
  size_t nb_column = gho_size_t_sread(c_str);
  size_t nb_output_dim = gho_size_t_sread(c_str);
  size_t nb_input_dim = gho_size_t_sread(c_str);
  size_t nb_local_dim = gho_size_t_sread(c_str);
  size_t nb_parameter = gho_size_t_sread(c_str);
  osl1_skip_comments_from_c_str(c_str);
  
  osl1_convex_relation_t r = osl1_convex_relation_create_args(
    nb_row, nb_output_dim, nb_input_dim, nb_local_dim, nb_parameter);
  
  osl1_vector_dimension_type_destroy(&r.output_dims_types);
  r.output_dims_types = osl1_vector_dimension_type_sread(c_str);
  
  for (size_t i = 0; i < nb_row; ++i) {
    for (size_t j = 0; j < nb_column; ++j) {
      if (r.precision == GHO_TYPE_LINT) {
        gho_lint_destroy(&r.matrix.li.array[i][j]);
        r.matrix.li.array[i][j] = gho_lint_sread(c_str);
      }
      else if (r.precision == GHO_TYPE_LLINT) {
        gho_llint_destroy(&r.matrix.lli.array[i][j]);
        r.matrix.lli.array[i][j] = gho_llint_sread(c_str);
      }
      #ifdef osl_with_gmp
      else if (r.precision == GHO_TYPE_GHO_MPZ_T) {
        gho_mpz_destroy(&r.matrix.mpz.array[i][j]);
        r.matrix.mpz.array[i][j] = gho_mpz_sread(c_str);
      }
      #endif
      else {
        fprintf(stderr, "ERROR: osl1_convex_relation_sread_openscop: "
                        "unknown precision!\n");
        exit(1);
      }
      osl1_skip_comments_from_c_str(c_str);
    }
  }
  
  gho_vector_any_destroy(&r.extensions);
  r.extensions = osl1_extensions_sread(c_str);
  
  return r;
}

// Copy & comparisons

/**
 * \brief Copy an osl1_convex_relation
 * \param[in] convex_relation An osl1_convex_relation
 * \return the osl1_convex_relation copied
 */
osl1_convex_relation_t osl1_convex_relation_copy(
                          const osl1_convex_relation_t* const convex_relation) {
  osl1_convex_relation_t r;
  osl1_convex_relation_copy_(convex_relation, &r);
  return r;
}

/**
 * \brief Copy an osl1_convex_relation
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] copy            A pointer on an not initialized
 *                            osl1_convex_relation
 * \warning Do not use this function, use osl1_convex_relation_copy
 */
void osl1_convex_relation_copy_(
                            const osl1_convex_relation_t* const convex_relation,
                            osl1_convex_relation_t* copy) {
  copy->type = convex_relation->type;
  copy->id = osl1_convex_relation_new_id();
  
  copy->nb_output_dim = convex_relation->nb_output_dim;
  copy->nb_input_dim = convex_relation->nb_input_dim;
  copy->nb_local_dim = convex_relation->nb_local_dim;
  copy->nb_parameter = convex_relation->nb_parameter;
  
  copy->output_dims_types =
    osl1_vector_dimension_type_copy(&convex_relation->output_dims_types);
  
  copy->precision = convex_relation->precision;
  
  if (convex_relation->precision == GHO_TYPE_LINT) {
    copy->matrix.li = gho_matrix_lint_copy(&convex_relation->matrix.li);
  }
  else if (convex_relation->precision == GHO_TYPE_LLINT) {
    copy->matrix.lli = gho_matrix_llint_copy(&convex_relation->matrix.lli);
  }
  #ifdef osl_with_gmp
  else if (convex_relation->precision == GHO_TYPE_GHO_MPZ_T) {
    copy->matrix.mpz = gho_matrix_mpz_copy(&convex_relation->matrix.mpz);
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_copy_: unknown precision!\n");
    exit(1);
  }
  
  copy->extensions = gho_vector_any_copy(&convex_relation->extensions);
}

/**
 * \brief Equality between two osl1_convex_relation
 * \param[in] a An osl1_convex_relation
 * \param[in] b An osl1_convex_relation
 * \return true if the osl1_convex_relation are equals, false otherwise
 */
bool osl1_convex_relation_equal(const osl1_convex_relation_t* const a,
                          const osl1_convex_relation_t* const b) {
  if (a->type != b->type) { return false; }
  if (a->nb_output_dim != b->nb_output_dim) { return false; }
  if (a->nb_input_dim != b->nb_input_dim) { return false; }
  if (a->nb_local_dim != b->nb_local_dim) { return false; }
  if (a->nb_parameter != b->nb_parameter) { return false; }
  
  if (osl1_vector_dimension_type_equal(&a->output_dims_types,
                                       &b->output_dims_types) == false) {
    return false;
  }
  
  if (a->precision == b->precision) {
    if (a->precision == GHO_TYPE_LINT) {
      if (gho_matrix_lint_equal(&a->matrix.li, &b->matrix.li) == false) {
        return false;
      }
    }
    else if (a->precision == GHO_TYPE_LLINT) {
      if (gho_matrix_llint_equal(&a->matrix.lli, &b->matrix.lli) == false) {
        return false;
      }
    }
    #ifdef osl_with_gmp
    else if (a->precision == GHO_TYPE_GHO_MPZ_T) {
      if (gho_matrix_mpz_equal(&a->matrix.mpz, &b->matrix.mpz) == false) {
        return false;
      }
    }
    #endif
    else {
      fprintf(stderr, "ERROR: osl1_convex_relation_equal: unknown precision!\n");
      exit(1);
    }
  }
  else {
    // TODO Compare two osl1_convex_relation_t without same precision
    fprintf(stderr, "ERROR: osl1_convex_relation_equal IS NOT FULLY IMPLEMENTED!\n");
    exit(1);
  }
  
  if (gho_vector_any_equal(&a->extensions, &b->extensions) == false) {
    return false;
  }
  
  return true;
}

// Conversion

/**
 * \brief Convert an osl1_convex_relation into a gho_string
 * \param[in] convex_relation An osl1_convex_relation
 * \return the gho_string from the osl1_convex_relation
 */
gho_string_t osl1_convex_relation_to_string(
                                     const osl1_convex_relation_t* const convex_relation) {
  gho_string_t r = gho_string_create();
  osl1_convex_relation_sprint(&r.c_str, convex_relation);
  return r;
}

/**
 * \brief Convert an osl1_convex_relation into a gho_any
 * \param[in] convex_relation An osl1_convex_relation
 * \return the gho_any from the osl1_convex_relation
 */
gho_any_t osl1_convex_relation_to_any(const osl1_convex_relation_t* const convex_relation) {
  gho_any_t r = gho_any_create();
  r.type = GHO_TYPE_OSL_CONVEX_RELATION;
  r.size_of_struct = sizeof(osl1_convex_relation_t);
  osl1_convex_relation_t* p = gho_alloc(osl1_convex_relation_t);
  osl1_convex_relation_copy_(convex_relation, p);
  r.any = p; p = NULL;
  r.destroy_fct = (gho_destroy_fct_t)osl1_convex_relation_destroy;
  r.fprinti_fct = (gho_fprinti_fct_t)osl1_convex_relation_fprinti;
  r.sprinti_fct = (gho_sprinti_fct_t)osl1_convex_relation_sprinti;
  r.copy_fct = (gho_copy_fct_t)osl1_convex_relation_copy_;
  r.equal_fct = (gho_equal_fct_t)osl1_convex_relation_equal;
  r.to_string_fct = (gho_to_string_fct_t)osl1_convex_relation_to_string;
  return r;
}

// Size

/**
 * \brief Return the number of rows
 * \param[in] convex_relation An osl1_convex_relation
 * \return the number of rows
 */
size_t osl1_convex_relation_nb_row(const osl1_convex_relation_t* const convex_relation) {
  if (convex_relation->precision == GHO_TYPE_LINT) {
    return convex_relation->matrix.li.nb_row;
  }
  else if (convex_relation->precision == GHO_TYPE_LLINT) {
    return convex_relation->matrix.lli.nb_row;
  }
  #ifdef osl_with_gmp
  else if (convex_relation->precision == GHO_TYPE_GHO_MPZ_T) {
    return convex_relation->matrix.mpz.nb_row;
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_nb_row: unknown precision!\n");
    exit(1);
  }
}

/**
 * \brief Return the number of columns
 * \param[in] convex_relation An osl1_convex_relation
 * \return the number of columns
 */
size_t osl1_convex_relation_nb_col(const osl1_convex_relation_t* const convex_relation) {
  if (convex_relation->precision == GHO_TYPE_LINT) {
    return convex_relation->matrix.li.nb_col;
  }
  else if (convex_relation->precision == GHO_TYPE_LLINT) {
    return convex_relation->matrix.lli.nb_col;
  }
  #ifdef osl_with_gmp
  else if (convex_relation->precision == GHO_TYPE_GHO_MPZ_T) {
    return convex_relation->matrix.mpz.nb_col;
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_nb_col: unknown precision!\n");
    exit(1);
  }
}

/**
 * \brief The osl1_convex_relation is empty?
 * \param[in] convex_relation An osl1_convex_relation
 * \return true if the osl1_convex_relation is empty, false otherwise
 */
bool osl1_convex_relation_empty(const osl1_convex_relation_t* const convex_relation) {
  return osl1_convex_relation_nb_row(convex_relation) == 0 ||
         osl1_convex_relation_nb_col(convex_relation) == 0;
}

// At

/**
 * \brief Return a gho_operand_t on the element i, j of the convex relation
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] i               Row index
 * \param[in] j               Column index
 * \return a gho_operand_t on the element i, j of the convex relation
 */
gho_operand_t osl1_convex_relation_at(osl1_convex_relation_t* convex_relation,
                                      const size_t i, const size_t j) {
  if (convex_relation->precision == GHO_TYPE_LINT) {
    return gho_operand_i_j(&convex_relation->matrix.li, i, j);
  }
  else if (convex_relation->precision == GHO_TYPE_LLINT) {
    return gho_operand_i_j(&convex_relation->matrix.lli, i, j);
  }
  #ifdef osl_with_gmp
  else if (convex_relation->precision == GHO_TYPE_GHO_MPZ_T) {
    return gho_operand_i_j(&convex_relation->matrix.mpz, i, j);
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_at: unknown precision!\n");
    exit(1);
  }
  return gho_operand_create();
}

/**
 * \brief Return a gho_coperand_t on the element i, j of the convex relation
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] i               Row index
 * \param[in] j               Column index
 * \return a gho_coperand_t on the element i, j of the convex relation
 */
gho_coperand_t osl1_convex_relation_cat(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i, const size_t j) {
  if (convex_relation->precision == GHO_TYPE_LINT) {
    return gho_coperand_i_j(&convex_relation->matrix.li, i, j);
  }
  else if (convex_relation->precision == GHO_TYPE_LLINT) {
    return gho_coperand_i_j(&convex_relation->matrix.lli, i, j);
  }
  #ifdef osl_with_gmp
  else if (convex_relation->precision == GHO_TYPE_GHO_MPZ_T) {
    return gho_coperand_i_j(&convex_relation->matrix.mpz, i, j);
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_cat: unknown precision!\n");
    exit(1);
  }
  return gho_coperand_create();
}

/**
 * \brief Print convex_relation[i][j] in a file
 * \param[in] file            A file
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] i               Row index
 * \param[in] j               Column index
 */
void osl1_convex_relation_at_fprint(FILE* file,
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i, const size_t j) {
  gho_coperand_t cop = osl1_convex_relation_cat(convex_relation, i, j);
  gho_coperand_fprint(file, &cop);
}

/**
 * \brief Print convex_relation[i][j] in a C string
 * \param[in] c_str           A C string
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] i               Row index
 * \param[in] j               Column index
 */
void osl1_convex_relation_at_sprint(char** c_str,
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i, const size_t j) {
  gho_coperand_t cop = osl1_convex_relation_cat(convex_relation, i, j);
  gho_coperand_sprint(c_str, &cop);
}

// Is

/**
 * \brief convex_relation[i][j] == 0
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] i               Row index
 * \param[in] j               Column index
 * \return convex_relation[i][j] == 0
 */
bool osl1_convex_relation_is_0(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i, const size_t j) {
  gho_coperand_t cop = osl1_convex_relation_cat(convex_relation, i, j);
  return gho_cop_is_0(cop);
}

/**
 * \brief convex_relation[i][j] == 1
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] i               Row index
 * \param[in] j               Column index
 * \return convex_relation[i][j] == 1
 */
bool osl1_convex_relation_is_1(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i, const size_t j) {
  gho_coperand_t cop = osl1_convex_relation_cat(convex_relation, i, j);
  return gho_cop_is_1(cop);
}

/**
 * \brief convex_relation[i][j] == -1
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] i               Row index
 * \param[in] j               Column index
 * \return convex_relation[i][j] == -1
 */
bool osl1_convex_relation_is_minus_1(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i, const size_t j) {
  gho_coperand_t cop = osl1_convex_relation_cat(convex_relation, i, j);
  return gho_cop_is_minus_1(cop);
}

// Set

/**
 * \brief convex_relation[i][j] = 0
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] i               Row index
 * \param[in] j               Column index
 */
void osl1_convex_relation_set_0(osl1_convex_relation_t* convex_relation,
                                const size_t i, const size_t j) {
  gho_operand_t op = osl1_convex_relation_at(convex_relation, i, j);
  gho_set_0(op);
}

/**
 * \brief convex_relation[i][j] = 1
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] i               Row index
 * \param[in] j               Column index
 */
void osl1_convex_relation_set_1(osl1_convex_relation_t* convex_relation,
                                const size_t i, const size_t j) {
  gho_operand_t op = osl1_convex_relation_at(convex_relation, i, j);
  gho_set_1(op);
}

/**
 * \brief convex_relation[i][j] = -1
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] i               Row index
 * \param[in] j               Column index
 */
void osl1_convex_relation_set_minus_1(osl1_convex_relation_t* convex_relation,
                                      const size_t i, const size_t j) {
  gho_operand_t op = osl1_convex_relation_at(convex_relation, i, j);
  gho_set_minus_1(op);
}

/**
 * \brief convex_relation[i][j] = value
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] i               Row index
 * \param[in] j               Column index
 * \param[in] value           A gho_llint
 */
void osl1_convex_relation_set_lli(osl1_convex_relation_t* convex_relation,
                                  const size_t i, const size_t j,
                                  const gho_llint value) {
  gho_operand_t op = osl1_convex_relation_at(convex_relation, i, j);
  gho_set_lli(op, value);
}

// Add (column)

/**
 * \brief Add a dimension at the end
 * \param[in] convex_relation An osl1_convex_relation_t
 * \warning Do not use this function, use osl1_convex_relation_add_output_dim,
 *          osl1_convex_relation_add_input_dim,
 *          osl1_convex_relation_add_local_dim and
 *          osl1_convex_relation_add_parameter functions
 */
void osl1_convex_relation_add_col_(osl1_convex_relation_t* convex_relation) {
  if (convex_relation->precision == GHO_TYPE_LINT) {
    gho_matrix_lint_add_col(&convex_relation->matrix.li);
  }
  else if (convex_relation->precision == GHO_TYPE_LLINT) {
    gho_matrix_llint_add_col(&convex_relation->matrix.lli);
  }
  #ifdef osl_with_gmp
  else if (convex_relation->precision == GHO_TYPE_GHO_MPZ_T) {
    gho_matrix_mpz_add_col(&convex_relation->matrix.mpz);
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_add_col_before_: "
                    "unknown precision!\n");
    exit(1);
  }
}

/**
 * \brief Add a dimension before a column index
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] j               Column index
 * \warning Do not use this function, use osl1_convex_relation_add_output_dim,
 *          osl1_convex_relation_add_input_dim,
 *          osl1_convex_relation_add_local_dim and
 *          osl1_convex_relation_add_parameter functions
 */
void osl1_convex_relation_add_col_before_(
                                        osl1_convex_relation_t* convex_relation,
                                        const size_t j) {
  if (convex_relation->precision == GHO_TYPE_LINT) {
    gho_matrix_lint_add_col_before(&convex_relation->matrix.li, j);
  }
  else if (convex_relation->precision == GHO_TYPE_LLINT) {
    gho_matrix_llint_add_col_before(&convex_relation->matrix.lli, j);
  }
  #ifdef osl_with_gmp
  else if (convex_relation->precision == GHO_TYPE_GHO_MPZ_T) {
    gho_matrix_mpz_add_col_before(&convex_relation->matrix.mpz, j);
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_add_col_before_: "
                    "unknown precision!\n");
    exit(1);
  }
}

/**
 * \brief Add a dimension after a column index
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] j               Column index
 * \warning Do not use this function, use osl1_convex_relation_add_output_dim,
 *          osl1_convex_relation_add_input_dim,
 *          osl1_convex_relation_add_local_dim and
 *          osl1_convex_relation_add_parameter functions
 */
void osl1_convex_relation_add_col_after_(
                                        osl1_convex_relation_t* convex_relation,
                                        const size_t j) {
  if (convex_relation->precision == GHO_TYPE_LINT) {
    gho_matrix_lint_add_col_after(&convex_relation->matrix.li, j);
  }
  else if (convex_relation->precision == GHO_TYPE_LLINT) {
    gho_matrix_llint_add_col_after(&convex_relation->matrix.lli, j);
  }
  #ifdef osl_with_gmp
  else if (convex_relation->precision == GHO_TYPE_GHO_MPZ_T) {
    gho_matrix_mpz_add_col_after(&convex_relation->matrix.mpz, j);
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_add_col_after_: "
                    "unknown precision!\n");
    exit(1);
  }
}

/**
 * \brief Add an output dimension
 * \param[in] convex_relation An osl1_convex_relation_t
 */
void osl1_convex_relation_add_output_dim(osl1_convex_relation_t* convex_relation) {
  const size_t j = convex_relation->nb_output_dim;
  osl1_convex_relation_add_col_after_(convex_relation, j);
  ++convex_relation->nb_output_dim;
}

/**
 * \brief Add an output dimension before a column index
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i_output_dim    Output dimension index
 */
void osl1_convex_relation_add_output_dim_before(
                                      osl1_convex_relation_t* convex_relation,
                                      const size_t i_output_dim) {
  #ifndef NDEBUG
    if (i_output_dim > convex_relation->nb_output_dim) {
      fprintf(stderr, "ERROR: osl1_convex_relation_add_output_dim_before: "
                      "i_output_dim is invalid!\n");
      exit(1);
    }
  #endif
  osl1_convex_relation_add_col_before_(convex_relation, i_output_dim + 1);
  ++convex_relation->nb_output_dim;
}

/**
 * \brief Add an output dimension after a column index
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i_output_dim    Output dimension index
 */
void osl1_convex_relation_add_output_dim_after(
                                      osl1_convex_relation_t* convex_relation,
                                      const size_t i_output_dim) {
  #ifndef NDEBUG
    if (i_output_dim >= convex_relation->nb_output_dim) {
      fprintf(stderr, "ERROR: osl1_convex_relation_add_output_dim_after: "
                      "i_output_dim is invalid!\n");
      exit(1);
    }
  #endif
  osl1_convex_relation_add_col_after_(convex_relation, i_output_dim + 1);
  ++convex_relation->nb_output_dim;
}

/**
 * \brief Add an input dimension
 * \param[in] convex_relation An osl1_convex_relation_t
 */
void osl1_convex_relation_add_input_dim(osl1_convex_relation_t* convex_relation) {
  const size_t j = convex_relation->nb_output_dim +
                   convex_relation->nb_input_dim;
  osl1_convex_relation_add_col_after_(convex_relation, j);
  ++convex_relation->nb_input_dim;
}

/**
 * \brief Add a local dimension
 * \param[in] convex_relation An osl1_convex_relation_t
 */
void osl1_convex_relation_add_local_dim(osl1_convex_relation_t* convex_relation) {
  const size_t j = convex_relation->nb_output_dim +
                   convex_relation->nb_input_dim +
                   convex_relation->nb_local_dim;
  osl1_convex_relation_add_col_after_(convex_relation, j);
  ++convex_relation->nb_local_dim;
}

/**
 * \brief Add a parameter dimension
 * \param[in] convex_relation An osl1_convex_relation_t
 */
void osl1_convex_relation_add_parameter(osl1_convex_relation_t* convex_relation) {
  const size_t j = convex_relation->nb_output_dim +
                   convex_relation->nb_input_dim +
                   convex_relation->nb_local_dim +
                   convex_relation->nb_parameter;
  osl1_convex_relation_add_col_after_(convex_relation, j);
  ++convex_relation->nb_parameter;
}

/**
 * \brief Add equation 0 = 0 after a row index
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i               Row index
 */
void osl1_convex_relation_add_equation_after(
                      osl1_convex_relation_t* convex_relation, const size_t i) {
  if (convex_relation->precision == GHO_TYPE_LINT) {
    gho_matrix_lint_add_row_after(&convex_relation->matrix.li, i);
  }
  else if (convex_relation->precision == GHO_TYPE_LLINT) {
    gho_matrix_llint_add_row_after(&convex_relation->matrix.lli, i);
  }
  #ifdef osl_with_gmp
  else if (convex_relation->precision == GHO_TYPE_GHO_MPZ_T) {
    gho_matrix_mpz_add_row_after(&convex_relation->matrix.mpz, i);
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_add_equation_after: "
                    "unknown precision!\n");
    exit(1);
  }
}

/**
 * \brief Add equation 0 = 0 before a row index
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i               Row index
 */
void osl1_convex_relation_add_equation_before(
                      osl1_convex_relation_t* convex_relation, const size_t i) {
  if (convex_relation->precision == GHO_TYPE_LINT) {
    gho_matrix_lint_add_row_before(&convex_relation->matrix.li, i);
  }
  else if (convex_relation->precision == GHO_TYPE_LLINT) {
    gho_matrix_llint_add_row_before(&convex_relation->matrix.lli, i);
  }
  #ifdef osl_with_gmp
  else if (convex_relation->precision == GHO_TYPE_GHO_MPZ_T) {
    gho_matrix_mpz_add_row_before(&convex_relation->matrix.mpz, i);
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_add_equation_before: "
                    "unknown precision!\n");
    exit(1);
  }
}

// Add (row)

/**
 * \brief Add row at the end
 * \param[in] convex_relation An osl1_convex_relation_t
 */
void osl1_convex_relation_add_row_(osl1_convex_relation_t* convex_relation) {
  if (convex_relation->precision == GHO_TYPE_LINT) {
    gho_matrix_lint_add_row(&convex_relation->matrix.li);
  }
  else if (convex_relation->precision == GHO_TYPE_LLINT) {
    gho_matrix_llint_add_row(&convex_relation->matrix.lli);
  }
  #ifdef osl_with_gmp
  else if (convex_relation->precision == GHO_TYPE_GHO_MPZ_T) {
    gho_matrix_mpz_add_row(&convex_relation->matrix.mpz);
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_add_row_: "
                    "unknown precision!\n");
    exit(1);
  }
}

/**
 * \brief Add a row before a row index
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i               Row index
 */
void osl1_convex_relation_add_row_before_(
                                        osl1_convex_relation_t* convex_relation,
                                        const size_t i) {
  if (convex_relation->precision == GHO_TYPE_LINT) {
    gho_matrix_lint_add_row_before(&convex_relation->matrix.li, i);
  }
  else if (convex_relation->precision == GHO_TYPE_LLINT) {
    gho_matrix_llint_add_row_before(&convex_relation->matrix.lli, i);
  }
  #ifdef osl_with_gmp
  else if (convex_relation->precision == GHO_TYPE_GHO_MPZ_T) {
    gho_matrix_mpz_add_row_before(&convex_relation->matrix.mpz, i);
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_row_col_before_: "
                    "unknown precision!\n");
    exit(1);
  }
}

/**
 * \brief Add a row after a row index
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i               Row index
 */
void osl1_convex_relation_add_row_after_(
                                        osl1_convex_relation_t* convex_relation,
                                        const size_t i) {
  if (convex_relation->precision == GHO_TYPE_LINT) {
    gho_matrix_lint_add_row_after(&convex_relation->matrix.li, i);
  }
  else if (convex_relation->precision == GHO_TYPE_LLINT) {
    gho_matrix_llint_add_row_after(&convex_relation->matrix.lli, i);
  }
  #ifdef osl_with_gmp
  else if (convex_relation->precision == GHO_TYPE_GHO_MPZ_T) {
    gho_matrix_mpz_add_row_after(&convex_relation->matrix.mpz, i);
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_row_col_after_: "
                    "unknown precision!\n");
    exit(1);
  }
}

// Remove

/**
 * \brief Remove a dimension (column)
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] j               Dimension (column) index
 */
void osl1_convex_relation_remove_dim(
                      osl1_convex_relation_t* convex_relation, const size_t j) {
  if (j == 0) {
    fprintf(stderr, "ERROR: osl1_convex_relation_remove_dim: "
                    "can not remove (in)equation column!\n");
    exit(1);
  }
  if (j == osl1_convex_relation_nb_col(convex_relation) - 1) {
    fprintf(stderr, "ERROR: osl1_convex_relation_remove_dim: "
                    "can not remove constant column!\n");
    exit(1);
  }
  
  if (convex_relation->precision == GHO_TYPE_LINT) {
    gho_matrix_lint_remove_col(&convex_relation->matrix.li, j);
  }
  else if (convex_relation->precision == GHO_TYPE_LLINT) {
    gho_matrix_llint_remove_col(&convex_relation->matrix.lli, j);
  }
  #ifdef osl_with_gmp
  else if (convex_relation->precision == GHO_TYPE_GHO_MPZ_T) {
    gho_matrix_mpz_remove_col(&convex_relation->matrix.mpz, j);
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_remove_col_: "
                    "unknown precision!\n");
    exit(1);
  }
  
  if (osl1_convex_relation_is_output_dim(convex_relation, j)) {
    --convex_relation->nb_output_dim;
  }
  else if (osl1_convex_relation_is_input_dim(convex_relation, j)) {
    --convex_relation->nb_input_dim;
  }
  else if (osl1_convex_relation_is_local_dim(convex_relation, j)) {
    --convex_relation->nb_local_dim;
  }
  else if (osl1_convex_relation_is_parameter_dim(convex_relation, j)) {
    --convex_relation->nb_parameter;
  }
}

/**
 * \brief Remove an output dimension
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i_output_dim    Output dimension (column) index
 */
void osl1_convex_relation_remove_output_dim(
           osl1_convex_relation_t* convex_relation, const size_t i_output_dim) {
  const size_t j =
    osl1_convex_relation_output_dim_to_j(convex_relation, i_output_dim);
  osl1_convex_relation_remove_dim(convex_relation, j);
}

/**
 * \brief Remove an input dimension
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i_input_dim     Input dimension (column) index
 */
void osl1_convex_relation_remove_input_dim(
            osl1_convex_relation_t* convex_relation, const size_t i_input_dim) {
  const size_t j =
    osl1_convex_relation_input_dim_to_j(convex_relation, i_input_dim);
  osl1_convex_relation_remove_dim(convex_relation, j);
}

/**
 * \brief Remove a local dimension
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i_local_dim     Local dimension (column) index
 */
void osl1_convex_relation_remove_local_dim(
            osl1_convex_relation_t* convex_relation, const size_t i_local_dim) {
  const size_t j =
    osl1_convex_relation_local_dim_to_j(convex_relation, i_local_dim);
  osl1_convex_relation_remove_dim(convex_relation, j);
}

/**
 * \brief Remove a parameter dimension
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i_parameter     Parameter (column) index
 */
void osl1_convex_relation_remove_parameter_dim(
            osl1_convex_relation_t* convex_relation, const size_t i_parameter) {
  const size_t j =
    osl1_convex_relation_parameter_dim_to_j(convex_relation, i_parameter);
  osl1_convex_relation_remove_dim(convex_relation, j);
}

/**
 * \brief Remove a (in)equation
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i               (In)equation index
 */
void osl1_convex_relation_remove_constraint(
                      osl1_convex_relation_t* convex_relation, const size_t i) {
  if (convex_relation->precision == GHO_TYPE_LINT) {
    gho_matrix_lint_remove_row(&convex_relation->matrix.li, i);
  }
  else if (convex_relation->precision == GHO_TYPE_LLINT) {
    gho_matrix_llint_remove_row(&convex_relation->matrix.lli, i);
  }
  #ifdef osl_with_gmp
  else if (convex_relation->precision == GHO_TYPE_GHO_MPZ_T) {
    gho_matrix_mpz_remove_row(&convex_relation->matrix.mpz, i);
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_remove_constraint: "
                    "unknown precision!\n");
    exit(1);
  }
}

// Index

/**
 * \brief Column index is an output dimension?
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] j               Column index
 * \return true if column index is an output dimension, false otherwise
 */
bool osl1_convex_relation_is_output_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t j) {
  if (convex_relation->nb_output_dim  == 0) {
    return false;
  }
  return j >= 1 &&
         j <= convex_relation->nb_output_dim;
}

/**
 * \brief Column index is an input dimension?
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] j               Column index
 * \return true if column index is an input dimension, false otherwise
 */
bool osl1_convex_relation_is_input_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t j) {
  if (convex_relation->nb_input_dim  == 0) {
    return false;
  }
  return j >= 1 + convex_relation->nb_output_dim &&
         j <= convex_relation->nb_output_dim + convex_relation->nb_input_dim;
}

/**
 * \brief Column index is a local dimension?
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] j               Column index
 * \return true if column index is a local dimension, false otherwise
 */
bool osl1_convex_relation_is_local_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t j) {
  if (convex_relation->nb_local_dim  == 0) {
    return false;
  }
  return j >= 1 + convex_relation->nb_output_dim +
              convex_relation->nb_input_dim &&
         j <= convex_relation->nb_output_dim + convex_relation->nb_input_dim +
              convex_relation->nb_local_dim;
}

/**
 * \brief Column index is a paramater dimension?
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] j               Column index
 * \return true if column index is a paramater dimension, false otherwise
 */
bool osl1_convex_relation_is_parameter_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t j) {
  if (convex_relation->nb_parameter  == 0) {
    return false;
  }
  return j >= 1 + convex_relation->nb_output_dim +
              convex_relation->nb_input_dim + convex_relation->nb_local_dim &&
         j <= convex_relation->nb_output_dim + convex_relation->nb_input_dim +
              convex_relation->nb_local_dim + convex_relation->nb_parameter;
}

/**
 * \brief Compute global column index of an output dimension
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i_output_dim    Output dimension (column) index
 * \return global column index of an output dimension
 */
size_t osl1_convex_relation_output_dim_to_j(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i_output_dim) {
  if (convex_relation->nb_output_dim == 0) {
    fprintf(stderr, "ERROR: osl1_convex_relation_output_dim_to_j: "
                    "number of output dimensions is 0!\n");
    exit(1);
  }
  return 1 + i_output_dim;
}

/**
 * \brief Compute global column index of an input dimension
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i_input_dim     Input dimension (column) index
 * \return global column index of an input dimension
 */
size_t osl1_convex_relation_input_dim_to_j(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i_input_dim) {
  if (convex_relation->nb_input_dim == 0) {
    fprintf(stderr, "ERROR: osl1_convex_relation_input_dim_to_j: "
                    "number of input dimensions is 0!\n");
    exit(1);
  }
  return 1 + convex_relation->nb_output_dim + i_input_dim;
}

/**
 * \brief Compute global column index of a local dimension
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i_local_dim     Local dimension (column) index
 * \return global column index of a local dimension
 */
size_t osl1_convex_relation_local_dim_to_j(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i_local_dim) {
  if (convex_relation->nb_local_dim == 0) {
    fprintf(stderr, "ERROR: osl1_convex_relation_local_dim_to_j: "
                    "number of local dimensions is 0!\n");
    exit(1);
  }
  return 1 + convex_relation->nb_output_dim + convex_relation->nb_input_dim +
         i_local_dim;
}

/**
 * \brief Compute global column index of a parameter dimension
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i_parameter     Parameter (column) index
 * \return global column index of a parameter dimension
 */
size_t osl1_convex_relation_parameter_dim_to_j(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i_parameter) {
  if (convex_relation->nb_parameter == 0) {
    fprintf(stderr, "ERROR: osl1_convex_relation_parameter_dim_to_j: "
                    "number of parameter dimensions is 0!\n");
    exit(1);
  }
  return 1 + convex_relation->nb_output_dim + convex_relation->nb_input_dim +
         convex_relation->nb_local_dim + i_parameter;
}

/**
 * \brief Compute output dimension index of a global column
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] j               Global column index
 * \return output dimension index of a global column
 */
size_t osl1_convex_relation_j_to_output_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t j) {
  const size_t r = j - 1;
  if (convex_relation->nb_output_dim == 0 ||
      r > osl1_convex_relation_output_dim_to_j(convex_relation,
                                              convex_relation->nb_output_dim)
  ) {
    fprintf(stderr, "ERROR: osl1_convex_relation_j_to_output_dim: "
                    "number of output dimensions is 0!\n");
    exit(1);
  }
  return r;
}

/**
 * \brief Compute input dimension index of a global column
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] j               Global column index
 * \return input dimension index of a global column
 */
size_t osl1_convex_relation_j_to_input_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t j) {
  const size_t r = j - 1 - convex_relation->nb_output_dim;
  if (convex_relation->nb_input_dim == 0 ||
      r > osl1_convex_relation_input_dim_to_j(convex_relation,
                                              convex_relation->nb_input_dim)
  ) {
    fprintf(stderr, "ERROR: osl1_convex_relation_j_to_input_dim: "
                    "number of input dimensions is 0!\n");
    exit(1);
  }
  return r;
}

/**
 * \brief Compute local dimension index of a global column
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] j               Global column index
 * \return local dimension index of a global column
 */
size_t osl1_convex_relation_j_to_local_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t j) {
  const size_t r = j - 1 - convex_relation->nb_output_dim -
                   convex_relation->nb_input_dim;
  if (convex_relation->nb_local_dim == 0 ||
      r > osl1_convex_relation_local_dim_to_j(convex_relation,
                                              convex_relation->nb_local_dim)
  ) {
    fprintf(stderr, "ERROR: osl1_convex_relation_j_to_local_dim: "
                    "number of local dimensions is 0!\n");
    exit(1);
  }
  return r;
}

/**
 * \brief Compute parameter dimension index of a global column
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] j               Global column index
 * \return parameter dimension index of a global column
 */
size_t osl1_convex_relation_j_to_parameter_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t j) {
  const size_t r = j - 1 - convex_relation->nb_output_dim -
                   convex_relation->nb_input_dim -
                   convex_relation->nb_local_dim;
  if (convex_relation->nb_parameter == 0 ||
      r > osl1_convex_relation_parameter_dim_to_j(convex_relation,
                                                  convex_relation->nb_parameter)
  ) {
    fprintf(stderr, "ERROR: osl1_convex_relation_j_to_parameter_dim: "
                    "number of parameter dimensions is 0!\n");
    exit(1);
  }
  return r;
}


// Dimensions

/**
 * \brief Return the output dimensions used in the convex relation
 *        (sorted by index)
 * \param[in] convex_relation An osl1_convex_relation_t
 * \return the output dimensions used in the convex relation (sorted by index)
 */
gho_vector_size_t_t osl1_convex_relation_output_dims_used(
                          const osl1_convex_relation_t* const convex_relation) {
  gho_vector_size_t_t r = gho_vector_size_t_create();
  const size_t nb_row = osl1_convex_relation_nb_row(convex_relation);
  for (size_t i = 0; i < nb_row; ++i) {
    for (size_t j = 1; j < 1 + convex_relation->nb_output_dim; ++j) {
      if (osl1_convex_relation_is_0(convex_relation, i, j) == false) {
        const size_t i_output_dim =
          osl1_convex_relation_j_to_output_dim(convex_relation, j);
        if (gho_vector_size_t_find(&r, &i_output_dim) == r.size) {
          gho_vector_size_t_add(&r, &i_output_dim);
        }
      }
    }
  }
  gho_vector_size_t_sort(&r);
  return r;
}

/**
 * \brief Return the output dimensions used in a row of the convex relation
 *        (sorted by index)
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i               Row index
 * \return the output dimensions used in the row ofthe convex relation
 *         (sorted by index)
 */
gho_vector_size_t_t osl1_convex_relation_output_dims_used_in_row(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i) {
  gho_vector_size_t_t r = gho_vector_size_t_create();
  for (size_t j = 1; j < 1 + convex_relation->nb_output_dim; ++j) {
    if (osl1_convex_relation_is_0(convex_relation, i, j) == false) {
      const size_t i_output_dim =
        osl1_convex_relation_j_to_output_dim(convex_relation, j);
      if (gho_vector_size_t_find(&r, &i_output_dim) == r.size) {
        gho_vector_size_t_add(&r, &i_output_dim);
      }
    }
  }
  return r;
}