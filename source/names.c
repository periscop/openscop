
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
 * \param[in] file  The file where the information has to be printed.
 * \param[in] names The names structure whose information has to be printed.
 * \param[in] level Number of spaces before printing, for each line.
 */
void openscop_names_idump(FILE * file, openscop_names_p names, int level) {
  int j;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (names != NULL)
    fprintf(file, "+-- openscop_names_t\n");
  else
    fprintf(file, "+-- NULL names\n");

  if (names != NULL) {
    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");
    
    // Print the various names.
    openscop_strings_idump(file, names->parameters, level + 1);
    openscop_strings_idump(file, names->iterators,  level + 1);
    openscop_strings_idump(file, names->scatt_dims, level + 1);
    openscop_strings_idump(file, names->local_dims, level + 1);
    openscop_strings_idump(file, names->arrays,     level + 1);
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
 * \param[in] file  The file where the information has to be printed.
 * \param[in] names The names structure whose information has to be printed.
 */
void openscop_names_dump(FILE * file, openscop_names_p names) {
  openscop_names_idump(file, names, 0);
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


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
  names->parameters = NULL;
  names->iterators  = NULL;
  names->scatt_dims = NULL;
  names->local_dims = NULL;
  names->arrays     = NULL;

  return names;
}


/**
 * openscop_names_free function:
 * This function frees the allocated memory for an openscop_names_t
 * structure. If the names are not character strings, it is the
 * responsibility of the user to free each array of elements (including
 * the array itself), this function will only free the openscop_names_t shell.
 * \param[in,out] names The pointer to the names structure we want to free.
 */
void openscop_names_free(openscop_names_p names) {
  if (names != NULL) {
    openscop_strings_free(names->parameters);
    openscop_strings_free(names->iterators);
    openscop_strings_free(names->scatt_dims);
    openscop_strings_free(names->local_dims);
    openscop_strings_free(names->arrays);

    free(names);
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_names_generate function:
 * this function generates some names. For each kind of name it will generate
 * a given number of names with a given prefix followed by a number.
 * \param[in] parameter_prefix Prefix for parameter names.
 * \param[in] nb_parameters    Number of parameters names to generate.
 * \param[in] iterator_prefix  Prefix for iterator names.
 * \param[in] nb_iteratorrs    Number of iterators names to generate.
 * \param[in] scatt_dim_prefix Prefix for scattering dimension names.
 * \param[in] nb_scatt_dims    Number of scattering dim names to generate.
 * \param[in] local_dim_prefix Prefix for local dimension names.
 * \param[in] nb_local_dims    Number of local dimension names to generate.
 * \param[in] array_prefix     Prefix for array names.
 * \param[in] nb_arrays        Number of array names to generate.
 * \return A new names structure containing generated names.
 */
openscop_names_p openscop_names_generate(
    char * parameter_prefix, int nb_parameters,
    char * iterator_prefix,  int nb_iterators,
    char * scatt_dim_prefix, int nb_scatt_dims,
    char * local_dim_prefix, int nb_local_dims,
    char * array_prefix,     int nb_arrays) {
  openscop_names_p names = openscop_names_malloc();

  names->parameters= openscop_strings_generate(parameter_prefix,nb_parameters);
  names->iterators = openscop_strings_generate(iterator_prefix, nb_iterators);
  names->scatt_dims= openscop_strings_generate(scatt_dim_prefix,nb_scatt_dims);
  names->local_dims= openscop_strings_generate(local_dim_prefix,nb_local_dims);
  names->arrays    = openscop_strings_generate(array_prefix,    nb_arrays);
  
  return names;
}

/**
 * openscop_names_clone function:
 * this function builds and returns a "hard copy" (not a pointer copy) of an
 * openscop_names_t data structure provided as parameter.
 * \param[in] names The pointer to the names structure we want to clone.
 * \return A pointer to the clone of the names structure provided as parameter.
 */
openscop_names_p openscop_names_clone(openscop_names_p names) {
  openscop_names_p clone = NULL;
  
  if (names != NULL) {
    clone = openscop_names_malloc();
    clone->parameters = openscop_strings_clone(names->parameters);
    clone->iterators  = openscop_strings_clone(names->iterators);
    clone->scatt_dims = openscop_strings_clone(names->scatt_dims);
    clone->local_dims = openscop_strings_clone(names->local_dims);
    clone->arrays     = openscop_strings_clone(names->arrays);
  }
  return clone;
}
