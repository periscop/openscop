
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


/*
 * For each extension called FOO that a programmer wishes to add to
 * OpenScop, the following functions must be provided in a dedicated
 * file FOO.c (follow the "comment" example):
 * - Display function (for internal use)
 * - Print function (to OpenScop's file format as a string)
 * - Read function (from OpenScop's file format as a string)
 * - Malloc function (allocate the extension part in an extension structure)
 * - Free function (free the extension part in an extension structure)
 * - Copy function
 * - Equal function
 */


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * openscop_extension_print_structure function:
 * this function displays a openscop_extension_t structure (*extensions) into
 * a file (file, possibly stdout) in a way that trends to be understandable.
 * It includes an indentation level (level) in order to work with others
 * print_structure functions.
 * \param file       File where informations are printed.
 * \param extensions The extensions whose information have to be printed.
 * \param level      Number of spaces before printing, for each line.
 */
void
openscop_extension_print_structure(FILE * file,
                                   openscop_extension_p extension,
                                   int level)
{
  int j, first = 1;
  
  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file,"|\t");

  if (extension != NULL)
    fprintf(file, "+-- openscop_extension_t\n");
  else
    fprintf(file, "+-- NULL extension\n");
 
  while (extension != NULL)
  {
    if (!first)
    {
      // Go to the right level.
      for (j = 0; j < level; j++)
        fprintf(file, "|\t");
      fprintf(file, "|   openscop_extension_t\n");
    }
    else
      first = 0;

    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");
    
    // Go to the right level.
    for (j = 0; j < level; j++)
      fprintf(file, "|\t");
    switch (extension->type)
    {
      case OPENSCOP_EXTENSION_COMMENT:
      {
        fprintf(file, "|\ttype = OPENSCOP_EXTENSION_COMMENT\n");
        break;
      }
      case OPENSCOP_EXTENSION_ARRAYS:
      {
        fprintf(file, "|\ttype = OPENSCOP_EXTENSION_ARRAYS\n");
        break;
      }
      default:
      {
        fprintf(file, "|\ttype = unsupported (%d)\n", extension->type);
      }
    }

    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");
    
    switch (extension->type)
    {
      case OPENSCOP_EXTENSION_COMMENT:
      {
        openscop_comment_print_structure(
            file,
            (openscop_comment_p)extension->extension,
            level + 1);
        break;
      }
      case OPENSCOP_EXTENSION_ARRAYS:
      {
        openscop_arrays_print_structure(
            file,
            (openscop_arrays_p)extension->extension,
            level + 1);
        break;
      }
      default:
      {
        // A blank line.
        for (j = 0; j <= level+1; j++)
          fprintf(file, "|\t");
        fprintf(file, "| Unsupported extension\n");
      }
    }
    
    extension = extension->next;

    // Next line.
    if (extension != NULL)
    {
      for (j = 0; j <= level; j++)
        fprintf(file, "|\t");
      fprintf(file, "V\n");
    }
  }
}


/**
 * openscop_extension_print function:
 * this function prints the content of a openscop_extension_t structure
 * (*extension) into a file (file, possibly stdout).
 * \param file  File where informations are printed.
 * \param extension The extension structure to print.
 */
void
openscop_extension_print(FILE * file, openscop_extension_p extension)
{
  openscop_extension_print_structure(file, extension, 0); 
}


/**
 * openscop_extension_print_openscop function:
 * this function prints the content of a openscop_extension_t structure
 * (*extension) into a string (returned) in the OpenScop format.
 * \param  extension The extension structure to print.
 * \return A string containing the OpenScop dump of the extension structure.
 */
