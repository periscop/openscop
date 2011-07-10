
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                            body.c                               **
     **-----------------------------------------------------------------**
     **                   First version: 25/06/2011                     **
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
# include <ctype.h>
# include <openscop/body.h>


/*+***************************************************************************
 *                         Structure display functions                       *
 *****************************************************************************/


/**
 * openscop_body_idump function:
 * this function displays an openscop_body_t structure (*body) into a
 * file (file, possibly stdout) in a way that trends to be understandable.
 * It includes an indentation level (level) in order to work with others
 * dumping functions.
 * \param[in] file  File where informations are printed.
 * \param[in] body  The body whose information has to be printed.
 * \param[in] level Number of spaces before printing, for each line.
 */
void openscop_body_idump(FILE * file, openscop_body_p body, int level) {
  int i, j;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (body != NULL) {
    fprintf(file, "+-- openscop_body_t\n");

    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    if (body->type == OPENSCOP_TYPE_STRING) {
      // Print the original iterator names.
      openscop_util_strings_idump(file, (char **)body->iterator,
                                  body->nb_iterators, level,
                                  "original iterator strings");

      // Print the original body expression.
      for (i = 0; i <= level; i++)
        fprintf(file, "|\t");
      if (body->expression != NULL)
        fprintf(file, "+-- Original expression: %s\n", (char *)body->expression);
      else
        fprintf(file, "+-- No original body expression\n");
    }
    else {
      for (i = 0; i <= level; i++)
        fprintf(file, "|\t");
      fprintf(file, "+-- Non textual information\n");
    }
  }
  else {
    fprintf(file, "+-- NULL body\n");
  }
  
  // The last line.
  for (j = 0; j <= level+1; j++)
    fprintf(file, "|\t");
  fprintf(file, "\n");
}


/**
 * openscop_body_dump function:
 * This function prints the content of a openscop_body_t structure
 * (*body) into  a file (file, possibly stdout).
 * \param file[in] File where informations are printed.
 * \param body[in] The body whose information has to be printed.
 */
void openscop_body_dump(FILE * file, openscop_body_p body) {
  openscop_body_idump(file, body, 0);
}


/**
 * openscop_body_print function:
 * This function prints the content of a openscop_body_t structure
 * (*body) into a file (file, possibly stdout) in the OpenScop format.
 * \param file[in]  File where informations are printed.
 * \param body[in]  The body whose information has to be printed.
 */
