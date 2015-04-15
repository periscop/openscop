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


// Conversion

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
