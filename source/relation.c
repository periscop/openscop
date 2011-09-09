
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                           relation.c                            **
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
# include <openscop/relation.h>


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * openscop_relation_print_type function:
 * this function displays the textual type of an openscop_relation_t structure
 * into a file (file, possibly stdout), accoding to the OpenScop specification.
 * \param[in] file     File where informations are printed.
 * \param[in] relation The relation whose type has to be printed.
 */
static
void openscop_relation_print_type(FILE * file, openscop_relation_p relation) {

  if (relation != NULL) {
    switch (relation->type) {
      case OPENSCOP_UNDEFINED: {
        fprintf(file, OPENSCOP_STRING_UNDEFINED);
        break;
      }
      case OPENSCOP_TYPE_CONTEXT: {
        fprintf(file, OPENSCOP_STRING_CONTEXT);
        break;
      }
      case OPENSCOP_TYPE_DOMAIN: {
        fprintf(file, OPENSCOP_STRING_DOMAIN);
        break;
      }
      case OPENSCOP_TYPE_SCATTERING: {
        fprintf(file, OPENSCOP_STRING_SCATTERING);
        break;
      }
      case OPENSCOP_TYPE_READ: {
        fprintf(file, OPENSCOP_STRING_READ);
        break;
      }
      case OPENSCOP_TYPE_WRITE: {
        fprintf(file, OPENSCOP_STRING_WRITE);
        break;
      }
      case OPENSCOP_TYPE_MAY_WRITE: {
        fprintf(file, OPENSCOP_STRING_MAY_WRITE);
        break;
      }
      default: {
        OPENSCOP_warning("unknown relation type, "
                         "replaced with "OPENSCOP_STRING_UNDEFINED);
        fprintf(file, OPENSCOP_STRING_UNDEFINED);
      }
    }
  }
}


/**
 * openscop_relation_idump function:
 * this function displays a openscop_relation_t structure (*relation) into a
 * file (file, possibly stdout) in a way that trends to be understandable.
 * It includes an indentation level (level) in order to work with others
 * print_structure functions.
 * \param[in] file     File where informations are printed.
 * \param[in] relation The relation whose information has to be printed.
 * \param[in] level    Number of spaces before printing, for each line.
 */
