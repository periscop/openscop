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

#include "../include/osl1/statement.h"
#include "../include/osl1/print.h"


// Create & destroy

/**
 * \brief Return a new osl1_statement
 * \return a new osl1_statement
 */
osl1_statement_t osl1_statement_create() {
  osl1_statement_t statement;
  statement.domain = osl1_relation_create();
  statement.scattering = osl1_relation_create();
  statement.accesses_read = osl1_vector_relation_create();
  statement.accesses_write = osl1_vector_relation_create();
  statement.extensions = gho_vector_any_create();
  return statement;
}

/**
 * \brief Destroy an osl1_statement
 * \param[in] statement An osl1_statement
 */
void osl1_statement_destroy(osl1_statement_t* statement) {
  osl1_relation_destroy(&statement->domain);
  osl1_relation_destroy(&statement->scattering);
  osl1_vector_relation_destroy(&statement->accesses_read);
  osl1_vector_relation_destroy(&statement->accesses_write);
  gho_vector_any_destroy(&statement->extensions);
}

/**
 * \brief Erase an osl1_statement
 * \param[in] statement An osl1_statement
 */
void osl1_statement_erase(osl1_statement_t* statement) {
  osl1_statement_destroy(statement);
  *statement = osl1_statement_create();
}

// Output

/**
 * \brief Print an osl1_statement in a file with indentation
 * \param[in] file      A C file
 * \param[in] statement An osl1_statement
 * \param[in] indent    Indentation (number of spaces)
 */
void osl1_statement_fprinti(FILE* file,
                            const osl1_statement_t* const statement,
                            const unsigned int indent) {
  osl1_statement_fprinti_openscop(file, statement, indent, NULL);
}

/**
 * \brief Print an osl1_statement in a file
 * \param[in] file      A C file
 * \param[in] statement An osl1_statement
 */
void osl1_statement_fprint(FILE* file,
                           const osl1_statement_t* const statement) {
  osl1_statement_fprinti(file, statement, 0);
}

/**
 * \brief Print an osl1_statement in stdout
 * \param[in] statement An osl1_statement
 */
void osl1_statement_print(const osl1_statement_t* const statement) {
  osl1_statement_fprint(stdout, statement);
}

/**
 * \brief Print an osl1_statement in a C string with indentation
 * \param[in] c_str     A C string
 * \param[in] statement An osl1_statement
 * \param[in] indent    Indentation (number of spaces)
 */
void osl1_statement_sprinti(char** c_str,
                            const osl1_statement_t* const statement,
                            const unsigned int indent) {
  osl1_statement_sprinti_openscop(c_str, statement, indent, NULL);
}

/**
 * \brief Print an osl1_statement in a C string
 * \param[in] c_str     A C string
 * \param[in] statement An osl1_statement
 */
void osl1_statement_sprint(char** c_str,
                           const osl1_statement_t* const statement) {
  osl1_statement_sprinti(c_str, statement, 0);
}

// Input

/**
 * \brief Read an osl1_statement from a file
 * \param[in] file A C file
 * \return the osl1_statement read
 */
osl1_statement_t osl1_statement_fread(FILE* file) {
  
  osl1_statement_t statement = osl1_statement_create();
  
  // Domain
  osl1_relation_destroy(&statement.domain);
  statement.domain = osl1_relation_fread(file);
  
  // Scattering
  osl1_relation_destroy(&statement.scattering);
  statement.scattering = osl1_relation_fread(file);
  
  // Accesses (read)
  osl1_vector_relation_destroy(&statement.accesses_write);
  statement.accesses_write = osl1_vector_relation_fread(file);
  
  // Accesses (write)
  osl1_vector_relation_destroy(&statement.accesses_write);
  statement.accesses_write = osl1_vector_relation_fread(file);
  
  // Extensions
  gho_vector_any_destroy(&statement.extensions);
  statement.extensions = osl1_extensions_fread(file);
  
  return statement;
}

/**
 * \brief Read an osl1_statement from a C string
 * \param[in] c_str A C string
 * \return the osl1_statement read
 */
