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


#include "../input.h"


// Input

/**
 * \brief Read an OpenScop extensions (gho_vector_any_t) from a file
 * \param[in] file A C file
 * \return the OpenScop extensions (gho_vector_any_t) read
 */
gho_vector_any_t osl1_extensions_fread(FILE* file) {
  gho_vector_any_t r = gho_vector_any_create();
  
  const size_t nb = gho_size_t_fread(file);
  osl1_skip_comments(file);
  
  for (size_t i = 0; i < nb; ++i) {
    // Read mark
    gho_string_t mark = gho_string_fread(file);
    // Read extension
    gho_any_t extension = osl1_extension_fread_with_mark(file, &mark);
    osl1_skip_comments(file);
    gho_vector_any_add(&r, &extension);
    gho_any_destroy(&extension);
    // Read end mark
    gho_string_t end_mark = gho_string_fread(file);
    osl1_skip_comments(file);
    // Destroy
    gho_string_destroy(&mark);
    gho_string_destroy(&end_mark);
  }
  
  return r;
}

/**
 * \brief Read an OpenScop extensions (gho_vector_any_t) from a C string
 * \param[in] c_str A C string
 * \return the OpenScop extensions (gho_vector_any_t) read
 */
gho_vector_any_t osl1_extensions_sread(const char** c_str) {
  gho_vector_any_t r = gho_vector_any_create();
  
  const size_t nb = gho_size_t_sread(c_str);
  osl1_skip_comments_from_c_str(c_str);
  
  for (size_t i = 0; i < nb; ++i) {
    // Read mark
    gho_string_t mark = gho_string_sread(c_str);
    // Read extension
    gho_any_t extension = osl1_extension_sread_with_mark(c_str, &mark);
    osl1_skip_comments_from_c_str(c_str);
    gho_vector_any_add(&r, &extension);
    gho_any_destroy(&extension);
    // Read end mark
    gho_string_t end_mark = gho_string_sread(c_str);
    osl1_skip_comments_from_c_str(c_str);
    // Destroy
    gho_string_destroy(&mark);
    gho_string_destroy(&end_mark);
  }
  
  return r;
}

/**
 * \brief Read an OpenScop extension (gho_any) from a file
 * \param[in] file A C file
 * \param[in] mark Mark (e.g. <extension_name>)
 * \return the OpenScop extension (gho_any) read
 */
gho_any_t osl1_extension_fread_with_mark(FILE* file,
                                         const gho_string_t* const mark) {
  // body
  if (gho_c_str_equal(mark->c_str, "<body>")) {
    osl1_extension_body_t extension = osl1_extension_body_fread(file);
    gho_any_t r = osl1_extension_body_to_any(&extension);
    osl1_extension_body_destroy(&extension);
    return r;
  }
  
  // comments
  if (gho_c_str_equal(mark->c_str, "<comments>")) {
    osl1_extension_comments_t extension = osl1_extension_comments_fread(file);
    gho_any_t r = osl1_extension_comments_to_any(&extension);
    osl1_extension_comments_destroy(&extension);
    return r;
  }

//   // coordinates
//   if (gho_c_str_equal(mark->c_str, "<coordinates>")) {
//     osl1_extension_coordinates_t extension = osl1_extension_coordinates_fread(file);
//     gho_any_t r = osl1_extension_coordinates_to_any(&extension);
//     osl1_extension_coordinates_destroy(&extension);
//     return r;
//   }

  // scatnames
  if (gho_c_str_equal(mark->c_str, "<scatnames>")) {
    osl1_extension_scatnames_t extension = osl1_extension_scatnames_fread(file);
    gho_any_t r = osl1_extension_scatnames_to_any(&extension);
    osl1_extension_scatnames_destroy(&extension);
    return r;
  }

  // unknown
  {
    gho_c_str_ignore_line(file);
    osl1_extension_unknown_t extension =
      osl1_extension_unknown_fread_with_mark(file, mark);
    gho_any_t r = osl1_extension_unknown_to_any(&extension);
    osl1_extension_unknown_destroy(&extension);
    return r;
  }
}

/**
 * \brief Read an OpenScop extension (gho_any) from a C string
 * \param[in] c_str A C string
 * \param[in] mark Mark (e.g. <extension_name>)
 * \return the OpenScop extension (gho_any) read
 */
gho_any_t osl1_extension_sread_with_mark(const char** c_str,
                                         const gho_string_t* const mark) {
  // body
  if (gho_c_str_equal(mark->c_str, "<body>")) {
    osl1_extension_body_t extension = osl1_extension_body_sread(c_str);
    gho_any_t r = osl1_extension_body_to_any(&extension);
    osl1_extension_body_destroy(&extension);
    return r;
  }
  
  // comments
  if (gho_c_str_equal(mark->c_str, "<comments>")) {
    osl1_extension_comments_t extension = osl1_extension_comments_sread(c_str);
    gho_any_t r = osl1_extension_comments_to_any(&extension);
    osl1_extension_comments_destroy(&extension);
    return r;
  }

  // scatnames
  if (gho_c_str_equal(mark->c_str, "<scatnames>")) {
    osl1_extension_scatnames_t extension = osl1_extension_scatnames_sread(c_str);
    gho_any_t r = osl1_extension_scatnames_to_any(&extension);
    osl1_extension_scatnames_destroy(&extension);
    return r;
  }
  
  // unknown
  {
    gho_c_str_ignore_line_from_c_str(c_str);
    osl1_extension_unknown_t extension =
      osl1_extension_unknown_sread_with_mark(c_str, mark);
    gho_any_t r = osl1_extension_unknown_to_any(&extension);
    osl1_extension_unknown_destroy(&extension);
    return r;
  }
}
