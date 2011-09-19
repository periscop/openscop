
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
 * this function displays an openscop_statement_t structure (*statement) into
 * a file (file, possibly stdout) in a way that trends to be understandable.
 * It includes an indentation level (level) in order to work with others
 * dumping functions.
 * \param[in] file      File where the information has to be printed.
 * \param[in] statement The statement whose information has to be printed.
 * \param[in] level     Number of spaces before printing, for each line.
 */
void openscop_statement_idump(FILE * file,
                              openscop_statement_p statement,
                              int level) {
  int j, first = 1, number = 1;

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
    for (j = 0; j <= level + 1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    // Print the domain of the statement.
    openscop_relation_idump(file, statement->domain, level + 1);

    // Print the scattering of the statement.
    openscop_relation_idump(file, statement->scattering, level + 1);

    // Print the array access information of the statement.
    openscop_relation_list_idump(file, statement->access, level + 1);

    // Print the original iterator names.
    openscop_generic_idump(file, statement->iterators, level + 1);

    // Print the original body expression.
    openscop_generic_idump(file, statement->body, level + 1);

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
 * this function prints the content of an openscop_statement_t structure
 * (*statement) into  a file (file, possibly stdout).
 * \param[in] file      The file where the information has to be printed.
 * \param[in] statement The statement whose information has to be printed.
 */
void openscop_statement_dump(FILE * file, openscop_statement_p statement) {
  openscop_statement_idump(file, statement, 0);
}


/**
 * openscop_statement_print function:
 * this function prints the content of an openscop_statement_t structure
 * (*statement) into a file (file, possibly stdout) in the OpenScop format.
 * \param[in] file      The file where the information has to be printed.
 * \param[in] statement The statement whose information has to be printed.
 */
void openscop_statement_print(FILE * file,
                              openscop_statement_p statement) {
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
    openscop_relation_print(file, statement->domain);
    fprintf(file, "\n");

    fprintf(file, "# ---------------------------------------------- ");
    fprintf(file, "%2d.2 Scattering\n", number);
    openscop_relation_print(file, statement->scattering);
    fprintf(file, "\n");

    fprintf(file, "# ---------------------------------------------- ");
    fprintf(file, "%2d.3 Access\n", number);
    openscop_relation_list_print_elts(file, statement->access);
    fprintf(file, "\n");

    fprintf(file, "# ---------------------------------------------- ");
    fprintf(file, "%2d.4 Body\n", number);
    if (openscop_generic_hasURI(statement->body, OPENSCOP_URI_STRINGS)) {
      fprintf(file, "# Statement body is provided\n");
      fprintf(file, "1\n");
      if (openscop_generic_hasURI(statement->iterators,OPENSCOP_URI_STRINGS)) {
        fprintf(file, "# Original iterators\n");
        openscop_generic_print(file, statement->iterators);
      }
      fprintf(file, "# Body expression\n");
      openscop_generic_print(file, statement->body);
    }
    else {
      fprintf(file, "# Statement body is not provided\n");
      fprintf(file, "0\n");
    }

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
 * \param[in,out] stmt The statement where to dispatch the relations.
 * \param[in,out] list The "brute" relation list to sort and dispatch (freed).
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
 * this function reads an openscop_statement_t structure from an input stream
 * (possibly stdin).
 * \param[in] file The input stream.
 * \return A pointer to the statement structure that has been read.
 */
openscop_statement_p openscop_statement_read(FILE * file) {
  int nb_iterators;
  char buffer[OPENSCOP_MAX_STRING], * start, * end;
  openscop_statement_p stmt = openscop_statement_malloc();
  openscop_relation_list_p list;
  openscop_interface_p interface;

  if (file) {
    // Read all statement relations.
    list = openscop_relation_list_read(file);

    // Store relations at the right place according to their type.
    openscop_statement_dispatch(stmt, list);

    // Read the body information.
    if (stmt->domain != NULL) {
      nb_iterators = stmt->domain->nb_output_dims;
    }
    else {
      OPENSCOP_warning("no domain, assuming 0 original iterator");
      nb_iterators = 0;
    }

    if (openscop_util_read_int(file, NULL) > 0) {
      // Read the original iterator names.
      if (nb_iterators > 0) {
        interface = openscop_strings_interface();
        start = openscop_util_skip_blank_and_comments(file, buffer);
        stmt->iterators = openscop_generic_sread(start, interface);
        openscop_interface_free(interface);
      }
      
      // Read the body:
      // - Skip blank/commented lines and spaces before the body.
      start = openscop_util_skip_blank_and_comments(file, buffer);
      
      // - Remove the comments after the body.
      end = start;
      while ((*end != '#') && (*end != '\n'))
        end++;
      *end = '\0';
      
      // - Build the body.
      stmt->body = openscop_generic_malloc();
      stmt->body->interface = openscop_strings_interface();
      stmt->body->data = openscop_strings_encapsulate(strdup(start));
    }
  }

  return stmt;
}


/*+***************************************************************************
 *                   Memory allocation/deallocation functions                *
 *****************************************************************************/


/**
 * openscop_statement_malloc function:
 * this function allocates the memory space for an openscop_statement_t
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
  statement->iterators  = NULL;
  statement->body       = NULL;
  statement->next       = NULL;

  return statement;
}


/**
 * openscop_statement_free function:
 * this function frees the allocated memory for an openscop_statement_t
 * structure.
 * \param[in,out] statement The pointer to the statement we want to free.
 */
void openscop_statement_free(openscop_statement_p statement) {
  openscop_statement_p next;

  while (statement != NULL) {
    next = statement->next;
    openscop_relation_free(statement->domain);
    openscop_relation_free(statement->scattering);
    openscop_relation_list_free(statement->access);
    openscop_generic_free(statement->iterators);
    openscop_generic_free(statement->body);

    free(statement);
    statement = next;
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_statement_add function:
 * this function adds a statement "statement" at the end of the statement
 * list pointed by "location".
 * \param[in,out] location  Address of the first element of the statement list.
 * \param[in]     statement The statement to add to the list.
 */
void openscop_statement_add(openscop_statement_p * location,
                            openscop_statement_p   statement) {
  while (*location != NULL)
    location = &((*location)->next);

  *location = statement;
}


/**
 * openscop_statement_number function:
 * this function returns the number of statements in the statement list
 * provided as parameter.
 * \param[in] statement The first element of the statement list.
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
 * This functions builds and returns a "hard copy" (not a pointer copy) of an
 * openscop_statement_t data structure provided as parameter.
 * \param[in] statement The pointer to the statement we want to clone.
 * \return A pointer to the clone of the statement provided as parameter.
 */
openscop_statement_p openscop_statement_clone(openscop_statement_p statement) {
  int first = 1;
  openscop_statement_p clone = NULL, node, previous = NULL;

  while (statement != NULL) {
    node             = openscop_statement_malloc();
    node->domain     = openscop_relation_clone(statement->domain);
    node->scattering = openscop_relation_clone(statement->scattering);
    node->access     = openscop_relation_list_clone(statement->access);
    node->iterators  = openscop_generic_clone(statement->iterators);
    node->body       = openscop_generic_clone(statement->body);
    node->next       = NULL;
    
    if (first) {
      first = 0;
      clone = node;
      previous = node;
    }
    else {
      previous->next = node;
      previous = previous->next;
    }

    statement = statement->next;
  }

  return clone;
}


/**
 * openscop_statement_equal function:
 * this function returns true if the two statements provided as parameters
 * are the same, false otherwise (the usr field is not tested).
 * \param[in] s1 The first statement.
 * \param[in] s2 The second statement.
 * \return 1 if s1 and s2 are the same (content-wise), 0 otherwise.
 */
int openscop_statement_equal(openscop_statement_p s1,
                             openscop_statement_p s2) {
  
  if (s1 == s2)
    return 1;
  
  if (((s1->next != NULL) && (s2->next == NULL)) ||
      ((s1->next == NULL) && (s2->next != NULL))) {
    OPENSCOP_info("statements are not the same"); 
    return 0;
  }

  if ((s1->next != NULL) && (s2->next != NULL)) {
    if (!openscop_statement_equal(s1->next, s2->next)) {
      OPENSCOP_info("number of statements is not the same"); 
      return 0;
    }
  }
    
  if (!openscop_relation_equal(s1->domain, s2->domain)) {
    OPENSCOP_info("statement domains are not the same"); 
    return 0;
  }

  if (!openscop_relation_equal(s1->scattering, s2->scattering)) {
    OPENSCOP_info("statement scatterings are not the same"); 
    return 0;
  }

  if (!openscop_relation_list_equal(s1->access, s2->access)) {
    OPENSCOP_info("statement accesses are not the same"); 
    return 0;
  }

  if (!openscop_generic_equal(s1->iterators, s2->iterators)) {
    OPENSCOP_info("statement original iterators are not the same"); 
    return 0;
  }

  if (!openscop_generic_equal(s1->body, s2->body)) {
    OPENSCOP_info("statement bodies are not the same"); 
    return 0;
  }

  return 1;
}


/**
 * openscop_statement_integrity_check function:
 * this function checks that a statement is "well formed" according to some
 * expected properties (setting an expected value to OPENSCOP_UNDEFINED means
 * that we do not expect a specific value). It returns 0 if the check failed
 * or 1 if no problem has been detected.
 * \param[in] statement              The statement we want to check.
 * \param[in] expected_nb_parameters Expected number of parameters.
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
    if ((expected_nb_iterators != OPENSCOP_UNDEFINED) &&
        (statement->iterators != NULL) &&
        (statement->iterators->interface != NULL) &&
        (statement->iterators->interface->URI != NULL) &&
        (strcmp(statement->iterators->interface->URI,
                OPENSCOP_URI_STRINGS) == 0) &&
        (expected_nb_iterators !=
         openscop_strings_size(statement->iterators->data))) {
      OPENSCOP_warning("unexpected number of original iterators");
      return 0;
    }

    statement = statement->next;
  }

  return 1;
}


/**
 * openscop_statement_get_nb_iterators function:
 * this function returns the number of surroounding iterators of a given
 * statement.
 * \param statement The statement we want to know the number of iterators.
 * \return The number of surrounding iterators for the statement.
 */
int openscop_statement_get_nb_iterators(openscop_statement_p statement) {

  if (statement->domain == NULL) {
    OPENSCOP_warning("no statement domain, assuming 0 iterators");
    return 0;
  }
  else {
    return statement->domain->nb_output_dims;
  }
}


