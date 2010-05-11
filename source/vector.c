
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                           vector.c                              **
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


# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <openscop/vector.h>


/*+****************************************************************************
 *                          Structure display function                        *
 ******************************************************************************/


/**
 * openscop_vector_print_structure function:
 * Displays a openscop_vector_t structure (*vector) into a file (file, possibly
 * stdout) in a way that trends to be understandable without falling in a deep
 * depression or, for the lucky ones, getting a headache... It includes an
 * indentation level (level) in order to work with others print_structure
 * functions.
 * \param file   File where informations are printed.
 * \param vector The vector whose information have to be printed.
 * \param level  Number of spaces before printing, for each line.
 **
 * - 01/05/2008: first version.
 */
void
openscop_vector_print_structure(FILE * file, openscop_vector_p vector, int level)
{
  int j;

  if (vector != NULL)
  {
    /* Go to the right level. */
    for (j = 0; j < level; j++)
      fprintf(file,"|\t");
    fprintf(file,"+-- openscop_vector_t\n");

    for (j = 0; j <= level; j++)
      fprintf(file,"|\t");
    fprintf(file,"%d\n",vector->Size);

    /* Display the vector. */
    for (j = 0; j <= level; j++)
      fprintf(file,"|\t");

    fprintf(file,"[ ");

    for (j = 0; j < vector->Size; j++)
    {
      SCOPINT_print(file,OPENSCOP_FMT,vector->p[j]);
      fprintf(file," ");
    }

    fprintf(file,"]\n");
  }
  else
  {
    /* Go to the right level. */
    for (j = 0; j < level; j++)
      fprintf(file,"|\t");
    fprintf(file,"+-- NULL vector\n");
  }

  /* The last line. */
  for (j = 0; j <= level; j++)
    fprintf(file,"|\t");
  fprintf(file,"\n");
}


/**
 * openscop_vector_print function:
 * This function prints the content of a openscop_vector_t structure
 * (*vector) into a file (file, possibly stdout).
 * \param file   File where informations are printed.
 * \param vector The vector whose information have to be printed.
 **
 * - 01/05/2008: first version.
 */
void
openscop_vector_print(FILE * file, openscop_vector_p vector)
{
  openscop_vector_print_structure(file,vector,0);
}


/*+****************************************************************************
 *                    Memory allocation/deallocation function                 *
 ******************************************************************************/


/**
 * openscop_vector_malloc function:
 * This function allocates the memory space for a openscop_vector_t structure and
 * sets its fields with default values. Then it returns a pointer to the
 * allocated space.
 * \param Size The number of entries of the vector to allocate.
 **
 * - 01/05/2008: first version.
 */
openscop_vector_p
openscop_vector_malloc(unsigned Size)
{
  openscop_vector_p vector;
  openscop_int_t * p;
  int i ;

  vector = (openscop_vector_p)malloc(sizeof(openscop_vector_t));
  if (vector == NULL)
  {
    fprintf(stderr, "[Scoplib] Memory Overflow.\n");
    exit(1);
  }
  vector->Size = Size;
  if (Size == 0)
    vector->p = NULL;
  else
  {
    p = (openscop_int_t *)malloc(Size * sizeof(openscop_int_t));
    if (p == NULL)
    {
      fprintf(stderr, "[Scoplib] Memory Overflow.\n");
      exit(1);
    }
    vector->p = p;
    for (i = 0; i < Size; i++)
      SCOPINT_init_set_si(vector->p[i],0);
  }
  return vector;
}


/**
 * openscop_vector_free function:
 * This function frees the allocated memory for a openscop_vector_t structure.
 * \param vector The pointer to the vector we want to free.
 **
 * - 01/05/2008: first version.
 */
void
openscop_vector_free(openscop_vector_p vector)
{
  int i;
  openscop_int_t * p;

  if (vector != NULL)
  {
    p = vector->p;
    for (i = 0; i < vector->Size; i++)
      SCOPINT_clear(*p++);

    free(vector->p);
    free(vector);
  }
}


/*+****************************************************************************
 *                            Processing functions                            *
 ******************************************************************************/

