
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                        relation_list.c                          **
     **-----------------------------------------------------------------**
     **                   First version: 08/10/2010                     **
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
# include <openscop/relation_list.h>


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * openscop_relation_list_print_structure function:
 * Displays a openscop_relation_list_t structure (a list of relations) into a
 * file (file, possibly stdout). See openscop_relation_print_structure for
 * more details.
 * \param file   File where informations are printed.
 * \param l	 The list of relations whose information have to be printed.
 * \param level  Number of spaces before printing, for each line.
 */
void
openscop_relation_list_print_structure(FILE * file, openscop_relation_list_p l,
				       int level)
{
  int j, first = 1;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file,"|\t");

  if (l != NULL)
    fprintf(file, "+-- openscop_relation_list_t\n");
  else
    fprintf(file, "+-- NULL relation list\n");

  while (l != NULL)
  {
    if (!first)
    {
      // Go to the right level.
      for (j = 0; j < level; j++)
        fprintf(file, "|\t");
      fprintf(file, "|   openscop_relation_list_t\n");
    }
    else
      first = 0;

    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    // Print a relation.
    openscop_relation_print_structure(file, l->elt, level+1);

    l = l->next;

    // Next line.
    if (l != NULL)
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
 * openscop_relation_list_print function:
 * This function prints the content of a openscop_relation_list_t into
 * a file (file, possibly stdout).
 * \param file File where informations are printed.
 * \param list The relation whose information have to be printed.
 */
void
openscop_relation_list_print(FILE * file, openscop_relation_list_p list)
{
  openscop_relation_list_print_structure(file, list, 0);
}


/**
 * openscop_relation_list_print_openscop function:
 * This function prints the content of a openscop_relation_list_t structure
 * into a file (file, possibly stdout) in the OpenScop format.
 * \param file  File where informations are printed.
 * \param list  The relation list whose information have to be printed.
 * \param type  Semantic about this relation (domain, access...).
 * \param names The textual names of the various elements. Is is important
 *              that names->nb_parameters is exact if the matrix
 *              representation is used. Set to NULL if printing comments
 *              is not needed.
 */
void
openscop_relation_list_print_openscop(FILE * file,
                                      openscop_relation_list_p list,
                                      int type, openscop_names_p names)
{
  int i;
  openscop_relation_list_p head = list;

  // Count the number of elements in the list.
  for (i = 0; list; list = list->next, i++)
    continue;
  
  // Print it.
  if (i > 1)
    fprintf(file,"# List of %d elements\n%d\n", i, i);
  else
    fprintf(file,"# List of %d element \n%d\n", i, i);

  // Print each element of the relation list.
  i = 0;
  while (head)
  {
    fprintf(file, "# List element No.%d\n", i);
    openscop_relation_print_openscop(file, head->elt, type, names);
    head = head->next;
    i++;
  }
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/**
 * openscop_relation_list_read function:
 * This function reads a list of relations into a file (foo,
 * posibly stdin) and returns a pointer this relation list.
 * \param file  The input stream.
 * \return A pointer to the relation list structure that has been read.
 */
openscop_relation_list_p
openscop_relation_list_read(FILE* file)
{
  char s[OPENSCOP_MAX_STRING];
  int i;
  openscop_relation_list_p list;
  openscop_relation_list_p res;
  int nb_mat;

  // Skip blank/commented lines.
  while (fgets(s, OPENSCOP_MAX_STRING, file) == 0 || s[0] == '#' ||
      isspace(s[0]))
    continue;
  
  // Read the number of relations to read.
  sscanf(s, "%d", &nb_mat);

  // Allocate the header of the list and start reading each element.
  res = list = openscop_relation_list_malloc();
  for (i = 0; i < nb_mat; ++i)
  {
    list->elt = openscop_relation_read(file);
    if (i < nb_mat - 1)
      list->next = openscop_relation_list_malloc();
    list = list->next;
  }

  return res;
}


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/


/**
 * openscop_relation_list_malloc function:
 * This function allocates the memory space for a openscop_relation_list_t
 * structure and sets its fields with default values. Then it returns
 * a pointer to the allocated space.
 * \return A pointer to an empty relation list with fields set to default
 *         values.
 */
openscop_relation_list_p
openscop_relation_list_malloc()
{
  openscop_relation_list_p res =
    (openscop_relation_list_p) malloc(sizeof(openscop_relation_list_t));

  if (res == NULL)
  {
    fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
    exit(1);
  }

  res->elt = NULL;
  res->next = NULL;

  return res;
}



/**
 * openscop_relation_list_free function:
 * This function frees the allocated memory for a openscop_relation_list_t
 * structure, and all the relations stored in the list.
 * \param list The pointer to the relation list we want to free.
 */
void
openscop_relation_list_free(openscop_relation_list_p list)
{
  openscop_relation_list_p tmp;

  if (list == NULL)
    return;

  while (list)
  {
    if (list->elt)
      openscop_relation_free(list->elt);
    tmp = list->next;
    free(list);
    list = tmp;
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_relation_list_node function:
 * This function builds an openscop_relation_list_t node and sets its
 * relation element as a copy of the one provided as parameter.
 * \param relation The pointer to the relation to copy/paste in a list node.
 * \return A pointer to a relation list node containing a copy of "relation".
 */
openscop_relation_list_p
openscop_relation_list_node(openscop_relation_p relation)
{
  openscop_relation_list_p new;
  
  new = openscop_relation_list_malloc();
  new->elt = openscop_relation_copy(relation);

  return new;
}


/**
 * openscop_relation_list_copy function:
 * This functions builds and returns a quasi-"hard copy" (not a pointer copy)
 * of a openscop_relation_list_t data structure provided as parameter.
 * \param list  The pointer to the relation list we want to copy.
 * \return A pointer to the full copy of the relation list in parameter.
 */
openscop_relation_list_p
openscop_relation_list_copy(openscop_relation_list_p list)
{
  int first = 1;
  openscop_relation_list_p copy = NULL, node, previous = NULL; 

  while (list != NULL)
  {
    node      = openscop_relation_list_malloc();
    node->elt = openscop_relation_copy(list->elt);

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

    list = list->next;
  }

  return copy;
}


/**
 * openscop_relation_list_concat function:
 * this function builds a new relation list as the concatenation of the
 * two lists sent as parameters.
 * \param l1  The first relation list.
 * \param l2  The second relation list.
 * \return A pointer to the relation list resulting from the concatenation of
 *         l1 and l2.
 */
openscop_relation_list_p
openscop_relation_list_concat(openscop_relation_list_p l1,
                              openscop_relation_list_p l2)
{
  openscop_relation_list_p new, end;

  if (l1 == NULL)
    return openscop_relation_list_copy(l2);

  if (l2 == NULL)
    return openscop_relation_list_copy(l1);

  new = openscop_relation_list_copy(l1);
  end = new;
  while (end->next != NULL)
    end = end->next;
  end->next = openscop_relation_list_copy(l2);

  return new;
}


/**
 * openscop_relation_list_equal function:
 * This function returns true if the two relation lists are the same, false
 * otherwise..
 * \param l1 The first relation list.
 * \param l2 The second relation list.
 * \return 1 if l1 and l2 are the same (content-wise), 0 otherwise.
 */
int
openscop_relation_list_equal(openscop_relation_list_p l1,
                             openscop_relation_list_p l2)
{
  while ((l1 != NULL) && (l2 != NULL))
  {
    if (!openscop_relation_equal(l1->elt, l2->elt))
      return 0;

    l1 = l1->next;
    l2 = l2->next;
  }

  if (((l1 == NULL) && (l2 != NULL)) || ((l1 != NULL) && (l2 == NULL)))
    return 0;
  
  return 1;
}


/**
 * openscop_relation_integrity_check function:
 * This function checks that a list of relation is "well formed" according to
 * some expected properties (setting an expected value to OPENSCOP_UNDEFINED
 * means that we do not expect a specific value) and what the relations are
 * supposed to represent (all relations of a list are supposed to have the
 * same semantics). It returns 0 if the check failed or 1 if no problem has
 * been detected.
 * \param list      The relation list we want to check.
 * \param type      Semantics about this relation (domain, access...).
 * \param expected_nb_output_dims Expected number of output dimensions.
 * \param expected_nb_input_dims  Expected number of input dimensions.
 * \param expected_nb_parameters  Expected number of parameters.
 * \return 0 if the integrity check fails, 1 otherwise.
 */
int
openscop_relation_list_integrity_check(openscop_relation_list_p list,
                                       int type,
                                       int expected_nb_output_dims,
                                       int expected_nb_input_dims,
                                       int expected_nb_parameters)
{
  while (list != NULL)
  {
    // Check the access function.
    if (( openscop_relation_is_matrix(list->elt) &&
         !openscop_relation_integrity_check(list->elt,
                                            type,
                                            OPENSCOP_UNDEFINED,
                                            OPENSCOP_UNDEFINED,
                                            OPENSCOP_UNDEFINED)) ||
        (!openscop_relation_is_matrix(list->elt) &&
         !openscop_relation_integrity_check(list->elt,
                                            type,
                                            expected_nb_output_dims,
                                            expected_nb_input_dims,
                                            expected_nb_parameters)))
    {
      return 0;
    }

    list = list->next;
  }

  return 1;
}

