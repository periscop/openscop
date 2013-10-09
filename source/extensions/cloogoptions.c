    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                     extensions/cloogoptions.c                   **
     **-----------------------------------------------------------------**
     **                   First version: 14/05/2013                     **
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

#include <osl/macros.h>
#include <osl/util.h>
#include <osl/interface.h>
#include <osl/extensions/cloogoptions.h>


/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * osl_cloogoptions_idump function:
 * this function displays an osl_cloogoptions_t structure  into a
 * file (file, possibly stdout) in a way that tends to be understandable. It
 * includes an indentation level (level) in order to work with others
 * idump functions.
 *
 * \param file         The file where the information has to be printed.
 * \param cloogoptions The cloogoptions structure to print.
 * \param level        Number of spaces before printing, for each line.
 */
void osl_cloogoptions_idump(FILE* file, osl_cloogoptions_p cloogoptions,
                           int level) {
  int j;

  // Go to the right level.
  for (j = 0; j < level; j++)
    fprintf(file, "|\t");

  if (cloogoptions != NULL)
    fprintf(file, "+-- osl_cloogoptions_t\n");
  else
    fprintf(file, "+-- NULL cloogoptions\n");

  if (cloogoptions != NULL) {
    // Go to the right level.
    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "l: %d\n", cloogoptions->l);

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "f: %d\n", cloogoptions->f);


    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "fs_ls_size: %d\n", cloogoptions->fs_ls_size);

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    int *ptr = cloogoptions->fs;
    fprintf(file, "fs:");
    for (j=0; j<cloogoptions->fs_ls_size; j++)
      fprintf(file, " %d,", *ptr++);
    fprintf(file, "\n");


    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    ptr = cloogoptions->ls;
    fprintf(file, "ls:");
    for (j=0; j<cloogoptions->fs_ls_size; j++)
      fprintf(file, " %d,", *ptr++);
    fprintf(file, "\n");



    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "stop: %d\n", cloogoptions->stop);

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "strides: %d\n", cloogoptions->strides);

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "sh: %d\n", cloogoptions->sh);

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "first_unroll: %d\n", cloogoptions->first_unroll);

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "esp: %d\n", cloogoptions->esp);

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "fsp: %d\n", cloogoptions->fsp);

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "otl: %d\n", cloogoptions->otl);

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "block: %d\n", cloogoptions->block);

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "compilable: %d\n", cloogoptions->compilable);

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "callable: %d\n", cloogoptions->callable);

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "language: %d\n", cloogoptions->language);

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file, "save_domains: %d\n", cloogoptions->save_domains);


    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    if(cloogoptions->name)
    fprintf(file, "name: %s\n", cloogoptions->name);
    else
    fprintf(file, "name: NULL\n");


    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    if (cloogoptions->scop != NULL)
      fprintf(file,"scop: (present but not printed).\n");
    else
      fprintf(file,"scop: NULL.\n");


    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file,"quiet: %d\n",cloogoptions->quiet) ;


    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file,"UNDOCUMENTED OPTIONS FOR THE AUTHOR ONLY\n") ;

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file,"leaks: %d\n",cloogoptions->leaks) ;

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file,"backtrack: %d\n",cloogoptions->backtrack);

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file,"override: %d\n",cloogoptions->override) ;

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file,"structure: %d\n",cloogoptions->structure) ;

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file,"noscalars: %d\n",cloogoptions->noscalars) ;

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file,"noblocks: %d\n",cloogoptions->noblocks) ;

    for (j = 0; j <= level; j++)
      fprintf(file, "|\t");
    fprintf(file,"nosimplify: %d\n",cloogoptions->nosimplify) ;

  }

  // The last line.
  for (j = 0; j <= level; j++)
    fprintf(file, "|\t");
  fprintf(file, "\n");
}



/**
 * osl_cloogoptions_dump function:
 * this function prints the content of an osl_cloogoptions_t structure
 * (*cloogoptions) into a file (file, possibly stdout).
 *
 * \param file         The file where the information has to be printed.
 * \param cloogoptions The cloogoptions structure to print.
 */
void osl_cloogoptions_dump(FILE* file, osl_cloogoptions_p cloogoptions) {
  osl_cloogoptions_idump(file, cloogoptions, 0);
}




