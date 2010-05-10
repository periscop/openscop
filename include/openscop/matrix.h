
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                           matrix.h                              **
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
 *  | T | |   |   | e |   | |   | |   |   |   | |   | |   | |    \  \  \     *
 *  | E | |   |   |   |   | |   | |   |   |   | |   | |   | |     \  \  \    *
 *  | * |*| * | * | * | * |*| * |*| * | * | * |*| * |*| * | /      \* \  \   *
 *  | O |p| e | n | S | c |o| p |-| L | i | b |r| a |r| y |/        \  \ /   *
 *  '---'-'---'---'---'---'-'---'-'---'---'---'-'---'-'---'          '--'    *
 *                                                                           *
 * Copyright (C) 2008 University Paris-Sud and INRIA                         *
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


#ifndef OPENSCOP_MATRIX_H
# define OPENSCOP_MATRIX_H

# include <stdio.h>
# include <openscop/macros.h>
# include <openscop/vector.h>


# if defined(__cplusplus)
extern "C"
  {
# endif


/**
 * The openscop_matrix_t structure stores a matrix information in the PolyLib
 * format (the first entry of each row has a specific meaning). When a row
 * describes a linear constraint, a 0 means it is an equality == 0, a 1 means
 * an inequality >= 0. When a row describes an array access, a number different
 * than 0 is the array identifier (the remainder of the row describes the
 * access function of the first dimension of this array), otherwise it means
 * the row describes access functions for next array dimensions.
 */
struct openscop_matrix
{
  unsigned NbRows;       /**< The number of rows */
  unsigned NbColumns;	 /**< The number of columns */
  openscop_int_t ** p;    /**< An array of pointers to the beginning
			    of each row */
  openscop_int_t * p_Init;/**< The matrix is stored here, contiguously
			    in memory */
  int p_Init_size;       /**< Needed to free the memory allocated by
			    mpz_init. */
};
typedef struct openscop_matrix   openscop_matrix_t;
typedef struct openscop_matrix * openscop_matrix_p;


/**
 * The openscop_matrix_list_t structure describes a (chained) list of
 * matrices. It is used to store the list of matrices for the
 * iteration domain of a statement (possibly being a union of
 * convex domains).
 *
 */
struct openscop_matrix_list
{
  openscop_matrix_p elt;             /**< An element of the list. */
  struct openscop_matrix_list* next; /**< Pointer to the next element
				       of the list.*/
};
typedef struct openscop_matrix_list	openscop_matrix_list_t;
typedef struct openscop_matrix_list *	openscop_matrix_list_p;


/*+****************************************************************************
 *                          Structure display function                        *
 ******************************************************************************/
void          openscop_matrix_print_structure(FILE *, openscop_matrix_p, int);
void          openscop_matrix_print(FILE *, openscop_matrix_p);
void          openscop_matrix_print_dot_scop(FILE *, openscop_matrix_p, int,
					    int, char **, int, char **,
					    int, char **);

void          openscop_matrix_list_print_structure(FILE *,
						  openscop_matrix_list_p, int);
void          openscop_matrix_list_print(FILE *, openscop_matrix_list_p);
void          openscop_matrix_list_print_dot_scop(FILE *, openscop_matrix_list_p,
						 int, int, char **, int,
						 char **, int, char **);


/******************************************************************************
 *                               Reading function                             *
 ******************************************************************************/
openscop_matrix_p	openscop_matrix_read(FILE *);
openscop_matrix_list_p	openscop_matrix_list_read(FILE *);
openscop_matrix_p	openscop_matrix_read_arrays(FILE *, char ***, int *);


/*+****************************************************************************
 *                    Memory allocation/deallocation function                 *
 ******************************************************************************/
openscop_matrix_p	openscop_matrix_malloc(unsigned, unsigned);
void			openscop_matrix_free_inside(openscop_matrix_p);
void			openscop_matrix_free(openscop_matrix_p);

openscop_matrix_list_p	openscop_matrix_list_malloc();
void			openscop_matrix_list_free(openscop_matrix_list_p);


/*+****************************************************************************
 *                            Processing functions                            *
 ******************************************************************************/
openscop_matrix_p openscop_matrix_ncopy(openscop_matrix_p, int);
openscop_matrix_p openscop_matrix_copy(openscop_matrix_p);
void	openscop_matrix_replace_vector(openscop_matrix_p, openscop_vector_p, int);
void    openscop_matrix_insert_vector(openscop_matrix_p, openscop_vector_p, int);
void	openscop_matrix_add_vector(openscop_matrix_p, openscop_vector_p, int);
void	openscop_matrix_sub_vector(openscop_matrix_p, openscop_vector_p, int);
openscop_matrix_p openscop_matrix_from_vector(openscop_vector_p);
void    openscop_matrix_replace_matrix(openscop_matrix_p, openscop_matrix_p, int);
void    openscop_matrix_insert_matrix(openscop_matrix_p, openscop_matrix_p, int);
openscop_matrix_p openscop_matrix_concat(openscop_matrix_p, openscop_matrix_p);
int	openscop_matrix_equal(openscop_matrix_p, openscop_matrix_p);    
    
# if defined(__cplusplus)
  }
# endif
#endif /* define OPENSCOP_MATRIX_H */
