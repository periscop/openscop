
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                          statement.c                            **
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


# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <openscop/statement.h>


/*+****************************************************************************
 *                         Structure display functions                        *
 ******************************************************************************/


/**
 * openscop_statement_print_structure function:
 * Displays a openscop_statement_t structure (*statement) into a file (file,
 * possibly stdout) in a way that trends to be understandable without falling
 * in a deep depression or, for the lucky ones, getting a headache... It
 * includes an indentation level (level) in order to work with others
 * print_structure functions.
 * \param file      File where informations are printed.
 * \param statement The statement whose information have to be printed.
 * \param level     Number of spaces before printing, for each line.
 **
 * - 30/04/2008: first version.
 */
void
openscop_statement_print_structure(FILE * file, openscop_statement_p statement,
				  int level)
{
  int i, j, first = 1, number = 1;

  /* Go to the right level. */
  for (j = 0; j < level; j++)
    fprintf(file,"|\t");

  if (statement != NULL)
    fprintf(file,"+-- openscop_statement_t (S%d)\n",number);
  else
    fprintf(file,"+-- NULL statement\n");

  while (statement != NULL)
  { if (!first)
    {
      /* Go to the right level. */
      for (j = 0; j < level; j++)
        fprintf(file,"|\t");
      fprintf(file,"|   openscop_statement_t (S%d)\n",number);
    }
    else
      first = 0;

    /* A blank line. */
    for (j = 0; j <= level+1; j++)
      fprintf(file,"|\t");
    fprintf(file,"\n");

    /* Print the domain of the statement. */
    openscop_matrix_list_print_structure(file,statement->domain,level+1);

    /* Print the schedule of the statement. */
    openscop_matrix_print_structure(file,statement->schedule,level+1);

    /* Print the array read access informations of the statement. */
    openscop_matrix_print_structure(file,statement->read,level+1);

    /* Print the array write access informations of the statement. */
    openscop_matrix_print_structure(file,statement->write,level+1);

    /* Print the original iterator names. */
    for (i=0; i<=level; i++)
      fprintf(file,"|\t");
    if (statement->nb_iterators > 0)
    {
      fprintf(file,"+-- Original iterator strings:");
      for (i = 0; i < statement->nb_iterators; i++)
        fprintf(file," %s",statement->iterators[i]);
      fprintf(file,"\n");
    }
    else
      fprintf(file,"+-- No original iterator string\n");

    /* A blank line. */
    for (i = 0; i <= level+1; i++)
      fprintf(file,"|\t");
    fprintf(file,"\n");

    /* Print the original statement body. */
    for (i = 0; i <= level; i++)
      fprintf(file,"|\t");
    if (statement->body != NULL)
      fprintf(file,"+-- Original body: %s\n",statement->body);
    else
      fprintf(file,"+-- No original body\n");

    /* Print the control and exit predicates associated to the statement. */
    /** @FIXME: do it! */

    /* A blank line. */
    for (i = 0; i <= level+1; i++)
      fprintf(file,"|\t");
    fprintf(file,"\n");

    statement = statement->next;
    number++;

    /* Next line. */
    if (statement != NULL)
    {
      for (j = 0; j <= level; j++)
        fprintf(file,"|\t");
      fprintf(file,"V\n");
    }
  }

  /* The last line. */
  for (j = 0; j <= level; j++)
    fprintf(file,"|\t");
  fprintf(file,"\n");
}


/**
 * openscop_statement_print function:
 * This function prints the content of a openscop_statement_t structure
 * (*statement) into  a file (file, possibly stdout).
 * \param file      File where informations are printed.
 * \param statement The statement whose information have to be printed.
 **
 * - 30/04/2008: first version.
 */
void
openscop_statement_print(FILE * file, openscop_statement_p statement)
{
  openscop_statement_print_structure(file, statement, 0);
}


/**
 * openscop_statement_print_dot_scop function:
 * This function prints the content of a openscop_statement_t structure
 * (*statement) into a file (file, possibly stdout) for the .scop format.
 * \param file          File where informations are printed.
 * \param statement     The statement whose information have to be printed.
 * \param nb_parameters The number of parameters in the SCoP.
 * \param parameters    An array containing all parameters names.
 * \param nb_arrays     The number of arrays accessed in the SCoP.
 * \param arrays        An array containing all accessed array names.
 **
 * - 02/05/2008: first version.
 */
