
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
 * this function displays an openscop_scop_t structure (*scop) into a
 * file (file, possibly stdout) in a way that trends to be understandable. It
 * includes an indentation level (level) in order to work with others
 * print_structure functions.
 * \param file  The file where the information has to be printed.
 * \param scop  The scop structure whose information has to be printed.
 * \param level Number of spaces before printing, for each line.
 */
void openscop_scop_print_structure(FILE * file, openscop_scop_p scop,
                                   int level) {
  int j;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (scop != NULL) {
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

    // Print the names.
    openscop_names_print_structure(file, scop->names, level+1);

    // Print the statements.
    openscop_statement_print_structure(file, scop->statement, level+1);

    // Print the extensions.
    openscop_extension_print_structure(file, scop->extension, level+1);

    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");
  }
  else {
    fprintf(file, "+-- NULL scop\n");
  }

  // The last line.
  for (j = 0; j <= level; j++)
    fprintf(file, "|\t");
  fprintf(file, "\n");
}


/**
 * openscop_scop_print function:
 * this function prints the content of an openscop_scop_t structure (*scop)
 * into a file (file, possibly stdout).
 * \param file The file where the information has to be printed.
 * \param scop The scop structure whose information has to be printed.
 */
void openscop_scop_print(FILE * file, openscop_scop_p scop) {
  openscop_scop_print_structure(file, scop, 0);
}


/**
 * openscop_scop_name_limits function:
 * this function finds the (maximum) number of various elements of a scop and
 * return the values through parameters. To ensure the correctness of the
 * results, an integrity check of the input scop should be run before calling
 * this function.
 * \param scop          The scop to analyse.
 * \parem nb_parameters The number of parameters in the scop (output).
 * \parem nb_iterators  The number of iterators in the scop (output).
 * \parem nb_scattdims  The number of scattdims in the scop (output).
 * \parem nb_localdims  The number of local dimensions in the scop (output).
 * \parem nb_arrays     The number of arrays in the scop (output).
 */
static
void openscop_scop_name_limits(openscop_scop_p scop,
                              int * nb_parameters,
                              int * nb_iterators,
                              int * nb_scattdims,
                              int * nb_localdims,
                              int * nb_arrays) {
  int i, k, tmp, coef, id;
  openscop_statement_p statement;
  openscop_relation_list_p list;
  
  // * The number of parameters is collected from the context,
  //   - in matrix format we compute it from the context using #columns,
  //   - in relation format it corresponds to the #parameters field.
  // * The numbers of local dimensions are collected from all relations
  //   in the corresponding field, it is 0 for matrix format.
  *nb_parameters = 0;
  *nb_localdims = 0;
  if (scop->context != NULL) { 
    if (openscop_relation_is_matrix(scop->context)) {
      *nb_parameters = scop->context->nb_columns - 2;
    }
    else {
      *nb_parameters = scop->context->nb_parameters;
      *nb_localdims  = scop->context->nb_local_dims;
    }
  }

  *nb_iterators = 0;
  *nb_scattdims = 0;
  *nb_arrays    = 0;
  statement = scop->statement;
  while (statement != NULL) {
    // * The number of iterators are defined by iteration domains,
    //   - in matrix format we compute it using #columns and #parameters,
    //   - in relation format it corresponds to the #output_dims.
    if (statement->domain != NULL) {
      if (openscop_relation_is_matrix(statement->domain)) {
        tmp = statement->domain->nb_columns - *nb_parameters - 2;
        if (tmp > *nb_iterators)
          *nb_iterators = tmp;
      }
      else {
        if (statement->domain->nb_output_dims > *nb_iterators)
          *nb_iterators = statement->domain->nb_output_dims;
	
	if (statement->domain->nb_local_dims > *nb_localdims)
	  *nb_localdims = statement->domain->nb_local_dims;
      }
    }

    // * The number of scattdims are defined by scattering,
    //   - in matrix format it corresponds to the number of rows,
    //   - in relation format it corresponds to the #input_dims.
    if (statement->scattering != NULL) {
      if (openscop_relation_is_matrix(statement->scattering)) {
        if (statement->domain->nb_rows > *nb_scattdims)
          *nb_scattdims = statement->scattering->nb_rows;
      }
      else {
        if (statement->scattering->nb_input_dims > *nb_scattdims)
          *nb_scattdims = statement->scattering->nb_input_dims;
	
	if (statement->scattering->nb_local_dims > *nb_localdims)
	  *nb_localdims = statement->scattering->nb_local_dims;
      }
    }

    // * The number of arrays are defined by accesses,
    //   - in matrix format, array identifiers are m[0][0],
    //   - in relation format, array identifiers are
    //     m[i][#columns -1] / m[i][1], with i the (supposedly only) row
    //     where m[i][1] is not 0.
    for (k = 0; k < 2; k++) {
      if (k == 0)
	list = statement->read;
      else
	list = statement->write;
      
      while (list != NULL) {
	if (list->elt != NULL) {
	  if (openscop_relation_is_matrix(list->elt)) {
	    if (SCOPINT_get_si(list->elt->m[0][0]) > *nb_arrays)
	      *nb_arrays = SCOPINT_get_si(list->elt->m[0][0]);
	  }
	  else {
	    for (i = 0; i < list->elt->nb_rows; i++) {
	      coef = SCOPINT_get_si(list->elt->m[i][1]);
	      if (coef != 0) {
		id = SCOPINT_get_si(list->elt->m[0][list->elt->nb_columns-1]);
		if (abs(id / coef) > *nb_arrays)
		  *nb_arrays = abs(id / coef);
	      }
	    }

	    if (statement->scattering->nb_local_dims > *nb_localdims)
	      *nb_localdims = statement->scattering->nb_local_dims;
	  }
	}

	list = list->next;
      }
    }

    statement = statement->next;
  }
}