/**
 * osl_cloogoptions_sprint function:
 * this function prints the content of an osl_cloogoptions_t structure
 * (*cloogoptions) into a string (returned) in the OpenScop textual format.
 *
 * \param  cloogoptions The cloogoptions structure to be printed.
 * \return              A string containing the OpenScop dump of the
 *                      cloogoptions structure.
 */
char* osl_cloogoptions_sprint(osl_cloogoptions_p cloogoptions) {
  int   high_water_mark = OSL_MAX_STRING;
  char* string = NULL;
  char  buffer[OSL_MAX_STRING];
  int   j = 0;

  if (cloogoptions != NULL) {
    OSL_malloc(string, char*, high_water_mark * sizeof(char));
    string[0] = '\0';

    // Print the cloogoptions content.
    sprintf(buffer, "# Last level to optimize\n%d\n", cloogoptions->l);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);

    sprintf(buffer, "# First level to optimize\n%d\n", cloogoptions->f);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);

    sprintf(buffer,"# size of fs and ls arrays\n%d\n",cloogoptions->fs_ls_size);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);

    sprintf(buffer, "# Last level to optimize (statement wise)\n");
    osl_util_safe_strcat(&string, buffer, &high_water_mark);
    for (j=0; j<cloogoptions->fs_ls_size; j++) {
      sprintf(buffer, "%d\n", cloogoptions->ls[j]);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    sprintf(buffer, "# First level to optimize (statement wise)\n");
    osl_util_safe_strcat(&string, buffer, &high_water_mark);
    for (j=0; j<cloogoptions->fs_ls_size; j++) {
      sprintf(buffer, "%d\n", cloogoptions->fs[j]);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    sprintf(buffer, "# Level to stop code generation\n%d\n"
                    "# Handle non-unit strides\n%d\n"
                    "# Compute simple hulls\n%d\n"
                    "# First dimension to unroll\n%d\n"
                    "# Spread equalities\n%d\n"
                    "# Level to start spreading equalities\n%d\n"
                    "# Eliminate one time loops\n%d\n"
                    "# Make block per dimension\n%d\n"
                    "# Generate compilable code\n%d\n"
                    "# Generate callable code\n%d\n"
                    "# Language: 1 Fortran, 0 C\n%d\n"
                    "# Save copy of domain\n%d\n",
           	    cloogoptions->stop,
           	    cloogoptions->strides,
           	    cloogoptions->sh,
           	    cloogoptions->first_unroll,
           	    cloogoptions->esp,
           	    cloogoptions->fsp,
           	    cloogoptions->otl,
           	    cloogoptions->block,
           	    cloogoptions->compilable,
           	    cloogoptions->callable,
           	    cloogoptions->language,
           	    cloogoptions->save_domains);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);

    sprintf(buffer, "# File name\n%s\n",
            cloogoptions->name?cloogoptions->name:OSL_STRING_NULL);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);

    sprintf(buffer,
                    "# Input has openscop format\n%d\n"
                    "# Quiet\n%d\n"
                    "# Check for memory leaks\n%d\n"
                    "# Backtracking in QW algorithm\n%d\n"
                    "# Bypass cloog correctness\n%d\n"
                    "# Print structure\n%d\n"
                    "# Dont make blocks\n%d\n"
                    "# Dont use scalar dims\n%d\n"
                    "# Dont simplify polyhedra\n%d\n",
           	    cloogoptions->openscop,
           	    cloogoptions->quiet,
           	    cloogoptions->leaks,
           	    cloogoptions->backtrack,
           	    cloogoptions->override,
           	    cloogoptions->structure,
           	    cloogoptions->noblocks,
           	    cloogoptions->noscalars,
           	    cloogoptions->nosimplify);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);


    // Keep only the memory space we need.
    OSL_realloc(string, char*, (strlen(string) + 1) * sizeof(char));
  }

  return string;
}



/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/**
 * osl_cloogoptions_sread function:
 * this function reads a cloogoptions structure from a string complying to the
 * OpenScop textual format and returns a pointer to this structure.
 * The input parameter is updated to the position in the input string this
 * function reaches right after reading the cloogoptions structure.
 *
 * \param[in,out] input The input string where to find cloogoptions.
 *                      Updated to the position after what has been read.
 * \return              A pointer to the cloogoptions structure that has
 *                      been read.
 */
