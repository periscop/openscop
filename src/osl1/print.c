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

#include "../include/osl1/print.h"


// Convex relation index name

/**
 * \brief Return name of a dimension
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] j               Dimension index
 * \param[in] scop            An osl1_scop_t (can be NULL)
 * \param[in] statement       An osl1_statement_t (can be NULL)
 * \return name of the dimension j
 */
gho_string_t osl1_convex_relation_name_column(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t j,
                            const osl1_scop_t* const scop,
                            const osl1_statement_t* const statement) {
  gho_string_t r = gho_string_create();
  
  // Get body
  const osl1_extension_body_t* const body =
    (statement != NULL) ?
      osl1_get_extension_cptr(GHO_TYPE_OSL_EXTENSION_BODY,
                              &statement->extensions)
    :
      NULL;
  // Get scatnames
  const osl1_extension_scatnames_t* const scatnames =
    (scop != NULL) ?
      osl1_get_extension_cptr(GHO_TYPE_OSL_EXTENSION_SCATNAMES,
                              &scop->extensions)
    :
      NULL;
  
  if (j == 0) { gho_string_add_c_str(&r, "e/i"); }
  
  else if (osl1_convex_relation_is_output_dim(convex_relation, j)) {
    const size_t i_output_dim =
      osl1_convex_relation_j_to_output_dim(convex_relation, j);
    // Domain
    if (convex_relation->nb_input_dim == 0) {
      if (body == NULL ||
          body->original_iterators.size < convex_relation->nb_output_dim) {
        gho_string_add_char(&r, (char)('i' + (char)i_output_dim));
      }
      else {
        gho_string_add(&r, &body->original_iterators.array[i_output_dim]);
      }
    }
    // Scattering or accesses
    else {
      if (scatnames == NULL ||
          scatnames->scatnames.size < convex_relation->nb_output_dim) {
        gho_string_destroy(&r);
        r = gho_size_t_to_string(&i_output_dim);
        gho_string_add_char_i(&r, 'c', 0);
      }
      else {
        gho_string_add(&r, &scatnames->scatnames.array[i_output_dim]);
        gho_string_add_char(&r, '\'');
      }
    }
  }
  
  else if (osl1_convex_relation_is_input_dim(convex_relation, j)) {
    const size_t i_input_dim =
      osl1_convex_relation_j_to_input_dim(convex_relation, j);
    if (body == NULL ||
        body->original_iterators.size < convex_relation->nb_input_dim) {
      gho_string_add_char(&r, (char)('i' + (char)i_input_dim));
    }
    else {
      gho_string_add(&r, &body->original_iterators.array[i_input_dim]);
    }
  }
  
  else if (osl1_convex_relation_is_local_dim(convex_relation, j)) {
    const size_t i_local_dim =
      osl1_convex_relation_j_to_local_dim(convex_relation, j);
    gho_string_destroy(&r);
    r = gho_size_t_to_string(&i_local_dim);
    gho_string_add_char_i(&r, 'l', 0);
  }
  
  else if (osl1_convex_relation_is_parameter_dim(convex_relation, j)) {
    const size_t i_parameter =
      osl1_convex_relation_j_to_parameter_dim(convex_relation, j);
    if (scop == NULL ||
        scop->parameters.size < convex_relation->nb_parameter) {
      gho_string_add_char(&r, (char)('N' - (char)i_parameter));
    }
    else {
      gho_string_add(&r, &scop->parameters.array[i_parameter]);
    }
  }
  
  else if (j + 1 == osl1_convex_relation_nb_col(convex_relation)) {
    gho_string_add_c_str(&r, "1");
  }
  
  else { gho_string_add_c_str(&r, "unknown"); }
  
  return r;
}

/**
 * \brief Return name of an output dimension
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i_output_dim    Output dimension index
 * \param[in] scop            An osl1_scop_t (can be NULL)
 * \param[in] statement       An osl1_statement_t (can be NULL)
 * \return name of the output dimension i_output_dim
 */
gho_string_t osl1_convex_relation_name_output_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i_output_dim,
                            const osl1_scop_t* const scop,
                            const osl1_statement_t* const statement) {
  return osl1_convex_relation_name_column(
    convex_relation,
    osl1_convex_relation_output_dim_to_j(convex_relation, i_output_dim),
    scop, statement
  );
}

/**
 * \brief Return name of an input dimension
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i_input_dim     Input dimension index
 * \param[in] scop            An osl1_scop_t (can be NULL)
 * \param[in] statement       An osl1_statement_t (can be NULL)
 * \return name of the input dimension i_input_dim
 */
gho_string_t osl1_convex_relation_name_input_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i_input_dim,
                            const osl1_scop_t* const scop,
                            const osl1_statement_t* const statement) {
  return osl1_convex_relation_name_column(
    convex_relation,
    osl1_convex_relation_input_dim_to_j(convex_relation, i_input_dim),
    scop, statement
  );
}

/**
 * \brief Return name of a local dimension
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i_local_dim     Local dimension index
 * \param[in] scop            An osl1_scop_t (can be NULL)
 * \param[in] statement       An osl1_statement_t (can be NULL)
 * \return name of the local dimension i_local_dim
 */
gho_string_t osl1_convex_relation_name_local_dim(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i_local_dim,
                            const osl1_scop_t* const scop,
                            const osl1_statement_t* const statement) {
  return osl1_convex_relation_name_column(
    convex_relation,
    osl1_convex_relation_local_dim_to_j(convex_relation, i_local_dim),
    scop, statement
  );
}

