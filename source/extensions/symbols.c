
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                     extensions/symbols.c                        **
     **-----------------------------------------------------------------**
     **                   First version: 07/03/2012                     **
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
 * Cedric Bastoul      <Cedric.Bastoul@u-psud.fr>                            *
 * Louis-Noel Pouchet  <Louis-Noel.pouchet@inria.fr>                         *
 * Prasanth Chatharasi <prasanth@iith.ac.in>                                 *
 *                                                                           *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <osl/macros.h>
#include <osl/util.h>
#include <osl/interface.h>
#include <osl/extensions/symbols.h>

/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * osl_symbols_idump function:
 * this function displays an osl_symbols_t structure (*symbols) into a
 * file (file, possibly stdout) in a way that trends to be understandable. It
 * includes an indentation level (level) in order to work with others
 * idump functions.
 * \param[in] file    The file where the information has to be printed.
 * \param[in] symbols The symbols structure to print.
 * \param[in] level   Number of spaces before printing, for each line.
 */
void osl_symbols_idump(FILE * file, osl_symbols_p symbols, int level) {

  int i, j, first = 1, number = 1;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (symbols != NULL)
    fprintf(file, "+-- osl_symbols_t\n");
  else
    fprintf(file, "+-- NULL symbols\n");

  while (symbols != NULL) {
    if (!first) {
      // Go to the right level.
      for (j = 0; j < level; j++)
        fprintf(file, "|\t");
      fprintf(file, "|   osl_symbol_t (node %d)\n", number);
    }
    else
      first = 0;

    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");


    // Print the identifier.
    for (i = 0; i <= level; i++)
      fprintf(file, "|\t");
    if (symbols->identifier != NULL) {
      fprintf(file, "+-- Identifier: ");
      osl_generic_idump(file, symbols->identifier, level);
    }
    else
      fprintf(file, "+-- Unknown identifier\n");

    // A blank line.
    for(j = 0; j <= level + 1; j++)
      fprintf(file, "|\t") ;
    fprintf(file, "\n") ;

    // Print the data type of identifier.
    for (i = 0; i <= level; i++)
      fprintf(file, "|\t");
    if (symbols->datatype != NULL) {
      fprintf(file, "+-- Datatype: ");
      osl_generic_idump(file, symbols->datatype, level);
    }
    else
      fprintf(file, "+-- Unknown datatype\n");


    // A blank line.
    for(j = 0; j <= level + 1; j++)
      fprintf(file, "|\t") ;
    fprintf(file, "\n") ;

    // Print the type of identifier.
    for (i = 0; i <= level; i++)
      fprintf(file, "|\t");
    if (symbols->scope != NULL) {
      fprintf(file, "+-- scope: ");
      osl_generic_idump(file, symbols->scope, level);
    }
    else
      fprintf(file, "+-- Unknown scope\n");


    // A blank line.
    for(j = 0; j <= level + 1; j++)
      fprintf(file, "|\t") ;
    fprintf(file, "\n") ;

    // Print the type of identifier.
    for (i = 0; i <= level; i++)
      fprintf(file, "|\t");
    if (symbols->type != OSL_UNDEFINED) {
      fprintf(file, "+-- Type: ");
      switch (symbols->type) {
        case OSL_SYMBOL_TYPE_ITERATOR : fprintf(file, "Iterator\n");  break;
        case OSL_SYMBOL_TYPE_PARAMETER: fprintf(file, "Parameter\n"); break;
        case OSL_SYMBOL_TYPE_ARRAY    : fprintf(file, "Array\n");     break;
        case OSL_SYMBOL_TYPE_FUNCTION : fprintf(file, "Function\n");  break;
        default : fprintf(file, "Unknown\n") ;
      }
    }
    else
      fprintf(file, "+-- Unknown type\n");

    // A blank line.
    for(j = 0; j <= level + 1; j++)
      fprintf(file, "|\t") ;
    fprintf(file, "\n") ;

    // Print the Number of dimensions in identifier.
    for (i = 0; i <= level; i++)
      fprintf(file, "|\t");
    if (symbols->nb_dims != OSL_UNDEFINED) {
      fprintf(file, "+-- Number of Dimensions: %d\n ", symbols->nb_dims);
    }
    else
      fprintf(file, "+-- Unknown number of dimensions\n");

    // A blank line.
    for(j = 0; j <= level + 1; j++)
      fprintf(file, "|\t") ;
    fprintf(file, "\n") ;

    // Print the origin identifier.
    for (i = 0; i <= level; i++)
      fprintf(file, "|\t");
    if (symbols->generated != OSL_UNDEFINED) {
      fprintf(file, "+-- Origin: %d\n ", symbols->generated);
    }
    else
      fprintf(file, "+-- Unknown origin\n");

    // A blank line.
    for(j = 0; j <= level + 1; j++)
      fprintf(file, "|\t") ;
    fprintf(file, "\n") ;

    // Print the extent of identifier.
    for (i = 0; i <= level; i++)
      fprintf(file, "|\t");
    if (symbols->extent != NULL) {
      fprintf(file, "+-- Extent: ");
      osl_relation_idump(file, symbols->extent, level);
    }
    else
      fprintf(file, "+-- Unknown extent\n");

    // A blank line.
    for(j = 0; j <= level + 1; j++)
      fprintf(file, "|\t") ;
    fprintf(file, "\n") ;

    symbols = symbols->next;
    number++;
  } 

  // The last line.
  for (j = 0; j <= level; j++)
    fprintf(file, "|\t");
  fprintf(file, "\n");
}


