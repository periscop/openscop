
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                      extensions/names.c                         **
     **-----------------------------------------------------------------**
     **                   First version: 18/04/2011                     **
     **-----------------------------------------------------------------**

 
 *****************************************************************************
 * OpenScop: Structures and formats for polyhedral tools to talk together    *
 *****************************************************************************
 *    ,___,,_,__,,__,,__,,__,,_,__,,_,__,,__,,___,_,__,,_,__,                *
 *    /   / /  //  //  //  // /   / /  //  //   / /  // /  /|,_,             *
 *   /   / /  //  //  //  // /   / /  //  //   / /  // /  / / /\             *
 *  |~~~|~|~~~|~~~|~~~|~~~|~|~~~|~|~~~|~~~|~~~|~|~~~|~|~~~|/_/  \            *
 *  | G |C| P | = | L | P |=| = |C| = | = | = |=| = |=| C |\  \ /\           *
 *  | R |l| o | = | e | l |=| = |a| = | = | = |=| = |=| L | \# \ /\          *
 *  | A |a| l | = | t | u |=| = |n| = | = | = |=| = |=| o | |\# \  \         *
 *  | P |n| l | = | s | t |=| = |d| = | = | = | |   |=| o | | \# \  \        *
 *  | H | | y |   | e | o | | = |l|   |   | = | |   | | G | |  \  \  \       *
 *  | I | |   |   | e |   | |   | |   |   |   | |   | |   | |   \  \  \      *
 *  | T | |   |   |   |   | |   | |   |   |   | |   | |   | |    \  \  \     *
 *  | E | |   |   |   |   | |   | |   |   |   | |   | |   | |     \  \  \    *
 *  | * |*| * | * | * | * |*| * |*| * | * | * |*| * |*| * | /      \* \  \   *
 *  | O |p| e | n | S | c |o| p |-| L | i | b |r| a |r| y |/        \  \ /   *
 *  '---'-'---'---'---'---'-'---'-'---'---'---'-'---'-'---'          '--'    *
 *                                                                           *
 * Copyright (C) 2008 University Paris-Sud 11 and INRIA                      *
 *                                                                           *
 * (3-clause BSD license)                                                    *
 * Redistribution and use in source  and binary forms, with or without       *
 * modification, are permitted provided that the following conditions        *
 * are met:                                                                  *
 *                                                                           *
 * 1. Redistributions of source code must retain the above copyright notice, *
 *    this list of conditions and the following disclaimer.                  *
 * 2. Redistributions in binary form must reproduce the above copyright      *
 *    notice, this list of conditions and the following disclaimer in the    *
 *    documentation and/or other materials provided with the distribution.   *
 * 3. The name of the author may not be used to endorse or promote products  *
 *    derived from this software without specific prior written permission.  *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR      *
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES *
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.   *
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,          *
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT  *
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY     *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  *
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.         *
 *                                                                           *
 * OpenScop Library, a library to manipulate OpenScop formats and data       *
 * structures. Written by:                                                   *
 * Cedric Bastoul     <Cedric.Bastoul@u-psud.fr> and                         *
 * Louis-Noel Pouchet <Louis-Noel.pouchet@inria.fr>                          *
 *                                                                           *
 *****************************************************************************/

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <openscop/names.h>


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * openscop_names_idump function:
 * this function displays an openscop_names_t structure (*names) into a
 * file (file, possibly stdout) in a way that trends to be understandable. It
 * includes an indentation level (level) in order to work with others
 * print_structure functions.
 * \param file  The file where the information has to be printed.
 * \param names The names structure whose information has to be printed.
 * \param level Number of spaces before printing, for each line.
 */
