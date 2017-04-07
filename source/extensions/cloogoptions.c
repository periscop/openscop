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
#include <osl/scop.h>
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
    fprintf(file,"quiet: %d\n",cloogoptions->quiet) ;
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
    if (cloogoptions->l_set) {
      sprintf(buffer, "l %d # Last level to optimize\n", cloogoptions->l);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->f_set) {
      sprintf(buffer, "f %d # First level to optimize\n", cloogoptions->f);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->fs_ls_size_set) {
      sprintf(buffer,"fs-ls-size %d # size of fs and ls arrays\n",
              cloogoptions->fs_ls_size);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->ls_set) {
      sprintf(buffer, "ls ");
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
      for (j=0; j<cloogoptions->fs_ls_size; j++) {
        sprintf(buffer, "%d ", cloogoptions->ls[j]);
        osl_util_safe_strcat(&string, buffer, &high_water_mark);
      }
      sprintf(buffer, "# Last level to optimize (statement wise)\n");
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->fs_set) {
      sprintf(buffer, "fs ");
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
      for (j=0; j<cloogoptions->fs_ls_size; j++) {
        sprintf(buffer, "%d ", cloogoptions->fs[j]);
        osl_util_safe_strcat(&string, buffer, &high_water_mark);
      }
      sprintf(buffer, "# First level to optimize (statement wise)\n");
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->stop_set) {
      sprintf(buffer, "stop %d # Level to stop code generation\n",
              cloogoptions->stop);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->strides_set) {
      sprintf(buffer, "strides %d # Handle non-unit strides\n",
              cloogoptions->strides);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->sh_set) {
      sprintf(buffer, "sh %d # Compute simple hulls\n", cloogoptions->sh);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->first_unroll_set) {
      sprintf(buffer, "first-unroll %d # First dimension to unroll\n",
              cloogoptions->first_unroll);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->otl_set) {
      sprintf(buffer, "otl %d # Eliminate one time loops\n",
              cloogoptions->otl);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->esp_set) {
      sprintf(buffer, "esp %d # Spread equalities\n", cloogoptions->esp);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->fsp_set) {
      sprintf(buffer, "fsp %d # Level to start spreading equalities\n",
              cloogoptions->fsp);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->block_set) {
      sprintf(buffer, "block %d # Make block per dimension\n",
              cloogoptions->block);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->compilable_set) {
      sprintf(buffer, "compilable %d # Generate compilable code\n",
              cloogoptions->compilable);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->callable_set) {
      sprintf(buffer, "callable %d # Generate callable code\n",
              cloogoptions->callable);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->language_set) {
      sprintf(buffer, "language %d # Language: 1 Fortran, 0 C\n",
              cloogoptions->language);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->name_set) {
      sprintf(buffer, "name %s # Name of the input file\n",
              cloogoptions->name);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->save_domains_set) {
      sprintf(buffer, "save-domains %d # Save copy of domain\n",
              cloogoptions->save_domains);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->openscop_set) {
      sprintf(buffer, "openscop %d # Input has openscop format\n",
              cloogoptions->openscop);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    if (cloogoptions->quiet_set) {
      sprintf(buffer, "quiet %d # Quiet\n", cloogoptions->openscop);
      osl_util_safe_strcat(&string, buffer, &high_water_mark);
    }

    // Keep only the memory space we need.
    OSL_realloc(string, char*, (strlen(string) + 1) * sizeof(char));
  }

  return string;
}



/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/


/**
 * osl_cloogoptions_read_args function:
 * this function reads CloogOptions passed to the main on the command line.
 * These options have the format "--cloog-option argument". This function will
 * onle read options belonging the CLooG. It will then update the passed
 * array of strings by removing the options that it has read. It will also
 * update the pointer to the number of arguments accordingly.
 *
 * \param[in,out] argc_ptr Pointer to argument count.
 * \param[in,out] argv_ptr Pointer to array of strings containing arguments.
 * \return osl_cloogoptions_p structure constructed from arguments.
 */
