
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                            test.c                               **
     **-----------------------------------------------------------------**
     **                   First version: 01/10/2010                     **
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
 * Louis-Noel Pouchet <Louis-Noel.Pouchet@inria.fr>                          *
 *                                                                           *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <openscop/openscop.h>

#define TEST_DIR    "."      // Directory to scan for OpenScop files
#define TEST_SUFFIX ".scop"  // Suffix of OpenScop files


/**
 * test_file function
 * This function tests an onpenscop file. A test has four steps:
 * 1. read the file to raise the data up to OpenScop data structures,
 * 2. dump the data structures to a new OpenScop file,
 * 3. read the generated file,
 * 4. compare the data structures.
 * If everything went well, the data structure of the two scops are the same.
 * \param input_name The name of the input file.
 * \param verbose    Verbose option (1 to set, 0 not to set).
 * \return 1 if the test is successful, 0 otherwise.
 */
int test_file(char * input_name, int verbose)
{
  int success = 0;
  int failure = 0;
  int equal;
  char * output_name;
  FILE * input_file, * output_file;
  openscop_scop_p input_scop;
  openscop_scop_p output_scop;

  printf("Testing file %20s... ", input_name); 
    
  // Raise the OpenScop file format to OpenScop data structures.
  input_file = fopen(input_name, "r");
  if (input_file == NULL)
  {
    fflush(stdout);
    fprintf(stderr, "\nError: unable to open file %s\n", input_name);
    exit(2);
  }
  input_scop = openscop_scop_read(input_file);
  fclose(input_file);
  
  // Dump the OpenScop data structures to OpenScop file format.
  output_name = tmpnam(NULL);
  output_file = fopen(output_name, "w");
  openscop_scop_print_openscop(output_file, input_scop);
  fclose(output_file);

  // Raise the generated file to data structures.
  output_file = fopen(output_name, "r");
  output_scop = openscop_scop_read(output_file);
  //output_scop = openscop_scop_copy(output_scop);
  fclose(output_file);

  if (verbose)
  {
    printf("\n\n*************************************************\n\n");
    openscop_scop_print(stdout, output_scop);
    openscop_scop_print_openscop(stdout, output_scop);
    printf("\n*************************************************\n\n");
  }

  // Compare the two scops.
  if (equal = openscop_scop_equal(input_scop, output_scop))
    printf("Success :-)\n");
  else
    printf("Failure :-(\n");

  // Save the planet.
  openscop_scop_free(input_scop);
  openscop_scop_free(output_scop);
  remove(output_name);

  return equal;
}


/**
 * OpenScop test program.
 * Usage: openscop_test [-v] [openscop_file]
 * This program scans a directory for openscop files and test each of them.
 * Optionnally the user can provide a file name to check this file only. A
 * verbose option is also provided to output more information during tests.
 */
int main(int argc, char * argv[])
{
  int total   = 0; // Total number of tests.
  int success = 0; // Number of successes.
  int verbose = 0; // 1 if the verbose option is set, 0 otherwise.
  int dirtest = 1; // 1 if we check a whole directory, 0 for a single file.
  int fileidx = 0; // Index of the file to check in argv (0 if none).
  int d_namlen;
  int suffix_length;
  DIR * dir;
  struct dirent * dp;

  // Process the command line information
  if (((argc > 1) && (!strcmp(argv[1], "-v"))) ||
      ((argc > 2) && (!strcmp(argv[2], "-v"))))
    verbose = 1;

  if ((argc > 3) || ((argc == 3) && (!verbose)))
  {
    fprintf(stderr, "usage: openscop_test [-v] [openscop_file]\n");
    exit(1); 
  }

  if ((argc - verbose) > 1)
  {
    dirtest = 0;
    fileidx = (!strcmp(argv[1], "-v")) ? 2 : 1;
  }

  // Proceed with the test(s), either directory or single file
  if (dirtest)
  {
    suffix_length = strlen(TEST_SUFFIX);
    
    // For each file in the directory to check...
    dir = opendir(TEST_DIR);
    while ((dp = readdir(dir)) != NULL)
    {
      d_namlen = strlen(dp->d_name);
      // If the file has the convenient suffix...
      if ((d_namlen > suffix_length) &&
          (!strcmp(dp->d_name+(d_namlen-suffix_length), TEST_SUFFIX)))
      {
        // Test it !
        success += test_file(dp->d_name, verbose);
        total++;
      }
    }
    closedir(dir);
  }
  else
  {
    success += test_file(argv[fileidx], verbose);
    total++;
  }

  printf("\n  +-----------------------+\n");
  printf("  | OpenScop Test Summary |\n");
  printf("  |-----------------------|\n");
  printf("  | total          %4d   |\n", total);
  printf("  | success(es)    %4d   |\n", success);
  printf("  | failure(s)     %4d   |\n", total - success);
  printf("  +-----------------------+\n\n");

  // Return 0 if all tests were successful, 1 otherwise.
  if (total - success)
    return 1;
  else
    return 0;
}
