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


#include "../../include/osl1/dimensions.h"
#include "../../include/osl1/equation.h"
#include "../../include/osl1/scop.h"


// Index

/**
 * \brief Column index is a beta dimension?
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] j               Column index
 * \return true if column index is a beta dimension, false otherwise
 */
bool osl1_is_beta_dim(const osl1_convex_relation_t* const convex_relation,
                      const size_t j) {
  if (osl1_convex_relation_is_output_dim(convex_relation, j)) {
    return convex_relation->output_dims_types.array[j - 1].dimension_type ==
                                                       osl1_dimension_type_beta;
  }
  return false;
}

/**
 * \brief Column index is an alpha dimension?
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] j               Column index
 * \return true if column index is an alpha dimension, false otherwise
 */
bool osl1_is_alpha_dim(const osl1_convex_relation_t* const convex_relation,
                        const size_t j) {
  if (osl1_convex_relation_is_output_dim(convex_relation, j)) {
    return convex_relation->output_dims_types.array[j - 1].dimension_type ==
                                                      osl1_dimension_type_alpha;
  }
  return false;
}

/**
 * \brief Compute output dimension index of a input dimension
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i               Index of alpha dimension
 * \return output dimension index of a global column
 */
size_t osl1_alpha_dim_to_output_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i_alpha_dim) {
  size_t i_alpha_dim_tmp = 0;
  for (size_t j = 1; j < 1 + convex_relation->nb_output_dim; ++j) {
    if (osl1_is_alpha_dim(convex_relation, j)) {
      if (i_alpha_dim == i_alpha_dim_tmp) {
        return osl1_convex_relation_j_to_output_dim(convex_relation, j);
      }
      ++i_alpha_dim_tmp;
    }
  }
  
  fflush(stdout);
  fprintf(stderr, "ERROR: osl1_alpha_dim_to_output_dim: "
                  "alpha dimension does not exist\n");
  exit(1);
}
