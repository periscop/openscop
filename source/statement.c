
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
# include <openscop/statement.h>


/*+***************************************************************************
 *                         Structure display functions                       *
 *****************************************************************************/


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
 */
void
openscop_statement_print_structure(FILE * file, openscop_statement_p statement,
                                   int level)
{
  int i, j, first = 1, number = 1;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (statement != NULL)
    fprintf(file, "+-- openscop_statement_t (S%d)\n", number);
  else
    fprintf(file, "+-- NULL statement\n");

  while (statement != NULL)
  { if (!first)
    {
      // Go to the right level.
      for (j = 0; j < level; j++)
        fprintf(file, "|\t");
      fprintf(file, "|   openscop_statement_t (S%d)\n", number);
    }
    else
      first = 0;

    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    // Print the domain of the statement.
    openscop_relation_print_structure(file, statement->domain, level+1);

    // Print the scattering of the statement.
    openscop_relation_print_structure(file, statement->scattering, level+1);

    // Print the array read access informations of the statement.
    openscop_relation_list_print_structure(file, statement->read, level+1);

    // Print the array write access informations of the statement.
    openscop_relation_list_print_structure(file, statement->write, level+1);

    // Print the original iterator names.
    for (i = 0; i <= level; i++)
      fprintf(file, "|\t");
    if (statement->nb_iterators > 0)
    {
      fprintf(file, "+-- Original iterator strings:");
      for (i = 0; i < statement->nb_iterators; i++)
        fprintf(file, " %s", statement->iterators[i]);
      fprintf(file, "\n");
    }
    else
      fprintf(file, "+-- No original iterator string\n");

    // A blank line.
    for (i = 0; i <= level+1; i++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    // Print the original statement body.
    for (i = 0; i <= level; i++)
      fprintf(file, "|\t");
    if (statement->body != NULL)
      fprintf(file, "+-- Original body: %s\n", statement->body);
    else
      fprintf(file, "+-- No original body\n");

    // A blank line.
    for (i = 0; i <= level+1; i++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    statement = statement->next;
    number++;

    // Next line.
    if (statement != NULL)
    {
      for (j = 0; j <= level; j++)
        fprintf(file, "|\t");
      fprintf(file, "V\n");
    }
  }

  // The last line.
  for (j = 0; j <= level; j++)
    fprintf(file, "|\t");
  fprintf(file, "\n");
}


/**
 * openscop_statement_print function:
 * This function prints the content of a openscop_statement_t structure
 * (*statement) into  a file (file, possibly stdout).
 * \param file      File where informations are printed.
 * \param statement The statement whose information have to be printed.
 */
void
openscop_statement_print(FILE * file, openscop_statement_p statement)
{
  openscop_statement_print_structure(file, statement, 0);
}


/**
 * openscop_statement_print_openscop function:
 * This function prints the content of a openscop_statement_t structure
 * (*statement) into a file (file, possibly stdout) in the OpenScop format.
 * \param file      File where informations are printed.
 * \param statement The statement whose information have to be printed.
 * \param names     The textual names of the various elements. Is is important
 *                  that names->nb_parameters is exact if the matrix
 *                  representation is used. Set to NULL if printing comments
 *                  is not needed.
 */
void
openscop_statement_print_openscop(FILE * file, openscop_statement_p statement,
                                  openscop_names_p names)                      
{
  int i, switched, number = 1;
  int tmp_nb_iterators = 0;
  char ** tmp_iterators = NULL;

  while (statement != NULL)
  {
    // Switch iterator names to the current statement names if possible.
    switched = 0;
    if (statement->nb_iterators > 0)
    {
      tmp_nb_iterators = names->nb_iterators;
      tmp_iterators = names->iterators;
      names->nb_iterators = statement->nb_iterators;
      names->iterators = statement->iterators;
      switched = 1;
    }

    fprintf(file, "# =============================================== ");
    fprintf(file, "Statement %d\n", number);

    fprintf(file, "# ---------------------------------------------- ");
    fprintf(file, "%2d.1 Domain\n", number);
    fprintf(file, "# Iteration domain\n");
    openscop_relation_print_openscop(file, statement->domain,
                                     OPENSCOP_TYPE_DOMAIN, names);
    fprintf(file, "\n");

    fprintf(file, "# ---------------------------------------------- ");
    fprintf(file, "%2d.2 Scattering\n", number);
    fprintf(file, "# Scattering function is provided\n");
    fprintf(file, "1\n");
    fprintf(file, "# Scattering function\n");
    openscop_relation_print_openscop(file, statement->scattering,
                                     OPENSCOP_TYPE_SCATTERING, names);
    fprintf(file, "\n");

    fprintf(file, "# ---------------------------------------------- ");
    fprintf(file, "%2d.3 Access\n", number);
    fprintf(file, "# Access informations are provided\n");
    fprintf(file, "1\n");
    fprintf(file, "\n# Read access information\n");
    openscop_relation_list_print_openscop(file, statement->read,
                                          OPENSCOP_TYPE_ACCESS, names);
    fprintf(file, "\n# Write access information\n");
    openscop_relation_list_print_openscop(file, statement->write,
                                          OPENSCOP_TYPE_ACCESS, names);
    fprintf(file, "\n");

    fprintf(file, "# ---------------------------------------------- ");
    fprintf(file, "%2d.4 Body\n", number);
    fprintf(file, "# Statement body is provided\n");
    fprintf(file, "1\n");
    if (statement->nb_iterators > 0)
    {
      fprintf(file, "# Original iterator names\n");
      for (i = 0; i < statement->nb_iterators; i++)
        fprintf(file, "%s ", statement->iterators[i]);
      fprintf(file, "\n");
    }
    else
      fprintf(file, "# No original iterator names\n");
    fprintf(file, "# Statement body\n");
    fprintf(file, "%s\n", statement->body);
    fprintf(file, "\n\n");

    if (switched == 1)
    {
      statement->nb_iterators = tmp_nb_iterators;
      statement->iterators = tmp_iterators;
    }
    statement = statement->next;
    number++;
  }
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/**
 * openscop_statement_read function:
 * This function reads a openscop_statement_t structure from an input stream
 * (possibly stdin).
 * \param file  The input stream.
 * \return A pointer to the statement structure that has been read.
 */
openscop_statement_p
openscop_statement_read(FILE * file)
{
  openscop_statement_p stmt = openscop_statement_malloc();
  char buff[OPENSCOP_MAX_STRING], * start, * end;
  int nb_iterators;

  if (file)
  {
    // Read the domain matrices.
    stmt->domain = openscop_relation_read(file);

    // Read the scattering, if any.
    if (openscop_util_read_int(file, NULL) > 0)
      stmt->scattering = openscop_relation_read(file);

    // Read the access functions, if any.
    if (openscop_util_read_int(file, NULL) > 0)
    {
      stmt->read = openscop_relation_list_read(file);
      stmt->write = openscop_relation_list_read(file);
    }

    // Read the body information, if any.
    if (openscop_util_read_int(file, NULL) > 0)
    {
      // Read the original iterator names.
      stmt->iterators = openscop_util_strings_read(file, &nb_iterators);
      stmt->nb_iterators = nb_iterators;
      
      // Read the body:
      // - Skip blank/commented lines and spaces.
      start = openscop_util_skip_blank_and_comments(file, buff);
      
      // - Remove the comments.
      end = start;
      while ((*end != '#') && (*end != '\n'))
        end++;
      *end = '\0';
      
      // - Copy the body.
      stmt->body = strdup(start);
    }
    else
    {
      stmt->nb_iterators = OPENSCOP_UNDEFINED;
      stmt->iterators = NULL;
      stmt->body = strdup("[undefined]");
    }
  }

  return stmt;
}


/*+***************************************************************************
 *                   Memory allocation/deallocation functions                *
 *****************************************************************************/


/**
 * openscop_statement_malloc function:
 * This function allocates the memory space for a openscop_statement_t
 * structure and sets its fields with default values. Then it returns a pointer
 * to the allocated space.
 * \return A pointer to an empty statement with fields set to default values.
 */
openscop_statement_p
openscop_statement_malloc()
{
  openscop_statement_p statement;

  statement = (openscop_statement_p)malloc(sizeof(openscop_statement_t));
  if (statement == NULL)
  {
    fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
    exit(1);
  }

  statement->domain     = NULL;
  statement->scattering = NULL;
  statement->read       = NULL;
  statement->write      = NULL;
  statement->nb_iterators = 0;
  statement->iterators  = NULL;
  statement->nb_local_dims = 0;
  statement->local_dims = NULL;
  statement->body       = NULL;
  statement->next       = NULL;

  return statement;
}


/**
 * openscop_statement_free function:
 * This function frees the allocated memory for a openscop_statement_t
 * structure.
 * \param statement The pointer to the statement we want to free.
 */
void
openscop_statement_free(openscop_statement_p statement)
{
  int i;
  openscop_statement_p next;

  while (statement != NULL)
  {
    next = statement->next;
    openscop_relation_free(statement->domain);
    openscop_relation_free(statement->scattering);
    openscop_relation_list_free(statement->read);
    openscop_relation_list_free(statement->write);
    if (statement->iterators != NULL)
    {
      for (i = 0; i < statement->nb_iterators; i++)
        free(statement->iterators[i]);
      free(statement->iterators);
    }
    if (statement->body != NULL)
      free(statement->body);

    free(statement);
    statement = next;
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_statement_add function:
 * This function adds a statement "statement" at the end of the statement
 * list pointed by "location".
 * \param location  Address of the first element of the statement list.
 * \param statement The statement to add to the list.
 */
void
openscop_statement_add(openscop_statement_p * location,
                       openscop_statement_p   statement)
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
 * \return The number of statements in the statement list.
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


/**
 * openscop_statement_copy function:
 * This functions builds and returns a "hard copy" (not a pointer copy) of a
 * openscop_statement_t data structure provided as parameter.
 * \param statement  The pointer to the statement we want to copy.
 * \return A pointer to the full copy of the statement provided as parameter.
 */
openscop_statement_p
openscop_statement_copy(openscop_statement_p statement)
{
  int first = 1;
  openscop_statement_p copy = NULL, node, previous = NULL;

  while (statement != NULL)
  {
    node               = openscop_statement_malloc();
    node->version      = statement->version;
    node->domain       = openscop_relation_copy(statement->domain);
    node->scattering   = openscop_relation_copy(statement->scattering);
    node->read         = openscop_relation_list_copy(statement->read);
    node->write        = openscop_relation_list_copy(statement->write);
    node->nb_iterators = statement->nb_iterators;
    node->iterators    = openscop_util_strings_copy(statement->iterators,
                                                    statement->nb_iterators);
    node->body         = strdup(statement->body);
    node->next         = NULL;
    
    if (first)
    {
      first = 0;
      copy = node;
      previous = node;
    }
    else
    {
      previous->next = node;
      previous = previous->next;
    }

    statement = statement->next;
  }

  return copy;
}


/**
 * openscop_statement_equal function:
 * This function returns true if the two statements are the same, false
 * otherwise (the usr field is not tested).
 * \param s1 The first statement.
 * \param s2 The second statement.
 * \return 1 if s1 and s2 are the same (content-wise), 0 otherwise.
 */
int
openscop_statement_equal(openscop_statement_p s1, openscop_statement_p s2)
{
  int i;

  if (((s1->next != NULL) && (s2->next == NULL)) ||
      ((s1->next == NULL) && (s2->next != NULL)))
    return 0;

  if ((s1->next != NULL) && (s2->next != NULL))
    if (!openscop_statement_equal(s1->next, s2->next))
      return 0;
    
  if (//(s1->version != s2->version) ||
      (s1->nb_iterators != s2->nb_iterators) ||
      (!openscop_relation_equal(s1->domain,     s2->domain))     ||
      (!openscop_relation_equal(s1->scattering, s2->scattering)) ||
      (!openscop_relation_list_equal(s1->read,  s2->read))       ||
      (!openscop_relation_list_equal(s1->write, s2->write))      ||
      (strcmp(s1->body, s2->body) != 0))
    return 0;

  for (i = 0; i < s1->nb_iterators; i++)
    if (strcmp(s1->iterators[i], s2->iterators[i]) != 0)
      return 0;

  return 1;
}


/**
 * openscop_statement_integrity_check function:
 * This function checks that a statement is "well formed" according to some
 * expected properties (setting an expected value to OPENSCOP_UNDEFINED means
 * that we do not expect a specific value). It returns 0 if the check failed
 * or 1 if no problem has been detected.
 * \param statement               The statement we want to check.
 * \param expected_nb_parameters  Expected number of parameters.
 * \return 0 if the integrity check fails, 1 otherwise.
 */
int
openscop_statement_integrity_check(openscop_statement_p statement,
                                   int expected_nb_parameters)
{
  int expected_nb_iterators = OPENSCOP_UNDEFINED;

  while (statement != NULL)
  {
    if (!openscop_relation_integrity_check(statement->domain,
                                           OPENSCOP_TYPE_DOMAIN,
                                           OPENSCOP_UNDEFINED,
                                           OPENSCOP_UNDEFINED,
                                           expected_nb_parameters))
      return 0;

    // Get the number of iterators.
    if (statement->domain != NULL)
    {
      if (openscop_relation_is_matrix(statement->domain))
      {
        if (expected_nb_parameters != OPENSCOP_UNDEFINED)
          expected_nb_iterators = statement->domain->nb_columns -
                                  expected_nb_parameters - 2;
        else
          expected_nb_iterators = OPENSCOP_UNDEFINED;
      }
      else
        expected_nb_iterators = statement->domain->nb_output_dims;
    }

    if (!openscop_relation_integrity_check(statement->scattering,
                                           OPENSCOP_TYPE_SCATTERING,
                                           OPENSCOP_UNDEFINED,
                                           expected_nb_iterators,
                                           expected_nb_parameters) ||
        !openscop_relation_list_integrity_check(statement->read,
                                           OPENSCOP_TYPE_ACCESS,
                                           OPENSCOP_UNDEFINED,
                                           expected_nb_iterators,
                                           expected_nb_parameters) ||
        !openscop_relation_list_integrity_check(statement->write,
                                           OPENSCOP_TYPE_ACCESS,
                                           OPENSCOP_UNDEFINED,
                                           expected_nb_iterators,
                                           expected_nb_parameters))
      return 0;
    
    if ((statement->nb_iterators > 0) &&
        (statement->nb_iterators < statement->domain->nb_output_dims))
    {
      fprintf(stderr, "[OpenScop] Warning: not enough original iterator "
                      "names.\n");
      return 0;
    }

    statement = statement->next;
  }

  return 1;
}
