
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                     extensions/irregular.h                        **
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


#ifndef OPENSCOP_IRREGULAR_H
# define OPENSCOP_IRREGULAR_H

# include <openscop/macros.h>
# include <openscop/util.h>

# if defined(__cplusplus)
extern "C"
  {
# endif


# define OPENSCOP_TAG_IRREGULAR_START  "<irregular>"
# define OPENSCOP_TAG_IRREGULAR_STOP   "</irregular>"


/**
 * The openscop_irregular_t structure stores an irregular extension to the core
 * OpenScop representation. It contains a list of predicates (in their textual
 * representation), and for each statement, its list of associated predicates.
 * The list of predicates contains both control and exit predicates (see
 * Benabderrhamane et al.'s paper at CC'2010), control predicates are listed
 * first, then come exit predicates.
 */
struct openscop_irregular {
  // List of predicates (textual representation).
  int nb_control;      /**< Number of control predicates in the SCoP. */
  int nb_exit;         /**< Number of exit predicates in the SCoP. */
  int * nb_iterators;  /**< nb_iterators[i]: #iterators for ith predicate. */
  char *** iterators;  /**< iterators[i]: array of (nb_control + nb_exit)
                            arrays of nb_iterators[i] strings. Each element
                            corresponds to the list of original iterators
                            for the ith predicate. */
  char ** body;        /**< body[i]: original source code of ith predicate. */
  
  // List of associated predicates for each statement.
  int nb_statements;   /**< Number of statements in the SCoP. */
  int * nb_predicates; /**< nb_predicates[i]: #predicates for ith statement. */
  int ** predicates;   /**< predicates[i]: array of nb_predicates[i] predicates
                            corresponding to the list of predicates associated
                            to the ith statement. */
};
typedef struct openscop_irregular   openscop_irregular_t;
typedef struct openscop_irregular * openscop_irregular_p;


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/
void   openscop_irregular_idump(FILE *, openscop_irregular_p, int);
void   openscop_irregular_dump(FILE *, openscop_irregular_p);
char * openscop_irregular_sprint(openscop_irregular_p);


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/
openscop_irregular_p openscop_irregular_sread(char *);


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/
openscop_irregular_p openscop_irregular_malloc();
void                 openscop_irregular_free(openscop_irregular_p);


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/
openscop_irregular_p openscop_irregular_copy(openscop_irregular_p);
int                  openscop_irregular_equal(openscop_irregular_p,
                                  openscop_irregular_p);
openscop_irregular_p openscop_irregular_add_control(openscop_irregular_p,
                                  char**, int, char*);
openscop_irregular_p openscop_irregular_add_predicates(openscop_irregular_p,
                                  int*, int);


# if defined(__cplusplus)
  }
# endif

#endif /* define OPENSCOP_IRREGULAR_H */
