
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
 * structure.
 */
struct openscop_names {
  openscop_strings_p parameters; /**< Parameter names */
  openscop_strings_p iterators;  /**< Iterator names */
  openscop_strings_p scatt_dims; /**< Scattering dimension names */
  openscop_strings_p local_dims; /**< Local dimension names */
  openscop_strings_p arrays;     /**< Array names */
};
typedef struct openscop_names   openscop_names_t;
typedef struct openscop_names * openscop_names_p;


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/
void             openscop_names_idump(FILE *, openscop_names_p, int);
void             openscop_names_dump(FILE *, openscop_names_p);


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/
openscop_names_p openscop_names_malloc();
void             openscop_names_free(openscop_names_p);


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/
openscop_names_p openscop_names_clone(openscop_names_p);
openscop_names_p openscop_names_generate(char *, int, char *, int,
                                         char *, int, char *, int,
                                         char *, int);


# if defined(__cplusplus)
  }
# endif

#endif /* define OPENSCOP_NAMES_H */
