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


#ifndef OSL1_ID_H
#define OSL1_ID_H

#include <stddef.h>

#include <gho/type.h>


#if defined(__cplusplus)
extern "C"
{
#endif

// Id
size_t osl1_convex_relation_new_id();
size_t osl1_statement_new_id();

// Precision
gho_type_t* osl1_convex_relation_precision();

#if defined(__cplusplus)
}
#endif

#endif
