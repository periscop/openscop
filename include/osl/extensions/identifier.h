
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                    extensions/identifier.h                      **
     **-----------------------------------------------------------------**
     **                   First version: 30/12/2014                     **
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

#ifndef OSL_IDENTIFIER_H
# define OSL_IDENTIFIER_H

# include <stdio.h>
# include <osl/interface.h>
# include <osl/scop.h>

# if defined(__cplusplus)
extern "C"
  {
# endif

# define OSL_URI_IDENTIFIER     "identifier"

/**
 * Stores an integer identifier of any OpenScop object having extensions.  The
 * generation and preservatio of unique identifiers must be ensured by the user
 * of the extension.
 */
struct osl_identifier {
  int id;
};
typedef struct osl_identifier   osl_identifier_t;
typedef struct osl_identifier * osl_identifier_p;

/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/
void             osl_identifier_idump(FILE *, osl_identifier_p, int);
void             osl_identifier_dump(FILE *, osl_identifier_p);
char *           osl_identifier_sprint(osl_identifier_p);

/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/
osl_identifier_p osl_identifier_sread(char **);

/*+***************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/
osl_identifier_p osl_identifier_malloc();
void             osl_identifier_free(osl_identifier_p);

/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/
osl_identifier_p osl_identifier_clone(osl_identifier_p);
int              osl_identifier_equal(osl_identifier_p, osl_identifier_p);
osl_interface_p  osl_identifier_interface();
void             osl_identifier_generate(osl_scop_p);
int              osl_identifier_is_unique(osl_scop_p);
osl_identifier_p osl_identifier_generate_one(osl_scop_p);
int              osl_identifier_statements_equal(osl_statement_p,
                                                 osl_statement_p);
osl_statement_p  osl_identifier_statement_lookup(osl_statement_p,
                                                 osl_identifier_p);

# if defined(__cplusplus)
  }
# endif

#endif // defined OSL_IDENTIFIER_H

