
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                          extension.h                            **
     **-----------------------------------------------------------------**
     **                   First version: 26/11/2010                     **
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


#ifndef OPENSCOP_EXTENSION_H
# define OPENSCOP_EXTENSION_H

# include <openscop/macros.h>
# include <openscop/util.h>
# include <openscop/comment.h>
# include <openscop/arrays.h>

# if defined(__cplusplus)
extern "C"
  {
# endif

#define OPENSCOP_EXTENSION_UNDEFINED   0
#define OPENSCOP_EXTENSION_STRING      1
#define OPENSCOP_EXTENSION_COMMENT     2
#define OPENSCOP_EXTENSION_ARRAYS      3

/**
 * The openscop_extension_t structure stores an extension to the core
 * OpenScop representation. It is a node of a NULL-terminated linked list of
 * extensions.
 */
struct openscop_extension {
  int type;                         /**< This extension's type. */
  void * extension;                 /**< Pointer to the extension itself. */
  struct openscop_extension * next; /**< Pointer to the next extension. */
};
typedef struct openscop_extension   openscop_extension_t;
typedef struct openscop_extension * openscop_extension_p;


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/
void openscop_extension_print_structure(FILE *, openscop_extension_p, int);
void openscop_extension_print(FILE *, openscop_extension_p);
void openscop_extension_print_openscop(FILE *, openscop_extension_p);


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/
char *               openscop_extension_read_string(FILE *);
openscop_extension_p openscop_extension_read(FILE *);


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/
void                 openscop_extension_add(openscop_extension_p*, int, void*);
openscop_extension_p openscop_extension_malloc();
void                 openscop_extension_free(openscop_extension_p);


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/
openscop_extension_p openscop_extension_copy(openscop_extension_p);
int openscop_extension_equal(openscop_extension_p, openscop_extension_p);
void * openscop_extension_lookup(openscop_extension_p, int);


# if defined(__cplusplus)
  }
# endif

#endif /* define OPENSCOP_EXTENSION_H */
