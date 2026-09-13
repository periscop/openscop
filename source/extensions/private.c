/******************************************************************************
 **                            OpenScop Library                              **
 **--------------------------------------------------------------------------**
 **                           extensions/private.c                           **
 **--------------------------------------------------------------------------**
 **                        First version: 13/09/2026                         **
 ******************************************************************************/

/******************************************************************************
 * OpenScop: Structures and formats for polyhedral tools to talk together     *
 ******************************************************************************
 *    ,___,,_,__,,__,,__,,__,,_,__,,_,__,,__,,___,_,__,,_,__,                 *
 *    /   / /  //  //  //  // /   / /  //  //   / /  // /  /|,_,              *
 *   /   / /  //  //  //  // /   / /  //  //   / /  // /  / / /\              *
 *  |~~~|~|~~~|~~~|~~~|~~~|~|~~~|~|~~~|~~~|~~~|~|~~~|~|~~~|/_/  \             *
 *  | G |C| P | = | L | P |=| = |C| = | = | = |=| = |=| C |\  \ /\            *
 *  | R |l| o | = | e | l |=| = |a| = | = | = |=| = |=| L | \# \ /\           *
 *  | A |a| l | = | t | u |=| = |n| = | = | = |=| = |=| o | |\# \  \          *
 *  | P |n| l | = | s | t |=| = |d| = | = | = | |   |=| o | | \# \  \         *
 *  | H | | y |   | e | o | | = |l|   |   | = | |   | | G | |  \  \  \        *
 *  | I | |   |   | e |   | |   | |   |   |   | |   | |   | |   \  \  \       *
 *  | T | |   |   |   |   | |   | |   |   |   | |   | |   | |    \  \  \      *
 *  | E | |   |   |   |   | |   | |   |   |   | |   | |   | |     \  \  \     *
 *  | * |*| * | * | * | * |*| * |*| * | * | * |*| * |*| * | /      \* \  \    *
 *  | O |p| e | n | S | c |o| p |-| L | i | b |r| a |r| y |/        \  \ /    *
 *  '---'-'---'---'---'---'-'---'-'---'---'---'-'---'-'---'          '--'     *
 *                                                                            *
 * Copyright (C) 2008 University Paris-Sud 11 and INRIA                       *
 *                                                                            *
 * (3-clause BSD license)                                                     *
 * Redistribution and use in source  and binary forms, with or without        *
 * modification, are permitted provided that the following conditions         *
 * are met:                                                                   *
 *                                                                            *
 * 1. Redistributions of source code must retain the above copyright notice,  *
 *    this list of conditions and the following disclaimer.                   *
 * 2. Redistributions in binary form must reproduce the above copyright       *
 *    notice, this list of conditions and the following disclaimer in the     *
 *    documentation and/or other materials provided with the distribution.    *
 * 3. The name of the author may not be used to endorse or promote products   *
 *    derived from this software without specific prior written permission.   *
 *                                                                            *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR       *
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES  *
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.    *
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,           *
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT   *
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY      *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT        *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF   *
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.          *
 *                                                                            *
 * OpenScop Library, a library to manipulate OpenScop formats and data        *
 * structures. Written by:                                                    *
 * Cedric Bastoul     <Cedric.Bastoul@u-psud.fr> and                          *
 * Louis-Noel Pouchet <Louis-Noel.pouchet@inria.fr>                           *
 *                                                                            *
 ******************************************************************************/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <osl/macros.h>
#include <osl/util.h>

#include <osl/extensions/private.h>

/******************************************************************************
 *                          Structure display function                        *
 ******************************************************************************/

/**
 * osl_private_idump function:
 * this function displays a private structure with an indentation level.
 * \param[in] file  The file where the information has to be printed.
 * \param[in] priv  The private structure to print.
 * \param[in] level The indentation level.
 */
void osl_private_idump(FILE* const file, const osl_private_t* const priv,
                       int level) {
  int i, j;

  for (j = 0; j < level; j++) {
    fprintf(file, "|\t");
  }
  if (priv != NULL) {
    fprintf(file, "+-- osl_private_t\n");
    for (j = 0; j <= level; j++) {
      fprintf(file, "|\t");
    }
    fprintf(file, "nb_variables: %d\n", priv->nb_variables);
    for (i = 0; i < priv->nb_variables; i++) {
      for (j = 0; j <= level; j++) {
        fprintf(file, "|\t");
      }
      fprintf(file, "array_id: %d, stmt_id: %d, nb_dims: %d\n",
              priv->array_id[i], priv->stmt_id[i], priv->nb_dims[i]);
    }
  } else {
    fprintf(file, "+-- NULL private\n");
  }
  for (j = 0; j <= level; j++) {
    fprintf(file, "|\t");
  }
  fprintf(file, "\n");
}

/**
 * osl_private_dump function:
 * this function displays a private structure without indentation.
 * \param[in] file The file where the information has to be printed.
 * \param[in] priv The private structure to print.
 */
void osl_private_dump(FILE* const file, const osl_private_t* const priv) {
  osl_private_idump(file, priv, 0);
}

/**
 * osl_private_sprint function:
 * this function prints a private structure in the OpenScop textual format.
 * \param[in] priv The private structure to print.
 * \return An allocated string, or NULL if priv is NULL.
 */
char* osl_private_sprint(const osl_private_t* const priv) {
  char* text;
  char buffer[128];
  size_t capacity = OSL_MAX_STRING;
  int i;

  if (priv == NULL) {
    return NULL;
  }
  OSL_malloc(text, char*, capacity);
  snprintf(text, capacity, "# Number of loop private variables\n%d\n"
           "# Loop private variables information\n", priv->nb_variables);
  for (i = 0; i < priv->nb_variables; i++) {
    snprintf(buffer, sizeof(buffer), "%d %d %d\n", priv->array_id[i],
             priv->stmt_id[i], priv->nb_dims[i]);
    osl_util_safe_strcat(&text, buffer, &capacity);
  }
  return text;
}