/**
 * osl_symbols_dump function:
 * this function prints the content of an osl_symbols_t structure
 * (*symbols) into a file (file, possibly stdout).
 * \param[in] file    The file where the information has to be printed.
 * \param[in] symbols The symbols structure to print.
 */
void osl_symbols_dump(FILE * file, osl_symbols_p symbols) {
  osl_symbols_idump(file, symbols, 0);
}


/**
 * osl_symbols_sprint function:
 * this function prints the content of an osl_symbols_t structure
 * (*symbols) into a string (returned) in the OpenScop textual format.
 * \param[in] symbols The symbols structure to print.
 * \return A string containing the OpenScop dump of the symbols structure.
 */
char * osl_symbols_sprint(osl_symbols_p symbols) {

  int nb_symbols = 0;
  int i = 1;
  int high_water_mark = OSL_MAX_STRING;
  int low_water_mark  = OSL_MIN_STRING;
  char * string = NULL;
  char buffer[OSL_MAX_STRING];

  if (symbols == NULL) {
    OSL_malloc(string, char *, low_water_mark * sizeof(char));
    string[0] = '\0';

    sprintf(buffer, "# Number of symbols\n");
    osl_util_safe_strcat(&string, buffer, &low_water_mark);

    sprintf(buffer, "%d\n", 0);
    osl_util_safe_strcat(&string, buffer, &low_water_mark);

    return string;
  }

  osl_symbols_p temp_symbols = symbols;
  while(temp_symbols != NULL) {
    nb_symbols++;
    temp_symbols = temp_symbols->next;
  }
  temp_symbols = symbols;

  OSL_malloc(string, char *, high_water_mark * sizeof(char));
  string[0] = '\0';

  sprintf(buffer, "# Number of symbols\n");
  osl_util_safe_strcat(&string, buffer, &high_water_mark);

  sprintf(buffer, "%d\n", nb_symbols);
  osl_util_safe_strcat(&string, buffer, &high_water_mark);

  while(temp_symbols != NULL) {

    int inner_detail_count = 1;

    sprintf(buffer, "# ===========================================\n");
    osl_util_safe_strcat(&string, buffer, &high_water_mark);

    sprintf(buffer, "# %d Data for symbol number %d \n", i, i);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);

    if (temp_symbols->type == OSL_UNDEFINED) {
      sprintf(buffer, "# %d.%d Symbol type\n 0 \n", i, inner_detail_count);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }
    else {
      sprintf(buffer, "# %d.%d Symbol type\n 1 \n", i, inner_detail_count);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
      switch (temp_symbols->type) {
        case OSL_SYMBOL_TYPE_ITERATOR : sprintf(buffer, "Iterator\n");  break;
        case OSL_SYMBOL_TYPE_PARAMETER: sprintf(buffer, "Parameter\n"); break;
        case OSL_SYMBOL_TYPE_ARRAY    : sprintf(buffer, "Array\n");     break;
        case OSL_SYMBOL_TYPE_FUNCTION : sprintf(buffer, "Function\n");  break;
        default : sprintf(buffer, "Unknown\n") ;
      }
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }
    inner_detail_count ++;


    // Printing Generated Boolean flag
    if (temp_symbols->generated == OSL_UNDEFINED)
      sprintf(buffer, "# %d.%d Generated Boolean \n 0 \n", i, inner_detail_count);
    else
      sprintf(buffer, "# %d.%d Generated Boolean \n 1 \n 1 \n", i, inner_detail_count);

    osl_util_safe_strcat(&string, buffer, &high_water_mark);
    inner_detail_count ++;


    // Printing Number of dimensions
    if (temp_symbols->nb_dims == OSL_UNDEFINED) {
      sprintf(buffer, "# %d.%d Number of dimensions \n 0 \n", i, inner_detail_count);
    }
    else {
      sprintf(buffer, "# %d.%d Number of dimensions \n 1 \n", i, inner_detail_count);
      sprintf(buffer, " %d\n", temp_symbols->nb_dims);
    }

    osl_util_safe_strcat(&string, buffer, &high_water_mark);
    inner_detail_count ++;

    // Printing Identifier
    if (temp_symbols->identifier != NULL) {
      sprintf(buffer, "# %d.%d Identifier \n 0 - Not provided\n", i, inner_detail_count);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }
    else {
      sprintf(buffer, "# %d.%d Identifier \n 1 - provided\n", i, inner_detail_count);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
      osl_util_safe_strcat(&string, osl_generic_sprint(temp_symbols->identifier), &high_water_mark);
    }


    inner_detail_count ++;

    // Printing Data type
    if (temp_symbols->datatype != NULL) {
      sprintf(buffer, "# %d.%d Datatype \n 0 - Not provided\n", i, inner_detail_count);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }
    else {
      sprintf(buffer, "# %d.%d Datatype \n 1 - provided \n", i, inner_detail_count);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
      osl_util_safe_strcat(&string, osl_generic_sprint(temp_symbols->datatype), &high_water_mark);
    }

    inner_detail_count ++;

    // Printing Scope
    if (temp_symbols->scope != NULL) {
      sprintf(buffer, "# %d.%d Scope \n 0 - Not provided \n", i, inner_detail_count);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }
    else {
      sprintf(buffer, "# %d.%d Scope \n 1 - provided\n", i, inner_detail_count);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
      osl_util_safe_strcat(&string, osl_generic_sprint(temp_symbols->scope), &high_water_mark);
    }

    inner_detail_count ++;

    // Printing Scope
    if (temp_symbols->extent != NULL) {
      sprintf(buffer, "# %d.%d Extent \n 0 - Not provided \n", i, inner_detail_count);
    }
    else {
      sprintf(buffer, "# %d.%d Extent \n 1 - provided \n", i, inner_detail_count);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
      char* extent = osl_relation_spprint(temp_symbols->extent, NULL);
      sprintf(buffer, "%s\n", extent);
    }

    osl_util_safe_strcat(&string, buffer, &high_water_mark);
    inner_detail_count ++;

    temp_symbols = temp_symbols->next;
  }

  OSL_realloc(string, char *, (strlen(string) + 1) * sizeof(char));

  return string;
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/**
 * osl_symbols_sread function:
 * this function reads a symbols structure from a string complying to the
 * OpenScop textual format and returns a pointer to this symbols structure.
 * The input parameter is updated to the position in the input string this
 * function reach right after reading the symbols structure.
 * \param[in,out] input The input string where to find a symbols.
 *                      Updated to the position after what has been read.
 * \return A pointer to the symbols structure that has been read.
 */
