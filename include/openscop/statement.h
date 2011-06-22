
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                         statement.h                             **
     **-----------------------------------------------------------------**
     **                   First version: 30/04/2008                     **
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


#ifndef OPENSCOP_STATEMENT_H
# define OPENSCOP_STATEMENT_H

# include <stdio.h>
# include <openscop/macros.h>
# include <openscop/util.h>
# include <openscop/names.h>
# include <openscop/relation.h>
# include <openscop/relation_list.h>

# if defined(__cplusplus)
extern "C"
  {
# endif


/**
 * The openscop_statement_t structure stores a list of statement. Each node
 * contains the useful informations for a given statement to process it
 * within a polyhedral framework. The order in the list may matter for naming
 * conventions (e.g. "S1" for the first statement in the list).
 */
struct openscop_statement {
  openscop_relation_p domain;     /**< Iteration domain of the statement */
  openscop_relation_p scattering; /**< Scattering function for the statement */
  openscop_relation_list_p read;  /**< Array read access informations */
  openscop_relation_list_p write; /**< Array write access informations */
  int nb_iterators;               /**< Number of names in 'iterators' */
  char ** iterators;              /**< Array of iterator names */
  char * body;                    /**< Original statement body */
  void * usr;                     /**< A user-defined field, not touched
				       AT ALL by the OpenScop Library. */
  struct openscop_statement * next; /**< Next statement in the linked list */
};
typedef struct openscop_statement   openscop_statement_t;
typedef struct openscop_statement * openscop_statement_p;


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/
void openscop_statement_idump(FILE *, openscop_statement_p, int);
void openscop_statement_dump(FILE *, openscop_statement_p);
void openscop_statement_print(FILE *, openscop_statement_p,
                                       openscop_names_p);


/*****************************************************************************
 *                              Reading function                             *
 *****************************************************************************/
openscop_statement_p openscop_statement_read(FILE*, int);


/*+***************************************************************************
 *                   Memory allocation/deallocation function                 *
 *****************************************************************************/
openscop_statement_p openscop_statement_malloc();
void                 openscop_statement_free(openscop_statement_p);


/*+***************************************************************************
 *                           Processing functions                            *
 *****************************************************************************/
void openscop_statement_add(openscop_statement_p *, openscop_statement_p);
void openscop_statement_compact(openscop_statement_p, int);
int  openscop_statement_number(openscop_statement_p);
openscop_statement_p openscop_statement_copy(openscop_statement_p);
int  openscop_statement_equal(openscop_statement_p, openscop_statement_p);
int  openscop_statement_integrity_check(openscop_statement_p, int);

# if defined(__cplusplus)
  }
# endif
#endif /* define OPENSCOP_STATEMENT_H */