/******************************************************************************
 *                               Reading function                             *
 ******************************************************************************/

/**
 * osl_private_sread function:
 * this function reads a private structure from the OpenScop textual format.
 * \param[in,out] input The input string, advanced past the data read.
 * \return The private structure that has been read, or NULL for NULL input.
 */
osl_private_t* osl_private_sread(char** input) {
  osl_private_p priv;
  int count, i, array_id, stmt_id, nb_dims;

  if (input == NULL || *input == NULL) {
    return NULL;
  }
  count = osl_util_read_int(NULL, input);
  if (count < 0) {
    OSL_error("negative private variable count");
  }
  priv = osl_private_malloc();
  for (i = 0; i < count; i++) {
    array_id = osl_util_read_int(NULL, input);
    stmt_id = osl_util_read_int(NULL, input);
    nb_dims = osl_util_read_int(NULL, input);
    osl_private_add(priv, array_id, stmt_id, nb_dims);
  }
  return priv;
}

/******************************************************************************
 *                    Memory allocation/deallocation function                 *
 ******************************************************************************/

/**
 * osl_private_malloc function:
 * this function allocates an empty private structure.
 * \return A private structure with its fields set to default values.
 */
osl_private_t* osl_private_malloc(void) {
  osl_private_p priv;

  OSL_malloc(priv, osl_private_p, sizeof(*priv));
  priv->nb_variables = 0;
  priv->array_id = NULL;
  priv->stmt_id = NULL;
  priv->nb_dims = NULL;
  return priv;
}

/**
 * osl_private_free function:
 * this function frees a private structure and its arrays.
 * \param[in,out] priv The private structure to free (may be NULL).
 */
void osl_private_free(osl_private_t* const priv) {
  if (priv != NULL) {
    free(priv->array_id);
    free(priv->stmt_id);
    free(priv->nb_dims);
    free(priv);
  }
}

/******************************************************************************
 *                            Processing functions                            *
 ******************************************************************************/

/**
 * osl_private_add function:
 * this function appends one scalar expansion entry to a private structure.
 * Identifiers and dimension counts must be positive; array IDs must be unique.
 * \param[in,out] priv The private structure to update.
 * \param[in] array_id The identifier used in the array's access relations.
 * \param[in] stmt_id  The one-based declaration statement number.
 * \param[in] nb_dims  The number of leading expansion dimensions.
 */
void osl_private_add(osl_private_t* const priv, int array_id, int stmt_id,
                      int nb_dims) {
  int i, n = priv->nb_variables;

  if (array_id <= 0 || stmt_id <= 0 || nb_dims <= 0 || n == INT_MAX) {
    OSL_error("invalid private variable entry");
  }
  for (i = 0; i < n; i++) {
    if (priv->array_id[i] == array_id) {
      OSL_error("duplicate private variable identifier");
    }
  }
  OSL_realloc(priv->array_id, int*, ((size_t)n + 1) * sizeof(int));
  OSL_realloc(priv->stmt_id, int*, ((size_t)n + 1) * sizeof(int));
  OSL_realloc(priv->nb_dims, int*, ((size_t)n + 1) * sizeof(int));
  priv->array_id[n] = array_id;
  priv->stmt_id[n] = stmt_id;
  priv->nb_dims[n] = nb_dims;
  priv->nb_variables++;
}

/**
 * osl_private_clone function:
 * this function builds a deep copy of a private structure.
 * \param[in] priv The private structure to clone.
 * \return An independent copy, or NULL if priv is NULL.
 */
osl_private_t* osl_private_clone(const osl_private_t* const priv) {
  osl_private_p clone;
  int i;

  if (priv == NULL) {
    return NULL;
  }
  clone = osl_private_malloc();
  for (i = 0; i < priv->nb_variables; i++) {
    osl_private_add(clone, priv->array_id[i], priv->stmt_id[i], priv->nb_dims[i]);
  }
  return clone;
}

/**
 * osl_private_equal function:
 * this function compares two private structures, ignoring entry order.
 * \param[in] a The first private structure.
 * \param[in] b The second private structure.
 * \return true if their entries agree, false otherwise.
 */
bool osl_private_equal(const osl_private_t* const a,
                        const osl_private_t* const b) {
  int i, j;

  if (a == b) {
    return true;
  }
  if (a == NULL || b == NULL || a->nb_variables != b->nb_variables) {
    return false;
  }
  for (i = 0; i < a->nb_variables; i++) {
    for (j = 0; j < b->nb_variables; j++) {
      if (a->array_id[i] == b->array_id[j]) {
        break;
      }
    }
    if (j == b->nb_variables || a->stmt_id[i] != b->stmt_id[j] ||
        a->nb_dims[i] != b->nb_dims[j]) {
      return false;
    }
  }
  return true;
}

/**
 * osl_private_interface function:
 * this function creates an interface for the private extension.
 * \return An allocated private extension interface.
 */
osl_interface_t* osl_private_interface(void) {
  osl_interface_p interface = osl_interface_malloc();

  OSL_strdup(interface->URI, OSL_URI_PRIVATE);
  interface->idump = (osl_idump_f)osl_private_idump;
  interface->sprint = (osl_sprint_f)osl_private_sprint;
  interface->sread = (osl_sread_f)osl_private_sread;
  interface->malloc = (osl_malloc_f)osl_private_malloc;
  interface->free = (osl_free_f)osl_private_free;
  interface->clone = (osl_clone_f)osl_private_clone;
  interface->equal = (osl_equal_f)osl_private_equal;
  return interface;
}