void openscop_body_print(FILE * file, openscop_body_p body) {
  int i;

  if ((body != NULL) && (body->type == OPENSCOP_TYPE_STRING)) {
    fprintf(file, "# Statement body is provided\n");
    fprintf(file, "1\n");
    if (body->nb_iterators > 0) {
      fprintf(file, "# Original iterator names\n");
      for (i = 0; i < body->nb_iterators; i++)
        fprintf(file, "%s ", (char *)body->iterator[i]);
      fprintf(file, "\n");
    }
    else {
      fprintf(file, "# No original iterator names\n");
    }
    fprintf(file, "# Statement body expression\n");
    fprintf(file, "%s\n", (char *)body->expression);
  }
  else {
    fprintf(file, "# Statement body is not provided\n");
    fprintf(file, "0\n");
  }
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/**
 * openscop_body_read function:
 * This function reads a openscop_body_t structure from an input stream
 * (possibly stdin).
 * \param[in] file         The input stream.
 * \param[in] nb_iterators The number of iterators.
 * \return A pointer to the body structure that has been read.
 */
openscop_body_p openscop_body_read(FILE * file, int nb_iterators) {
  openscop_body_p body = NULL;
  char buff[OPENSCOP_MAX_STRING], * start, * end;
  int nb_strings;

  if (file) {
    // Read the body information, if any.
    if (openscop_util_read_int(file, NULL) > 0) {
      body = openscop_body_malloc();
      body->type = OPENSCOP_TYPE_STRING;
    
      // Read the original iterator names.
      if (nb_iterators > 0) {
        body->iterator = (void *)openscop_util_strings_read(file, &nb_strings);
        body->nb_iterators = nb_strings;
        if (nb_iterators != nb_strings) {
          fprintf(stderr, "[OpenScop] Warning: not the expected number of "
                          "original iterators.\n");
        }
      }
      
      // Read the body:
      // - Skip blank/commented lines and spaces before the body.
      start = openscop_util_skip_blank_and_comments(file, buff);
      
      // - Remove the comments after the body.
      end = start;
      while ((*end != '#') && (*end != '\n'))
        end++;
      *end = '\0';
      
      // - Copy the body.
      body->expression = strdup(start);
    }
  }

  return body;
}


/*+***************************************************************************
 *                   Memory allocation/deallocation functions                *
 *****************************************************************************/


/**
 * openscop_body_malloc function:
 * This function allocates the memory space for a openscop_body_t
 * structure and sets its fields with default values. Then it returns a pointer
 * to the allocated space.
 * \return A pointer to an empty body with fields set to default values.
 */
openscop_body_p openscop_body_malloc() {
  openscop_body_p body;

  body = (openscop_body_p)malloc(sizeof(openscop_body_t));
  if (body == NULL) {
    fprintf(stderr, "[OpenScop] Error: memory overflow.\n");
    exit(1);
  }

  body->type         = OPENSCOP_UNDEFINED;
  body->nb_iterators = 0;
  body->iterator     = NULL;
  body->expression   = NULL;

  return body;
}


/**
 * openscop_body_free function:
 * This function frees the allocated memory for a openscop_body_t
 * structure.
 * \param[in,out] body The pointer to the body we want to free.
 */
void openscop_body_free(openscop_body_p body) {

  if (body != NULL) {
    openscop_util_strings_free((char**)(body->iterator), body->nb_iterators);
    if (body->expression != NULL)
      free(body->expression);

    free(body);
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_body_copy function:
 * This functions builds and returns a "hard copy" (not a pointer copy) of an
 * openscop_body_t data structure provided as parameter. However, let us
 * recall here that non-string elements are untouched by the OpenScop Library.
 * \param[in] body The pointer to the body we want to copy.
 * \return A pointer to the full copy of the body provided as parameter.
 */
openscop_body_p openscop_body_copy(openscop_body_p body) {
  openscop_body_p copy = NULL;

  if (body != NULL) {
    copy = openscop_body_malloc();
    copy->type = body->type;
    copy->nb_iterators = body->nb_iterators;
    if (body->type == OPENSCOP_TYPE_STRING) {
      copy->iterator = (void*)openscop_util_strings_copy(
                           (char**)body->iterator, body->nb_iterators);
      copy->expression = strdup(body->expression);
    }
  }

  return copy;
}


/**
 * openscop_body_equal function:
 * This function returns true if the two bodies are the same, false
 * otherwise (the usr field is not tested). However, let us
 * recall here that non-string elements are untouched by the OpenScop Library.
 * \param b1 The first body.
 * \param b2 The second body.
 * \return 1 if b1 and b2 are the same (content-wise), 0 otherwise.
 */
int openscop_body_equal(openscop_body_p b1, openscop_body_p b2) {
  
  if (b1 == b2)
    return 1;
 
  if (((b1 != NULL) && (b2 == NULL)) ||
      ((b1 == NULL) && (b2 != NULL))) {
    fprintf(stderr, "[OpenScop] info: bodies are not the same.\n"); 
    return 0;
  }

  if (b1->type != b2->type) {
    fprintf(stderr, "[OpenScop] info: body types are not the same.\n"); 
    return 0;
  }

  if (b1->type == OPENSCOP_TYPE_STRING) {
    if (!openscop_util_strings_equal((char**)b1->iterator, b1->nb_iterators,
                                     (char**)b2->iterator, b2->nb_iterators)) {
      fprintf(stderr, "[OpenScop] info: body iterators are not the same.\n"); 
      return 0;
    }

    if (((b1->expression == NULL) && (b2->expression != NULL)) ||
        ((b1->expression != NULL) && (b2->expression == NULL)) ||
        ((b1->expression != NULL)           &&
         (b2->expression != NULL)           &&
         (b1->type == OPENSCOP_TYPE_STRING) &&
         (b2->type == OPENSCOP_TYPE_STRING) &&
         (strcmp(b1->expression, b2->expression) != 0))) {
      fprintf(stderr,"[OpenScop] info: body expressions are not the same.\n"); 
      return 0;
    }
  }

  return 1;
}


/**
 * openscop_body_integrity_check function:
 * This function checks that a body is "well formed" according to some
 * expected properties (setting an expected value to OPENSCOP_UNDEFINED means
 * that we do not expect a specific value). It returns 0 if the check failed
 * or 1 if no problem has been detected.
 * \param[in] body                  The body we want to check.
 * \param[in] expected_nb_iterators Expected number of iterators.
 * \return 0 if the integrity check fails, 1 otherwise.
 */
int openscop_body_integrity_check(openscop_body_p body,
                                  int expected_nb_iterators) {

  if ((body != NULL) &&
      (expected_nb_iterators != OPENSCOP_UNDEFINED) &&
      (expected_nb_iterators != body->nb_iterators)) {
    fprintf(stderr, "[OpenScop] Warning: unexpected #original iterators.\n");
    return 0;
  }

  return 1;
}
