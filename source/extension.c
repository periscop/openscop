
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                          extension.c                            **
     **-----------------------------------------------------------------**
     **                   First version: 26/11/2010                     **
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
# include <openscop/extension.h>


/* !!!!!!!! TO ADD A NEW EXTENSION, PLEASE READ THE MANUAL FIRST !!!!!!!!!!! */


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * openscop_extension_idump function:
 * this function displays a openscop_extension_t structure (*extensions) into
 * a file (file, possibly stdout) in a way that trends to be understandable.
 * It includes an indentation level (level) in order to work with others
 * print_structure functions.
 * \param file       File where informations are printed.
 * \param extensions The extensions whose information have to be printed.
 * \param level      Number of spaces before printing, for each line.
 */
void openscop_extension_idump(FILE * file,
                              openscop_extension_p extension, int level) {
  int j, first = 1;
  
  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file,"|\t");

  if (extension != NULL)
    fprintf(file, "+-- openscop_extension_t\n");
  else
    fprintf(file, "+-- NULL extension\n");
 
  while (extension != NULL) {
    if (!first) {
      // Go to the right level.
      for (j = 0; j < level; j++)
        fprintf(file, "|\t");
      fprintf(file, "|   openscop_extension_t\n");
    }
    else
      first = 0;

    // A blank line
    for(j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    openscop_interface_idump(file, extension->interface, level + 1);
   
    if (extension->interface != NULL)
      extension->interface->idump(file, extension->extension, level + 1);
    
    extension = extension->next;

    // Next line.
    if (extension != NULL) {
      for (j = 0; j <= level; j++)
        fprintf(file, "|\t");
      fprintf(file, "V\n");
    }
  }
}


/**
 * openscop_extension_dump function:
 * this function prints the content of a openscop_extension_t structure
 * (*extension) into a file (file, possibly stdout).
 * \param file  File where informations are printed.
 * \param extension The extension structure to print.
 */
void openscop_extension_dump(FILE * file, openscop_extension_p extension) {
  openscop_extension_idump(file, extension, 0); 
}


/**
 * openscop_extension_print function:
 * this function prints the content of a openscop_extension_t structure
 * (*extension) into a string (returned) in the OpenScop format.
 * \param  extension The extension structure to print.
 * \return A string containing the OpenScop dump of the extension structure.
 */
