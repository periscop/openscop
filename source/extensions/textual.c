
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                     extensions/textual.c                        **
     **-----------------------------------------------------------------**
     **                   First version: 15/17/2010                     **
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
# include <openscop/extensions/textual.h>


/* CAUTION : TEXTUAL IS A VERY SPECIAL CASE: DO NOT USE IT AS AN EXAMPLE !!! */


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * openscop_textual_idump function:
 * this function displays an openscop_textual_t structure (*textual) into a
 * file (file, possibly stdout) in a way that trends to be understandable. It
 * includes an indentation level (level) in order to work with others
 * print_structure functions.
 * \param file    The file where the information has to be printed.
 * \param textual The textual structure whose information has to be printed.
 * \param level   Number of spaces before printing, for each line.
 */
void openscop_textual_idump(FILE * file, openscop_textual_p textual,
                             int level) {
  int j;
  char * tmp;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (textual != NULL) {
    fprintf(file, "+-- openscop_textual_t: ");
    
    // Display the textual message (without any carriage return).
    tmp = strdup(textual->textual);
    for (j = 0; j < strlen(tmp); j++)
      if (tmp[j] == '\n')
	tmp[j] = ' ';

    if (strlen(tmp) > 40) {
      for (j = 0; j < 20; j++)
        fprintf(file, "%c", tmp[j]);
      fprintf(file, "   ...   ");
      for (j = strlen(tmp) - 20; j < strlen(tmp); j++)
        fprintf(file, "%c", tmp[j]);
      fprintf(file, "\n");
    }
    else {
      fprintf(file,"%s\n", tmp);
    }
    free(tmp);
  }
  else {
    fprintf(file, "+-- NULL textual\n");
  }

  // The last line.
  for (j = 0; j <= level; j++)
    fprintf(file, "|\t");
  fprintf(file, "\n");
}


/**
 * openscop_textual_dump function:
 * this function prints the content of an openscop_textual_t structure
 * (*textual) into a file (file, possibly stdout).
 * \param file    The file where the information has to be printed.
 * \param textual The textual structure whose information has to be printed.
 */
void openscop_textual_dump(FILE * file, openscop_textual_p textual) {
  openscop_textual_idump(file, textual, 0);
}



#if 0
/**
 * openscop_textual_sprint function:
 * this function prints the content of an openscop_textual_t structure
 * (*textual) into a string (returned) in the OpenScop textual format.
 * \param  textual The textual structure whose information has to be printed.
 * \return A string containing the OpenScop dump of the textual structure.
 */
char * openscop_textual_sprint(openscop_textual_p textual) {
  char * string = NULL;

  if ((textual != NULL) && (textual->textual != NULL)) {
    if (strlen(textual->textual) > OPENSCOP_MAX_STRING) 
      OPENSCOP_error("textual too long");
    
    string = strdup(textual->textual);
    if (string == NULL)
      OPENSCOP_error("memory overflow");
  }

  return string;
}
#else
/**
 * openscop_textual_sprint function:
 * this function returns NULL. This is part of the special behavior of
 * the textual option (printing it along with other options would double
 * the options...).
 * \param  textual The textual structure whose information has to be printed.
 * \return NULL.
 */
char * openscop_textual_sprint(openscop_textual_p textual) {

  return NULL;
}
#endif


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/

/**
 * openscop_textual_sread function:
 * this function reads a textual structure from a string complying to the
 * OpenScop textual format and returns a pointer to this textual structure.
 * The string should contain only one textual format of a textual structure.
 * \param  extensions The input string where to find a textual structure.
 * \return A pointer to the textual structure that has been read.
 */
openscop_textual_p openscop_textual_sread(char * extensions) {
  openscop_textual_p textual = NULL;

  if (extensions != NULL) {
    if (strlen(extensions) > OPENSCOP_MAX_STRING) 
      OPENSCOP_error("textual too long");

    textual = openscop_textual_malloc();
    textual->textual = strdup(extensions);
    if (textual->textual == NULL)
      OPENSCOP_error("memory overflow");
  }

  return textual;
}


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/


/**
 * openscop_textual_malloc function:
 * This function allocates the memory space for an openscop_textual_t
 * structure and sets its fields with default values. Then it returns a
 * pointer to the allocated space.
 * \return A pointer to an empty textual structure with fields set to
 *         default values.
 */
openscop_textual_p openscop_textual_malloc() {
  openscop_textual_p textual;

  OPENSCOP_malloc(textual, openscop_textual_p, sizeof(openscop_textual_t));
  textual->textual = NULL;

  return textual;
}


/**
 * openscop_textual_free function:
 * This function frees the allocated memory for an openscop_textual_t
 * structure.
 * \param textual The pointer to the textual structure we want to free.
 */
void openscop_textual_free(openscop_textual_p textual) {
  if (textual != NULL) {
    if(textual->textual != NULL)
      free(textual->textual);
    free(textual);
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_textual_clone function:
 * This function builds and returns a "hard copy" (not a pointer copy) of an
 * openscop_textual_t data structure.
 * \param textual The pointer to the textual structure we want to copy.
 * \return A pointer to the copy of the textual structure.
 */
openscop_textual_p openscop_textual_clone(openscop_textual_p textual) {
  openscop_textual_p copy;

  if (textual == NULL)
    return NULL;

  copy = openscop_textual_malloc();
  copy->textual = strdup(textual->textual);
  if ((copy->textual == NULL) && (textual->textual != NULL))
    OPENSCOP_error("memory overflow");

  return copy;
}


#if 0
/**
 * openscop_textual_equal function:
 * this function returns true if the two textual structures are the same
 * (content-wise), false otherwise.
 * \param f1  The first textual structure.
 * \param ff  The second textual structure.
 * \return 1 if f1 and f2 are the same (content-wise), 0 otherwise.
 */
int openscop_textual_equal(openscop_textual_p f1, openscop_textual_p f2) {
 
  if (f1 == f2)
    return 1;

  if (((f1 == NULL) && (f2 != NULL)) || ((f1 != NULL) && (f2 == NULL)))
    return 0;

  if (strcmp(f1->textual, f2->textual))
    return 0;

  return 1;
}
#else
/**
 * openscop_textual_equal function:
 * this function returns 1. This is part of the special behavior of
 * the textual option (the text string can be easily different while the
 * options are actually identical.
 * \param f1  The first textual structure.
 * \param ff  The second textual structure. 
 * \return 1.
 */
int openscop_textual_equal(openscop_textual_p f1, openscop_textual_p f2) {

  return 1;
}
#endif


/**
 * openscop_textual_generate_id function:
 * this function creates an identity structure corresponding to the textual
 * extension and returns it).
 * \return An identity structure corresponding to the textual extension.
 */
openscop_extension_id_p openscop_textual_generate_id() {
  openscop_extension_id_p id = openscop_extension_id_malloc();
  
  id->URI    = strdup(OPENSCOP_URI_TEXTUAL);
  id->idump  = (openscop_idump_f)openscop_textual_idump;
  id->dump   = (openscop_dump_f)openscop_textual_dump;
  id->sprint = (openscop_sprint_f)openscop_textual_sprint;
  id->sread  = (openscop_sread_f)openscop_textual_sread;
  id->malloc = (openscop_malloc_f)openscop_textual_malloc;
  id->free   = (openscop_free_f)openscop_textual_free;
  id->clone  = (openscop_clone_f)openscop_textual_clone;
  id->equal  = (openscop_equal_f)openscop_textual_equal;

  return id;
}

