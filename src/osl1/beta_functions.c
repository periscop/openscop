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


#include <gho/vector/size_t.h>
#include <gho/math_T.h>

#include "../../include/osl1/beta_functions.h"
#include "../../include/osl1/equation.h"


// Extract

/**
 * \brief Extract the beta of a convex relation
 * \param[in] convex_relation An osl1_convex_relation_t
 * \return the beta extracted
 */
osl1_beta_t osl1_extract_beta(
                          const osl1_convex_relation_t* const convex_relation) {
  osl1_beta_t r = osl1_beta_create();
  const size_t nb_row = osl1_convex_relation_nb_row(convex_relation);
  for (size_t i = 0; i < nb_row; ++i) {
    if (osl1_is_beta_equation(convex_relation, i)) {
      const size_t beta_value = osl1_get_beta_value(convex_relation, i);
      osl1_beta_add(&r, &beta_value);
    }
  }
  return r;
}

/**
 * \brief Extract all betas of a scop
 * \param[in] scop An osl1_scop_t
 * \return betas extracted
 */
osl1_vector_beta_t osl1_extract_betas(const osl1_scop_t* const scop) {
  osl1_vector_beta_t r = osl1_vector_beta_create();
  // For all statements
  for (size_t s = 0; s < scop->statements.size; ++s) {
    const osl1_statement_t* const statement = &scop->statements.array[s];
    // For all convex relations
    for (size_t u = 0; u < statement->scattering.size; ++u) {
      const osl1_convex_relation_t* const convex_relation =
        &statement->scattering.array[u];
      // Extract & add beta
      osl1_beta_t beta = osl1_extract_beta(convex_relation);
      osl1_vector_beta_add(&r, &beta);
      osl1_beta_destroy(&beta);
    }
  }
  return r;
}


// Get from beta

/**
 * \brief Find the convex relation (const) with a beta
 * \param[in] scop An osl1_scop_t
 * \param[in] beta A beta
 * \return osl1_convex_relation_t (const) found, NULL if not found
 */
const osl1_convex_relation_t* osl1_get_convex_relation_cptr(
                                                const osl1_scop_t* const scop,
                                                const osl1_beta_t* const beta) {
  // For all statements
  for (size_t s = 0; s < scop->statements.size; ++s) {
    const osl1_statement_t* const statement = &scop->statements.array[s];
    for (size_t u = 0; u < statement->scattering.size; ++u) {
    // For all convex relations
      const osl1_convex_relation_t* const convex_relation =
        &statement->scattering.array[u];
      // Get convex relation
      osl1_beta_t beta_tmp = osl1_extract_beta(convex_relation);
      bool found = false;
      if (osl1_beta_equal(beta, &beta_tmp)) { found = true; }
      osl1_beta_destroy(&beta_tmp);
      if (found) { return convex_relation; }
    }
  }
  return NULL;
}

/**
 * \brief Find the convex relation with a beta
 * \param[in] scop An osl1_scop_t
 * \param[in] beta A beta
 * \return osl1_convex_relation_t found, NULL if not found
 */
osl1_convex_relation_t* osl1_get_convex_relation_ptr(
                                                osl1_scop_t* scop,
                                                const osl1_beta_t* const beta) {
  return (osl1_convex_relation_t*)osl1_get_convex_relation_cptr(scop, beta);
}

/**
 * \brief Find the convex relations with a beta prefix
 * \param[in] scop        An osl1_scop_t
 * \param[in] beta_prefix A beta prefix
 * \return the vector of pointers to the convex relation with same beta prefix
 */
