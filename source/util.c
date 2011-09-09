
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

  if ((file != NULL && str != NULL) || (file == NULL && str == NULL))
    OPENSCOP_error("one and only one of the two parameters"
                   " of util_read_int can be non-NULL");

  if (file != NULL) {
    // Parse from a file.
    start = openscop_util_skip_blank_and_comments(file, s);
    if (sscanf(start, " %d", &res) != 1)
      OPENSCOP_error("an int was expected");
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
        if (sscanf(s, "%d", &res) != 1)
          OPENSCOP_error("an int was expected");
        read_int = 1;
      }
    }
    while (! read_int);
  }

  return res;
}


/**
 * openscop_util_read_uptotag function:
 * this function reads a file up to a given tag (the tag is read) or the
 * end of file. It puts everything it reads in a string which is returned.
 * \param[in] file The file where to read the tail.
 * \param[in] tag  The tag which, when reached, stops the file reading.
 * \return The string that has been read from the file.
 */
char * openscop_util_read_uptotag(FILE * file, char * tag) {
  int high_water_mark = OPENSCOP_MAX_STRING;
  int nb_chars = 0;
  int lentag = strlen(tag);
  int tag_found = 0;
  char * res;

  OPENSCOP_malloc(res, char *, high_water_mark * sizeof(char));

  // - Copy everything else to the res string.
  while (!feof(file)) {
    res[nb_chars] = fgetc(file); 
    nb_chars++;

    if ((nb_chars >= lentag) &&
        (!strncmp(&res[nb_chars - lentag], tag, lentag))) {
      tag_found = 1;
      break;
    }

    if (nb_chars >= high_water_mark) {
      high_water_mark += high_water_mark;
      OPENSCOP_realloc(res, char *, high_water_mark * sizeof(char));
    }
  }

  if (!tag_found)
    OPENSCOP_info("tag was not found, end of file reached");

  // - 0-terminate the string.
  OPENSCOP_realloc(res, char *, (nb_chars + 1) * sizeof(char));
  res[nb_chars] = '\0';

  return res;
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
    OPENSCOP_malloc(res, char *, (size + 1) * sizeof(char));
    
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

  if (strlen(src) >= OPENSCOP_MAX_STRING)
    OPENSCOP_error("string to concatenate is too long");

  if (strlen(*dst) + strlen(src) >= *hwm) {
    *hwm += OPENSCOP_MAX_STRING;
    OPENSCOP_realloc(*dst, char *, *hwm * sizeof(char));
  }

  strcat(*dst, src);
}


/**
 * openscop_util_get_precision function:
 * this function returns the precision defined by the precision environment
 * variable or the highest available precision if it is not defined.
 * \return environment precision if defined or highest available precision.
 */
int openscop_util_get_precision() {
  int precision = OPENSCOP_PRECISION_DP;
  char * precision_env;

#ifdef OPENSCOP_GMP_IS_HERE
  precision = OPENSCOP_PRECISION_MP;
#endif

  precision_env = getenv(OPENSCOP_PRECISION_ENV);
  if (precision_env != NULL) {
    if (!strcmp(precision_env, OPENSCOP_PRECISION_ENV_SP))
      precision = OPENSCOP_PRECISION_SP;
    else if (!strcmp(precision_env, OPENSCOP_PRECISION_ENV_DP))
      precision = OPENSCOP_PRECISION_DP;
    else if (!strcmp(precision_env, OPENSCOP_PRECISION_ENV_MP))
      precision = OPENSCOP_PRECISION_MP;
    else
      OPENSCOP_warning("bad precision environment value");
  }

  return precision;
}


/**
 * openscop_util_print_provided function:
 * this function prints a "provided" boolean in a file (file, possibly stdout),
 * with a comment title according to the OpenScop specification.
 * \param[in] file     File where the information has to be printed.
 * \param[in] provided The provided boolean to print.
 * \param[in] title    A string to use as a title for the provided booblean.
 */
void openscop_util_print_provided(FILE * file, int provided, char * title) {
  if (provided) {
    fprintf(file, "# %s provided\n", title);
    fprintf(file, "1\n");
  }
  else {
    fprintf(file, "# %s not provided\n", title);
    fprintf(file, "0\n\n");
  }
}

