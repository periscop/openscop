
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                           matrix.c                              **
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
# include <string.h>
# include <ctype.h>
# include <openscop/matrix.h>


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * openscop_matrix_print_structure function:
 * Displays a openscop_matrix_t structure (*matrix) into a file (file, possibly
 * stdout) in a way that trends to be understandable without falling in a deep
 * depression or, for the lucky ones, getting a headache... It includes an
 * indentation level (level) in order to work with others print_structure
 * functions.
 * \param file   File where informations are printed.
 * \param matrix The matrix whose information have to be printed.
 * \param level  Number of spaces before printing, for each line.
 */
void
openscop_matrix_print_structure(FILE * file, openscop_matrix_p matrix,
                                int level)
{
  int i, j;

  /* Go to the right level. */
  for (j = 0; j < level; j++)
    fprintf(file,"|\t");

  if (matrix != NULL)
  {
    fprintf(file,"+-- openscop_matrix_t\n");

    for(j = 0; j <= level; j++)
      fprintf(file,"|\t");
    fprintf(file,"%d %d\n",matrix->NbRows,matrix->NbColumns);

    /* Display the matrix. */
    for (i = 0; i < matrix->NbRows; i++)
    {
      for (j = 0; j <= level; j++)
        fprintf(file,"|\t");

      fprintf(file,"[ ");

      for (j = 0; j < matrix->NbColumns; j++)
      {
        SCOPINT_print(file,OPENSCOP_FMT,matrix->p[i][j]);
        fprintf(file," ");
      }

      fprintf(file,"]\n");
    }
  }
  else
    fprintf(file,"+-- NULL matrix\n");

  /* The last line. */
  for (j = 0; j <= level; j++)
    fprintf(file,"|\t");
  fprintf(file,"\n");
}


/**
 * openscop_matrix_print function:
 * This function prints the content of a openscop_matrix_t structure
 * (*matrix) into a file (file, possibly stdout).
 * \param file   File where informations are printed.
 * \param matrix The matrix whose information have to be printed.
 */
void
openscop_matrix_print(FILE * file, openscop_matrix_p matrix)
{
  openscop_matrix_print_structure(file,matrix,0);
}



/**
 * openscop_matrix_expression_element function:
 * This function returns a string containing the printing of a value (possibly
 * an iterator or a parameter with its coefficient or a constant).
 * \param val   The coefficient or constant value.
 * \param first Pointer to a boolean set to 1 if the current value is the first
 *              of an expresion, 0 otherwise (this function may update it).
 * \param cst   A boolean set to 1 if the value is a constant, 0 otherwise.
 * \param name  String containing the name of the iterator or of the parameter.
 */
static
char *
openscop_matrix_expression_element(openscop_int_t val, int * first, int cst,
				  char * name)
{
  char * sval, * body, * temp;

  temp = (char *)malloc(OPENSCOP_MAX_STRING * sizeof(char));
  body = (char *)malloc(OPENSCOP_MAX_STRING * sizeof(char));
  sval = (char *)malloc(OPENSCOP_MAX_STRING * sizeof(char));
  body[0] = '\0';
  sval[0] = '\0';

  /* statements for the 'normal' processing. */
  if (SCOPINT_notzero_p(val) && (!cst))
  {
    if ((*first) || SCOPINT_neg_p(val))
    {
      if (SCOPINT_one_p(val))           /* case 1 */
        sprintf(sval,"%s",name);
      else
      {
        if (SCOPINT_mone_p(val))        /* case -1 */
          sprintf(sval,"-%s",name);
	else                         /* default case */
	{
	  SCOPINT_sprint(sval,OPENSCOP_FMT_TXT,val);
	  sprintf(temp,"*%s",name);
	  strcat(sval,temp);
        }
      }
      *first = 0;
    }
    else
    {
      if (SCOPINT_one_p(val))
        sprintf(sval,"+%s",name);
      else
      {
        sprintf(sval,"+");
	SCOPINT_sprint(temp,OPENSCOP_FMT_TXT,val);
	strcat(sval,temp);
	sprintf(temp,"*%s",name);
	strcat(sval,temp);
      }
    }
  }
  else
  {
    if (cst)
    {
      if ((SCOPINT_zero_p(val) && (*first)) || SCOPINT_neg_p(val))
        SCOPINT_sprint(sval,OPENSCOP_FMT_TXT,val);
      if (SCOPINT_pos_p(val))
      {
        if (!(*first))
        {
	  SCOPINT_sprint(sval,"+"OPENSCOP_FMT_TXT,val); /* Block macro ! */
	}
	else
          SCOPINT_sprint(sval,OPENSCOP_FMT_TXT,val);
      }
    }
  }
  free(temp);
  free(body);

  return(sval);
}


