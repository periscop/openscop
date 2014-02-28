
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                     extensions/cloogoptions.h                   **
     **-----------------------------------------------------------------**
     **                   First version: 14/05/2013                     **
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


#ifndef OSL_CLOOGOPTIONS_H
# define OSL_CLOOGOPTIONS_H

# include <stdio.h>
# include <osl/interface.h>

# if defined(__cplusplus)
extern "C"
  {
# endif


# define OSL_URI_CLOOGOPTIONS "cloogoptions"


struct osl_cloogoptions
{
  /* OPTIONS FOR LOOP GENERATION */
  int l ;           /* Last level to optimize. */
  int l_set ;       /* l is set. */
  int f ;           /* First level to optimize. */
  int f_set ;       /* f is set. */

  int *ls;          /* Last level to optimize (statement-wise). */
  int ls_set;       /* ls is set. */
  int *fs;          /* First level to optimize (statement-wise). */
  int fs_set;       /* fs is set. */
  int fs_ls_size;   /* Size of the fs and ls arrays (same size) */
  int fs_ls_size_set; /* fs_ls_size is set */
  int stop ;        /* Level to stop code generation. */
  int stop_set ;    /* stop is set. */
  int strides ;     /* 1 if user wants to handle non-unit strides (then loop
                     * increment can be something else than one), 0 otherwise.
                     */
  int strides_set;  /* strides is set. */
  int sh;	          /* 1 for computing simple hulls */
  int sh_set ;      /* sh is set. */
  int first_unroll; /* The first dimension to unroll */
  int first_unroll_set ;    /* first_unroll is set. */

  /* OPTIONS FOR PRETTY PRINTING */
  int esp ;         /* 1 if user wants to spread all equalities, i.e. when there
                     * is something like "i = 3*j + 1 ; A[i] = 0 ;" the
                     * generator will write "A[3*j + 1] = 0 ;", 0 otherwise.
                     */
  int esp_set ;     /* esp is set. */
  int fsp ;         /* The iteration level where equalities spreading can begin
                     * (it might happen that the user wants not to spread values
                     * of scattering iterators).
                     */
  int fsp_set ;     /* fsp is set. */
  int otl ;         /* 1 for eliminate loops running just one time and write
                     * them as an affectation of the iterator, 0 otherwise.
                     */
  int otl_set ;     /* otl is set. */
  int block ;       /* 1 to make one new block {...} per new dimension,
                     * 0 otherwise.
                     */
  int block_set ;    /* block is set. */
  int compilable;   /* 1 to generate a compilable code by using
                     * preprocessing, 0 otherwise.
                     */
  int compilable_set ;    /* compilable is set. */
  int callable;     /* 1 to generate callable code by using
                     * preprocessing, 0 otherwise.
                     */
  int callable_set ;    /* callable is set. */
  int language;     /* 1 to generate FORTRAN, 0 for C otherwise. */
  int language_set ;    /* language is set. */

  int save_domains; /* Save unsimplified copy of domain. */
  int save_domains_set ;    /* save_domains is set. */

  /* MISC OPTIONS */
  char * name ;     /* Name of the input file. */
  int name_set ;
  int openscop;     /* 1 if the input file has OpenScop format, 0 otherwise. */
  int openscop_set ;    /* openscop is set. */
  struct osl_scop *scop; /* Input OpenScop scop if any, NULL otherwise. */

  int quiet;        /* Don't print any informational messages. */
  int quiet_set ;   /* quiet is set. */
} ;

typedef struct osl_cloogoptions osl_cloogoptions_t;
typedef struct osl_cloogoptions * osl_cloogoptions_p;

/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/
void osl_cloogoptions_idump(FILE *, osl_cloogoptions_p, int);
void osl_cloogoptions_dump(FILE *, osl_cloogoptions_p);
char* osl_cloogoptions_sprint(osl_cloogoptions_p);


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/
osl_cloogoptions_p osl_cloogoptions_sread(char **);

/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/
osl_cloogoptions_p osl_cloogoptions_malloc();
void osl_cloogoptions_free(osl_cloogoptions_p);


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/
osl_cloogoptions_p osl_cloogoptions_clone(osl_cloogoptions_p);
int osl_cloogoptions_equal(osl_cloogoptions_p, osl_cloogoptions_p);
osl_interface_p   osl_cloogoptions_interface();


# if defined(__cplusplus)
  }
# endif

#endif /* define OSL_CLOOGOPTIONS_H */
