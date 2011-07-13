
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                           strings.c                             **
     **-----------------------------------------------------------------**
     **                   First version: 13/07/2011                     **
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
# include <openscop/strings.h>


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * openscop_strings_idump function:
 * this function displays an array of strings into a file (file, possibly
 * stdout) in a way that trends to be understandable. It includes an
 * indentation level (level) in order to work with others
 * print_structure functions.
 * \param[in] file       The file where the information has to be printed.
 * \param[in] strings    The array of strings that has to be printed.
 * \param[in] level      Number of spaces before printing, for each line.
 * \param[in] title      A string to use as a title for the array of strings.
 */
void openscop_strings_idump(FILE * file, char ** strings, int level,
                            char * title) {
  int i, nb_strings;
  
  for (i = 0; i <= level; i++)
    fprintf(file, "|\t");
  
  if ((strings != NULL) &&
      ((nb_strings = openscop_strings_size(strings)) > 0)) {
    fprintf(file, "+-- %s:", title);
    for (i = 0; i < nb_strings; i++)
      fprintf(file, " %s", strings[i]);
    fprintf(file, "\n");
  }
  else
    fprintf(file, "+-- No %s\n", title);

  // A blank line.
  for (i = 0; i <= level+1; i++)
    fprintf(file, "|\t");
  fprintf(file, "\n");
}


/**
 * openscop_strings_print function:
 * this function prints the content of an array of strings
 * into a file (file, possibly stdout) in the OpenScop textual format.
 * \param[in] file     The file where the information has to be printed.
 * \param[in] strings  The array of strings that has to be printed.
 * \param[in] provided Boolean set to 1 to print a "provided" boolean
 *                     before the string list, 0 otherwise.
 * \param[in] print    Boolean set to 1 to print the strings, 0 otherwise.
 * \param[in] title    A string to use as a title for the array of strings.
 */
void openscop_strings_print(FILE * file, char ** strings, 
                            int provided, int print, char * title) {
  int i, nb_strings;
  
  if ((print != 0) && 
      ((nb_strings = openscop_strings_size(strings)) > 0)) {
    if (provided) {
      fprintf(file, "# %s are provided\n", title);
      fprintf(file, "1\n");
    }
    fprintf(file, "# %s\n", title);
    for (i = 0; i < nb_strings; i++)
      fprintf(file, "%s ", strings[i]);
    fprintf(file, "\n\n");
  }
  else {
    if (provided) {
      fprintf(file, "# %s are not provided\n", title);
      fprintf(file, "0\n\n");
    }
  }
}


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * openscop_strings_read function.
 * this function reads an array of strings from a file (possibly stdin)
 * complying to the OpenScop textual format and returns a pointer to this
 * array as well as the number of elements of this array (through the
 * parameter nb_strings).
 * \param[in] file       The file where to read the array of strings.
 * \return The array of strings that has been read.
 */
char ** openscop_strings_read(FILE * file) {
  char str[OPENSCOP_MAX_STRING];
  char tmp[OPENSCOP_MAX_STRING];
  char * s, * start;
  char ** strings = NULL;
  int nb_strings;
  int i, count;

  // Skip blank/commented lines and spaces.
  start = openscop_util_skip_blank_and_comments(file, str);

  // Count the actual number of strings.
  nb_strings = 0;
  s = start;
  while (1) {
    for (count = 0; *s && ! isspace(*s) && *s != '#'; count++)
      s++;
    
    if (count != 0)
      nb_strings++;

    if ((*s == '#') || (*s == '\n'))
      break;
    else
      ++s;
  }

  if (nb_strings > 0) {
    // Allocate the array of strings. Make it NULL-terminated.
    OPENSCOP_malloc(strings, char **, sizeof(char *) * (nb_strings + 1));
    strings[nb_strings] = NULL;

    // Read the desired number of strings.
    s = start;
    for (i = 0; i < nb_strings; i++) {
      for (count = 0; *s && ! isspace(*s) && *s != '#'; count++)
	tmp[count] = *(s++);
      tmp[count] = '\0';
      strings[i] = strdup(tmp);
      if (strings[i] == NULL)
        OPENSCOP_error("memory overflow");
      if (*s != '#')
	++s;
    }
  }

  return strings;
}


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/