osl_symbols_p osl_symbols_sread(char ** input) {
  osl_symbols_p symbols;
  osl_symbols_p head;
  int nb_symbols;

  if (*input == NULL) {
    OSL_debug("no symbols optional tag");
    return NULL;
  }

  if (strlen(*input) > OSL_MAX_STRING) 
    OSL_error("symbols too long");

  // Find the number of names provided.
  nb_symbols = osl_util_read_int(NULL, input);

  if (nb_symbols == 0)
    return NULL;

  head = symbols = osl_symbols_malloc();

  while( nb_symbols != 0 ) {

    // Reading the type of symbol
    if(osl_util_read_int(NULL, input) != 0 ) {
      char* type = osl_util_read_string(NULL, input);
      if( strcmp(type, "Iterator") == 0 )
        symbols->type = OSL_SYMBOL_TYPE_ITERATOR;
      else if (strcmp(type, "Parameter") == 0)
        symbols->type = OSL_SYMBOL_TYPE_PARAMETER;
      else if (strcmp(type, "Array") == 0)
        symbols->type = OSL_SYMBOL_TYPE_ARRAY;
      else if (strcmp(type, "Function") == 0)
        symbols->type = OSL_SYMBOL_TYPE_FUNCTION;
      else
        symbols->type = OSL_UNDEFINED;
    }
    else
      symbols->type = OSL_UNDEFINED;

    // Reading origin of symbol
    if(osl_util_read_int(NULL, input) != 0) 
      symbols->generated = osl_util_read_int(NULL, input);
    else
      symbols->generated = OSL_UNDEFINED;

    // Reading Number of dimensions of a symbol
    if(osl_util_read_int(NULL, input) != 0)
      symbols->nb_dims = osl_util_read_int(NULL, input);
    else
      symbols->nb_dims = OSL_UNDEFINED;

    // Reading identifier
    if(osl_util_read_int(NULL, input) != 0) {
      osl_interface_p registry = osl_strings_interface();
      char* generic_string = osl_util_tag_content(*input, strdup("string"));
      symbols->identifier = osl_generic_sread_one(&generic_string, registry);
      free(generic_string);
    }
    else
      symbols->identifier = NULL;

    // Reading data type
    if(osl_util_read_int(NULL, input) != 0) {
      osl_interface_p registry = osl_strings_interface();
      char* generic_string = osl_util_tag_content(*input, strdup("string"));
      symbols->datatype = osl_generic_sread_one(&generic_string, registry);
      free(generic_string);
    }
    else
      symbols->datatype = NULL;

    // Reading scope
    if(osl_util_read_int(NULL, input) != 0) {
      osl_interface_p registry = osl_strings_interface();
      char* generic_string = osl_util_tag_content(*input, strdup("string"));
      symbols->scope = osl_generic_sread_one(&generic_string, registry);
      free(generic_string);
    }
    else
      symbols->scope = NULL;

    // Reading extent
    if(osl_util_read_int(NULL, input) != 0) {
      char* generic_string = osl_util_tag_content(*input, strdup("string"));
      symbols->extent = osl_relation_sread(input);
      free(generic_string);
    }
    else
      symbols->extent = NULL;

    nb_symbols --;
    if (nb_symbols != 0) {
      symbols->next = osl_symbols_malloc ();
      symbols = symbols->next;
    }
  } 

  return head;
} 


