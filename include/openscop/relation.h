
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


#ifndef OPENSCOP_RELATION_H
# define OPENSCOP_RELATION_H

# include <stdio.h>
# include <openscop/macros.h>
# include <openscop/util.h>
# include <openscop/names.h>
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
 * 1 + nb_output_dims + nb_input_dims + dims + nb_parameters + 1.
 * Moreover we use the following conventions:
 * - Sets (e.g., iteration domains) are the images of relations with a
 *   zero-dimensional domain, hence the number of input dimensions is 0.
 * - The first output dimension of any access relations corresponds to
 *   the name of the array.
 * The type field may provide some semantics about the relation, it may be:
 * - Undefined : OPENSCOP_UNDEFINED,
 * - An iteration domain : OPENSCOP_TYPE_DOMAIN,
 * - A scattering relation : OPENSCOP_TYPE_SCATTERING,
 * - An access relation : OPENSCOP_TYPE_ACCESS.
 */
struct openscop_relation {
  int type;                        /**< Semantics about the relation */
  int nb_rows;                     /**< The number of rows */
  int nb_columns;	           /**< The number of columns */
  int nb_output_dims;              /**< The number of output dimensions */
  int nb_input_dims;               /**< The number of input dimensions */
  int nb_local_dims;               /**< The number of local (existentially
                                        quantified) dimensions */
  int nb_parameters;               /**< The number of parameters */
  openscop_int_t ** m;             /**< An array of pointers to the beginning
			                of each row of the relation matrix */
  struct openscop_relation * next; /**< Pointer to the next relation in the
                                        union of relations (NULL if none) */
};
typedef struct openscop_relation   openscop_relation_t;
typedef struct openscop_relation * openscop_relation_p;


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/
void                openscop_relation_idump(FILE *,
                                        openscop_relation_p, int);
void                openscop_relation_dump(FILE *, openscop_relation_p);
char *              openscop_relation_expression(
                                        openscop_relation_p relation,
                                        int row, openscop_names_p names);
void                openscop_relation_print(FILE *,
                                        openscop_relation_p,
                                        openscop_names_p);


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/
openscop_relation_p openscop_relation_read(FILE *);
openscop_relation_p openscop_relation_read_arrays(FILE *, char ***, int *);


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/
openscop_relation_p openscop_relation_malloc(int, int);
void                openscop_relation_free_inside(openscop_relation_p);
void                openscop_relation_free(openscop_relation_p);


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/
int                 openscop_relation_is_matrix(openscop_relation_p);
openscop_relation_p openscop_relation_ncopy(openscop_relation_p, int);
openscop_relation_p openscop_relation_copy(openscop_relation_p);
void                openscop_relation_replace_vector(openscop_relation_p,
                                        openscop_vector_p, int);
void                openscop_relation_insert_vector(openscop_relation_p,
                                        openscop_vector_p, int);
void                openscop_relation_add_vector(openscop_relation_p,
                                        openscop_vector_p, int);
void                openscop_relation_sub_vector(openscop_relation_p,
                                        openscop_vector_p, int);
openscop_relation_p openscop_relation_from_vector(openscop_vector_p);
void                openscop_relation_replace_relation(openscop_relation_p,
                                        openscop_relation_p, int);
void                openscop_relation_insert_relation(openscop_relation_p,
                                        openscop_relation_p, int);
openscop_relation_p openscop_relation_concat(openscop_relation_p,
                                        openscop_relation_p);
int                 openscop_relation_equal(openscop_relation_p,
                                        openscop_relation_p);    
int                 openscop_relation_integrity_check(openscop_relation_p,
                                        int, int, int, int);
openscop_relation_p openscop_relation_union(openscop_relation_p,
                                        openscop_relation_p);
void                openscop_relation_set_type(openscop_relation_p, int);
int                 openscop_relation_get_array_id(openscop_relation_p);


# if defined(__cplusplus)
  }
# endif
#endif /* define OPENSCOP_RELATION_H */
