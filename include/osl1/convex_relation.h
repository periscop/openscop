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


#ifndef OSL1_CONVEX_RELATION_H
#define OSL1_CONVEX_RELATION_H

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#include <gho/type.h>
#include <gho/string.h>
#include <gho/any.h>
#include <gho/vector/any.h>
#include <gho/matrix/lint.h>
#include <gho/matrix/llint.h>
#ifdef osl_with_gmp
  #include <gho/matrix/mpz_t.h>
#endif
#include <gho/operand.h>

#include "extension.h"


/**
 * \brief Convex relation type (domain, scattering, access read, access write)
 */
typedef enum {
  
  OSL_TYPE_CONVEX_RELATION_DOMAIN,
  OSL_TYPE_CONVEX_RELATION_SCATTERING,
  OSL_TYPE_CONVEX_RELATION_READ,
  OSL_TYPE_CONVEX_RELATION_WRITE
  
} osl1_convex_relation_type_t;


/**
 * \brief osl1_convex_relation_t encapsulates a convex relation
 */
typedef struct {
  
  /// \brief Type
  gho_type_t type;
  
  /// \brief Number of output dimensions
  size_t nb_output_dim;
  
  /// \brief Number of input dimensions
  size_t nb_input_dim;
  
  /// \brief Number of local dimensions
  size_t nb_local_dim;
  
  /// \brief Number of parameters
  size_t nb_parameter;
  
  /// \brief Precision used for matrix
  gho_type_t precision;
  
  /// \brief Matrix
  union {
    
    /// \brief Matrix (long int)
    gho_matrix_lint_t li;
    
    /// \brief Matrix (long long int)
    gho_matrix_llint_t lli;
    
    #ifdef osl_with_gmp
      /// \brief Matrix (GMP mpz_t)
      gho_matrix_mpz_t mpz;
    #endif
    
  } matrix;
  
  /// \brief Extensions
  gho_vector_any_t extensions;
  
} osl1_convex_relation_t;


/// \brief Default precision used by osl1_convex_relation_t
#ifdef osl_with_gmp
  #define OSL_CONVEX_RELATION_DEFAULT_INT_TYPE GHO_TYPE_GHO_MPZ_T
#else
  #define OSL_CONVEX_RELATION_DEFAULT_INT_TYPE GHO_TYPE_LLINT
#endif


// Create & destroy
static inline
osl1_convex_relation_t osl1_convex_relation_create();
static inline
osl1_convex_relation_t osl1_convex_relation_create_args(
                                                    size_t const nb_row,
                                                    size_t const nb_output_dim,
                                                    size_t const nb_input_dim,
                                                    size_t const nb_local_dim,
                                                    size_t const nb_parameter);
static inline
osl1_convex_relation_t osl1_convex_relation_create_args_and_int_type(
                                                   size_t const nb_row,
                                                   size_t const nb_output_dim,
                                                   size_t const nb_input_dim,
                                                   size_t const nb_local_dim,
                                                   size_t const nb_parameter,
                                                   gho_type_t const precision);
static inline
void osl1_convex_relation_destroy(osl1_convex_relation_t* convex_relation);
static inline
void osl1_convex_relation_reset(osl1_convex_relation_t* convex_relation);

// Output
void osl1_convex_relation_fprinti(FILE* file,
                            const osl1_convex_relation_t* const convex_relation,
                            const unsigned int indent);
void osl1_convex_relation_fprint(FILE* file,
                          const osl1_convex_relation_t* const convex_relation);
void osl1_convex_relation_print(
                          const osl1_convex_relation_t* const convex_relation);
void osl1_convex_relation_sprinti(char** c_str,
                            const osl1_convex_relation_t* const convex_relation,
                            const unsigned int indent);
void osl1_convex_relation_sprint(char** c_str,
                          const osl1_convex_relation_t* const convex_relation);

// Input
static inline
osl1_convex_relation_t osl1_convex_relation_fread(FILE* file);
static inline
osl1_convex_relation_t osl1_convex_relation_sread(const char** c_str);

// Copy & comparisons
static inline
osl1_convex_relation_t osl1_convex_relation_copy(
                          const osl1_convex_relation_t* const convex_relation);
static inline
void osl1_convex_relation_copy_(
                            const osl1_convex_relation_t* const convex_relation,
                            osl1_convex_relation_t* copy);