osl_cloogoptions_p osl_cloogoptions_sread(char** input) {
  osl_cloogoptions_p cloogoptions;
  int j=0;

  if (*input == NULL) {
    OSL_debug("no cloogoptions optional tag");
    return NULL;
  }

  // Build the cloogoptions structure.
  cloogoptions = osl_cloogoptions_malloc();

  // Read the cloogoptions.
  cloogoptions->l = osl_util_read_int(NULL, input);
  cloogoptions->f = osl_util_read_int(NULL, input);
  cloogoptions->fs_ls_size = osl_util_read_int(NULL, input);

  if (cloogoptions->fs_ls_size) {
    OSL_malloc(cloogoptions->ls, int*, cloogoptions->fs_ls_size);
    for (j=0; j< cloogoptions->fs_ls_size; j++)
      cloogoptions->ls[j] = osl_util_read_int(NULL, input);

    OSL_malloc(cloogoptions->fs, int*, cloogoptions->fs_ls_size);
    for (j=0; j< cloogoptions->fs_ls_size; j++)
      cloogoptions->fs[j] = osl_util_read_int(NULL, input);
  }

  cloogoptions->stop = osl_util_read_int(NULL, input);
  cloogoptions->strides = osl_util_read_int(NULL, input);
  cloogoptions->sh = osl_util_read_int(NULL, input);
  cloogoptions->first_unroll = osl_util_read_int(NULL, input);
  cloogoptions->esp = osl_util_read_int(NULL, input);
  cloogoptions->fsp = osl_util_read_int(NULL, input);
  cloogoptions->otl = osl_util_read_int(NULL, input);
  cloogoptions->block = osl_util_read_int(NULL, input);
  cloogoptions->compilable = osl_util_read_int(NULL, input);
  cloogoptions->callable = osl_util_read_int(NULL, input);
  cloogoptions->language = osl_util_read_int(NULL, input);
  cloogoptions->save_domains = osl_util_read_int(NULL, input);

  // Read the file name (and path).
  cloogoptions->name = osl_util_read_string(NULL, input);
  if (!strcmp(cloogoptions->name,OSL_STRING_NULL)) {
    free(cloogoptions->name);
    cloogoptions->name = NULL;
  }

  cloogoptions->openscop = osl_util_read_int(NULL, input);
  cloogoptions->quiet = osl_util_read_int(NULL, input);
  cloogoptions->leaks = osl_util_read_int(NULL, input);
  cloogoptions->backtrack = osl_util_read_int(NULL, input);
  cloogoptions->override = osl_util_read_int(NULL, input);
  cloogoptions->structure = osl_util_read_int(NULL, input);
  cloogoptions->noblocks = osl_util_read_int(NULL, input);
  cloogoptions->noscalars = osl_util_read_int(NULL, input);
  cloogoptions->nosimplify = osl_util_read_int(NULL, input);

  return cloogoptions;
}



/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/


/**
 * osl_cloogoptions_malloc function:
 * This function allocates the memory space for a osl_cloogoptions structure and
 * fills its fields with the default values. It returns a pointer to the
 * allocated structure.
 *
 * \return    A pointer to the cloogoptions structure that has been allocated.
 */
