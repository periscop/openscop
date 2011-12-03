
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <osl/macros.h>
#include <osl/util.h>
#include <osl/interface.h>
#include <osl/extensions/lines.h>


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * osl_lines_idump function:
 * this function displays an osl_lines_t structure (*lines) into a
 * file (file, possibly stdout) in a way that trends to be understandable. It
 * includes an indentation level (level) in order to work with others
 * idump functions.
 * \param file  The file where the information has to be printed.
 * \param lines The lines structure whose information has to be printed.
 * \param level Number of spaces before printing, for each line.
 */
void osl_lines_idump(FILE * file, osl_lines_p lines, int level) {
  int j;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (lines != NULL)
    fprintf(file, "+-- osl_lines_t\n");
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
 * osl_lines_dump function:
 * this function prints the content of an osl_lines_t structure
 * (*lines) into a file (file, possibly stdout).
 * \param file    The file where the information has to be printed.
 * \param lines The lines structure whose information has to be printed.
 */
void osl_lines_dump(FILE * file, osl_lines_p lines) {
  osl_lines_idump(file, lines, 0);
}


/**
 * osl_lines_sprint function:
 * this function prints the content of an osl_lines_t structure
 * (*lines) into a string (returned) in the OpenScop textual format.
 * \param  lines The lines structure whose information has to be printed.
 * \return A string containing the OpenScop dump of the lines structure.
 */
char * osl_lines_sprint(osl_lines_p lines) {
  int high_water_mark = OSL_MAX_STRING;
  char * string = NULL;
  char * buffer;

  if (lines != NULL) {
    OSL_malloc(string, char *, high_water_mark * sizeof(char));
    OSL_malloc(buffer, char *, OSL_MAX_STRING * sizeof(char));
    string[0] = '\0';
   
    // Print the begin tag.
    sprintf(buffer, OSL_TAG_LINES_START);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);

    // Print the lines content.
    sprintf(buffer, "\n%d - %d\n", lines->start, lines->end);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);

    // Print the end tag.
    sprintf(buffer, OSL_TAG_LINES_STOP"\n");
    osl_util_safe_strcat(&string, buffer, &high_water_mark);
  
    // Keep only the memory space we need.
    OSL_realloc(string, char *, (strlen(string) + 1) * sizeof(char));
    free(buffer);
  }

  return string;
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/

/**
 * osl_lines_sread function:
 * this function reads a lines structure from a string complying to the
 * OpenScop textual format and returns a pointer to this lines structure.
 * The string should contain only one textual format of a lines structure.
 * \param  extensions The input string where to find a lines structure.
 * \return A pointer to the lines structure that has been read.
 */
osl_lines_p osl_lines_sread(char ** extensions_fixme) {
  char * content, *tmp;
  osl_lines_p lines;

  // FIXME: this is a quick and dirty thing to accept char ** instead
  //        of char * in the parameter: really do it and update the
  //        pointer to after what has been read.
  content = *extensions_fixme;

  if (content == NULL) {
    OSL_debug("no lines optional tag");
    return NULL;
  }

  if (strlen(content) > OSL_MAX_STRING) 
    OSL_error("lines too long");
  
  lines = osl_lines_malloc();
  tmp = strtok(content," -");
  lines->start = atoi(tmp);
  if(lines->start == -1)
    OSL_error("lines start NaN");
  
  tmp = strtok(NULL," -");
  lines->end = atoi(tmp);
  if(lines->end == -1)
    OSL_error("lines end NaN");
  
  return lines;
}


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/


/**
 * osl_lines_malloc function:
 * This function allocates the memory space for an osl_lines_t
 * structure and sets its fields with default values. Then it returns a
 * pointer to the allocated space.
 * \return A pointer to an empty lines structure with fields set to
 *         default values.
 */
osl_lines_p osl_lines_malloc() {
  osl_lines_p lines;
  
  OSL_malloc(lines, osl_lines_p, sizeof(osl_lines_t));
  lines->start = OSL_UNDEFINED;
  lines->end   = OSL_UNDEFINED;

  return lines;
}


/**
 * osl_lines_free function:
 * This function frees the allocated memory for an osl_lines_t
 * structure.
 * \param lines The pointer to the lines structure we want to free.
 */
void osl_lines_free(osl_lines_p lines) {
  if (lines != NULL) {
    free(lines);
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * osl_lines_clone function:
 * This function builds and returns a "hard copy" (not a pointer copy) of an
 * osl_lines_t data structure.
 * \param lines The pointer to the lines structure we want to copy.
 * \return A pointer to the copy of the lines structure.
 */
osl_lines_p osl_lines_clone(osl_lines_p lines) {
  osl_lines_p copy;

  if (lines == NULL)
    return NULL;

  copy = osl_lines_malloc();
  copy->start = lines->start;
  copy->end = lines->end;

  return copy;
}


/**
 * osl_lines_equal function:
 * this function returns true if the two lines structures are the same
 * (content-wise), false otherwise. This functions considers two lines
 * \param c1  The first lines structure.
 * \param c2  The second lines structure.
 * \return 1 if c1 and c2 are the same (content-wise), 0 otherwise.
 */
int osl_lines_equal(osl_lines_p c1, osl_lines_p c2) {
  if (c1 == c2)
    return 1;

  if (((c1 == NULL) && (c2 != NULL)) || ((c1 != NULL) && (c2 == NULL)))
    return 0;

  if ((c1->start != c2->start) || (c1->end != c2->end))
    return 0;

  return 1;
}


/**
 * osl_lines_interface function:
 * this function creates an interface structure corresponding to the lines
 * extension and returns it).
 * \return An interface structure for the lines extension.
 */
osl_interface_p osl_lines_interface() {
  osl_interface_p interface = osl_interface_malloc();
  
  interface->URI    = strdup(OSL_URI_LINES);
  interface->idump  = (osl_idump_f)osl_lines_idump;
  interface->sprint = (osl_sprint_f)osl_lines_sprint;
  interface->sread  = (osl_sread_f)osl_lines_sread;
  interface->malloc = (osl_malloc_f)osl_lines_malloc;
  interface->free   = (osl_free_f)osl_lines_free;
  interface->clone  = (osl_clone_f)osl_lines_clone;
  interface->equal  = (osl_equal_f)osl_lines_equal;

  return interface;
}

