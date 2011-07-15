
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
# include <openscop/scop.h>


/*+***************************************************************************
 *                         Structure display functions                       *
 *****************************************************************************/


/**
 * openscop_scop_idump function:
 * this function displays an openscop_scop_t structure (*scop) into a
 * file (file, possibly stdout) in a way that trends to be understandable. It
 * includes an indentation level (level) in order to work with others
 * print_structure functions.
 * \param file  The file where the information has to be printed.
 * \param scop  The scop structure whose information has to be printed.
 * \param level Number of spaces before printing, for each line.
 */
void openscop_scop_idump(FILE * file, openscop_scop_p scop, int level) {
  int j;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (scop != NULL) {
    fprintf(file, "+-- openscop_scop_t\n");

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
    openscop_relation_idump(file, scop->context, level+1);

    // Print the parameters.
    openscop_strings_idump(file,
        (scop->parameter_type == OPENSCOP_TYPE_STRING) ? 
            (char **)scop->parameters : NULL,
        level, "parameters");

    // Print the statements.
    openscop_statement_idump(file, scop->statement, level+1);

    // Print the registered extension ids.
    openscop_extension_id_idump(file, scop->registry, level+1);

    // Print the extensions.
    openscop_extension_idump(file, scop->extension, level+1);

    // A blank line.
    for (j = 0; j <= level+1; j++)
      fprintf(file, "|\t");
    fprintf(file, "\n");
  }
  else {
    fprintf(file, "+-- NULL scop\n");
  }

  // The last line.
  for (j = 0; j <= level; j++)
    fprintf(file, "|\t");
  fprintf(file, "\n");
}


/**
 * openscop_scop_dump function:
 * this function prints the content of an openscop_scop_t structure (*scop)
 * into a file (file, possibly stdout).
 * \param file The file where the information has to be printed.
 * \param scop The scop structure whose information has to be printed.
 */
void openscop_scop_dump(FILE * file, openscop_scop_p scop) {
  openscop_scop_idump(file, scop, 0);
}


#if 0
/**
 * openscop_scop_name_limits function:
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
void openscop_scop_name_limits(openscop_scop_p scop,
                              int * nb_parameters,
                              int * nb_iterators,
                              int * nb_scattdims,
                              int * nb_localdims,
                              int * nb_arrays) {
  int array_id;
  openscop_statement_p statement;
  openscop_relation_list_p list;
  
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
      array_id = openscop_relation_get_array_id(list->elt);
      if (array_id > *nb_arrays)
        *nb_arrays = array_id;

      list = list->next;
    }

    statement = statement->next;
  }
}


/**
 * openscop_scop_full_names function:
 * this function generates an openscop_names_p structure which contains
 * enough names for the scop provided as parameter, for each kind of names.
 * If the names contained in the input scop are not sufficient, this function
 * generated the missing names.
 * \param scop The scop we need a name for each element.
 * \return A set of names for the scop.
 */
static
openscop_names_p openscop_scop_full_names(openscop_scop_p scop) {
  int nb_parameters;
  int nb_iterators;
  int nb_scattdims;
  int nb_localdims;
  int nb_arrays;
  openscop_arrays_p arrays;
  openscop_names_p names;

  names = openscop_names_clone(scop->names);

  // Extract array names information from extensions.
  openscop_strings_free(names->arrays, names->nb_arrays);
  arrays = (openscop_arrays_p)openscop_extension_lookup(scop->extension,
                                  OPENSCOP_EXTENSION_ARRAYS);
  names->arrays = openscop_arrays_generate_names(arrays,
                                  &(names->nb_arrays));
  
  // Complete names if necessary.
  openscop_scop_name_limits(scop, &nb_parameters,
                                  &nb_iterators,
                                  &nb_scattdims,
				  &nb_localdims,
			          &nb_arrays);

  openscop_strings_complete(&names->parameters, &names->nb_parameters,
                                 "P_", nb_parameters);
  
  openscop_strings_complete(&names->iterators,  &names->nb_iterators,
                                 "i_", nb_iterators);
  
  openscop_strings_complete(&names->scattdims,  &names->nb_scattdims,
                                 "s_", nb_scattdims);
  
  openscop_strings_complete(&names->localdims,  &names->nb_localdims,
                                 "l_", nb_localdims);
  
  openscop_strings_complete(&names->arrays,     &names->nb_arrays,
                                 "A_", nb_arrays);

  return names;
}
#endif

/**
 * openscop_scop_print function:
 * this function prints the content of an openscop_scop_t structure (*scop)
 * into a file (file, possibly stdout) in the OpenScop textual format.
 * \param file The file where the information has to be printed.
 * \param scop The scop structure whose information has to be printed.
 */