void
openscop_statement_print_dot_scop(FILE * file, openscop_statement_p statement,
				 int nb_parameters, char ** parameters,
				 int nb_arrays, char ** arrays)
{
  int i, number = 1;

  while (statement != NULL)
  {
    fprintf(file,"# =============================================== ");
    fprintf(file,"Statement %d\n",number);

    fprintf(file,"# ---------------------------------------------- ");
    fprintf(file,"%2d.1 Domain\n",number);
    fprintf(file,"# Iteration domain\n");
    openscop_matrix_list_print_dot_scop(file, statement->domain,
				       OPENSCOP_TYPE_DOMAIN,
				       statement->nb_iterators,
				       statement->iterators,
				       nb_parameters,parameters,
				       nb_arrays,arrays);
    fprintf(file,"\n");

    fprintf(file,"# ---------------------------------------------- ");
    fprintf(file,"%2d.2 Scattering\n",number);
    fprintf(file,"# Scattering function is provided\n");
    fprintf(file,"1\n");
    fprintf(file,"# Scattering function\n");
    openscop_matrix_print_dot_scop(file,statement->schedule,
				  OPENSCOP_TYPE_SCATTERING,
				  statement->nb_iterators,statement->iterators,
				  nb_parameters,parameters,
				  nb_arrays,arrays);
    fprintf(file,"\n");

    fprintf(file,"# ---------------------------------------------- ");
    fprintf(file,"%2d.3 Access\n",number);
    fprintf(file,"# Access informations are provided\n");
    fprintf(file,"1\n");
    fprintf(file,"# Read access informations\n");
    openscop_matrix_print_dot_scop(file,statement->read,OPENSCOP_TYPE_ACCESS,
				  statement->nb_iterators,statement->iterators,
				  nb_parameters,parameters,
				  nb_arrays,arrays);
    fprintf(file,"# Write access informations\n");
    openscop_matrix_print_dot_scop(file,statement->write,OPENSCOP_TYPE_ACCESS,
				  statement->nb_iterators,statement->iterators,
				  nb_parameters,parameters,
				  nb_arrays,arrays);
    fprintf(file,"\n");

    fprintf(file,"# ---------------------------------------------- ");
    fprintf(file,"%2d.4 Body\n",number);
    fprintf(file,"# Statement body is provided\n");
    fprintf(file,"1\n");
    if (statement->nb_iterators > 0)
    {
      fprintf(file,"# Original iterator names\n");
      for (i = 0; i < statement->nb_iterators; i++)
        fprintf(file,"%s ",statement->iterators[i]);
      fprintf(file,"\n");
    }
    else
      fprintf(file,"# No original iterator names\n");
    fprintf(file,"# Statement body\n");
    fprintf(file,"%s\n",statement->body);
    fprintf(file,"\n\n");

    statement = statement->next;
    number++;
  }
}



/******************************************************************************
 *                               Reading function                             *
 ******************************************************************************/

/**
 * Internal function. Read 'nb_strings' strings on the input 'file'.
 *
 * \FIXME should be placed somewhere else, it's duplicated in scop.c.
 */
static
char**
openscop_statement_read_strings(FILE* file, int nb_strings)
{
  char str[OPENSCOP_MAX_STRING];
  char tmp[OPENSCOP_MAX_STRING];
  char* s;
  char** res = NULL;
  int i;
  int count;

  /* Skip blank/commented lines. */
  while (fgets(str, OPENSCOP_MAX_STRING, file) == 0 || str[0] == '#' ||
	 isspace(str[0]))
    ;
  s = str;

  /* Allocate the array of string. Make it NULL-terminated. */
  res = (char**) malloc(sizeof(char*) * (nb_strings + 1));
  res[nb_strings] = NULL;

  /* Read the desired number of strings. */
  for (i = 0; i < nb_strings; ++i)
    {
      for (count = 0; *s && ! isspace(*s) && *s != '#'; ++count)
	tmp[count] = *(s++);
      tmp[count] = '\0';
      res[i] = strdup(tmp);
      if (*s != '#')
	++s;
    }

  return res;
}

/**
 * Internal function. Read an int on the input 'file'.
 *
 * \FIXME should be placed somewhere else, it's duplicated in scop.c.
 */
static
int
openscop_statement_read_int(FILE* file)
{
  char s[OPENSCOP_MAX_STRING];
  int res;

  /* Skip blank/commented lines. */
  while (fgets(s, OPENSCOP_MAX_STRING, file) == 0 || s[0] == '#' ||
	 isspace(s[0]))
    ;
  sscanf(s, "%d", &res);

  return res;
}

char**	    openscop_scop_generate_names(char*, int);

/**
 * openscop_statement_read function:
 * This function reads a openscop_statement_t structure from an input stream
 * (possibly stdin).
 * \param file		The input stream
 * \param nb_parameters	The number of global parameters for the program
 * \param arrays	The array containing names of arrays of the
 *			input program
 * \param nb_arr	The size of the array parameter
 */