/**
 * openscop_scop_full_names function:
 * this function generates an openscop_names_p structure which contains
 * enough names for the scop provided as parameter, for each kind of names.
 * If the names contained in the input scop are not sufficient, this function
 * generated the missing names.
 * \param scop The scop we need a name for each element.
 * \return A set of names for the scop.
 */
static
openscop_names_p openscop_scop_full_names(openscop_scop_p scop) {
  int nb_parameters;
  int nb_iterators;
  int nb_scattdims;
  int nb_localdims;
  int nb_arrays;
  openscop_arrays_p arrays;
  openscop_names_p names;

  names = openscop_names_copy(scop->names);

  // Extract array names information from extensions.
  openscop_util_strings_free(names->arrays, names->nb_arrays);
  arrays = (openscop_arrays_p)openscop_extension_lookup(scop->extension,
                                  OPENSCOP_EXTENSION_ARRAYS);
  names->arrays = openscop_arrays_generate_names(arrays,
                                  &(names->nb_arrays));
  
  // Complete names if necessary.
  openscop_scop_name_limits(scop, &nb_parameters,
                                  &nb_iterators,
                                  &nb_scattdims,
				  &nb_localdims,
			          &nb_arrays);

  openscop_util_strings_complete(&names->parameters, &names->nb_parameters,
                                 "P_", nb_parameters);
  
  openscop_util_strings_complete(&names->iterators,  &names->nb_iterators,
                                 "i_", nb_iterators);
  
  openscop_util_strings_complete(&names->scattdims,  &names->nb_scattdims,
                                 "s_", nb_scattdims);
  
  openscop_util_strings_complete(&names->localdims,  &names->nb_localdims,
                                 "l_", nb_localdims);
  
  openscop_util_strings_complete(&names->arrays,     &names->nb_arrays,
                                 "A_", nb_arrays);

  return names;
}


/**
 * openscop_scop_print_openscop function:
 * this function prints the content of an openscop_scop_t structure (*scop)
 * into a file (file, possibly stdout) in the OpenScop textual format.
 * \param file The file where the information has to be printed.
 * \param scop The scop structure whose information has to be printed.
 */