void openscop_relation_idump(FILE * file,
                             openscop_relation_p relation,
                             int level) {
  int i, j, first = 1;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (relation != NULL) {
    fprintf(file, "+-- openscop_relation_t (");
    openscop_relation_print_type(file, relation);
    fprintf(file, ", ");
    openscop_int_dump_precision(file, relation->precision);
    fprintf(file, ")\n");
  }
  else {
    fprintf(file, "+-- NULL relation\n");
  }

  while (relation != NULL) {
    if (! first) {
      // Go to the right level.
      for (j = 0; j < level; j++)
        fprintf(file, "|\t");
      fprintf(file, "|   openscop_relation_t (");
      openscop_relation_print_type(file, relation);
      fprintf(file, ", ");
      openscop_int_dump_precision(file, relation->precision);
      fprintf(file, ")\n");
    }
    else
      first = 0;

    // A blank line
    for(j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "%d %d %d %d %d %d\n",
            relation->nb_rows,        relation->nb_columns,
            relation->nb_output_dims, relation->nb_input_dims,
            relation->nb_local_dims,  relation->nb_parameters);

    // Display the relation.
    for (i = 0; i < relation->nb_rows; i++) {
      for (j = 0; j <= level; j++)
        fprintf(file, "|\t");

      fprintf(file, "[ ");

      for (j = 0; j < relation->nb_columns; j++) {
        openscop_int_print(file, relation->precision, relation->m[i], j);
        fprintf(file, " ");
      }

      fprintf(file, "]\n");
    }

    relation = relation->next;

    // Next line.
    if (relation != NULL) {
      for (j = 0; j <= level; j++)
        fprintf(file, "|\t");
      fprintf(file, "|\n");
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
 * openscop_relation_dump function:
 * this function prints the content of a openscop_relation_t structure
 * (*relation) into a file (file, possibly stdout).
 * \param[in] file     File where informations are printed.
 * \param[in] relation The relation whose information have to be printed.
 */
void openscop_relation_dump(FILE * file, openscop_relation_p relation) {
  openscop_relation_idump(file, relation, 0);
}


#if 0
/**
 * openscop_relation_expression_element function:
 * this function returns a string containing the printing of a value (possibly
 * an iterator or a parameter with its coefficient or a constant).
 * \param[in]     val       Address of the coefficient or constant value.
 * \param[in]     precision The precision of the value.
 * \param[in,out] first     Pointer to a boolean set to 1 if the current value
 *                          is the first of an expresion, 0 otherwise (maybe
 *                          updated).
 * \param[in]     cst       A boolean set to 1 if the value is a constant,
 *                          0 otherwise.
 * \param[in]     name      String containing the name of the element.
 * \return A string that contains the printing of a value.
 */
static
char * openscop_relation_expression_element(void * val,
                                            int precision, int * first,
                                            int cst, char * name) {
  char * temp = (char *)malloc(OPENSCOP_MAX_STRING * sizeof(char));
  char * body = (char *)malloc(OPENSCOP_MAX_STRING * sizeof(char));
  char * sval = (char *)malloc(OPENSCOP_MAX_STRING * sizeof(char));
  
  body[0] = '\0';
  sval[0] = '\0';

  // statements for the 'normal' processing.
  if (openscop_int_notzero(val) && (!cst)) {
    if ((*first) || openscop_int_neg(val)) {
      if (OPENSCOP_INT_one_p(val)) {         // case 1
        sprintf(sval, "%s", name);
      }
      else {
        if (OPENSCOP_INT_mone_p(val)) {      // case -1
          sprintf(sval, "-%s", name);
        }
	else {                          // default case
	  OPENSCOP_INT_sprint(sval, OPENSCOP_FMT_TXT, val);
	  sprintf(temp, "*%s", name);
	  strcat(sval, temp);
        }
      }
      *first = 0;
    }
    else {
      if (OPENSCOP_INT_one_p(val)) {
        sprintf(sval, "+%s", name);
      }
      else {
        sprintf(sval, "+");
	OPENSCOP_INT_sprint(temp, OPENSCOP_FMT_TXT, val);
	strcat(sval, temp);
	sprintf(temp, "*%s", name);
	strcat(sval, temp);
      }
    }
  }
  else {
    if (cst) {
      if ((OPENSCOP_INT_zero_p(val) && (*first)) || OPENSCOP_INT_neg_p(val))
        OPENSCOP_INT_sprint(sval, OPENSCOP_FMT_TXT, val);
      if (OPENSCOP_INT_pos_p(val)) {
        if (!(*first)) {
	  OPENSCOP_INT_sprint(sval, "+"OPENSCOP_FMT_TXT, val); // Block macro !
	}
	else {
          OPENSCOP_INT_sprint(sval, OPENSCOP_FMT_TXT, val);
        }
      }
    }
  }
  free(temp);
  free(body);

  return(sval);
}


/**
 * openscop_relation_expression function:
 * this function returns a string corresponding to an affine expression
 * stored at the "row"^th row of the relation pointed by "relation".
 * \param[in] relation A set of linear expressions.
 * \param[in] row      The row corresponding to the expression.
 * \param[in] names    The textual names of the various elements.
 *                     Set to NULL if printing comments is not needed.
 * \return A string that contains the printing of an affine expression.
 */
char * openscop_relation_expression(openscop_relation_p relation,
                                    int row, openscop_names_p names) {
  int i, first = 1;
  char * sval;
  char * sline = (char *)malloc(OPENSCOP_MAX_STRING * sizeof(char));
  sline[0] = '\0';

  // First the iterator part.
  for (i = 1; i <= names->nb_iterators; i++) {
    sval = openscop_relation_expression_element(
        &(relation->m[row][i]), relation->precision, &first, 0,
        names->iterators[i-1]);
    strcat(sline, sval);
    free(sval);
  }

  // Next the local dims part.
  for (i = names->nb_iterators + 1;
       i <= names->nb_iterators + names->nb_localdims; i++) {
    sval = openscop_relation_expression_element(
        &(relation->m[row][i]), relation->precision, &first, 0,
	names->localdims[i - names->nb_iterators - 1]);
    strcat(sline, sval);
    free(sval);
  }

  // Next the parameter part.
  for (i = names->nb_iterators + names->nb_localdims + 1;
       i <= names->nb_iterators + names->nb_localdims + names->nb_parameters;
       i++) {
    sval = openscop_relation_expression_element(
        &(relation->m[row][i]), relation->precision, &first, 0,
	names->parameters[i - names->nb_iterators - names->nb_localdims - 1]);
    strcat(sline, sval);
    free(sval);
  }

  // Finally the constant part (yes, I reused it).
  sval = openscop_relation_expression_element(
      &(relation->m[row][i]), relation->precision, &first, 1, NULL);
  strcat(sline, sval);
  free(sval);

  return sline;
}


/**
 * openscop_relation_properties function:
 * this function returns, through its parameters, the values of the relation
 * attributes (nb_iterators, nb_parameters etc), depending on its value and
 * its type. The array identifier 0 is used when there is no array
 * identifier (AND this is OK), OPENSCOP_UNDEFINED is used to report it
 * is impossible to provide the property while it should.
 * This function is not intended for checking, the input relation should be
 * correct.
 * \param[in]  relation      The relation to extract property values.
 * \param[out] nb_parameters Number of parameter property.
 * \param[out] nb_iterators  Number of iterators property.
 * \param[out] nb_scattdims  Number of scattering dimensions property.
 * \param[out] nb_localdims  Number of local dimensions property.
 * \param[out] array_id      Array identifier property.
 */
static
void openscop_relation_properties(openscop_relation_p relation,
                                int * nb_parameters,
                                int * nb_iterators,
                                int * nb_scattdims,
                                int * nb_localdims,
                                int * array_id) {

  int type;
 
  *nb_parameters = OPENSCOP_UNDEFINED;
  *nb_iterators  = OPENSCOP_UNDEFINED;
  *nb_scattdims  = OPENSCOP_UNDEFINED;
  *nb_localdims  = OPENSCOP_UNDEFINED;
  *array_id      = OPENSCOP_UNDEFINED;
 
  if (relation == NULL)
    return;

  if (openscop_relation_is_access(relation))
    type = OPENSCOP_TYPE_ACCESS;
  else
    type = relation->type;

  // There is some redundancy but I believe the code is cleaner this way.
  switch (type) {
    case OPENSCOP_TYPE_CONTEXT: {
      *nb_parameters = relation->nb_parameters;
      *nb_iterators  = 0;
      *nb_scattdims  = 0;
      *nb_localdims  = relation->nb_local_dims;
      *array_id      = 0;
      break;
    }
    case OPENSCOP_TYPE_DOMAIN: {
      *nb_parameters = relation->nb_parameters;
      *nb_iterators  = relation->nb_output_dims;
      *nb_scattdims  = 0;
      *nb_localdims  = relation->nb_local_dims;
      *array_id      = 0;
      break;
    }
    case OPENSCOP_TYPE_SCATTERING: {
      *nb_parameters = relation->nb_parameters;
      *nb_iterators  = relation->nb_input_dims;
      *nb_scattdims  = relation->nb_output_dims;
      *nb_localdims  = relation->nb_local_dims;
      *array_id      = 0;
      break;
    }
    case OPENSCOP_TYPE_ACCESS: {
      *nb_parameters = relation->nb_parameters;
      *nb_iterators  = relation->nb_input_dims;
      *nb_scattdims  = 0;
      *nb_localdims  = relation->nb_local_dims;
      *array_id      = openscop_relation_get_array_id(relation);
      break;
    }
  }
}


/**
 * openscop_relation_printable_comments function:
 * this function returns 1 if we can print safely the comments for the
 * relation provided as parameter (in the OpenScop file), 0 otherwise.
 * \param[in] relation The relation we want to know if we can print comments.
 * \param[in] names    The names used for comment printing.
 * \return 1 if we can print the comments safely, 0 otherwise.
 */
static
int openscop_relation_printable_comments(openscop_relation_p relation,
                                         openscop_names_p names) {
  int nb_parameters;
  int nb_iterators;
  int nb_scattdims;
  int nb_localdims;
  int array_id;
 
  if ((relation == NULL) || (names == NULL))
    return 0;

  // TODO: remove this !!!
  // Temporarily deactivate comments, to finish OpenScop RFC first.
  return 0;

  // We cannot print comments if the names are not textual.
  if (names->textual != 1)
    return 0;

  // We cannot print comments if the relation is not of one known type.
  if (!(relation->type == OPENSCOP_TYPE_DOMAIN) &&
      !(relation->type == OPENSCOP_TYPE_SCATTERING) &&
      !(relation->type == OPENSCOP_TYPE_ACCESS))
    return 0;

  // We cannot print comments if we are not sure we have enough names.
  nb_parameters = names->nb_parameters;
  openscop_relation_properties(relation, &nb_parameters, &nb_iterators,
                               &nb_scattdims, &nb_localdims, &array_id);

  if ((nb_parameters == OPENSCOP_UNDEFINED)   ||
      (nb_iterators  == OPENSCOP_UNDEFINED)   ||
      (nb_scattdims  == OPENSCOP_UNDEFINED)   ||
      (nb_localdims  == OPENSCOP_UNDEFINED)   ||
      (array_id      == OPENSCOP_UNDEFINED)   ||
      (nb_parameters >  names->nb_parameters) ||
      (nb_iterators  >  names->nb_iterators)  ||
      (nb_scattdims  >  names->nb_scattdims)  ||
      (nb_localdims  >  names->nb_localdims)  ||
      (array_id      >  names->nb_arrays)) {
    
    OPENSCOP_warning("something is wrong with the names or "
                     "an array identifier, printing comments deactivated");
    return 0;
  }

  return 1;
}


/**
 * openscop_relation_print_comment function:
 * this function prints a comment corresponding to a constraint of a relation,
 * according to its type. This function does not check that printing the
 * comment is possible (i.e., are there enough names ?), hence it is the
 * responsibility of the user to ensure he/she can call this function safely.
 * \param[in] file     File where informations are printed.
 * \param[in] relation The relation for which a comment has to be printed.
 * \param[in] row      The constrain row for which a comment has to be printed.
 * \param[in] names    The textual names of the various elements.
 */ 
static
void openscop_relation_print_comment(FILE * file,
                                     openscop_relation_p relation, int row,
                                     openscop_names_p names) {
  int k;
  int type;
  char * expression;
  
  if (openscop_relation_is_access(relation))
    type = OPENSCOP_TYPE_ACCESS;
  else
    type = relation->type;

  switch (type) {
    case OPENSCOP_TYPE_DOMAIN: {
      expression = openscop_relation_expression(relation, row, names);
      fprintf(file, "   ## %s", expression);
      free(expression);
      if (OPENSCOP_INT_zero_p(relation->m[row][0]))
        fprintf(file, " == 0");
      else
        fprintf(file, " >= 0");
      break;
    }
    case OPENSCOP_TYPE_SCATTERING: {
      expression = openscop_relation_expression(relation, row, names);
      fprintf(file, "   ## %s", expression);
      free(expression);
      break;
    }
    case OPENSCOP_TYPE_ACCESS: {
      //TODO: works only for matrix: use openscop_relation_get_array_id
      if (OPENSCOP_INT_notzero_p(relation->m[row][0])) {
        if (strncmp(names->arrays[OPENSCOP_INT_get_si(relation->m[row][0]) - 1],
                    OPENSCOP_FAKE_ARRAY, strlen(OPENSCOP_FAKE_ARRAY)))
          fprintf(file, "   ## %s",
                  names->arrays[OPENSCOP_INT_get_si(relation->m[row][0]) - 1]);
        k = row;
        do {
          expression = openscop_relation_expression(relation, k, names);
          fprintf(file, "[%s]", expression);
          free(expression);
          k++;
        }
        while ((k < relation->nb_rows) &&
               OPENSCOP_INT_zero_p(relation->m[k][0]));
      }
      else {
        fprintf(file, "   ##");
      }
    }
  }
}
#endif

/**
 * openscop_relation_print function:
 * this function prints the content of an openscop_relation_t structure
 * (*relation) into a file (file, possibly stdout) in the OpenScop format.
 * \param[in] file     File where informations are printed.
 * \param[in] relation The relation whose information has to be printed.
 */
void openscop_relation_print(FILE * file,
                             openscop_relation_p relation) {
  int i, j;
  int part, nb_parts;
  int printable_comments;
  openscop_relation_p r;

  if (relation == NULL) {
    fprintf(file, "# NULL relation\n");
    return;
  }

  //printable_comments = openscop_relation_printable_comments(relation, names); 
  printable_comments = 0;

  // Count the number of parts in the union and print it if it is not 1.
  r = relation;
  nb_parts = 0;
  while (r != NULL) {
    nb_parts++;
    r = r->next;
  }

  if (nb_parts > 0) {
    openscop_relation_print_type(file, relation);
    fprintf(file, "\n");
  }

  if (nb_parts > 1)
    fprintf(file, "# Union with %d parts\n%d\n", nb_parts, nb_parts);

  // Print each part of the union.
  for (part = 1; part <= nb_parts; part++) {
    if (nb_parts > 1)
      fprintf(file, "# Union part No.%d\n", part);
    if ((relation->nb_output_dims == OPENSCOP_UNDEFINED) && 
        (relation->nb_input_dims  == OPENSCOP_UNDEFINED) && 
        (relation->nb_local_dims  == OPENSCOP_UNDEFINED) && 
        (relation->nb_parameters  == OPENSCOP_UNDEFINED)) 
      fprintf(file, "%d %d\n", relation->nb_rows, relation->nb_columns);
    else
      fprintf(file, "%d %d %d %d %d %d\n",
              relation->nb_rows,        relation->nb_columns,
              relation->nb_output_dims, relation->nb_input_dims,
              relation->nb_local_dims,  relation->nb_parameters);

    for (i = 0; i < relation->nb_rows; i++) {
      for (j = 0; j < relation->nb_columns; j++) {
        openscop_int_print(file, relation->precision, relation->m[i], j);
        fprintf(file, " ");
      }

      //if (printable_comments)
      //  openscop_relation_print_comment(file, relation, i, names);

      fprintf(file, "\n");
    }
    relation = relation->next;
  }
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/**
 * openscop_relation_read_type function:
 * this function reads a textual relation type and returns its integer
 * counterpart.
 * \param[in] file The input stream.
 * \return The relation type.
 */
static
int openscop_relation_read_type(FILE * file) {
  int type;
  openscop_strings_p strings;
  
  strings = openscop_strings_read(file);
  if (openscop_strings_size(strings) > 1) {
    OPENSCOP_warning("uninterpreted information (after the relation type)");
  }
  if (openscop_strings_size(strings) == 0)
    OPENSCOP_error("no relation type");
 
  if (!strcmp(strings->string[0], OPENSCOP_STRING_UNDEFINED)) {
    type = OPENSCOP_UNDEFINED;
    goto return_type;
  }

  if (!strcmp(strings->string[0], OPENSCOP_STRING_CONTEXT)) {
    type = OPENSCOP_TYPE_CONTEXT; 
    goto return_type;
  }

  if (!strcmp(strings->string[0], OPENSCOP_STRING_DOMAIN)) {
    type = OPENSCOP_TYPE_DOMAIN; 
    goto return_type;
  }

  if (!strcmp(strings->string[0], OPENSCOP_STRING_SCATTERING)) {
    type = OPENSCOP_TYPE_SCATTERING; 
    goto return_type;
  }

  if (!strcmp(strings->string[0], OPENSCOP_STRING_READ)) {
    type = OPENSCOP_TYPE_READ; 
    goto return_type;
  }

  if (!strcmp(strings->string[0], OPENSCOP_STRING_WRITE)) {
    type = OPENSCOP_TYPE_WRITE; 
    goto return_type;
  }

  if (!strcmp(strings->string[0], OPENSCOP_STRING_MAY_WRITE)) {
    type = OPENSCOP_TYPE_MAY_WRITE; 
    goto return_type;
  }

  OPENSCOP_error("relation type not supported");

return_type:
  openscop_strings_free(strings);
  return type;
}


/**
 * openscop_relation_read function:
 * this function reads a relation into a file (foo, posibly stdin) and
 * returns a pointer this relation. The relation is set to the maximum
 * available precision.
 * \param[in] file The input stream.
 * \return A pointer to the relation structure that has been read.
 */
openscop_relation_p openscop_relation_read(FILE * foo) {
  int i, j, k, n, read = 0;
  int nb_rows, nb_columns;
  int nb_output_dims, nb_input_dims, nb_local_dims, nb_parameters;
  int nb_union_parts = 1;
  int may_read_nb_union_parts = 1;
  int read_properties = 1;
  int first = 1;
  int type;
  int precision = openscop_util_get_precision();
  char * c, s[OPENSCOP_MAX_STRING], str[OPENSCOP_MAX_STRING];
  openscop_relation_p relation, relation_union = NULL, previous = NULL;

  type = openscop_relation_read_type(foo);

  // Read each part of the union (the number of parts may be updated inside)
  for (k = 0; k < nb_union_parts; k++) {
    // Read the number of union parts or the properties of the union part
    while (read_properties) {
      read_properties = 0;

      // Read relation properties.
      c = openscop_util_skip_blank_and_comments(foo, s);
      read = sscanf(c, " %d %d %d %d %d %d", &nb_rows, &nb_columns,
                                             &nb_output_dims, &nb_input_dims,
                                             &nb_local_dims, &nb_parameters);
    
      if (((read != 1) && (read != 6)) ||
          ((read == 1) && (may_read_nb_union_parts != 1)))
        OPENSCOP_error("not 1 or 6 integers on the first relation line");

      if (read == 1) {
        // Only one number means a union and is the number of parts.
        nb_union_parts = nb_rows;
        if (nb_union_parts < 1)
          OPENSCOP_error("negative nb of union parts");
        
        // Allow to read the properties of the first part of the union.
        read_properties = 1;
      }

      may_read_nb_union_parts = 0;
    }

    // Allocate the union part and fill its properties.
    relation = openscop_relation_pmalloc(precision, nb_rows, nb_columns);
    relation->type           = type;
    relation->nb_output_dims = nb_output_dims;
    relation->nb_input_dims  = nb_input_dims;
    relation->nb_local_dims  = nb_local_dims;
    relation->nb_parameters  = nb_parameters;

    // Read the matrix of constraints.
    for (i = 0; i < relation->nb_rows; i++) {
      c = openscop_util_skip_blank_and_comments(foo, s);
      if (c == NULL)
        OPENSCOP_error("not enough rows");

      for (j = 0; j < relation->nb_columns; j++) {
        if (c == NULL || *c == '#' || *c == '\n')
          OPENSCOP_error("not enough columns");
        if (sscanf(c, "%s%n", str, &n) == 0)
          OPENSCOP_error("not enough rows");

        openscop_int_sread(str, precision, relation->m[i], j);
        c += n;
      }
    }
    
    // Build the linked list of union parts.
    if (first == 1) {
      relation_union = relation;
      first = 0;
    }
    else {
      previous->next = relation;
    }

    previous = relation;
    read_properties = 1;
  }

  return relation_union;
}


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/


/**
 * openscop_relation_pmalloc function:
 * (precision malloc) this function allocates the memory space for an
 * openscop_relation_t structure and sets its fields with default values.
 * Then it returns a pointer to the allocated space.
 * \param[in] precision  The precision of the constraint matrix.
 * \param[in] nb_rows    The number of row of the relation to allocate.
 * \param[in] nb_columns The number of columns of the relation to allocate.
 * \return A pointer to an empty relation with fields set to default values
 *         and a ready-to-use constraint matrix.
 */
openscop_relation_p openscop_relation_pmalloc(int precision,
                                              int nb_rows, int nb_columns) {
  openscop_relation_p relation;
  void ** p, * q;
  int i, j;

  OPENSCOP_malloc(relation, openscop_relation_p, sizeof(openscop_relation_t));
  relation->type           = OPENSCOP_UNDEFINED;
  relation->nb_rows        = nb_rows;
  relation->nb_columns     = nb_columns;
  relation->nb_output_dims = OPENSCOP_UNDEFINED;
  relation->nb_input_dims  = OPENSCOP_UNDEFINED;
  relation->nb_parameters  = OPENSCOP_UNDEFINED;
  relation->nb_local_dims  = OPENSCOP_UNDEFINED;
  relation->precision      = precision;
  
  if ((nb_rows == 0) || (nb_columns == 0) ||
      (nb_rows == OPENSCOP_UNDEFINED) || (nb_columns == OPENSCOP_UNDEFINED)) {
    relation->m = NULL;
  } 
  else {
    OPENSCOP_malloc(p, void **, nb_rows * sizeof(void *));
    OPENSCOP_malloc(q, void *,
                    nb_rows * nb_columns * openscop_int_sizeof(precision));
    relation->m = p;
    for (i = 0; i < nb_rows; i++) {
      relation->m[i] = openscop_int_address(precision, q, i * nb_columns);
      for (j = 0; j < nb_columns; j++)
        openscop_int_init_set_si(precision, relation->m[i], j, 0);
    }
  }
 
  relation->next = NULL;

  return relation;
}


/**
 * openscop_relation_malloc function:
 * this function allocates the memory space for an openscop_relation_t
 * structure and sets its fields with default values. Then it returns a
 * pointer to the allocated space. The precision of the constraint matrix
 * elements corresponds to the precision environment variable or to the
 * highest available precision if it is not defined.
 * \param[in] nb_rows    The number of row of the relation to allocate.
 * \param[in] nb_columns The number of columns of the relation to allocate.
 * \return A pointer to an empty relation with fields set to default values
 *         and a ready-to-use constraint matrix.
 */
openscop_relation_p openscop_relation_malloc(int nb_rows, int nb_columns) {
  int precision = openscop_util_get_precision();
  return openscop_relation_pmalloc(precision, nb_rows, nb_columns);
}


/**
 * openscop_relation_free_inside function:
 * this function frees the allocated memory for the inside of a
 * openscop_relation_t structure, i.e. only m.
 * \param[in] relation The pointer to the relation we want to free internals.
 */
void openscop_relation_free_inside(openscop_relation_p relation) {
  int i, nb_elements;
  void * p;

  if (relation == NULL)
    return;

  nb_elements = relation->nb_rows * relation->nb_columns;
  
  if (nb_elements > 0)
    p = relation->m[0];
  
  for (i = 0; i < nb_elements; i++)
    openscop_int_clear(relation->precision, p, i);

  if (relation->m != NULL) {
    if (nb_elements > 0)
      free(relation->m[0]);
    free(relation->m);
  }
}


/**
 * openscop_relation_free function:
 * this function frees the allocated memory for an openscop_relation_t
 * structure.
 * \param[in] relation The pointer to the relation we want to free.
 */
void openscop_relation_free(openscop_relation_p relation) {
  openscop_relation_p tmp;
  
  if (relation == NULL)
    return;

  while (relation != NULL) {
    tmp = relation->next;
    openscop_relation_free_inside(relation);
    free(relation);
    relation = tmp;
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_relation_ncopy function:
 * this functions builds and returns a "hard copy" (not a pointer copy) of a
 * openscop_relation_t data structure such that the copy is restricted to the
 * "n" first rows of the relation. This applies to all the parts in the case
 * of a relation union.
 * \param[in] relation The pointer to the relation we want to copy.
 * \param[in] n        The number of row of the relation we want to copy (the
 *                     special value -1 means "all the rows").
 * \return A pointer to the full copy of the relation union restricted to the
 *         first n rows of constraint matrix for each part of the union.
 */
openscop_relation_p openscop_relation_ncopy(openscop_relation_p relation,
                                            int n) {
  int i, j;
  int first = 1, all_rows = 0;
  openscop_relation_p copy = NULL, node, previous = NULL;

  if (n == -1)
    all_rows = 1;

  while (relation != NULL) {
    if (all_rows)
      n = relation->nb_rows;

    if (n > relation->nb_rows)
      OPENSCOP_error("not enough rows to copy in the relation");

    node = openscop_relation_pmalloc(relation->precision,
                                     n, relation->nb_columns);
    node->type           = relation->type;
    node->nb_output_dims = relation->nb_output_dims;
    node->nb_input_dims  = relation->nb_input_dims;
    node->nb_local_dims  = relation->nb_local_dims;
    node->nb_parameters  = relation->nb_parameters;

    for (i = 0; i < n; i++)
      for (j = 0; j < relation->nb_columns; j++)
        openscop_int_assign(relation->precision,
                            node->m[i], j,
                            relation->m[i], j);
  
    if (first) {
      first = 0;
      copy = node;
      previous = node;
    }
    else {
      previous->next = node;
      previous = previous->next;
    }

    relation = relation->next;
  }

  return copy;
}


/**
 * openscop_relation_clone function:
 * this function builds and returns a "hard copy" (not a pointer copy) of an
 * openscop_relation_t data structure (the full union of relation).
 * \param[in] relation The pointer to the relation we want to copy.
 * \return A pointer to the copy of the union of relations.
 */
openscop_relation_p openscop_relation_clone(openscop_relation_p relation) {
  if (relation == NULL)
    return NULL;

  return openscop_relation_ncopy(relation, -1);
}


/**
 * openscop_relation_replace_vector function:
 * this function replaces the "row"^th row of a relation "relation" with the
 * vector "vector". It directly updates the relation union part pointed
 * by "relation" and this part only.
 * \param[in,out] relation The relation we want to replace a row.
 * \param[in]     vector   The vector that will replace a row of the relation.
 * \param[in]     row      The row of the relation to be replaced.
 */
void openscop_relation_replace_vector(openscop_relation_p relation,
                                      openscop_vector_p vector, int row) {
  int i;

  if ((relation == NULL) || (vector == NULL)     ||
      (relation->precision != vector->precision) ||
      (relation->nb_columns != vector->size)     ||
      (row >= relation->nb_rows) || (row < 0))
    OPENSCOP_error("vector cannot replace relation row");

  for (i = 0; i < vector->size; i++)
    openscop_int_assign(relation->precision,
                        relation->m[row], i,
                        vector->v, i);
}


/**
 * openscop_relation_add_vector function:
 * this function adds (meaning, +) a vector to the "row"^th row of a
 * relation "relation". It directly updates the relation union part pointed
 * by "relation" and this part only.
 * \param[in,out] relation The relation we want to add a vector to a row.
 * \param[in]     vector   The vector that will replace a row of the relation.
 * \param[in]     row      The row of the relation to be replaced.
 */
void openscop_relation_add_vector(openscop_relation_p relation,
                                  openscop_vector_p vector, int row) {
  int i;

  if ((relation == NULL) || (vector == NULL)     ||
      (relation->precision != vector->precision) ||
      (relation->nb_columns != vector->size)     ||
      (row >= relation->nb_rows) || (row < 0))
    OPENSCOP_error("vector cannot be added to relation");

  if (openscop_int_get_si(relation->precision, relation->m[row], 0) == 0)
    openscop_int_assign(relation->precision,
                        relation->m[row], 0,
                        vector->v, 0);

  for (i = 1; i < vector->size; i++)
    openscop_int_add(relation->precision,
                     relation->m[row], i,
                     relation->m[row], i,
                     vector->v, i);
}


/**
 * openscop_relation_sub_vector function:
 * this function subtracts the vector "vector" to the "row"^th row of
 * a relation "relation. It directly updates the relation union part pointed
 * by "relation" and this part only.
 * \param[in,out] relation The relation where to subtract a vector to a row.
 * \param[in]     vector   The vector to subtract to a relation row.
 * \param[in]     row      The row of the relation to subtract the vector.
 */
void openscop_relation_sub_vector(openscop_relation_p relation,
                                  openscop_vector_p vector, int row) {
  int i;

  if ((relation == NULL) || (vector == NULL)     ||
      (relation->precision != vector->precision) ||
      (relation->nb_columns != vector->size)     ||
      (row >= relation->nb_rows) || (row < 0))
    OPENSCOP_error("vector cannot be subtracted to row");

  if (openscop_int_get_si(relation->precision, relation->m[row], 0) == 0)
    openscop_int_assign(relation->precision,
                        relation->m[row], 0,
                        vector->v, 0);

  for (i = 1; i < vector->size; i++)
    openscop_int_sub(relation->precision,
                     relation->m[row], i,
                     relation->m[row], i,
                     vector->v, i);
}


/**
 * openscop_relation_insert_vector function:
 * this function inserts a new row corresponding to the vector "vector" to
 * the relation "relation" by inserting it at the "row"^th row. It directly
 * updates the relation union part pointed by "relation" and this part only.
 * If "vector" (or "relation") is NULL, the relation is left unmodified.
 * \param[in,out] relation The relation we want to extend.
 * \param[in]     vector   The vector that will be added relation.
 * \param[in]     row      The row where to insert the vector.
 */
void openscop_relation_insert_vector(openscop_relation_p relation,
                                     openscop_vector_p vector, int row) {
  openscop_relation_p temp;

  temp = openscop_relation_from_vector(vector);
  openscop_relation_insert_constraints(relation, temp, row);
  openscop_relation_free(temp);
}


/**
 * openscop_relation_from_vector function:
 * this function converts a vector "vector" to a relation with a single row
 * and returns a pointer to that relation.
 * \param[in] vector The vector to convert to a relation.
 * \return A pointer to a relation resulting from the vector conversion.
 */
openscop_relation_p openscop_relation_from_vector(openscop_vector_p vector) {
  openscop_relation_p relation;

  if (vector == NULL)
    return NULL;

  relation = openscop_relation_pmalloc(vector->precision, 1, vector->size);
  openscop_relation_replace_vector(relation, vector, 0);
  return relation;
}


/**
 * openscop_relation_replace_constraints function:
 * this function replaces some rows of a relation "r1" with the rows of
 * the relation "r2". It begins at the "row"^th row of "r1". It directly
 * updates the relation union part pointed by "r1" and this part only.
 * \param[in,out] r1  The relation we want to change some rows.
 * \param[in]     r2  The relation containing the new rows.
 * \param[in]     row The first row of the relation r1 to be replaced.
 */
void openscop_relation_replace_constraints(openscop_relation_p r1,
                                           openscop_relation_p r2, int row) {
  int i, j;

  if ((r1 == NULL) || (r2 == NULL)       ||
      (r1->precision != r2->precision)   ||
      (r1->nb_columns != r1->nb_columns) ||
      ((row + r2->nb_rows) > r1->nb_rows) || (row < 0))
    OPENSCOP_error("relation rows could not be replaced");

  for (i = 0; i < r2->nb_rows; i++)
    for (j = 0; j < r2->nb_columns; j++)
      openscop_int_assign(r1->precision, r1->m[i+row], j, r2->m[i], j);
}


/**
 * openscop_relation_insert_constraints function:
 * this function adds new rows corresponding to the relation "r1" to
 * the relation "r2" by inserting it at the "row"^th row. It directly
 * updates the relation union part pointed by "r1" and this part only.
 * If "r2" (or "r1") is NULL, the relation is left unmodified.
 * \param[in,out] r1  The relation we want to extend.
 * \param[in]     r2  The relation to be inserted.
 * \param[in]     row The row where to insert the relation
 */
void openscop_relation_insert_constraints(openscop_relation_p r1,
                                          openscop_relation_p r2, int row) {
  int i, j;
  openscop_relation_p temp;

  if ((r1 == NULL) || (r2 == NULL))
    return;

  if ((r1->nb_columns != r2->nb_columns) ||
      (r1->precision != r2->precision)   ||
      (row > r1->nb_rows) || (row < 0))
    OPENSCOP_error("constraints cannot be inserted");

  // We use a temporary relation just to reuse existing functions. Cleaner.
  temp = openscop_relation_pmalloc(r1->precision,
                                   r1->nb_rows + r2->nb_rows,
                                   r1->nb_columns);

  for (i = 0; i < row; i++)
    for (j = 0; j < r1->nb_columns; j++)
      openscop_int_assign(r1->precision, temp->m[i], j, r1->m[i], j);

  openscop_relation_replace_constraints(temp, r2, row);

  for (i = row + r2->nb_rows; i < r2->nb_rows + r1->nb_rows; i++)
    for (j = 0; j < r1->nb_columns; j++)
      openscop_int_assign(r1->precision,
                          temp->m[i], j,
                          r1->m[i-r2->nb_rows], j);

  openscop_relation_free_inside(r1);

  // Replace the inside of relation.
  r1->nb_rows = temp->nb_rows;
  r1->m = temp->m;

  // Free the temp "shell".
  free(temp);
}


/**
 * openscop_relation_concat_constraints function:
 * this function builds a new relation from two relations sent as
 * parameters. The new set of constraints is built as the concatenation
 * of the rows of the first elements of the two relation unions r1 and r2.
 * This means, there is no next field in the result.
 * \param[in] r1  The first relation.
 * \param[in] r2  The second relation.
 * \return A pointer to the relation resulting from the concatenation of
 *         the first elements of r1 and r2.
 */
openscop_relation_p openscop_relation_concat_constraints(
    openscop_relation_p r1,
    openscop_relation_p r2) {
  openscop_relation_p new;

  if (r1 == NULL)
    return openscop_relation_clone(r2);

  if (r2 == NULL)
    return openscop_relation_clone(r1);

  if (r1->nb_columns != r2->nb_columns)
    OPENSCOP_error("incompatible sizes for concatenation");
  
  if (r1->next || r2->next)
    OPENSCOP_warning("relation concatenation is done on the first elements "
                     "of union only");

  new = openscop_relation_pmalloc(r1->precision,
                                  r1->nb_rows + r2->nb_rows,
                                  r1->nb_columns);
  openscop_relation_replace_constraints(new, r1, 0);
  openscop_relation_replace_constraints(new, r2, r1->nb_rows);

  return new;
}


/**
 * openscop_relation_equal function:
 * this function returns true if the two relations provided as parameters
 * are the same, false otherwise.
 * \param[in] r1  The first relation.
 * \param[in] r2  The second relation.
 * \return 1 if r1 and r2 are the same (content-wise), 0 otherwise.
 */
int openscop_relation_equal(openscop_relation_p r1, openscop_relation_p r2) {
  int i, j;

  while ((r1 != NULL) && (r2 != NULL)) {
    if (r1 == r2)
      return 1;

    if ((r1->type           != r2->type)           ||
        (r1->precision      != r2->precision)      ||
        (r1->nb_rows        != r2->nb_rows)        ||
        (r1->nb_columns     != r2->nb_columns)     ||
        (r1->nb_output_dims != r2->nb_output_dims) ||
        (r1->nb_input_dims  != r2->nb_input_dims)  ||
        (r1->nb_local_dims  != r2->nb_local_dims)  ||
        (r1->nb_parameters  != r2->nb_parameters))
      return 0;

    for (i = 0; i < r1->nb_rows; ++i)
      for (j = 0; j < r1->nb_columns; ++j)
        if (openscop_int_ne(r1->precision, r1->m[i], j, r2->m[i], j))
          return 0;

    r1 = r1->next;
    r2 = r2->next;
  }
  
  if (((r1 == NULL) && (r2 != NULL)) || ((r1 != NULL) && (r2 == NULL)))
    return 0;
  
  return 1;
}


/**
 * openscop_relation_check_attribute internal function:
 * This function checks whether an "actual" value is the same as an
 * "expected" value or not. If the expected value is set to
 * OPENSCOP_UNDEFINED, this function sets it to the "actual" value
 * and do not report a difference has been detected.
 * It returns 0 if a difference has been detected, 1 otherwise.
 * \param[in,out] expected Pointer to the expected value (the value is
 *                         modified if it was set to OPENSCOP_UNDEFINED).
 * \param[in]     actual   Value we want to check.
 * \return 0 if the values are not the same while the expected value was
 *         not OPENSCOP_UNDEFINED, 1 otherwise.
 */
static
int openscop_relation_check_attribute(int * expected, int actual) {
  if (*expected != OPENSCOP_UNDEFINED) { 
    if ((actual != OPENSCOP_UNDEFINED) &&
        (actual != *expected)) {
      OPENSCOP_warning("unexpected atribute");
      return 0;
    }
  }
  else {
    *expected = actual;
  }

  return 1;
}


/**
 * openscop_relation_check_nb_columns internal function:
 * This function checks that the number of columns of a relation
 * corresponds to some expected properties (setting an expected property to
 * OPENSCOP_UNDEFINED makes this function unable to detect a problem).
 * It returns 0 if the number of columns seems incorrect or 1 if no problem
 * has been detected.
 * \param[in] relation  The relation we want to check the number of columns.
 * \param[in] expected_nb_output_dims Expected number of output dimensions.
 * \param[in] expected_nb_input_dims  Expected number of input dimensions.
 * \param[in] expected_nb_parameters  Expected number of parameters.
 * \return 0 if the number of columns seems incorrect, 1 otherwise.
 */
static
int openscop_relation_check_nb_columns(openscop_relation_p relation,
                                       int expected_nb_output_dims,
                                       int expected_nb_input_dims,
                                       int expected_nb_parameters) {
  int expected_nb_local_dims, expected_nb_columns;
  
  if ((expected_nb_output_dims != OPENSCOP_UNDEFINED) &&
      (expected_nb_input_dims  != OPENSCOP_UNDEFINED) &&
      (expected_nb_parameters  != OPENSCOP_UNDEFINED)) {
    
    if (relation->nb_local_dims == OPENSCOP_UNDEFINED)
      expected_nb_local_dims = 0;
    else
      expected_nb_local_dims = relation->nb_local_dims;

    expected_nb_columns = expected_nb_output_dims +
                          expected_nb_input_dims  +
                          expected_nb_local_dims  +
                          expected_nb_parameters  +
                          2;
    
    if (expected_nb_columns != relation->nb_columns) {
      OPENSCOP_warning("unexpected number of columns");
      return 0;
    }
  }

  return 1;
}


/**
 * openscop_relation_integrity_check function:
 * this function checks that a relation is "well formed" according to some
 * expected properties (setting an expected value to OPENSCOP_UNDEFINED means
 * that we do not expect a specific value) and what the relation is supposed
 * to represent. It returns 0 if the check failed or 1 if no problem has been
 * detected.
 * \param[in] relation  The relation we want to check.
 * \param[in] type      Semantics about this relation (domain, access...).
 * \param[in] expected_nb_output_dims Expected number of output dimensions.
 * \param[in] expected_nb_input_dims  Expected number of input dimensions.
 * \param[in] expected_nb_parameters  Expected number of parameters.
 * \return 0 if the integrity check fails, 1 otherwise.
 */
int openscop_relation_integrity_check(openscop_relation_p relation,
                                      int expected_type,
                                      int expected_nb_output_dims,
                                      int expected_nb_input_dims,
                                      int expected_nb_parameters) {
  int i;

  // Check the NULL case.
  if (relation == NULL) {
    if ((expected_nb_output_dims != OPENSCOP_UNDEFINED) ||
        (expected_nb_input_dims  != OPENSCOP_UNDEFINED) ||
        (expected_nb_parameters  != OPENSCOP_UNDEFINED)) {
      OPENSCOP_warning("NULL relation with some expected attibutes");
      //return 0;
    }

    return 1;
  }

  // Check the type.
  if (((expected_type != OPENSCOP_TYPE_ACCESS) &&
       (expected_type != relation->type)) ||
      ((expected_type == OPENSCOP_TYPE_ACCESS) &&
       (!openscop_relation_is_access(relation)))) {
    OPENSCOP_warning("wrong type");
    openscop_relation_dump(stderr, relation);
    return 0;
  }

  // Check that relations have no undefined atributes.
  if ((relation->nb_output_dims == OPENSCOP_UNDEFINED) ||
      (relation->nb_input_dims  == OPENSCOP_UNDEFINED) ||
      (relation->nb_local_dims  == OPENSCOP_UNDEFINED) ||
      (relation->nb_parameters  == OPENSCOP_UNDEFINED)) {
    OPENSCOP_warning("all attributes should be defined");
    openscop_relation_dump(stderr, relation);
    return 0;
  }

  // Check that a context has actually 0 output dimensions.
  if ((relation->type == OPENSCOP_TYPE_CONTEXT) &&
      (relation->nb_output_dims != 0)) {
    OPENSCOP_warning("context without 0 as number of output dimensions");
    openscop_relation_dump(stderr, relation);
    return 0;
  }

  // Check that a domain or a context has actually 0 input dimensions.
  if (((relation->type == OPENSCOP_TYPE_DOMAIN) ||
       (relation->type == OPENSCOP_TYPE_CONTEXT)) &&
      (relation->nb_input_dims != 0)) {
    OPENSCOP_warning("domain or context without 0 input dimensions");
    openscop_relation_dump(stderr, relation);
    return 0;
  }

  // Check properties according to expected values (and if expected values
  // are undefined, define them with the first relation part properties).
  if (!openscop_relation_check_attribute(&expected_nb_output_dims,
                                         relation->nb_output_dims) ||
      !openscop_relation_check_attribute(&expected_nb_input_dims,
                                         relation->nb_input_dims)  ||
      !openscop_relation_check_attribute(&expected_nb_parameters,
                                         relation->nb_parameters)) {
    openscop_relation_dump(stderr, relation);
    return 0;
  }

  while (relation != NULL) {

    // Attributes (except the number of local dimensions) should be the same
    // in all parts of the union.
    if ((expected_nb_output_dims != relation->nb_output_dims) ||
        (expected_nb_input_dims  != relation->nb_input_dims)  ||
        (expected_nb_parameters  != relation->nb_parameters)) {
      OPENSCOP_warning("inconsistent attributes");
      openscop_relation_dump(stderr, relation);
      return 0;
    }
   
    // Check whether the number of columns is OK or not.
    if (!openscop_relation_check_nb_columns(relation,
                                            expected_nb_output_dims,
                                            expected_nb_input_dims,
                                            expected_nb_parameters)) {
      openscop_relation_dump(stderr, relation);
      return 0;
    }

    // Check the first column. The first column of a relation part should be
    // made of 0 or 1 only.
    if ((relation->nb_rows > 0) && (relation->nb_columns > 0)) {
      for (i = 0; i < relation->nb_rows; i++) {
        if (!openscop_int_zero(relation->precision, relation->m[i], 0) &&
            !openscop_int_one(relation->precision, relation->m[i], 0)) {
          OPENSCOP_warning("first column of a relation is not "
                           "strictly made of 0 or 1");
          openscop_relation_dump(stderr, relation);
          return 0;
        }
      }
    }

    // Array accesses must provide the array identifier.
    if ((openscop_relation_is_access(relation)) &&
        (openscop_relation_get_array_id(relation) == OPENSCOP_UNDEFINED)) {
      openscop_relation_dump(stderr, relation);
      return 0;
    }

    relation = relation->next;
  }

  return 1;
}


/**
 * openscop_relation_union function:
 * this function builds a new relation from two relations provided
 * as parameters. The new relation is built as an union of the
 * two relations: the list of constraint sets are linked together.
 * \param[in] r1 The first relation.
 * \param[in] r2 The second relation.
 * \return A new relation corresponding to the union of r1 and r2.
 */
openscop_relation_p openscop_relation_union(openscop_relation_p r1,
                                            openscop_relation_p r2) {
  openscop_relation_p copy1, copy2, tmp;
  
  if ((r1 == NULL) && (r2 == NULL))
    return NULL;
  
  copy1 = openscop_relation_clone(r1);
  copy2 = openscop_relation_clone(r2);

  if ((r1 != NULL) && (r2 == NULL))
    return copy1;
    
  if ((r1 == NULL) && (r2 != NULL))
    return copy2;

  tmp = copy1;
  while (tmp->next != NULL)
    tmp = tmp->next;

  tmp->next = copy2;
  return copy1;
}


/** 
 * openscop_relation_set_type function:
 * this function sets the type of each relation union part in the relation
 * to the one provided as parameter.
 * \param relation The relation to set the type.
 * \param type     The type.
 */
void openscop_relation_set_type(openscop_relation_p relation, int type) {

  while (relation != NULL) {
    relation->type = type;
    relation = relation->next;
  }
}


/**
 * openscop_relation_get_array_id function:
 * this function returns the array identifier in a relation with access type
 * It returns OPENSCOP_UNDEFINED if it is not able to find it (in particular
 * if there are irregularities in the relation).
 * \param[in] relation The relation where to find an array identifier.
 * \return The array identifier in the relation or OPENSCOP_UNDEFINED.
 */
int openscop_relation_get_array_id(openscop_relation_p relation) {
  int i;
  int first = 1;
  int array_id = OPENSCOP_UNDEFINED;
  int reference_array_id = OPENSCOP_UNDEFINED;
  int nb_array_id;
  int row_id = 0;
  int precision;

  if (relation == NULL)
    return OPENSCOP_UNDEFINED;
  
  if (!openscop_relation_is_access(relation)) {
    OPENSCOP_warning("asked for an array id of non-array relation");
    return OPENSCOP_UNDEFINED;
  }
  
  while (relation != NULL) {
    precision = relation->precision;

    // There should be room to store the array identifier.
    if ((relation->nb_rows < 1) ||
        (relation->nb_columns < 3)) {
      OPENSCOP_warning("no array identifier in an access function");
      return OPENSCOP_UNDEFINED;
    }

    // Array identifiers are m[i][#columns -1] / m[i][1], with i the only row
    // where m[i][1] is not 0.
    // - check there is exactly one row such that m[i][1] is not 0,
    // - check the whole ith row if full of 0 except m[i][1] and the id,
    // - check that (m[i][#columns -1] % m[i][1]) == 0,
    // - check that (-m[i][#columns -1] / m[i][1]) > 0.
    nb_array_id = 0;
    for (i = 0; i < relation->nb_rows; i++) {
      if (!openscop_int_zero(precision, relation->m[i], 1)) {
        nb_array_id ++;
        row_id = i;
      }
    }
    if (nb_array_id == 0) {
      OPENSCOP_warning("no array identifier in an access function");
      return OPENSCOP_UNDEFINED;
    }
    if (nb_array_id > 1) {
      OPENSCOP_warning("several array identifiers in one access function");
      return OPENSCOP_UNDEFINED;
    }
    for (i = 0; i < relation->nb_columns - 1; i++) {
      if ((i != 1) && !openscop_int_zero(precision, relation->m[row_id], i)) {
        OPENSCOP_warning("non integer array identifier");
        return OPENSCOP_UNDEFINED;
      }
    }
    if (!openscop_int_divisible(precision,
                                relation->m[row_id], relation->nb_columns - 1,
                                relation->m[row_id], 1)) {
      OPENSCOP_warning("rational array identifier");
      return OPENSCOP_UNDEFINED;
    }
    array_id = -openscop_int_get_si(precision,
                                    relation->m[row_id],
                                    relation->nb_columns - 1);
    array_id /= openscop_int_get_si(precision, relation->m[row_id], 1);
    if (array_id <= 0) {
      OPENSCOP_warning("negative or 0 identifier in access function");
      return OPENSCOP_UNDEFINED;
    }

    // Unions of accesses are allowed, but they should refer at the same array.
    if (first) {
      reference_array_id = array_id;
      first = 0;
    }
    else {
      if (reference_array_id != array_id) {
        OPENSCOP_warning("inconsistency of array identifiers in an "
                         "union of access relations");
        return OPENSCOP_UNDEFINED;
      }
    }
    
    relation = relation->next;
  }

  return array_id;
}


/**
 * openscop_relation_is_access function:
 * this function returns 1 if the relation corresponds to an access relation,
 * whatever its precise type (read, write etc.), 0 otherwise.
 * \param relation The relation to check wheter it is an access relation or not.
 * \return 1 if the relation is an access relation, 0 otherwise.
 */
int openscop_relation_is_access(openscop_relation_p relation) {

  if (relation == NULL)
    return 0;
  
  if ((relation->type == OPENSCOP_TYPE_ACCESS)    ||
      (relation->type == OPENSCOP_TYPE_READ)      ||
      (relation->type == OPENSCOP_TYPE_WRITE)     ||
      (relation->type == OPENSCOP_TYPE_MAY_WRITE))
    return 1;

  return 0;
}



