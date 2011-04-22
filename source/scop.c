
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                            scop.c                               **
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
# include <string.h>
# include <openscop/scop.h>


/*+***************************************************************************
 *                         Structure display functions                       *
 *****************************************************************************/


/**
 * openscop_scop_print_structure function:
 * Displays a openscop_scop_t structure (*scop) into a file (file, possibly
 * stdout) in a way that trends to be understandable without falling in a deep
 * depression or, for the lucky ones, getting a headache... It includes an
 * indentation level (level) in order to work with others print_structure
 * functions.
 * \param file   File where informations are printed.
 * \param scop   The scop whose information have to be printed.
 * \param level  Number of spaces before printing, for each line.
 */
void
openscop_scop_print_structure(FILE * file, openscop_scop_p scop, int level)
{
  int i, j;

  if (scop != NULL)
  {
    // Go to the right level.
    for (j = 0; j < level; j++)
      fprintf(file, "|\t");
    fprintf(file, "+-- openscop_scop_t\n");

    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    // Print the language.
    for (j = 0; j < level; j++)
      fprintf(file, "|\t");
    fprintf(file, "|\tLanguage: %s\n", scop->language);

    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    // Print the context of the scop.
    openscop_relation_print_structure(file, scop->context, level+1);

    // Print the original parameter names.
    for (i = 0; i <= level; i++)
      fprintf(file, "|\t");
    if (scop->nb_parameters > 0)
    {
      fprintf(file, "+-- Parameter strings:");
      for (i = 0; i < scop->nb_parameters; i++)
        fprintf(file, " %s", scop->parameters[i]);
      fprintf(file, "\n");
    }
    else
      fprintf(file, "+-- No parameter strings\n");

    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    // Print the iterator names.
    for (i = 0; i <= level; i++)
      fprintf(file, "|\t");
    if (scop->nb_iterators > 0)
    {
      fprintf(file, "+-- Iterator strings:");
      for (i = 0; i < scop->nb_iterators; i++)
        fprintf(file, " %s", scop->iterators[i]);
      fprintf(file, "\n");
    }
    else
      fprintf(file,"+-- No iterator string\n");

    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    // Print the scattering dimension names.
    for (i = 0; i <= level; i++)
      fprintf(file, "|\t");
    if (scop->nb_scattdims > 0)
    {
      fprintf(file, "+-- Scattering dimension strings:");
      for (i = 0; i < scop->nb_scattdims; i++)
        fprintf(file, " %s", scop->scattdims[i]);
      fprintf(file, "\n");
    }
    else
      fprintf(file, "+-- No scattering dimension string\n");

    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    // Print the statements.
    openscop_statement_print_structure(file, scop->statement, level+1);

    // Print the extensions.
    openscop_extension_print_structure(file, scop->extension, level+1);

    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");
  }
  else
  {
    // Go to the right level.
    for (j = 0; j < level; j++)
      fprintf(file, "|\t");
    fprintf(file, "+-- NULL scop\n");
  }

  // The last line.
  for (j = 0; j <= level; j++)
    fprintf(file, "|\t");
  fprintf(file, "\n");
}


/**
 * openscop_scop_print function:
 * This function prints the content of a openscop_scop_t structure (*scop) into
 * a file (file, possibly stdout).
 * \param file   File where informations are printed.
 * \param scop   The scop whose information have to be printed.
 */
void
openscop_scop_print(FILE * file, openscop_scop_p scop)
{
  openscop_scop_print_structure(file, scop, 0);
}


/**
 * openscop_scop_print_openscop function:
 * This function prints the content of a openscop_scop_t structure (*scop)
 * into a file (file, possibly stdout) in the OpenScop format.
 * \param file    File where informations are printed.
 * \param scop    The scop whose information have to be printed.
 */