osl_cloogoptions_p osl_cloogoptions_read_args(int *argc_ptr, char***argv_ptr){

  int argc = *argc_ptr;
  char** argv = *argv_ptr;
  char** newargv = NULL;
  int i = 0;
  int new_i = 0;
  int idx = 0;
  int unused_cnt = 0;
  int *used = (int*)malloc(sizeof(int)*argc);

  osl_cloogoptions_p clops = osl_cloogoptions_malloc();
  for(i=0; i< argc; i++)
    used[i] = 0;

  for (i=0; i< argc; i++) {
    if (!strcmp(argv[i], "--cloog-l")) {
      used[i++] = 1;
      clops->l_set = osl_util_read_arg_int(i, argv, &clops->l);
      used[i] = 1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-f")) {
      used[i++] = 1;
      clops->f_set = osl_util_read_arg_int(i, argv, &clops->f);
      used[i] = 1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-fs-ls-size")) {
      used[i++] = 1;
      clops->fs_ls_size_set = osl_util_read_arg_int(i, argv,
                                &clops->fs_ls_size);
      used[i] = 1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-ls")) {
      if (!clops->fs_ls_size_set)
        OSL_error("--cloog-fs-ls-size options should be before --cloog-ls\n");

      OSL_malloc(clops->ls, int*, sizeof(int)*clops->fs_ls_size);
      used[i++] = 1;
      for (idx=0; idx<clops->fs_ls_size; idx++) {
        clops->ls_set = osl_util_read_arg_int(i, argv, &clops->ls[idx]);
        used[i+idx] = 1;
      }
      i += clops->fs_ls_size-1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-fs")) {
      if (!clops->fs_ls_size_set)
        OSL_error("--cloog-fs-ls-size options should be before --cloog-fs\n");

      OSL_malloc(clops->fs, int*, sizeof(int)*clops->fs_ls_size);
      used[i++] = 1;  //--cloog-fs
      for (idx=0; idx<clops->fs_ls_size; idx++) {
        clops->fs_set = osl_util_read_arg_int(i, argv, &clops->fs[idx]);
        used[i+idx] = 1;
      }
      i += clops->fs_ls_size-1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-stop")) {
      used[i++] = 1;
      clops->stop_set = osl_util_read_arg_int(i, argv, &clops->stop);
      used[i] = 1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-strides")) {
      used[i++] = 1;
      clops->strides = osl_util_read_arg_int(i, argv, &clops->strides);
      used[i] = 1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-sh")) {
      used[i++] = 1;
      clops->sh_set = osl_util_read_arg_int(i, argv, &clops->sh);
      used[i] = 1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-first-unroll")) {
      used[i++] = 1;
      clops->first_unroll_set = osl_util_read_arg_int(i, argv,
                                &clops->first_unroll);
      used[i] = 1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-esp")) {
      used[i++] = 1;
      clops->esp_set = osl_util_read_arg_int(i, argv, &clops->esp);
      used[i] = 1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-fsp")) {
      used[i++] = 1;
      clops->fsp_set = osl_util_read_arg_int(i, argv, &clops->fsp);
      used[i] = 1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-otl")) {
      used[i++] = 1;
      clops->otl_set = osl_util_read_arg_int(i, argv, &clops->otl);
      used[i] = 1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-block")) {
      used[i++] = 1;
      clops->block_set = osl_util_read_arg_int(i, argv, &clops->block);
      used[i] = 1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-compilable")) {
      used[i++] = 1;
      clops->compilable_set = osl_util_read_arg_int(i, argv,
                              &clops->compilable);
      used[i] = 1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-callable")) {
      used[i++] = 1;
      clops->callable_set = osl_util_read_arg_int(i,
                            argv, &clops->callable);
      used[i] = 1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-quiet")) {
      used[i++] = 1;
      clops->quiet_set = osl_util_read_arg_int(i, argv, &clops->quiet);
      used[i] = 1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-save-domains")) {
      used[i++] = 1;
      clops->save_domains_set = osl_util_read_arg_int(i, argv,
                                &clops->save_domains);
      used[i] = 1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-name")) {
      used[i++] = 1;
      clops->name_set = osl_util_read_arg_string(i, argv, &clops->name);
      used[i] = 1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-language")) {
      used[i++] = 1;
      clops->language_set = osl_util_read_arg_int(i, argv, &clops->language);
      used[i] = 1;  // incremented by loop
    }

    if (!strcmp(argv[i], "--cloog-openscop")) {
      used[i++] = 1;
      clops->openscop_set = osl_util_read_arg_int(i, argv, &clops->openscop);
      used[i] = 1;  // incremented by loop
    }

  }

  //Integrity check for -fs -ls
  if ((clops->fs_ls_size && (!clops->fs || !clops->ls))
      || (!clops->fs_ls_size && (clops->fs || clops->ls)))
    OSL_error("Both cloog-fs and cloog-ls should have fs_ls_size elements.\n");

  //Remove the consumed arguments from the list
  for (i=0; i< argc; i++)
    if (used[i]==0)
      unused_cnt++;

  newargv = (char**)malloc(sizeof(char*)*unused_cnt);

  for (i=0; i< argc; i++)
    if (used[i]==0)
      OSL_strdup(newargv[new_i++], argv[i]);

  for (i=0; i< argc; i++)
    free(argv[i]);
  free(argv);
  free(used);

  *argc_ptr = unused_cnt;
  *argv_ptr = newargv;

  return clops;
}


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
  char* line = NULL;
  char* line_bk = NULL;
  char* option = NULL;

  if (*input == NULL) {
    OSL_debug("no cloogoptions optional tag");
    return NULL;
  }

  // Build the cloogoptions structure.
  cloogoptions = osl_cloogoptions_malloc();

  // Read the cloogoptions.
  line_bk = line = osl_util_read_line(NULL, input);
  while (line[0]) {

    if (option)
      free(option);
    option = osl_util_read_string(NULL, &line);

    if (strcmp(option, "l")==0) {
      cloogoptions->l = osl_util_read_int(NULL, &line);
      cloogoptions->l_set = 1;
    }

    if (strcmp(option, "f")==0) {
      cloogoptions->f = osl_util_read_int(NULL, &line);
      cloogoptions->f_set = 1;
    }

    if (strcmp(option, "fs-ls-size")==0) {
      cloogoptions->fs_ls_size = osl_util_read_int(NULL, &line);
      cloogoptions->fs_ls_size_set = 1;
    }

    if (strcmp(option, "ls")==0) {
      if (!cloogoptions->fs_ls_size_set)
        OSL_error("option fs-ls-size should be provided before ls\n");

      OSL_malloc(cloogoptions->ls, int*,
                 sizeof(int*)*cloogoptions->fs_ls_size);
      for (j=0; j< cloogoptions->fs_ls_size; j++)
        cloogoptions->ls[j] = osl_util_read_int(NULL, &line);
      cloogoptions->ls_set = 1;
    }

    if (strcmp(option, "fs")==0) {
      if (!cloogoptions->fs_ls_size_set)
        OSL_error("option fs-ls-size should be provided before fs\n");

      OSL_malloc(cloogoptions->fs, int*,
                 sizeof(int*)*cloogoptions->fs_ls_size);
      for (j=0; j< cloogoptions->fs_ls_size; j++)
        cloogoptions->fs[j] = osl_util_read_int(NULL, &line);
      cloogoptions->fs_set = 1;
    }

    if (strcmp(option, "stop")==0) {
      cloogoptions->stop = osl_util_read_int(NULL, &line);
      cloogoptions->stop_set = 1;
    }

    if (strcmp(option, "strides")==0) {
      cloogoptions->strides = osl_util_read_int(NULL, &line);
      cloogoptions->strides = 1;
    }

    if (strcmp(option, "sh")==0) {
      cloogoptions->sh = osl_util_read_int(NULL, &line);
      cloogoptions->sh_set = 1;
    }

    if (strcmp(option, "first-unroll")==0) {
      cloogoptions->first_unroll = osl_util_read_int(NULL, &line);
      cloogoptions->first_unroll_set = 1;
    }

    if (strcmp(option, "esp")==0) {
      cloogoptions->esp = osl_util_read_int(NULL, &line);
      cloogoptions->esp_set = 1;
    }

    if (strcmp(option, "fsp")==0) {
      cloogoptions->fsp = osl_util_read_int(NULL, &line);
      cloogoptions->fsp_set = 1;
    }

    if (strcmp(option, "otl")==0) {
      cloogoptions->otl = osl_util_read_int(NULL, &line);
      cloogoptions->otl_set = 1;
    }

    if (strcmp(option, "block")==0) {
      cloogoptions->block = osl_util_read_int(NULL, &line);
      cloogoptions->block_set = 1;
    }

    if (strcmp(option, "compilable")==0) {
      cloogoptions->compilable = osl_util_read_int(NULL, &line);
      cloogoptions->compilable_set = 1;
    }

    if (strcmp(option, "callable")==0) {
      cloogoptions->callable = osl_util_read_int(NULL, &line);
      cloogoptions->callable_set = 1;
    }

    if (strcmp(option, "language")==0) {
      cloogoptions->language = osl_util_read_int(NULL, &line);
      cloogoptions->language_set = 1;
    }

    if (strcmp(option, "name")==0) {
      cloogoptions->name = osl_util_read_string(NULL, &line);
      cloogoptions->name_set = 1;
    }

    if (strcmp(option, "save-domains")==0) {
      cloogoptions->save_domains = osl_util_read_int(NULL, &line);
      cloogoptions->save_domains_set = 1;
    }

    if (strcmp(option, "openscop")==0) {
      cloogoptions->openscop = osl_util_read_int(NULL, &line);
      cloogoptions->openscop_set = 1;
    }

    if (strcmp(option, "quiet")==0) {
      cloogoptions->quiet = osl_util_read_int(NULL, &line);
      cloogoptions->quiet_set = 1;
    }

    if (line)
      free(line_bk);
    line_bk = line = osl_util_read_line(NULL, input);
  }

  if(line)
    free(line);
  if(option)
    free(option);
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
  options->l_set        = 0;
  options->f            =  1;   /* First level to optimize: the first. */
  options->f_set        = 0;
  options->ls           = NULL; /* Statement-wise l option is not set */
  options->ls_set       = 0;
  options->fs           = NULL; /* Statement-wise f option is not set */
  options->fs_set       = 0;
  options->fs_ls_size   = 0;    /* No statement-wise f/s control */
  options->fs_ls_size_set = 0;
  options->stop         = -1;   /* Generate all the code. */
  options->stop_set     = 0;
  options->strides      = 0;    /* Generate a code with unit strides. */
  options->strides_set  = 0;
  options->sh	          = 0;    /* Compute actual convex hull. */
  options->sh_set       = 0;
  options->first_unroll = -1;   /* First level to unroll: none. */
  options->first_unroll_set = 0;
  options->name	        = NULL;
  /* OPTIONS FOR PRETTY PRINTING */
  options->esp          = 1;    /* We want Equality SPreading.*/
  options->esp_set      = 0;
  options->fsp          = 1;    /* The First level to SPread is the first. */
  options->fsp_set      = 0;
  options->otl          = 1;    /* We want to fire One Time Loops. */
  options->otl_set      = 0;
  options->block        = 0;    /* We don't want to force statement blocks. */
  options->block_set    = 0;
  options->compilable   = 0;    /* No compilable code. */
  options->compilable_set = 0;
  options->callable     = 0;    /* No callable code. */
  options->callable_set = 0;
  options->quiet        = 0;    /* Do print informational messages. */
  options->quiet_set    = 0;
  options->save_domains = 0;    /* Don't save domains. */
  options->save_domains_set = 0;
  /* MISC OPTIONS */
  options->language     = 0;    /* The default output language is C. */
  options->language_set = 0;
  options->openscop     = 0;    /* The input file has not the OpenScop format.*/
  options->openscop_set = 0;

  return options ;
}



