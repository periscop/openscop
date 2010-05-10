
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


#ifndef SCOPLIB_RELATION_H
# define SCOPLIB_RELATION_H

# include <stdio.h>
# include <openscop/macros.h>
# include <openscop/vector.h>


# if defined(__cplusplus)
extern "C"
  {
# endif


/**
 * The scoplib_relation_t structure stores a union of relations. It is a
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
struct scoplib_relation
{
  unsigned nb_rows;               /**< The number of rows */
  unsigned nb_columns;	          /**< The number of columns */
  unsigned nb_output_dims;        /**< The number of output dimensions */
  unsigned nb_input_dims;         /**< The number of input dimensions */
  unsigned nb_local_dims;         /**< The number of local (existentially
                                       quantified) dimensions */
  unsigned nb_parameters;         /**< The number of parameters */
  scoplib_int_t ** m;             /**< An array of pointers to the beginning
			               of each row of the relation matrix */
  scoplib_int_t * store;          /**< The relation matrix is stored here,
                                       contiguously in memory */
  struct scoplib_relation * next; /**< Pointer to the next relation in the
                                       union of relations (NULL if none) */
};
typedef struct scoplib_relation   scoplib_relation_t;
typedef struct scoplib_relation * scoplib_relation_p;


/*+****************************************************************************
 *                          Structure display function                        *
 ******************************************************************************/
void          scoplib_matrix_print_structure(FILE *, scoplib_matrix_p, int);
void          scoplib_matrix_print(FILE *, scoplib_matrix_p);
void          scoplib_matrix_print_dot_scop(FILE *, scoplib_matrix_p, int,
					    int, char **, int, char **,
					    int, char **);

void          scoplib_matrix_list_print_structure(FILE *,
						  scoplib_matrix_list_p, int);
void          scoplib_matrix_list_print(FILE *, scoplib_matrix_list_p);
void          scoplib_matrix_list_print_dot_scop(FILE *, scoplib_matrix_list_p,
						 int, int, char **, int,
						 char **, int, char **);


/******************************************************************************
 *                               Reading function                             *
 ******************************************************************************/
scoplib_matrix_p	scoplib_matrix_read(FILE *);
scoplib_matrix_list_p	scoplib_matrix_list_read(FILE *);
scoplib_matrix_p	scoplib_matrix_read_arrays(FILE *, char ***, int *);


/*+****************************************************************************
 *                    Memory allocation/deallocation function                 *
 ******************************************************************************/
scoplib_matrix_p	scoplib_matrix_malloc(unsigned, unsigned);
void			scoplib_matrix_free_inside(scoplib_matrix_p);
void			scoplib_matrix_free(scoplib_matrix_p);

scoplib_matrix_list_p	scoplib_matrix_list_malloc();
void			scoplib_matrix_list_free(scoplib_matrix_list_p);


/*+****************************************************************************
 *                            Processing functions                            *
 ******************************************************************************/
scoplib_matrix_p scoplib_matrix_ncopy(scoplib_matrix_p, int);
scoplib_matrix_p scoplib_matrix_copy(scoplib_matrix_p);
void	scoplib_matrix_replace_vector(scoplib_matrix_p, scoplib_vector_p, int);
void    scoplib_matrix_insert_vector(scoplib_matrix_p, scoplib_vector_p, int);
void	scoplib_matrix_add_vector(scoplib_matrix_p, scoplib_vector_p, int);
void	scoplib_matrix_sub_vector(scoplib_matrix_p, scoplib_vector_p, int);
scoplib_matrix_p scoplib_matrix_from_vector(scoplib_vector_p);
void    scoplib_matrix_replace_matrix(scoplib_matrix_p, scoplib_matrix_p, int);
void    scoplib_matrix_insert_matrix(scoplib_matrix_p, scoplib_matrix_p, int);
scoplib_matrix_p scoplib_matrix_concat(scoplib_matrix_p, scoplib_matrix_p);
int	scoplib_matrix_equal(scoplib_matrix_p, scoplib_matrix_p);    
    
# if defined(__cplusplus)
  }
# endif
#endif /* define SCOPLIB_RELATION_H */