/**
 * openscop_strings_generate function:
 * This function generates an array of size 'nb_strings' of strings of the
 * form "prefixXX" where XX goes from 1 to nb.
 * \param[in] prefix     The prefix of the generated names.
 * \param[in] nb_strings The number of strings to generate.
 * \return An array of 'nb' generated strings.
 */
char ** openscop_strings_generate(char * prefix, int nb_strings) {
  char ** strings = NULL;
  char buff[strlen(prefix) + 16]; // TODO: better (log10(INT_MAX) ?) :-D.
  int i;

  if (nb_strings) {
    OPENSCOP_malloc(strings, char **, sizeof(char *) * (nb_strings + 1));
    strings[nb_strings] = NULL;
    for (i = 0; i < nb_strings; i++) {
      sprintf(buff, "%s%d", prefix, i + 1);
      strings[i] = strdup(buff);
      if (strings[i] == NULL)
        OPENSCOP_error("memory overflow");
    }
  }

  return strings;
}


/**
 * openscop_strings_free function:
 * this function frees the allocated memory for an array of strings.
 * \param[in] strings The array of strings we want to free.
 */
void openscop_strings_free(char ** strings) {
  int i;

  if (strings != NULL) {
    i = 0;
    while(strings[i] != NULL) {
      free(strings[i]);
      i++;
    }
    free(strings);
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_strings_clone internal function.
 * this function builds and return a "hard copy" (not a pointer copy) of an
 * array of strings provided as parameter.
 * \param[in] strings    The array of strings to clone.
 * \return The clone of the array of strings.
 */
char ** openscop_strings_clone(char ** strings) {
  int i, nb_strings;
  char ** clone;
  
  if ((strings == NULL) ||
      ((nb_strings = openscop_strings_size(strings)) == 0))
    return NULL;

  OPENSCOP_malloc(clone, char **, (nb_strings + 1) * sizeof(char *));
  clone[nb_strings] = NULL;
  for (i = 0; i < nb_strings; i++) {
    clone[i] = strdup(strings[i]);
    if (clone[i] == NULL)
      OPENSCOP_error("memory overflow");
  }

  return clone;
}


/**
 * openscop_strings_equal function:
 * this function returns true if the two arrays of strings are the same
 * (content-wise), false otherwise.
 * \param[in] s1 The first array of strings.
 * \param[in] s2 The second array of strings.
 * \return 1 if s1 and s2 are the same (content-wise), 0 otherwise.
 */
int openscop_strings_equal(char ** s1, char ** s2) {
  int i, nb_s1;
  
  if (s1 == s2)
    return 1;

  if (((s1 == NULL) && (s2 != NULL)) ||
      ((s1 != NULL) && (s2 == NULL)) ||
      ((nb_s1 = openscop_strings_size(s1)) !=
       openscop_strings_size(s2)))
    return 0;

  for (i = 0; i < nb_s1; i++)
    if (strcmp(s1[i], s2[i]) != 0)
      return 0;

  return 1;
}


/**
 * openscop_strings_size function:
 * this function returns the number of elements in the NULL-terminated
 * strings array.
 * \param[in] strings The array of strings we need to know the size.
 * \return The number of elements in the array of strings.
 */
int openscop_strings_size(char ** strings) {
  int size = 0;

  if (strings != NULL) {
    while(strings[size] != NULL) {
      size++;
    }
  }

  return size;
}


/**
 * openscop_strings_complete function:
 * this function completes an array of strings with generated strings.
 * \param[in,out] strings     Pointer to the initial array of strings.
 * \param[in]     prefix      The prefix of the generated names.
 * \param[in]     nb_complete The desired number of strings in the new array.
 */
void openscop_strings_complete(char *** strings, char * prefix,
                                    int nb_complete) {
  int i, nb_new;
  char ** completion;

  nb_new = nb_complete - openscop_strings_size(*strings);
  if (nb_new < 0) {
    fprintf(stderr, "[OpenScop] Error: asked to complete the following "
                    "string array but it would be smaller than the original "
                    "(desired length: %d):\n", nb_complete);
    openscop_strings_idump(stderr, *strings, -1, "To be completed");
    exit(1);
  }

  if (nb_new > 0) {
    OPENSCOP_realloc(*strings, char **, (nb_complete + 1) * sizeof(char *));
    *strings[nb_complete] = NULL;
    completion = openscop_strings_generate(prefix, nb_new);
    for (i = 0; i < nb_new; i++)
      (*strings)[i + openscop_strings_size(*strings)] = completion[i];
    free(completion);
  }
}