void openscop_extension_print(FILE * file, openscop_extension_p extension) {
  char * string;
  
  if (extension == NULL)
    return;

  while (extension != NULL) {
    if (extension->interface != NULL) {
      string = extension->interface->sprint(extension->extension);
      if (string != NULL) {
        fprintf(file, "%s\n", string);
        free(string);
      }
    }
    extension = extension->next;
  }
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/**
 * openscop_extension_read function:
 * this function reads a list of extensions from a string complying to the
 * OpenScop textual format and a list of knows extension identities. It
 * returns a pointer to an extension structure which contain this list of
 * extension.
 * \param string   The string where to read a list of extension fields.
 * \param registry The list of knows extensions (others are ignored).
 * \return A pointer to the extension list that has been read.
 */
openscop_extension_p
openscop_extension_sread(char * string, openscop_interface_p registry) {
  openscop_extension_p extension = NULL, new;
  openscop_interface_p interface;
  void * x;

  while (registry != NULL) {
    x = registry->sread(string);
    if (x != NULL) {
      interface = openscop_interface_nclone(registry, 1);
      new = openscop_extension_malloc();
      new->interface = interface;
      new->extension = x;
      openscop_extension_add(&extension, new);
    }
    registry = registry->next;
  }
  
  return extension;
}


/**
 * openscop_extension_read function:
 * this function reads a list of extensions from a file (possibly stdin)
 * complying to the OpenScop textual format and a list of knows extension
 * identities. It returns a pointer to an extension structure which contain
 * this list of extension.
 * \param file     The input file where to read a list of extension fields.
 * \param registry The list of knows extensions (others are ignored).
 * \return A pointer to the extension list that has been read.
 */
openscop_extension_p
openscop_extension_read(FILE * file, openscop_interface_p registry) {
  char * extension_string;
  void * extension_list;

  extension_string = openscop_util_read_uptotag(file, OPENSCOP_TAG_END_SCOP);
  extension_list = openscop_extension_sread(extension_string, registry);
  free(extension_string);
  return extension_list;
}


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/


/**
 * openscop_extension_add function:
 * this function adds an extension node (it may be a list as well) to a list
 * of extensions provided as parameter (list). The new node is inserted at
 * the end of the list. 
 * \param list      The list of extensions to add a node (NULL if empty).
 * \param extension The new extension to add to the list.
 */
void openscop_extension_add(openscop_extension_p * list,
                            openscop_extension_p extension) {
  openscop_extension_p tmp = *list, check;
  
  if (extension != NULL) {
    // First, check that the extension list is OK.
    check = extension;
    while (check != NULL) {
      if ((check->interface == NULL) || (check->interface->URI == NULL))
        OPENSCOP_error("no interface or URI in an extension to add to a list");

      if (openscop_extension_lookup(*list, check->interface->URI) != NULL)
        OPENSCOP_error("only one extension with a given URI is allowed");
      check = check->next;
    }

    if (*list != NULL) {
      while (tmp->next != NULL)
        tmp = tmp->next;
      tmp->next = extension;
    }
    else {
      *list = extension;
    }
  }
}


/**
 * openscop_extension_malloc function:
 * This function allocates the memory space for a openscop_extension_t
 * structure and sets its fields with default values. Then it returns a
 * pointer to the allocated space.
 * \return A pointer to an empty extension structure with fields set to
 *         default values.
 */
openscop_extension_p openscop_extension_malloc() {
  openscop_extension_p extension;

  OPENSCOP_malloc(extension, openscop_extension_p,
                  sizeof(openscop_extension_t));
  extension->interface = NULL;
  extension->extension = NULL;
  extension->next      = NULL;

  return extension;
}


/**
 * openscop_extension_free function:
 * This function frees the allocated memory for an extension structure.
 * \param extension The pointer to the extension structure we want to free.
 */
void openscop_extension_free(openscop_extension_p extension) {
  openscop_extension_p next;

  while (extension != NULL) {
    next = extension->next;
    if (extension->interface != NULL) {
      extension->interface->free(extension->extension);
      openscop_interface_free(extension->interface);
    }
    else {
      if (extension->extension != NULL) {
        OPENSCOP_warning("unregistered extension, memory leaks are possible");
        free(extension->extension);
      }
    }
    free(extension);
    extension = next;
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_extension_clone function:
 * This function builds and returns a "hard copy" (not a pointer copy) of an
 * openscop_extension_t data structure.
 * \param extension The pointer to the extension structure we want to clone.
 * \return A pointer to the clone of the extension structure.
 */
openscop_extension_p openscop_extension_clone(openscop_extension_p extension) {
  openscop_extension_p clone = NULL, new;
  openscop_interface_p interface;
  void * x;

  while (extension != NULL) { 
    if (extension->interface != NULL) {
      x = extension->interface->clone(extension->extension);
      interface = openscop_interface_clone(extension->interface);
      new = openscop_extension_malloc();
      new->interface = interface;
      new->extension = x;
      openscop_extension_add(&clone, new);
    }
    else {
      OPENSCOP_warning("unregistered extension, cloning ignored");
    }
    extension = extension->next;
  }

  return clone;
}


/**
 * openscop_extension_count function:
 * this function counts the number of elements in the extension list provided
 * as parameter (x) and returns this number.
 * \param x The list of extensions.
 * \return  The number of elements in the list.
 */
int openscop_extension_count(openscop_extension_p x) {
  int extension_number = 0;

  while (x != NULL) {
    extension_number++;
    x = x->next;
  }

  return extension_number;
}


/**
 * openscop_extension_equal function:
 * this function returns true if the two extension structures are the same,
 * false otherwise. This functions considers two extension structures as equal
 * if the order of the array names differ, however the identifiers and names
 * must be the same.
 * \param a1  The first extension structure.
 * \param a2  The second extension structure.
 * \return 1 if a1 and a2 are the same (content-wise), 0 otherwise.
 */
int openscop_extension_equal(openscop_extension_p x1,
                             openscop_extension_p x2) {
  int x1_extension_number, x2_extension_number;
  int found, equal;
  openscop_extension_p backup_x2 = x2;

  if (x1 == x2)
    return 1;

  // Check whether the number of extensions is the same or not.
  x1_extension_number = openscop_extension_count(x1);
  x2_extension_number = openscop_extension_count(x2);
  if (x1_extension_number != x2_extension_number)
    return 0;

  // Check that for each extension in x1 a similar extension is in x2.
  while (x1 != NULL) {
    x2 = backup_x2;
    found = 0;
    while ((x2 != NULL) && (found != 1)) {
      if (openscop_interface_equal(x1->interface, x2->interface)) {
        if (x1->interface != NULL) {
          equal = x1->interface->equal(x1->extension, x2->extension);
        }
        else {
          OPENSCOP_warning("unregistered extension, "
                           "cannot state extension equality");
          equal = 0;
        }

        if (equal == 0)
          return 0;
        else
          found = 1;
      }

      x2 = x2->next;
    }

    if (found != 1)
      return 0;

    x1 = x1->next;
  }

  return 1;
}


/**
 * openscop_extension_lookup function:
 * this function returns the first extension with a given URI in the
 * extension list provided as parameter and NULL if it doesn't find such
 * an extension.
 * \param x    The extension list where to search a given extension URI.
 * \param URI  The URI of the extension we are looking for.
 * \return The first extension of the requested URI in the list.
 */
void * openscop_extension_lookup(openscop_extension_p x, char * URI) {
  while (x != NULL) {
    if ((x->interface != NULL) && (!strcmp(x->interface->URI, URI)))
      return x->extension;

    x = x->next;
  }

  return NULL;
}
