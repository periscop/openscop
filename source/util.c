
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


/**
 * openscop_util_copy_strings internal function.
 * This function builds and return a "hard copy" (not a pointer copy) of an
 * array of strings.
 * \param strings    The array of strings to copy.
 * \param nb_strings The number of strings in the array to copy.
 * \return A pointer to the copy of the array of strings.
 */
char **
openscop_util_copy_strings(char ** strings, int nb_strings)
{
  int i;
  char ** copy;
  
  if ((strings == NULL) || (nb_strings == 0))
    return NULL;

  copy = (char **)malloc(nb_strings * sizeof(char *));

  for (i = 0; i < nb_strings; i++)
    copy[i] = strdup(strings[i]);

  return copy;
}


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
char * openscop_util_skip_blank_and_comments(FILE * file, char * str)
{
  char * start;

  do
  {
    start = fgets(str, OPENSCOP_MAX_STRING, file);
    while ((start != NULL) && isspace(*start) && (*start != '\n'))
      start++;
  }
  while (start != NULL && (*start == '#' || *start == '\n'));

  return start;
}


/**
 * openscop_util_read_strings internal function.
 * Read a line in the input 'file' and extract the first 'nb_strings' strings
 * from it. nb_strings is a maximum number (the special value -1 corresponds
 * to infinity). If *max is not NULL, it is updated with the maximum number
 * of strings that could have been read. It returns the NULL-terminated array
 * of strings that have been read.
 * \param file       The file where to read some strings.
 * \param nb_strings Maximum number of strings to read (-1: infinity).
 * \param max        Address to store the maximum number of strings that could
 *                   have been read (stored if the address is not NULL).
 * \return An array of strings.
 */
char **
openscop_util_read_strings(FILE * file, int nb_strings, int * max)
{
  char str[OPENSCOP_MAX_STRING];
  char tmp[OPENSCOP_MAX_STRING];
  char * s, * start;
  char ** res = NULL;
  int i, count, actual_nb_strings = 0;

  // Skip blank/commented lines and spaces.
  start = openscop_util_skip_blank_and_comments(file, str);

  // Count the actual number of strings.
  s = start;
  while (1)
  {
    for (count = 0; *s && ! isspace(*s) && *s != '#'; ++count)
      s++;
    
    if (count != 0)
      actual_nb_strings++;

    if ((*s == '#') || (*s == '\n'))
      break;
    else
      ++s;
  }

  // Update the number of strings if necessary.
  if ((nb_strings == -1) || (actual_nb_strings < nb_strings))
    nb_strings = actual_nb_strings;

  if (max != NULL)
    *max = actual_nb_strings;
  
  // Allocate the array of strings. Make it NULL-terminated.
  res = (char **) malloc(sizeof(char *) * (nb_strings + 1));
  res[nb_strings] = NULL;

  // Read the desired number of strings.
  s = start;
  for (i = 0; i < nb_strings; ++i)
  {
    for (count = 0; *s && ! isspace(*s) && *s != '#'; ++count)
      tmp[count] = *(s++);
    tmp[count] = '\0';
    res[i] = strdup(tmp);
    if (*s != '#')
      ++s;
  }

  return res;
}


/**
 * openscop_util_read_int internal function.
 * Read an int on the input 'file' or the input string 'str' depending on
 * which one is not NULL.
 * \param file The file where to read an int (if not NULL).
 * \param str  The string where to read an int (if not NULL). This pointer
 *             is updated to reflect the read and points after the int.
 * \return The int that have been read.
 */
