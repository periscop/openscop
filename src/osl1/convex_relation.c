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


#include "../include/osl1/convex_relation.h"


// Id

/**
 * \brief Return a new id for osl1_convex_relation_t
 * \return a new id for osl1_convex_relation_t
 */
size_t osl1_convex_relation_new_id() {
  static size_t id = 0;
  return id++;
}

// Precision

/**
 * \brief Return int precision used for osl1_convex_relation_t
 * \return int precision used for osl1_convex_relation_t
 */
gho_type_t* osl1_convex_relation_precision() {
//   #ifdef osl_with_gmp
//     static gho_type_t precision = GHO_TYPE_GHO_MPZ_T;
//   #else
    static gho_type_t precision = GHO_TYPE_LLINT;
//   #endif
  return &precision;
}

/**
 * \brief Return int precision used for osl1_convex_relation_t
 * \return int precision used for osl1_convex_relation_t
 */
gho_type_t osl1_convex_relation_get_precision() {
  return *osl1_convex_relation_precision();
}

/**
 * \brief Set int precision used for osl1_convex_relation_t
 * \param[in] precision gho type of the precision
 */
void osl1_convex_relation_set_precision(const gho_type_t type) {
  *osl1_convex_relation_precision() = type;
}

/**
 * \brief Set int precision used for osl1_convex_relation_t to long int
 */
void osl1_convex_relation_set_precision_lint() {
  osl1_convex_relation_set_precision(GHO_TYPE_LINT);
}

/**
 * \brief Set int precision used for osl1_convex_relation_t to long long int
 */
void osl1_convex_relation_set_precision_llint() {
  osl1_convex_relation_set_precision(GHO_TYPE_LLINT);
}

#ifdef osl_with_gmp

/**
 * \brief Set int precision used for osl1_convex_relation_t to mpz
 */
void osl1_convex_relation_set_precision_mpz() {
  osl1_convex_relation_set_precision(GHO_TYPE_GHO_MPZ_T);
}
#endif
