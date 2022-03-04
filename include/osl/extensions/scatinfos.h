/******************************************************************************
 **                            OpenScop Library                              **
 **--------------------------------------------------------------------------**
 **                         extensions/scatinfos.h                           **
 **--------------------------------------------------------------------------**
 **                        First version: 04/03/2022                         **
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

#ifndef OSL_SCATINFOS_H
#define OSL_SCATINFOS_H

#include <stdio.h>

#include <osl/interface.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define OSL_URI_SCATINFOS "scatinfos"

/**
 * The osl_scatinfos_t structure stores informations about scattering
 * dimensions as an extension to the core OpenScop representation.
 * It provides SCoP-wide information about each scattering dimension,
 * e.g. whether it is parallel, sequential, part of a permutable
 * sequence of dimensions, etc. Its aim is to communicate such information
 * among different tools in the polyhedral chain.
 */
struct osl_scatinfos {
  size_t nb_scatdims; /**< \brief Number of scattering dimensions */
  int* parallel;      /**< \brief Parallel type (0:sequential, 1: parallel) */
  int* permutable;    /**< \brief Sequence of permutable loops */
  int* type;          /**< \brief Basic type (0: scalar, 1: loop) */
};
typedef struct osl_scatinfos osl_scatinfos_t;
typedef struct osl_scatinfos* osl_scatinfos_p;

/******************************************************************************
 *                          Structure display function                        *
 ******************************************************************************/

void osl_scatinfos_idump(FILE*, const osl_scatinfos_t*, int) OSL_NONNULL_ARGS(1);
void osl_scatinfos_dump(FILE*, const osl_scatinfos_t*) OSL_NONNULL_ARGS(1);
char* osl_scatinfos_sprint(const osl_scatinfos_t*) OSL_WARN_UNUSED_RESULT;

/******************************************************************************
 *                               Reading function                             *
 ******************************************************************************/

osl_scatinfos_t* osl_scatinfos_sread(char**) OSL_WARN_UNUSED_RESULT;

/******************************************************************************
 *                    Memory allocation/deallocation function                 *
 ******************************************************************************/

osl_scatinfos_t* osl_scatinfos_malloc(void) OSL_WARN_UNUSED_RESULT;
void osl_scatinfos_free(osl_scatinfos_t*);

/******************************************************************************
 *                            Processing functions                            *
 ******************************************************************************/

osl_scatinfos_t* osl_scatinfos_clone(const osl_scatinfos_t*) OSL_WARN_UNUSED_RESULT;
bool osl_scatinfos_equal(const osl_scatinfos_t*, const osl_scatinfos_t*);
osl_interface_t* osl_scatinfos_interface(void) OSL_WARN_UNUSED_RESULT;

#if defined(__cplusplus)
}
#endif

#endif /* define OSL_SCATINFOS_H */
