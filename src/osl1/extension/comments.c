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


#include <stdlib.h>

#include "../../include/osl1/extension/comments.h"
#include "../../include/osl1/input.h"


// Create & destroy

/**
 * \brief Return a new osl1_extension_comments_t
 * \return a new osl1_extension_comments_t
 */
osl1_extension_comments_t osl1_extension_comments_create() {
  osl1_extension_comments_t comments;
  comments.comments = gho_vector_string_create();
  return comments;
}

/**
 * \brief Destroy an osl1_extension_comments_t
 * \param[in] comments An osl1_extension_comments_t
 */
void osl1_extension_comments_destroy(osl1_extension_comments_t* comments) {
  gho_vector_string_destroy(&comments->comments);
}

/**
 * \brief Reset an osl1_extension_comments_t
 * \param[in] comments An osl1_extension_comments_t
 */
void osl1_extension_comments_reset(osl1_extension_comments_t* comments) {
  osl1_extension_comments_destroy(comments);
  *comments = osl1_extension_comments_create();
}

// Output

/**
 * \brief Print an osl1_extension_comments_t in a file with indentation
 * \param[in] file     A C file
 * \param[in] comments An osl1_extension_comments_t
 * \param[in] indent   Indentation (number of spaces)
 */
void osl1_extension_comments_fprinti(FILE* file,
                                const osl1_extension_comments_t* const comments,
                                const unsigned int indent) {
  gho_c_str_fprinti(file, "<comments>\n", indent);
  
  gho_c_str_fprinti(file, "# First comments of the source code\n", indent + 4);
  for (size_t i = 0; i < comments->comments.size; ++i) {
    gho_fprinti(file, indent + 4);
    gho_string_fprint(file, &comments->comments.array[i]);
    gho_c_str_fprint(file, "\n");
  }
  
  gho_c_str_fprinti(file, "</comments>", indent);
}

/**
 * \brief Print an osl1_extension_comments_t in a file
 * \param[in] file A C file
 * \param[in] comments An osl1_extension_comments_t
 */
void osl1_extension_comments_fprint(FILE* file,
                              const osl1_extension_comments_t* const comments) {
  osl1_extension_comments_fprinti(file, comments, 0);
}

/**
 * \brief Print an osl1_extension_comments_t in stdout
 * \param[in] comments An osl1_extension_comments_t
 */
void osl1_extension_comments_print(
                              const osl1_extension_comments_t* const comments) {
  osl1_extension_comments_fprint(stdout, comments);
}

/**
 * \brief Print an osl1_extension_comments_t in a C string with indentation
 * \param[in] c_str    A C string
 * \param[in] comments An osl1_extension_comments_t
 * \param[in] indent   Indentation (number of spaces)
 */
void osl1_extension_comments_sprinti(char** c_str,
                                const osl1_extension_comments_t* const comments,
                                const unsigned int indent) {
  gho_c_str_sprinti(c_str, "<comments>\n", indent);
  
  gho_c_str_sprinti(c_str, "# First comments of the source code\n", indent + 4);
  for (size_t i = 0; i < comments->comments.size; ++i) {
    gho_sprinti(c_str, indent + 4);
    gho_string_sprint(c_str, &comments->comments.array[i]);
    gho_c_str_sprint(c_str, "\n");
  }
  
  gho_c_str_sprinti(c_str, "</comments>", indent);
}

/**
 * \brief Print an osl1_extension_comments_t in a C string
 * \param[in] c_str    A C string
 * \param[in] comments An osl1_extension_comments_t
 */
void osl1_extension_comments_sprint(char** c_str,
                              const osl1_extension_comments_t* const comments) {
  osl1_extension_comments_sprinti(c_str, comments, 0);
}

// Input

/**
 * \brief Read an osl1_extension_comments_t from a file
 * \param[in] file A C file
 * \return the osl1_extension_comments_t read
 */
osl1_extension_comments_t osl1_extension_comments_fread(FILE* file) {
  osl1_skip_comments(file);
  osl1_extension_comments_t r = osl1_extension_comments_create();
  
  // TODO
  
//   int nb_iterator = gho_int_fread(file);
//   osl1_skip_comments(file);
//   
//   if (nb_iterator > 0) {
//     for (size_t i = 0; i < (size_t)nb_iterator; ++i) {
//       gho_string_t iterator = gho_string_fread(file);
//       gho_vector_string_add(&r.original_iterators, &iterator);
//       gho_string_destroy(&iterator);
//     }
//   }
//   osl1_skip_comments(file);
//   
//   gho_string_t expression = gho_string_get_line(file);
//   gho_string_add(&r.expression, &expression);
//   gho_string_destroy(&expression);
//   osl1_skip_comments(file);
  
  // TODO accesses
  //fprintf(stderr, "TODO: osl1_extension_comments_fread IS NOT FULLY IMPLEMENTED!\n");
  
  return r;
}

/**
 * \brief Read an osl1_extension_comments_t from a C string
 * \param[in] c_str A C string
 * \return the osl1_extension_comments_t read
 */
osl1_extension_comments_t osl1_extension_comments_sread(const char** c_str) {
  osl1_skip_comments_from_c_str(c_str);
  osl1_extension_comments_t r = osl1_extension_comments_create();
  
  // TODO
  
  return r;
}

