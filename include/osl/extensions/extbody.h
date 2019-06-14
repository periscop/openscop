
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                      extensions/extbody.h                        **
     **-----------------------------------------------------------------**
     **                   First version: 07/12/2010                     **
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

#ifndef OSL_EXTBODY_H
#define OSL_EXTBODY_H

#include <stdio.h>

#include <osl/attributes.h>
#include <osl/body.h>
#include <osl/interface.h>
#include <osl/strings.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define OSL_URI_EXTBODY "extbody"

/**
 * The osl_extbody_t structure stores the coordinates of each access in the
 * body. osl_extbody is replaced by the simple body.
 */
struct osl_extbody {
  osl_body_p body;
  size_t nb_access; /**< Nb of access. */
  int* start;       /**< Array of nb_access start. */
  int* length;      /**< Array of nb_access length. */
};
typedef struct osl_extbody osl_extbody_t;
typedef struct osl_extbody* osl_extbody_p;
typedef struct osl_extbody const osl_const_extbody_t;
typedef struct osl_extbody* const osl_extbody_const_p;
typedef struct osl_extbody const* osl_const_extbody_p;
typedef struct osl_extbody const* const osl_const_extbody_const_p;

/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/
void osl_extbody_idump(FILE*, const osl_extbody_t*, int) OSL_NONNULL_ARGS(1);
void osl_extbody_dump(FILE*, const osl_extbody_t*) OSL_NONNULL_ARGS(1);
char* osl_extbody_sprint(const osl_extbody_t*) OSL_WARN_UNUSED_RESULT;

/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/
osl_extbody_t* osl_extbody_sread(char**) OSL_WARN_UNUSED_RESULT;

/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/
osl_extbody_t* osl_extbody_malloc(void) OSL_WARN_UNUSED_RESULT;
void osl_extbody_free(osl_extbody_t*);

/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/
osl_extbody_t* osl_extbody_clone(const osl_extbody_t*) OSL_WARN_UNUSED_RESULT;
int osl_extbody_equal(const osl_extbody_t*, const osl_extbody_t*);
osl_interface_t* osl_extbody_interface(void) OSL_WARN_UNUSED_RESULT;
void osl_extbody_add(osl_extbody_t*, int, int);

#if defined(__cplusplus)
}
#endif

#endif /* define OSL_EXTBODY_H */