osl1_vector_convex_relation_ptr_t osl1_get_convex_relation_vector_ptr(
                                         osl1_scop_t* scop,
                                         const osl1_beta_t* const beta_prefix) {
  osl1_vector_convex_relation_ptr_t r =
    osl1_vector_convex_relation_ptr_create();
  // For all statements
  for (size_t s = 0; s < scop->statements.size; ++s) {
    const osl1_statement_t* const statement = &scop->statements.array[s];
    for (size_t u = 0; u < statement->scattering.size; ++u) {
    // For all convex relations
      osl1_convex_relation_t* convex_relation = &statement->scattering.array[u];
      // Get convex relation
      osl1_beta_t beta_tmp = osl1_extract_beta(convex_relation);
      if (osl1_same_beta_prefix(&beta_tmp, beta_prefix)) {
        osl1_vector_convex_relation_ptr_add(&r, &convex_relation);
      }
      osl1_beta_destroy(&beta_tmp);
    }
  }
  return r;
}

/**
 * \brief Get the number of statements with this beta prefix
 * \param[in] scop        An osl1_scop_t
 * \param[in] beta_prefix A beta prefix
 * \return the number of statements with this beta prefix
 */
size_t osl1_nb_statement_beta_prefix(const osl1_scop_t* const scop,
                                     const osl1_beta_t* const beta_prefix) {
  size_t nb_statement = 0;
  // For all statements
  for (size_t s = 0; s < scop->statements.size; ++s) {
    const osl1_statement_t* const statement = &scop->statements.array[s];
    for (size_t u = 0; u < statement->scattering.size; ++u) {
    // For all convex relations
      const osl1_convex_relation_t* const convex_relation =
        &statement->scattering.array[u];
      // Get convex relation
      osl1_beta_t beta = osl1_extract_beta(convex_relation);
      if (osl1_same_beta_prefix(&beta, beta_prefix)) { ++nb_statement; }
      osl1_beta_destroy(&beta);
    }
  }
  return nb_statement;
}

/**
 * \brief Get the number of statements in loop
 *        (a loop is considered as a statement)
 * \param[in] scop        An osl1_scop_t
 * \param[in] beta_prefix A beta prefix (beta loop)
 * \return the number of statements in loop
 */
size_t osl1_nb_statement_in_loop(const osl1_scop_t* const scop,
                                       const osl1_beta_t* const beta_prefix) {
  size_t nb_statement = 0;
  gho_vector_size_t_t beta_values = gho_vector_size_t_create();
  // For all statements
  for (size_t s = 0; s < scop->statements.size; ++s) {
    const osl1_statement_t* const statement = &scop->statements.array[s];
    for (size_t u = 0; u < statement->scattering.size; ++u) {
    // For all convex relations
      const osl1_convex_relation_t* const convex_relation =
        &statement->scattering.array[u];
      // Get convex relation
      osl1_beta_t beta = osl1_extract_beta(convex_relation);
      if (osl1_same_beta_prefix(&beta, beta_prefix)) {
        const size_t beta_value = beta.array[beta_prefix->size - 1];
        if (gho_vector_size_t_find(&beta_values, &beta_value) ==
                                                             beta_values.size) {
           gho_vector_size_t_add(&beta_values, &beta_value);
          ++nb_statement;
        }
      }
      osl1_beta_destroy(&beta);
    }
  }
  gho_vector_size_t_destroy(&beta_values);
  return nb_statement;
}


// Other

/**
 * \brief Extract max value of beta prefix
 * \param[in] scop        An osl1_scop_t
 * \param[in] beta_prefix A beta prefix (beta loop)
 * \return max value of beta prefix
 */
size_t osl1_beta_prefix_max_value(const osl1_scop_t* const scop,
                                  const osl1_beta_t* const beta_prefix) {
  size_t max_value = 0;
  // For all statements
  for (size_t s = 0; s < scop->statements.size; ++s) {
    const osl1_statement_t* const statement = &scop->statements.array[s];
    for (size_t u = 0; u < statement->scattering.size; ++u) {
    // For all convex relations
      const osl1_convex_relation_t* const convex_relation =
        &statement->scattering.array[u];
      // Get convex relation
      osl1_beta_t beta = osl1_extract_beta(convex_relation);
      if (osl1_same_beta_prefix(&beta, beta_prefix)) {
        max_value = gho_T_max(max_value, beta.array[beta_prefix->size - 1]);
      }
      osl1_beta_destroy(&beta);
    }
  }
  return max_value;
}