int
openscop_util_read_int(FILE * file, char ** str)
{
  char s[OPENSCOP_MAX_STRING], * start;
  int res;
  int i = 0;
  int read_int = 0;

  if ((file != NULL && str != NULL) || (file == NULL && str == NULL))
  {
    fprintf(stderr, "[OpenScop] Error: one and only one of the two parameters"
                    " of util_read_int can be non-NULL\n");
    exit (1);
  }

  if (file != NULL)
  {
    // Parse from a file.
    start = openscop_util_skip_blank_and_comments(file, s);
    sscanf(start, " %d", &res);
  }
  if (str != NULL)
  {
    // Parse from a string.
    // Skip blank/commented lines.
    do
    {
      while (*str && **str && isspace(**str))
        ++(*str);
      if (**str == '#')
      {
        while (**str && **str != '\n')
          ++(*str);
      }
      else
      {
        // Build the chain to analyze.
        while (**str && !isspace(**str) && **str != '\n')
          s[i++] = *((*str)++);
        s[i] = '\0';
        sscanf(s, "%d", &res);
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
char *
openscop_util_read_tail(FILE * file)
{
  int high_water_mark = OPENSCOP_MAX_STRING;
  int nb_chars = 0;
  char buff[OPENSCOP_MAX_STRING], *c;
  char * extensions;

  // - Skip blank/commented lines and spaces.
  c = openscop_util_skip_blank_and_comments(file, buff);
  if (c ==  NULL)
    return NULL;

  extensions = (char *)malloc(high_water_mark * sizeof(char));
  if (extensions == NULL)
  {
    fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
    exit(1);
  }
  
  strcpy(extensions, c);
  nb_chars = strlen(c);

  // - Copy everything else to the option tags field.
  while (!feof(file))
  {
    extensions[nb_chars] = fgetc(file); 
    nb_chars++;

    if (nb_chars >= high_water_mark)
    {
      high_water_mark += high_water_mark;
      extensions = (char *)realloc(extensions, high_water_mark * sizeof(char));
      if (extensions == NULL)
      {
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


void
openscop_util_free_name_array(char ** name_array, int nb_names)
{
  int i;

  for (i = 0; i < nb_names; i++)
    free(name_array[i]);
  free(name_array);
}


/**
 * openscop_util_generate_names internal function:
 * This function generates an array of size 'nb' of chars of the form
 * "seedXX" where XX goes from 1 to nb.
 * \param seed  The prefix for the created names.
 * \param nb    The number of names to generate.
 * \return An array of 'nb' generated strings.
 */
char **
openscop_util_generate_names(char * seed, int nb)
{
  char ** res = NULL;
  char buff[strlen(seed) + 16];
  int i;

  if (nb)
  {
    res = (char **)malloc(sizeof(char *) * nb);
    if (res == NULL)
    {
      fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
      exit(1);
    }
    for (i = 0; i < nb; ++i)
    {
      sprintf(buff, "%s%d", seed, i + 1);
      res[i] = strdup(buff);
    }
  }

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
char *
openscop_util_tag_content(char * str, char * tag, char * endtag)
{
  int i;
  char * start;
  char * stop;
  int size = 0;
  int lentag;
  char * res = NULL;

  if (str)
  {
    start = str;
    lentag = strlen(tag);
    for (; start && *start && strncmp(start, tag, lentag); ++start)
      ;
    // The tag 'tag' was not found.
    if (! *start)
      return NULL;
    start += lentag;
    stop = start;
    lentag = strlen(endtag);
    for (size = 0; *stop && strncmp(stop, endtag, lentag); ++stop, ++size)
      ;
    // the tag 'endtag' was not found.
    if (! *stop)
      return NULL;
    res = (char *)malloc((size + 1) * sizeof(char));
    if (res == NULL)
    {
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


char **
openscop_util_read_tag_arrays(char * str, int * nb_arrays)
{
  int i, k, nb_names, array_index, max_index = 0;
  int high_water_mark = OPENSCOP_MAX_ARRAYS;
  char ** arrays;
  char ** tmpnames;
  char * content, * content_backup;
  char buff[OPENSCOP_MAX_STRING];

  content = openscop_util_tag_content(str, OPENSCOP_TAG_ARRAY_START,
                                           OPENSCOP_TAG_ARRAY_STOP);

  if (content == NULL)
  {
    fprintf(stderr, "[OpenScop] Info: no array optional tag.\n");
    *nb_arrays = 0;
    return NULL;
  }
  content_backup = content;

  // Allocate the array of names.
  arrays = (char **)malloc(high_water_mark * sizeof(char *));
  for (i = 0; i < high_water_mark; i++)
    arrays[i] = NULL;

  // Find the number of names provided.
  nb_names = openscop_util_read_int(NULL, &content);

  // Get each array name.
  for (k = 0; k < nb_names; k++)
  { 
    // Skip blank or commented lines.
    while (*content == '#' || *content == '\n')
    {
      for (; *content != '\n'; ++content)
        ;
      ++content;
    }

    // Get the array name index.
    for (i = 0; *content && ! isspace(*content); ++i, ++content)
      buff[i] = *content;
    buff[i] = '\0';
    sscanf(buff, "%d", &array_index);
    max_index = (max_index > array_index) ? max_index : array_index;
    if (array_index > high_water_mark)
    { 
      fprintf(stderr, "[OpenScop] Info: array name indices sound high.\n");
      high_water_mark += OPENSCOP_MAX_ARRAYS;
      arrays = (char **)realloc(arrays, high_water_mark * sizeof(char *));
      if (arrays == NULL)
      {
        fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
        exit(1);
      }
      for (i = high_water_mark - OPENSCOP_MAX_ARRAYS; i < high_water_mark; i++)
        arrays[i] = NULL;
    }
    if (array_index <= 0)
    {
      fprintf(stderr, "[OpenScop] Error: array index must be > 0.\n");
      exit(1);
    }
    
    // Get the array name in buff.
    while (*content && isspace(*content))
      ++content;
    for (i = 0; *content && ! isspace(*content); ++i, ++content)
      buff[i] = *content;
    buff[i] = '\0';

    // Array index is in 0-basis.
    if (arrays[array_index - 1] != NULL)
    {
      fprintf(stderr, "[OpenScop] Warning: two array names have the "
                      "same index.\n");
      free(arrays[array_index - 1]);
    }
    arrays[array_index - 1] = strdup(buff);

    // Go to the end of line.
    while (*content && *content != '\n')
      ++content;
  }
  free(content_backup);

  // Free unused memory.
  arrays = (char **)realloc(arrays, max_index * sizeof(char *));

  // Fill the missing names (and let's hope there is no need for higher index).
  tmpnames = openscop_util_generate_names("var", max_index);
  for (i = 0; i < max_index; i++)
  {
    if (arrays[i] == NULL || arrays[i][0] == '\0')
      arrays[i] = tmpnames[i]; // Use a generated name.
    else
      free(tmpnames[i]);       // Use a read name.
  }
  free(tmpnames);
  
  if (OPENSCOP_DEBUG == 1)
  {
    printf("max_index: %d\n", max_index); 
    for (i = 0; i < max_index; i++)
      printf("%s ", arrays[i]);
    printf("\n");
  }

  *nb_arrays = max_index;
  return arrays;
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
 */
void
openscop_util_safe_strcat(char ** dst, char * src, int * hwm)
{

  if (strlen(src) >= OPENSCOP_MAX_STRING)
  {
    fprintf(stderr, "[OpenScop] Error: string to concatenate is too long.\n");
    exit(1);
  }

  if (strlen(*dst) + strlen(src) >= *hwm)
  {
    *hwm += OPENSCOP_MAX_STRING;
    *dst = (char *)realloc(*dst, *hwm * sizeof(char));
    if (*dst == NULL)
    {
      fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
      exit(1);
    }
  }

  strcat(*dst, src);
}




