
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
 * \param[in] file    The file where the information has to be printed.
 * \param[in] strings The array of strings that has to be printed.
 * \param[in] level   Number of spaces before printing, for each line.
 */
void openscop_strings_idump(FILE * file, openscop_strings_p strings,
                            int level) {
  int i, nb_strings;
  
  for (i = 0; i < level; i++)
    fprintf(file, "|\t");
  
  if (strings != NULL) {
    nb_strings = openscop_strings_size(strings);
    fprintf(file, "+-- openscop_strings_t:");
    for (i = 0; i < nb_strings; i++)
      fprintf(file, " %s", strings->string[i]);
    fprintf(file, "\n");
  }
  else
    fprintf(file, "+-- NULL strings\n");

  // A blank line.
  for (i = 0; i <= level; i++)
    fprintf(file, "|\t");
  fprintf(file, "\n");
}


/**
 * openscop_strings_dump function:
 * this function prints the content of an openscop_strings_t structure
 * (*strings) into a file (file, possibly stdout).
 * \param[in] file    The file where the information has to be printed.
 * \param[in] strings The strings structure which has to be printed.
 */
void openscop_strings_dump(FILE * file, openscop_strings_p strings) {
  openscop_strings_idump(file, strings, 0);
}


/**
 * openscop_strings_sprint function:
 * this function prints the content of an openscop_strings_t structure
 * (*strings) into a string (returned) in the OpenScop textual format.
 * \param[in] strings The strings structure which has to be printed.
 * \return A string containing the OpenScop dump of the strings structure.
 */
char * openscop_strings_sprint(openscop_strings_p strings) {
  int i;
  int high_water_mark = OPENSCOP_MAX_STRING;
  char * string = NULL;
  char * buffer;

  if (strings != NULL) {
    OPENSCOP_malloc(string, char *, high_water_mark * sizeof(char));
    OPENSCOP_malloc(buffer, char *, OPENSCOP_MAX_STRING * sizeof(char));
    string[0] = '\0';
   
    // Print the begin tag.
    for (i = 0; i < openscop_strings_size(strings); i++) {
      sprintf(buffer, "%s", strings->string[i]);
      openscop_util_safe_strcat(&string, buffer, &high_water_mark);
      if (i < openscop_strings_size(strings) - 1)
        openscop_util_safe_strcat(&string, " ", &high_water_mark);
    }
    sprintf(buffer, "\n");
    openscop_util_safe_strcat(&string, buffer, &high_water_mark);
    free(buffer);
  }

  return string;
}


/**
 * openscop_strings_print function:
 * this function prints the content of an openscop_strings_t structure
 * (*body) into a file (file, possibly stdout) in the OpenScop format.
 * \param file[in]    File where informations are printed.
 * \param strings[in] The strings whose information has to be printed.
 */
void openscop_strings_print(FILE * file, openscop_strings_p strings) {
  char * string;
  
  string = openscop_strings_sprint(strings);
  if (string != NULL) {
    fprintf(file, "%s", string);
    free(string);
  }
}


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * openscop_strings_sread function:
 * this function reads a strings structure from a string complying to the
 * OpenScop textual format and returns a pointer to this strings structure.
 * The input string should only contain the list of strings this function
 * has to read (comments at the end of the line are accepted).
 * \param[in] input The input string where to find a strings structure.
 * \return A pointer to the strings structure that has been read.
 */
openscop_strings_p openscop_strings_sread(char * input) {
  char tmp[OPENSCOP_MAX_STRING];
  char * s;
  char ** string = NULL;
  int nb_strings;
  int i, count;
  openscop_strings_p strings = NULL;

  // Count the actual number of strings.
  nb_strings = 0;
  s = input;
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
    OPENSCOP_malloc(string, char **, sizeof(char *) * (nb_strings + 1));
    string[nb_strings] = NULL;

    // Read the desired number of strings.
    s = input;
    for (i = 0; i < nb_strings; i++) {
      for (count = 0; *s && ! isspace(*s) && *s != '#'; count++)
	tmp[count] = *(s++);
      tmp[count] = '\0';
      string[i] = strdup(tmp);
      if (string[i] == NULL)
        OPENSCOP_error("memory overflow");
      if (*s != '#')
	++s;
    }

    // Build the strings structure
    strings = openscop_strings_malloc();
    strings->string = string;
  }

  return strings;
}


/**
 * openscop_strings_read function.
 * this function reads a strings structure from a file (possibly stdin)
 * complying to the OpenScop textual format and returns a pointer to this
 * structure.
 * parameter nb_strings).
 * \param[in] file The file where to read the strings structure.
 * \return The strings structure that has been read.
 */
openscop_strings_p openscop_strings_read(FILE * file) {
  char buffer[OPENSCOP_MAX_STRING], * start;
  openscop_strings_p strings;

  start = openscop_util_skip_blank_and_comments(file, buffer);
  strings = openscop_strings_sread(start);

  return strings;
}
  

/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/


/**
 * openscop_strings_malloc function:
 * This function allocates the memory space for an openscop_strings_t
 * structure and sets its fields with default values. Then it returns a
 * pointer to the allocated space.
 * \return A pointer to an empty strings structure with fields set to
 *         default values.
 */