void
openscop_scop_print_openscop(FILE * file, openscop_scop_p scop)
{
  int i;
  int nb_arrays = 0;
  char ** arrays = NULL;
  openscop_arrays_p array_ids;
  
  // Extract array names information.
  array_ids = (openscop_arrays_p)openscop_extension_lookup(scop->extension,
                                     OPENSCOP_EXTENSION_ARRAYS);
  arrays = openscop_arrays_generate_names(array_ids, &nb_arrays);

  if (0)
  {
    fprintf(file, "#                                                     \n");
    fprintf(file, "#          <|                                         \n");
    fprintf(file, "#           A                                         \n");
    fprintf(file, "#          /.\\                                       \n");
    fprintf(file, "#     <|  [\"\"M#                                     \n");
    fprintf(file, "#      A   | #            Clan McCloog Castle         \n");
    fprintf(file, "#     /.\\ [\"\"M#           [Generated by the OpenScop ");
    fprintf(file, "Library %s %s bits]\n",OPENSCOP_RELEASE, OPENSCOP_VERSION);
    fprintf(file, "#    [\"\"M# | #  U\"U#U                              \n");
    fprintf(file, "#     | #  | #  \\ .:/                                \n");
    fprintf(file, "#     | #  | #___| #                                  \n");
    fprintf(file, "#     | \"--'     .-\"                                \n");
    fprintf(file, "#   |\"-\"-\"-\"-\"-#-#-##                            \n");
    fprintf(file, "#   |     # ## ######                                 \n");
    fprintf(file, "#    \\       .::::'/                                 \n");
    fprintf(file, "#     \\      ::::'/                                  \n");
    fprintf(file, "#   :8a|    # # ##                                    \n");
    fprintf(file, "#   ::88a      ###                                    \n");
    fprintf(file, "#  ::::888a  8a ##::.                                 \n");
    fprintf(file, "#  ::::::888a88a[]::::                                \n");
    fprintf(file, "# :::::::::SUNDOGa8a::::. ..                          \n");
    fprintf(file, "# :::::8::::888:Y8888:::::::::...                     \n");
    fprintf(file, "#::':::88::::888::Y88a______________________________");
    fprintf(file, "________________________\n");
    fprintf(file, "#:: ::::88a::::88a:Y88a                             ");
    fprintf(file, "     __---__-- __\n");
    fprintf(file, "#' .: ::Y88a:::::8a:Y88a                            ");
    fprintf(file, "__----_-- -------_-__\n");
    fprintf(file, "#  :' ::::8P::::::::::88aa.                   _ _- -");
    fprintf(file, "-  --_ --- __  --- __--\n");
    fprintf(file, "#.::  :::::::::::::::::::Y88as88a...s88aa.\n");
  }
  else
  {
    fprintf(file, "# [File generated by the OpenScop Library %s %s bits]\n",
            OPENSCOP_RELEASE,OPENSCOP_VERSION);
  }

  fprintf(file, "\nOpenScop\n\n");
  fprintf(file, "# =============================================== Global\n");
  fprintf(file, "# Language\n");
  fprintf(file, "%s\n\n", scop->language);

  fprintf(file, "# Context\n");
  openscop_relation_print_openscop(file, scop->context, OPENSCOP_TYPE_DOMAIN,
				0, NULL,
				scop->nb_parameters, scop->parameters,
				nb_arrays, arrays);
  fprintf(file, "\n");

  if (scop->nb_parameters > 0)
  {
    fprintf(file, "# Parameter names are provided\n");
    fprintf(file, "1\n");
    fprintf(file, "# Parameter names\n");
    for (i = 0; i < scop->nb_parameters; i++)
      fprintf(file, "%s ", scop->parameters[i]);
    fprintf(file, "\n\n");
  }
  else
  {
    fprintf(file, "# Parameter names are not provided\n");
    fprintf(file, "0\n\n");
  }

  if (scop->nb_iterators > 0)
  {
    fprintf(file, "# Iterator names are provided\n");
    fprintf(file, "1\n");
    fprintf(file, "# Iterator names\n");
    for (i = 0; i < scop->nb_iterators; i++)
      fprintf(file, "%s ", scop->iterators[i]);
    fprintf(file, "\n\n");
  }
  else
  {
    fprintf(file, "# Iterator names are not provided\n");
    fprintf(file, "0\n\n");
  }

  if (scop->nb_scattdims > 0)
  {
    fprintf(file, "# Scattering dimension names are provided\n");
    fprintf(file, "1\n");
    fprintf(file, "# Scattering dimension names\n");
    for (i = 0; i < scop->nb_scattdims; i++)
      fprintf(file, "%s ", scop->scattdims[i]);
    fprintf(file, "\n\n");
  }
  else
  {
    fprintf(file, "# Scattering dimension names are not provided\n");
    fprintf(file, "0\n\n");
  }

  fprintf(file, "# Number of statements\n");
  fprintf(file, "%d\n\n",openscop_statement_number(scop->statement));

  openscop_statement_print_openscop(file, scop->statement,
				    scop->nb_parameters, scop->parameters,
				    nb_arrays, arrays);
  if (scop->extension)
  {
    fprintf(file, "# ==============================================="
                  " Extensions\n");
    openscop_extension_print_openscop(file, scop->extension);
  }

  // Free array names
  if (nb_arrays != 0)
  {
    for (i = 0; i < nb_arrays; i++)
      free(arrays[i]);
    free(arrays);
  }
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


static
void
openscop_scop_update_val(int * variable, int value)
{
  if ((*variable == OPENSCOP_UNDEFINED) || (*variable == value))
    *variable = value;
  else
    fprintf(stderr, "[OpenScop] Warning: number of iterators and "
                    "parameters inconsistency.\n");
}

static
void
openscop_scop_update_properties(openscop_relation_p relation,
                                int nb_output_dims, int nb_input_dims,
                                int nb_parameters)
{
  if (relation != NULL)
  {
    openscop_scop_update_val(&(relation->nb_output_dims), nb_output_dims);
    openscop_scop_update_val(&(relation->nb_input_dims),  nb_input_dims);
    openscop_scop_update_val(&(relation->nb_parameters),  nb_parameters);   
  }
}


/**
 * openscop_scop_propagate_properties internal function:
 * This function tries to propagate information in all relations through the
 * whole openscop representation. For instance, the number of parameters can
 * be found in the context as well as in any relation: if it is undefined in
 * the relation, this function defines it, if it is different than the
 * expected value, it reports an error. This function does the same for
 * the number of output and input dimensions.
 * \param scop  The SCoP we want to propagate properties.
 */
static
void
openscop_scop_propagate_properties(openscop_scop_p scop)
{
  int i, nb_parameters;
  openscop_statement_p     statement;
  openscop_relation_p      relation;
  openscop_relation_list_p list;

  // Context part: get the number of parameters.
  if ((scop->context != NULL) &&
      (openscop_relation_is_matrix(scop->context)))
  {
    nb_parameters = scop->context->nb_columns - 2;
    openscop_scop_update_properties(scop->context, 0, 0, nb_parameters);
  }
  else
    return;

  // For each statement:
  statement = scop->statement;
  while (statement != NULL)
  {
    // - Domain part,
    relation = statement->domain;
    if (openscop_relation_is_matrix(relation))
    {
      while (relation != NULL)
      {
        openscop_scop_update_properties(relation,
                   relation->nb_columns - nb_parameters - 2, 0, nb_parameters);
        relation = relation->next;
      }
    }

    // - Scattering part,
    relation = statement->scattering;
    if (openscop_relation_is_matrix(relation))
    {
      while (relation != NULL)
      {
        openscop_scop_update_properties(relation,
                   0, relation->nb_columns - nb_parameters - 2, nb_parameters);
        relation = relation->next;
      }
    }

    // - Access part.
    for (i = 0; i < 2; i++)
    {
      if (i == 0)
        list = statement->read;
      else
        list = statement->write;

      while (list != NULL)
      {
        relation = list->elt;
        if (openscop_relation_is_matrix(relation))
        {
          while (relation != NULL)
          {
            openscop_scop_update_properties(relation,
                   0, relation->nb_columns - nb_parameters - 2, nb_parameters);
            relation = relation->next;
          }
        }

        list = list->next;
      }
    }
    
    statement = statement->next;
  }
}


/**
 * openscop_scop_read function:
 * This function reads a openscop_scop_t structure from an input stream
 * (possibly stdin) corresponding to an OpenScop input file. If some relation
 * properties (number of input/output/local dimensions and number of
 * parameters) are undefined, it will define them according to the available
 * information. 
 * \param file  The input stream
 */
openscop_scop_p
openscop_scop_read(FILE * file)
{
  openscop_scop_p scop      = NULL;
  openscop_statement_p stmt = NULL;
  openscop_statement_p prev = NULL;
  int nb_statements;
  int max;
  char ** tmp;
  int i;

  if (file == NULL)
    return NULL;

  scop = openscop_scop_malloc();

  // Backup the arrays of the program. Buffer is reajustable.
  /*int nb_arr = OPENSCOP_MAX_STRING;
  char ** arrays = (char **) malloc (sizeof(char *) * nb_arr);
  for (i = 0; i < nb_arr; ++i)
    arrays[i] = NULL;
  */

  //
  // I. CONTEXT PART
  //

  // Ensure the file is a .scop.
  tmp = openscop_util_read_strings(file, 1, &max);
  if ((max == 0) || (strcmp(*tmp, "OpenScop")))
  {
    fprintf(stderr, "[OpenScop] Error: not an OpenScop file "
                    "(type \"%s\".\n", *tmp);
    exit (1);
  }
  if (max > 1)
    fprintf(stderr, "[OpenScop] Warning: uninterpreted information "
                    "(after file type).\n");
  free(*tmp);
  free(tmp);

  // Read the language.
  char ** language =  openscop_util_read_strings(file, 1, &max);
  if (max == 0)
  {
    fprintf(stderr, "[OpenScop] Error: no language (backend) specified.\n");
    exit (1);
  }
  if (max > 1)
    fprintf(stderr, "[OpenScop] Warning: uninterpreted information "
                    "(after language).\n");
  scop->language = *language;
  free(language);

  // Read the context.
  scop->context  = openscop_relation_read(file);
  scop->nb_parameters = scop->context->nb_columns - 2;

  // Read the parameter names, if any.
  if (openscop_util_read_int(file, NULL) > 0)
  {
    scop->parameters = openscop_util_read_strings(file,
                                                  scop->nb_parameters, &max);
    if (max < scop->nb_parameters)
    {
      fprintf(stderr, "[OpenScop] Error: not enough parameter names.\n");
      exit (1);
    }
    if (max > scop->nb_parameters)
      fprintf(stderr, "[OpenScop] Warning: uninterpreted information "
                      "(after parameter names).\n");
  }
  else
    scop->parameters = NULL;

  // Read the iterator names, if any.
  if (openscop_util_read_int(file, NULL) > 0)
    scop->iterators = openscop_util_read_strings(file, -1,
                                                 &(scop->nb_iterators));
  else
  {
    scop->nb_iterators = 0;
    scop->iterators = NULL;
  }

  // Read the scattering dimension names, if any.
  if (openscop_util_read_int(file, NULL) > 0)
    scop->scattdims = openscop_util_read_strings(file, -1,
                                                 &(scop->nb_scattdims));
  else
  {
    scop->nb_scattdims = 0;
    scop->scattdims = NULL;
  }

  //
  // II. STATEMENT PART
  //

  // Read the number of statements.
  nb_statements = openscop_util_read_int(file, NULL);

  for (i = 0; i < nb_statements; ++i)
  {
    // Read each statement.
    stmt = openscop_statement_read(file);
    if (scop->statement == NULL)
      scop->statement = stmt;
    else
      prev->next = stmt;
    prev = stmt;
  }

  //
  // III. OPTION PART
  //

  // Read the remainder of the file, and store it in the extension field.
  scop->extension = openscop_extension_read(file);
  
  //
  // VI. FINALIZE AND CHECK
  //
  openscop_scop_propagate_properties(scop);

  if (!openscop_scop_integrity_check(scop))
    fprintf(stderr, "[OpenScop] Warning: global integrity check failed.\n");

  return scop;
}


/*+***************************************************************************
 *                   Memory allocation/deallocation functions                *
 *****************************************************************************/


/**
 * openscop_scop_malloc function:
 * This function allocates the memory space for a openscop_scop_t structure and
 * sets its fields with default values. Then it returns a pointer to the
 * allocated space.
 * \return A pointer to an empty scop with fields set to default values.
 */
openscop_scop_p
openscop_scop_malloc()
{
  openscop_scop_p scop;

  scop = (openscop_scop_p)malloc(sizeof(openscop_scop_t));
  if (scop == NULL)
  {
    fprintf(stderr, "[OpenScop] Memory Overflow.\n");
    exit(1);
  }

  scop->version            = 1;
  scop->textual_names      = 1;
  scop->language           = NULL;
  scop->context            = NULL;
  scop->nb_parameters      = 0;
  scop->nb_iterators       = 0;
  scop->nb_scattdims       = 0;
  scop->parameters         = NULL;
  scop->iterators          = NULL;
  scop->scattdims          = NULL;
  scop->statement          = NULL;
  scop->extension          = NULL;
  scop->usr	           = NULL;

  return scop;
}


/**
 * openscop_scop_free function:
 * This function frees the allocated memory for a openscop_scop_t structure.
 * \param scop The pointer to the scop we want to free.
 */
void
openscop_scop_free(openscop_scop_p scop)
{
 int i;

  if (scop != NULL)
  {
    if (scop->language != NULL)
      free(scop->language);
    
    openscop_relation_free(scop->context);
    
    if (scop->parameters != NULL)
    {
      for (i = 0; i < scop->nb_parameters; i++)
        free(scop->parameters[i]);
      free(scop->parameters);
    }
    
    if (scop->iterators != NULL)
    {
      for (i = 0; i < scop->nb_iterators; i++)
        free(scop->iterators[i]);
      free(scop->iterators);
    }
    
    if (scop->scattdims != NULL)
    {
      for (i = 0; i < scop->nb_scattdims; i++)
        free(scop->scattdims[i]);
      free(scop->scattdims);
    }
    
    openscop_statement_free(scop->statement);
    openscop_extension_free(scop->extension);

    free(scop);
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_scop_copy function:
 * This functions builds and returns a "hard copy" (not a pointer copy)
 * of a openscop_statement_t data structure provided as parameter.
 * Note that the usr field is not touched by this function.
 * \param statement  The pointer to the scop we want to copy.
 * \return A pointer to the full copy of the scop provided as parameter.
 */
openscop_scop_p
openscop_scop_copy(openscop_scop_p scop)
{
  openscop_scop_p copy;
  
  copy                     = openscop_scop_malloc();
  copy->textual_names      = scop->textual_names;
  copy->version            = scop->version;
  copy->language           = strdup(scop->language);
  copy->context            = openscop_relation_copy(scop->context);
  copy->nb_parameters      = scop->nb_parameters;
  copy->nb_iterators       = scop->nb_iterators;
  copy->nb_scattdims       = scop->nb_scattdims;
  copy->parameters         = openscop_util_copy_strings(scop->parameters,
                                                        scop->nb_parameters);
  copy->iterators          = openscop_util_copy_strings(scop->iterators,
                                                        scop->nb_iterators);
  copy->scattdims          = openscop_util_copy_strings(scop->scattdims,
                                                        scop->nb_scattdims);
  copy->statement          = openscop_statement_copy(scop->statement);
  copy->extension          = openscop_extension_copy(scop->extension);

  return copy;
}


/**
 * openscop_scop_equal function:
 * this function returns true if the two scops are the same, false
 * otherwise (the usr field is not tested).
 * \param s1 The first scop.
 * \param s2 The second scop.
 * \return 1 if s1 and s2 are the same (content-wise), 0 otherwise.
 */
int
openscop_scop_equal(openscop_scop_p s1, openscop_scop_p s2)
{
  int i;

  if (s1->version != s2->version)
  {
    fprintf(stderr, "[OpenScop] info: versions are not the same.\n"); 
    //return 0;
  }
  
  if (strcmp(s1->language, s2->language) != 0)
  {
    fprintf(stderr, "[OpenScop] info: languages are not the same.\n"); 
    return 0;
  }

  if (!openscop_relation_equal(s1->context, s2->context))
  {
    fprintf(stderr, "[OpenScop] info: contexts are not the same.\n"); 
    return 0;
  }
  
  if (s1->nb_parameters != s2->nb_parameters)
  {
    fprintf(stderr, "[OpenScop] info: #parameters are not the same.\n"); 
    return 0;
  }
  
  if (s1->nb_iterators != s2->nb_iterators)
  {
    fprintf(stderr, "[OpenScop] info: #iterators are not the same.\n"); 
    return 0;
  }
  
  if (s1->nb_scattdims != s2->nb_scattdims)
  {
    fprintf(stderr, "[OpenScop] info: #scattdims are not the same.\n");
    return 0;
  }

  if (!openscop_statement_equal(s1->statement, s2->statement))
  {
    fprintf(stderr, "[OpenScop] info: statements are not the same.\n"); 
    return 0;
  }
  
  if (!openscop_extension_equal(s1->extension, s2->extension))
  {
    fprintf(stderr, "[OpenScop] info: extensions are not the same.\n"); 
    return 0;
  }

  for (i = 0; i < s1->nb_parameters; i++)
    if (strcmp(s1->parameters[i], s2->parameters[i]) != 0)
    {
      fprintf(stderr, "[OpenScop] info: parameter names are not the same.\n");
      return 0;
    }
  
  for (i = 0; i < s1->nb_iterators; i++)
    if (strcmp(s1->iterators[i], s2->iterators[i]) != 0)
    {
      fprintf(stderr, "[OpenScop] info: iterator names are not the same.\n");
      return 0;
    }

  for (i = 0; i < s1->nb_scattdims; i++)
    if (strcmp(s1->scattdims[i], s2->scattdims[i]) != 0)
    {
      fprintf(stderr, "[OpenScop] info: scattdims names are not the same.\n");
      return 0;
    }

  return 1;
}


/**
 * openscop_scop_integrity_check function:
 * This function checks that a scop is "well formed". It returns 0 if the
 * check failed or 1 if no problem has been detected.
 * \param scop  The scop we want to check.
 * \return 0 if the integrity check fails, 1 otherwise.
 */
int
openscop_scop_integrity_check(openscop_scop_p scop)
{
  int expected_nb_parameters;
  int nb_iterators, max_nb_iterators = 0;
  int max_nb_scattdims = 0;
  openscop_statement_p statement;

  // Check the language.
  if ((scop->language != NULL) &&
      (!strcmp(scop->language, "caml")  || !strcmp(scop->language, "Caml") ||
       !strcmp(scop->language, "ocaml") || !strcmp(scop->language, "OCaml")))
    fprintf(stderr, "[OpenScop] Alert: Caml ?! Are you sure ?! ;)\n");
  
  // Check the context.
  if (!openscop_relation_integrity_check(scop->context,
                                         OPENSCOP_TYPE_CONTEXT,
                                         0, 0, OPENSCOP_UNDEFINED))
    return 0;

  // Get the number of parameters.
  if (scop->context != NULL)
  { 
    if (openscop_relation_is_matrix(scop->context))
      expected_nb_parameters = scop->context->nb_columns - 2;
    else
      expected_nb_parameters = scop->context->nb_parameters;
  }
  else
    expected_nb_parameters = OPENSCOP_UNDEFINED;

  if (!openscop_statement_integrity_check(scop->statement,
                                          expected_nb_parameters))
    return 0;

  // Ensure we have enough names.
  if (expected_nb_parameters == OPENSCOP_UNDEFINED)
    expected_nb_parameters = 0;

  statement = scop->statement;
  while (statement != NULL)
  {
    if (statement->domain != NULL)
    {
      if (openscop_relation_is_matrix(statement->domain))
      {
        nb_iterators = statement->domain->nb_columns -
                       expected_nb_parameters - 2;
        if (nb_iterators > max_nb_iterators)
          max_nb_iterators = nb_iterators;
      }
      else
      {
        if (statement->domain->nb_output_dims > max_nb_iterators)
          max_nb_iterators = statement->domain->nb_output_dims;
      }
    }

    if (statement->scattering != NULL)
    {
      if (openscop_relation_is_matrix(statement->scattering))
      {
        if (statement->domain->nb_rows > max_nb_scattdims)
          max_nb_scattdims = statement->scattering->nb_rows;
      }
      else
      {
        if (statement->scattering->nb_input_dims > max_nb_scattdims)
          max_nb_scattdims = statement->scattering->nb_input_dims;
      }
    }

    statement = statement->next;
  }
  
  if ((scop->nb_iterators > 0) &&
      (scop->nb_iterators < max_nb_iterators))
  {
    fprintf(stderr, "[OpenScop] Warning: not enough iterator names.\n");
    return 0;
  }
  
  if ((scop->nb_scattdims > 0) &&
      (scop->nb_scattdims < max_nb_scattdims))
  {
    fprintf(stderr, "[OpenScop] Warning: not enough scattering "
                    "dimension names.\n");
    return 0;
  }

  return 1;
}