/**
 * openscop_matrix_expression function:
 * This function returns a string corresponding to an affine expression
 * stored at the "row"^th row of the matrix pointed by "matrix".
 * \param matrix        A set of linear expressions.
 * \param row           The row of the matrix corresponding to the expression.
 * \param nb_iterators  The number of iterators for the considered statement.
 * \param iterators     An array containing iterator names for the statement.
 * \param nb_parameters The number of parameters in the SCoP.
 * \param parameters    An array containing all parameters names.
 */
static
char *
openscop_matrix_expression(openscop_matrix_p matrix, int row,
			  int nb_iterators,  char ** iterators,
			  int nb_parameters, char ** parameters)
{
  int i, first = 1;
  char * sline, * sval;

  sline = (char *)malloc(OPENSCOP_MAX_STRING * sizeof(char)) ;
  sline[0] = '\0' ;

  /* First the iterator part. */
  for (i = 1; i <= nb_iterators; i++)
  {
    sval = openscop_matrix_expression_element(matrix->p[row][i],&first,0,
					     iterators[i-1]);
    strcat(sline,sval);
    free(sval);
  }

  /* Next the parameter part. */
  for (i = nb_iterators + 1; i <= nb_iterators + nb_parameters; i++)
  {
    sval = openscop_matrix_expression_element(matrix->p[row][i],&first,0,
					     parameters[i - nb_iterators - 1]);
    strcat(sline,sval);
    free(sval);
  }

  /* Finally the constant part (yes, I reused it). */
  sval = openscop_matrix_expression_element(matrix->p[row][i],&first,1,NULL);
  strcat(sline,sval);
  free(sval);

  return sline;
}


/**
 * openscop_matrix_print_dot_scop function:
 * This function prints the content of a openscop_matrix_t structure
 * (*matrix) into a file (file, possibly stdout) for the .scop format.
 * \param file          File where informations are printed.
 * \param matrix        The matrix whose information have to be printed.
 * \param type          Semantic about this matrix (domain, access...).
 * \param nb_iterators  The number of iterators for the considered statement.
 * \param iterators     An array containing iterator names for the statement.
 * \param nb_parameters The number of parameters in the SCoP.
 * \param parameters    An array containing all parameters names.
 * \param nb_arrays     The number of arrays accessed in the SCoP.
 * \param arrays        An array containing all accessed array names.
 */
