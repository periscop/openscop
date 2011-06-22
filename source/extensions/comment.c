
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                     extensions/comment.c                        **
     **-----------------------------------------------------------------**
     **                   First version: 07/12/2010                     **
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


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * openscop_comment_idump function:
 * this function displays an openscop_comment_t structure (*comment) into a
 * file (file, possibly stdout) in a way that trends to be understandable. It
 * includes an indentation level (level) in order to work with others
 * print_structure functions.
 * \param file    The file where the information has to be printed.
 * \param comment The comment structure whose information has to be printed.
 * \param level   Number of spaces before printing, for each line.
 */
void openscop_comment_idump(FILE * file, openscop_comment_p comment,
                            int level) {
  int j;
  char * tmp;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (comment != NULL)
    fprintf(file, "+-- openscop_comment_t\n");
  else
    fprintf(file, "+-- NULL comment\n");

  if (comment != NULL) {
    // Go to the right level.
    for(j = 0; j <= level; j++)
      fprintf(file, "|\t");
  
    // Display the comment message (without any carriage return).
    tmp = strdup(comment->comment);
    for (j = 0; j < strlen(tmp); j++)
      if (tmp[j] == '\n')
	tmp[j] = ' ';
    fprintf(file, "comment: %s\n", tmp);
    free(tmp);
  }

  // The last line.
  for (j = 0; j <= level; j++)
    fprintf(file, "|\t");
  fprintf(file, "\n");
}


/**
 * openscop_comment_dump function:
 * this function prints the content of an openscop_comment_t structure
 * (*comment) into a file (file, possibly stdout).
 * \param file    The file where the information has to be printed.
 * \param comment The comment structure whose information has to be printed.
 */
void openscop_comment_dump(FILE * file, openscop_comment_p comment) {
  openscop_comment_idump(file, comment, 0);
}


/**
 * openscop_comment_sprint function:
 * this function prints the content of an openscop_comment_t structure
 * (*comment) into a string (returned) in the OpenScop textual format.
 * \param  comment The comment structure whose information has to be printed.
 * \return A string containing the OpenScop dump of the comment structure.
 */
char * openscop_comment_sprint(openscop_comment_p comment) {
  int high_water_mark = OPENSCOP_MAX_STRING;
  char * string = NULL;
  char * buffer;

  if (comment != NULL) {
    string = (char *)malloc(high_water_mark * sizeof(char));
    buffer = (char *)malloc(OPENSCOP_MAX_STRING * sizeof(char));
    if ((string == NULL) || (buffer == NULL)) {
      fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
      exit(1);
    }
    string[0] = '\0';
   
    // Print the begin tag.
    sprintf(buffer, OPENSCOP_TAG_COMMENT_START);
    openscop_util_safe_strcat(&string, buffer, &high_water_mark);

    // Print the comment.
    sprintf(buffer, "\n%s", comment->comment);
    openscop_util_safe_strcat(&string, buffer, &high_water_mark);

    // Print the end tag.
    sprintf(buffer, OPENSCOP_TAG_COMMENT_STOP"\n");
    openscop_util_safe_strcat(&string, buffer, &high_water_mark);
  
    // Keep only the memory space we need.
    string = (char *)realloc(string, (strlen(string) + 1) * sizeof(char));
    free(buffer);
  }

  return string;
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/

/**
 * openscop_comment_sread function:
 * this function reads a comment structure from a string complying to the
 * OpenScop textual format and returns a pointer to this comment structure.
 * The string should contain only one textual format of a comment structure.
 * \param  extensions The input string where to find a comment structure.
 * \return A pointer to the comment structure that has been read.
 */
openscop_comment_p openscop_comment_sread(char * extensions) {
  char * content;
  openscop_comment_p comment;

  content = openscop_util_tag_content(extensions, OPENSCOP_TAG_COMMENT_START,
                                                  OPENSCOP_TAG_COMMENT_STOP);
  if (content == NULL) {
    fprintf(stderr, "[OpenScop] Info: no comment optional tag.\n");
    return NULL;
  }

  if (strlen(content) > OPENSCOP_MAX_STRING) { 
    fprintf(stderr, "[OpenScop] Error: comment too long.\n");
    exit(1);
  }

  comment = openscop_comment_malloc();
  comment->comment = content;

  return comment;
}


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/


/**
 * openscop_comment_malloc function:
 * This function allocates the memory space for an openscop_comment_t
 * structure and sets its fields with default values. Then it returns a
 * pointer to the allocated space.
 * \return A pointer to an empty comment structure with fields set to
 *         default values.
 */
openscop_comment_p openscop_comment_malloc() {
  openscop_comment_p comment;

  comment = (openscop_comment_p)malloc(sizeof(openscop_comment_t));
  if (comment == NULL) {
    fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
    exit(1);
  }
  
  comment->comment = NULL;

  return comment;
}


/**
 * openscop_comment_free function:
 * This function frees the allocated memory for an openscop_comment_t
 * structure.
 * \param comment The pointer to the comment structure we want to free.
 */
void openscop_comment_free(openscop_comment_p comment) {
  if (comment != NULL) {
    if(comment->comment != NULL)
      free(comment->comment);
    free(comment);
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_comment_copy function:
 * This function builds and returns a "hard copy" (not a pointer copy) of an
 * openscop_comment_t data structure.
 * \param comment The pointer to the comment structure we want to copy.
 * \return A pointer to the copy of the comment structure.
 */
openscop_comment_p openscop_comment_copy(openscop_comment_p comment) {
  openscop_comment_p copy;

  if (comment == NULL)
    return NULL;

  copy = openscop_comment_malloc();
  copy->comment = strdup(comment->comment);
  if ((copy->comment == NULL) && (comment->comment != NULL)) {
    fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
    exit(1);
  }

  return copy;
}


/**
 * openscop_comment_equal function:
 * this function returns true if the two comment structures are the same
 * (content-wise), false otherwise.
 * \param c1  The first comment structure.
 * \param c2  The second comment structure.
 * \return 1 if c1 and c2 are the same (content-wise), 0 otherwise.
 */
int openscop_comment_equal(openscop_comment_p c1, openscop_comment_p c2) {
  
  if (c1 == c2)
    return 1;

  if (((c1 == NULL) && (c2 != NULL)) || ((c1 != NULL) && (c2 == NULL)))
    return 0;

  if (strcmp(c1->comment, c2->comment))
    return 0;

  return 1;
}