osl_cloogoptions_p osl_cloogoptions_malloc()
{ osl_cloogoptions_p options ;

  /* Memory allocation for the CloogOptions structure. */
  OSL_malloc(options, osl_cloogoptions_p, sizeof(osl_cloogoptions_t));

  /* We set the various fields with default values. */
  /* OPTIONS FOR LOOP GENERATION */
  options->l            = -1;   /* Last level to optimize: infinity. */
  options->f            =  1;   /* First level to optimize: the first. */
  options->ls           = NULL; /* Statement-wise l option is not set */
  options->fs           = NULL; /* Statement-wise f option is not set */
  options->fs_ls_size   = 0;    /* No statement-wise f/s control */
  options->stop         = -1;   /* Generate all the code. */
  options->strides      = 0;    /* Generate a code with unit strides. */
  options->sh	          = 0;    /* Compute actual convex hull. */
  options->first_unroll = -1;   /* First level to unroll: none. */
  options->name	        = NULL;
  /* OPTIONS FOR PRETTY PRINTING */
  options->esp          = 1;  /* We want Equality SPreading.*/
  options->fsp          = 1;  /* The First level to SPread is the first. */
  options->otl          = 1;  /* We want to fire One Time Loops. */
  options->block        = 0;  /* We don't want to force statement blocks. */
  options->compilable   = 0;  /* No compilable code. */
  options->callable     = 0;  /* No callable code. */
  options->quiet        = 0;  /* Do print informational messages. */
  options->save_domains = 0;  /* Don't save domains. */
  /* MISC OPTIONS */
  options->language     = 0;  /* The default output language is C. */
  options->openscop     = 0;  /* The input file has not the OpenScop format.*/
  options->scop         = NULL; /* No default SCoP.*/
  /* UNDOCUMENTED OPTIONS FOR THE AUTHOR ONLY */
  options->leaks        = 0;  /* I don't want to print allocation statistics.*/
  options->backtrack    = 0;  /* Perform backtrack in Quillere's algorithm.*/
  options->override     = 0;  /* I don't want to override CLooG decisions.*/
  options->structure    = 0;  /* I don't want to print internal structure.*/
  options->noblocks     = 0;  /* I do want to make statement blocks.*/
  options->noscalars    = 0;  /* I do want to use scalar dimensions.*/
  options->nosimplify   = 0;  /* I do want to simplify polyhedra.*/

  return options ;
}



/**
 * osl_cloogoptions_free function:
 * This functions frees the memory space for a osl_cloogoptions structure
 *
 * \param[in] input Pointer to osl_cloogoptions_t to free
 */
void osl_cloogoptions_free(osl_cloogoptions_p options){

  if (options->fs)
    free(options->fs);
  if (options->ls)
    free(options->ls);
  if (options->name)
    free(options->name);

  free(options);
}



/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/


/**
 * osl_cloogoptions_clone function:
 * This function makes a hard copy of the osl_cloogoptions structure passed
 * to it and returns a pointer to the newly formed copy.
 *
 * \param[in] options   Pointer to osl_cloogoptions_t structure to clone
 * \return              Pointer to newly created clone.
 */
osl_cloogoptions_p osl_cloogoptions_clone(osl_cloogoptions_p options)
{ osl_cloogoptions_p cloogoptions ;
  int j=0;

  /* Memory allocation for the CloogOptions structure. */
  cloogoptions = osl_cloogoptions_malloc();

  /* OPTIONS FOR LOOP GENERATION */
  cloogoptions->l           = options->l;
  cloogoptions->f           = options->f;
  cloogoptions->fs_ls_size  = options->fs_ls_size;

  if (cloogoptions->fs_ls_size) {
    OSL_malloc(cloogoptions->ls, int*, options->fs_ls_size);
    OSL_malloc(cloogoptions->fs, int*, options->fs_ls_size);
    for (j=0; j< cloogoptions->fs_ls_size; j++) {
      cloogoptions->ls[j] = options->ls[j];
      cloogoptions->fs[j] = options->fs[j];
    }
  }
  cloogoptions->stop         = options->stop ;
  cloogoptions->strides      = options->strides;
  cloogoptions->sh	         = options->sh;
  cloogoptions->first_unroll = options->first_unroll;

  if (options->name)
    OSL_strdup(cloogoptions->name, options->name);

  /* OPTIONS FOR PRETTY PRINTING */
  cloogoptions->esp          = options->esp;
  cloogoptions->fsp          = options->fsp;
  cloogoptions->otl          = options->otl;
  cloogoptions->block        = options->block;
  cloogoptions->compilable   = options->compilable;
  cloogoptions->callable     = options->callable;
  cloogoptions->quiet        = options->quiet;
  cloogoptions->save_domains = options->save_domains;
  /* MISC OPTIONS */
  cloogoptions->language     =  options->language;
  cloogoptions->openscop     =  options->openscop;
  cloogoptions->scop         =  options->scop;
  /* UNDOCUMENTED OPTIONS FOR THE AUTHOR ONLY */
  cloogoptions->leaks        =  options->leaks;
  cloogoptions->backtrack    =  options->backtrack;
  cloogoptions->override     =  options->override;
  cloogoptions->structure    =  options->structure;
  cloogoptions->noblocks     =  options->noblocks;
  cloogoptions->noscalars    =  options->noscalars;
  cloogoptions->nosimplify   =  options->nosimplify;

  return cloogoptions ;
}