static inline
bool osl1_convex_relation_equal(const osl1_convex_relation_t* const a,
                                const osl1_convex_relation_t* const b);

// Conversion
static inline
gho_string_t osl1_convex_relation_to_string(
                          const osl1_convex_relation_t* const convex_relation);
static inline
gho_any_t osl1_convex_relation_to_any(
                          const osl1_convex_relation_t* const convex_relation);

// Size
static inline
size_t osl1_convex_relation_nb_row(
                          const osl1_convex_relation_t* const convex_relation);
static inline
size_t osl1_convex_relation_nb_col(
                          const osl1_convex_relation_t* const convex_relation);
static inline
bool osl1_convex_relation_empty(
                          const osl1_convex_relation_t* const convex_relation);

// At
static inline
gho_operand_t osl1_convex_relation_at(osl1_convex_relation_t* convex_relation,
                                      const size_t i, const size_t j);
static inline
gho_coperand_t osl1_convex_relation_cat(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i, const size_t j);
static inline
void osl1_convex_relation_at_fprint(FILE* file,
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i, const size_t j);
static inline
void osl1_convex_relation_at_sprint(char** c_str,
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i, const size_t j);

// Is
static inline
bool osl1_convex_relation_is_0(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i, const size_t j);
static inline
bool osl1_convex_relation_is_1(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i, const size_t j);
static inline
bool osl1_convex_relation_is_minus_1(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i, const size_t j);

// Set
static inline
void osl1_convex_relation_set_0(osl1_convex_relation_t* convex_relation,
                                const size_t i, const size_t j);
static inline
void osl1_convex_relation_set_1(osl1_convex_relation_t* convex_relation,
                                const size_t i, const size_t j);
static inline
void osl1_convex_relation_set_minus_1(osl1_convex_relation_t* convex_relation,
                                      const size_t i, const size_t j);

// Add
static inline
void osl1_convex_relation_add_col_after_(
                                        osl1_convex_relation_t* convex_relation,
                                        const size_t i);
static inline
void osl1_convex_relation_add_output_dim(
                                      osl1_convex_relation_t* convex_relation);
static inline
void osl1_convex_relation_add_input_dim(
                                      osl1_convex_relation_t* convex_relation);
static inline
void osl1_convex_relation_add_local_dim(
                                      osl1_convex_relation_t* convex_relation);
static inline
void osl1_convex_relation_add_parameter(
                                      osl1_convex_relation_t* convex_relation);
static inline
void osl1_convex_relation_add_equation_after(
                      osl1_convex_relation_t* convex_relation, const size_t i);
static inline
void osl1_convex_relation_add_equation_before(
                      osl1_convex_relation_t* convex_relation, const size_t i);

// Remove
static inline
void osl1_convex_relation_remove_dim(
                      osl1_convex_relation_t* convex_relation, const size_t j);
static inline
void osl1_convex_relation_remove_output_dim(
           osl1_convex_relation_t* convex_relation, const size_t i_output_dim);
static inline
void osl1_convex_relation_remove_input_dim(
            osl1_convex_relation_t* convex_relation, const size_t i_input_dim);
static inline
void osl1_convex_relation_remove_local_dim(
            osl1_convex_relation_t* convex_relation, const size_t i_local_dim);
static inline
void osl1_convex_relation_remove_parameter_dim(
            osl1_convex_relation_t* convex_relation, const size_t i_parameter);
static inline
void osl1_convex_relation_remove_constraint(
                      osl1_convex_relation_t* convex_relation, const size_t i);

// Index

static inline
bool osl1_convex_relation_is_output_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t j);
static inline
bool osl1_convex_relation_is_input_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t j);
static inline
bool osl1_convex_relation_is_local_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t j);
static inline
bool osl1_convex_relation_is_parameter_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t j);
static inline
size_t osl1_convex_relation_output_dim_to_j(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i_output_dim);
static inline
size_t osl1_convex_relation_input_dim_to_j(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i_input_dim);
static inline
size_t osl1_convex_relation_local_dim_to_j(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i_local_dim);
static inline
size_t osl1_convex_relation_parameter_dim_to_j(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i_parameter);
static inline
size_t osl1_convex_relation_j_to_output_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t j);
static inline
size_t osl1_convex_relation_j_to_input_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t j);
static inline
size_t osl1_convex_relation_j_to_local_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t j);
static inline
size_t osl1_convex_relation_j_to_parameter_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t j);

#include "implementation/convex_relation.h"

#endif