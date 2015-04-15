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
  
  gho_c_str_fprinti(file, "# Id = ", indent);
  gho_size_t_fprint(file, &statement->id);
  gho_c_str_fprint(file, "\n\n");
  
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
  
  gho_c_str_sprinti(c_str, "# Id = ", indent);
  gho_size_t_sprint(c_str, &statement->id);
  gho_c_str_sprint(c_str, "\n\n");
  
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

/**
 * \brief Print an osl1_statement in a file with indentation
 * \param[in] file      A C file
 * \param[in] statement An osl1_statement
 * \param[in] indent    Indentation (number of spaces)
 */
void osl1_statement_fprinti(FILE* file,
                            const osl1_statement_t* const statement,
                            const unsigned int indent) {
  osl1_statement_fprinti_openscop(file, statement, indent, NULL);
}

/**
 * \brief Print an osl1_statement in a file
 * \param[in] file      A C file
 * \param[in] statement An osl1_statement
 */
void osl1_statement_fprint(FILE* file,
                           const osl1_statement_t* const statement) {
  osl1_statement_fprinti(file, statement, 0);
}

/**
 * \brief Print an osl1_statement in stdout
 * \param[in] statement An osl1_statement
 */
void osl1_statement_print(const osl1_statement_t* const statement) {
  osl1_statement_fprint(stdout, statement);
}

/**
 * \brief Print an osl1_statement in a C string with indentation
 * \param[in] c_str     A C string
 * \param[in] statement An osl1_statement
 * \param[in] indent    Indentation (number of spaces)
 */
void osl1_statement_sprinti(char** c_str,
                            const osl1_statement_t* const statement,
                            const unsigned int indent) {
  osl1_statement_sprinti_openscop(c_str, statement, indent, NULL);
}

/**
 * \brief Print an osl1_statement in a C string
 * \param[in] c_str     A C string
 * \param[in] statement An osl1_statement
 */
void osl1_statement_sprint(char** c_str,
                           const osl1_statement_t* const statement) {
  osl1_statement_sprinti(c_str, statement, 0);
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
