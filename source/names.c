
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
 * openscop_names_print_structure function:
 * this function displays an openscop_names_t structure (*names) into a
 * file (file, possibly stdout) in a way that trends to be understandable. It
 * includes an indentation level (level) in order to work with others
 * print_structure functions.
 * \param file  The file where the information has to be printed.
 * \param names The names structure whose information has to be printed.
 * \param level Number of spaces before printing, for each line.
 */
void openscop_names_print_structure(FILE * file, openscop_names_p names,
                                    int level) {
  int j;

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
    
    // Print the original parameter names.
    openscop_util_strings_print_structure(file, names->parameters,
					  names->nb_parameters, level,
					  "Parameter strings");

    // Print the iterator names.
    openscop_util_strings_print_structure(file, names->iterators,
					  names->nb_iterators, level,
					  "Iterator strings");
    
    // Print the scattering dimension names.
    openscop_util_strings_print_structure(file, names->scattdims,
					  names->nb_scattdims, level,
					  "Scattering dimension strings");
    
    // Print the local dimension names.
    openscop_util_strings_print_structure(file, names->localdims,
					  names->nb_localdims, level,
					  "Local dimension strings");

    // Print the array names.
    openscop_util_strings_print_structure(file, names->arrays,
					  names->nb_arrays, level,
					  "Array strings");
  }

  // The last line.
  for (j = 0; j <= level; j++)
    fprintf(file, "|\t");
  fprintf(file, "\n");
}


/**
 * openscop_names_print function:
 * this function prints the content of an openscop_names_t structure
 * (*names) into a file (file, possibly stdout).
 * \param file  The file where the information has to be printed.
 * \param names The names structure whose information has to be printed.
 */
void openscop_names_print(FILE * file, openscop_names_p names) {
  openscop_names_print_structure(file, names, 0);
}


/**
 * openscop_names_print_openscop function:
 * this function prints the content of an openscop_names_t structure (*names)
 * into a file (file, possibly stdout) in the OpenScop textual format.
 * \param file The file where the information has to be printed.
 * \param names The names structure whose information has to be printed.
 */
void openscop_names_print_openscop(FILE * file, openscop_names_p names) {
  int print = ((names != NULL) && (names->textual == 1));
  
  openscop_util_strings_print_openscop(file,
                                       names->parameters, names->nb_parameters,
                                       print, "Parameter names");
  
  openscop_util_strings_print_openscop(file,
                                       names->iterators, names->nb_iterators,
                                       print, "Iterator names");
  
  openscop_util_strings_print_openscop(file,
                                       names->scattdims, names->nb_scattdims,
                                       print, "Scattering dimension names");
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
    names->parameters = openscop_util_strings_read(file,
                                                   &(names->nb_parameters));
  }
  else {
    names->nb_parameters = 0;
    names->parameters = NULL;
  }

  if (openscop_util_read_int(file, NULL) > 0) {
    names->iterators  = openscop_util_strings_read(file,
                                                   &(names->nb_iterators));
  }
  else {
    names->nb_iterators = 0;
    names->iterators = NULL;
  }

  if (openscop_util_read_int(file, NULL) > 0) {
      names->scattdims  = openscop_util_strings_read(file,
                                                     &(names->nb_scattdims));
  }
  else {
    names->nb_scattdims = 0;
    names->scattdims = NULL;
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
  openscop_names_p names = (openscop_names_p)malloc(sizeof(openscop_names_t));

  if (names == NULL) {
    fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
    exit(1);
  }
  
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
      openscop_util_strings_free(names->parameters, names->nb_parameters);
      openscop_util_strings_free(names->iterators,  names->nb_iterators);
      openscop_util_strings_free(names->scattdims,  names->nb_scattdims);
      
      openscop_util_strings_free(names->localdims,  names->nb_localdims);
      openscop_util_strings_free(names->arrays,     names->nb_arrays);
    }

    free(names);
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_names_copy function:
 * this function builds and returns a "hard copy" (not a pointer copy) of an
 * openscop_names_t data structure provided as parameter.
 * \param names The pointer to the names structure we want to copy.
 * \return A pointer to the copy of the names structure provided as parameter.
 */
openscop_names_p openscop_names_copy(openscop_names_p names) {
  openscop_names_p copy = openscop_names_malloc();

  copy->textual       = names->textual;
  copy->nb_parameters = names->nb_parameters;
  copy->nb_iterators  = names->nb_iterators;
  copy->nb_scattdims  = names->nb_scattdims;
  copy->parameters    = openscop_util_strings_copy(names->parameters,
                                                   names->nb_parameters);
  copy->iterators     = openscop_util_strings_copy(names->iterators,
                                                   names->nb_iterators);
  copy->scattdims     = openscop_util_strings_copy(names->scattdims,
                                                   names->nb_scattdims);

  copy->nb_localdims  = names->nb_localdims;
  copy->nb_arrays     = names->nb_arrays;
  copy->localdims     = openscop_util_strings_copy(names->localdims,
                                                   names->nb_localdims);
  copy->arrays        = openscop_util_strings_copy(names->arrays,
                                                   names->nb_arrays);

  return copy;
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

  if (!openscop_util_strings_equal(n1->parameters, n1->nb_parameters,
	                           n2->parameters, n1->nb_parameters)) {
    fprintf(stderr, "[OpenScop] info: parameters are not the same.\n"); 
    return 0;
  }
  
  if (!openscop_util_strings_equal(n1->iterators, n1->nb_iterators,
	                           n2->iterators, n1->nb_iterators)) {
    fprintf(stderr, "[OpenScop] info: iterators are not the same.\n"); 
    return 0;
  }
  
  if (!openscop_util_strings_equal(n1->scattdims, n1->nb_scattdims,
	                           n2->scattdims, n1->nb_scattdims)) {
    fprintf(stderr, "[OpenScop] info: scattdims are not the same.\n");
    return 0;
  }
  
  if (!openscop_util_strings_equal(n1->localdims, n1->nb_localdims,
	                           n2->localdims, n1->nb_localdims)) {
    fprintf(stderr, "[OpenScop] info: localdims are not the same.\n");
    return 0;
  }

  if (!openscop_util_strings_equal(n1->arrays, n1->nb_arrays,
	                           n2->arrays, n1->nb_arrays)) {
    fprintf(stderr, "[OpenScop] info: arrays are not the same.\n");
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
    fprintf(stderr, "[OpenScop] Warning: not enough parameter names.\n");
    return 0;
  }

  if ((names->nb_iterators > 0) &&
      (names->nb_iterators < min_nb_iterators)) {
    fprintf(stderr, "[OpenScop] Warning: not enough iterator names.\n");
    return 0;
  }
  
  if ((names->nb_scattdims > 0) &&
      (names->nb_scattdims < min_nb_scattdims)) {
    fprintf(stderr, "[OpenScop] Warning: not enough scattering "
                    "dimension names.\n");
    return 0;
  }

  return 1;
}

