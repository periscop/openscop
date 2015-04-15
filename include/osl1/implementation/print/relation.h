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

#include "../../print.h"


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
