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

#include <gho/output.h>
#include <gho/c_str.h>

#include "../include/osl1/print_polylib.h"


// Relation

/**
 * \brief Print osl1_relation_t in a file
 * \param[in] file     A C file
 * \param[in] relation An osl1_relation_t
 */
void osl1_relation_fprint_polylib(FILE* file,
                                  const osl1_relation_t* const relation) {
  if (relation->size > 1) {
    gho_size_t_fprint(file, &relation->size);
    gho_c_str_fprint(file, "\n");
  }
  for (size_t cr = 0; cr < relation->size; ++cr) {
    const osl1_convex_relation_t* const convex_relation = &relation->array[cr];
    // nb_*
    const size_t nb_row = osl1_convex_relation_nb_row(convex_relation);
    const size_t nb_col = osl1_convex_relation_nb_col(convex_relation);
    const size_t nb_output_dim = convex_relation->nb_output_dim;
    const size_t nb_input_dim = convex_relation->nb_input_dim;
    const size_t nb_local_dim = convex_relation->nb_local_dim;
    const size_t nb_parameter = convex_relation->nb_parameter;
    gho_size_t_fprint(file, &nb_row);
    gho_c_str_fprint(file, " ");
    gho_size_t_fprint(file, &nb_col);
    gho_c_str_fprint(file, " ");
    gho_size_t_fprint(file, &nb_output_dim);
    gho_c_str_fprint(file, " ");
    gho_size_t_fprint(file, &nb_input_dim);
    gho_c_str_fprint(file, " ");
    gho_size_t_fprint(file, &nb_local_dim);
    gho_c_str_fprint(file, " ");
    gho_size_t_fprint(file, &nb_parameter);
    gho_c_str_fprint(file, "\n");
    // Matrix
    for (size_t i = 0; i < nb_row; i++) {
      for (size_t j = 0; j < nb_col; j++) {
        osl1_convex_relation_at_fprint(file, convex_relation, i, j);
        gho_c_str_fprint(file, " ");
      }
      gho_c_str_fprint(file, "\n");
    }
  }
}

/**
 * \brief Print osl1_relation_t in a C string
 * \param[in] c_str    A C string
 * \param[in] relation An osl1_relation_t
 */
void osl1_relation_sprint_polylib(char** c_str,
                                  const osl1_relation_t* const relation) {
  if (relation->size > 1) {
    gho_size_t_sprint(c_str, &relation->size);
    gho_c_str_sprint(c_str, "\n");
  }
  for (size_t cr = 0; cr < relation->size; ++cr) {
    const osl1_convex_relation_t* const convex_relation = &relation->array[cr];
    // nb_*
    const size_t nb_row = osl1_convex_relation_nb_row(convex_relation);
    const size_t nb_col = osl1_convex_relation_nb_col(convex_relation);
    const size_t nb_output_dim = convex_relation->nb_output_dim;
    const size_t nb_input_dim = convex_relation->nb_input_dim;
    const size_t nb_local_dim = convex_relation->nb_local_dim;
    const size_t nb_parameter = convex_relation->nb_parameter;
    gho_size_t_sprint(c_str, &nb_row);
    gho_c_str_sprint(c_str, " ");
    gho_size_t_sprint(c_str, &nb_col);
    gho_c_str_sprint(c_str, " ");
    gho_size_t_sprint(c_str, &nb_output_dim);
    gho_c_str_sprint(c_str, " ");
    gho_size_t_sprint(c_str, &nb_input_dim);
    gho_c_str_sprint(c_str, " ");
    gho_size_t_sprint(c_str, &nb_local_dim);
    gho_c_str_sprint(c_str, " ");
    gho_size_t_sprint(c_str, &nb_parameter);
    gho_c_str_sprint(c_str, "\n");
    // Matrix
    for (size_t i = 0; i < nb_row; i++) {
      for (size_t j = 0; j < nb_col; j++) {
        osl1_convex_relation_at_sprint(c_str, convex_relation, i, j);
        gho_c_str_sprint(c_str, " ");
      }
      gho_c_str_sprint(c_str, "\n");
    }
  }
}
