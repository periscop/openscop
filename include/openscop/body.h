
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                            body.h                               **
     **-----------------------------------------------------------------**
     **                   First version: 25/06/2011                     **
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


#ifndef OPENSCOP_BODY_H
# define OPENSCOP_BODY_H

# include <stdio.h>
# include <openscop/macros.h>
# include <openscop/util.h>

# if defined(__cplusplus)
extern "C"
  {
# endif


/**
 * The openscop_body_t structure stores a statement body. Statement body
 * information may be strings of characters (char *) or a generic pointer
 * to anything else (void *). The OpenScop library does not touch AT ALL
 * generic information: printing, copy etc. must be done externally.
 */
struct openscop_body {
  int type;          /**< OPENSCOP_TYPE_GENERIC if iterators and expression
                          are generic (void *), OPENSCOP_TYPE_STRING if they
                          are strings (they can be casted to char *) */
  int nb_iterators;  /**< Number of elements in the 'iterators' array */
  void ** iterator;  /**< Array of original iterators */
  void * expression; /**< Original statement expression */
};
typedef struct openscop_body   openscop_body_t;
typedef struct openscop_body * openscop_body_p;


/*---------------------------------------------------------------------------+
 |                          Structure display function                       |
 +---------------------------------------------------------------------------*/
void openscop_body_idump(FILE *, openscop_body_p, int);
void openscop_body_dump(FILE *, openscop_body_p);
void openscop_body_print(FILE *, openscop_body_p);


/*****************************************************************************
 *                              Reading function                             *
 *****************************************************************************/
openscop_body_p openscop_body_read(FILE *, int);


/*+***************************************************************************
 *                   Memory allocation/deallocation function                 *
 *****************************************************************************/
openscop_body_p openscop_body_malloc();
void            openscop_body_free(openscop_body_p);


/*+***************************************************************************
 *                           Processing functions                            *
 *****************************************************************************/
openscop_body_p openscop_body_clone(openscop_body_p);
int             openscop_body_equal(openscop_body_p, openscop_body_p);
int             openscop_body_integrity_check(openscop_body_p, int);

# if defined(__cplusplus)
  }
# endif
#endif /* define OPENSCOP_BODY_H */