osl1_statement_t osl1_statement_sread(const char** c_str) {
  
  osl1_statement_t statement = osl1_statement_create();
  
  // Domain
  osl1_relation_destroy(&statement.domain);
  statement.domain = osl1_relation_sread(c_str);
  
  // Scattering
  osl1_relation_destroy(&statement.scattering);
  statement.scattering = osl1_relation_sread(c_str);
  
  // Accesses (read)
  osl1_vector_relation_destroy(&statement.accesses_write);
  statement.accesses_write = osl1_vector_relation_sread(c_str);
  
  // Accesses (write)
  osl1_vector_relation_destroy(&statement.accesses_write);
  statement.accesses_write = osl1_vector_relation_sread(c_str);
  
  // Extensions
  gho_vector_any_destroy(&statement.extensions);
  statement.extensions = osl1_extensions_sread(c_str);
  
  return statement;
}

// Copy & comparisons

/**
 * \brief Copy an osl1_statement
 * \param[in] statement An osl1_statement
 * \return the osl1_statement copied
 */
osl1_statement_t osl1_statement_copy(const osl1_statement_t* const statement) {
  osl1_statement_t r;
  osl1_statement_copy_(statement, &r);
  return r;
}

/**
 * \brief Copy an osl1_statement
 * \param[in] statement An osl1_statement
 * \param[in] copy      A pointer on an not initialized osl1_statement
 * \warning Do not use this function, use osl1_statement_copy
 */
void osl1_statement_copy_(const osl1_statement_t* const statement,
                          osl1_statement_t* copy) {
  copy->domain = osl1_relation_copy(&statement->domain);
  copy->scattering = osl1_relation_copy(&statement->scattering);
  copy->accesses_read = osl1_vector_relation_copy(&statement->accesses_read);
  copy->accesses_write = osl1_vector_relation_copy(&statement->accesses_write);
  copy->extensions = gho_vector_any_copy(&statement->extensions);
}

/**
 * \brief Equality between two osl1_statement
 * \param[in] a An osl1_statement
 * \param[in] b An osl1_statement
 * \return true if the osl1_statement are equals, false otherwise
 */
bool osl1_statement_equal(const osl1_statement_t* const a,
                          const osl1_statement_t* const b) {
  return (
    osl1_relation_equal(&a->domain, &b->domain) &&
    osl1_relation_equal(&a->scattering, &b->scattering) &&
    osl1_vector_relation_equal(&a->accesses_read, &b->accesses_read) &&
    osl1_vector_relation_equal(&a->accesses_write, &b->accesses_write) &&
    gho_vector_any_equal(&a->extensions, &b->extensions)
  );
}

// Conversion

/**
 * \brief Convert an osl1_statement into A gho_string
 * \param[in] statement An osl1_statement
 * \return the gho_string from the osl1_statement
 */
gho_string_t osl1_statement_to_string(const osl1_statement_t* const statement) {
  gho_string_t r = gho_string_create();
  osl1_statement_sprint(&r.c_str, statement);
  return r;
}

/**
 * \brief Convert an osl1_statement into A gho_any
 * \param[in] statement An osl1_statement
 * \return the gho_any from the osl1_statement
 */
gho_any_t osl1_statement_to_any(const osl1_statement_t* const statement) {
  gho_any_t r = gho_any_create();
  r.type = GHO_TYPE_OSL_STATEMENT;
  r.size_of_struct = sizeof(osl1_statement_t);
  osl1_statement_t* p = gho_alloc(osl1_statement_t);
  osl1_statement_copy_(statement, p);
  r.any = p; p = NULL;
  r.destroy_fct = (gho_destroy_fct_t)osl1_statement_destroy;
  r.fprinti_fct = (gho_fprinti_fct_t)osl1_statement_fprinti;
  r.sprinti_fct = (gho_sprinti_fct_t)osl1_statement_sprinti;
  r.copy_fct = (gho_copy_fct_t)osl1_statement_copy_;
  r.equal_fct = (gho_equal_fct_t)osl1_statement_equal;
  r.to_string_fct = (gho_to_string_fct_t)osl1_statement_to_string;
  return r;
}
