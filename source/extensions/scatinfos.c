/******************************************************************************
 **                            OpenScop Library                              **
 **--------------------------------------------------------------------------**
 **                         extensions/scatinfos.c                           **
 **--------------------------------------------------------------------------**
 **                        First version: 07/12/2010                         **
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <osl/interface.h>
#include <osl/macros.h>
#include <osl/util.h>

#include <osl/extensions/scatinfos.h>

/******************************************************************************
 *                          Structure display function                        *
 ******************************************************************************/

/**
 * osl_scatinfos_idump function:
 * this function displays an osl_scatinfos_t structure (*scatinfos) into a
 * file (file, possibly stdout) in a way that trends to be understandable. It
 * includes an indentation level (level) in order to work with others
 * idump functions.
 * \param[in] file      The file where the information has to be printed.
 * \param[in] scatinfos The scatinfos structure to print.
 * \param[in] level     Number of spaces before printing, for each line.
 */
void osl_scatinfos_idump(FILE* const file,
                         const osl_scatinfos_t* const scatinfos, int level) {
  // Go to the right level.
  for (size_t j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (scatinfos != NULL)
    fprintf(file, "+-- osl_scatinfos_t\n");
  else
    fprintf(file, "+-- NULL scatinfos\n");

  if (scatinfos != NULL) {
    // Go to the right level.
    for (size_t j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "+--nb_scatdims: %zu\n", scatinfos->nb_scatdims);

    // A blank line.
    for (size_t j = 0; j <= level + 1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    // Display the parallel info.
    for (size_t j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "+--parallel--: ");
    for (size_t i = 0; i < scatinfos->nb_scatdims; i++) {
      fprintf(file, "%d, ", scatinfos->parallel[i]);
    }
    fprintf(file, "\n");

    // A blank line.
    for (size_t j = 0; j <= level + 1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    // Display the permutable info.
    for (size_t j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "+--permutable: ");
    for (size_t i = 0; i < scatinfos->nb_scatdims; i++) {
      fprintf(file, "%d, ", scatinfos->permutable[i]);
    }
    fprintf(file, "\n");

    // A blank line.
    for (size_t j = 0; j <= level + 1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    // Display the type info.
    for (size_t j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "+--type------: ");
    for (size_t i = 0; i < scatinfos->nb_scatdims; i++) {
      fprintf(file, "%d, ", scatinfos->type[i]);
    }
    fprintf(file, "\n");
  }

  // The last line.
  for (size_t j = 0; j <= level; j++)
    fprintf(file, "|\t");
  fprintf(file, "\n");
}

/**
 * osl_scatinfos_dump function:
 * this function prints the content of an osl_scatinfos_t structure
 * (*scatinfos) into a file (file, possibly stdout).
 * \param[in] file      The file where the information has to be printed.
 * \param[in] scatinfos The scatinfos structure to print.
 */
void osl_scatinfos_dump(FILE* const file,
                        const osl_scatinfos_t* const scatinfos) {
  osl_scatinfos_idump(file, scatinfos, 0);
}

/**
 * osl_scatinfos_sprint function:
 * this function prints the content of an osl_scatinfos_t structure
 * (*scatinfos) into a string (returned) in the OpenScop textual format.
 * \param[in] scatinfos The scatinfos structure to print.
 * \return A string containing the OpenScop dump of the scatinfos structure.
 */
char* osl_scatinfos_sprint(const osl_scatinfos_t* const scatinfos) {
  size_t high_water_mark = OSL_MAX_STRING;
  char* string = NULL;
  char buffer[OSL_MAX_STRING];

  if (scatinfos != NULL) {
    OSL_malloc(string, char*, high_water_mark * sizeof(char));
    string[0] = '\0';

    sprintf(buffer, "# Number of scattering dimensions\n");
    osl_util_safe_strcat(&string, buffer, &high_water_mark);
    sprintf(buffer, "%zu\n", scatinfos->nb_scatdims);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);

    if (scatinfos->nb_scatdims > 0) {
      sprintf(buffer, "# Parallel info\n");
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }
    for (size_t i = 0; i < scatinfos->nb_scatdims; i++) {
      sprintf(buffer, "%d ", scatinfos->parallel[i]);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (scatinfos->nb_scatdims > 0) {
      sprintf(buffer, "\n# Permutable info\n");
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }
    for (size_t i = 0; i < scatinfos->nb_scatdims; i++) {
      sprintf(buffer, "%d ", scatinfos->permutable[i]);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (scatinfos->nb_scatdims > 0) {
      sprintf(buffer, "\n# Type info\n");
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }
    for (size_t i = 0; i < scatinfos->nb_scatdims; i++) {
      sprintf(buffer, "%d ", scatinfos->type[i]);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (scatinfos->nb_scatdims > 0) {
      sprintf(buffer, "\n");
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }
    // Keep only the memory space we need.
    OSL_realloc(string, char*, (strlen(string) + 1) * sizeof(char));
  }

  return string;
}

/******************************************************************************
 *                               Reading function                             *
 ******************************************************************************/

/**
 * osl_scatinfos_sread function:
 * this function reads a scatinfos structure from a string complying to the
 * OpenScop textual format and returns a pointer to this scatinfos structure.
 * The input parameter is updated to the position in the input string this
 * function reach right after reading the scatinfos structure.
 * \param[in,out] input The input string where to find a scatinfos.
 *                      Updated to the position after what has been read.
 * \return A pointer to the scatinfos structure that has been read.
 */
osl_scatinfos_t* osl_scatinfos_sread(char** input) {
  osl_scatinfos_p scatinfos;

  if (*input == NULL) {
    OSL_debug("no scatinfos optional tag");
    return NULL;
  }

  scatinfos = osl_scatinfos_malloc();
  scatinfos->nb_scatdims = (size_t)osl_util_read_int(NULL, input);

  OSL_malloc(scatinfos->parallel, int*, scatinfos->nb_scatdims * sizeof(int));
  for (size_t i = 0; i < scatinfos->nb_scatdims; i++)
    scatinfos->parallel[i] = osl_util_read_int(NULL, input);

  OSL_malloc(scatinfos->permutable, int*, scatinfos->nb_scatdims * sizeof(int));
  for (size_t i = 0; i < scatinfos->nb_scatdims; i++)
    scatinfos->permutable[i] = osl_util_read_int(NULL, input);

  OSL_malloc(scatinfos->type, int*, scatinfos->nb_scatdims * sizeof(int));
  for (size_t i = 0; i < scatinfos->nb_scatdims; i++)
    scatinfos->type[i] = osl_util_read_int(NULL, input);

  return scatinfos;
}

/******************************************************************************
 *                    Memory allocation/deallocation function                 *
 ******************************************************************************/

/**
 * osl_scatinfos_malloc function:
 * this function allocates the memory space for an osl_scatinfos_t
 * structure and sets its fields with default values. Then it returns a
 * pointer to the allocated space.
 * \return A pointer to an empty scatinfos structure with fields set to
 *         default values.
 */
osl_scatinfos_t* osl_scatinfos_malloc(void) {
  osl_scatinfos_p scatinfos;

  OSL_malloc(scatinfos, osl_scatinfos_p, sizeof(osl_scatinfos_t));
  scatinfos->nb_scatdims = 0;
  scatinfos->parallel = NULL;
  scatinfos->permutable = NULL;
  scatinfos->type = NULL;

  return scatinfos;
}

/**
 * osl_scatinfos_free function:
 * this function frees the allocated memory for an osl_scatinfos_t
 * structure.
 * \param[in,out] scatinfos The pointer to the scatinfos structure to free.
 */
void osl_scatinfos_free(osl_scatinfos_t* scatinfos) {
  if (scatinfos) {
    if (scatinfos->parallel)
      free(scatinfos->parallel);
    if (scatinfos->permutable)
      free(scatinfos->permutable);
    if (scatinfos->type)
      free(scatinfos->type);
    free(scatinfos);
  }
}

/******************************************************************************
 *                            Processing functions                            *
 ******************************************************************************/

/**
 * osl_scatinfos_clone function:
 * this function builds and returns a "hard copy" (not a pointer copy) of an
 * osl_scatinfos_t data structure.
 * \param[in] scatinfos The pointer to the scatinfos structure to clone.
 * \return A pointer to the clone of the scatinfos structure.
 */
osl_scatinfos_t* osl_scatinfos_clone(const osl_scatinfos_t* const scatinfos) {
  osl_scatinfos_p clone;

  if (scatinfos == NULL)
    return NULL;

  clone = osl_scatinfos_malloc();
  clone->nb_scatdims = scatinfos->nb_scatdims;

  OSL_malloc(clone->parallel, int*, clone->nb_scatdims * sizeof(int));
  for (size_t i = 0; i < clone->nb_scatdims; i++)
    clone->parallel[i] = scatinfos->parallel[i];

  OSL_malloc(clone->permutable, int*, clone->nb_scatdims * sizeof(int));
  for (size_t i = 0; i < clone->nb_scatdims; i++)
    clone->permutable[i] = scatinfos->permutable[i];

  OSL_malloc(clone->type, int*, clone->nb_scatdims * sizeof(int));
  for (size_t i = 0; i < clone->nb_scatdims; i++)
    clone->type[i] = scatinfos->type[i];

  return clone;
}

/**
 * osl_scatinfos_equal function:
 * this function returns true if the two scatinfos structures are the same
 * (content-wise), false otherwise.
 * \param[in] c1  The first scatinfos structure.
 * \param[in] c2  The second scatinfos structure.
 * \return 1 if c1 and c2 are the same (content-wise), 0 otherwise.
 */
bool osl_scatinfos_equal(const osl_scatinfos_t* const c1,
                         const osl_scatinfos_t* const c2) {
  if (c1 == c2)
    return 1;

  if (((c1 == NULL) && (c2 != NULL)) || ((c1 != NULL) && (c2 == NULL))) {
    OSL_info("scatinfos are not the same");
    return 0;
  }

  // Check whether the number of scattering dimensions is the same.
  if (c1->nb_scatdims != c2->nb_scatdims) {
    return 0;
  }

  // Chech whether info is the same
  for (size_t i = 0; i < c1->nb_scatdims; i++) {
    if (c1->parallel[i] != c2->parallel[i])
      return 0;
    if (c1->permutable[i] != c2->permutable[i])
      return 0;
    if (c1->type[i] != c2->type[i])
      return 0;
  }

  return 1;
}

/**
 * osl_scatinfos_interface function:
 * this function creates an interface structure corresponding to the scatinfos
 * extension and returns it).
 * \return An interface structure for the scatinfos extension.
 */
osl_interface_t* osl_scatinfos_interface(void) {
  osl_interface_p interface = osl_interface_malloc();

  OSL_strdup(interface->URI, OSL_URI_SCATINFOS);
  interface->idump = (osl_idump_f)osl_scatinfos_idump;
  interface->sprint = (osl_sprint_f)osl_scatinfos_sprint;
  interface->sread = (osl_sread_f)osl_scatinfos_sread;
  interface->malloc = (osl_malloc_f)osl_scatinfos_malloc;
  interface->free = (osl_free_f)osl_scatinfos_free;
  interface->clone = (osl_clone_f)osl_scatinfos_clone;
  interface->equal = (osl_equal_f)osl_scatinfos_equal;

  return interface;
}
