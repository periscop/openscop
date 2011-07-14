
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                          scop_list.c                            **
     **-----------------------------------------------------------------**
     **                   First version: 14/07/2011                     **
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
# include <openscop/scop_list.h>


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * openscop_scop_list_idump function:
 * this function displays a openscop_scop_list_t structure (*list) into a
 * file (file, possibly stdout) in a way that trends to be understandable.
 * It includes an indentation level (level) in order to work with others
 * print_structure functions.
 * \param[in] file  File where informations are printed.
 * \param[in] list  The scop_list whose information has to be printed.
 * \param[in] level Number of spaces before printing, for each line.
 */
void openscop_scop_list_idump(FILE * file,
                              openscop_scop_list_p list,
                              int level) {
  int j, first = 1;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (list != NULL)
    fprintf(file, "+-- openscop_scop_list_t\n");
  else
    fprintf(file, "+-- NULL scop list\n");

  while (list != NULL) {
    if (!first) {
      // Go to the right level.
      for (j = 0; j < level; j++)
        fprintf(file, "|\t");
      fprintf(file, "|   openscop_scop_list_t\n");
    }
    else
      first = 0;

    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    // Print a relation.
    openscop_scop_idump(file, list->elt, level+1);

    list = list->next;

    // Next line.
    if (list != NULL) {
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
 * openscop_scop_list_dump function:
 * this function prints the content of a openscop_scop_list_t structure
 * (*scop_list) into a file (file, possibly stdout).
 * \param[in] file File where informations are printed.
 * \param[in] list The scop_list whose information have to be printed.
 */
void openscop_scop_list_dump(FILE * file, openscop_scop_list_p list) {
  openscop_scop_list_idump(file, list, 0);
}


/**
 * openscop_scop_list_print function:
 * this function prints the content of an openscop_scop_list_t structure
 * (*list) into a file (file, possibly stdout) in the OpenScop format.
 * \param[in] file  File where informations are printed.
 * \param[in] list  The list whose information has to be printed.
 */
void openscop_scop_list_print(FILE * file, openscop_scop_list_p list) {

  if (list == NULL) {
    fprintf(file,"# NULL scop list\n");
  }
  else {
    while(list != NULL) {
      openscop_scop_print(file, list->elt);
      fprintf(file, "\n");
      list = list->next;
    }
  }
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/**
 * openscop_scop_list_read function:
 * this function reads a scop list into a file (foo, posibly stdin) and
 * returns a pointer this list.
 * \param[in] file The input stream.
 * \return A pointer to the scop list structure that has been read.
 */
openscop_scop_list_p openscop_scop_list_read(FILE * file) {
  openscop_scop_p scop;
  openscop_scop_list_p list = NULL, current = NULL, node;
  int first = 1;

  while ((scop = openscop_scop_read(file)) != NULL) {
    node = openscop_scop_list_malloc();
    node->elt = scop;
    if (first) {
      list = node;
      first = 0;
    }
    else {
      current->next = node;
    }
    current = node;
  }

  return list;
}


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/


/**
 * openscop_scop_list_malloc function:
 * this function allocates the memory space for a openscop_scop_list_t
 * structure and sets its fields with default values. Then it returns a
 * pointer to the allocated space.
 * \return A pointer to an empty scop list with fields set to default values.
 */
openscop_scop_list_p openscop_scop_list_malloc() {
  openscop_scop_list_p list;

  OPENSCOP_malloc(list, openscop_scop_list_p, sizeof(openscop_scop_list_t));
  list->elt  = NULL;
  list->next = NULL;
  
  return list;
}


/**
 * openscop_scop_list_free function:
 * this function frees the allocated memory for a openscop_scop_list_t
 * structure.
 * \param[in,out] list The pointer to the scop_list we want to free.
 */
void openscop_scop_list_free(openscop_scop_list_p list) {
  openscop_scop_list_p tmp;
  
  if (list == NULL)
    return;

  while (list != NULL) {
    if (list->elt != NULL)
      openscop_scop_free(list->elt);
    tmp = list->next;
    free(list);
    list = tmp;
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_scop_list_clone function:
 * this function builds and returns a "hard copy" (not a pointer copy) of an
 * openscop_scop_list_t data structure (the full union of scop_list).
 * \param[in] list The pointer to the scop list we want to clone.
 * \return A pointer to the clone of the scop list.
 */
openscop_scop_list_p openscop_scop_list_clone(openscop_scop_list_p list) {
  openscop_scop_list_p clone = NULL, node, previous = NULL;
  int first = 1;
  
  while (list != NULL) {
    node      = openscop_scop_list_malloc();
    node->elt = openscop_scop_clone(list->elt);
 
    if (first) {
      first = 0;
      clone = node;
      previous = node;
    }
    else {
      previous->next = node;
      previous = previous->next;
    }

    list = list->next;
  }

  return clone;
}


/**
 * openscop_scop_list_equal function:
 * this function returns true if the two scop lists provided as parameters
 * are the same, false otherwise.
 * \param[in] l1  The first list.
 * \param[in] l2  The second list.
 * \return 1 if l1 and l2 are the same (content-wise), 0 otherwise.
 */
int openscop_scop_list_equal(openscop_scop_list_p l1, openscop_scop_list_p l2) {
  while ((l1 != NULL) && (l2 != NULL)) {
    if (l1 == l2)
      return 1;
    
    if (!openscop_scop_equal(l1->elt, l2->elt))
      return 0;

    l1 = l1->next;
    l2 = l2->next;
  }

  if (((l1 == NULL) && (l2 != NULL)) || ((l1 != NULL) && (l2 == NULL)))
    return 0;
 
  return 1;
}


/**
 * openscop_scop_list_integrity_check function:
 * this function checks that a scop list is "well formed" according to
 * OpenScop specifications. It returns 0 if the check failed or 1 if no
 * problem has been detected.
 * \param[in] list  The scop_list we want to check.
 * \return 0 if the integrity check fails, 1 otherwise.
 */
int openscop_scop_list_integrity_check(openscop_scop_list_p list) {

  while (list != NULL) {
    if (openscop_scop_integrity_check(list->elt) == 0)
      return 0;

    list = list->next;
  }
  return 1;
}
