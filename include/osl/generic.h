/******************************************************************************
 **                            OpenScop Library                              **
 **--------------------------------------------------------------------------**
 **                                generic.h                                 **
 **--------------------------------------------------------------------------**
 **                        First version: 26/11/2010                         **
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

#ifndef OSL_generic_H
#define OSL_generic_H

#include <osl/attributes.h>
#include <osl/interface.h>

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * The osl_generic_t structure stores OpenScop data and operations with
 * no pre-defined type. The information is accessible through the data pointer
 * while the type and operations are accessible through the interface pointer.
 * A generic is a also a node of a NULL-terminated linked list of generics.
 */
struct osl_generic {
  void *data;                /**< Pointer to the data. */
  osl_interface_p interface; /**< Interface to work with the data. */
  struct osl_generic *next;  /**< Pointer to the next generic. */
};
typedef struct osl_generic osl_generic_t;
typedef struct osl_generic *osl_generic_p;
typedef struct osl_generic const osl_const_generic_t;
typedef struct osl_generic *const osl_generic_const_p;
typedef struct osl_generic const *osl_const_generic_p;
typedef struct osl_generic const *const osl_const_generic_const_p;

/******************************************************************************
 *                          Structure display function                        *
 ******************************************************************************/
void osl_generic_idump(FILE *, const osl_generic_t *, int) OSL_NONNULL_ARGS(1);
void osl_generic_dump(FILE *, const osl_generic_t *) OSL_NONNULL_ARGS(1);
void osl_generic_print(FILE *, const osl_generic_t *) OSL_NONNULL_ARGS(1);
char *osl_generic_sprint(const osl_generic_t *);

// SCoPLib Compatibility
void osl_generic_print_options_scoplib(FILE *, const osl_generic_t *)
    OSL_NONNULL_ARGS(1);
/******************************************************************************
 *                               Reading function                             *
 ******************************************************************************/
osl_generic_t *osl_generic_sread(char **, osl_interface_t *)
    OSL_NONNULL_ARGS(1);
osl_generic_t *osl_generic_sread_one(char **, osl_interface_t *)
    OSL_NONNULL_ARGS(1);
osl_generic_t *osl_generic_read_one(FILE *, osl_interface_t *)
    OSL_NONNULL_ARGS(1);
osl_generic_t *osl_generic_read(FILE *, osl_interface_t *) OSL_NONNULL_ARGS(1);

/******************************************************************************
 *                    Memory allocation/deallocation function                 *
 ******************************************************************************/
void osl_generic_add(osl_generic_t **, osl_generic_t *) OSL_NONNULL_ARGS(1);
void osl_generic_remove_node(osl_generic_t **, osl_generic_t *)
    OSL_NONNULL_ARGS(1);
void osl_generic_remove(osl_generic_t **, const char *) OSL_NONNULL_ARGS(1);
osl_generic_t *osl_generic_malloc(void) OSL_WARN_UNUSED_RESULT;
void osl_generic_free(osl_generic_t *);

/******************************************************************************
 *                            Processing functions                            *
 ******************************************************************************/
int osl_generic_number(const osl_generic_t *);
osl_generic_t *osl_generic_clone(const osl_generic_t *) OSL_WARN_UNUSED_RESULT;
osl_generic_t *osl_generic_nclone(const osl_generic_t *,
                                  int) OSL_WARN_UNUSED_RESULT;
bool osl_generic_equal(const osl_generic_t *, const osl_generic_t *);
int osl_generic_has_URI(const osl_generic_t *, char const *const);
void *osl_generic_lookup(const osl_generic_t *, char const *const);
osl_generic_t *osl_generic_shell(void *,
                                 osl_interface_t *) OSL_WARN_UNUSED_RESULT;
int osl_generic_count(const osl_generic_t *);

#if defined(__cplusplus)
}
#endif

#endif /* define OSL_generic_H */