// Copy & comparisons

/**
 * \brief Copy an osl1_extension_comments_t
 * \param[in] comments An osl1_extension_comments_t
 * \return the osl1_extension_comments_t copied
 */
osl1_extension_comments_t osl1_extension_comments_copy(
                              const osl1_extension_comments_t* const comments) {
  osl1_extension_comments_t r;
  osl1_extension_comments_copy_(comments, &r);
  return r;
}

/**
 * \brief Copy an osl1_extension_comments_t
 * \param[in] comments An osl1_extension_comments_t
 * \param[in] copy     A pointer on an not initialized osl1_extension_comments_t
 * \warning Do not use this function, use osl1_extension_comments_copy
 */
void osl1_extension_comments_copy_(
                                const osl1_extension_comments_t* const comments,
                                osl1_extension_comments_t* copy) {
  copy->comments = gho_vector_string_copy(&comments->comments);
}

/**
 * \brief Equality between two osl1_extension_comments_t
 * \param[in] a An osl1_extension_comments_t
 * \param[in] b An osl1_extension_comments_t
 * \return true if the osl1_extension_comments_t are equals, false otherwise
 */
bool osl1_extension_comments_equal(const osl1_extension_comments_t* const a,
                                   const osl1_extension_comments_t* const b) {
  return gho_vector_string_equal(&a->comments, &b->comments);
}

// Conversion

/**
 * \brief Convert an osl1_extension_comments_t into a gho_string
 * \param[in] comments An osl1_extension_comments_t
 * \return the gho_string from the osl1_extension_comments_t
 */
gho_string_t osl1_extension_comments_to_string(
                              const osl1_extension_comments_t* const comments) {
  gho_string_t r = gho_string_create();
  osl1_extension_comments_sprint(&r.c_str, comments);
  return r;
}

/**
 * \brief Convert an osl1_extension_comments_t into a gho_any
 * \param[in] comments An osl1_extension_comments_t
 * \return the gho_any from the osl1_extension_comments_t
 */
gho_any_t osl1_extension_comments_to_any(
                              const osl1_extension_comments_t* const comments) {
  gho_any_t r = gho_any_create();
  r.type = GHO_TYPE_OSL_EXTENSION_COMMENTS;
  r.size_of_struct = sizeof(osl1_extension_comments_t);
  osl1_extension_comments_t* p = gho_alloc(osl1_extension_comments_t);
  osl1_extension_comments_copy_(comments, p);
  r.any = p; p = NULL;
  r.destroy_fct = (gho_destroy_fct_t)osl1_extension_comments_destroy;
  r.fprinti_fct = (gho_fprinti_fct_t)osl1_extension_comments_fprinti;
  r.sprinti_fct = (gho_sprinti_fct_t)osl1_extension_comments_sprinti;
  r.copy_fct = (gho_copy_fct_t)osl1_extension_comments_copy_;
  r.equal_fct = (gho_equal_fct_t)osl1_extension_comments_equal;
  r.to_string_fct = (gho_to_string_fct_t)osl1_extension_comments_to_string;
  return r;
}

// Extract

/**
 * \brief Extract comment lines from a C file
 * \param[in] comments   An osl1_extension_comments_t
 * \param[in] file       A C file
 * \param[in] line_start Line where comments start
 * \warning Thing on the line after a multiple line end mark are ignored
 * \return the comments extracted
 */
osl1_extension_comments_t osl1_extension_comments_extract(FILE* file,
                                                      const size_t line_start) {
  osl1_extension_comments_t r = osl1_extension_comments_create();
  
  for (size_t i = 0; i < line_start - 1; ++i) {
    gho_string_ignore_line(file);
  }
  
  bool empty_line = true;
  bool is_comment = false;
  bool is_multi_line_comment = false;
  while (empty_line || is_comment || is_multi_line_comment) {
    if (is_multi_line_comment == false) { gho_read_whitespace(file); }
    gho_string_t line = gho_string_peek_line(file);
    size_t size = gho_string_size(&line);
    if (size != 0) {
      empty_line = false;
      // Is comment?
      if (size < 2) { is_comment = false; }
      else if (line.c_str[0] == '/' && line.c_str[1] == '/') {
        is_comment = true;
        gho_string_remove_until(&line, 2);
        if (size > 1 && line.c_str[0] == ' ') {
          gho_string_remove(&line, 0);
        }
        size = gho_string_size(&line);
      }
      else if (line.c_str[0] == '/' && line.c_str[1] == '*') {
        is_multi_line_comment = true;
        gho_string_remove_until(&line, 2);
        if (size > 1 && line.c_str[0] == ' ') {
          gho_string_remove(&line, 0);
        }
        size = gho_string_size(&line);
      }
      else { is_comment = false; }
      // Get comment
      if (is_comment) {
        gho_vector_string_add(&r.comments, &line);
      }
      if (is_multi_line_comment) {
        const size_t end = gho_string_find_c_str(&line, "*/");
        if (end != size) {
          is_multi_line_comment = false;
          empty_line = true;
          gho_string_remove_after(&line, end);
        }
        gho_vector_string_add(&r.comments, &line);
      }
    }
    else {
      empty_line = true;
    }
    
    gho_string_ignore_line(file);
    gho_string_destroy(&line);
  }
  
  return r;
}
