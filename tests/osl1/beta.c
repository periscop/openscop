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

#include <osl1/beta_functions.h>
#include <gho/test.h>


int main() {
  
  printf("\n");
  
  int nb_fail = 0;
  
  ++nb_fail;
  {
    osl1_beta_t beta = osl1_beta_create_n(3);
    
    {
      osl1_beta_t beta_prefix = osl1_beta_create_n(1);
      osl1_beta_to_beta_prefix(&beta_prefix);
      
      const bool same_beta_prefix = osl1_same_beta_prefix(&beta, &beta_prefix);
      
      printf("Beta = "); osl1_beta_print(&beta); printf("\n");
      printf("Beta = "); osl1_beta_print(&beta_prefix); printf("\n");
      printf("osl1_same_beta_prefix = %s\n", same_beta_prefix ? "true" : "false");
      
      osl1_beta_destroy(&beta_prefix);
    }
    printf("\n");
    
    {
      osl1_beta_t beta_prefix = osl1_beta_create_n(2);
      beta_prefix.array[0] = 1;
      osl1_beta_to_beta_prefix(&beta_prefix);
      
      const bool same_beta_prefix = osl1_same_beta_prefix(&beta, &beta_prefix);
      
      printf("Beta = "); osl1_beta_print(&beta); printf("\n");
      printf("Beta = "); osl1_beta_print(&beta_prefix); printf("\n");
      printf("osl1_same_beta_prefix = %s\n", same_beta_prefix ? "true" : "false");
      
      osl1_beta_destroy(&beta_prefix);
    }
    printf("\n");
    
    {
      osl1_beta_t beta_prefix = osl1_beta_create_n(3);
      osl1_beta_to_beta_prefix(&beta_prefix);
      
      const bool same_beta_prefix = osl1_same_beta_prefix(&beta, &beta_prefix);
      
      printf("Beta = "); osl1_beta_print(&beta); printf("\n");
      printf("Beta = "); osl1_beta_print(&beta_prefix); printf("\n");
      printf("osl1_same_beta_prefix = %s\n", same_beta_prefix ? "true" : "false");
      
      osl1_beta_destroy(&beta_prefix);
    }
    printf("\n");
    
    {
      osl1_beta_t beta_prefix = osl1_beta_create_n(4);
      osl1_beta_to_beta_prefix(&beta_prefix);
      
      const bool same_beta_prefix = osl1_same_beta_prefix(&beta, &beta_prefix);
      
      printf("Beta = "); osl1_beta_print(&beta); printf("\n");
      printf("Beta = "); osl1_beta_print(&beta_prefix); printf("\n");
      printf("osl1_same_beta_prefix = %s\n", same_beta_prefix ? "true" : "false");
      
      osl1_beta_destroy(&beta_prefix);
    }
    printf("\n");
    
    osl1_beta_destroy(&beta);
  }
  
  ++nb_fail;
  {
    FILE* file = fopen("../tests/osl1_scop/matmul.scop", "r");
    if (file == NULL) { file = fopen("./tests/osl1_scop/matmul.scop", "r"); }
    if (file == NULL) { file = fopen("./osl/tests/osl1_scop/matmul.scop", "r"); }
    if (file != NULL) {
      osl1_scop_t scop = osl1_scop_fread(file);
      osl1_vector_beta_t betas = osl1_extract_betas(&scop);
      
      printf("Betas = "); osl1_vector_beta_print(&betas); printf("\n");
      
      // osl1_nb_statement_beta_prefix
      
      {
        osl1_beta_t beta_prefix = osl1_beta_create_n(1);
        osl1_beta_to_beta_prefix(&beta_prefix);
        const size_t nb = osl1_nb_statement_beta_prefix(&scop, &beta_prefix);
        
        printf("Number of statements with this beta prefix (");
        osl1_beta_print(&beta_prefix);
        printf(") = %zu\n", nb);
        
        osl1_beta_to_beta_prefix(&beta_prefix);
      }
      
      {
        osl1_beta_t beta_prefix = osl1_beta_create_n(2);
        osl1_beta_to_beta_prefix(&beta_prefix);
        const size_t nb = osl1_nb_statement_beta_prefix(&scop, &beta_prefix);
        
        printf("Number of statements with this beta prefix (");
        osl1_beta_print(&beta_prefix);
        printf(") = %zu\n", nb);
        
        osl1_beta_to_beta_prefix(&beta_prefix);
      }
      
      {
        osl1_beta_t beta_prefix = osl1_beta_create_n(3);
        osl1_beta_to_beta_prefix(&beta_prefix);
        const size_t nb = osl1_nb_statement_beta_prefix(&scop, &beta_prefix);
        
        printf("Number of statements with this beta prefix (");
        osl1_beta_print(&beta_prefix);
        printf(") = %zu\n", nb);
        
        osl1_beta_to_beta_prefix(&beta_prefix);
      }
      
      {
        osl1_beta_t beta_prefix = osl1_beta_create_n(4);
        beta_prefix.array[3] = 1;
        osl1_beta_to_beta_prefix(&beta_prefix);
        const size_t nb = osl1_nb_statement_beta_prefix(&scop, &beta_prefix);
        
        printf("Number of statements with this beta prefix (");
        osl1_beta_print(&beta_prefix);
        printf(") = %zu\n", nb);
        
        osl1_beta_to_beta_prefix(&beta_prefix);
      }
      
      {
        osl1_beta_t beta_prefix = osl1_beta_create_n(4);
        beta_prefix.array[2] = 1;
        osl1_beta_to_beta_prefix(&beta_prefix);
        const size_t nb = osl1_nb_statement_beta_prefix(&scop, &beta_prefix);
        
        printf("Number of statements with this beta prefix (");
        osl1_beta_print(&beta_prefix);
        printf(") = %zu\n", nb);
        
        osl1_beta_to_beta_prefix(&beta_prefix);
      }
      
      // osl1_nb_statement_in_loop
      
      {
        osl1_beta_t beta_prefix = osl1_beta_create_n(1);
        osl1_beta_to_beta_prefix(&beta_prefix);
        const size_t nb = osl1_nb_statement_in_loop(&scop, &beta_prefix);
        
        printf("Number of statements in this loop (");
        osl1_beta_print(&beta_prefix);
        printf(") = %zu\n", nb);
        
        osl1_beta_to_beta_prefix(&beta_prefix);
      }
      
      {
        osl1_beta_t beta_prefix = osl1_beta_create_n(2);
        osl1_beta_to_beta_prefix(&beta_prefix);
        const size_t nb = osl1_nb_statement_in_loop(&scop, &beta_prefix);
        
        printf("Number of statements in this loop (");
        osl1_beta_print(&beta_prefix);
        printf(") = %zu\n", nb);
        
        osl1_beta_to_beta_prefix(&beta_prefix);
      }
      
      {
        osl1_beta_t beta_prefix = osl1_beta_create_n(3);
        osl1_beta_to_beta_prefix(&beta_prefix);
        const size_t nb = osl1_nb_statement_in_loop(&scop, &beta_prefix);
        
        printf("Number of statements in this loop (");
        osl1_beta_print(&beta_prefix);
        printf(") = %zu\n", nb);
        
        osl1_beta_to_beta_prefix(&beta_prefix);
      }
      
      {
        osl1_beta_t beta_prefix = osl1_beta_create_n(4);
        beta_prefix.array[3] = 1;
        osl1_beta_to_beta_prefix(&beta_prefix);
        const size_t nb = osl1_nb_statement_in_loop(&scop, &beta_prefix);
        
        printf("Number of statements in this loop (");
        osl1_beta_print(&beta_prefix);
        printf(") = %zu\n", nb);
        
        osl1_beta_to_beta_prefix(&beta_prefix);
      }
      
      {
        osl1_beta_t beta_prefix = osl1_beta_create_n(4);
        beta_prefix.array[2] = 1;
        osl1_beta_to_beta_prefix(&beta_prefix);
        const size_t nb = osl1_nb_statement_in_loop(&scop, &beta_prefix);
        
        printf("Number of statements in this loop (");
        osl1_beta_print(&beta_prefix);
        printf(") = %zu\n", nb);
        
        osl1_beta_to_beta_prefix(&beta_prefix);
      }
      
      
      
      
      
      fclose(file);
      osl1_scop_destroy(&scop);
      osl1_vector_beta_destroy(&betas);
    }
  }
  printf("\n");
  
  return nb_fail;
}
