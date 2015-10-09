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


// Conversion

/**
 * \brief Convert an osl1_dimension_type into a gho_any
 * \param[in] dimension_type An osl1_dimension_type
 * \return the gho_any from the osl1_dimension_type
 */
gho_any_t osl1_dimension_type_to_any(const osl1_dimension_type_t* const dimension_type) {
  gho_any_t r = gho_any_create();
  r.type = GHO_TYPE_OSL_DIMENSION_TYPE;
  r.size_of_struct = sizeof(osl1_dimension_type_t);
  osl1_dimension_type_t* p = gho_alloc(osl1_dimension_type_t);
  osl1_dimension_type_copy_(dimension_type, p);
  r.any = p; p = NULL;
  r.destroy_fct = (gho_destroy_fct_t)osl1_dimension_type_destroy;
  r.fprinti_fct = (gho_fprinti_fct_t)osl1_dimension_type_fprinti;
  r.sprinti_fct = (gho_sprinti_fct_t)osl1_dimension_type_sprinti;
  r.copy_fct = (gho_copy_fct_t)osl1_dimension_type_copy_;
  r.equal_fct = (gho_equal_fct_t)osl1_dimension_type_equal;
  r.to_string_fct = (gho_to_string_fct_t)osl1_dimension_type_to_string;
  return r;
}
