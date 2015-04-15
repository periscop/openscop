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

/**
 * \brief Print an osl1_scop in a file with indentation
 * \param[in] file   A C file
 * \param[in] scop   An osl1_scop
 * \param[in] indent Indentation (number of spaces)
 */
void osl1_scop_fprinti(FILE* file, const osl1_scop_t* const scop,
                       const unsigned int indent) {
  osl1_scop_fprinti_openscop(file, scop, indent);
}

/**
 * \brief Print an osl1_scop in a file
 * \param[in] file A C file
 * \param[in] scop An osl1_scop
 */
void osl1_scop_fprint(FILE* file, const osl1_scop_t* const scop) {
  osl1_scop_fprinti(file, scop, 0);
}

/**
 * \brief Print an osl1_scop in stdout
 * \param[in] scop An osl1_scop
 */
void osl1_scop_print(const osl1_scop_t* const scop) {
  osl1_scop_fprint(stdout, scop);
}

/**
 * \brief Print an osl1_scop in a C string with indentation
 * \param[in] c_str  A C string
 * \param[in] scop   An osl1_scop
 * \param[in] indent Indentation (number of spaces)
 */
void osl1_scop_sprinti(char** c_str, const osl1_scop_t* const scop,
                       const unsigned int indent) {
  osl1_scop_sprinti_openscop(c_str, scop, indent);
}

/**
 * \brief Print an osl1_scop in a C string
 * \param[in] c_str A C string
 * \param[in] scop  An osl1_scop
 */
void osl1_scop_sprint(char** c_str, const osl1_scop_t* const scop) {
  osl1_scop_sprinti(c_str, scop, 0);
}
