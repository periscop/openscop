
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                           extension.c                           **
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


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * openscop_extension_print_structure function:
 * Displays a openscop_extension_t structure (*extensions) into a file (file,
 * possibly stdout) in a way that trends to be understandable. It includes an
 * indentation level (level) in order to work with others print_structure
 * functions.
 * \param file       File where informations are printed.
 * \param extensions The extensions whose information have to be printed.
 * \param level      Number of spaces before printing, for each line.
 */
void
openscop_extension_print_structure(FILE * file,
                                   openscop_extension_p extension,
                                   int level)
{
  if (extension == NULL)
    return;

  switch (extension->type) {
    case OPENSCOP_EXTENSION_COMMENT: {
      openscop_comment_print_structure(file, extension->extension, level);
      break;
    }
    case OPENSCOP_EXTENSION_ARRAYS: {
      openscop_arrays_print_structure(file, extension->extension, level);
      break;
    }
    default: {
      fprintf(stderr, "[OpenScop] Error: unknown extension.\n");
      exit(1);
    }
  }
}


void openscop_extension_print(FILE * file, openscop_extension_p extension)
{

}

void openscop_extension_print_openscop(FILE * file,
                                       openscop_extension_p extension)
{

}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/

char * openscop_extension_read_string(FILE * file)
{
  int high_water_mark = OPENSCOP_MAX_STRING;
  int nb_chars = 0;
  char buff[OPENSCOP_MAX_STRING], *c;
  char * extensions;

  extensions = (char *)malloc(high_water_mark * sizeof(char));
  if (extensions == NULL)
  {
    fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
    exit(1);
  }
  
  // - Skip blank/commented lines and spaces.
  c = openscop_util_skip_blank_and_comments(file, buff);
  strcpy(extensions, c);
  nb_chars = strlen(c);

  // - Copy everything else to the option tags field.
  while (!feof(file))
  {
    extensions[nb_chars] = fgetc(file); 
    nb_chars++;

    //printf("EXTENSIONS: %s", extensions);
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

/*
openscop_extension_p openscop_extension_read(FILE * file)
{
  char * extension_string;
  openscop_extension_p extension = NULL;

  extension_string = openscop_extension_read_string(file);
  
  openscop_extension_add(&extension, extension_string,
                         OPENSCOP_EXTENSION_COMMENT, openscop_comment_read);   
  openscop_extension_add(&extension, extension_string,
                         OPENSCOP_EXTENSION_ARRAYS,  openscop_arrays_read); 

  return NULL;
}
*/


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/
/*
void openscop_extension(openscop_extension_p * extension, char * string,
                        int type, (void *)read(char *))
{
  void * new_ext;

  new_ext = (void *)
  if (*extension == NULL)
  {
    
  }

}
*/

openscop_extension_p openscop_extension_malloc()
{
  openscop_extension_p extension;

  extension = (openscop_extension_p)malloc(sizeof(openscop_extension_p));
  extension->type      = OPENSCOP_EXTENSION_UNDEFINED;
  extension->extension = NULL;
  extension->next      = NULL;

  return extension;
}


void openscop_extension_free(openscop_extension_p extension)
{


}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


openscop_extension_p openscop_extension_copy(openscop_extension_p extension)
{

  return NULL;
}


int openscop_extension_equal(openscop_extension_p x1, openscop_extension_p x2)
{

  return 1;
}


/*+***************************************************************************
 *                        Extension-Dependent Functions                      *
 *****************************************************************************/

/*
 * For each extension called FOOEXT that a programmer wishes to add to
 * OpenScop, the following functions must be provided in a dedicated
 * section (follow the "Array Extension" example):
 * - Display function (for internal use)
 * - Print function (to OpenScop's file format as a string)
 * - Read function (from OpenScop's file format as a string)
 * - Malloc function (allocate the extension part in an extension structure)
 * - Free function (free the extension part in an extension structure)
 * - Copy function
 * - Equal function
 */


/*+***************************************************************************
 *                                Array Extension                            *
 *****************************************************************************/


/*
char **
openscop_extension_read_tag_arrays(char * str, int * nb_arrays)
{
  int i, k, nb_names, array_index, max_index = 0;
  int high_water_mark = OPENSCOP_MAX_ARRAYS;
  char ** arrays;
  char ** tmpnames;
  char * content;
  char buff[OPENSCOP_MAX_STRING];

  content = openscop_util_tag_content(str, OPENSCOP_TAG_ARRAY_START,
                                           OPENSCOP_TAG_ARRAY_STOP);

  if (content == NULL)
  {
    fprintf(stderr, "[OpenScop] Info: no array optional tag.\n");
    *nb_arrays = 0;
    return NULL;
  }

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
*/
