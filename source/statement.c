
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
 * openscop_statement_idump function:
 * Displays a openscop_statement_t structure (*statement) into a file (file,
 * possibly stdout) in a way that trends to be understandable without falling
 * in a deep depression or, for the lucky ones, getting a headache... It
 * includes an indentation level (level) in order to work with others
 * print_structure functions.
 * \param file      File where informations are printed.
 * \param statement The statement whose information have to be printed.
 * \param level     Number of spaces before printing, for each line.
 */
void openscop_statement_idump(FILE * file,
                              openscop_statement_p statement,
                              int level) {
  int i, j, first = 1, number = 1;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (statement != NULL)
    fprintf(file, "+-- openscop_statement_t (S%d)\n", number);
  else
    fprintf(file, "+-- NULL statement\n");

  while (statement != NULL) {
    if (!first) {
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
    openscop_relation_idump(file, statement->domain, level+1);

    // Print the scattering of the statement.
    openscop_relation_idump(file, statement->scattering, level+1);

    // Print the array access information of the statement.
    openscop_relation_list_idump(file, statement->access, level+1);

    // Print the statement body information.
    openscop_body_idump(file, statement->body, level+1);

    // A blank line.
    for (i = 0; i <= level+1; i++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    statement = statement->next;
    number++;

    // Next line.
    if (statement != NULL) {
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
 * openscop_statement_dump function:
 * This function prints the content of a openscop_statement_t structure
 * (*statement) into  a file (file, possibly stdout).
 * \param file      File where informations are printed.
 * \param statement The statement whose information have to be printed.
 */
void openscop_statement_dump(FILE * file, openscop_statement_p statement) {
  openscop_statement_idump(file, statement, 0);
}


/**
 * openscop_statement_print function:
 * This function prints the content of a openscop_statement_t structure
 * (*statement) into a file (file, possibly stdout) in the OpenScop format.
 * \param file      File where informations are printed.
 * \param statement The statement whose information have to be printed.
 * \param names     The textual names of the various elements.
 *                  Set to NULL if printing comments is not needed.
 */
void openscop_statement_print(FILE * file,
                              openscop_statement_p statement,
                              openscop_names_p names) {
  int nb_relations, number = 1;

  while (statement != NULL) {
    nb_relations = 0;

    fprintf(file, "# =============================================== ");
    fprintf(file, "Statement %d\n", number);

    fprintf(file, "# Number of relations describing the statement:\n");

    if (statement->domain != NULL)
      nb_relations ++;
    if (statement->scattering != NULL)
      nb_relations ++;
    nb_relations += openscop_relation_list_count(statement->access); 

    fprintf(file, "%d\n\n", nb_relations);

    fprintf(file, "# ---------------------------------------------- ");
    fprintf(file, "%2d.1 Domain\n", number);
    openscop_relation_print(file, statement->domain, names);
    fprintf(file, "\n");

    fprintf(file, "# ---------------------------------------------- ");
    fprintf(file, "%2d.2 Scattering\n", number);
    openscop_relation_print(file, statement->scattering, names);
    fprintf(file, "\n");

    fprintf(file, "# ---------------------------------------------- ");
    fprintf(file, "%2d.3 Access\n", number);
    openscop_relation_list_print_elts(file, statement->access, names);
    fprintf(file, "\n");

    fprintf(file, "# ---------------------------------------------- ");
    fprintf(file, "%2d.4 Body\n", number);
    openscop_body_print(file, statement->body);

    fprintf(file, "\n\n");
    statement = statement->next;
    number++;
  }
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/**
 * openscop_statement_dispatch function:
 * this function dispatches the relations from a relation list to the
 * convenient fields of a statement structure: it extracts the domain,
 * the scattering and the access list and store them accordingly in the
 * statement structure provided as a parameter.
 * \param stmt The statement where to dispatch the relations.
 * \param list The "brute" relation list to sort and dispatch (freed).
 */
static
void openscop_statement_dispatch(openscop_statement_p stmt,
                                 openscop_relation_list_p list) {
  openscop_relation_list_p domain_list; 
  openscop_relation_list_p scattering_list; 
  int nb_domains, nb_scattering, nb_accesses;

  // Domain.
  domain_list = openscop_relation_list_filter(list, OPENSCOP_TYPE_DOMAIN);
  nb_domains = openscop_relation_list_count(domain_list); 
  if (nb_domains > 1)
    OPENSCOP_error("more than one domain for a statement");
  
  if (domain_list != NULL) {
    stmt->domain = domain_list->elt;
    domain_list->elt = NULL;
    openscop_relation_list_free(domain_list);
  }
  else {
    stmt->domain = NULL;
  }

  // Scattering.
  scattering_list=openscop_relation_list_filter(list,OPENSCOP_TYPE_SCATTERING);
  nb_scattering = openscop_relation_list_count(scattering_list); 
  if (nb_scattering > 1)
    OPENSCOP_error("more than one scattering relation for a statement");
  
  if (scattering_list != NULL) {
    stmt->scattering = scattering_list->elt;
    scattering_list->elt = NULL;
    openscop_relation_list_free(scattering_list);
  }
  else {
    stmt->scattering = NULL;
  }

  // Access.
  stmt->access = openscop_relation_list_filter(list, OPENSCOP_TYPE_ACCESS);
  nb_accesses = openscop_relation_list_count(stmt->access);

  if ((nb_domains + nb_scattering + nb_accesses) !=
      (openscop_relation_list_count(list)))
    OPENSCOP_error("unexpected relation type to define a statement");

  openscop_relation_list_free(list);
}


/**
 * openscop_statement_read function:
 * This function reads a openscop_statement_t structure from an input stream
 * (possibly stdin).
 * \param file The input stream.
 * \return A pointer to the statement structure that has been read.
 */
openscop_statement_p openscop_statement_read(FILE * file) {
  openscop_statement_p stmt = openscop_statement_malloc();
  openscop_relation_list_p list;
  int expected_nb_iterators;

  if (file) {
    // Read all statement relations.
    list = openscop_relation_list_read(file);

    // Store relations at the right place according to their type.
    openscop_statement_dispatch(stmt, list);

    // Read the body information.
    if (stmt->domain != NULL) {
      expected_nb_iterators = stmt->domain->nb_output_dims;
    }
    else {
      OPENSCOP_warning("no domain, assuming 0 original iterator");
      expected_nb_iterators = 0;
    }
    stmt->body = openscop_body_read(file, expected_nb_iterators);
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
openscop_statement_p openscop_statement_malloc() {
  openscop_statement_p statement;

  OPENSCOP_malloc(statement, openscop_statement_p,
                  sizeof(openscop_statement_t));
  statement->domain     = NULL;
  statement->scattering = NULL;
  statement->access     = NULL;
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
void openscop_statement_free(openscop_statement_p statement) {
  openscop_statement_p next;

  while (statement != NULL) {
    next = statement->next;
    openscop_relation_free(statement->domain);
    openscop_relation_free(statement->scattering);
    openscop_relation_list_free(statement->access);
    openscop_body_free(statement->body);

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
void openscop_statement_add(openscop_statement_p * location,
                            openscop_statement_p   statement) {
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
int openscop_statement_number(openscop_statement_p statement) {
  int number = 0;

  while (statement != NULL) {
    number++;
    statement = statement->next;
  }
  return number;
}


/**
 * openscop_statement_clone function:
 * This functions builds and returns a "hard copy" (not a pointer copy) of a
 * openscop_statement_t data structure provided as parameter.
 * \param statement  The pointer to the statement we want to copy.
 * \return A pointer to the full copy of the statement provided as parameter.
 */
openscop_statement_p openscop_statement_clone(openscop_statement_p statement) {
  int first = 1;
  openscop_statement_p copy = NULL, node, previous = NULL;

  while (statement != NULL) {
    node               = openscop_statement_malloc();
    node->domain       = openscop_relation_clone(statement->domain);
    node->scattering   = openscop_relation_clone(statement->scattering);
    node->access       = openscop_relation_list_clone(statement->access);
    node->body         = openscop_body_clone(statement->body);
    node->next         = NULL;
    
    if (first) {
      first = 0;
      copy = node;
      previous = node;
    }
    else {
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
int openscop_statement_equal(openscop_statement_p s1,
                             openscop_statement_p s2) {
  
  if (s1 == s2)
    return 1;
  
  if (((s1->next != NULL) && (s2->next == NULL)) ||
      ((s1->next == NULL) && (s2->next != NULL)))
    return 0;

  if ((s1->next != NULL) && (s2->next != NULL))
    if (!openscop_statement_equal(s1->next, s2->next))
      return 0;
    
  if ((!openscop_relation_equal(s1->domain,      s2->domain))     ||
      (!openscop_relation_equal(s1->scattering,  s2->scattering)) ||
      (!openscop_relation_list_equal(s1->access, s2->access))     ||
      (!openscop_body_equal(s1->body, s2->body)))
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
int openscop_statement_integrity_check(openscop_statement_p statement,
                                       int expected_nb_parameters) {
  int expected_nb_iterators;

  while (statement != NULL) {
    // Check the domain.
    if (!openscop_relation_integrity_check(statement->domain,
                                           OPENSCOP_TYPE_DOMAIN,
                                           OPENSCOP_UNDEFINED,
                                           0,
                                           expected_nb_parameters)) {
      return 0;
    }

    // Get the number of iterators.
    if (statement->domain != NULL)
      expected_nb_iterators = statement->domain->nb_output_dims;
    else
      expected_nb_iterators = OPENSCOP_UNDEFINED;

    // Check the scattering relation.
    if (!openscop_relation_integrity_check(statement->scattering,
                                           OPENSCOP_TYPE_SCATTERING,
                                           OPENSCOP_UNDEFINED,
                                           expected_nb_iterators,
                                           expected_nb_parameters)) {
      return 0;
    }

    // Check the access relations.
    if (!openscop_relation_list_integrity_check(statement->access,
                                           OPENSCOP_TYPE_ACCESS,
                                           OPENSCOP_UNDEFINED,
                                           expected_nb_iterators,
                                           expected_nb_parameters)) {
      return 0;
    }

    // Check the statement body.
    if (!openscop_body_integrity_check(statement->body,
                                           expected_nb_iterators)) {
      return 0;
    }

    statement = statement->next;
  }

  return 1;
}
