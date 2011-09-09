
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                      extensions/arrays.h                        **
     **-----------------------------------------------------------------**
     **                   First version: 07/12/2010                     **
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


#ifndef OPENSCOP_ARRAYS_H
# define OPENSCOP_ARRAYS_H

# include <openscop/macros.h>
# include <openscop/strings.h>
# include <openscop/interface.h>

# if defined(__cplusplus)
extern "C"
  {
# endif


# define OPENSCOP_URI_ARRAYS        "arrays"
# define OPENSCOP_TAG_ARRAYS_START  "<"OPENSCOP_URI_ARRAYS">"
# define OPENSCOP_TAG_ARRAYS_STOP   "</"OPENSCOP_URI_ARRAYS">"


/**
 * The openscop_arrays_t structure stores a set of array names in
 * the extension part of the OpenScop representation. Each name
 * has a name string and an identifier: the ith name as name
 * string names[i] and identifier id[i].
 */
struct openscop_arrays {
  int nb_names;      /**< Number of names. */
  int  *  id;        /**< Array of nb_names identifiers. */
  char ** names;     /**< Array of nb_names names. */
};
typedef struct openscop_arrays   openscop_arrays_t;
typedef struct openscop_arrays * openscop_arrays_p;


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/
void   openscop_arrays_idump(FILE *, openscop_arrays_p, int);
void   openscop_arrays_dump(FILE *, openscop_arrays_p);
char * openscop_arrays_sprint(openscop_arrays_p);


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/
openscop_arrays_p openscop_arrays_sread(char *);


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/
openscop_arrays_p openscop_arrays_malloc();
void              openscop_arrays_free(openscop_arrays_p);


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/
openscop_arrays_p openscop_arrays_clone(openscop_arrays_p);
int               openscop_arrays_equal(openscop_arrays_p, openscop_arrays_p);
char **           openscop_arrays_generate_names(openscop_arrays_p, int *);
openscop_interface_p openscop_arrays_interface();

# if defined(__cplusplus)
  }
# endif

#endif /* define OPENSCOP_ARRAYS_H */