openscop_strings_p openscop_strings_malloc() {
  openscop_strings_p strings;

  OPENSCOP_malloc(strings, openscop_strings_p, sizeof(openscop_strings_t));
  strings->string = NULL;

  return strings;
}


/**
 * openscop_strings_free function:
 * this function frees the allocated memory for a strings data structure.
 * \param[in] strings The strings structure we want to free.
 */
void openscop_strings_free(openscop_strings_p strings) {
  int i;

  if (strings != NULL) {
    if (strings->string != NULL) {
      i = 0;
      while(strings->string[i] != NULL) {
        free(strings->string[i]);
        i++;
      }
      free(strings->string);
    }
    free(strings);
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_strings_clone function.
 * this function builds and return a "hard copy" (not a pointer copy) of an
 * strings structure provided as parameter.
 * \param[in] strings The strings structure to clone.
 * \return The clone of the strings structure.
 */
openscop_strings_p openscop_strings_clone(openscop_strings_p strings) {
  int i, nb_strings;
  openscop_strings_p clone = NULL;
  
  if (strings == NULL)
    return NULL;

  clone = openscop_strings_malloc();
  if ((nb_strings = openscop_strings_size(strings)) == 0)
    return clone;

  OPENSCOP_malloc(clone->string, char **, (nb_strings + 1) * sizeof(char *));
  clone->string[nb_strings] = NULL;
  for (i = 0; i < nb_strings; i++) {
    clone->string[i] = strdup(strings->string[i]);
    if (clone->string[i] == NULL)
      OPENSCOP_error("memory overflow");
  }

  return clone;
}


/**
 * openscop_strings_equal function:
 * this function returns true if the two strings structures are the same
 * (content-wise), false otherwise.
 * \param[in] s1 The first strings structure.
 * \param[in] s2 The second strings structure.
 * \return 1 if s1 and s2 are the same (content-wise), 0 otherwise.
 */
int openscop_strings_equal(openscop_strings_p s1, openscop_strings_p s2) {
  int i, nb_s1;
  
  if (s1 == s2)
    return 1;

  if (((s1 == NULL) && (s2 != NULL)) ||
      ((s1 != NULL) && (s2 == NULL)) ||
      ((nb_s1 = openscop_strings_size(s1)) != openscop_strings_size(s2)))
    return 0;

  for (i = 0; i < nb_s1; i++)
    if (strcmp(s1->string[i], s2->string[i]) != 0)
      return 0;

  return 1;
}


/**
 * openscop_strings_size function:
 * this function returns the number of elements in the NULL-terminated
 * strings array of the strings structure.
 * \param[in] strings The strings structure we need to know the size.
 * \return The number of strings in the strings structure.
 */
int openscop_strings_size(openscop_strings_p strings) {
  int size = 0;

  if ((strings != NULL) && (strings->string != NULL)) {
    while (strings->string[size] != NULL) {
      size++;
    }
  }

  return size;
}


/**
 * openscop_strings_encapsulate function:
 * this function builds a new strings structure to encapsulate the string
 * provided as a parameter (the reference to this string is used directly).
 * \param[in] string The string to encapsulate in a strings structure.
 * \return A new strings structure containing only the provided string.
 */
openscop_strings_p openscop_strings_encapsulate(char * string) {
  openscop_strings_p capsule = openscop_strings_malloc();
  
  OPENSCOP_malloc(capsule->string, char **, 2 * sizeof(char *));
  capsule->string[0] = string;
  capsule->string[1] = NULL;
  
  return capsule;
}


/**
 * openscop_strings_interface function:
 * this function creates an interface structure corresponding to the strings
 * structure and returns it).
 * \return An interface structure for the strings structure.
 */
openscop_interface_p openscop_strings_interface() {
  openscop_interface_p interface = openscop_interface_malloc();
  
  interface->URI    = strdup(OPENSCOP_URI_STRINGS);
  interface->idump  = (openscop_idump_f)openscop_strings_idump;
  interface->dump   = (openscop_dump_f)openscop_strings_dump;
  interface->sprint = (openscop_sprint_f)openscop_strings_sprint;
  interface->sread  = (openscop_sread_f)openscop_strings_sread;
  interface->malloc = (openscop_malloc_f)openscop_strings_malloc;
  interface->free   = (openscop_free_f)openscop_strings_free;
  interface->clone  = (openscop_clone_f)openscop_strings_clone;
  interface->equal  = (openscop_equal_f)openscop_strings_equal;

  return interface;
}


/**
 * openscop_strings_generate function:
 * this function generates a new strings structure containing
 * 'nb_strings' strings of the form "prefixXX" where XX goes from 1 to
 * nb_strings.
 * \param[in] prefix     The prefix of the generated strings.
 * \param[in] nb_strings The number of strings to generate.
 * \return A new strings structure containing generated strings.
 */
openscop_strings_p openscop_strings_generate(char * prefix, int nb_strings) {
  char ** strings = NULL;
  char buff[strlen(prefix) + 16]; // TODO: better (log10(INT_MAX) ?) :-D.
  int i;
  openscop_strings_p generated;

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

  generated = openscop_strings_malloc();
  generated->string = strings;
  return generated;
}


#if 0
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
#endif
