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


#ifndef OSL1_PRINT_RELATION_POLYLIB_H
#define OSL1_PRINT_RELATION_POLYLIB_H

#include <stdio.h>

#include "../relation.h"


// Relation
static inline
void osl1_relation_fprint_polylib(FILE* file,
                                  const osl1_relation_t* const relation);
static inline
void osl1_relation_sprint_polylib(char** c_str,
                                  const osl1_relation_t* const relation);

#endif
