
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                            scop.c                               **
     **-----------------------------------------------------------------**
     **                   First version: 30/04/2008                     **
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
# include <osl/scop.h>


/*+***************************************************************************
 *                         Structure display functions                       *
 *****************************************************************************/


/**
 * osl_scop_idump function:
 * this function displays an osl_scop_t structure (*scop) into a
 * file (file, possibly stdout) in a way that trends to be understandable. It
 * includes an indentation level (level) in order to work with others
 * print_structure functions.
 * \param file  The file where the information has to be printed.
 * \param scop  The scop structure whose information has to be printed.
 * \param level Number of spaces before printing, for each line.
 */
void osl_scop_idump(FILE * file, osl_scop_p scop, int level) {
  int j, first = 1;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (scop != NULL)
    fprintf(file, "+-- osl_scop_t\n");
  else
    fprintf(file, "+-- NULL scop\n");

  while (scop != NULL) {
    if (!first) {
      // Go to the right level.
      for (j = 0; j < level; j++)
        fprintf(file, "|\t");
      fprintf(file, "|   osl_scop_t\n");
    }
    else
      first = 0;

    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    // Print the version.
    for (j = 0; j < level; j++)
      fprintf(file, "|\t");
    fprintf(file, "|\tVersion: %d\n", scop->version);

    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    // Print the language.
    for (j = 0; j < level; j++)
      fprintf(file, "|\t");
    fprintf(file, "|\tLanguage: %s\n", scop->language);

    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");

    // Print the context of the scop.
    osl_relation_idump(file, scop->context, level+1);

    // Print the parameters.
    osl_generic_idump(file, scop->parameters, level+1);

    // Print the statements.
    osl_statement_idump(file, scop->statement, level+1);

    // Print the registered extension interfaces.
    osl_interface_idump(file, scop->registry, level+1);

    // Print the extensions.
    osl_generic_idump(file, scop->extension, level+1);

    scop = scop->next;

    // Next line.
    if (scop != NULL) {
      for (j = 0; j <= level; j++)
        fprintf(file, "|\t");
      fprintf(file, "V\n");
    }
  }

  // The last line.
  for (j = 0; j <= level; j++)
    fprintf(file, "|\t");
  fprintf(file, "\n");
}


/**
 * osl_scop_dump function:
 * this function prints the content of an osl_scop_t structure (*scop)
 * into a file (file, possibly stdout).
 * \param file The file where the information has to be printed.
 * \param scop The scop structure whose information has to be printed.
 */
void osl_scop_dump(FILE * file, osl_scop_p scop) {
  osl_scop_idump(file, scop, 0);
}


#if 0
/**
 * osl_scop_name_limits function:
 * this function finds the (maximum) number of various elements of a scop and
 * return the values through parameters. To ensure the correctness of the
 * results, an integrity check of the input scop should be run before calling
 * this function.
 * \param scop          The scop to analyse.
 * \parem nb_parameters The number of parameters in the scop (output).
 * \parem nb_iterators  The number of iterators in the scop (output).
 * \parem nb_scattdims  The number of scattdims in the scop (output).
 * \parem nb_localdims  The number of local dimensions in the scop (output).
 * \parem nb_arrays     The number of arrays in the scop (output).
 */
