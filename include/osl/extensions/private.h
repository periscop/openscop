/******************************************************************************
 **                            OpenScop Library                              **
 **--------------------------------------------------------------------------**
 **                           extensions/private.h                           **
 **--------------------------------------------------------------------------**
 **                        First version: 13/09/2026                         **
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

#ifndef OSL_PRIVATE_H
#define OSL_PRIVATE_H

#include <stdio.h>

#include <osl/attributes.h>
#include <osl/interface.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define OSL_URI_PRIVATE "private"

/**
 * The osl_private_t structure stores SCoP-level scalar expansion metadata.
 * Statement numbers are one-based.
 * Each entry identifies an array, its declaration statement, and the number
 * of leading access dimensions introduced by expansion at that declaration.
 * Only variables with at least one expansion dimension are listed.
 */
struct osl_private {
  int nb_variables; /**< Number of loop-private variables. */
  int* array_id;    /**< Array of nb_variables array identifiers. */
  int* stmt_id;     /**< Array of one-based declaration statement numbers. */
  int* nb_dims;     /**< Array of leading expansion dimension counts. */
};
typedef struct osl_private osl_private_t;
typedef struct osl_private* osl_private_p;

/******************************************************************************
 *                         Structure display function                         *
 ******************************************************************************/

void osl_private_idump(FILE*, const osl_private_t*, int) OSL_NONNULL_ARGS(1);
void osl_private_dump(FILE*, const osl_private_t*) OSL_NONNULL_ARGS(1);
char* osl_private_sprint(const osl_private_t*) OSL_WARN_UNUSED_RESULT;

/******************************************************************************
 *                              Reading function                              *
 ******************************************************************************/

osl_private_t* osl_private_sread(char**) OSL_WARN_UNUSED_RESULT;

/******************************************************************************
 *                  Memory allocation/deallocation function                   *
 ******************************************************************************/

osl_private_t* osl_private_malloc(void) OSL_WARN_UNUSED_RESULT;
void osl_private_free(osl_private_t*);

/******************************************************************************
 *                            Processing functions                            *
 ******************************************************************************/

osl_private_t* osl_private_clone(const osl_private_t*) OSL_WARN_UNUSED_RESULT;
bool osl_private_equal(const osl_private_t*, const osl_private_t*);
void osl_private_add(osl_private_t*, int, int, int) OSL_NONNULL_ARGS(1);
osl_interface_t* osl_private_interface(void) OSL_WARN_UNUSED_RESULT;

#if defined(__cplusplus)
}
#endif
#endif /* OSL_PRIVATE_H */