void openscop_scop_print_openscop(FILE * file, openscop_scop_p scop) {
  openscop_names_p names;
  int tmp_nb_iterators = 0;
  char ** tmp_iterators = NULL;

  if (openscop_scop_integrity_check(scop) == 0) {
    fprintf(stderr, "[OpenScop] Error: OpenScop integrity check failed.\n");
    exit(1);
  }

  // Build a name structure for pretty printing of relations.
  names = openscop_scop_full_names(scop);

  if (0) {
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
  else {
    fprintf(file, "# [File generated by the OpenScop Library %s %s bits]\n",
            OPENSCOP_RELEASE,OPENSCOP_VERSION);
  }

  fprintf(file, "\nOpenScop\n\n");
  fprintf(file, "# =============================================== Global\n");
  fprintf(file, "# Language\n");
  fprintf(file, "%s\n\n", scop->language);

  fprintf(file, "# Context\n");
  // Remove the iterators from the names structure to print comments, as
  // this information is used to know the number of iterators.
  // TODO: do this in openscop_relation_print_openscop
  tmp_nb_iterators = names->nb_iterators;
  tmp_iterators = names->iterators;
  names->nb_iterators = 0;
  names->iterators = NULL;
  openscop_relation_print_openscop(file, scop->context,
                                   OPENSCOP_TYPE_DOMAIN, names);
  names->nb_iterators = tmp_nb_iterators;
  names->iterators = tmp_iterators;
  fprintf(file, "\n");

  openscop_names_print_openscop(file, scop->names);

  fprintf(file, "# Number of statements\n");
  fprintf(file, "%d\n\n",openscop_statement_number(scop->statement));

  openscop_statement_print_openscop(file, scop->statement, names);
  
  if (scop->extension) {
    fprintf(file, "# ==============================================="
                  " Extensions\n");
    openscop_extension_print_openscop(file, scop->extension);
  }

  openscop_names_free(names);
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


static
void openscop_scop_update_val(int * variable, int value) {
  if ((*variable == OPENSCOP_UNDEFINED) || (*variable == value))
    *variable = value;
  else
    fprintf(stderr, "[OpenScop] Warning: number of iterators and "
                    "parameters inconsistency.\n");
}

static
void openscop_scop_update_properties(openscop_relation_p relation,
                                     int nb_output_dims, int nb_input_dims,
                                     int nb_parameters) {
  if (relation != NULL) {
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
void openscop_scop_propagate_properties(openscop_scop_p scop) {
  int i, nb_parameters;
  openscop_statement_p     statement;
  openscop_relation_p      relation;
  openscop_relation_list_p list;

  // Context part: get the number of parameters.
  if ((scop->context != NULL) &&
      (openscop_relation_is_matrix(scop->context))) {
    nb_parameters = scop->context->nb_columns - 2;
    openscop_scop_update_properties(scop->context, 0, 0, nb_parameters);
  }
  else {
    return;
  }

  // For each statement:
  statement = scop->statement;
  while (statement != NULL) {
    // - Domain part,
    relation = statement->domain;
    if (openscop_relation_is_matrix(relation)) {
      while (relation != NULL) {
        openscop_scop_update_properties(
            relation, relation->nb_columns-nb_parameters-2, 0, nb_parameters);
        relation = relation->next;
      }
    }

    // - Scattering part,
    relation = statement->scattering;
    if (openscop_relation_is_matrix(relation)) {
      while (relation != NULL) {
        openscop_scop_update_properties(
            relation, 0, relation->nb_columns-nb_parameters-2, nb_parameters);
        relation = relation->next;
      }
    }

    // - Access part.
    for (i = 0; i < 2; i++) {
      if (i == 0)
        list = statement->read;
      else
        list = statement->write;

      while (list != NULL) {
        relation = list->elt;
        if (openscop_relation_is_matrix(relation)) {
          while (relation != NULL) {
            openscop_scop_update_properties(
                relation, 0, relation->nb_columns - nb_parameters - 2,
                nb_parameters);
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
 * this function reads a scop structure from a file (possibly stdin)
 * complying to the OpenScop textual format and returns a pointer to this
 * scop structure. If some relation properties (number of input/output/local
 * dimensions and number of parameters) are undefined, it will define them
 * according to the available information. 
 * \param file The file where the scop has to be read.
 * \return A pointer to the scop structure that has been read.
 */
openscop_scop_p openscop_scop_read(FILE * file) {
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

  //
  // I. CONTEXT PART
  //

  // Ensure the file is a .scop.
  tmp = openscop_util_strings_read(file, &max);
  if ((max == 0) || (strcmp(*tmp, "OpenScop"))) {
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
  char ** language =  openscop_util_strings_read(file, &max);
  if (max == 0) {
    fprintf(stderr, "[OpenScop] Error: no language (backend) specified.\n");
    exit (1);
  }
  if (max > 1)
    fprintf(stderr, "[OpenScop] Warning: uninterpreted information "
                    "(after language).\n");
  scop->language = *language;
  free(language);

  // Read the context.
  scop->context = openscop_relation_read(file);
  scop->names = openscop_names_read(file);

  //
  // II. STATEMENT PART
  //

  // Read the number of statements.
  nb_statements = openscop_util_read_int(file, NULL);

  for (i = 0; i < nb_statements; ++i) {
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
 * this function allocates the memory space for a openscop_scop_t structure and
 * sets its fields with default values. Then it returns a pointer to the
 * allocated space.
 * \return A pointer to an empty scop with fields set to default values.
 */
openscop_scop_p openscop_scop_malloc() {
  openscop_scop_p scop;

  scop = (openscop_scop_p)malloc(sizeof(openscop_scop_t));
  if (scop == NULL) {
    fprintf(stderr, "[OpenScop] Memory Overflow.\n");
    exit(1);
  }

  scop->version            = 1;
  scop->language           = NULL;
  scop->context            = NULL;
  scop->names              = NULL;
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
void openscop_scop_free(openscop_scop_p scop) {
  if (scop != NULL) {
    if (scop->language != NULL)
      free(scop->language);
    
    openscop_relation_free(scop->context);
    openscop_names_free(scop->names);
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
 * \param statement The pointer to the scop we want to copy.
 * \return A pointer to the full copy of the scop provided as parameter.
 */
openscop_scop_p openscop_scop_copy(openscop_scop_p scop) {
  openscop_scop_p copy;
  
  copy                     = openscop_scop_malloc();
  copy->version            = scop->version;
  if (scop->language != NULL)
    copy->language         = strdup(scop->language);
  copy->context            = openscop_relation_copy(scop->context);
  copy->names              = openscop_names_copy(scop->names);
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
int openscop_scop_equal(openscop_scop_p s1, openscop_scop_p s2) {
  
  if (s1 == s2)
    return 1;

  if (s1->version != s2->version) {
    fprintf(stderr, "[OpenScop] info: versions are not the same.\n"); 
    return 0;
  }
  
  if (strcmp(s1->language, s2->language) != 0) {
    fprintf(stderr, "[OpenScop] info: languages are not the same.\n"); 
    return 0;
  }

  if (!openscop_relation_equal(s1->context, s2->context)) {
    fprintf(stderr, "[OpenScop] info: contexts are not the same.\n"); 
    return 0;
  }
  
  if (!openscop_names_equal(s1->names, s2->names)) {
    fprintf(stderr, "[OpenScop] info: names are not the same.\n"); 
    return 0;
  }
  
  if (!openscop_statement_equal(s1->statement, s2->statement)) {
    fprintf(stderr, "[OpenScop] info: statements are not the same.\n"); 
    return 0;
  }
  
  if (!openscop_extension_equal(s1->extension, s2->extension)) {
    fprintf(stderr, "[OpenScop] info: extensions are not the same.\n"); 
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
int openscop_scop_integrity_check(openscop_scop_p scop) {
  int expected_nb_parameters;
  int max_nb_parameters;
  int max_nb_iterators;
  int max_nb_scattdims;
  int max_nb_localdims;
  int max_nb_arrays;

  openscop_scop_print(stdout, scop);

  // Check the language.
  if ((scop->language != NULL) &&
      (!strcmp(scop->language, "caml")  || !strcmp(scop->language, "Caml") ||
       !strcmp(scop->language, "ocaml") || !strcmp(scop->language, "OCaml")))
    fprintf(stderr, "[OpenScop] Alert: What ?! Caml ?! Are you sure ?!\n");
  
  // Check the context.
  if (openscop_relation_is_matrix(scop->context))

  if (!openscop_relation_integrity_check(scop->context,
                                         OPENSCOP_TYPE_CONTEXT,
                                         OPENSCOP_UNDEFINED,
                                         OPENSCOP_UNDEFINED,
                                         OPENSCOP_UNDEFINED))
    return 0;

  // Get the number of parameters.
  if (scop->context != NULL) { 
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
  openscop_scop_name_limits(scop, &max_nb_parameters,
                                  &max_nb_iterators,
                                  &max_nb_scattdims,
				  &max_nb_localdims,
			          &max_nb_arrays);

  return openscop_names_integrity_check(scop->names, expected_nb_parameters,
                                        max_nb_iterators, max_nb_scattdims);
}
