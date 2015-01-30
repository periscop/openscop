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


#ifndef OSL1_EXTENSION_H
#define OSL1_EXTENSION_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

#include <gho/string.h>
#include <gho/any.h>
#include <gho/vector/any.h>
#include <gho/type.h>

#include "extension/body.h"
#include "extension/coordinates.h"
#include "extension/scatnames.h"
#include "extension/unknown.h"


// Get
void* osl1_get_extension_ptr(gho_type_t const type,
                             gho_vector_any_t* extensions);
const void* osl1_get_extension_cptr(gho_type_t const type,
                                    const gho_vector_any_t* const extensions);

// Input
static inline
gho_any_t osl1_extension_fread_with_mark(FILE* file,
                                         const gho_string_t* const mark);
static inline
gho_any_t osl1_extension_sread_with_mark(const char** c_str,
                                         const gho_string_t* const mark);

#include "extension/extension.h"

#endif
