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


#include <osl1/id.h>


// Id

/**
 * \brief Return a new id for osl1_convex_relation_t
 * \return a new id for osl1_convex_relation_t
 */
size_t osl1_convex_relation_new_id() {
  static size_t id = 0;
  return id++;
}

/**
 * \brief Return a new id for osl1_statement_t
 * \return a new id for osl1_statement_t
 */
size_t osl1_statement_new_id() {
  static size_t id = 0;
  return id++;
}

// Convex relation precision

/**
 * \brief Return int precision used for osl1_convex_relation_t
 * \return int precision used for osl1_convex_relation_t
 */
gho_type_t* osl1_convex_relation_precision() {
  static gho_type_t precision = 0;
  return &precision;
}