/**
 * \brief Return name of a parameter dimension
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] i_parameter     Parameter index
 * \param[in] scop            An osl1_scop_t (can be NULL)
 * \param[in] statement       An osl1_statement_t (can be NULL)
 * \return name of the parameter dimension i_parameter
 */
gho_string_t osl1_convex_relation_name_parameter(
                            const osl1_convex_relation_t* const convex_relation,
                            const size_t i_parameter,
                            const osl1_scop_t* const scop,
                            const osl1_statement_t* const statement) {
  return osl1_convex_relation_name_column(
    convex_relation,
    osl1_convex_relation_parameter_dim_to_j(convex_relation, i_parameter),
    scop, statement
  );
}

/**
 * \brief Print a name in column size in a file
 * \param[in] file        A C file
 * \param[in] name        A gho_size_t
 * \param[in] column_size Size of the column
 */
void osl1_convex_relation_fprint_name(FILE * file,
                                      const gho_string_t* const name,
                                      const gho_uint column_size) {
  const gho_uint name_size = (gho_uint)gho_string_size(name);
  
  const gho_uint space_before =
    (column_size > name_size) ? ((column_size - name_size) / 2) : 0;
  const gho_uint space_after = (gho_uint)
    gho_T_max((int)column_size - (int)space_before - (int)name_size, 0);
  
  gho_fprinti(file, space_before);
  gho_string_fprint(file, name);
  gho_fprinti(file, space_after);
}

/**
 * \brief Print a name in column size in a C string
 * \param[in] c_str       A C string
 * \param[in] name        A gho_size_t
 * \param[in] column_size Size of the column
 */
void osl1_convex_relation_sprint_name(char** c_str,
                                      const gho_string_t* const name,
                                      const gho_uint column_size) {
  const gho_uint name_size = (gho_uint)gho_string_size(name);
  
  const gho_uint space_before =
    (column_size > name_size) ? ((column_size - name_size + 1) / 2) : 0;
  const gho_uint space_after = (gho_uint)
    gho_T_max((int)column_size - (int)space_before - (int)name_size, 0);
  
  gho_sprinti(c_str, space_before);
  gho_string_sprint(c_str, name);
  gho_sprinti(c_str, space_after);
}

/**
 * \brief Compute column sizes of an osl1_convex_relation_t
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] scop            An osl1_scop_t (can be NULL)
 * \param[in] statement       An osl1_statement_t (can be NULL)
 * \return column sizes of an osl1_convex_relation_t
 */
gho_vector_uint_t osl1_convex_relation_column_sizes(
                            const osl1_convex_relation_t* const convex_relation,
                            const osl1_scop_t* const scop,
                            const osl1_statement_t* const statement) {
  const size_t nb_row = osl1_convex_relation_nb_row(convex_relation);
  const size_t nb_col = osl1_convex_relation_nb_col(convex_relation);
  
  gho_vector_uint_t r =
    gho_vector_uint_create_n(nb_col);
  
  for (size_t i = 0; i < nb_col; ++i) {
    gho_string_t name =
      osl1_convex_relation_name_column(convex_relation, i, scop, statement);
    r.array[i] = gho_T_max(r.array[i], (gho_uint)gho_string_size(&name) + 2);
    gho_string_destroy(&name);
  }
  
  for (size_t i = 0; i < nb_row; ++i) {
    for (size_t j = 0; j < nb_col; ++j) {
      gho_coperand_t cop = osl1_convex_relation_cat(convex_relation, i, j);
      gho_string_t cop_string = gho_coperand_to_string(&cop);
      r.array[i] =
        gho_T_max(r.array[i], (gho_uint)gho_string_size(&cop_string) + 2);
      gho_string_destroy(&cop_string);
    }
  }
  
  return r;
}

// Convex relation

/**
 * \brief Print an osl1_convex_relation_t in a file with indentation
 * \param[in] file            A C file
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] indent          Indentation (number of spaces)
 * \param[in] scop            An osl1_scop_t (can be NULL)
 * \param[in] statement       An osl1_statement_t (can be NULL)
 */