/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/


/**
 * osl_symbols_malloc function:
 * this function allocates the memory space for an osl_symbols_t
 * structure and sets its fields with default values. Then it returns a
 * pointer to the allocated space.
 * \return A pointer to an empty symbols structure with fields set to
 *         default values.
 */
osl_symbols_p osl_symbols_malloc() {
  osl_symbols_p symbols;

  OSL_malloc(symbols, osl_symbols_p, sizeof(osl_symbols_t));
  symbols->type       = OSL_UNDEFINED;
  symbols->generated  = OSL_UNDEFINED;
  symbols->nb_dims    = OSL_UNDEFINED;

  symbols->identifier = NULL;
  symbols->datatype   = NULL;
  symbols->scope      = NULL;
  symbols->extent     = NULL;

  symbols->usr        = NULL;
  symbols->tag        = OSL_UNDEFINED;

  return symbols;
}


/**
 * osl_symbols_free function:
 * this function frees the allocated memory for an osl_symbols_t
 * structure.
 * \param[in,out] symbols The pointer to the symbols structure to free.
 */
void osl_symbols_free(osl_symbols_p symbols) {
  if (symbols != NULL) {
    if (symbols->identifier != NULL)
      osl_generic_free(symbols->identifier);
    if (symbols->datatype != NULL)
      osl_generic_free(symbols->datatype);
    if (symbols->scope != NULL)
      osl_generic_free(symbols->scope);
    if(symbols->extent != NULL)
      osl_relation_free(symbols->extent);
    if (symbols->usr != NULL)
      free(symbols->usr);
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * osl_symbols_clone function:
 * this function builds and returns a "hard copy" (not a pointer copy) of an
 * osl_symbols_t data structure.
 * \param[in] symbols The pointer to the symbols structure to clone.
 * \return A pointer to the clone of the symbols structure.
 */
osl_symbols_p osl_symbols_clone(osl_symbols_p symbols) {
  osl_symbols_p clone;

  if (symbols == NULL)
    return NULL;

  clone = osl_symbols_malloc();
  clone->type      = symbols->type;
  clone->generated = symbols->generated;
  clone->nb_dims    = symbols->nb_dims;

  clone->identifier = osl_generic_clone(symbols->identifier);
  clone->datatype   = osl_generic_clone(symbols->datatype);
  clone->scope      = osl_generic_clone(symbols->scope);
  clone->extent     = osl_relation_clone(symbols->extent);

  clone->usr        = symbols->usr;
  clone->tag        = symbols->tag;

  return clone;
}


/**
 * osl_symbols_equal function:
 * this function returns true if the two symbols structures are the same
 * (content-wise), false otherwise.
 * \param[in] c1  The first symbols structure.
 * \param[in] c2  The second symbols structure.
 * \return 1 if c1 and c2 are the same (content-wise), 0 otherwise.
 */
int osl_symbols_equal(osl_symbols_p c1, osl_symbols_p c2) {

  if (c1 == c2)
    return 1;

  if (((c1 == NULL) && (c2 != NULL)) || ((c1 != NULL) && (c2 == NULL)))
    return 0;

  if (c1->type == c2->type && c1->generated == c2->generated && 
      c1->nb_dims == c2->nb_dims && c1->tag == c2->tag) {
    if (osl_generic_equal(c1->identifier, c2->identifier)) {
      if (osl_generic_equal(c1->datatype, c2->datatype)) {
        if (osl_generic_equal(c1->scope, c2->scope)) {
          if (osl_relation_equal(c1->extent, c2->extent)) {
            return 1;
          }
        }
      }
    }
  }

  return 0;
}


/**
 * osl_symbols_interface function:
 * this function creates an interface structure corresponding to the symbols
 * extension and returns it).
 * \return An interface structure for the symbols extension.
 */
osl_interface_p osl_symbols_interface() {
  osl_interface_p interface = osl_interface_malloc();

  interface->URI    = strdup(OSL_URI_SYMBOLS);
  interface->idump  = (osl_idump_f)osl_symbols_idump;
  interface->sprint = (osl_sprint_f)osl_symbols_sprint;
  interface->sread  = (osl_sread_f)osl_symbols_sread;
  interface->malloc = (osl_malloc_f)osl_symbols_malloc;
  interface->free   = (osl_free_f)osl_symbols_free;
  interface->clone  = (osl_clone_f)osl_symbols_clone;
  interface->equal  = (osl_equal_f)osl_symbols_equal;
  return interface;
}
