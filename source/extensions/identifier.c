
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                    extensions/identifier.c                      **
     **-----------------------------------------------------------------**
     **                   First version: 30/12/2014                     **
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
#include <limits.h>

#include <osl/macros.h>
#include <osl/util.h>
#include <osl/interface.h>
#include <osl/extensions/identifier.h>


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/

/**
 * osl_identifier_idump function:
 * this function displays an osl_identifier_t structure (*identifier) into a
 * file (file, possibly stdout) in a way that trends to be understandable. It
 * includes an indentation level (level) in order to work with others
 * idump functions.
 * \param[in] file        The file where the information has to be printed.
 * \param[in] identifier  The identifier structure to print.
 * \param[in] level       Number of spaces before printing, for each line.
 */
void osl_identifier_idump(FILE * file, osl_identifier_p identifier, int level) {
  int j;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (identifier != NULL)
    fprintf(file, "+-- osl_identifier_t\n");
  else
    fprintf(file, "+-- NULL identifier\n");

  if (identifier != NULL) {
    // Go to the right level.
    for(j = 0; j <= level; j++)
      fprintf(file, "|\t");

    // Display the identifier (without any carriage return).
    fprintf(file, "identifier: %d\n", identifier->id);
  }

  // The last line.
  for (j = 0; j <= level; j++)
    fprintf(file, "|\t");
  fprintf(file, "\n");
}

/**
 * osl_identifier_dump function:
 * this function prints the content of an osl_identifier_t structure
 * (*identifier) into a file (file, possibly stdout).
 * \param[in] file       The file where the information has to be printed.
 * \param[in] identifier The identifier structure to print.
 */
void osl_identifier_dump(FILE *file, osl_identifier_p identifier) {
  osl_identifier_idump(file, identifier, 0);
}

/**
 * osl_identifier_sprint function:
 * this function prints the content of an osl_identifier_t structure
 * (*identifier) into a string (returned) in the OpenScop textual format.
 * \param[in] identifier The identifier structure to print.
 * \return A string containing the OpenScop dump of the identifier structure.
 */
char * osl_identifier_sprint(osl_identifier_p identifier) {
  int high_water_mark = OSL_MAX_STRING;
  char * string = NULL;
  char buffer[OSL_MAX_STRING];

  if (identifier != NULL) {
    OSL_malloc(string, char *, high_water_mark * sizeof(char));
    string[0] = '\0';

    sprintf(buffer, "%d\n", identifier->id);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);

    // Keep only the memory space we need.
    OSL_realloc(string, char *, (strlen(string) + 1) * sizeof(char));
  }

  return string;
}

/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/

/**
 * osl_identifier_sread function:
 * this function reads a identifier structure from a string complying to the
 * OpenScop textual format and returns a pointer to this identifier structure.
 * The input parameter is updated to the position in the input string this
 * function reach right after reading the identifier structure.
 * \param[in,out] input The input string where to find a identifier.
 *                      Updated to the position after what has been read.
 * \return A pointer to the identifier structure that has been read.
 */
osl_identifier_p osl_identifier_sread(char ** input) {
  osl_identifier_p identifier;

  if (*input == NULL) {
    OSL_debug("no identifier optional tag");
    return NULL;
  }

  // Build the identifier structure
  identifier = osl_identifier_malloc();
  if (sscanf(*input, "%d", &identifier->id) != 1) 
    OSL_error("integer identifier expected");

  return identifier;
}

/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/

/**
 * osl_identifier_malloc function:
 * this function allocates the memory space for an osl_identifier_t
 * structure and sets its fields with default values. Then it returns a
 * pointer to the allocated space.
 * \return A pointer to an empty identifier structure with fields set to
 *         default values.
 */
osl_identifier_p osl_identifier_malloc() {
  osl_identifier_p identifier;

  OSL_malloc(identifier, osl_identifier_p, sizeof(osl_identifier_t));
  identifier->id = OSL_UNDEFINED;

  return identifier;
}

/**
 * osl_identifier_free function:
 * this function frees the allocated memory for an osl_identifier_t
 * structure.
 * \param[in,out] identifier The pointer to the identifier structure to free.
 */
void osl_identifier_free(osl_identifier_p identifier) {
  if (identifier != NULL)
    free(identifier);
}

/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/

/**
 * osl_identifier_clone function:
 * This function provided for consistency with osl_interface_p only.
 * Identifiers must be unique and are not supposed to be cloned.
 * \param[in] identifier The identifier structure to clone.
 * \return A carbon-copy of the identifier structure with the same value.
 */
osl_identifier_p osl_identifier_clone(osl_identifier_p identifier) {
  osl_identifier_p clone;
  OSL_warning("unique identifiers must not be cloned");

  clone = osl_identifier_malloc();
  clone->id = identifier->id;
  return clone;
}

/**
 * osl_identifier_equal function:
 * this function returns true if the two identifier structures are the same
 * (content-wise), false otherwise.
 * \param[in] c1  The first identifier structure.
 * \param[in] c2  The second identifier structure.
 * \return 1 if c1 and c2 are the same (content-wise), 0 otherwise.
 */
int osl_identifier_equal(osl_identifier_p i1, osl_identifier_p i2) {
  if (i1 == i2)
    return 1;

  // Case of both NULLs is accounted for in the previous condition.
  if (i1 == NULL || i2 == NULL)
    return 0;

  return i1->id == i2->id;
}

/**
 * osl_identifier_interface function:
 * this function creates an interface structure corresponding to the identifier
 * extension and returns it).
 * \return An interface structure for the identifier extension.
 */
