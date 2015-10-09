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


#ifndef OSL1_PRINT_SCOP_H
#define OSL1_PRINT_SCOP_H

#include <stdio.h>

#include "../scop.h"


// SCoP
static inline
void osl1_scop_fprinti_openscop(FILE* file,
                                const osl1_scop_t* const scop,
                                const unsigned int indent);
static inline
void osl1_scop_sprinti_openscop(char** c_str,
                                const osl1_scop_t* const scop,
                                const unsigned int indent);

#endif