void openscop_scop_print(FILE * file, openscop_scop_p scop) {

  if (scop == NULL) {
    fprintf(file, "# NULL scop\n");
    return;
  }

  if (openscop_scop_integrity_check(scop) == 0)
    OPENSCOP_warning("OpenScop integrity check failed. "
                     "Something may go wrong");

  if (0) {
    fprintf(file, "#                                                     \n");
    fprintf(file, "#          <|                                         \n");
    fprintf(file, "#           A                                         \n");
    fprintf(file, "#          /.\\                                       \n");
    fprintf(file, "#     <|  [\"\"M#                                     \n");
    fprintf(file, "#      A   | #            Clan McCloog Castle         \n");
    fprintf(file, "#     /.\\ [\"\"M#           [Generated by the OpenScop ");
    fprintf(file, "Library %s %s bits]\n",OPENSCOP_RELEASE, OPENSCOP_VERSION);
    fprintf(file, "#    [\"\"M# | #  U\"U#U                              \n");
    fprintf(file, "#     | #  | #  \\ .:/                                \n");
    fprintf(file, "#     | #  | #___| #                                  \n");
    fprintf(file, "#     | \"--'     .-\"                                \n");
    fprintf(file, "#   |\"-\"-\"-\"-\"-#-#-##                            \n");
    fprintf(file, "#   |     # ## ######                                 \n");
    fprintf(file, "#    \\       .::::'/                                 \n");
    fprintf(file, "#     \\      ::::'/                                  \n");
    fprintf(file, "#   :8a|    # # ##                                    \n");
    fprintf(file, "#   ::88a      ###                                    \n");
    fprintf(file, "#  ::::888a  8a ##::.                                 \n");
    fprintf(file, "#  ::::::888a88a[]::::                                \n");
    fprintf(file, "# :::::::::SUNDOGa8a::::. ..                          \n");
    fprintf(file, "# :::::8::::888:Y8888:::::::::...                     \n");
    fprintf(file, "#::':::88::::888::Y88a______________________________");
    fprintf(file, "________________________\n");
    fprintf(file, "#:: ::::88a::::88a:Y88a                             ");
    fprintf(file, "     __---__-- __\n");
    fprintf(file, "#' .: ::Y88a:::::8a:Y88a                            ");
    fprintf(file, "__----_-- -------_-__\n");
    fprintf(file, "#  :' ::::8P::::::::::88aa.                   _ _- -");
    fprintf(file, "-  --_ --- __  --- __--\n");
    fprintf(file, "#.::  :::::::::::::::::::Y88as88a...s88aa.\n");
  }
  else {
    fprintf(file, "# [File generated by the OpenScop Library %s %s bits]\n",
            OPENSCOP_RELEASE,OPENSCOP_VERSION);
  }

  fprintf(file, "\n"OPENSCOP_TAG_START_SCOP"\n\n");
  fprintf(file, "# =============================================== Global\n");
  fprintf(file, "# Language\n");
  fprintf(file, "%s\n\n", scop->language);

  fprintf(file, "# Context\n");
  openscop_relation_print(file, scop->context, NULL);
  fprintf(file, "\n");

  openscop_strings_print(file, (char **)scop->parameters, 1,
      (scop->parameter_type == OPENSCOP_TYPE_STRING), "Parameters");

  fprintf(file, "# Number of statements\n");
  fprintf(file, "%d\n\n",openscop_statement_number(scop->statement));

  openscop_statement_print(file, scop->statement, NULL);

  if (scop->extension) {
    fprintf(file, "# ==============================================="
                  " Extensions\n");
    openscop_extension_print(file, scop->extension);
  }
  fprintf(file, "\n"OPENSCOP_TAG_END_SCOP"\n\n");
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/**
 * openscop_scop_read function:
 * this function reads a scop structure from a file (possibly stdin)
 * complying to the OpenScop textual format and returns a pointer to this
 * scop structure. If some relation properties (number of input/output/local
 * dimensions and number of parameters) are undefined, it will define them
 * according to the available information. 
 * \param file The file where the scop has to be read.
 * \return A pointer to the scop structure that has been read.
 */
openscop_scop_p openscop_scop_read(FILE * file) {
  openscop_scop_p scop      = NULL;
  openscop_statement_p stmt = NULL;
  openscop_statement_p prev = NULL;
  int nb_statements, nb_parameters;
  char * tmp, ** language;
  int i;

  if (file == NULL)
    return NULL;

  //
  // I. START TAG
  //
  tmp = openscop_util_read_uptotag(file, OPENSCOP_TAG_START_SCOP);
  free(tmp);
  if (feof(file)) {
    OPENSCOP_info("no more scop in the file");
    return NULL;
  }

  scop = openscop_scop_malloc();
  
  //
  // II. CONTEXT PART
  //

  // Read the language.
  language = openscop_strings_read(file);
  if (openscop_strings_size(language) == 0)
    OPENSCOP_error("no language (backend) specified");
  
  if (openscop_strings_size(language) > 1)
    OPENSCOP_warning("uninterpreted information (after language)");

  scop->language = *language;
  free(language);

  // Read the context domain.
  scop->context = openscop_relation_read(file);

  // Read the parameters.
  scop->parameter_type = OPENSCOP_TYPE_STRING;
  if (openscop_util_read_int(file, NULL) > 0) {
    scop->parameters = (void **)openscop_strings_read(file);
    nb_parameters = openscop_strings_size((char **)scop->parameters);
    if ((scop->context != NULL) &&
        (nb_parameters != scop->context->nb_parameters))
      OPENSCOP_warning("bad number of parameters");
  }

  //
  // III. STATEMENT PART
  //

  // Read the number of statements.
  nb_statements = openscop_util_read_int(file, NULL);

  for (i = 0; i < nb_statements; i++) {
    // Read each statement.
    stmt = openscop_statement_read(file);
    if (scop->statement == NULL)
      scop->statement = stmt;
    else
      prev->next = stmt;
    prev = stmt;
  }

  //
  // IV. EXTENSION PART (TO THE END TAG)
  //

  // Read up the end tag (if any), and store extensions in the extension field.
  scop->extension = openscop_extension_read(file, scop->registry);
  
  if (!openscop_scop_integrity_check(scop))
    OPENSCOP_warning("scop integrity check failed");

  return scop;
}


/*+***************************************************************************
 *                   Memory allocation/deallocation functions                *
 *****************************************************************************/


/**
 * openscop_scop_register_default_extensions function:
 * this function registers the default OpenScop Library extensions to an
 * existing scop.
 * \param scop The scop for which default options have to be registered.
 */
static
void openscop_scop_register_default_extensions(openscop_scop_p scop) {
  
  openscop_extension_id_add(&scop->registry, openscop_textual_generate_id());
  openscop_extension_id_add(&scop->registry, openscop_comment_generate_id());
  openscop_extension_id_add(&scop->registry, openscop_arrays_generate_id());
  openscop_extension_id_add(&scop->registry, openscop_lines_generate_id());
  openscop_extension_id_add(&scop->registry, openscop_irregular_generate_id());
}


/**
 * openscop_scop_malloc function:
 * this function allocates the memory space for a openscop_scop_t structure and
 * sets its fields with default values. Then it returns a pointer to the
 * allocated space.
 * \return A pointer to an empty scop with fields set to default values.
 */
openscop_scop_p openscop_scop_malloc() {
  openscop_scop_p scop;

  OPENSCOP_malloc(scop, openscop_scop_p, sizeof(openscop_scop_t));
  scop->version        = 1;
  scop->language       = NULL;
  scop->context        = NULL;
  scop->parameter_type = OPENSCOP_UNDEFINED;
  scop->parameters     = NULL;
  scop->statement      = NULL;
  scop->registry       = NULL;
  scop->extension      = NULL;
  scop->usr	       = NULL;
  openscop_scop_register_default_extensions(scop);

  return scop;
}


/**
 * openscop_scop_free function:
 * This function frees the allocated memory for a openscop_scop_t structure.
 * \param scop The pointer to the scop we want to free.
 */
void openscop_scop_free(openscop_scop_p scop) {
  if (scop != NULL) {
    if (scop->language != NULL)
      free(scop->language);
    
    openscop_strings_free((char **)scop->parameters);
    openscop_relation_free(scop->context);
    openscop_statement_free(scop->statement);
    openscop_extension_id_free(scop->registry);
    openscop_extension_free(scop->extension);

    free(scop);
  }
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * openscop_scop_clone function:
 * This functions builds and returns a "hard copy" (not a pointer copy)
 * of a openscop_statement_t data structure provided as parameter.
 * Note that the usr field is not touched by this function.
 * \param statement The pointer to the scop we want to copy.
 * \return A pointer to the full copy of the scop provided as parameter.
 */
openscop_scop_p openscop_scop_clone(openscop_scop_p scop) {
  openscop_scop_p copy = NULL;
  
  if (scop != NULL) {
    copy                 = openscop_scop_malloc();
    copy->version        = scop->version;
    if (scop->language != NULL)
      copy->language     = strdup(scop->language);
    copy->context        = openscop_relation_clone(scop->context);
    copy->parameter_type = scop->parameter_type;
    copy->parameters     = (void **)openscop_strings_clone(
                               (char **)scop->parameters);
    copy->statement      = openscop_statement_clone(scop->statement);
    copy->registry       = openscop_extension_id_clone(scop->registry);
    copy->extension      = openscop_extension_clone(scop->extension);
  }

  return copy;
}


/**
 * openscop_scop_equal function:
 * this function returns true if the two scops are the same, false
 * otherwise (the usr field is not tested).
 * \param s1 The first scop.
 * \param s2 The second scop.
 * \return 1 if s1 and s2 are the same (content-wise), 0 otherwise.
 */
int openscop_scop_equal(openscop_scop_p s1, openscop_scop_p s2) {
  
  if (s1 == s2)
    return 1;

  if (s1->version != s2->version) {
    OPENSCOP_info("versions are not the same"); 
    return 0;
  }
  
  if (strcmp(s1->language, s2->language) != 0) {
    OPENSCOP_info("languages are not the same"); 
    return 0;
  }

  if (!openscop_relation_equal(s1->context, s2->context)) {
    OPENSCOP_info("contexts are not the same"); 
    return 0;
  }
  
  if (s1->parameter_type != s2->parameter_type) {
    OPENSCOP_info("parameter types are not the same"); 
    return 0;
  }

  if ((s1->parameter_type == OPENSCOP_TYPE_STRING) &&
      (!openscop_strings_equal((char **)s1->parameters,
                               (char **)s2->parameters))) {
    OPENSCOP_info("parameters are not the same"); 
    return 0;
  }
  
  if (!openscop_statement_equal(s1->statement, s2->statement)) {
    OPENSCOP_info("statements are not the same"); 
    return 0;
  }
  
  if (!openscop_extension_id_equal(s1->registry, s2->registry)) {
    OPENSCOP_info("registries are not the same"); 
    return 0;
  }

  if (!openscop_extension_equal(s1->extension, s2->extension)) {
    OPENSCOP_info("extensions are not the same"); 
    return 0;
  }


  return 1;
}


/**
 * openscop_scop_integrity_check function:
 * This function checks that a scop is "well formed". It returns 0 if the
 * check failed or 1 if no problem has been detected.
 * \param scop  The scop we want to check.
 * \return 0 if the integrity check fails, 1 otherwise.
 */
int openscop_scop_integrity_check(openscop_scop_p scop) {
  int expected_nb_parameters;

  if (scop == NULL)
    return 1;

  // Check the language.
  if ((scop->language != NULL) &&
      (!strcmp(scop->language, "caml")  || !strcmp(scop->language, "Caml") ||
       !strcmp(scop->language, "ocaml") || !strcmp(scop->language, "OCaml")))
    fprintf(stderr, "[OpenScop] Alert: What ?! Caml ?! Are you sure ?!?!\n");
  
  // Check the context.
  if (!openscop_relation_integrity_check(scop->context,
                                         OPENSCOP_TYPE_CONTEXT,
                                         OPENSCOP_UNDEFINED,
                                         OPENSCOP_UNDEFINED,
                                         OPENSCOP_UNDEFINED))
    return 0;

  // Get the number of parameters.
  if (scop->context != NULL) 
    expected_nb_parameters = scop->context->nb_parameters;
  else
    expected_nb_parameters = OPENSCOP_UNDEFINED;

  if (!openscop_statement_integrity_check(scop->statement,
                                          expected_nb_parameters))
    return 0;

  return 1;
}


/**
 * openscop_scop_register_extension function:
 * this function registers a list of extension identities to a scop, i.e., it
 * adds them to the scop registry. In addition, it will extract extensions
 * corresponding to those identities from the textual form of the extensions
 * (if any) and add them to the scop extension list.
 * \param scop The scop for which an extension id has to be registered.
 * \param id   The extension id to register within the scop.
 */
void openscop_scop_register_extension(openscop_scop_p scop,
                                      openscop_extension_id_p id) {
  openscop_extension_p textual, new;
  char * extension_string;

  if ((id != NULL) && (scop != NULL)) {
    openscop_extension_id_add(&scop->registry, id);

    textual = openscop_extension_lookup(scop->extension, id->URI);
    if (textual != NULL) {
      extension_string = ((openscop_textual_p)textual->extension)->textual;
      new = openscop_extension_sread(extension_string, id);
      openscop_extension_add(&scop->extension, new);
    }
  }
}


