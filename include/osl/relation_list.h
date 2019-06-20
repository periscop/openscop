/******************************************************************************
 **                            OpenScop Library                              **
 **--------------------------------------------------------------------------**
 **                             relation_list.h                              **
 **--------------------------------------------------------------------------**
 **                        First version: 08/10/2010                         **
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

#ifndef OSL_RELATION_LIST_H
#define OSL_RELATION_LIST_H

#include <stdio.h>

#include <osl/attributes.h>
#include <osl/relation.h>

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * The osl_relation_list_t structure describes a (NULL-terminated
 * linked) list of relations.
 */
struct osl_relation_list {
  osl_relation_p elt;             /**< An element of the list. */
  struct osl_relation_list *next; /**< Pointer to the next element
                                       of the list.*/
};
typedef struct osl_relation_list osl_relation_list_t;
typedef struct osl_relation_list *osl_relation_list_p;

/******************************************************************************
 *                          Structure display function                        *
 ******************************************************************************/

void osl_relation_list_idump(FILE *, const osl_relation_list_t *, int)
    OSL_NONNULL_ARGS(1);
void osl_relation_list_dump(FILE *, const osl_relation_list_t *)
    OSL_NONNULL_ARGS(1);
void osl_relation_list_pprint_elts(FILE *, const osl_relation_list_t *,
                                   const osl_names_t *) OSL_NONNULL_ARGS(1);
void osl_relation_list_pprint(FILE *, const osl_relation_list_t *,
                              const osl_names_t *) OSL_NONNULL_ARGS(1);
void osl_relation_list_print(FILE *, const osl_relation_list_t *)
    OSL_NONNULL_ARGS(1);

// SCoPLib Compatibility
void osl_relation_list_pprint_access_array_scoplib(FILE *,
                                                   const osl_relation_list_t *,
                                                   const osl_names_t *, int)
    OSL_NONNULL_ARGS(1);

/******************************************************************************
 *                               Reading function                             *
 ******************************************************************************/

osl_relation_list_t *osl_relation_list_pread(FILE *, int) OSL_WARN_UNUSED_RESULT
    OSL_NONNULL_ARGS(1);
osl_relation_list_t *osl_relation_list_read(FILE *) OSL_WARN_UNUSED_RESULT
    OSL_NONNULL_ARGS(1);

/******************************************************************************
 *                    Memory allocation/deallocation function                 *
 ******************************************************************************/

osl_relation_list_t *osl_relation_list_malloc(void) OSL_WARN_UNUSED_RESULT;
void osl_relation_list_free(osl_relation_list_t *);

/******************************************************************************
 *                            Processing functions                            *
 ******************************************************************************/

osl_relation_list_t *osl_relation_list_node(const osl_relation_t *)
    OSL_WARN_UNUSED_RESULT;
osl_relation_list_t *osl_relation_list_clone(const osl_relation_list_t *)
    OSL_WARN_UNUSED_RESULT;
osl_relation_list_t *osl_relation_list_concat(const osl_relation_list_t *,
                                              const osl_relation_list_t *)
    OSL_WARN_UNUSED_RESULT;
void osl_relation_list_add(osl_relation_list_t **, osl_relation_list_t *);
void osl_relation_list_push(osl_relation_list_t **, osl_relation_list_t *);
osl_relation_list_t *osl_relation_list_pop(osl_relation_list_p *)
    OSL_WARN_UNUSED_RESULT;
void osl_relation_list_dup(osl_relation_list_t **);
void osl_relation_list_drop(osl_relation_list_t **);
void osl_relation_list_destroy(osl_relation_list_t **);
int osl_relation_list_equal(const osl_relation_list_t *,
                            const osl_relation_list_t *);
int osl_relation_list_integrity_check(const osl_relation_list_t *, int, int,
                                      int, int);
void osl_relation_list_set_type(osl_relation_list_t *, int);
osl_relation_list_t *osl_relation_list_filter(const osl_relation_list_t *,
                                              int) OSL_WARN_UNUSED_RESULT;
size_t osl_relation_list_count(const osl_relation_list_t *);
void osl_relation_list_get_attributes(const osl_relation_list_t *, int *, int *,
                                      int *, int *, int *);
#if defined(__cplusplus)
}
#endif

#endif /* define OSL_RELATION_LIST_H */