void
openscop_matrix_print_dot_scop(FILE * file, openscop_matrix_p matrix, int type,
			      int nb_iterators,  char ** iterators,
			      int nb_parameters, char ** parameters,
			      int nb_arrays,     char ** arrays)
{
  int i, j, k;
  char * expression;

  if (matrix == NULL)
  {
    fprintf(file,"0 %d\n",nb_iterators+nb_parameters+2);
    return;
  }

  fprintf(file,"%d %d\n",matrix->NbRows,matrix->NbColumns);

  for (i = 0; i < matrix->NbRows; i++)
  {
    for (j = 0; j < matrix->NbColumns; j++)
    {
      SCOPINT_print(file,OPENSCOP_FMT,matrix->p[i][j]);
      fprintf(file," ");
    }

    if (type == OPENSCOP_TYPE_DOMAIN)
    {
      expression = openscop_matrix_expression(matrix,i,nb_iterators,iterators,
					     nb_parameters,parameters);
      fprintf(file,"   ## %s",expression);
      free(expression);
      if (SCOPINT_zero_p(matrix->p[i][0]))
        fprintf(file," == 0");
      else
        fprintf(file," >= 0");
    }

    if (type == OPENSCOP_TYPE_SCATTERING)
    {
      expression = openscop_matrix_expression(matrix,i,nb_iterators,iterators,
					     nb_parameters,parameters);
      fprintf(file,"   ## %s",expression);
      free(expression);
    }

    if (type == OPENSCOP_TYPE_ACCESS)
    {
      if (SCOPINT_notzero_p(matrix->p[i][0]))
      {
	if (strncmp(arrays[SCOPINT_get_si(matrix->p[i][0]) - 1],
		    OPENSCOP_FAKE_ARRAY, strlen(OPENSCOP_FAKE_ARRAY)))
	  fprintf(file,"   ## %s",arrays[SCOPINT_get_si(matrix->p[i][0]) - 1]);
	k = i;
	do
	{
	  expression = openscop_matrix_expression(matrix,k,nb_iterators,
						 iterators,
						 nb_parameters,parameters);
          fprintf(file,"[%s]",expression);
          free(expression);
	  k++;
	}
	while ((k < matrix->NbRows) && SCOPINT_zero_p(matrix->p[k][0]));
      }
      else
        fprintf(file,"   ##");
    }

    fprintf(file,"\n");
  }
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/**
 * openscop_matrix_read function:
 * Adaptation from the PolyLib. This function reads a matrix into a file (foo,
 * posibly stdin) and returns a pointer this matrix.
 */
openscop_matrix_p
openscop_matrix_read(FILE* foo)
{
  unsigned NbRows, NbColumns;
  int i, j, n;
  char* c, s[OPENSCOP_MAX_STRING], str[OPENSCOP_MAX_STRING];
  openscop_matrix_p matrix;
  openscop_int_t* p;

  while (fgets(s, OPENSCOP_MAX_STRING, foo) == 0)
    ;
  while ((*s=='#' || *s=='\n') ||
	 (sscanf(s, " %u %u", &NbRows, &NbColumns) < 2))
    fgets(s, OPENSCOP_MAX_STRING, foo);

  matrix = openscop_matrix_malloc(NbRows, NbColumns);

  p = matrix->p_Init;
  for (i = 0; i < matrix->NbRows; i++)
    {
      do
	{
	  c = fgets(s, OPENSCOP_MAX_STRING, foo);
	  while ((c != NULL) && isspace(*c) && (*c != '\n'))
	    c++;
	}
      while (c != NULL && (*c == '#' || *c == '\n'));

      if (c == NULL)
	{
	  fprintf(stderr, "[Scoplib] Error: not enough rows\n");
	  exit(1);
	}
      for (j = 0; j < matrix->NbColumns; j++)
	{
	  if (c == NULL || *c == '#' || *c == '\n')
	    {
	      fprintf(stderr, "[Scoplib] Error: not enough columns\n");
	      exit(1);
	    }
	  if (sscanf(c, "%s%n", str, &n) == 0)
	    {
	      fprintf(stderr, "[Scoplib] Error: not enough rows\n");
	      exit(1);
	    }
#if defined(OPENSCOP_INT_T_IS_MP)
      long long val;
	  sscanf(str, "%lld", &val);
	  mpz_set_si(*p++, val);
#else
	  sscanf(str, OPENSCOP_FMT_TXT, p++);
#endif
	  c += n;
	}
    }

  return matrix;
}


/**
 * openscop_matrix_read_arrays function:
 * This function reads a matrix into a file (foo, posibly stdin) and
 * returns a pointer this matrix. In addition, it reads the arrays as
 * comments at the end of the line.
 */
openscop_matrix_p
openscop_matrix_read_arrays(FILE* foo, char*** arrays, int* nb_arr)
{
  unsigned NbRows, NbColumns;
  int i, j, n;
  int count;
  char* c, s[OPENSCOP_MAX_STRING], str[OPENSCOP_MAX_STRING],
    buff[OPENSCOP_MAX_STRING];
  openscop_matrix_p matrix;
  openscop_int_t* p;

  while (fgets(s, OPENSCOP_MAX_STRING, foo) == 0)
    ;
  while ((*s=='#' || *s=='\n') ||
	 (sscanf(s, " %u %u", &NbRows, &NbColumns) < 2))
    fgets(s, OPENSCOP_MAX_STRING, foo);

  matrix = openscop_matrix_malloc(NbRows, NbColumns);

  p = matrix->p_Init;
  for (i = 0; i < matrix->NbRows; i++)
    {
      do
	{
	  c = fgets(s, OPENSCOP_MAX_STRING, foo);
	  while ((c != NULL) && isspace(*c) && (*c != '\n'))
	    c++;
	}
      while (c != NULL && (*c == '#' || *c == '\n'));

      if (c == NULL)
	{
	  fprintf(stderr, "[Scoplib] Error: not enough rows\n");
	  exit(1);
	}

      for (j = 0; j < matrix->NbColumns; j++)
	{
	  if (c == NULL || *c == '#' || *c == '\n')
	    {
	      fprintf(stderr, "[Scoplib] Error: not enough columns\n");
	      exit(1);
	    }
	  if (sscanf(c, "%s%n", str, &n) == 0)
	    {
	      fprintf(stderr, "[Scoplib] Error: not enough rows\n");
	      exit(1);
	    }
#if defined(OPENSCOP_INT_T_IS_MP)
      long long val;
	  sscanf(str, "%lld", &val);
	  mpz_set_si(*p++, val);
#else
	  sscanf(str, OPENSCOP_FMT_TXT, p++);
#endif
	  c += n;
	}
      /* Read the array, passed as a comment at the end of the line. */
      if (c)
	{
	  while (c && (isspace(*c) || *c == '#'))
	    ++c;
	  for (count = 0; c && *c != '[' && *c != '\n'; ++count)
	    buff[count] = *(c++);
	  buff[count] = '\0';
	  if (count && SCOPINT_get_si(matrix->p[i][0]))
	    {
	      /* Increase the buffer size if we run out of space. */
	      if (SCOPINT_get_si(matrix->p[i][0]) - 1 > *nb_arr)
		{
		  *nb_arr = SCOPINT_get_si(matrix->p[i][0]) - 1;
		  *arrays = (char**) realloc(*arrays,
					     sizeof(char*) * (*nb_arr + 1));
		}
	      /* Backup the array name. */
	      (*arrays)[SCOPINT_get_si(matrix->p[i][0]) - 1] = strdup(buff);
	    }
	}
    }

  return matrix;
}


/*+****************************************************************************
 *                    Memory allocation/deallocation function                 *
 ******************************************************************************/

/**
 * openscop_matrix_malloc function:
 * This function allocates the memory space for a openscop_matrix_t structure and
 * sets its fields with default values. Then it returns a pointer to the
 * allocated space.
 * \param NbRows    The number of row of the matrix to allocate.
 * \param NbColumns The number of columns of the matrix to allocate.
 */
openscop_matrix_p
openscop_matrix_malloc(unsigned NbRows, unsigned NbColumns)
{
  openscop_matrix_p matrix;
  openscop_int_t ** p, * q;
  int i, j;

  matrix = (openscop_matrix_p)malloc(sizeof(openscop_matrix_t));
  if (matrix == NULL)
  {
    fprintf(stderr, "[Scoplib] Memory Overflow.\n");
    exit(1);
  }
  matrix->NbRows = NbRows;
  matrix->NbColumns = NbColumns;
  matrix->p_Init_size = NbRows * NbColumns;
  if (matrix->p_Init_size == 0)
  {
    matrix->p = NULL;
    matrix->p_Init = NULL;
  }
  else
  {
    p = (openscop_int_t **)malloc(NbRows*sizeof(openscop_int_t *));
    if (p == NULL)
    {
      fprintf(stderr, "[Scoplib] Memory Overflow.\n");
      exit(1);
    }
    q = (openscop_int_t *)malloc(NbRows * NbColumns * sizeof(openscop_int_t));
    if (q == NULL)
    {
      fprintf(stderr, "[Scoplib] Memory Overflow.\n");
      exit(1);
    }
    matrix->p = p;
    matrix->p_Init = q;
    for (i = 0; i < NbRows; i++)
    {
      *p++ = q;
      for (j = 0; j < NbColumns; j++)
        SCOPINT_init_set_si(*(q+j),0);
      q += NbColumns;
    }
  }
  return matrix;
}


/**
 * openscop_matrix_free_inside function:
 * This function frees the allocated memory for the inside of a
 * openscop_matrix_t structure, i.e. only p and p_Init.
 * \param matrix The pointer to the matrix we want to free.
 */
void
openscop_matrix_free_inside(openscop_matrix_p matrix)
{
  int i;
  openscop_int_t * p;

  if (matrix == NULL)
    return;

  p = matrix->p_Init;
  for (i = 0; i < matrix->p_Init_size; i++)
    SCOPINT_clear(*p++);

  if (matrix->p_Init != NULL)
    free(matrix->p_Init);

  if (matrix->p != NULL)
    free(matrix->p);
}


/**
 * openscop_matrix_free function:
 * This function frees the allocated memory for a openscop_matrix_t structure.
 * \param matrix The pointer to the matrix we want to free.
 */
void
openscop_matrix_free(openscop_matrix_p matrix)
{
  if (matrix == NULL)
    return;

  openscop_matrix_free_inside(matrix);
  free(matrix);
}


/*+****************************************************************************
 *                            Processing functions                            *
 ******************************************************************************/


/**
 * openscop_matrix_ncopy function:
 * this functions builds and returns a "hard copy" (not a pointer copy) of a
 * openscop_matrix_t data structure such that the copy is restricted to the "n"
 * first rows of the matrix.
 * \param matrix The pointer to the matrix we want to copy.
 * \param n      The number of row of the matrix we want to copy.
 */
openscop_matrix_p
openscop_matrix_ncopy(openscop_matrix_p matrix, int n)
{
  int i, j;
  openscop_matrix_p copy;

  if (matrix == NULL)
    return NULL;

  if (n > matrix->NbRows)
  {
    fprintf(stderr,"[Scoplib] Error: not enough rows in the matrix\n");
    exit(1);
  }

  copy = openscop_matrix_malloc(n,matrix->NbColumns);

  for (i = 0; i < n; i++)
    for (j = 0; j < matrix->NbColumns; j++)
      SCOPINT_assign(copy->p[i][j],matrix->p[i][j]);

  return copy;
}


/**
 * openscop_matrix_copy function:
 * this function builds and returns a "hard copy" (not a pointer copy) of a
 * openscop_matrix_t data structure.
 * \param matrix The pointer to the matrix we want to copy.
 */
openscop_matrix_p
openscop_matrix_copy(openscop_matrix_p matrix)
{
  if (matrix == NULL)
    return NULL;

  return openscop_matrix_ncopy(matrix,matrix->NbRows);
}


/**
 * openscop_matrix_replace_vector function:
 * this function replaces the "row"^th row of a matrix "matrix" with the
 * vector "vector". It directly updates "matrix".
 * \param matrix The matrix we want to change a row.
 * \param vector The vector that will replace a row of the matrix.
 * \param row    The row of the matrix to be replaced.
 */
void
openscop_matrix_replace_vector(openscop_matrix_p matrix,
                               openscop_vector_p vector, int row)
{
  int i;

  if ((matrix == NULL) || (vector == NULL) ||
      (matrix->NbColumns != vector->Size) ||
      (row >= matrix->NbRows) || (row < 0))
  {
    fprintf(stderr,"[Scoplib] Error: vector cannot replace a matrix row\n");
    exit(1);
  }

  for (i = 0; i < vector->Size; i++)
    SCOPINT_assign(matrix->p[row][i],vector->p[i]);
}


/**
 * openscop_matrix_add_vector function:
 * this function adds the "row"^th row of a matrix "matrix" with the
 * vector "vector". It directly updates "matrix".
 * \param matrix The matrix we want to change a row.
 * \param vector The vector that will replace a row of the matrix.
 * \param row    The row of the matrix to be replaced.
 */
void
openscop_matrix_add_vector(openscop_matrix_p matrix, openscop_vector_p vector,
			  int row)
{
  int i;

  if ((matrix == NULL) || (vector == NULL) ||
      (matrix->NbColumns != vector->Size) ||
      (row >= matrix->NbRows) || (row < 0))
  {
    fprintf(stderr,"[Scoplib] Error: vector cannot replace a matrix row\n");
    exit(1);
  }

  if (SCOPINT_get_si(matrix->p[row][0]) == 0)
    SCOPINT_assign(matrix->p[row][0],vector->p[0]);
  for (i = 1; i < vector->Size; i++)
    SCOPINT_addto(matrix->p[row][i],matrix->p[row][i],vector->p[i]);
}


/**
 * openscop_matrix_sub_vector function:
 * this function substracts the vector "vector" to the "row"^th row of
 * a matrix "matrix. It directly updates "matrix".
 * \param matrix The matrix we want to change a row.
 * \param vector The vector that will replace a row of the matrix.
 * \param row    The row of the matrix to be replaced.
 */
void
openscop_matrix_sub_vector(openscop_matrix_p matrix, openscop_vector_p vector,
			  int row)
{
  int i;

  if ((matrix == NULL) || (vector == NULL) ||
      (matrix->NbColumns != vector->Size) ||
      (row >= matrix->NbRows) || (row < 0))
  {
    fprintf(stderr,"[Scoplib] Error: vector cannot replace a matrix row\n");
    exit(1);
  }

  if (SCOPINT_get_si(matrix->p[row][0]) == 0)
    SCOPINT_assign(matrix->p[row][0],vector->p[0]);
  for (i = 1; i < vector->Size; i++)
    SCOPINT_subtract(matrix->p[row][i],matrix->p[row][i],vector->p[i]);
}


/**
 * openscop_matrix_insert_vector function:
 * this function adds a new row corresponding to the vector "vector" to
 * the matrix "matrix" by inserting it at the "row"^th row. It directly
 * updates "matrix". If "vector" (or "matrix") is NULL, the matrix is left
 * unmodified.
 * \param matrix The matrix we want to extend.
 * \param vector The vector that will be added matrix.
 * \param row The row where to insert the vector.
 */
void
openscop_matrix_insert_vector(openscop_matrix_p matrix, openscop_vector_p vector,
			     int row)
{
  int i, j;
  openscop_matrix_p new;

  if ((vector == NULL) || (matrix == NULL))
    return;

  if ((matrix->NbColumns != vector->Size) ||
      (row > matrix->NbRows) || (row < 0))
  {
    fprintf(stderr,"[Scoplib] Error: vector cannot be inserted\n");
    exit(1);
  }

  /* We use a temporary matrix just to reuse existing functions. Cleaner. */
  new = openscop_matrix_malloc(matrix->NbRows+1,matrix->NbColumns);

  for (i = 0; i < row; i++)
    for (j = 0; j < matrix->NbColumns; j++)
      SCOPINT_assign(new->p[i][j],matrix->p[i][j]);

  openscop_matrix_replace_vector(new,vector,row);

  for (i = row+1; i < matrix->NbRows; i++)
    for (j = 0; j < matrix->NbColumns; j++)
      SCOPINT_assign(new->p[i][j],matrix->p[i-1][j]);

  openscop_matrix_free_inside(matrix);

  /* Replace the inside of matrix */
  matrix->NbRows = new->NbRows;
  matrix->NbColumns = new->NbColumns;
  matrix->p = new->p;
  matrix->p_Init = new->p_Init;
  /* Free the new "shell" */
  free(new);
}


/**
 * openscop_matrix_from_vector function:
 * this function converts a vector "vector" to a matrix with a single row
 * and returns a pointer to that matrix.
 * \param vector The vector to convert to a matrix.
 */
openscop_matrix_p
openscop_matrix_from_vector(openscop_vector_p vector)
{
  openscop_matrix_p matrix;

  if (vector == NULL)
    return NULL;

  matrix = openscop_matrix_malloc(1,vector->Size);
  openscop_matrix_replace_vector(matrix,vector,0);
  return matrix;
}


/**
 * openscop_matrix_replace_matrix function:
 * this function replaces some rows of a matrix "m1" with the rows of
 * the matrix "m2". It begins at the "row"^th row of "m1". It directly
 * updates "m1".
 * \param m1  The matrix we want to change some row1.
 * \param m2  The matrix containing the new rows.
 * \param row The first row of the matrix m1 to be replaced.
 */
void
openscop_matrix_replace_matrix(openscop_matrix_p m1, openscop_matrix_p m2, int row)
{
  int i, j;

  if ((m1 == NULL) || (m2 == NULL) ||
      (m1->NbColumns != m1->NbColumns) ||
      ((row + m2->NbRows) > m1->NbRows) || (row < 0))
  {
    fprintf(stderr,"[Scoplib] Error: vector cannot replace a matrix row\n");
    exit(1);
  }

  for (i = 0; i < m2->NbRows; i++)
    for (j = 0; j < m2->NbColumns; j++)
      SCOPINT_assign(m1->p[i+row][j],m2->p[i][j]);
}


/**
 * openscop_matrix_insert_matrix function:
 * this function adds new rows corresponding to the matrix "m1" to
 * the matrix "m2" by inserting it at the "row"^th row. It directly
 * updates "m1". If "m2" (or "m1") is NULL, the matrix is left
 * unmodified.
 * \param m1  The matrix we want to extend.
 * \param m2  The matrix to be inserted.
 * \param row The row where to insert the matrix
 */
void
openscop_matrix_insert_matrix(openscop_matrix_p m1, openscop_matrix_p m2, int row)
{
  int i, j;
  openscop_matrix_p new;

  if ((m1 == NULL) || (m2 == NULL))
    return;

  if ((m1->NbColumns != m2->NbColumns) ||
      (row > m1->NbRows) || (row < 0))
  {
    fprintf(stderr,"[Scoplib] Error: matrix cannot be inserted\n");
    exit(1);
  }

  /* We use a temporary matrix just to reuse existing functions. Cleaner. */
  new = openscop_matrix_malloc(m1->NbRows+m2->NbRows,m1->NbColumns);

  for (i = 0; i < row; i++)
    for (j = 0; j < m1->NbColumns; j++)
      SCOPINT_assign(new->p[i][j],m1->p[i][j]);

  openscop_matrix_replace_matrix(new,m2,row);

  for (i = row + m2->NbRows; i < m1->NbRows; i++)
    for (j = 0; j < m1->NbColumns; j++)
      SCOPINT_assign(new->p[i][j],m1->p[i-m2->NbRows][j]);

  openscop_matrix_free_inside(m1);

  /* Replace the inside of matrix */
  m1->NbRows = new->NbRows;
  m1->NbColumns = new->NbColumns;
  m1->p = new->p;
  m1->p_Init = new->p_Init;

  /* Free the new "container" */
  free(new);
}


/**
 * openscop_matrix_concat function:
 * this function builds a new matrix as the concatenation of the rows of
 * two other matrices sent as parameters.
 * \param m1  The first matrix.
 * \param m2  The second matrix.
 */
openscop_matrix_p
openscop_matrix_concat(openscop_matrix_p m1, openscop_matrix_p m2)
{
  openscop_matrix_p new;

  if (m1 == NULL)
    return openscop_matrix_copy(m2);

  if (m2 == NULL)
    return openscop_matrix_copy(m1);

  if (m1->NbColumns != m2->NbColumns)
  {
    fprintf(stderr,"[Scoplib] Error: matrices cannot be concatenated\n");
    exit(1);
  }

  new = openscop_matrix_malloc(m1->NbRows+m2->NbRows,m1->NbColumns);
  openscop_matrix_replace_matrix(new,m1,0);
  openscop_matrix_replace_matrix(new,m2,m1->NbRows);

  return new;
}


/**
 * openscop_matrix_equal function:
 * this function returns true if the two matrices are the same, false
 * otherwise.
 * \param m1  The first matrix.
 * \param m2  The second matrix.
 * \return 1 if m1 and m2 are the same (content-wise), 0 otherwise.
 */
int
openscop_matrix_equal(openscop_matrix_p m1, openscop_matrix_p m2)
{
  if (m1 == m2)
    return 1;
  if (m1 == NULL || m2 == NULL)
    return 0;
  if (m1->NbRows != m2->NbRows || m1->NbColumns != m2->NbColumns)
    return 0;
  int i, j;
  for (i = 0; i < m1->NbRows; ++i)
    for (j = 0; j < m1->NbColumns; ++j)
      if (SCOPINT_ne(m1->p[i][j], m2->p[i][j]))
	return 0;
  return 1;
}