void osl1_convex_relation_fprinti_openscop(FILE* file,
                            const osl1_convex_relation_t* const convex_relation,
                            const unsigned int indent,
                            const osl1_scop_t* const scop,
                            const osl1_statement_t* const statement) {
  
  const size_t nb_row = osl1_convex_relation_nb_row(convex_relation);
  const size_t nb_col = osl1_convex_relation_nb_col(convex_relation);
  const size_t nb_output_dim = convex_relation->nb_output_dim;
  const size_t nb_input_dim = convex_relation->nb_input_dim;
  const size_t nb_local_dim = convex_relation->nb_local_dim;
  const size_t nb_parameter = convex_relation->nb_parameter;
  
  gho_c_str_fprinti(file, "# nb row, col, output, input, local, param\n",
                    indent);
  gho_fprinti(file, indent);
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
  
  gho_c_str_fprinti(file, "# Matrix (precision used = ", indent);
  if (convex_relation->precision == GHO_TYPE_LINT) {
    gho_c_str_fprint(file, "long int)\n");
  }
  else if (convex_relation->precision == GHO_TYPE_LLINT) {
    gho_c_str_fprint(file, "long long int)\n");
  }
  #ifdef osl_with_gmp
  else if (convex_relation->precision == GHO_TYPE_GHO_MPZ_T) {
    gho_c_str_fprint(file, "GMP mpz_t)\n");
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_fprinti_openscop: "
                    "unknown precision!\n");
    exit(1);
  }
  
  gho_vector_uint_t column_sizes =
    osl1_convex_relation_column_sizes(convex_relation, scop, statement);
  
  gho_c_str_fprinti(file, "#", indent);
  // (In)equation
  {
    const size_t i = 0;
    gho_string_t name =
      osl1_convex_relation_name_column(convex_relation, i, scop, statement);
    osl1_convex_relation_fprint_name(file, &name, column_sizes.array[0]);
    gho_string_destroy(&name);
  }
  gho_c_str_fprint(file, "|");
  // Output dimensions
  for (size_t i = 0; i < nb_output_dim; ++i) {
    gho_string_t name =
      osl1_convex_relation_name_output_dim(convex_relation, i, scop, statement);
    const size_t column_sizes_i = i + 1;
    osl1_convex_relation_fprint_name(file, &name,
                                     column_sizes.array[column_sizes_i]);
    gho_string_destroy(&name);
  }
  gho_c_str_fprint(file, "|");
  // Input dimensions
  for (size_t i = 0; i < nb_input_dim; ++i) {
    gho_string_t name =
      osl1_convex_relation_name_input_dim(convex_relation, i, scop, statement);
    const size_t column_sizes_i = 1 + nb_output_dim;
    osl1_convex_relation_fprint_name(file, &name,
                                     column_sizes.array[column_sizes_i]);
    gho_string_destroy(&name);
  }
  gho_c_str_fprint(file, "|");
  // Local dimensions
  for (size_t i = 0; i < nb_local_dim; ++i) {
    gho_string_t name =
      osl1_convex_relation_name_local_dim(convex_relation, i, scop, statement);
    const size_t column_sizes_i = 1 + nb_output_dim + nb_input_dim;
    osl1_convex_relation_fprint_name(file, &name,
                                     column_sizes.array[column_sizes_i]);
    gho_string_destroy(&name);
  }
  gho_c_str_fprint(file, "|");
  // Parameters
  for (size_t i = 0; i < nb_parameter; ++i) {
    gho_string_t name =
      osl1_convex_relation_name_parameter(convex_relation, i, scop, statement);
    const size_t column_sizes_i = 1 + nb_output_dim + nb_input_dim +
                                  nb_local_dim;
    osl1_convex_relation_fprint_name(file, &name,
                                     column_sizes.array[column_sizes_i]);
    gho_string_destroy(&name);
  }
  gho_c_str_fprint(file, "|");
  // Constant
  {
    const size_t i = nb_col - 1;
    gho_string_t name =
      osl1_convex_relation_name_column(convex_relation, i, scop, statement);
    const size_t column_sizes_i = 1 + nb_output_dim + nb_input_dim +
                                  nb_local_dim + nb_parameter;
    osl1_convex_relation_fprint_name(file, &name,
                                     column_sizes.array[column_sizes_i]);
    gho_string_destroy(&name);
  }
  gho_c_str_fprint(file, "\n");
  
  for (size_t i = 0; i < nb_row; ++i) {
    gho_fprinti(file, indent);
    gho_c_str_fprint(file, " ");
    for (size_t j = 0; j < nb_col; ++j) {
      // |
      if (j == 1) {
        gho_c_str_fprint(file, " ");
      }
      if (j == 1 + nb_output_dim) {
        gho_c_str_fprint(file, " ");
      }
      if (j == 1 + nb_output_dim + nb_input_dim) {
        gho_c_str_fprint(file, " ");
      }
      if (j == 1 + nb_output_dim + nb_input_dim + nb_local_dim) {
        gho_c_str_fprint(file, " ");
      }
      if (j == 1 + nb_output_dim + nb_input_dim + nb_local_dim + nb_parameter) {
        gho_c_str_fprint(file, " ");
      }
      // Get convex_relation[i][j]
      gho_coperand_t cop = osl1_convex_relation_cat(convex_relation, i, j);
      gho_string_t cop_string = gho_coperand_to_string(&cop);
      // Display convex_relation[i][j]
      osl1_convex_relation_fprint_name(file, &cop_string,
                                       column_sizes.array[j]);
      // Destroy
      gho_string_destroy(&cop_string);
    }
    // Display equation
    gho_c_str_fprint(file, "# ");
    bool first_number = true;
    for (size_t j = 1; j < nb_col; ++j) {
      if (osl1_convex_relation_is_0(convex_relation, i, j) == false) {
        // +
        if (first_number == false) { gho_c_str_fprint(file, " + "); }
        first_number = false;
        // Coefficient
        if (osl1_convex_relation_is_1(convex_relation, i, j)) {
          if (j == nb_col - 1) {
            gho_c_str_fprint(file, "1");
          }
        }
        else if (osl1_convex_relation_is_minus_1(convex_relation, i, j)) {
          if (j == nb_col - 1) {
            gho_c_str_fprint(file, "-1");
          }
          else {
            gho_c_str_fprint(file, "-");
          }
        }
        else {
          osl1_convex_relation_at_fprint(file, convex_relation, i, j);
        }
        // Name of dimension
        if (j != nb_col - 1) {
          gho_string_t name =
            osl1_convex_relation_name_column(convex_relation, j,
                                             scop, statement);
          gho_string_fprint(file, &name);
          gho_string_destroy(&name);
        }
      }
      if (j == nb_col - 1) {
        if (first_number) { gho_c_str_fprint(file, "0"); }
        if (osl1_convex_relation_is_0(convex_relation, i, 0)) {
          gho_c_str_fprint(file, " = 0");
        }
        else {
        gho_c_str_fprint(file, " >= 0");
        }
      }
    }
    gho_c_str_fprint(file, "\n");
  }
  gho_c_str_fprint(file, "\n");
  
  gho_vector_uint_destroy(&column_sizes);
  
  gho_c_str_fprinti(file, "# Number of convex relation extensions\n", indent);
  gho_size_t_fprinti(file, &convex_relation->extensions.size, indent);
  if (convex_relation->extensions.size != 0) {
    gho_c_str_fprint(file, "\n");
    gho_c_str_fprinti(file, "# Convex relation extensions\n", indent);
    osl1_extensions_fprinti_openscop(file, &convex_relation->extensions, indent);
  }
}

