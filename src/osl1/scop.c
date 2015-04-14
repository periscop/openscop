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

#include "../include/osl1/scop.h"


// Create & destroy

/**
 * \brief Return a new osl1_scop
 * \return a new osl1_scop
 */
osl1_scop_t osl1_scop_create() {
  osl1_scop_t scop;
  scop.context = osl1_relation_create();
  scop.parameters = gho_vector_string_create();
  scop.statements = osl1_vector_statement_create();
  scop.extensions = gho_vector_any_create();
  return scop;
}

/**
 * \brief Destroy an osl1_scop
 * \param[in] scop An osl1_scop
 */
void osl1_scop_destroy(osl1_scop_t* scop) {
  osl1_relation_destroy(&scop->context);
  gho_vector_string_destroy(&scop->parameters);
  osl1_vector_statement_destroy(&scop->statements);
  gho_vector_any_destroy(&scop->extensions);
}

/**
 * \brief Reset an osl1_scop
 * \param[in] scop An osl1_scop
 */
void osl1_scop_reset(osl1_scop_t* scop) {
  osl1_scop_destroy(scop);
  *scop = osl1_scop_create();
}

// Output

/**
 * \brief Print an osl1_scop in a file with indentation
 * \param[in] file   A C file
 * \param[in] scop   An osl1_scop
 * \param[in] indent Indentation (number of spaces)
 */
void osl1_scop_fprinti(FILE* file, const osl1_scop_t* const scop,
                       const unsigned int indent) {
  osl1_scop_fprinti_openscop(file, scop, indent);
}

/**
 * \brief Print an osl1_scop in a file
 * \param[in] file A C file
 * \param[in] scop An osl1_scop
 */
void osl1_scop_fprint(FILE* file, const osl1_scop_t* const scop) {
  osl1_scop_fprinti(file, scop, 0);
}

/**
 * \brief Print an osl1_scop in stdout
 * \param[in] scop An osl1_scop
 */
void osl1_scop_print(const osl1_scop_t* const scop) {
  osl1_scop_fprint(stdout, scop);
}

/**
 * \brief Print an osl1_scop in a C string with indentation
 * \param[in] c_str  A C string
 * \param[in] scop   An osl1_scop
 * \param[in] indent Indentation (number of spaces)
 */
void osl1_scop_sprinti(char** c_str, const osl1_scop_t* const scop,
                       const unsigned int indent) {
  osl1_scop_sprinti_openscop(c_str, scop, indent);
}

/**
 * \brief Print an osl1_scop in a C string
 * \param[in] c_str A C string
 * \param[in] scop  An osl1_scop
 */
void osl1_scop_sprint(char** c_str, const osl1_scop_t* const scop) {
  osl1_scop_sprinti(c_str, scop, 0);
}

// Input

/**
 * \brief Read an osl1_scop from a file
 * \param[in] file A C file
 * \return the osl1_scop read
 */
osl1_scop_t osl1_scop_fread(FILE* file) {
  
  osl1_scop_t scop = osl1_scop_create();
  
  // Comment
  osl1_skip_comments(file);
  
  // <OpenScop1>
  {
    gho_string_t s = gho_string_fread(file);
    if (gho_string_equal_c_str(&s, "<OpenScop1>") == false) {
      fprintf(stderr, "ERROR: osl1_scop_fread "
                      "can read OpenScop1 format only.\n");
      fprintf(stderr, "       read = ");
      gho_string_fprint(stderr, &s);
      fprintf(stderr, "\n");
      gho_string_destroy(&s);
      return scop;
    }
    gho_string_destroy(&s);
  }
  osl1_skip_comments(file);
  
  // Context
  osl1_relation_destroy(&scop.context);
  scop.context = osl1_relation_fread(file);
  
  // Parameters
  const size_t nb_parameters = gho_size_t_fread(file);
  osl1_skip_comments(file);
  for (size_t i = 0; i < nb_parameters; ++i) {
    gho_string_t parameter = gho_string_fread(file);
    gho_vector_string_add(&scop.parameters, &parameter);
    gho_string_destroy(&parameter);
    osl1_skip_comments(file);
  }
  
  // Statements
  osl1_vector_statement_destroy(&scop.statements);
  scop.statements = osl1_vector_statement_fread(file);
  
  // Extensions
  gho_vector_any_destroy(&scop.extensions);
  scop.extensions = osl1_extensions_fread(file);
  
  // </OpenScop1>
  {
    gho_string_t s = gho_string_fread(file);
    if (gho_string_equal_c_str(&s, "</OpenScop1>") == false) {
      fprintf(stderr, "ERROR: osl1_scop_fread "
                      "did not read </OpenScop1> like expected.\n");
      fprintf(stderr, "       read = ");
      gho_string_fprint(stderr, &s);
      fprintf(stderr, "\n");
    }
    gho_string_destroy(&s);
  }
  
  return scop;
}

/**
 * \brief Read an osl1_scop from a C string
 * \param[in] c_str A C string
 * \return the osl1_scop read
 */