/**
 * osl_cloogoptions_equal function:
 * This functions compares two osl_cloogoptions_t structures and returns 1
 * if the two are equal, 0 otherwise
 *
 * \param[in] cloogoptions Pointer to osl_cloogoptions_t structure to compare
 * \param[in] options      Pointer to osl_cloogoptions_t structure to compare
 * \return                 1 if both structures are equal, 0 otherwise
 */
int osl_cloogoptions_equal(osl_cloogoptions_p cloogoptions,
                           osl_cloogoptions_p options)
{

  int j = 0;

  if (cloogoptions == options)
    return 1;

  /* OPTIONS FOR LOOP GENERATION */
  if (cloogoptions->l != options->l)
    return 0;
  if (cloogoptions->f != options->f)
    return 0;
  if (cloogoptions->fs_ls_size  != options->fs_ls_size)
    return 0;

  for (j=0; j< cloogoptions->fs_ls_size; j++) {
    if (cloogoptions->ls[j] != options->ls[j])
    return 0;
    if (cloogoptions->fs[j] != options->fs[j])
    return 0;
  }
  if (cloogoptions->fs != options->fs)
    return 0;
  if (cloogoptions->stop != options->stop)
    return 0;
  if (cloogoptions->strides != options->strides)
    return 0;
  if (cloogoptions->sh != options->sh)
    return 0;
  if (cloogoptions->first_unroll != options->first_unroll)
    return 0;

  if (cloogoptions->name != options->name) {
    if (!strcmp(cloogoptions->name, options->name))
      return 0;
  }
  /* OPTIONS FOR PRETTY PRINTING */
  if (cloogoptions->esp != options->esp)
    return 0;
  if (cloogoptions->fsp != options->fsp)
    return 0;
  if (cloogoptions->otl != options->otl)
    return 0;
  if (cloogoptions->block != options->block)
    return 0;
  if (cloogoptions->compilable  != options->compilable)
    return 0;
  if (cloogoptions->callable != options->callable)
    return 0;
  if (cloogoptions->quiet != options->quiet)
    return 0;
  if (cloogoptions->save_domains != options->save_domains)
    return 0;
  /* MISC OPTIONS */
  if (cloogoptions->language != options->language)
    return 0;
  if (cloogoptions->openscop != options->openscop)
    return 0;
  if (cloogoptions->scop != options->scop)
    return 0;
  /* UNDOCUMENTED OPTIONS FOR THE AUTHOR ONLY */
  if (cloogoptions->leaks != options->leaks)
    return 0;
  if (cloogoptions->backtrack != options->backtrack)
    return 0;
  if (cloogoptions->override != options->override)
    return 0;
  if (cloogoptions->structure != options->structure)
    return 0;
  if (cloogoptions->noblocks != options->noblocks)
    return 0;
  if (cloogoptions->noscalars != options->noscalars)
    return 0;
  if (cloogoptions->nosimplify != options->nosimplify)
    return 0;

  return 1;
}


/**
 * osl_cloogoptions_interface function:
 * this function creates an interface structure corresponding the cloogoptions
 * extension and returns it.
 *
 * \return An interface structure for the cloogoptions extension.
 */
osl_interface_p osl_cloogoptions_interface() {
  osl_interface_p interface = osl_interface_malloc();

  interface->URI    = strdup(OSL_URI_CLOOGOPTIONS);
  interface->idump  = (osl_idump_f)osl_cloogoptions_idump;
  interface->sprint = (osl_sprint_f)osl_cloogoptions_sprint;
  interface->sread  = (osl_sread_f)osl_cloogoptions_sread;
  interface->malloc = (osl_malloc_f)osl_cloogoptions_malloc;
  interface->free   = (osl_free_f)osl_cloogoptions_free;
  interface->clone  = (osl_clone_f)osl_cloogoptions_clone;
  interface->equal  = (osl_equal_f)osl_cloogoptions_equal;

  return interface;
}

