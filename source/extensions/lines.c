
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                     extensions/lines.c                        **
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
 * openscop_lines_print_structure function:
 * this function displays an openscop_lines_t structure (*lines) into a
 * file (file, possibly stdout) in a way that trends to be understandable. It
 * includes an indentation level (level) in order to work with others
 * print_structure functions.
 * \param file  The file where the information has to be printed.
 * \param lines The lines structure whose information has to be printed.
 * \param level Number of spaces before printing, for each line.
 */
void openscop_lines_print_structure(FILE * file, openscop_lines_p lines,
                                    int level) {
  int j;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (lines != NULL)
    fprintf(file, "+-- openscop_lines_t\n");
  else
    fprintf(file, "+-- NULL lines\n");

  if (lines != NULL) {
    // Go to the right level.
    for(j = 0; j <= level; j++)
      fprintf(file, "|\t");
  
    // Display the lines content.
    fprintf(file, "lines: %d - %d\n", lines->start,lines->end);
  }

  // The last line.
  for (j = 0; j <= level; j++)
    fprintf(file, "|\t");
  fprintf(file, "\n");
}


/**
 * openscop_lines_print function:
 * this function prints the content of an openscop_lines_t structure
 * (*lines) into a file (file, possibly stdout).
 * \param file    The file where the information has to be printed.
 * \param lines The lines structure whose information has to be printed.
 */
void openscop_lines_print(FILE * file, openscop_lines_p lines) {
  openscop_lines_print_structure(file, lines, 0);
}


/**
 * openscop_lines_print_openscop function:
 * this function prints the content of an openscop_lines_t structure
 * (*lines) into a string (returned) in the OpenScop textual format.
 * \param  lines The lines structure whose information has to be printed.
 * \return A string containing the OpenScop dump of the lines structure.
 */
char * openscop_lines_print_openscop(openscop_lines_p lines) {
  int high_water_mark = OPENSCOP_MAX_STRING;
  char * string = NULL;
  char * buffer;

  if (lines != NULL) {
    string = (char *)malloc(high_water_mark * sizeof(char));
    buffer = (char *)malloc(OPENSCOP_MAX_STRING * sizeof(char));
    if ((string == NULL) || (buffer == NULL)) {
      fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
      exit(1);
    }
    string[0] = '\0';
   
    // Print the begin tag.
    sprintf(buffer, OPENSCOP_TAG_LINES_START);
    openscop_util_safe_strcat(&string, buffer, &high_water_mark);

    // Print the lines content.
    sprintf(buffer, "\n%d - %d\n", lines->start, lines->end);
    openscop_util_safe_strcat(&string, buffer, &high_water_mark);

    // Print the end tag.
    sprintf(buffer, OPENSCOP_TAG_LINES_STOP"\n");
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
 * openscop_lines_read function:
 * this function reads a lines structure from a string complying to the
 * OpenScop textual format and returns a pointer to this lines structure.
 * The string should contain only one textual format of a lines structure.
 * \param  extensions The input string where to find a lines structure.
 * \return A pointer to the lines structure that has been read.
 */
openscop_lines_p openscop_lines_read(char * extensions) {
  char * content, *tmp;
  openscop_lines_p lines;

  content = openscop_util_tag_content(extensions, OPENSCOP_TAG_LINES_START,
                                                  OPENSCOP_TAG_LINES_STOP);
  if (content == NULL) {
    fprintf(stderr, "[OpenScop] Info: no lines optional tag.\n");
    return NULL;
  }

  if (strlen(content) > OPENSCOP_MAX_STRING) { 
    fprintf(stderr, "[OpenScop] Error: lines too long.\n");
    exit(1);
  }
  lines = openscop_lines_malloc();
  tmp = strtok(content," -");
  lines->start = atoi(tmp);
  if(lines->start == -1) {
    fprintf(stderr, "[OpenScop] Error: lines start NaN.\n");
    exit(1);
  }
  tmp = strtok(NULL," -");
  lines->end = atoi(tmp);
  if(lines->end == -1) {
    fprintf(stderr, "[OpenScop] Error: lines end NaN.\n");
    exit(1);
  }
  return lines;
}


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/


/**
 * openscop_lines_malloc function:
 * This function allocates the memory space for an openscop_lines_t
 * structure and sets its fields with default values. Then it returns a
 * pointer to the allocated space.
 * \return A pointer to an empty lines structure with fields set to
 *         default values.
 */
openscop_lines_p openscop_lines_malloc() {
  openscop_lines_p lines = (openscop_lines_p)malloc(sizeof(openscop_lines_t));
  
  if (lines == NULL) {
    fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
    exit(1);
  }
  
  lines->start = OPENSCOP_UNDEFINED;
  lines->end   = OPENSCOP_UNDEFINED;

  return lines;
}


/**
 * openscop_lines_free function:
 * This function frees the allocated memory for an openscop_lines_t
 * structure.
 * \param lines The pointer to the lines structure we want to free.
 */
void openscop_lines_free(openscop_lines_p lines) {
  if (lines != NULL) {
    free(lines);
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_lines_copy function:
 * This function builds and returns a "hard copy" (not a pointer copy) of an
 * openscop_lines_t data structure.
 * \param lines The pointer to the lines structure we want to copy.
 * \return A pointer to the copy of the lines structure.
 */
openscop_lines_p openscop_lines_copy(openscop_lines_p lines) {
  openscop_lines_p copy;

  if (lines == NULL)
    return NULL;

  copy = openscop_lines_malloc();
  if (copy == NULL) {
    fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
    exit(1);
  }
  copy->start = lines->start;
  copy->end = lines->end;

  return copy;
}


/**
 * openscop_lines_equal function:
 * this function returns true if the two lines structures are the same
 * (content-wise), false otherwise. This functions considers two lines
 * \param c1  The first lines structure.
 * \param c2  The second lines structure.
 * \return 1 if c1 and c2 are the same (content-wise), 0 otherwise.
 */
int openscop_lines_equal(openscop_lines_p c1, openscop_lines_p c2) {
  if ((c1 == NULL) && (c2 == NULL))
    return 1;

  if (((c1 == NULL) && (c2 != NULL)) || ((c1 != NULL) && (c2 == NULL)))
    return 0;

  if ((c1->start != c2->start) || (c1->end != c2->end))
    return 0;

  return 1;
}
