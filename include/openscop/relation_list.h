
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                        relation_list.h                          **
     **-----------------------------------------------------------------**
     **                   First version: 08/10/2010                     **
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


#ifndef OPENSCOP_RELATION_LIST_H
# define OPENSCOP_RELATION_LIST_H

# include <stdio.h>
# include <openscop/macros.h>
# include <openscop/names.h>
# include <openscop/vector.h>
# include <openscop/relation.h>


# if defined(__cplusplus)
extern "C"
  {
# endif


/**
 * The openscop_relation_list_t structure describes a (NULL-terminated
 * linked) list of relations.
 */
struct openscop_relation_list {
  openscop_relation_p elt;              /**< An element of the list. */
  struct openscop_relation_list * next; /**< Pointer to the next element
				             of the list.*/
};
typedef struct openscop_relation_list   openscop_relation_list_t;
typedef struct openscop_relation_list * openscop_relation_list_p;


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/
void openscop_relation_list_print_structure(FILE *,
                                     openscop_relation_list_p, int);
void openscop_relation_list_print(FILE *, openscop_relation_list_p);
void openscop_relation_list_print_openscop(FILE *,
                                     openscop_relation_list_p, int,
                                     openscop_names_p);


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/
openscop_relation_list_p openscop_relation_list_read(FILE *);


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/
openscop_relation_list_p openscop_relation_list_malloc();
void                     openscop_relation_list_free(openscop_relation_list_p);


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/
openscop_relation_list_p openscop_relation_list_node(openscop_relation_p);
openscop_relation_list_p openscop_relation_list_copy(openscop_relation_list_p);
openscop_relation_list_p openscop_relation_list_concat(
                                             openscop_relation_list_p,
                                             openscop_relation_list_p);
int                      openscop_relation_list_equal(openscop_relation_list_p,
                                             openscop_relation_list_p);
int                      openscop_relation_list_integrity_check(
                                             openscop_relation_list_p,
                                             int, int, int, int);

# if defined(__cplusplus)
  }
# endif
#endif /* define OPENSCOP_RELATION_LIST_H */