openscop_statement_p
openscop_statement_read (FILE* file, int nb_parameters, char*** arrays,
			int* nb_arr)
{
  openscop_statement_p stmt = openscop_statement_malloc();
  char** tmp;

  if (file)
    {
      /* Read the domain matrices. */
      stmt->domain = openscop_matrix_list_read(file);

      /* Read the scattering, if any. */
      if (openscop_statement_read_int(file) > 0)
	stmt->schedule = openscop_matrix_read(file);

      /* Read the access functions, if any. */
      if (openscop_statement_read_int(file) > 0)
	{
	  stmt->read = openscop_matrix_read_arrays(file, arrays, nb_arr);
	  stmt->write = openscop_matrix_read_arrays(file, arrays, nb_arr);
	}

      stmt->nb_iterators = stmt->domain->elt->NbColumns - 2 - nb_parameters;
      /* Read the body information, if any. */
      if (openscop_statement_read_int(file) > 0)
	{
	  if (stmt->nb_iterators > 0)
	    stmt->iterators = openscop_statement_read_strings(file,
							  stmt->nb_iterators);
	  tmp = openscop_statement_read_strings(file, 1);
	  stmt->body = tmp[0];
	  free(tmp);
	}
      else
	{
	  stmt->iterators = openscop_scop_generate_names("i",
							stmt->nb_iterators);
	  stmt->body = strdup("[undefined]");
	}
    }

  return stmt;
}


/*+****************************************************************************
 *                   Memory allocation/deallocation functions                 *
 ******************************************************************************/


/**
 * openscop_statement_malloc function:
 * This function allocates the memory space for a openscop_statement_t structure
 * and sets its fields with default values. Then it returns a pointer to the
 * allocated space.
 **
 * - 30/04/2008: first version.
 */
openscop_statement_p
openscop_statement_malloc()
{
  openscop_statement_p statement;

  statement = (openscop_statement_p)malloc(sizeof(openscop_statement_t));
  if (statement == NULL)
  {
    fprintf(stderr, "[Scoplib] Memory Overflow.\n");
    exit(1);
  }

  statement->domain    = NULL;
  statement->schedule  = NULL;
  statement->read      = NULL;
  statement->write     = NULL;
  statement->nb_iterators = 0;
  statement->iterators = NULL;
  statement->body      = NULL;
  statement->next      = NULL;


  /* Non-static code support specifics. */
  statement->exit_predicates		= NULL;
  statement->nb_exit_predicates		= 0;
  statement->control_predicates		= NULL;
  statement->nb_control_predicates	= 0;

  return statement;
}


/**
 * openscop_statement_free function:
 * This function frees the allocated memory for a openscop_statement_t structure.
 * \param statement The pointer to the statement we want to free.
 **
 * - 30/04/2008: first version.
 */
void
openscop_statement_free(openscop_statement_p statement)
{
  int i;
  openscop_statement_p next;

  while (statement != NULL)
  {
    next = statement->next;
    openscop_matrix_list_free(statement->domain);
    openscop_matrix_free(statement->schedule);
    openscop_matrix_free(statement->read);
    openscop_matrix_free(statement->write);
    if (statement->iterators != NULL)
    {
      for (i = 0; i < statement->nb_iterators; i++)
        free(statement->iterators[i]);
      free(statement->iterators);
    }
    if (statement->body != NULL)
      free(statement->body);

    /* Non-static code support specifics. */
    if (statement->exit_predicates != NULL)
      free(statement->exit_predicates);
    if (statement->control_predicates != NULL)
      free(statement->control_predicates);

    free(statement);
    statement = next;
  }
}


/*+****************************************************************************
 *                            Processing functions                            *
 ******************************************************************************/


/**
 * openscop_statement_add function:
 * This function adds a statement "statement" at the end of the statement
 * list pointed by "location".
 * \param location  Address of the first element of the statement list.
 * \param statement The statement to add to the list.
 **
 * - 30/04/2008: first version.
 */
void
openscop_statement_add(openscop_statement_p * location,
		      openscop_statement_p statement)
{
  while (*location != NULL)
    location = &((*location)->next);

  *location = statement;
}



/**
 * openscop_statement_number function:
 * This function returns the number of statements in the statement list
 * provided as parameter.
 * \param statement The first element of the statement list.
 **
 * - 03/05/2008: first version.
 */
int
openscop_statement_number(openscop_statement_p statement)
{
  int number = 0;

  while (statement != NULL)
  {
    number++;
    statement = statement->next;
  }
  return number;
}