void openscop_names_idump(FILE * file, openscop_names_p names, int level) {
  int j;
  char * parm_msg = "Parameter strings";
  char * iter_msg = "Iterator strings";
  char * scat_msg = "Scattering dimension strings";
  char * loca_msg = "Local dimension strings";
  char * arra_msg = "Array strings";

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (names != NULL) {
    if (names->textual == 1)
      fprintf(file, "+-- openscop_names_t\n");
    else
      fprintf(file, "+-- openscop_names_t (non textual)\n");
  }
  else {
    fprintf(file, "+-- NULL names\n");
  }

  if ((names != NULL) && (names->textual == 1)) {
    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");
    
    // Print the various names.
    openscop_strings_idump(file, names->parameters, level, parm_msg);
    openscop_strings_idump(file, names->iterators,  level, iter_msg);
    openscop_strings_idump(file, names->scattdims,  level, scat_msg);
    openscop_strings_idump(file, names->localdims,  level, loca_msg);
    openscop_strings_idump(file, names->arrays,     level, arra_msg);
  }

  // The last line.
  for (j = 0; j <= level; j++)
    fprintf(file, "|\t");
  fprintf(file, "\n");
}


/**
 * openscop_names_dump function:
 * this function prints the content of an openscop_names_t structure
 * (*names) into a file (file, possibly stdout).
 * \param file  The file where the information has to be printed.
 * \param names The names structure whose information has to be printed.
 */
void openscop_names_dump(FILE * file, openscop_names_p names) {
  openscop_names_idump(file, names, 0);
}


/**
 * openscop_names_print function:
 * this function prints the content of an openscop_names_t structure (*names)
 * into a file (file, possibly stdout) in the OpenScop textual format.
 * \param file The file where the information has to be printed.
 * \param names The names structure whose information has to be printed.
 */