osl1_scop_t osl1_scop_sread(const char** c_str) {
  
  osl1_scop_t scop = osl1_scop_create();
  
  // Comment
  osl1_skip_comments_from_c_str(c_str);
  
  // <OpenScop1>
  {
    gho_string_t s = gho_string_sread(c_str);
    if (gho_string_equal_c_str(&s, "<OpenScop1>") == false) {
      fprintf(stderr, "ERROR: osl1_scop_sread "
                      "can read OpenScop1 format only.\n");
      fprintf(stderr, "       read = ");
      gho_string_fprint(stderr, &s);
      fprintf(stderr, "\n");
      gho_string_destroy(&s);
      return scop;
    }
    gho_string_destroy(&s);
  }
  osl1_skip_comments_from_c_str(c_str);
  
  // Context
  osl1_relation_destroy(&scop.context);
  scop.context = osl1_relation_sread(c_str);
  
  // Parameters
  const size_t nb_parameters = gho_size_t_sread(c_str);
  osl1_skip_comments_from_c_str(c_str);
  for (size_t i = 0; i < nb_parameters; ++i) {
    gho_string_t parameter = gho_string_sread(c_str);
    gho_vector_string_add(&scop.parameters, &parameter);
    gho_string_destroy(&parameter);
    osl1_skip_comments_from_c_str(c_str);
  }
  
  // Statements
  osl1_vector_statement_destroy(&scop.statements);
  scop.statements = osl1_vector_statement_sread(c_str);
  
  // Extensions
  gho_vector_any_destroy(&scop.extensions);
  scop.extensions = osl1_extensions_sread(c_str);
  
  // </OpenScop1>
  {
    gho_string_t s = gho_string_sread(c_str);
    if (gho_string_equal_c_str(&s, "</OpenScop1>") == false) {
      fprintf(stderr, "ERROR: osl1_scop_sread "
                      "did not read </OpenScop1> like expected.\n");
      fprintf(stderr, "       read = ");
      gho_string_fprint(stderr, &s);
      fprintf(stderr, "\n");
    }
    gho_string_destroy(&s);
  }
  
  return scop;
}

// Copy & comparisons

/**
 * \brief Copy an osl1_scop
 * \param[in] scop An osl1_scop
 * \return the osl1_scop copied
 */
osl1_scop_t osl1_scop_copy(const osl1_scop_t* const scop) {
  osl1_scop_t r;
  osl1_scop_copy_(scop, &r);
  return r;
}

/**
 * \brief Copy an osl1_scop
 * \param[in] scop An osl1_scop
 * \param[in] copy A pointer on an not initialized osl1_scop
 * \warning Do not use this function, use osl1_scop_copy
 */
void osl1_scop_copy_(const osl1_scop_t* const scop, osl1_scop_t* copy) {
  copy->context = osl1_relation_copy(&scop->context);
  copy->parameters = gho_vector_string_copy(&scop->parameters);
  copy->statements = osl1_vector_statement_copy(&scop->statements);
  copy->extensions = gho_vector_any_copy(&scop->extensions);
}

/**
 * \brief Equality between two osl1_scop
 * \param[in] a An osl1_scop
 * \param[in] b An osl1_scop
 * \return true if the osl1_scop are equals, false otherwise
 */
bool osl1_scop_equal(const osl1_scop_t* const a, const osl1_scop_t* const b) {
  return (
    osl1_relation_equal(&a->context, &b->context) &&
    gho_vector_string_equal(&a->parameters, &b->parameters) &&
    osl1_vector_statement_equal(&a->statements, &b->statements) &&
    gho_vector_any_equal(&a->extensions, &b->extensions)
  );
}

// Conversion

/**
 * \brief Convert an osl1_scop into A gho_string
 * \param[in] scop An osl1_scop
 * \return the gho_string from the osl1_scop
 */
gho_string_t osl1_scop_to_string(const osl1_scop_t* const scop) {
  gho_string_t r = gho_string_create();
  osl1_scop_sprint(&r.c_str, scop);
  return r;
}

/**
 * \brief Convert an osl1_scop into A gho_any
 * \param[in] scop An osl1_scop
 * \return the gho_any from the osl1_scop
 */
gho_any_t osl1_scop_to_any(const osl1_scop_t* const scop) {
  gho_any_t r = gho_any_create();
  r.type = GHO_TYPE_OSL_SCOP;
  r.size_of_struct = sizeof(osl1_scop_t);
  osl1_scop_t* p = gho_alloc(osl1_scop_t);
  osl1_scop_copy_(scop, p);
  r.any = p; p = NULL;
  r.destroy_fct = (gho_destroy_fct_t)osl1_scop_destroy;
  r.fprinti_fct = (gho_fprinti_fct_t)osl1_scop_fprinti;
  r.sprinti_fct = (gho_sprinti_fct_t)osl1_scop_sprinti;
  r.copy_fct = (gho_copy_fct_t)osl1_scop_copy_;
  r.equal_fct = (gho_equal_fct_t)osl1_scop_equal;
  r.to_string_fct = (gho_to_string_fct_t)osl1_scop_to_string;
  return r;
}
