
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                      extensions/annotation.h                    **
     **-----------------------------------------------------------------**

 
 *****************************************************************************
 * OpenScop: Structures and formats for polyhedral tools to talk together    *
 *****************************************************************************
 *    ,___,,_,__,,__,,__,,__,,_,__,,_,__,,__,,___,_,__,,_,__,                *
 *    /   / /  //  //  //  // /   / /  //  //   / /  // /  /|,_,             *
 *   /   / /  //  //  //  // /   / /  //  //   / /  // /  / / /\             *
 *  |~~~|~|~~~|~~~|~~~|~~~|~|~~~|~|~~~|~~~|~~~|~|~~~|~|~~~|/_/  \            *
 *  | G |C| P | = | L | P |=| = |C| = | = | = |=| = |=| C |\  \ /\           *
 *  | R |l| o | = | e | l |=| = |a| = | = | = |=| = |=| L | \# \ /\          *
 *  | A |a| l | = | t | u |=| = |n| = | = | = |=| = |=| o | |\# \  \         *
 *  | P |n| l | = | s | t |=| = |d| = | = | = | |   |=| o | | \# \  \        *
 *  | H | | y |   | e | o | | = |l|   |   | = | |   | | G | |  \  \  \       *
 *  | I | |   |   | e |   | |   | |   |   |   | |   | |   | |   \  \  \      *
 *  | T | |   |   |   |   | |   | |   |   |   | |   | |   | |    \  \  \     *
 *  | E | |   |   |   |   | |   | |   |   |   | |   | |   | |     \  \  \    *
 *  | * |*| * | * | * | * |*| * |*| * | * | * |*| * |*| * | /      \* \  \   *
 *  | O |p| e | n | S | c |o| p |-| L | i | b |r| a |r| y |/        \  \ /   *
 *  '---'-'---'---'---'---'-'---'-'---'---'---'-'---'-'---'          '--'    *
 *                                                                           *
 * Copyright (C) 2008 University Paris-Sud 11 and INRIA                      *
 *                                                                           *
 * (3-clause BSD license)                                                    *
 * Redistribution and use in source  and binary forms, with or without       *
 * modification, are permitted provided that the following conditions        *
 * are met:                                                                  *
 *                                                                           *
 * 1. Redistributions of source code must retain the above copyright notice, *
 *    this list of conditions and the following disclaimer.                  *
 * 2. Redistributions in binary form must reproduce the above copyright      *
 *    notice, this list of conditions and the following disclaimer in the    *
 *    documentation and/or other materials provided with the distribution.   *
 * 3. The name of the author may not be used to endorse or promote products  *
 *    derived from this software without specific prior written permission.  *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR      *
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES *
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.   *
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,          *
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT  *
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY     *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  *
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.         *
 *                                                                           *
 * OpenScop Library, a library to manipulate OpenScop formats and data       *
 * structures. Written by:                                                   *
 * Cedric Bastoul     <Cedric.Bastoul@u-psud.fr> and                         *
 * Louis-Noel Pouchet <Louis-Noel.pouchet@inria.fr>                          *
 *                                                                           *
 *****************************************************************************/

#ifndef OSL_ANNOTATION_H
#define OSL_ANNOTATION_H

#include <stdio.h>
#include <stdbool.h>

#include <osl/attributes.h>
#include <osl/strings.h>

#if defined(__cplusplus)
extern "C"
{
#endif

/* URI */
#define OSL_URI_ANNOTATION "annotation"

/* Texts */

/** \brief No corresponding text. */
#define OSL_ANNOTATION_TEXT_NONE 0
/** \brief Text provided by the user. */
#define OSL_ANNOTATION_TEXT_USER 1
/** \brief The text must be preceded with "#pragma". */
#define OSL_ANNOTATION_TEXT_PRAGMA 2

struct osl_annotation_text {
  int* types;
  char** lines;
  size_t count;
};
typedef struct osl_annotation_text osl_annotation_text_t;

/**
 * \brief Annotations
 *
 * Annotation can have multiple types at the same type ! Inspect the types
 * with bit masks.
 */
struct osl_annotation {
  osl_annotation_text_t prefix;
  osl_annotation_text_t suffix;
};
typedef struct osl_annotation osl_annotation_t;

/*****************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/

void osl_annotation_idump(FILE* file, const osl_annotation_t* annotation, int level)
    OSL_NONNULL_ARGS(1);
void osl_annotation_dump(FILE* file, const osl_annotation_t* annotation)
    OSL_NONNULL_ARGS(1);
char* osl_annotation_sprint(const osl_annotation_t* annotation);

/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/

osl_annotation_t* osl_annotation_sread(char** input) OSL_WARN_UNUSED_RESULT;

/*****************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/

osl_annotation_t* osl_annotation_malloc(void) OSL_WARN_UNUSED_RESULT;
void osl_annotation_free(osl_annotation_t* annotation);

/*****************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/

osl_annotation_t* osl_annotation_clone(const osl_annotation_t* annotation)
    OSL_WARN_UNUSED_RESULT;

bool osl_annotation_equal(const osl_annotation_t* a1, const osl_annotation_t* a2);

osl_interface_t* osl_annotation_interface(void) OSL_WARN_UNUSED_RESULT;

void osl_annotation_append_prefix(osl_annotation_t* annotation, int prefix_type,
                              char* prefix);
void osl_annotation_append_suffix(osl_annotation_t* annotation, int suffix_type,
                              char* suffix);

#if defined(__cplusplus)
}
#endif

#endif