void openscop_names_print(FILE * file, openscop_names_p names) {
  int print;
  char * parm_msg = "Parameter names";
  char * iter_msg = "Iterator names";
  char * scat_msg = "Scattering dimension names";
  
  if (names != NULL) {
    print = (names->textual == 1);
    openscop_strings_print(file, names->parameters, 1, print, parm_msg);
    openscop_strings_print(file, names->iterators,  1, print, iter_msg);
    openscop_strings_print(file, names->scattdims,  1, print, scat_msg);
  }
  else {
    openscop_strings_print(file, NULL, 1, 0, parm_msg);
    openscop_strings_print(file, NULL, 1, 0, iter_msg);
    openscop_strings_print(file, NULL, 1, 0, scat_msg);
  }
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/**
 * openscop_names_read function:
 * this function reads a names structure from a file (possibly stdin)
 * complying to the OpenScop textual format and returns a pointer to this
 * names structure.
 * \param file The file where the names has to be read.
 * \return A pointer to the names structure that has been read.
 */
openscop_names_p openscop_names_read(FILE * file) {
  openscop_names_p names = openscop_names_malloc();

  if (openscop_util_read_int(file, NULL) > 0) {
    names->parameters = openscop_strings_read(file);
    names->nb_parameters = openscop_strings_size(names->parameters);
  }
  else {
    names->parameters = NULL;
    names->nb_parameters = 0;
  }

  if (openscop_util_read_int(file, NULL) > 0) {
    names->iterators = openscop_strings_read(file);
    names->nb_iterators = openscop_strings_size(names->iterators);
  }
  else {
    names->iterators = NULL;
    names->nb_iterators = 0;
  }

  if (openscop_util_read_int(file, NULL) > 0) {
    names->scattdims = openscop_strings_read(file);
    names->nb_scattdims = openscop_strings_size(names->scattdims);
  }
  else {
    names->scattdims = NULL;
    names->nb_scattdims = 0;
  }

  return names;
}


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/


/**
 * openscop_names_malloc function:
 * this function allocates the memory space for an openscop_names_t
 * structure and sets its fields with default values. Then it returns a
 * pointer to the allocated space.
 * \return A pointer to an empty names structure with fields set to
 *         default values.
 */
openscop_names_p openscop_names_malloc() {
  openscop_names_p names;

  OPENSCOP_malloc(names, openscop_names_p, sizeof(openscop_names_t));
  names->textual       = 1;
  names->nb_parameters = 0;
  names->nb_iterators  = 0;
  names->nb_scattdims  = 0;
  names->parameters    = NULL;
  names->iterators     = NULL;
  names->scattdims     = NULL;
  names->nb_localdims  = 0;
  names->nb_arrays     = 0;
  names->localdims     = NULL;
  names->arrays        = NULL;

  return names;
}


/**
 * openscop_names_free function:
 * This function frees the allocated memory for an openscop_names_t
 * structure. If the names are not character strings, it is the
 * responsibility of the user to free each array of elements (including
 * the array itself), this function will only free the openscop_names_t shell.
 * \param names The pointer to the names structure we want to free.
 */
void openscop_names_free(openscop_names_p names) {
  if (names != NULL) {
    if (names->textual == 1) {
      openscop_strings_free(names->parameters);
      openscop_strings_free(names->iterators);
      openscop_strings_free(names->scattdims);
      openscop_strings_free(names->localdims);
      openscop_strings_free(names->arrays);
    }

    free(names);
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_names_clone function:
 * this function builds and returns a "hard copy" (not a pointer copy) of an
 * openscop_names_t data structure provided as parameter.
 * \param names The pointer to the names structure we want to clone.
 * \return A pointer to the clone of the names structure provided as parameter.
 */
openscop_names_p openscop_names_clone(openscop_names_p names) {
  openscop_names_p clone = NULL;
  
  if (names != NULL) {
    clone = openscop_names_malloc();
    clone->textual       = names->textual;
    clone->nb_parameters = names->nb_parameters;
    clone->nb_iterators  = names->nb_iterators;
    clone->nb_scattdims  = names->nb_scattdims;
    clone->parameters    = openscop_strings_clone(names->parameters);
    clone->iterators     = openscop_strings_clone(names->iterators);
    clone->scattdims     = openscop_strings_clone(names->scattdims);
    clone->nb_localdims  = names->nb_localdims;
    clone->nb_arrays     = names->nb_arrays;
    clone->localdims     = openscop_strings_clone(names->localdims);
    clone->arrays        = openscop_strings_clone(names->arrays);
  }
  return clone;
}


/**
 * openscop_names_equal function:
 * this function returns true if the two names structures are the same
 * (content-wise), false otherwise.
 * \param n1  The first names structure.
 * \param n2  The second names structure.
 * \return 1 if n1 and n2 are the same (content-wise), 0 otherwise.
 */
int openscop_names_equal(openscop_names_p n1, openscop_names_p n2) {
  if (n1 == n2)
    return 1;

  if (((n1 == NULL) && (n2 != NULL)) || ((n1 != NULL) && (n2 == NULL)))
    return 0;

  if (!openscop_strings_equal(n1->parameters, n2->parameters)) {
    OPENSCOP_info("parameters are not the same"); 
    return 0;
  }
  
  if (!openscop_strings_equal(n1->iterators, n2->iterators)) {
    OPENSCOP_info("iterators are not the same"); 
    return 0;
  }
  
  if (!openscop_strings_equal(n1->scattdims, n2->scattdims)) {
    OPENSCOP_info("scattdims are not the same");
    return 0;
  }
  
  if (!openscop_strings_equal(n1->localdims, n2->localdims)) {
    OPENSCOP_info("localdims are not the same");
    return 0;
  }

  if (!openscop_strings_equal(n1->arrays, n2->arrays)) {
    OPENSCOP_info("arrays are not the same");
    return 0;
  }

  return 1;
}


/**
 * openscop_names_integrity_check function:
 * This function checks that an openscop_names_t structure is "well formed".
 * It returns 0 if the check failed or 1 if no problem has been detected.
 * \param names The names structure we want to check.
 * \param min_nb_parameters The minimum acceptable number of parameters.
 * \param min_nb_iterators  The minimum acceptable number of iterators.
 * \param min_nb_scattdims  The minimum acceptable number of scattdims.
 * \return 0 if the integrity check fails, 1 otherwise.
 */
int openscop_names_integrity_check(openscop_names_p names,
                                   int min_nb_parameters,
                                   int min_nb_iterators,
                                   int min_nb_scattdims) {
  if ((names->nb_parameters > 0) &&
      (names->nb_parameters < min_nb_parameters)) {
    OPENSCOP_warning("not enough parameter names");
    return 0;
  }

  if ((names->nb_iterators > 0) &&
      (names->nb_iterators < min_nb_iterators)) {
    OPENSCOP_warning("not enough iterator names");
    return 0;
  }
  
  if ((names->nb_scattdims > 0) &&
      (names->nb_scattdims < min_nb_scattdims)) {
    OPENSCOP_warning("not enough scattering dimension names");
    return 0;
  }

  return 1;
}