static
void osl_scop_name_limits(osl_scop_p scop,
                              int * nb_parameters,
                              int * nb_iterators,
                              int * nb_scattdims,
                              int * nb_localdims,
                              int * nb_arrays) {
  int array_id;
  osl_statement_p statement;
  osl_relation_list_p list;
  
  // * The number of parameters is collected from the context,
  // * The numbers of local dimensions are collected from all relations
  //   in the corresponding field.
  *nb_parameters = 0;
  *nb_localdims = 0;
  if (scop->context != NULL) { 
    *nb_parameters = scop->context->nb_parameters;
    *nb_localdims  = scop->context->nb_local_dims;
  }

  *nb_iterators = 0;
  *nb_scattdims = 0;
  *nb_arrays    = 0;
  statement = scop->statement;
  while (statement != NULL) {
    // * The number of iterators are defined by iteration domains,
    //   it corresponds to the #output_dims.
    if (statement->domain != NULL) {
      if (statement->domain->nb_output_dims > *nb_iterators)
        *nb_iterators = statement->domain->nb_output_dims;

      if (statement->domain->nb_local_dims > *nb_localdims)
        *nb_localdims = statement->domain->nb_local_dims;
    }

    // * The number of scattdims are defined by scattering,
    //   it corresponds to the #output_dims.
    if (statement->scattering != NULL) {
      if (statement->scattering->nb_output_dims > *nb_scattdims)
        *nb_scattdims = statement->scattering->nb_output_dims;
	
      if (statement->scattering->nb_local_dims > *nb_localdims)
        *nb_localdims = statement->scattering->nb_local_dims;
    }

    // * The number of arrays are defined by accesses,
    list = statement->access;
    while (list != NULL) {
      array_id = osl_relation_get_array_id(list->elt);
      if (array_id > *nb_arrays)
        *nb_arrays = array_id;

      list = list->next;
    }

    statement = statement->next;
  }
}


/**
 * osl_scop_full_names function:
 * this function generates an osl_names_p structure which contains
 * enough names for the scop provided as parameter, for each kind of names.
 * If the names contained in the input scop are not sufficient, this function
 * generated the missing names.
 * \param scop The scop we need a name for each element.
 * \return A set of names for the scop.
 */
static
osl_names_p osl_scop_full_names(osl_scop_p scop) {
  int nb_parameters;
  int nb_iterators;
  int nb_scattdims;
  int nb_localdims;
  int nb_arrays;
  osl_arrays_p arrays;
  osl_names_p names;

  names = osl_names_clone(scop->names);

  // Extract array names information from extensions.
  osl_strings_free(names->arrays, names->nb_arrays);
  arrays = (osl_arrays_p)osl_extension_lookup(scop->extension,
                                  OSL_EXTENSION_ARRAYS);
  names->arrays = osl_arrays_generate_names(arrays,
                                  &(names->nb_arrays));
  
  // Complete names if necessary.
  osl_scop_name_limits(scop, &nb_parameters,
                                  &nb_iterators,
                                  &nb_scattdims,
				  &nb_localdims,
			          &nb_arrays);

  osl_strings_complete(&names->parameters, &names->nb_parameters,
                                 "P_", nb_parameters);
  
  osl_strings_complete(&names->iterators,  &names->nb_iterators,
                                 "i_", nb_iterators);
  
  osl_strings_complete(&names->scattdims,  &names->nb_scattdims,
                                 "s_", nb_scattdims);
  
  osl_strings_complete(&names->localdims,  &names->nb_localdims,
                                 "l_", nb_localdims);
  
  osl_strings_complete(&names->arrays,     &names->nb_arrays,
                                 "A_", nb_arrays);

  return names;
}
#endif


/**
 * osl_scop_print function:
 * this function prints the content of an osl_scop_t structure (*scop)
 * into a file (file, possibly stdout) in the OpenScop textual format.
 * \param file The file where the information has to be printed.
 * \param scop The scop structure whose information has to be printed.
 */
