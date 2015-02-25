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


#include "../include/osl1/osl_to_osl1.h"


// osl to osl1

/**
 * @brief Convert an osl_scop_t into an osl1_vector_scop_t
 * @param[in] scop_osl An osl_scop_t
 * @return the osl1_vector_scop_t from the osl_scop_t
 */
osl1_vector_scop_t osl_to_osl1(const osl_scop_t* const scop_osl) {
  osl1_vector_scop_t r = osl1_vector_scop_create();
  for (const osl_scop_t* p = scop_osl; p != NULL; p = p->next) {
    osl1_scop_t tmp = osl_to_osl1_scop(p);
    osl1_vector_scop_add(&r, &tmp);
    osl1_scop_destroy(&tmp);
  }
  return r;
}

/**
 * @brief Convert the first scop of an osl_scop_t into an osl1_scop_t
 * @param[in] scop_osl An osl_scop_t
 * @return the osl1_scop_t from the first scop of the osl_scop_t
 */
osl1_scop_t osl_to_osl1_scop(const osl_scop_t* const scop_osl) {
  osl1_scop_t r = osl1_scop_create();
  if (scop_osl != NULL) {
    // Context
    osl1_relation_destroy(&r.context);
    r.context = osl_to_osl1_relation(scop_osl->context);
    // Parameters
    if (scop_osl->parameters != NULL &&
        scop_osl->parameters->data != NULL &&
        scop_osl->parameters->interface != NULL &&
        scop_osl->parameters->interface->URI != NULL &&
        strcmp(scop_osl->parameters->interface->URI, "strings") == 0
    ) {
      const osl_strings_t* const parameters_osl = scop_osl->parameters->data;
      for (char** p = parameters_osl->string; p != NULL; ++p) { // p should be const
        gho_vector_string_add_c_str(&r.parameters, *p);
      }
    }
    // Statements
    osl1_vector_statement_destroy(&r.statements);
    r.statements = osl_to_osl1_statement(scop_osl->statement);
    // Extensions
    gho_vector_any_destroy(&r.extensions);
    r.extensions = osl_to_osl1_extensions(scop_osl->extension);
  }
  return r;
}

/**
 * @brief Convert an osl_statement_t into an osl1_vector_statement_t
 * @param[in] statement_osl An osl_statement_t
 * @return the osl1_vector_statement_t from the osl_statement_t
 */
osl1_vector_statement_t osl_to_osl1_statement(
                                   const osl_statement_t* const statement_osl) {
  osl1_vector_statement_t r = osl1_vector_statement_create();
  for (const osl_statement_t* p = statement_osl; p != NULL; p = p->next) {
    osl1_statement_t tmp = osl1_statement_create();
    // Iteration domain
    osl1_relation_destroy(&tmp.domain);
    tmp.domain = osl_to_osl1_relation(p->domain);
    // Scattering (mapping)
    osl1_relation_destroy(&tmp.scattering);
    tmp.scattering = osl_to_osl1_relation(p->scattering);
    // Accesses
    for (const osl_relation_list_t* q = p->access; q != NULL; q = q->next) {
      if (q->elt != NULL) {
        osl1_relation_t relation = osl_to_osl1_relation(q->elt);
        if (q->elt->type == OSL_TYPE_ACCESS || q->elt->type == OSL_TYPE_READ) {
          osl1_vector_relation_add(&tmp.accesses_read, &relation);
        }
        else {
          osl1_vector_relation_add(&tmp.accesses_write, &relation);
        }
        osl1_relation_destroy(&relation);
      }
    }
    // Extensions
    gho_vector_any_destroy(&tmp.extensions);
    tmp.extensions = osl_to_osl1_extensions(p->extension);
    // Add
    osl1_vector_statement_add(&r, &tmp);
    osl1_statement_destroy(&tmp);
  }
  return r;
}

/**
 * @brief Convert an osl_generic_t into an gho_vector_any_t
 * @param[in] relation_osl An osl_generic_t
 * @return the gho_vector_any_t from the osl_generic_t
 */
gho_vector_any_t osl_to_osl1_extensions(
                                    const osl_generic_t* const extensions_osl) {
  gho_vector_any_t r = gho_vector_any_create();
  for (const osl_generic_t* p = extensions_osl; p != NULL; p = p->next) {
  if (p->data != NULL && p->interface != NULL) {
      gho_any_t any;
      // body
      if (strcmp(p->interface->URI, "body") == 0) {
        const osl_body_t* const body = p->data;
        osl1_extension_body_t tmp = osl1_extension_body_create();
        // Expression
        if (body->expression != NULL && body->expression->string != NULL) {
          gho_string_add_c_str(&tmp.expression, body->expression->string[0]);
        }
        // Names of original iterators
        if (body->iterators != NULL) {
          for (char** s = body->iterators->string; s != NULL; ++s) { 
            gho_vector_string_add_c_str(&tmp.original_iterators, *s);
          }
        }
        // To Any
        any = osl1_extension_body_to_any(&tmp);
        osl1_extension_body_destroy(&tmp);
      }
      // scatnames
      if (strcmp(p->interface->URI, "scatnames") == 0) {
        const osl_scatnames_t* const scatnames = p->data;
        osl1_extension_scatnames_t tmp = osl1_extension_scatnames_create();
        // Names of output dimensions of scattering
        if (scatnames->names != NULL) {
          for (char** s = scatnames->names->string; s != NULL; ++s) { 
            gho_vector_string_add_c_str(&tmp.scatnames, *s);
          }
        }
        // To Any
        any = osl1_extension_scatnames_to_any(&tmp);
        osl1_extension_scatnames_destroy(&tmp);
      }
      // unknown
      else {
        osl1_extension_unknown_t tmp = osl1_extension_unknown_create();
        // Mark
        gho_string_add_c_str(&tmp.mark, p->interface->URI);
        // Extension
        char* c_str = p->interface->sprint(p->data);
        gho_string_add_c_str(&tmp.extension, c_str);
        free(c_str); c_str = NULL;
        // To Any
        any = osl1_extension_unknown_to_any(&tmp);
        osl1_extension_unknown_destroy(&tmp);
      }
      // Add
      gho_vector_any_add(&r, &any);
      gho_any_destroy(&any);
    }
  }
  return r;
}
