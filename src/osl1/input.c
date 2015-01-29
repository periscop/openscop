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


#include <stdlib.h>

#include "../include/osl1/input.h"
#include "../include/gho/input.h"
#include "../include/gho/char.h"


/**
 * @brief Ignore an OpenScop comment from a file
 * @param[in] file A C file
 */
void osl1_skip_comments(FILE* file) {
  gho_read_whitespace(file);
  while (gho_char_fpeek(file) == '#') {
    gho_string_ignore_line(file);
    gho_read_whitespace(file);
  }
}

/**
 * @brief Ignore an OpenScop comment from a C string
 * @param[in] c_str A C string
 */
void osl1_skip_comments_from_c_str(const char** c_str) {
  gho_read_whitespace_from_c_str(c_str);
  while (gho_char_speek(c_str) == '#') {
    gho_string_ignore_line_from_c_str(c_str);
    gho_read_whitespace_from_c_str(c_str);
  }
}