/**
 * osl_cloogoptions_free function:
 * This functions frees the memory space for a osl_cloogoptions structure
 *
 * \param[in] input Pointer to osl_cloogoptions_t to free
 */
void osl_cloogoptions_free(osl_cloogoptions_p options){

  if (options->fs_set)
    free(options->fs);
  if (options->ls_set)
    free(options->ls);
  if (options->name_set)
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
  cloogoptions->l_set       = options->l_set;
  cloogoptions->l           = options->l;
  cloogoptions->f_set       = options->f_set;
  cloogoptions->f           = options->f;
  cloogoptions->fs_ls_size_set  = options->fs_ls_size_set;
  cloogoptions->fs_ls_size  = options->fs_ls_size;

  cloogoptions->ls_set      = options->ls_set ;
  cloogoptions->fs_set      = options->fs_set ;
  if (options->fs_ls_size_set && options->fs_set
            && options->ls_set) {
    OSL_malloc(cloogoptions->ls, int*, sizeof(int)*options->fs_ls_size);
    OSL_malloc(cloogoptions->fs, int*, sizeof(int)*options->fs_ls_size);
    for (j=0; j< cloogoptions->fs_ls_size; j++) {
      cloogoptions->ls[j]   = options->ls[j];
      cloogoptions->fs[j]   = options->fs[j];
    }
  }
  else {
    OSL_error("cloog-fs-ls-size, cloog-ls, cloog-fs must be set together\n");
  }

  cloogoptions->stop_set     = options->stop_set ;
  cloogoptions->stop         = options->stop ;
  cloogoptions->strides_set  = options->strides_set;
  cloogoptions->strides      = options->strides;
  cloogoptions->sh_set	     = options->sh_set;
  cloogoptions->sh	         = options->sh;
  cloogoptions->first_unroll_set = options->first_unroll_set;
  cloogoptions->first_unroll = options->first_unroll;

  cloogoptions->name_set	   = options->name_set;
  if (options->name)
    OSL_strdup(cloogoptions->name, options->name);

  /* OPTIONS FOR PRETTY PRINTING */
  cloogoptions->esp_set      = options->esp_set;
  cloogoptions->esp          = options->esp;
  cloogoptions->fsp_set      = options->fsp_set;
  cloogoptions->fsp          = options->fsp;
  cloogoptions->otl_set      = options->otl_set;
  cloogoptions->otl          = options->otl;
  cloogoptions->block_set    = options->block_set;
  cloogoptions->block        = options->block;
  cloogoptions->compilable_set   = options->compilable_set;
  cloogoptions->compilable   = options->compilable;
  cloogoptions->callable_set = options->callable_set;
  cloogoptions->callable     = options->callable;
  cloogoptions->quiet_set    = options->quiet_set;
  cloogoptions->quiet        = options->quiet;
  cloogoptions->save_domains_set = options->save_domains_set;
  cloogoptions->save_domains = options->save_domains;
  /* MISC OPTIONS */
  cloogoptions->language_set     =  options->language_set;
  cloogoptions->language     =  options->language;
  cloogoptions->openscop_set =  options->openscop_set;
  cloogoptions->openscop     =  options->openscop;

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
  if ((cloogoptions->l_set != options->l_set)
      || (cloogoptions->l != options->l))
    return 0;
  if ((cloogoptions->f_set != options->f_set)
      || (cloogoptions->f != options->f))
    return 0;
  if ((cloogoptions->fs_ls_size_set != options->fs_ls_size_set)
      || (cloogoptions->fs_ls_size  != options->fs_ls_size))
    return 0;

  if ((cloogoptions->fs_set != options->fs_set)
      || (cloogoptions->ls_set != options->ls_set))
    return 0;
  for (j=0; j< cloogoptions->fs_ls_size; j++) {
    if (cloogoptions->ls[j] != options->ls[j])
    return 0;
    if (cloogoptions->fs[j] != options->fs[j])
    return 0;
  }

  if ((cloogoptions->stop_set != options->stop_set)
      || (cloogoptions->stop != options->stop))
    return 0;
  if ((cloogoptions->strides_set != options->strides_set)
      || (cloogoptions->strides != options->strides))
    return 0;
  if ((cloogoptions->sh_set != options->sh_set)
      || (cloogoptions->sh != options->sh))
    return 0;
  if ((cloogoptions->first_unroll_set != options->first_unroll_set)
      || (cloogoptions->first_unroll != options->first_unroll))
    return 0;

  if ((cloogoptions->name_set != options->name_set)
      || (strcmp(cloogoptions->name, options->name)))
      return 0;
  /* OPTIONS FOR PRETTY PRINTING */
  if ((cloogoptions->esp_set != options->esp_set)
      || (cloogoptions->esp != options->esp))
    return 0;
  if ((cloogoptions->fsp_set != options->fsp_set)
      || (cloogoptions->fsp != options->fsp))
    return 0;
  if ((cloogoptions->otl_set != options->otl_set)
      || (cloogoptions->otl != options->otl))
    return 0;
  if ((cloogoptions->block_set != options->block_set)
      || (cloogoptions->block != options->block))
    return 0;
  if ((cloogoptions->compilable_set != options->compilable_set)
      || (cloogoptions->compilable != options->compilable))
    return 0;
  if ((cloogoptions->callable_set != options->callable_set)
      || (cloogoptions->callable != options->callable))
    return 0;
  if ((cloogoptions->quiet_set != options->quiet_set)
      || (cloogoptions->quiet != options->quiet))
    return 0;
  if ((cloogoptions->save_domains_set != options->save_domains_set)
      || (cloogoptions->save_domains != options->save_domains))
    return 0;
  /* MISC OPTIONS */
  if ((cloogoptions->language_set != options->language_set)
      || (cloogoptions->language != options->language))
    return 0;
  if ((cloogoptions->openscop_set != options->openscop_set)
      || (cloogoptions->openscop != options->openscop))
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