/**
 * \brief Print an osl1_convex_relation_t in a C string with indentation
 * \param[in] c_str           A C string
 * \param[in] convex_relation An osl1_convex_relation_t
 * \param[in] indent          Indentation (number of spaces)
 * \param[in] scop            An osl1_scop_t (can be NULL)
 * \param[in] statement       An osl1_statement_t (can be NULL)
 */
void osl1_convex_relation_sprinti_openscop(char** c_str,
                            const osl1_convex_relation_t* const convex_relation,
                            const unsigned int indent,
                            const osl1_scop_t* const scop,
                            const osl1_statement_t* const statement) {
  
  const size_t nb_row = osl1_convex_relation_nb_row(convex_relation);
  const size_t nb_col = osl1_convex_relation_nb_col(convex_relation);
  const size_t nb_output_dim = convex_relation->nb_output_dim;
  const size_t nb_input_dim = convex_relation->nb_input_dim;
  const size_t nb_local_dim = convex_relation->nb_local_dim;
  const size_t nb_parameter = convex_relation->nb_parameter;
  
  gho_c_str_sprinti(c_str, "# nb row, col, output, input, local, param\n",
                    indent);
  gho_sprinti(c_str, indent);
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
  
  gho_c_str_sprinti(c_str, "# Matrix (precision used = ", indent);
  if (convex_relation->precision == GHO_TYPE_LINT) {
    gho_c_str_sprint(c_str, "long int)\n");
  }
  else if (convex_relation->precision == GHO_TYPE_LLINT) {
    gho_c_str_sprint(c_str, "long long int)\n");
  }
  #ifdef osl_with_gmp
  else if (convex_relation->precision == GHO_TYPE_GHO_MPZ_T) {
    gho_c_str_sprint(c_str, "GMP mpz_t)\n");
  }
  #endif
  else {
    fprintf(stderr, "ERROR: osl1_convex_relation_sprinti_openscop: "
                    "unknown precision!\n");
    exit(1);
  }
  
  gho_vector_uint_t column_sizes =
    osl1_convex_relation_column_sizes(convex_relation, scop, statement);
  
  gho_c_str_sprinti(c_str, "#", indent);
  // (In)equation
  {
    const size_t i = 0;
    gho_string_t name =
      osl1_convex_relation_name_column(convex_relation, i, scop, statement);
    osl1_convex_relation_sprint_name(c_str, &name, column_sizes.array[0]);
    gho_string_destroy(&name);
  }
  gho_c_str_sprint(c_str, "|");
  // Output dimensions
  for (size_t i = 0; i < nb_output_dim; ++i) {
    gho_string_t name =
      osl1_convex_relation_name_output_dim(convex_relation, i, scop, statement);
    const size_t column_sizes_i = i + 1;
    osl1_convex_relation_sprint_name(c_str, &name,
                                     column_sizes.array[column_sizes_i]);
    gho_string_destroy(&name);
  }
  gho_c_str_sprint(c_str, "|");
  // Input dimensions
  for (size_t i = 0; i < nb_input_dim; ++i) {
    gho_string_t name =
      osl1_convex_relation_name_input_dim(convex_relation, i, scop, statement);
    const size_t column_sizes_i = 1 + nb_output_dim;
    osl1_convex_relation_sprint_name(c_str, &name,
                                     column_sizes.array[column_sizes_i]);
    gho_string_destroy(&name);
  }
  gho_c_str_sprint(c_str, "|");
  // Local dimensions
  for (size_t i = 0; i < nb_local_dim; ++i) {
    gho_string_t name =
      osl1_convex_relation_name_local_dim(convex_relation, i, scop, statement);
    const size_t column_sizes_i = 1 + nb_output_dim + nb_input_dim;
    osl1_convex_relation_sprint_name(c_str, &name,
                                     column_sizes.array[column_sizes_i]);
    gho_string_destroy(&name);
  }
  gho_c_str_sprint(c_str, "|");
  // Parameters
  for (size_t i = 0; i < nb_parameter; ++i) {
    gho_string_t name =
      osl1_convex_relation_name_parameter(convex_relation, i, scop, statement);
    const size_t column_sizes_i = 1 + nb_output_dim + nb_input_dim +
                                  nb_local_dim;
    osl1_convex_relation_sprint_name(c_str, &name,
                                     column_sizes.array[column_sizes_i]);
    gho_string_destroy(&name);
  }
  gho_c_str_sprint(c_str, "|");
  // Constant
  {
    const size_t i = nb_col - 1;
    gho_string_t name =
      osl1_convex_relation_name_column(convex_relation, i, scop, statement);
    const size_t column_sizes_i = 1 + nb_output_dim + nb_input_dim +
                                  nb_local_dim + nb_parameter;
    osl1_convex_relation_sprint_name(c_str, &name,
                                     column_sizes.array[column_sizes_i]);
    gho_string_destroy(&name);
  }
  gho_c_str_sprint(c_str, "\n");
  
  for (size_t i = 0; i < nb_row; ++i) {
    gho_sprinti(c_str, indent);
    gho_c_str_sprint(c_str, " ");
    for (size_t j = 0; j < nb_col; ++j) {
      // |
      if (j == 1) {
        gho_c_str_sprint(c_str, " ");
      }
      if (j == 1 + nb_output_dim) {
        gho_c_str_sprint(c_str, " ");
      }
      if (j == 1 + nb_output_dim + nb_input_dim) {
        gho_c_str_sprint(c_str, " ");
      }
      if (j == 1 + nb_output_dim + nb_input_dim + nb_local_dim) {
        gho_c_str_sprint(c_str, " ");
      }
      if (j == 1 + nb_output_dim + nb_input_dim + nb_local_dim + nb_parameter) {
        gho_c_str_sprint(c_str, " ");
      }
      // Get convex_relation[i][j]
      gho_coperand_t cop = osl1_convex_relation_cat(convex_relation, i, j);
      gho_string_t cop_string = gho_coperand_to_string(&cop);
      // Display convex_relation[i][j]
      osl1_convex_relation_sprint_name(c_str, &cop_string,
                                       column_sizes.array[j]);
      // Destroy
      gho_string_destroy(&cop_string);
    }
    // Display equation
    gho_c_str_sprint(c_str, "# ");
    bool first_number = true;
    for (size_t j = 1; j < nb_col; ++j) {
      if (osl1_convex_relation_is_0(convex_relation, i, j) == false) {
        // +
        if (first_number == false) { gho_c_str_sprint(c_str, " + "); }
        first_number = false;
        // Coefficient
        if (osl1_convex_relation_is_1(convex_relation, i, j)) {
          if (j == nb_col - 1) {
            gho_c_str_sprint(c_str, "1");
          }
        }
        else if (osl1_convex_relation_is_minus_1(convex_relation, i, j)) {
          if (j == nb_col - 1) {
            gho_c_str_sprint(c_str, "-1");
          }
          else {
            gho_c_str_sprint(c_str, "-");
          }
        }
        else {
          osl1_convex_relation_at_sprint(c_str, convex_relation, i, j);
        }
        // Name of dimension
        if (j != nb_col - 1) {
          gho_string_t name =
            osl1_convex_relation_name_column(convex_relation, j,
                                             scop, statement);
          gho_string_sprint(c_str, &name);
          gho_string_destroy(&name);
        }
      }
      if (j == nb_col - 1) {
        if (first_number) { gho_c_str_sprint(c_str, "0"); }
        if (osl1_convex_relation_is_0(convex_relation, i, j)) {
          gho_c_str_sprint(c_str, " = 0");
        }
        else {
        gho_c_str_sprint(c_str, " >= 0");
        }
      }
    }
    gho_c_str_sprint(c_str, "\n");
  }
  gho_c_str_sprint(c_str, "\n");
  
  gho_vector_uint_destroy(&column_sizes);
  
  gho_c_str_sprinti(c_str, "# Number of convex relation extensions\n", indent);
  gho_size_t_sprinti(c_str, &convex_relation->extensions.size, indent);
  if (convex_relation->extensions.size != 0) {
    gho_c_str_sprint(c_str, "\n");
    gho_c_str_sprinti(c_str, "# Convex relation extensions\n", indent);
    osl1_extensions_sprinti_openscop(c_str, &convex_relation->extensions, indent);
  }
}

