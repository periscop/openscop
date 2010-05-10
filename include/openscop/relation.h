
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                          relation.h                             **
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


#ifndef OPENSCOP_RELATION_H
# define OPENSCOP_RELATION_H

# include <stdio.h>
# include <openscop/macros.h>
# include <openscop/vector.h>


# if defined(__cplusplus)
extern "C"
  {
# endif


/**
 * The openscop_relation_t structure stores a union of relations. It is a
 * NULL-terminated linked list of relations. Each relation is described
 * using a matrix where each row represents a linear constraint. The entries
 * of each row are organised in the following order:
 * - An equality/inequality tag: 0 means the row corresponds to an
 *   equality constraint == 0, 1 means it is an inequality >= 0.
 * - The coefficients of the output dimensions.
 * - The coefficients of the input dimensions (0 for a set).
 * - The coefficients of the local (existentially quantified) dimensions.
 * - The coefficients of the parameters.
 * - The coefficient of the constant.
 * Thus we have the following invariant: nb_columns =
 * 1 + nb_output_dims + nb_input_dims + nb_local_dims + nb_parameters + 1.
 * Moreover we use the following conventions:
 * - Sets (e.g., iteration domains) are the images of relations with a
 *   zero-dimensional domain, hence the number of input dimensions is 0.
 * - The first output dimension of any access relations corresponds to
 *   the name of the array.
 */
struct openscop_relation
{
  unsigned nb_rows;               /**< The number of rows */
  unsigned nb_columns;	          /**< The number of columns */
  unsigned nb_output_dims;        /**< The number of output dimensions */
  unsigned nb_input_dims;         /**< The number of input dimensions */
  unsigned nb_local_dims;         /**< The number of local (existentially
                                       quantified) dimensions */
  unsigned nb_parameters;         /**< The number of parameters */
  openscop_int_t ** m;             /**< An array of pointers to the beginning
			               of each row of the relation matrix */
  openscop_int_t * store;          /**< The relation matrix is stored here,
                                       contiguously in memory */
  struct openscop_relation * next; /**< Pointer to the next relation in the
                                       union of relations (NULL if none) */
};
typedef struct openscop_relation   openscop_relation_t;
typedef struct openscop_relation * openscop_relation_p;


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
#endif /* define OPENSCOP_RELATION_H */