/**
 * openscop_vector_add_scalar function:
 * This function adds a scalar to the vector representation of an affine
 * expression (this means we add the scalar only to the very last entry of the
 * vector). It returns a new vector resulting from this addition.
 * \param vector The basis vector.
 * \param scalar The scalar to add to the vector.
 **
 * - 01/05/2008: first version.
 */
openscop_vector_p
openscop_vector_add_scalar(openscop_vector_p vector, int scalar)
{
  int i;
  openscop_vector_p result;

  if ((vector == NULL) || (vector->Size < 2))
  {
    fprintf(stderr,"[Scoplib] Error: incompatible vector for addition\n");
    exit(1);
  }

  result = openscop_vector_malloc(vector->Size);
  for (i = 0; i < vector->Size; i++)
    SCOPINT_assign(result->p[i],vector->p[i]);
  SCOPINT_add_int(result->p[vector->Size - 1],
		  vector->p[vector->Size - 1],scalar);

  return result;
}


/**
 * openscop_vector_add function:
 * This function achieves the addition of two vectors and returns the
 * result as a new vector (the addition means the ith entry of the new vector
 * is equal to the ith entry of vector v1 plus the ith entry of vector v2).
 * \param v1 The first vector for the addition.
 * \param v2 The second vector for the addition (result is v1+v2).
 **
 * - 01/05/2008: first version.
 */
openscop_vector_p
openscop_vector_add(openscop_vector_p v1, openscop_vector_p v2)
{
  int i;
  openscop_vector_p v3;

  if ((v1 == NULL) || (v2 == NULL) || (v1->Size != v2->Size))
  {
    fprintf(stderr,"[Scoplib] Error: incompatible vectors for addition\n");
    exit(1);
  }

  v3 = openscop_vector_malloc(v1->Size);
  for (i = 0; i < v1->Size; i++)
    SCOPINT_addto(v3->p[i],v1->p[i],v2->p[i]);

  return v3;
}


/**
 * openscop_vector_sub function:
 * This function achieves the subtraction of two vectors and returns the
 * result as a new vector (the addition means the ith entry of the new vector
 * is equal to the ith entry of vector v1 minus the ith entry of vector v2).
 * \param v1 The first vector for the subtraction.
 * \param v2 The second vector for the subtraction (result is v1-v2).
 **
 * - 01/05/2008: first version.
 */
openscop_vector_p
openscop_vector_sub(openscop_vector_p v1, openscop_vector_p v2)
{
  int i;
  openscop_vector_p v3;

  if ((v1 == NULL) || (v2 == NULL) || (v1->Size != v2->Size))
  {
    fprintf(stderr,"[Scoplib] Error: incompatible vectors for subtraction\n");
    exit(1);
  }

  v3 = openscop_vector_malloc(v1->Size);
  for (i = 0; i < v1->Size; i++)
    SCOPINT_subtract(v3->p[i],v1->p[i],v2->p[i]);

  return v3;
}


/**
 * openscop_vector_tag_inequality function:
 * This function tags a vector representation of a contraint as being an
 * inequality >=0. This means in the PolyLib format, to set to 1 the very first
 * entry of the vector. It modifies directly the vector provided as an argument.
 * \param vector The vector to be tagged.
 **
 * - 01/05/2008: first version.
 */
void
openscop_vector_tag_inequality(openscop_vector_p vector)
{
  if ((vector == NULL) || (vector->Size < 1))
  {
    fprintf(stderr,"[Scoplib] Error: vector cannot be tagged\n");
    exit(1);
  }
  SCOPINT_set_si(vector->p[0],1);
}


/**
 * openscop_vector_tag_equality function:
 * This function tags a vector representation of a contraint as being an
 * equality ==0. This means in the PolyLib format, to set to 0 the very first
 * entry of the vector. It modifies directly the vector provided as an argument.
 * \param vector The vector to be tagged.
 **
 * - 01/05/2008: first version.
 */
void
openscop_vector_tag_equality(openscop_vector_p vector)
{
  if ((vector == NULL) || (vector->Size < 1))
  {
    fprintf(stderr,"[Scoplib] Error: vector cannot be tagged\n");
    exit(1);
  }
  SCOPINT_set_si(vector->p[0],0);
}
