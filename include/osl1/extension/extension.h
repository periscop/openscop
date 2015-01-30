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


#ifndef OSL1_EXTENSION_EXTENSION_H
#define OSL1_EXTENSION_EXTENSION_H


// Input

/**
 * \brief Read an OpenScop extension (gho_any) from a file
 * \param[in] file A C file
 * \param[in] mark Mark (e.g. <extension_name>)
 * \return the OpenScop extension (gho_any) read
 */
gho_any_t osl1_extension_fread_with_mark(FILE* file,
                                         const gho_string_t* const mark) {
//   // body
//   if (osl1_c_str_equal(mark->c_str, "<body>")) {
//     osl1_extension_body_t extension = osl1_extension_body_fread(file);
//     gho_any_t r = osl1_extension_body_to_any(&extension);
//     osl1_extension_body_destroy(&extension);
//     return r;
//   }

//   // coordinates
//   if (osl1_c_str_equal(mark->c_str, "<coordinates>")) {
//     osl1_extension_coordinates_t extension = osl1_extension_coordinates_fread(file);
//     gho_any_t r = osl1_extension_coordinates_to_any(&extension);
//     osl1_extension_coordinates_destroy(&extension);
//     return r;
//   }

//   // scatnames
//   if (osl1_c_str_equal(mark->c_str, "<scatnames>")) {
//     osl1_extension_scatnames_t extension = osl1_extension_scatnames_fread(file);
//     gho_any_t r = osl1_extension_scatnames_to_any(&extension);
//     osl1_extension_scatnames_destroy(&extension);
//     return r;
//   }

  // unknown
  {
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
  // unknown
  {
    osl1_extension_unknown_t extension =
      osl1_extension_unknown_sread_with_mark(c_str, mark);
    gho_any_t r = osl1_extension_unknown_to_any(&extension);
    osl1_extension_unknown_destroy(&extension);
    return r;
  }
}

#endif