/**
 * \brief Print an osl1_convex_relation in a file with indentation
 * \param[in] file            A C file
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] indent          Indentation (number of spaces)
 */
void osl1_convex_relation_fprinti(FILE* file,
                            const osl1_convex_relation_t* const convex_relation,
                            const unsigned int indent) {
  osl1_convex_relation_fprinti_openscop(file, convex_relation, indent,
                                        NULL, NULL);
}

/**
 * \brief Print an osl1_convex_relation in a file
 * \param[in] file            A C file
 * \param[in] convex_relation An osl1_convex_relation
 */
void osl1_convex_relation_fprint(FILE* file,
                           const osl1_convex_relation_t* const convex_relation) {
  osl1_convex_relation_fprinti(file, convex_relation, 0);
}

/**
 * \brief Print an osl1_convex_relation in stdout
 * \param[in] convex_relation An osl1_convex_relation
 */
void osl1_convex_relation_print(const osl1_convex_relation_t* const convex_relation) {
  osl1_convex_relation_fprint(stdout, convex_relation);
}

/**
 * \brief Print an osl1_convex_relation in a C string with indentation
 * \param[in] c_str      A C string
 * \param[in] convex_relation An osl1_convex_relation
 * \param[in] indent     Indentation (number of spaces)
 */
void osl1_convex_relation_sprinti(char** c_str,
                            const osl1_convex_relation_t* const convex_relation,
                            const unsigned int indent) {
  osl1_convex_relation_sprinti_openscop(c_str, convex_relation, indent,
                                        NULL, NULL);
}

/**
 * \brief Print an osl1_convex_relation in a C string
 * \param[in] c_str      A C string
 * \param[in] convex_relation An osl1_convex_relation
 */
void osl1_convex_relation_sprint(char** c_str,
                          const osl1_convex_relation_t* const convex_relation) {
  osl1_convex_relation_sprinti(c_str, convex_relation, 0);
}

// Relation

/**
 * \brief Print an osl1_relation_t in a file with indentation
 * \param[in] file      A C file
 * \param[in] relation  An osl1_relation_t
 * \param[in] indent    Indentation (number of spaces)
 * \param[in] scop      An osl1_scop_t (can be NULL)
 * \param[in] statement An osl1_statement_t (can be NULL)
 */
