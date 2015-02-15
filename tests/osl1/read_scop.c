// Copyright © 2015 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include <stdio.h>
#include <stdlib.h>

#include <osl1/scop.h>
#include <gho/test.h>


int main(int argc, char** argv) {
  
  printf("\n");
  
  if (argc <= 1 || argc > 2) {
    printf("Usage: %s <file.scop>\n", argv[0]);
    printf("\n");
    return 1;
  }
  
  int nb_fail = 0;
  
  // SCoP file
  const char* const filename = argv[1];
  FILE* file = fopen(filename, "r");
  
  // File is open
  ++nb_fail;
  if (file) {
    // Read file
    osl1_scop_t scop = osl1_scop_fread(file);
    
    // Print
    osl1_scop_fprinti_openscop(stdout, &scop, 0);
    printf("\n\n");
    
    // Print in string
    gho_string_t scop_string = osl1_scop_to_string(&scop);
    
    // Read from string
    const char* scop_string_c_str = scop_string.c_str;
    osl1_scop_t scop_from_string = osl1_scop_sread(&scop_string_c_str);
    
    // Print
    osl1_scop_fprinti_openscop(stdout, &scop_from_string, 0);
    printf("\n\n");
    
    // Test
    nb_fail -= gho_test(osl1_scop_equal(&scop, &scop_from_string),
                        "read_scop fails!\n");
    
    // Destroy
    osl1_scop_destroy(&scop);
    gho_string_destroy(&scop_string);
    osl1_scop_destroy(&scop_from_string);
  }
  
  // Close file
  fclose(file);
  
  printf("%s ", argv[0]);
  printf("fails = %d\n", nb_fail);
  printf("\n");
  
  return nb_fail;
}
