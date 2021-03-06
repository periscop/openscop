/******************************************************************************
 **                            OpenScop Library                              **
 **--------------------------------------------------------------------------**
 **                               statement.h                                **
 **--------------------------------------------------------------------------**
 **                        First version: 30/04/2008                         **
 ******************************************************************************/

/******************************************************************************
 * OpenScop: Structures and formats for polyhedral tools to talk together     *
 ******************************************************************************
 *    ,___,,_,__,,__,,__,,__,,_,__,,_,__,,__,,___,_,__,,_,__,                 *
 *    /   / /  //  //  //  // /   / /  //  //   / /  // /  /|,_,              *
 *   /   / /  //  //  //  // /   / /  //  //   / /  // /  / / /\              *
 *  |~~~|~|~~~|~~~|~~~|~~~|~|~~~|~|~~~|~~~|~~~|~|~~~|~|~~~|/_/  \             *
 *  | G |C| P | = | L | P |=| = |C| = | = | = |=| = |=| C |\  \ /\            *
 *  | R |l| o | = | e | l |=| = |a| = | = | = |=| = |=| L | \# \ /\           *
 *  | A |a| l | = | t | u |=| = |n| = | = | = |=| = |=| o | |\# \  \          *
 *  | P |n| l | = | s | t |=| = |d| = | = | = | |   |=| o | | \# \  \         *
 *  | H | | y |   | e | o | | = |l|   |   | = | |   | | G | |  \  \  \        *
 *  | I | |   |   | e |   | |   | |   |   |   | |   | |   | |   \  \  \       *
 *  | T | |   |   |   |   | |   | |   |   |   | |   | |   | |    \  \  \      *
 *  | E | |   |   |   |   | |   | |   |   |   | |   | |   | |     \  \  \     *
 *  | * |*| * | * | * | * |*| * |*| * | * | * |*| * |*| * | /      \* \  \    *
 *  | O |p| e | n | S | c |o| p |-| L | i | b |r| a |r| y |/        \  \ /    *
 *  '---'-'---'---'---'---'-'---'-'---'---'---'-'---'-'---'          '--'     *
 *                                                                            *
 * Copyright (C) 2008 University Paris-Sud 11 and INRIA                       *
 *                                                                            *
 * (3-clause BSD license)                                                     *
 * Redistribution and use in source  and binary forms, with or without        *
 * modification, are permitted provided that the following conditions         *
 * are met:                                                                   *
 *                                                                            *
 * 1. Redistributions of source code must retain the above copyright notice,  *
 *    this list of conditions and the following disclaimer.                   *
 * 2. Redistributions in binary form must reproduce the above copyright       *
 *    notice, this list of conditions and the following disclaimer in the     *
 *    documentation and/or other materials provided with the distribution.    *
 * 3. The name of the author may not be used to endorse or promote products   *
 *    derived from this software without specific prior written permission.   *
 *                                                                            *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR       *
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES  *
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.    *
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,           *
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT   *
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY      *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT        *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF   *
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.          *
 *                                                                            *
 * OpenScop Library, a library to manipulate OpenScop formats and data        *
 * structures. Written by:                                                    *
 * Cedric Bastoul     <Cedric.Bastoul@u-psud.fr> and                          *
 * Louis-Noel Pouchet <Louis-Noel.pouchet@inria.fr>                           *
 *                                                                            *
 ******************************************************************************/

#ifndef OSL_STATEMENT_H
#define OSL_STATEMENT_H

#include <stdio.h>

#include <osl/attributes.h>
#include <osl/body.h>
#include <osl/extensions/extbody.h>
#include <osl/generic.h>
#include <osl/interface.h>
#include <osl/names.h>
#include <osl/relation.h>
#include <osl/relation_list.h>

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * The osl_statement_t structure stores a list of statement. Each node
 * contains the useful informations for a given statement to process it
 * within a polyhedral framework. The order in the list may matter for naming
 * conventions (e.g. "S1" for the first statement in the list).
 */
struct osl_statement {
  osl_relation_p domain;      /**< Iteration domain of the statement */
  osl_relation_p scattering;  /**< Scattering relation of the statement*/
  osl_relation_list_p access; /**< Access information */
  osl_generic_p extension;    /**< A list of statement extensions */
  void* usr;                  /**< A user-defined field, not touched
                                   AT ALL by the OpenScop Library. */
  struct osl_statement* next; /**< Next statement in the linked list */
};
typedef struct osl_statement osl_statement_t;
typedef struct osl_statement* osl_statement_p;

/******************************************************************************
 *                          Structure display function                        *
 ******************************************************************************/

void osl_statement_idump(FILE*, const osl_statement_t*, int)
    OSL_NONNULL_ARGS(1);
void osl_statement_dump(FILE*, const osl_statement_t*) OSL_NONNULL_ARGS(1);
void osl_statement_pprint(FILE*, const osl_statement_t*, const osl_names_t*)
    OSL_NONNULL_ARGS(1);
void osl_statement_print(FILE*, const osl_statement_t*) OSL_NONNULL_ARGS(1);

// SCoPLib Compatibility
void osl_statement_pprint_scoplib(FILE*, const osl_statement_t*,
                                  const osl_names_t*) OSL_NONNULL_ARGS(1);

/******************************************************************************
 *                              Reading function                              *
 ******************************************************************************/

osl_statement_t* osl_statement_pread(FILE*, osl_interface_t*, int);
osl_statement_t* osl_statement_read(FILE*) OSL_NONNULL_ARGS(1);

/******************************************************************************
 *                   Memory allocation/deallocation function                  *
 ******************************************************************************/

osl_statement_t* osl_statement_malloc(void) OSL_WARN_UNUSED_RESULT;
void osl_statement_free(osl_statement_t*);

/******************************************************************************
 *                           Processing functions                             *
 ******************************************************************************/

void osl_statement_add(osl_statement_t**, osl_statement_t*);
void osl_statement_compact(osl_statement_p, int);
int osl_statement_number(const osl_statement_t*);
osl_statement_t* osl_statement_nclone(const osl_statement_t*,
                                      int) OSL_WARN_UNUSED_RESULT;
osl_statement_t* osl_statement_clone(const osl_statement_t*)
    OSL_WARN_UNUSED_RESULT;
osl_statement_t* osl_statement_remove_unions(const osl_statement_t*)
    OSL_WARN_UNUSED_RESULT;
int osl_statement_equal(const osl_statement_t*, const osl_statement_t*);
int osl_statement_integrity_check(const osl_statement_t*, int);
int osl_statement_get_nb_iterators(const osl_statement_t*);
void osl_statement_get_attributes(const osl_statement_t*, int*, int*, int*,
                                  int*, int*);
osl_body_t* osl_statement_get_body(const osl_statement_t*);
#if defined(__cplusplus)
}
#endif

#endif /* define OSL_STATEMENT_H */