void osl1_relation_fprinti_openscop(FILE* file,
                                    const osl1_relation_t* const relation,
                                    const unsigned int indent,
                                    const osl1_scop_t* const scop,
                                    const osl1_statement_t* const statement) {
  
  gho_c_str_fprinti(file, "# Number of convex relations\n", indent);
  gho_size_t_fprinti(file, &relation->size, indent);
  gho_c_str_fprint(file, "\n\n");
  
  for (size_t i = 0; i < relation->size; ++i) {
    gho_c_str_fprinti(file, "# Convex relation ", indent);
    const size_t tmp = i + 1;
    gho_size_t_fprint(file, &tmp);
    gho_c_str_fprint(file, " / ");
    gho_size_t_fprint(file, &relation->size);
    gho_c_str_fprint(file, "\n\n");
    osl1_convex_relation_fprinti_openscop(file, &relation->array[i], indent,
                                          scop, statement);
    if (i != relation->size - 1) { gho_c_str_fprint(file, "\n"); }
  }
}

/**
 * \brief Print an osl1_relation_t in a C string with indentation
 * \param[in] c_str     A C string
 * \param[in] relation  An osl1_relation_t
 * \param[in] indent    Indentation (number of spaces)
 * \param[in] scop      An osl1_scop_t (can be NULL)
 * \param[in] statement An osl1_statement_t (can be NULL)
 */
void osl1_relation_sprinti_openscop(char** c_str,
                                    const osl1_relation_t* const relation,
                                    const unsigned int indent,
                                    const osl1_scop_t* const scop,
                                    const osl1_statement_t* const statement) {
  
  gho_c_str_sprinti(c_str, "# Number of convex relations\n", indent);
  gho_size_t_sprinti(c_str, &relation->size, indent);
  gho_c_str_sprint(c_str, "\n\n");
  
  for (size_t i = 0; i < relation->size; ++i) {
    gho_c_str_sprinti(c_str, "# Convex relation ", indent);
    const size_t tmp = i + 1;
    gho_size_t_sprint(c_str, &tmp);
    gho_c_str_sprint(c_str, " / ");
    gho_size_t_sprint(c_str, &relation->size);
    gho_c_str_sprint(c_str, "\n\n");
    osl1_convex_relation_sprinti_openscop(c_str, &relation->array[i], indent,
                                          scop, statement);
    if (i != relation->size - 1) { gho_c_str_sprint(c_str, "\n"); }
  }
}

// Vector of relations

/**
 * \brief Print an osl1_vector_relation_t in a file with indentation
 * \param[in] file      A C file
 * \param[in] relations An osl1_vector_relation_t
 * \param[in] indent    Indentation (number of spaces)
 * \param[in] scop      An osl1_scop_t (can be NULL)
 * \param[in] statement An osl1_statement_t (can be NULL)
 */
void osl1_vector_relation_fprinti_openscop(FILE* file,
                                  const osl1_vector_relation_t* const relations,
                                  const unsigned int indent,
                                  const osl1_scop_t* const scop,
                                  const osl1_statement_t* const statement) {
  
  for (size_t i = 0; i < relations->size; ++i) {
    gho_c_str_fprinti(file, "# Relation ", indent);
    const size_t tmp = i + 1;
    gho_size_t_fprint(file, &tmp);
    gho_c_str_fprint(file, " / ");
    gho_size_t_fprint(file, &relations->size);
    gho_c_str_fprint(file, "\n\n");
    osl1_relation_fprinti_openscop(file, &relations->array[i], indent,
                                   scop, statement);
    if (i != relations->size - 1) { gho_c_str_fprint(file, "\n"); }
  }
}

/**
 * \brief Print an osl1_vector_relation_t in a C string with indentation
 * \param[in] c_str     A C string
 * \param[in] relations An osl1_vector_relation_t
 * \param[in] indent    Indentation (number of spaces)
 * \param[in] scop      An osl1_scop_t (can be NULL)
 * \param[in] statement An osl1_statement_t (can be NULL)
 */
void osl1_vector_relation_sprinti_openscop(char** c_str,
                                  const osl1_vector_relation_t* const relations,
                                  const unsigned int indent,
                                  const osl1_scop_t* const scop,
                                  const osl1_statement_t* const statement) {
  
  for (size_t i = 0; i < relations->size; ++i) {
    gho_c_str_sprinti(c_str, "# Relation ", indent);
    const size_t tmp = i + 1;
    gho_size_t_sprint(c_str, &tmp);
    gho_c_str_sprint(c_str, " / ");
    gho_size_t_sprint(c_str, &relations->size);
    gho_c_str_sprint(c_str, "\n\n");
    osl1_relation_sprinti_openscop(c_str, &relations->array[i], indent,
                                   scop, statement);
    if (i != relations->size - 1) { gho_c_str_sprint(c_str, "\n"); }
  }
}

// Statement

/**
 * \brief Print an osl1_statement_t in a file with indentation
 * \param[in] file      A C file
 * \param[in] statement An osl1_statement_t
 * \param[in] indent    Indentation (number of spaces)
 * \param[in] scop      An osl1_scop_t (can be NULL)
 */
