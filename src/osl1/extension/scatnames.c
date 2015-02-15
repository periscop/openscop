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

#include <gho/char.h>

#include "../../include/osl1/extension/scatnames.h"
#include "../../include/osl1/input.h"


// Create & destroy

/**
 * \brief Return a new osl1_extension_scatnames
 * \return a new osl1_extension_scatnames
 */
osl1_extension_scatnames_t osl1_extension_scatnames_create() {
  osl1_extension_scatnames_t scatnames;
  scatnames.scatnames = gho_vector_string_create();
  return scatnames;
}

/**
 * \brief Destroy an osl1_extension_scatnames
 * \param[in] scatnames An osl1_extension_scatnames
 */
void osl1_extension_scatnames_destroy(osl1_extension_scatnames_t* scatnames) {
  gho_vector_string_destroy(&scatnames->scatnames);
}

/**
 * \brief Reset an osl1_extension_scatnames
 * \param[in] scatnames An osl1_extension_scatnames
 */
void osl1_extension_scatnames_reset(osl1_extension_scatnames_t* scatnames) {
  osl1_extension_scatnames_destroy(scatnames);
  *scatnames = osl1_extension_scatnames_create();
}

// Output

/**
 * \brief Print an osl1_extension_scatnames in a file with indentation
 * \param[in] file   A C file
 * \param[in] scatnames   An osl1_extension_scatnames
 * \param[in] indent Indentation (number of spaces)
 */
void osl1_extension_scatnames_fprinti(FILE* file,
                              const osl1_extension_scatnames_t* const scatnames,
                              const unsigned int indent) {
  gho_c_str_fprinti(file, "<scatnames>\n", indent);
  
  gho_fprinti(file, indent + 4);
  for (size_t i = 0; i < scatnames->scatnames.size; ++i) {
    gho_string_fprint(file, &scatnames->scatnames.array[i]);
    gho_c_str_fprint(file, " ");
  }
  gho_c_str_fprint(file, "\n");
  
  gho_c_str_fprinti(file, "</scatnames>", indent);
}

/**
 * \brief Print an osl1_extension_scatnames in a file
 * \param[in] file     A C file
 * \param[in] scatnames An osl1_extension_scatnames
 */
void osl1_extension_scatnames_fprint(FILE* file,
                            const osl1_extension_scatnames_t* const scatnames) {
  osl1_extension_scatnames_fprinti(file, scatnames, 0);
}

/**
 * \brief Print an osl1_extension_scatnames in stdout
 * \param[in] scatnames An osl1_extension_scatnames
 */
void osl1_extension_scatnames_print(
                            const osl1_extension_scatnames_t* const scatnames) {
  osl1_extension_scatnames_fprint(stdout, scatnames);
}

/**
 * \brief Print an osl1_extension_scatnames in a C string with indentation
 * \param[in] c_str  A C string
 * \param[in] scatnames   An osl1_extension_scatnames
 * \param[in] indent Indentation (number of spaces)
 */
void osl1_extension_scatnames_sprinti(char** c_str,
                              const osl1_extension_scatnames_t* const scatnames,
                              const unsigned int indent) {
  gho_c_str_sprinti(c_str, "<scatnames>\n", indent);
  
  gho_sprinti(c_str, indent + 4);
  for (size_t i = 0; i < scatnames->scatnames.size; ++i) {
    gho_string_sprint(c_str, &scatnames->scatnames.array[i]);
    gho_c_str_sprint(c_str, " ");
  }
  gho_c_str_sprint(c_str, "\n");
  
  gho_c_str_sprinti(c_str, "</scatnames>", indent);
}

/**
 * \brief Print an osl1_extension_scatnames in a C string
 * \param[in] c_str A C string
 * \param[in] scatnames  An osl1_extension_scatnames
 */
void osl1_extension_scatnames_sprint(char** c_str,
                               const osl1_extension_scatnames_t* const scatnames) {
  osl1_extension_scatnames_sprinti(c_str, scatnames, 0);
}

// Input

/**
 * \brief Read an osl1_extension_scatnames from a file
 * \param[in] file A C file
 * \return the osl1_extension_scatnames read
 */
osl1_extension_scatnames_t osl1_extension_scatnames_fread(FILE* file) {
  osl1_skip_comments(file);
  osl1_extension_scatnames_t r = osl1_extension_scatnames_create();
  
  gho_string_t scatname = gho_string_create();
  while (true) {
     const char c = gho_char_fread(file);
     if (c == '\n') { break; }
     else if (c == ' ') {
       if (gho_string_size(&scatname) > 0) {
         gho_vector_string_add(&r.scatnames, &scatname);
         gho_string_reset(&scatname);
       }
     }
     else { gho_string_add_char(&scatname, c); }
  }
  if (gho_string_size(&scatname) > 0) {
    gho_vector_string_add(&r.scatnames, &scatname);
  }
  gho_string_destroy(&scatname);
  
  return r;
}

