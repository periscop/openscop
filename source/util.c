
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                            util.c                               **
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
# include <ctype.h>
# include <string.h>
# include <openscop/util.h>


/*+***************************************************************************
 *                       Functions on arrays of strings                      *
 *****************************************************************************/


/**
 * openscop_util_strings_print_structure function:
 * this function displays an array of strings into a file (file, possibly
 * stdout) in a way that trends to be understandable. It includes an
 * indentation level (level) in order to work with others
 * print_structure functions.
 * \param file       The file where the information has to be printed.
 * \param strings    The array of strings that has to be printed.
 * \param nb_strings The number of strings in the array of strings.
 * \param level      Number of spaces before printing, for each line.
 * \param title      A string to use as a title for the array of strings.
 */
void openscop_util_strings_print_structure(FILE * file,
                                           char ** strings, int nb_strings,
				           int level,
				           char * title) {
  int i;
  
  // Print the original parameter names.
  for (i = 0; i <= level; i++)
    fprintf(file, "|\t");
  if (nb_strings > 0) {
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
 * openscop_util_strings_print_openscop function:
 * this function prints the content of an array of strings
 * into a file (file, possibly stdout) in the OpenScop textual format.
 * \param file       The file where the information has to be printed.
 * \param strings    The array of strings that has to be printed.
 * \param nb_strings The number of strings in the array of strings.
 * \param print      Boolean not set to 0 to print the names, 0 otherwise.
 * \param title      A string to use as a title for the array of strings.
 */
void openscop_util_strings_print_openscop(FILE * file, 
                                          char ** strings, int nb_strings,
		                          int print,
				          char * title) {
  int i;
  
  if ((print != 0) && (nb_strings > 0)) {
    fprintf(file, "# %s are provided\n", title);
    fprintf(file, "1\n");
    fprintf(file, "# %s\n", title);
    for (i = 0; i < nb_strings; i++)
      fprintf(file, "%s ", strings[i]);
    fprintf(file, "\n\n");
  }
  else {
    fprintf(file, "# %s are not provided\n", title);
    fprintf(file, "0\n\n");
  }
}


/**
 * openscop_util_strings_read function.
 * this function reads an array of strings from a file (possibly stdin)
 * complying to the OpenScop textual format and returns a pointer to this
 * array as well as the number of elements of this array (through the
 * parameter nb_strings).
 * \param file       The file where to read the array of strings.
 * \param nb_strings Pointer to where to store the number of strings (output).
 * \return The array of strings that has been read.
 */
char ** openscop_util_strings_read(FILE * file, int * nb_strings) {
  char str[OPENSCOP_MAX_STRING];
  char tmp[OPENSCOP_MAX_STRING];
  char * s, * start;
  char ** strings = NULL;
  int i, count;

  // Skip blank/commented lines and spaces.
  start = openscop_util_skip_blank_and_comments(file, str);

  // Count the actual number of strings.
  *nb_strings = 0;
  s = start;
  while (1) {
    for (count = 0; *s && ! isspace(*s) && *s != '#'; ++count)
      s++;
    
    if (count != 0)
      (*nb_strings)++;

    if ((*s == '#') || (*s == '\n'))
      break;
    else
      ++s;
  }

  if (*nb_strings > 0) {
    // Allocate the array of strings. Make it NULL-terminated.
    strings = (char **) malloc(sizeof(char *) * ((*nb_strings) + 1));
    if (strings == NULL) {
      fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
      exit(1);
    }
    strings[*nb_strings] = NULL;

    // Read the desired number of strings.
    s = start;
    for (i = 0; i < *nb_strings; ++i) {
      for (count = 0; *s && ! isspace(*s) && *s != '#'; ++count)
	tmp[count] = *(s++);
      tmp[count] = '\0';
      strings[i] = strdup(tmp);
      if (strings[i] == NULL) {
	fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
	exit(1);
      }
      if (*s != '#')
	++s;
    }
  }

  return strings;
}


/**
 * openscop_util_strings_generate function:
 * This function generates an array of size 'nb' of strings of the form
 * "prefixXX" where XX goes from 1 to nb.
 * \param prefix     The prefix of the generated names.
 * \param nb_strings The number of strings to generate.
 * \return An array of 'nb' generated strings.
 */
char ** openscop_util_strings_generate(char * prefix, int nb_strings) {
  char ** strings = NULL;
  char buff[strlen(prefix) + 16]; // TODO: better (log10(INT_MAX) ?) :-D.
  int i;

  if (nb_strings) {
    strings = (char **)malloc(sizeof(char *) * nb_strings);
    if (strings == NULL) {
      fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
      exit(1);
    }
    for (i = 0; i < nb_strings; i++) {
      sprintf(buff, "%s%d", prefix, i + 1);
      strings[i] = strdup(buff);
      if (strings[i] == NULL) {
	fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
	exit(1);
      }
    }
  }

  return strings;
}


/**
 * openscop_util_strings_complete function:
 * this function completes an array of strings with generated strings.
 * \param strings     Pointer to the initial array of strings (modified).
 * \param nb_strings  Pointer to the initial number of strings (modified).
 * \param prefix      The prefix of the generated names.
 * \param nb_complete The desired number of strings in the new array.
 */
void openscop_util_strings_complete(char *** strings, int * nb_strings,
                                    char *   prefix,  int   nb_complete) {
  int i, nb_new;
  char ** completion;

  nb_new = nb_complete - *nb_strings;
  if (nb_new < 0) {
    fprintf(stderr, "[OpenScop] Error: asked to complete a string array "
                    "but it would be smaller than the original.\n");
    exit(1);
  }

  if (nb_new > 0) {
    *strings = (char **)realloc(*strings, nb_complete * sizeof(char *));
    completion = openscop_util_strings_generate(prefix, nb_new);
    for (i = 0; i < nb_new; i++)
      (*strings)[i + *nb_strings] = completion[i];
    free(completion);
    *nb_strings = nb_complete;
  }
}


/**
 * openscop_util_strings_free function:
 * this function frees the allocated memory for an array of strings.
 * \param strings The array of strings we want to free.
 * \param nb_strings The number of strings in the array of strings.
 */
void openscop_util_strings_free(char ** strings, int nb_strings) {
  int i;

  if (strings != NULL) {
    for (i = 0; i < nb_strings; i++)
      if (strings[i] != NULL)
	free(strings[i]);
    free(strings);
  }
}


/**
 * openscop_util_copy_strings internal function.
 * this function builds and return a "hard copy" (not a pointer copy) of an
 * array of strings provided as parameter.
 * \param strings    The array of strings to copy.
 * \param nb_strings The number of strings in the array to copy.
 * \return The copy of the array of strings.
 */
char ** openscop_util_strings_copy(char ** strings, int nb_strings) {
  int i;
  char ** copy;
  
  if ((strings == NULL) || (nb_strings == 0))
    return NULL;

  copy = (char **)malloc(nb_strings * sizeof(char *));
  if (copy == NULL)  {
    fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
    exit(1);
  }
  for (i = 0; i < nb_strings; i++) {
    copy[i] = strdup(strings[i]);
    if (copy[i] == NULL) {
      fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
      exit(1);
    }
  }

  return copy;
}


/**
 * openscop_util_strings_equal function:
 * this function returns true if the two arrays of strings are the same
 * (content-wise), false otherwise.
 * \param s1    The first array of strings.
 * \param nb_s1 The number of strings in the first array of string.
 * \param s2    The second array of strings.
 * \param nb_s2 The number of strings in the second array of string.
 * \return 1 if s1 and s2 are the same (content-wise), 0 otherwise.
 */
int openscop_util_strings_equal(char ** s1, int nb_s1, char ** s2, int nb_s2) {
  int i;
  
  if (s1 == s2)
    return 1;

  if (((s1 == NULL) && (s2 != NULL)) ||
      ((s1 != NULL) && (s2 == NULL)) ||
      (nb_s1 != nb_s2))
    return 0;

  for (i = 0; i < nb_s1; i++)
    if (strcmp(s1[i], s2[i]) != 0)
      return 0;

  return 1;
}


/*+***************************************************************************
 *                             Utility functions                             *
 *****************************************************************************/


/**
 * openscop_util_skip_blank_and_comments internal function.
 * This function reads the open file 'file' line by line and skips
 * blank/comment lines and spaces. The first line where there is some
 * useful information is stored at the address 'str' (the memory to
 * store the line must be allocated before the call to this function
 * and must be at least OPENSCOP_MAX_STRING*sizeof(char)). The pointer
 * to the first useful information in this line is returned by the
 * function.
 * \param file The (opened) file to read.
 * \param str  Address of an allocated space to store the first line
 *             that contains useful information.
 * \return The address of the the first useful digit in str.
 */
char * openscop_util_skip_blank_and_comments(FILE * file, char * str) {
  char * start;

  do {
    start = fgets(str, OPENSCOP_MAX_STRING, file);
    while ((start != NULL) && isspace(*start) && (*start != '\n'))
      start++;
  }
  while (start != NULL && (*start == '#' || *start == '\n'));

  return start;
}


/**
 * openscop_util_read_int internal function.
 * Read an int on the input 'file' or the input string 'str' depending on
 * which one is not NULL (exactly one of them must not be NULL).
 * \param file The file where to read an int (if not NULL).
 * \param str  The string where to read an int (if not NULL). This pointer
 *             is updated to reflect the read and points after the int.
 * \return The int that have been read.
 */
int openscop_util_read_int(FILE * file, char ** str) {
  char s[OPENSCOP_MAX_STRING], * start;
  int res;
  int i = 0;
  int read_int = 0;

  if ((file != NULL && str != NULL) || (file == NULL && str == NULL)) {
    fprintf(stderr, "[OpenScop] Error: one and only one of the two parameters"
                    " of util_read_int can be non-NULL\n");
    exit (1);
  }

  if (file != NULL) {
    // Parse from a file.
    start = openscop_util_skip_blank_and_comments(file, s);
    sscanf(start, " %d", &res);
  }
  if (str != NULL) {
    // Parse from a string.
    // Skip blank/commented lines.
    do {
      while (*str && **str && isspace(**str))
        ++(*str);
      if (**str == '#') {
        while (**str && **str != '\n')
          ++(*str);
      }
      else {
        // Build the chain to analyze.
        while (**str && !isspace(**str) && **str != '\n')
          s[i++] = *((*str)++);
        s[i] = '\0';
        if (sscanf(s, "%d", &res) != 1)	{
          fprintf(stderr, "[OpenScop] Error: an int was expected.\n");
          exit(1);
        }
        read_int = 1;
      }
    }
    while (! read_int);
  }

  return res;
}


/**
 * openscop_util_read_tail function:
 * this function puts the remainder of a file (from the current file pointer to
 * the end of the file) to a string and returns this string. This excepts the
 * first blank or commented lines (commented according to the OpenScop textual
 * format).
 * \param  file The file where to read the tail.
 * \return The string corresponding to the tail of the input file.
 */
char * openscop_util_read_tail(FILE * file) {
  int high_water_mark = OPENSCOP_MAX_STRING;
  int nb_chars = 0;
  char buff[OPENSCOP_MAX_STRING], *c;
  char * extensions;

  // - Skip blank/commented lines and spaces.
  c = openscop_util_skip_blank_and_comments(file, buff);
  if (c ==  NULL)
    return NULL;

  extensions = (char *)malloc(high_water_mark * sizeof(char));
  if (extensions == NULL) {
    fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
    exit(1);
  }
  
  strcpy(extensions, c);
  nb_chars = strlen(c);

  // - Copy everything else to the option tags field.
  while (!feof(file)) {
    extensions[nb_chars] = fgetc(file); 
    nb_chars++;

    if (nb_chars >= high_water_mark) {
      high_water_mark += high_water_mark;
      extensions = (char *)realloc(extensions, high_water_mark * sizeof(char));
      if (extensions == NULL) {
        fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
        exit(1);
      }
    }
  }

  // - 0-terminate the string.
  extensions = (char *)realloc(extensions, nb_chars * sizeof(char));
  extensions[nb_chars - 1] = '\0';

  return extensions;
}


/**
 * openscop_util_tag_content function:
 * This function returns a freshly allocated string containing the
 * content, in the given string 'str', between the tag 'tag' and
 * the tag 'endtag'. If the tag 'tag' is not found, returns NULL.
 * \param str    The string where to find a given content.
 * \param tag    The string that marks the beginning of the content.
 * \param endtag The string that marks the end of the content.
 * \return The string between 'tag' and 'endtag' in 'str'.
 */
char * openscop_util_tag_content(char * str, char * tag, char * endtag) {
  int i;
  char * start;
  char * stop;
  int size = 0;
  int lentag;
  char * res = NULL;

  if (str) {
    start = str;
    lentag = strlen(tag);
    for (; start && *start && strncmp(start, tag, lentag); ++start)
      continue;
    
    // The tag 'tag' was not found.
    if (! *start)
      return NULL;
    start += lentag;
    stop = start;
    lentag = strlen(endtag);
    for (size = 0; *stop && strncmp(stop, endtag, lentag); ++stop, ++size)
      continue;
    
    // the tag 'endtag' was not found.
    if (! *stop)
      return NULL;
    res = (char *)malloc((size + 1) * sizeof(char));
    if (res == NULL) {
      fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
      exit(1);
    }
    
    // Copy the chain between the two tags.
    for (++start, i = 0; start != stop; ++start, ++i)
      res[i] = *start;
    res[i] = '\0';
  }

  return res;
}


/**
 * openscop_util_safe_strcat function:
 * this function concatenates the string src to the string *dst
 * and reallocates *dst if necessary. The current size of the
 * *dst buffer must be *hwm (high water mark), if there is some
 * reallocation, this value is updated.
 * \param dst pointer to the destination string (may be reallocated).
 * \param src string to concatenate to dst.
 * \param hwm pointer to the size of the *dst buffer (may be updated).
 * TODO: This function is not that safe, improve it !
 */
void openscop_util_safe_strcat(char ** dst, char * src, int * hwm) {

  if (strlen(src) >= OPENSCOP_MAX_STRING) {
    fprintf(stderr, "[OpenScop] Error: string to concatenate is too long.\n");
    exit(1);
  }

  if (strlen(*dst) + strlen(src) >= *hwm) {
    *hwm += OPENSCOP_MAX_STRING;
    *dst = (char *)realloc(*dst, *hwm * sizeof(char));
    if (*dst == NULL) {
      fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
      exit(1);
    }
  }

  strcat(*dst, src);
}
