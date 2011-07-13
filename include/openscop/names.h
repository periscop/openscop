
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                      extensions/names.h                         **
     **-----------------------------------------------------------------**
     **                   First version: 18/05/2011                     **
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


#ifndef OPENSCOP_NAMES_H
# define OPENSCOP_NAMES_H

# include <openscop/macros.h>
# include <openscop/util.h>
# include <openscop/strings.h>

# if defined(__cplusplus)
extern "C"
  {
# endif


/**
 * The openscop_names_t structure stores the various names (names of iterators,
 * parameters...) necessary to generate a code from the OpenScop data
 * structure. The term "name" is generic and corresponds to a pointer to the
 * information necessary to generate the code. A name may be a string of
 * characters (char *) or a pointer to anything else. For textual tools
 * convenience, the default type is (char *), but it may be casted to your
 * preferred type iff the "textual" field is 0.
 */
struct openscop_names {
  int textual;        /**< 1 if names are character strings, 0 otherwise. */
  int nb_parameters;  /**< Number of parameters names. */
  int nb_iterators;   /**< Number of iterators names. */
  int nb_scattdims;   /**< Number of scattering dimensions names. */
  char ** parameters; /**< Array of nb_parameters parameter names. */
  char ** iterators;  /**< Array of nb_iterators iterator names. */
  char ** scattdims;  /**< Array of nb_scattdims scattering dimension names. */

  // The following is not part of the OpenScop specification (internal use).
  int nb_localdims;   //   Number of local dimension names.
  int nb_arrays;      //   Number of array names.
  char ** localdims;  //   Array of nb_locals local dimension names.
  char ** arrays;     //   Array of nb_arrays array dimension names.
};
typedef struct openscop_names   openscop_names_t;
typedef struct openscop_names * openscop_names_p;


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/
void             openscop_names_idump(FILE *, openscop_names_p, int);
void             openscop_names_dump(FILE *, openscop_names_p);
void             openscop_names_print(FILE *, openscop_names_p);


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/
openscop_names_p openscop_names_read(FILE *);


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/
openscop_names_p openscop_names_malloc();
void             openscop_names_free(openscop_names_p);


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/
openscop_names_p openscop_names_clone(openscop_names_p);
int              openscop_names_equal(openscop_names_p, openscop_names_p);
int              openscop_names_integrity_check(openscop_names_p,int,int,int);


# if defined(__cplusplus)
  }
# endif

#endif /* define OPENSCOP_NAMES_H */