void osl1_statement_fprinti_openscop(FILE* file,
                                     const osl1_statement_t* const statement,
                                     const unsigned int indent,
                                     const osl1_scop_t* const scop) {
  
  gho_c_str_fprinti(file, "# Domain\n", indent);
  gho_c_str_fprinti(file, "# ------\n\n", indent);
  osl1_relation_fprinti_openscop(file, &statement->domain, indent,
                                 scop, statement);
  gho_c_str_fprint(file, "\n\n");
  
  gho_c_str_fprinti(file, "# Scattering\n", indent);
  gho_c_str_fprinti(file, "# ----------\n\n", indent);
  osl1_relation_fprinti_openscop(file, &statement->scattering, indent,
                                 scop, statement);
  gho_c_str_fprint(file, "\n\n");
  
  gho_c_str_fprinti(file, "# Number of accesses relations (read)\n", indent);
  gho_size_t_fprinti(file, &statement->accesses_read.size, indent);
  gho_c_str_fprint(file, "\n\n");
  if (statement->accesses_read.size != 0) {
    gho_c_str_fprinti(file, "# Accesses (read)\n", indent);
    gho_c_str_fprinti(file, "# ---------------\n\n", indent);
    osl1_vector_relation_fprinti_openscop(file, &statement->accesses_read,
                                          indent, scop, statement);
    gho_c_str_fprint(file, "\n\n");
  }
  
  gho_c_str_fprinti(file, "# Number of accesses relations (write)\n", indent);
  gho_size_t_fprinti(file, &statement->accesses_write.size, indent);
  gho_c_str_fprint(file, "\n\n");
  if (statement->accesses_write.size != 0) {
    gho_c_str_fprinti(file, "# Accesses (write)\n", indent);
    gho_c_str_fprinti(file, "# ----------------\n\n", indent);
    osl1_vector_relation_fprinti_openscop(file, &statement->accesses_write,
                                          indent, scop, statement);
    gho_c_str_fprint(file, "\n\n");
  }
  
  gho_c_str_fprinti(file, "# Number of statement extensions\n", indent);
  gho_size_t_fprinti(file, &statement->extensions.size, indent);
  gho_c_str_fprint(file, "\n\n");
  gho_c_str_fprinti(file, "# Statement extensions\n", indent);
  gho_c_str_fprinti(file, "# --------------------\n\n", indent);
  osl1_extensions_fprinti_openscop(file, &statement->extensions, indent);
}

/**
 * \brief Print an osl1_statement_t in a C string with indentation
 * \param[in] c_str     A C string
 * \param[in] statement An osl1_statement_t
 * \param[in] indent    Indentation (number of spaces)
 * \param[in] scop      An osl1_scop_t (can be NULL)
 */
void osl1_statement_sprinti_openscop(char** c_str,
                                     const osl1_statement_t* const statement,
                                     const unsigned int indent,
                                     const osl1_scop_t* const scop) {
  
  gho_c_str_sprinti(c_str, "# Domain\n", indent);
  gho_c_str_sprinti(c_str, "# ------\n\n", indent);
  osl1_relation_sprinti_openscop(c_str, &statement->domain, indent,
                                 scop, statement);
  gho_c_str_sprint(c_str, "\n\n");
  
  gho_c_str_sprinti(c_str, "# Scattering\n", indent);
  gho_c_str_sprinti(c_str, "# ----------\n\n", indent);
  osl1_relation_sprinti_openscop(c_str, &statement->scattering, indent,
                                 scop, statement);
  gho_c_str_sprint(c_str, "\n\n");
  
  gho_c_str_sprinti(c_str, "# Number of accesses relations (read)\n", indent);
  gho_size_t_sprinti(c_str, &statement->accesses_read.size, indent);
  gho_c_str_sprint(c_str, "\n\n");
  if (statement->accesses_read.size != 0) {
    gho_c_str_sprinti(c_str, "# Accesses (read)\n", indent);
    gho_c_str_sprinti(c_str, "# ---------------\n\n", indent);
    osl1_vector_relation_sprinti_openscop(c_str, &statement->accesses_read,
                                          indent, scop, statement);
    gho_c_str_sprint(c_str, "\n\n");
  }
  
  gho_c_str_sprinti(c_str, "# Number of accesses relations (write)\n", indent);
  gho_size_t_sprinti(c_str, &statement->accesses_write.size, indent);
  gho_c_str_sprint(c_str, "\n\n");
  if (statement->accesses_write.size != 0) {
    gho_c_str_sprinti(c_str, "# Accesses (write)\n", indent);
    gho_c_str_sprinti(c_str, "# ----------------\n\n", indent);
    osl1_vector_relation_sprinti_openscop(c_str, &statement->accesses_write,
                                          indent, scop, statement);
    gho_c_str_sprint(c_str, "\n\n");
  }
  
  gho_c_str_sprinti(c_str, "# Number of statement extensions\n", indent);
  gho_size_t_sprinti(c_str, &statement->extensions.size, indent);
  gho_c_str_sprint(c_str, "\n\n");
  gho_c_str_sprinti(c_str, "# Statement extensions\n", indent);
  gho_c_str_sprinti(c_str, "# --------------------\n\n", indent);
  osl1_extensions_sprinti_openscop(c_str, &statement->extensions, indent);
}

// Vector of statements

/**
 * \brief Print an osl1_vector_statement_t in a file with indentation
 * \param[in] file       A C file
 * \param[in] statements An osl1_vector_statement_t
 * \param[in] indent     Indentation (number of spaces)
 * \param[in] scop       An osl1_scop_t (can be NULL)
 */
void osl1_vector_statement_fprinti_openscop(FILE* file,
                                const osl1_vector_statement_t* const statements,
                                const unsigned int indent,
                                const osl1_scop_t* const scop) {
  gho_c_str_fprinti(file, "# Number of statements\n", indent);
  gho_size_t_fprinti(file, &statements->size, indent);
  gho_c_str_fprint(file, "\n\n");
  
  for (size_t i = 0; i < statements->size; ++i) {
    gho_c_str_fprint(file, "# Statement ");
    const size_t tmp = i + 1;
    gho_size_t_fprint(file, &tmp);
    gho_c_str_fprint(file, " / ");
    gho_size_t_fprint(file, &statements->size);
    gho_c_str_fprint(file, "\n");
    gho_c_str_fprint(file, "# ---------------\n\n");
    osl1_statement_fprinti_openscop(file, &statements->array[i], indent + 4,
                                    scop);
    if (i != statements->size - 1) { gho_c_str_fprint(file, "\n\n"); }
  }
}

