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


#include "../../include/osl1/dimensions.h"
#include "../../include/osl1/equation.h"
#include "../../include/osl1/scop.h"


/**
 * \brief The (in)equation is an equation
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] i               Row index
 * \return true if the row is an equation, false otherwise
 */
bool osl1_is_equation(const osl1_convex_relation_t* const convex_relation,
                      const size_t i) {
  return osl1_convex_relation_is_0(convex_relation, i, 0);
}

/**
 * \brief The (in)equation is an inequation
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] i               Row index
 * \return true if the row is an inequation, false otherwise
 */
bool osl1_is_inequation(const osl1_convex_relation_t* const convex_relation,
                        const size_t i) {
  return (osl1_is_equation(convex_relation, i) == false);
}

/**
 * \brief The equation is a constant equation
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] i               Row index
 * \return true if the row is a constant equation, false otherwise
 */
bool osl1_is_constant_equation(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i) {
  if (osl1_is_inequation(convex_relation, i)) { return false; }
  
  const size_t nb_col = osl1_convex_relation_nb_col(convex_relation);
  for (size_t j = 1; j < nb_col - 1; ++j) {
    if (osl1_convex_relation_is_0(convex_relation, i, j) == false) {
      return false;
    }
  }
  
  return true;
}

/**
 * \brief The equation is a parameter equation
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] i               Row index
 * \return true if the row is a parameter equation, false otherwise
 */
bool osl1_is_parameter_equation(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i) {
  if (osl1_is_constant_equation(convex_relation, i)) { return false; }
  
  const size_t nb_dim = convex_relation->nb_output_dim
                      + convex_relation->nb_input_dim
                      + convex_relation->nb_local_dim;
  for (size_t j = 1; j < 1 + nb_dim; ++j) {
    if (osl1_convex_relation_is_0(convex_relation, i, j) == false) {
      return false;
    }
  }
  
  return true;
}

/**
 * \brief The equation is a beta equation
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] i          Row index
 * \return true if the row is a beta equation, false otherwise
 */
bool osl1_is_beta_equation(const osl1_convex_relation_t* const convex_relation,
                           const size_t i) {
  if (osl1_is_inequation(convex_relation, i)) { return false; }
  
  if (osl1_is_constant_equation(convex_relation, i)) { return false; }
  
  if (osl1_is_parameter_equation(convex_relation, i)) { return false; }
  
  const size_t nb_output_dim = convex_relation->nb_output_dim;
  const size_t nb_input_dim = convex_relation->nb_input_dim;
  const size_t nb_local_dim = convex_relation->nb_local_dim;
  
  {
    size_t nb_not_0 = 0;
    for (size_t j = 1; j < 1 + nb_output_dim; ++j) {
      if (osl1_convex_relation_is_0(convex_relation, i, j) == false) {
        ++nb_not_0;
        if (nb_not_0 == 2) { return false; }
        else if (osl1_is_beta_dim(convex_relation, j) == false) { return false; }
      }
    }
  }
  
  {
    const size_t begin = 1 + nb_output_dim;
    const size_t end = 1 + nb_output_dim + nb_input_dim;
    for (size_t j = begin; j < end; ++j) {
      if (osl1_convex_relation_is_0(convex_relation, i, j) == false) {
        return false;
      }
    }
  }
  
  {
    const size_t begin = 1 + nb_output_dim + nb_input_dim;
    const size_t end = 1 + nb_output_dim + nb_input_dim + nb_local_dim;
    for (size_t j = begin; j < end; ++j) {
      if (osl1_convex_relation_is_0(convex_relation, i, j) == false) {
        return false;
      }
    }
  }
  
  return true;
}

/**
 * \brief The equation is an alpha equation
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] i          Row index
 * \return true if the row is an alpha equation, false otherwise
 */
bool osl1_is_alpha_equation(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i) {
  if (osl1_is_constant_equation(convex_relation, i)) { return false; }
  
  if (osl1_is_parameter_equation(convex_relation, i)) { return false; }
  
  if (osl1_is_beta_equation(convex_relation, i)) { return false; }
  
  return true;
}

/**
 * \brief Get row index of the nth beta equation
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] n               Beta equation number
 * \return row index of the nth beta equation
 */
size_t osl1_get_beta_equation(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t n) {
  if (n == 0) {
    fprintf(stderr, "ERROR: osl1_get_beta_equation: "
                    "n must be > 0!\n");
    exit(1);
  }
  
  const size_t nb_row = osl1_convex_relation_nb_row(convex_relation);
  size_t nb_beta_equation = 0;
  for (size_t i = 0; i < nb_row; ++i) {
    if (osl1_is_beta_equation(convex_relation, i)) {
      ++nb_beta_equation;
      if (n == nb_beta_equation) { return i; }
    }
  }
  
  fprintf(stderr, "ERROR: osl1_get_beta_equation: "
                  "nth beta equation does not exist!\n");
  exit(1);
}