void osl_scop_print(FILE * file, osl_scop_p scop) {

  if (scop == NULL) {
    fprintf(file, "# NULL scop\n");
    return;
  }
  else {
    fprintf(file, "# [File generated by the OpenScop Library %s %s bits]\n",
            OSL_RELEASE,OSL_VERSION);
  }

  if (osl_scop_integrity_check(scop) == 0)
    OSL_warning("OpenScop integrity check failed. "
                     "Something may go wrong.");
  
  while (scop != NULL) {
    fprintf(file, "\n"OSL_TAG_START_SCOP"\n\n");
    fprintf(file, "# =============================================== "
                  "Global\n");
    fprintf(file, "# Language\n");
    fprintf(file, "%s\n\n", scop->language);

    fprintf(file, "# Context\n");
    osl_relation_print(file, scop->context);
    fprintf(file, "\n");

    osl_util_print_provided(file,
        osl_generic_hasURI(scop->parameters, OSL_URI_STRINGS),
        "Parameters are");
    osl_generic_print(file, scop->parameters);

    fprintf(file, "\n# Number of statements\n");
    fprintf(file, "%d\n\n",osl_statement_number(scop->statement));

    osl_statement_print(file, scop->statement);

    if (scop->extension) {
      fprintf(file, "# =============================================== "
                    "Extensions\n");
      osl_generic_print(file, scop->extension);
    }
    fprintf(file, "\n"OSL_TAG_END_SCOP"\n\n");
    
    scop = scop->next;
  }
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/**
 * osl_scop_read function:
 * this function reads a list of scop structures from a file (possibly stdin)
 * complying to the OpenScop textual format and returns a pointer to this
 * scop list. If some relation properties (number of input/output/local
 * dimensions and number of parameters) are undefined, it will define them
 * according to the available information. 
 * \param file The file where the scop has to be read.
 * \return A pointer to the scop structure that has been read.
 */
osl_scop_p osl_scop_read(FILE * file) {
  osl_scop_p list = NULL, current = NULL, scop;
  osl_statement_p stmt = NULL;
  osl_statement_p prev = NULL;
  osl_interface_p interface;
  osl_strings_p language;
  int nb_statements;
  char buffer[OSL_MAX_STRING];
  char * tmp, * start;
  int first = 1;
  int i;

  if (file == NULL)
    return NULL;

  while(1) {
    //
    // I. START TAG
    //
    tmp = osl_util_read_uptotag(file, OSL_TAG_START_SCOP);
    free(tmp);
    if (feof(file)) {
      OSL_info("no more scop in the file");
      break;
    }

    scop = osl_scop_malloc();
    osl_scop_register_default_extensions(scop);

    //
    // II. CONTEXT PART
    //

    // Read the language.
    language = osl_strings_read(file);
    if (osl_strings_size(language) == 0)
      OSL_error("no language (backend) specified");

    if (osl_strings_size(language) > 1)
      OSL_warning("uninterpreted information (after language)");

    if (language != NULL) {
      scop->language = strdup(language->string[0]);
      osl_strings_free(language);
    }

    // Read the context domain.
    scop->context = osl_relation_read(file);

    // Read the parameters.
    scop->parameter_type = OSL_TYPE_STRING;
    if (osl_util_read_int(file, NULL) > 0) {
      interface = osl_strings_interface();
      start = osl_util_skip_blank_and_comments(file, buffer);
      scop->parameters = osl_generic_sread(start, interface);
      osl_interface_free(interface);
    }

    //
    // III. STATEMENT PART
    //

    // Read the number of statements.
    nb_statements = osl_util_read_int(file, NULL);

    for (i = 0; i < nb_statements; i++) {
      // Read each statement.
      stmt = osl_statement_read(file);
      if (scop->statement == NULL)
        scop->statement = stmt;
      else
        prev->next = stmt;
      prev = stmt;
    }

    //
    // IV. EXTENSION PART (TO THE END TAG)
    //

    // Read up the end tag (if any), and store extensions.
    scop->extension = osl_generic_read(file, scop->registry);

    // Add the new scop to the list.
    if (first) {
      list = scop;
      first = 0;
    }
    else {
      current->next = scop;
    }
    current = scop;    
  }
  
  if (!osl_scop_integrity_check(list))
    OSL_warning("scop integrity check failed");

  return list;
}


/*+***************************************************************************
 *                   Memory allocation/deallocation functions                *
 *****************************************************************************/


/**
 * osl_scop_malloc function:
 * this function allocates the memory space for a osl_scop_t structure and
 * sets its fields with default values. Then it returns a pointer to the
 * allocated space.
 * \return A pointer to an empty scop with fields set to default values.
 */
osl_scop_p osl_scop_malloc() {
  osl_scop_p scop;

  OSL_malloc(scop, osl_scop_p, sizeof(osl_scop_t));
  scop->version        = 1;
  scop->language       = NULL;
  scop->context        = NULL;
  scop->parameter_type = OSL_UNDEFINED;
  scop->parameters     = NULL;
  scop->statement      = NULL;
  scop->registry       = NULL;
  scop->extension      = NULL;
  scop->usr            = NULL;
  scop->next           = NULL;

  return scop;
}


/**
 * osl_scop_free function:
 * This function frees the allocated memory for a osl_scop_t structure.
 * \param scop The pointer to the scop we want to free.
 */
void osl_scop_free(osl_scop_p scop) {
  osl_scop_p tmp;
  
  while (scop != NULL) {
    if (scop->language != NULL)
      free(scop->language);
    osl_generic_free(scop->parameters);
    osl_relation_free(scop->context);
    osl_statement_free(scop->statement);
    osl_interface_free(scop->registry);
    osl_generic_free(scop->extension);

    tmp = scop->next;
    free(scop);
    scop = tmp;
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * osl_scop_register_default_extensions function:
 * this function registers the default OpenScop Library extensions to an
 * existing scop.
 * \param scop The scop for which default options have to be registered.
 */
void osl_scop_register_default_extensions(osl_scop_p scop) {
  
  osl_interface_add(&(scop->registry), osl_textual_interface());
  osl_interface_add(&(scop->registry), osl_comment_interface());
  osl_interface_add(&(scop->registry), osl_arrays_interface());
  osl_interface_add(&(scop->registry), osl_lines_interface());
  osl_interface_add(&(scop->registry), osl_irregular_interface());
}


/**
 * osl_scop_clone function:
 * This functions builds and returns a "hard copy" (not a pointer copy)
 * of a osl_statement_t data structure provided as parameter.
 * Note that the usr field is not touched by this function.
 * \param statement The pointer to the scop we want to clone.
 * \return A pointer to the full clone of the scop provided as parameter.
 */
osl_scop_p osl_scop_clone(osl_scop_p scop) {
  osl_scop_p clone = NULL, node, previous = NULL;
  int first = 1;
  
  while (scop != NULL) {
    node                 = osl_scop_malloc();
    node->version        = scop->version;
    if (scop->language != NULL)
      node->language     = strdup(scop->language);
    node->context        = osl_relation_clone(scop->context);
    node->parameter_type = scop->parameter_type;
    node->parameters     = osl_generic_clone(scop->parameters);
    node->statement      = osl_statement_clone(scop->statement);
    node->registry       = osl_interface_clone(scop->registry);
    node->extension      = osl_generic_clone(scop->extension);
    
    if (first) {
      first = 0;
      clone = node;
      previous = node;
    }
    else {
      previous->next = node;
      previous = previous->next;
    }

    scop = scop->next;
  }

  return clone;
}


/**
 * osl_scop_equal function:
 * this function returns true if the two scops are the same, false
 * otherwise (the usr field is not tested).
 * \param s1 The first scop.
 * \param s2 The second scop.
 * \return 1 if s1 and s2 are the same (content-wise), 0 otherwise.
 */
int osl_scop_equal(osl_scop_p s1, osl_scop_p s2) {

  while ((s1 != NULL) && (s2 != NULL)) {
    if (s1 == s2)
      return 1;

    if (s1->version != s2->version) {
      OSL_info("versions are not the same"); 
      return 0;
    }

    if (strcmp(s1->language, s2->language) != 0) {
      OSL_info("languages are not the same"); 
      return 0;
    }

    if (!osl_relation_equal(s1->context, s2->context)) {
      OSL_info("contexts are not the same"); 
      return 0;
    }

    if (s1->parameter_type != s2->parameter_type) {
      OSL_info("parameter types are not the same"); 
      return 0;
    }

    if (!osl_generic_equal(s1->parameters, s2->parameters)) {
      OSL_info("parameters are not the same"); 
      return 0;
    }

    if (!osl_statement_equal(s1->statement, s2->statement)) {
      OSL_info("statements are not the same"); 
      return 0;
    }

    if (!osl_interface_equal(s1->registry, s2->registry)) {
      OSL_info("registries are not the same"); 
      return 0;
    }

    if (!osl_generic_equal(s1->extension, s2->extension)) {
      OSL_info("extensions are not the same"); 
      return 0;
    }

    s1 = s1->next;
    s2 = s2->next;
  }
  
  if (((s1 == NULL) && (s2 != NULL)) || ((s1 != NULL) && (s2 == NULL)))
    return 0;

  return 1;
}


/**
 * osl_scop_integrity_check function:
 * This function checks that a scop is "well formed". It returns 0 if the
 * check failed or 1 if no problem has been detected.
 * \param scop  The scop we want to check.
 * \return 0 if the integrity check fails, 1 otherwise.
 */
int osl_scop_integrity_check(osl_scop_p scop) {
  int expected_nb_parameters;


  while (scop != NULL) {
    // Check the language.
    if ((scop->language != NULL) &&
        (!strcmp(scop->language, "caml")  || !strcmp(scop->language, "Caml") ||
         !strcmp(scop->language, "ocaml") || !strcmp(scop->language, "OCaml")))
      fprintf(stderr, "[OpenScop] Alert: What ?! Caml ?! Are you sure ?!?!\n");

    // Check the context.
    if (!osl_relation_integrity_check(scop->context,
                                      OSL_TYPE_CONTEXT,
                                      OSL_UNDEFINED,
                                      OSL_UNDEFINED,
                                      OSL_UNDEFINED))
      return 0;

    // Get the number of parameters.
    if (scop->context != NULL) 
      expected_nb_parameters = scop->context->nb_parameters;
    else
      expected_nb_parameters = OSL_UNDEFINED;
    
    // TODO : check the number of parameter strings.

    if (!osl_statement_integrity_check(scop->statement,
                                       expected_nb_parameters))
      return 0;

    scop = scop->next;
  }

  return 1;
}


/**
 * osl_scop_get_nb_parameters function:
 * this function returns the number of global parameters of a given SCoP.
 * \param scop The scop we want to know the number of global parameters.
 * \return The number of global parameters in the scop.
 */
int osl_scop_get_nb_parameters(osl_scop_p scop) {

  if (scop->context == NULL) {
    OSL_warning("no context domain, assuming 0 parameters");
    return 0;
  }
  else {
    return scop->context->nb_parameters;
  }
}


/**
 * osl_scop_register_extension function:
 * this function registers a list of extension interfaces to a scop, i.e., it
 * adds them to the scop registry. In addition, it will extract extensions
 * corresponding to those interfaces from the textual form of the extensions
 * (if any) and add them to the scop extension list.
 * \param scop      The scop for which an extension has to be registered.
 * \param interface The extension interface to register within the scop.
 */
void osl_scop_register_extension(osl_scop_p scop, osl_interface_p interface) {
  osl_generic_p textual, new;
  char * extension_string;

  if ((interface != NULL) && (scop != NULL)) {
    osl_interface_add(&scop->registry, interface);

    textual = osl_generic_lookup(scop->extension, interface->URI);
    if (textual != NULL) {
      extension_string = ((osl_textual_p)textual->data)->textual;
      new = osl_generic_sread(extension_string, interface);
      osl_generic_add(&scop->extension, new);
    }
  }
}


