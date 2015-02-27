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



#include <gho/int/mpz_t.h>

// osl to osl1

/**
 * @brief Convert an osl_relation_t into an osl1_relation_t
 * @param[in] relation_osl An osl_relation_t
 * @return the osl1_relation_t from the osl_relation_t
 */
osl1_relation_t osl_to_osl1_relation(const osl_relation_t* const relation_osl) {
  osl1_relation_t r = osl1_relation_create();
  for (const osl_relation_t* p = relation_osl; p != NULL; p = p->next) {
    // Preconditions
    #ifndef NDEBUG
    if (p->nb_rows < 0) {
      fprintf(stderr, "ERROR: osl_to_osl1_relation: "
                      "relation_osl.nb_rows < 0!\n");
      exit(1);
    }
    if (p->nb_output_dims < 0) {
      fprintf(stderr, "ERROR: osl_to_osl1_relation: "
                      "relation_osl.nb_output_dims < 0!\n");
      exit(1);
    }
    if (p->nb_input_dims < 0) {
      fprintf(stderr, "ERROR: osl_to_osl1_relation: "
                      "relation_osl.nb_input_dims < 0!\n");
      exit(1);
    }
    if (p->nb_local_dims < 0) {
      fprintf(stderr, "ERROR: osl_to_osl1_relation: "
                      "relation_osl.nb_local_dims < 0!\n");
      exit(1);
    }
    if (p->nb_parameters < 0) {
      fprintf(stderr, "ERROR: osl_to_osl1_relation: "
                      "relation_osl.nb_parameters < 0!\n");
      exit(1);
    }
    #endif
    // Create convex relation
    gho_type_t precision = OSL_CONVEX_RELATION_DEFAULT_INT_TYPE;
    if (p->precision == OSL_PRECISION_SP) { precision = GHO_TYPE_LINT; }
    if (p->precision == OSL_PRECISION_DP) { precision = GHO_TYPE_LLINT; }
    #ifdef osl_with_gmp
    if (p->precision == OSL_PRECISION_MP) { precision = GHO_TYPE_GHO_MPZ_T; }
    #endif
    osl1_convex_relation_t tmp = osl1_convex_relation_create_args_and_int_type(
      (size_t)p->nb_rows,
      (size_t)p->nb_output_dims,
      (size_t)p->nb_input_dims,
      (size_t)p->nb_local_dims,
      (size_t)p->nb_parameters,
      precision);
    // Matrix
    const size_t nb_row = osl1_convex_relation_nb_row(&tmp);
    const size_t nb_col = osl1_convex_relation_nb_col(&tmp);
    for (size_t i = 0; i < nb_row; ++i) {
      for (size_t j = 0; j < nb_col; ++j) {
        gho_operand_t e = osl1_convex_relation_at(&tmp, i, j);
        if (p->precision == OSL_PRECISION_SP) {
          gho_set_lli(e, p->m[i][j].sp);
        }
        else if (p->precision == OSL_PRECISION_DP) {
          gho_set_lli(e, p->m[i][j].dp);
        }
        #ifdef osl_with_gmp
        else if (p->precision == OSL_PRECISION_MP) {
          mpz_t* value_gmp_mpz = p->m[i][j].mp;
          gho_mpz_t value =
            gho_mpz_create_from_gmp((const mpz_t* const)value_gmp_mpz);
          gho_operand_t value_op = gho_operand_type(&value, GHO_TYPE_GHO_MPZ_T);
          gho_set(e, value_op);
          gho_mpz_destroy(&value);
        }
        #endif
      }
    }
    // Add
    osl1_relation_add(&r, &tmp);
    osl1_convex_relation_destroy(&tmp);
  }
  return r;
}