osl_interface_p osl_identifier_interface() {
  osl_interface_p interface = osl_interface_malloc();

  OSL_strdup(interface->URI, OSL_URI_IDENTIFIER);
  interface->idump  = (osl_idump_f) osl_identifier_idump;
  interface->sprint = (osl_sprint_f)osl_identifier_sprint;
  interface->sread  = (osl_sread_f) osl_identifier_sread;
  interface->malloc = (osl_malloc_f)osl_identifier_malloc;
  interface->free   = (osl_free_f)  osl_identifier_free;
  interface->clone  = (osl_clone_f) osl_identifier_clone;
  interface->equal  = (osl_equal_f) osl_identifier_equal;

  return interface;
}

/**
 * osl_identifier_generate function:
 * this function generates consecutive unique identifiers for all the
 * statements in the scop provided as the argument.  It creates a new
 * identifier extensions for the statement unless the statement already
 * contains such extensions, in which case it updates the identifier value.
 * \param[in,out] scop The scop to generate unique identifiers for.
 */
void osl_identifier_generate(osl_scop_p scop) {
  osl_statement_p stmt;
  osl_identifier_p identifier;
  int consecutive = 1;

  for ( ; scop != NULL; scop = scop->next) {
    for (stmt = scop->statement; stmt != NULL; stmt = stmt->next) {
      identifier = (osl_identifier_p) osl_generic_lookup(stmt->extension,
                                                         OSL_URI_IDENTIFIER);
      if (identifier == NULL) {
        identifier = osl_identifier_malloc();
        if (stmt->extension == NULL)
          stmt->extension = osl_generic_shell(identifier, osl_identifier_interface());
        else
          osl_generic_add(&stmt->extension, osl_generic_shell(identifier, osl_identifier_interface()));
      }
      identifier->id = consecutive++;
    }
  }
}

/**
 * osl_identifier_is_unique function:
 * this function checks whether all identifiers of the statements in the scop are unique.
 * \param[in] scop The scop to check identifiers for uniquiness.
 * \return 1 if all identifiers are unique, 0 otherwise.
 */
int osl_identifier_is_unique(osl_scop_p scop) {
  osl_statement_p stmt;
  osl_identifier_p identifier;
  int *ids, result = 1;
  size_t size, used, i, j;

  size = 10;
  used = 0;
  OSL_malloc(ids, int *, size * sizeof(int));

  for ( ; scop != NULL; scop = scop->next) {
    for (stmt = scop->statement; stmt != NULL; stmt = stmt->next) {
      identifier = (osl_identifier_p) osl_generic_lookup(stmt->extension,
                                                         OSL_URI_IDENTIFIER);
      if (identifier != NULL) {
        ids[used++] = identifier->id;
        if (used >= size) {
          size *= 2;
          OSL_realloc(ids, int *, size * sizeof(int));
        }
      }
    }
  }

  for (i = 0; i < used; i++) {
    for (j = i + 1; j < used; j++) {
      if (ids[i] == ids[j]) {
        result = 0;
        break;
      }
    }
    if (result == 0)
      break;
  }

  free(ids);
  return result;
}

/**
 * osl_identifier_generate_one function:
 * this function generates a new identifier structure with the integer
 * identifier that is not present in the given scop.
 * \param[in] scop The scop with respect to which the identifier should be unique.
 * \return The unique identifier.
 */
osl_identifier_p osl_identifier_generate_one(osl_scop_p scop) {
  osl_statement_p stmt;
  osl_identifier_p identifier;
  int id;

  for ( ; scop != NULL; scop = scop->next) {
    for (stmt = scop->statement; stmt != NULL; stmt = stmt->next) {
      identifier = (osl_identifier_p) osl_generic_lookup(stmt->extension,
                                                         OSL_URI_IDENTIFIER);
      if (identifier != NULL) {
        id = OSL_max(id, identifier->id);
      }
    }
  }

  if (id == INT_MAX)
    OSL_warning("identifier overflow");
  identifier = osl_identifier_malloc();
  identifier->id = (id + 1);

  return identifier;
}

/**
 * osl_identifier_statements_equal function:
 * this function checks whether two statements have the same identifier.
 * \param[in] stmt1 The first statement to compare.
 * \param[in] stmt2 The second statement to compare.
 * \return 1 if the statements have equal identifiers, 0 otherwise.
 */
int osl_identifier_statements_equal(osl_statement_p stmt1, osl_statement_p stmt2) {
  osl_identifier_p id1, id2;

  id1 = (osl_identifier_p) osl_generic_lookup(stmt1->extension, OSL_URI_IDENTIFIER);
  id2 = (osl_identifier_p) osl_generic_lookup(stmt2->extension, OSL_URI_IDENTIFIER);
  if (id1 == NULL || id2 == NULL)
    return 0;
  return osl_identifier_equal(id1, id2);
}

/**
 * osl_identifier_statement_lookup function:
 * this function looks up in the list of statements a statement such that its
 * identifier is equal to the provided one.
 * \param[in] stmt The list of statements.
 * \param[in] id   The identifier to look for.
 * \return The pointer to the statement with given identifier if it exists,
 *         \c NULL otherwise.
 */
osl_statement_p osl_identifier_statement_lookup(osl_statement_p stmt, osl_identifier_p id) {
  osl_identifier_p identifier;

  if (id == NULL)
    return NULL;

  for ( ; stmt != NULL; stmt = stmt->next) {
    identifier = (osl_identifier_p) osl_generic_lookup(stmt->extension, OSL_URI_IDENTIFIER);
    if (identifier == NULL)
      continue;
    if (osl_identifier_equal(identifier, id))
      return stmt;
  }
  return NULL;
}