/**
 * \brief Print an osl1_vector_statement_t in a C string with indentation
 * \param[in] c_str      A C string
 * \param[in] statements An osl1_vector_statement_t
 * \param[in] indent     Indentation (number of spaces)
 * \param[in] scop       An osl1_scop_t (can be NULL)
 */
void osl1_vector_statement_sprinti_openscop(char** c_str,
                                const osl1_vector_statement_t* const statements,
                                const unsigned int indent,
                                const osl1_scop_t* const scop) {
  gho_c_str_sprinti(c_str, "# Number of statements\n", indent);
  gho_size_t_sprinti(c_str, &statements->size, indent);
  gho_c_str_sprint(c_str, "\n\n");
  
  for (size_t i = 0; i < statements->size; ++i) {
    gho_c_str_sprint(c_str, "# Statement ");
    const size_t tmp = i + 1;
    gho_size_t_sprint(c_str, &tmp);
    gho_c_str_sprint(c_str, " / ");
    gho_size_t_sprint(c_str, &statements->size);
    gho_c_str_sprint(c_str, "\n");
    gho_c_str_sprint(c_str, "# ---------------\n\n");
    osl1_statement_sprinti_openscop(c_str, &statements->array[i], indent + 4,
                                    scop);
    if (i != statements->size - 1) { gho_c_str_sprint(c_str, "\n\n"); }
  }
}

// SCoP

/**
 * \brief Print an osl1_scop_t in a file with indentation
 * \param[in] file   A C file
 * \param[in] scop   An osl1_scop_t
 * \param[in] indent Indentation (number of spaces)
 */
void osl1_scop_fprinti_openscop(FILE* file,
                                const osl1_scop_t* const scop,
                                const unsigned int indent) {
  
  gho_c_str_fprinti(file, "<OpenScop1>\n", indent);
  gho_c_str_fprint(file, "\n");
  
  gho_c_str_fprinti(file, "# Context\n", indent);
  gho_c_str_fprinti(file, "# -------\n\n", indent);
  osl1_relation_fprinti_openscop(file, &scop->context, indent, scop, NULL);
  gho_c_str_fprint(file, "\n\n");
  
  gho_c_str_fprinti(file, "# Parameters\n", indent);
  gho_c_str_fprinti(file, "# ----------\n", indent);
  gho_size_t_fprinti(file, &scop->parameters.size, indent);
  gho_c_str_fprint(file, "\n");
  for (size_t i = 0; i < scop->parameters.size; ++i) {
    gho_string_fprinti(file, &scop->parameters.array[i], indent);
    gho_c_str_fprint(file, " ");
  }
  gho_c_str_fprint(file, "\n\n");
  
  osl1_vector_statement_fprinti_openscop(file, &scop->statements, indent,
                                         scop);
  gho_c_str_fprint(file, "\n\n");
  
  gho_c_str_fprinti(file, "# Number of SCoP extensions\n", indent);
  gho_size_t_fprinti(file, &scop->extensions.size, indent);
  gho_c_str_fprint(file, "\n\n");
  gho_c_str_fprinti(file, "# SCoP extensions\n", indent);
  gho_c_str_fprinti(file, "# ---------------\n\n", indent);
  osl1_extensions_fprinti_openscop(file, &scop->extensions, indent);
  gho_c_str_fprint(file, "\n\n");
  
  gho_c_str_fprinti(file, "</OpenScop1>", indent);
}

/**
 * \brief Print an osl1_scop_t in a C string with indentation
 * \param[in] c_str  A C string
 * \param[in] scop   An osl1_scop_t
 * \param[in] indent Indentation (number of spaces)
 */
void osl1_scop_sprinti_openscop(char** c_str,
                                const osl1_scop_t* const scop,
                                const unsigned int indent) {
  
  gho_c_str_sprinti(c_str, "<OpenScop1>\n", indent);
  gho_c_str_sprint(c_str, "\n");
  
  gho_c_str_sprinti(c_str, "# Context\n", indent);
  gho_c_str_sprinti(c_str, "# -------\n\n", indent);
  osl1_relation_sprinti_openscop(c_str, &scop->context, indent, scop, NULL);
  gho_c_str_sprint(c_str, "\n\n");
  
  gho_c_str_sprinti(c_str, "# Parameters\n", indent);
  gho_c_str_sprinti(c_str, "# ----------\n", indent);
  gho_size_t_sprinti(c_str, &scop->parameters.size, indent);
  gho_c_str_sprint(c_str, "\n");
  for (size_t i = 0; i < scop->parameters.size; ++i) {
    gho_string_sprinti(c_str, &scop->parameters.array[i], indent);
    gho_c_str_sprint(c_str, " ");
  }
  gho_c_str_sprint(c_str, "\n\n");
  
  osl1_vector_statement_sprinti_openscop(c_str, &scop->statements, indent,
                                         scop);
  gho_c_str_sprint(c_str, "\n\n");
  
  gho_c_str_sprinti(c_str, "# Number of SCoP extensions\n", indent);
  gho_size_t_sprinti(c_str, &scop->extensions.size, indent);
  gho_c_str_sprint(c_str, "\n\n");
  gho_c_str_sprinti(c_str, "# SCoP extensions\n", indent);
  gho_c_str_sprinti(c_str, "# ---------------\n\n", indent);
  osl1_extensions_sprinti_openscop(c_str, &scop->extensions, indent);
  gho_c_str_sprint(c_str, "\n\n");
  
  gho_c_str_sprinti(c_str, "</OpenScop1>", indent);
}

// Vector of SCoP
