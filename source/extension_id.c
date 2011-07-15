
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                        extension_id.c                           **
     **-----------------------------------------------------------------**
     **                   First version: 15/07/2011                     **
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
# include <openscop/extension_id.h>


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * openscop_extension_id_idump function:
 * this function displays an openscop_extension_id_t structure (*id) into a
 * file (file, possibly stdout) in a way that trends to be understandable. It
 * includes an indentation level (level) in order to work with others
 * print_structure functions.
 * \param file         The file where the information has to be printed.
 * \param extension_id The extension_id structure which has to be printed.
 * \param level        Number of spaces before printing, for each line.
 */
void openscop_extension_id_idump(FILE * file, openscop_extension_id_p id,
                                 int level) {
  int j, first = 1;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (id != NULL)
    fprintf(file, "+-- openscop_extension_id_t: URI = %s\n", id->URI);
  else
    fprintf(file, "+-- NULL extension_id\n");

  
  while (id != NULL) {
    if (!first) {
      // Go to the right level.
      for (j = 0; j < level; j++)
        fprintf(file, "|\t");
      fprintf(file, "|   openscop_extension_id_t: URI = %s\n", id->URI);
    }
    else
      first = 0;

    id = id->next;

    // Next line.
    if (id != NULL) {
      for (j = 0; j <= level+1; j++)
        fprintf(file, "|\t");
      fprintf(file, "\n");
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
 * openscop_extension_id_dump function:
 * this function prints the content of a openscop_extension_id_t structure
 * (*id) into a file (file, possibly stdout).
 * \param file  File where informations are printed.
 * \param extension The extension idstructure to print.
 */
void openscop_extension_id_dump(FILE * file, openscop_extension_id_p id) {
  openscop_extension_id_idump(file, id, 0); 
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/


/**
 * openscop_extension_id_add function:
 * this function adds an extension id node (it may be a list as well) to a
 * list of extension ids provided as parameter (list). The new node
 * is inserted at the end of the list. 
 * \param list The list of extension ids to add a node (NULL if empty).
 * \param id   The extension id to add to the list.
 */
void openscop_extension_id_add(openscop_extension_id_p * list,
                               openscop_extension_id_p id) {
  openscop_extension_id_p tmp = *list, check_id;

  if (id != NULL) {
    // First, check that the id list is OK.
    check_id = id;
    while (check_id != NULL) {
      if (check_id->URI == NULL)
        OPENSCOP_error("no URI in an extension id to add to a list");

      if (openscop_extension_id_lookup(*list, check_id->URI) != NULL)
        OPENSCOP_error("only one extension with a given URI is allowed");
      check_id = check_id->next;
    }

    if (*list != NULL) {
      while (tmp->next != NULL)
        tmp = tmp->next;
      tmp->next = id;
    }
    else {
      *list = id;
    }
  }
}


/**
 * openscop_extension_id_malloc function:
 * This function allocates the memory space for a openscop_extension_id_t
 * structure and sets its fields with default values. Then it returns a
 * pointer to the allocated space.
 * \return A pointer to an empty extension id structure with fields set to
 *         default values.
 */
openscop_extension_id_p openscop_extension_id_malloc() {
  openscop_extension_id_p id;

  OPENSCOP_malloc(id, openscop_extension_id_p,
                  sizeof(openscop_extension_id_t));
  id->URI    = NULL;
  id->idump  = NULL; 
  id->dump   = NULL; 
  id->sprint = NULL; 
  id->sread  = NULL; 
  id->malloc = NULL; 
  id->free   = NULL; 
  id->clone  = NULL; 
  id->equal  = NULL;
  id->next   = NULL;

  return id;
}


/**
 * openscop_extension_id_free function:
 * this function frees the allocated memory for an openscop_extension_id_t
 * structure, and all the ids stored in the list.
 * \param[in] id The pointer to the extension id we want to free.
 */
void openscop_extension_id_free(openscop_extension_id_p id) {
  openscop_extension_id_p tmp;
  
  if (id == NULL)
    return;

  while (id != NULL) {
    tmp = id->next;
    if (id->URI != NULL)
      free(id->URI);
    free(id);
    id = tmp;
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_extension_id_nclone function:
 * This function builds and returns a "hard copy" (not a pointer copy) of the
 * n first elements of an openscop_extension_id_t list.
 * \param id The pointer to the extension id structure we want to clone.
 * \param n  The number of nodes of the list we want to copy (-1 for infinity).
 * \return The clone of the n first nodes of the extension id list.
 */
openscop_extension_id_p
openscop_extension_id_nclone(openscop_extension_id_p id, int n) {
  openscop_extension_id_p clone = NULL, new;
  int i = 0;

  while ((id != NULL) && ((n == -1) || (i < n))) {
    new = openscop_extension_id_malloc();
    new->URI    = strdup(id->URI);
    new->idump  = id->idump;
    new->dump   = id->dump;
    new->sprint = id->sprint;
    new->sread  = id->sread;
    new->malloc = id->malloc;
    new->free   = id->free;
    new->clone  = id->clone;
    new->equal  = id->equal;
    openscop_extension_id_add(&clone, new);
    id = id->next;
    i++;
  }

  return clone;
}


/**
 * openscop_extension_id_clone function:
 * This function builds and returns a "hard copy" (not a pointer copy) of an
 * openscop_extension_id_t data structure.
 * \param extension The pointer to the extension id structure we want to copy.
 * \return A pointer to the copy of the extension id structure.
 */
openscop_extension_id_p
openscop_extension_id_clone(openscop_extension_id_p id) {

  return openscop_extension_id_nclone(id, -1);
}


/**
 * openscop_extension_id_equal function:
 * this function returns true if the two extension id structures are the same,
 * false otherwise. 
 * \param id1  The first extension id structure.
 * \param id2  The second extension id structure.
 * \return 1 if id1 and id2 are the same (content-wise), 0 otherwise.
 */
int openscop_extension_id_equal(openscop_extension_id_p id1,
                                openscop_extension_id_p id2) {

  if (id1 == id2)
    return 1;
  
  if (((id1 == NULL) && (id2 != NULL)) || ((id1 != NULL) && (id2 == NULL)))
    return 0;

  if (strcmp(id1->URI, id2->URI) ||
      (id1->idump  != id2->idump)  ||
      (id1->dump   != id2->dump)   ||
      (id1->sprint != id2->sprint) ||
      (id1->sread  != id2->sread)  ||
      (id1->malloc != id2->malloc) ||
      (id1->free   != id2->free)   ||
      (id1->clone  != id2->clone)  ||
      (id1->equal  != id2->equal))
    return 0;

  return 1;
}


/**
 * openscop_extension_id_lookup function:
 * this function returns the first extension id with a given URI in the
 * extension list provided as parameter and NULL if it doesn't find such
 * an extension id.
 * \param list The extension id list where to search a given extension URI.
 * \param URI  The URI of the extension id we are looking for.
 * \return The first extension id of the requested URI in the list.
 */
openscop_extension_id_p
openscop_extension_id_lookup(openscop_extension_id_p list, char * URI) {
  while (list != NULL) {
    if ((list->URI != NULL) && (!strcmp(list->URI, URI)))
      return list;

    list = list->next;
  }

  return NULL;
}

