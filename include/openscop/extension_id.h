
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                        extension_id.h                           **
     **-----------------------------------------------------------------**
     **                   First version: 15/07/2011                     **
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


#ifndef OPENSCOP_EXTENSION_ID_H
# define OPENSCOP_EXTENSION_ID_H

# include <openscop/macros.h>

# if defined(__cplusplus)
extern "C"
  {
# endif


typedef void   (*openscop_idump_f) (FILE *, void *, int);
typedef void   (*openscop_dump_f)  (FILE *, void *);
typedef char * (*openscop_sprint_f)(void *);
typedef void * (*openscop_sread_f) (char *);
typedef void * (*openscop_malloc_f)();
typedef void   (*openscop_free_f)  (void *);
typedef void * (*openscop_clone_f) (void *);
typedef int    (*openscop_equal_f) (void *, void *);


/**
 * The openscop_extension_id structure stores the URI and base
 * functions pointers an extension implementation has to offer. It
 * is a node in a NULL-terminated list of extension ids.
 */
struct openscop_extension_id {
  char * URI;               /**< Unique extension identifier string */
  openscop_idump_f  idump;  /**< Pointer to extension idump function */
  openscop_dump_f   dump;   /**< Pointer to extension dump function */
  openscop_sprint_f sprint; /**< Pointer to extension sprint function */
  openscop_sread_f  sread;  /**< Pointer to extension sread function */
  openscop_malloc_f malloc; /**< Pointer to extension malloc function */
  openscop_free_f   free;   /**< Pointer to extension free function */
  openscop_clone_f  clone;  /**< Pointer to extension clone function */
  openscop_equal_f  equal;  /**< Pointer to extension equal function */
  struct openscop_extension_id * next; /**< Next id in the list */
};
typedef struct openscop_extension_id   openscop_extension_id_t;
typedef struct openscop_extension_id * openscop_extension_id_p;


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/
void openscop_extension_id_idump(FILE *, openscop_extension_id_p, int);
void openscop_extension_id_dump(FILE *, openscop_extension_id_p);


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/
void                    openscop_extension_id_add(openscop_extension_id_p *,
                                                 openscop_extension_id_p);
openscop_extension_id_p openscop_extension_id_malloc();
void                    openscop_extension_id_free(openscop_extension_id_p);


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/
openscop_extension_id_p openscop_extension_id_nclone(openscop_extension_id_p,
                                                     int);
openscop_extension_id_p openscop_extension_id_clone(openscop_extension_id_p);
int                     openscop_extension_id_equal(openscop_extension_id_p,
                                                    openscop_extension_id_p);
openscop_extension_id_p openscop_extension_id_lookup(openscop_extension_id_p,
                                                     char *);

# if defined(__cplusplus)
  }
# endif

#endif /* define OPENSCOP_EXTENSION_ID_H */
