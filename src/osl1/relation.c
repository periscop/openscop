// Copyright © 2014-2015 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr

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


#include <gho/int/size_t.h>

#include "../include/osl1/relation.h"
#include "../include/osl1/input.h"


// Input

/**
 * \brief Read an osl1_relation_t from a file in OpenScop format
 * \param[in] file A C file
 * \return the osl1_relation_t read
 */
osl1_relation_t osl1_relation_fread(FILE* file) {
  
  osl1_relation_t relation = osl1_relation_create();
  
  osl1_skip_comments(file);
  const size_t nb_convex_relation = gho_size_t_fread(file);
  osl1_skip_comments(file);
  
  for (size_t i = 0; i < nb_convex_relation; ++i) {
    osl1_convex_relation_t convex_relation = osl1_convex_relation_fread(file);
    osl1_relation_add(&relation, &convex_relation);
    osl1_convex_relation_destroy(&convex_relation);
    osl1_skip_comments(file);
  }
  
  return relation;
}

/**
 * \brief Read an osl1_relation_t from a C string in OpenScop format
 * \param[in] c_str A C string
 * \return the osl1_relation_t read
 */
osl1_relation_t osl1_relation_sread(const char** c_str) {
  
  osl1_relation_t relation = osl1_relation_create();
  
  osl1_skip_comments_from_c_str(c_str);
  const size_t nb_convex_relation = gho_size_t_sread(c_str);
  osl1_skip_comments_from_c_str(c_str);
  
  for (size_t i = 0; i < nb_convex_relation; ++i) {
    osl1_convex_relation_t convex_relation = osl1_convex_relation_sread(c_str);
    osl1_relation_add(&relation, &convex_relation);
    osl1_convex_relation_destroy(&convex_relation);
    osl1_skip_comments_from_c_str(c_str);
  }
  
  return relation;
}