/**
 * \brief Read an osl1_extension_scatnames from a C string
 * \param[in] c_str A C string
 * \return the osl1_extension_scatnames read
 */
osl1_extension_scatnames_t osl1_extension_scatnames_sread(const char** c_str) {
  osl1_skip_comments_from_c_str(c_str);
  osl1_extension_scatnames_t r = osl1_extension_scatnames_create();
  
  gho_string_t scatname = gho_string_create();
  while (true) {
     const char c = gho_char_sread(c_str);
     if (c == '\n') { break; }
     else if (c == ' ') {
       if (gho_string_size(&scatname) > 0) {
         gho_vector_string_add(&r.scatnames, &scatname);
         gho_string_reset(&scatname);
       }
     }
     else { gho_string_add_char(&scatname, c); }
  }
  if (gho_string_size(&scatname) > 0) {
    gho_vector_string_add(&r.scatnames, &scatname);
  }
  gho_string_destroy(&scatname);
  
  return r;
}

// Copy & comparisons

/**
 * \brief Copy an osl1_extension_scatnames
 * \param[in] scatnames An osl1_extension_scatnames
 * \return the osl1_extension_scatnames copied
 */
osl1_extension_scatnames_t osl1_extension_scatnames_copy(
                            const osl1_extension_scatnames_t* const scatnames) {
  osl1_extension_scatnames_t r;
  osl1_extension_scatnames_copy_(scatnames, &r);
  return r;
}

/**
 * \brief Copy an osl1_extension_scatnames
 * \param[in] scatnames An osl1_extension_scatnames
 * \param[in] copy A pointer on an not initialized osl1_extension_scatnames
 * \warning Do not use this function, use osl1_extension_scatnames_copy
 */
void osl1_extension_scatnames_copy_(
                              const osl1_extension_scatnames_t* const scatnames,
                              osl1_extension_scatnames_t* copy) {
  copy->scatnames = gho_vector_string_copy(&scatnames->scatnames);
}

/**
 * \brief Equality between two osl1_extension_scatnames
 * \param[in] a An osl1_extension_scatnames
 * \param[in] b An osl1_extension_scatnames
 * \return true if the osl1_extension_scatnames are equals, false otherwise
 */
bool osl1_extension_scatnames_equal(const osl1_extension_scatnames_t* const a,
                              const osl1_extension_scatnames_t* const b) {
  return gho_vector_string_equal(&a->scatnames, &b->scatnames);
}

// Conversion

/**
 * \brief Convert an osl1_extension_scatnames into a gho_string
 * \param[in] scatnames An osl1_extension_scatnames
 * \return the gho_string from the osl1_extension_scatnames
 */
gho_string_t osl1_extension_scatnames_to_string(
                            const osl1_extension_scatnames_t* const scatnames) {
  gho_string_t r = gho_string_create();
  osl1_extension_scatnames_sprint(&r.c_str, scatnames);
  return r;
}

/**
 * \brief Convert an osl1_extension_scatnames into a gho_any
 * \param[in] scatnames An osl1_extension_scatnames
 * \return the gho_any from the osl1_extension_scatnames
 */
gho_any_t osl1_extension_scatnames_to_any(
                            const osl1_extension_scatnames_t* const scatnames) {
  gho_any_t r = gho_any_create();
  r.type = GHO_TYPE_OSL_EXTENSION_SCATNAMES;
  r.size_of_struct = sizeof(osl1_extension_scatnames_t);
  osl1_extension_scatnames_t* p = gho_alloc(osl1_extension_scatnames_t);
  osl1_extension_scatnames_copy_(scatnames, p);
  r.any = p; p = NULL;
  r.destroy_fct = (gho_destroy_fct_t)osl1_extension_scatnames_destroy;
  r.fprinti_fct = (gho_fprinti_fct_t)osl1_extension_scatnames_fprinti;
  r.sprinti_fct = (gho_sprinti_fct_t)osl1_extension_scatnames_sprinti;
  r.copy_fct = (gho_copy_fct_t)osl1_extension_scatnames_copy_;
  r.equal_fct = (gho_equal_fct_t)osl1_extension_scatnames_equal;
  r.to_string_fct = (gho_to_string_fct_t)osl1_extension_scatnames_to_string;
  return r;
}