void
openscop_extension_print_openscop(FILE * file, openscop_extension_p extension)
{
  char * string;
  int ignored;
  
  if (extension == NULL)
    return;

  while (extension != NULL)
  {
    ignored = 0;
    switch (extension->type)
    {
      case OPENSCOP_EXTENSION_COMMENT:
      {
        string = openscop_comment_print_openscop(
                     (openscop_comment_p)extension->extension);
        break;
      }
      case OPENSCOP_EXTENSION_ARRAYS:
      {
        string = openscop_arrays_print_openscop(
                     (openscop_arrays_p)extension->extension);
        break;
      }
      default:
      {
        ignored = 1;
        fprintf(stderr,
                "[OpenScop] Warning: unsupported extension, "
                "printing it has been ignored.\n");
      }
    }
    if (!ignored)
    {
      fprintf(file, "%s\n", string);
      free(string);
    }

    extension = extension->next;
  }
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/**
 * openscop_extension_read function:
 * this function reads a list of extensions from a file (possibly stdin)
 * complying to the OpenScop textual format and returns a pointer to an
 * extension structure which contain this list of extension.
 * \param  file The input file where to read a list of extension fields.
 * \return A pointer to the extension structure that has been read.
 */
openscop_extension_p
openscop_extension_read(FILE * file)
{
  char * extension_string;
  openscop_extension_p extension = NULL;
  void * x;

  extension_string = openscop_util_read_tail(file);
  
  x = (void *)openscop_comment_read(extension_string);
  openscop_extension_add(&extension, OPENSCOP_EXTENSION_COMMENT, x);   
 
  x = (void *)openscop_arrays_read(extension_string);
  openscop_extension_add(&extension, OPENSCOP_EXTENSION_ARRAYS, x);   
  
  free(extension_string);
  return extension;
}


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/


/**
 * openscop_extension_add function:
 * this function adds an extension node to a list of extensions provided
 * as parameter (extension). The new node is allocated in this function and
 * filled with the information provided as parameter (type and x). The new
 * node is inserted at the beginning of the list. 
 * \param extension The list of extension fields to add a node (NULL if empty).
 * \param type      The type of the new extension to add.
 * \param x         The new extension to add.
 */
void
openscop_extension_add(openscop_extension_p * extension, int type, void * x)
{
  openscop_extension_p new;

  if (x != NULL)
  {
    new = openscop_extension_malloc();
    new->type = type;
    new->extension = x;
    new->next = *extension;
    *extension = new;
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
openscop_extension_p
openscop_extension_malloc()
{
  openscop_extension_p extension;

  extension = (openscop_extension_p)malloc(sizeof(openscop_extension_t));
  if (extension == NULL)
  {
    fprintf(stderr, "[OpenScop] Error: memory Overflow.\n");
    exit(1);
  }
  
  extension->type      = OPENSCOP_EXTENSION_UNDEFINED;
  extension->extension = NULL;
  extension->next      = NULL;

  return extension;
}


/**
 * openscop_extension_free function:
 * This function frees the allocated memory for an extension structure.
 * \param extension The pointer to the extension structure we want to free.
 */
void
openscop_extension_free(openscop_extension_p extension)
{
  openscop_extension_p next;

  while (extension != NULL)
  {
    next = extension->next;
    switch (extension->type)
    {
      case OPENSCOP_EXTENSION_COMMENT:
      {
        openscop_comment_free(extension->extension);
        break;
      }
      case OPENSCOP_EXTENSION_ARRAYS:
      {
        openscop_arrays_free(extension->extension);
        break;
      }
      default:
      {
        fprintf(stderr,
                "[OpenScop] Warning: unsupported extension, "
                "memory leaks are possible.\n");
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
 * openscop_extension_copy function:
 * This function builds and returns a "hard copy" (not a pointer copy) of an
 * openscop_extension_t data structure.
 * \param extension The pointer to the extension structure we want to copy.
 * \return A pointer to the copy of the extension structure.
 */
openscop_extension_p
openscop_extension_copy(openscop_extension_p extension)
{
  openscop_extension_p copy = NULL;
  void * x;

  while (extension != NULL)
  { 
    switch (extension->type)
    {
      case OPENSCOP_EXTENSION_COMMENT:
      {
        x = (void *)openscop_comment_copy(extension->extension);
        break;
      }
      case OPENSCOP_EXTENSION_ARRAYS:
      {
        x = (void *)openscop_arrays_copy(extension->extension);
        break;
      }
      default:
      {
        fprintf(stderr,
                "[OpenScop] Warning: unsupported extension, "
                "copy ignored.\n");
        x = NULL;
      }
    }
    
    openscop_extension_add(&copy, extension->type, x);
    extension = extension->next;
  }

  return copy;
}


/**
 * openscop_extension_count function:
 * this function counts the number of elements in the extension list provided
 * as parameter (x) and returns this number.
 * \param x The list of extensions.
 * \return  The number of elements in the list.
 */
int
openscop_extension_count(openscop_extension_p x)
{
  int extension_number = 0;

  while (x != NULL)
  {
    extension_number++;
    x = x->next;
  }

  return extension_number;
}


/**
 * openscop_extension_equal function:
 * this function returns true if the two extension structures are the same, false
 * otherwise. This functions considers two extension structures as equal if
 * the order of the array names differ, however the identifiers and names
 * must be the same.
 * \param a1  The first extension structure.
 * \param a2  The second extension structure.
 * \return 1 if a1 and a2 are the same (content-wise), 0 otherwise.
 */
int
openscop_extension_equal(openscop_extension_p x1, openscop_extension_p x2)
{
  int x1_extension_number, x2_extension_number;
  int found, equal;
  openscop_extension_p backup_x2 = x2;

  // Check whether the number of extensions is the same or not.
  x1_extension_number = openscop_extension_count(x1);
  x2_extension_number = openscop_extension_count(x2);
  if (x1_extension_number != x2_extension_number)
    return 0;

  // Check that for each extension in x1 a similar extension is in x2.
  while (x1 != NULL)
  {
    x2 = backup_x2;
    found = 0;
    while ((x2 != NULL) && (found != 1))
    {
      if (x1->type == x2->type)
      {
        switch (x1->type)
        {
          case OPENSCOP_EXTENSION_COMMENT:
          {
            equal = openscop_comment_equal(x1->extension, x2->extension);
            break;
          }
          case OPENSCOP_EXTENSION_ARRAYS:
          {
            equal = openscop_arrays_equal(x1->extension, x2->extension);
            break;
          }
          default:
          {
            fprintf(stderr,
                    "[OpenScop] Warning: unsupported extension, "
                    "cannot state extension equality.\n");
            equal = 0;
          }
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
 * this function returns the first extension of a given type (type) in the
 * extension list provided as parameter (x) and NULL if it doesn't find such
 * an extension.
 * \param x    The extension list where to search a given extension type.
 * \param type The type of the extension we are looking for.
 * \return The first extension of the requested type in the list.
 */
void *
openscop_extension_lookup(openscop_extension_p x, int type)
{
  while (x != NULL)
  {
    if (x->type == type)
      return x->extension;

    x = x->next;
  }

  return NULL;
}