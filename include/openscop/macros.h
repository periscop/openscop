
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                           macros.h                              **
     **-----------------------------------------------------------------**
     **                   First version: 30/04/2008                     **
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


#ifndef OPENSCOP_MACROS_H
# define OPENSCOP_MACROS_H


# if defined(OPENSCOP_INT_T_IS_LONGLONG)
#  define OPENSCOP_FMT     "%4lld"
#  define OPENSCOP_FMT_TXT "%lld"
#  define openscop_int_t long long

# elif defined(OPENSCOP_INT_T_IS_LONG)
#  define OPENSCOP_FMT     "%4ld"
#  define OPENSCOP_FMT_TXT "%ld"
#  define openscop_int_t long int

# elif defined(OPENSCOP_INT_T_IS_MP)  /* GNUMP */
#include <gmp.h>
#  define OPENSCOP_FMT     "%4s"
#  define OPENSCOP_FMT_TXT "%s"
#  define openscop_int_t mpz_t

# else
#  error Define OPENSCOP_INT_T_IS_xxx to use this file.

# endif

# define OPENSCOP_DEBUG	                0    // 1 for debug mode, 0 otherwise.
# define OPENSCOP_BACKEND_C             0
# define OPENSCOP_BACKEND_FORTRAN       1
# define OPENSCOP_UNDEFINED             -1
# define OPENSCOP_MAX_STRING		2048
# define OPENSCOP_MAX_ARRAYS		128
# define OPENSCOP_TYPE_BARE	        0
# define OPENSCOP_TYPE_ITERATOR	        1
# define OPENSCOP_TYPE_PARAMETER        2
# define OPENSCOP_TYPE_ARRAY            3
# define OPENSCOP_TYPE_FUNCTION	        4
# define OPENSCOP_TYPE_CONTEXT	        6
# define OPENSCOP_TYPE_DOMAIN           7
# define OPENSCOP_TYPE_SCATTERING       8
# define OPENSCOP_TYPE_ACCESS	        9
# define OPENSCOP_TYPE_UNKNOWN	        10
# define OPENSCOP_FAKE_ARRAY            "fakearray"

# define OPENSCOP_TAG_ARRAY_START       "<arrays>"
# define OPENSCOP_TAG_ARRAY_STOP        "</arrays>"


/*+***************************************************************************
 *                            OPENSCOP GMP MACROS                            *
 *****************************************************************************/
# ifdef OPENSCOP_INT_T_IS_MP
/* Basic Macros */
#  define SCOPINT_init(val)                (mpz_init((val)))
#  define SCOPINT_assign(v1,v2)            (mpz_set((v1),(v2)))
#  define SCOPINT_set_si(val,i)            (mpz_set_si((val),(i)))
#  define SCOPINT_get_si(val)              (mpz_get_si((val)))
#  define SCOPINT_init_set_si(val,i)       (mpz_init_set_si((val),(i)))
#  define SCOPINT_clear(val)               (mpz_clear((val)))
#  define SCOPINT_print(Dst,fmt,val)       { char *str; \
                                        str = mpz_get_str(0,10,(val)); \
                                        fprintf((Dst),(fmt),str); free(str); \
                                        }
#  define SCOPINT_sprint(Dst,fmt,val)      { char * str; \
                                        str = mpz_get_str(0,10,(val)); \
                                        sprintf((Dst),(fmt),str); free(str); \
                                        }

/* Boolean operators on 'openscop_int_t' */
#  define SCOPINT_eq(v1,v2)                (mpz_cmp((v1),(v2)) == 0)
#  define SCOPINT_ne(v1,v2)                (mpz_cmp((v1),(v2)) != 0)

/* Binary operators on 'openscop_int_t' */
#  define SCOPINT_increment(ref,val)       (mpz_add_ui((ref),(val),1))
#  define SCOPINT_addto(ref,val1,val2)     (mpz_add((ref),(val1),(val2)))
#  define SCOPINT_multo(ref,val1,val2)     (mpz_mul((ref),(val1),(val2)))
#  define SCOPINT_add_int(ref,val,vint)    (mpz_add_ui((ref),(val),(long)(vint)))
#  define SCOPINT_subtract(ref,val1,val2)  (mpz_sub((ref),(val1),(val2)))
#  define SCOPINT_oppose(ref,val)          (mpz_neg((ref),(val)))

/* Conditional operations on 'openscop_int_t' */
#  define SCOPINT_pos_p(val)               (mpz_sgn(val) >  0)
#  define SCOPINT_neg_p(val)               (mpz_sgn(val) <  0)
#  define SCOPINT_zero_p(val)              (mpz_sgn(val) == 0)
#  define SCOPINT_notzero_p(val)           (mpz_sgn(val) != 0)
#  define SCOPINT_one_p(val)               (mpz_cmp_si(val,1)  == 0)
#  define SCOPINT_mone_p(val)              (mpz_cmp_si(val,-1) == 0)

/*+***************************************************************************
 *                         OPENSCOP BASIC TYPES MACROS                       *
 *****************************************************************************/
# else
/* Basic Macros */
#  define SCOPINT_init(val)                ((val) = 0)
#  define SCOPINT_assign(v1,v2)            ((v1)  = (v2))
#  define SCOPINT_set_si(val,i)            ((val) = (openscop_int_t)(i))
#  define SCOPINT_get_si(val)              ((val))
#  define SCOPINT_init_set_si(val,i)       ((val) = (openscop_int_t)(i))
#  define SCOPINT_clear(val)               ((val) = 0)
#  define SCOPINT_print(Dst,fmt,val)       (fprintf((Dst),(fmt),(val)))
#  define SCOPINT_sprint(Dst,fmt,val)      (sprintf((Dst),(fmt),(val)))

/* Boolean operators on 'openscop_int_t' */
#  define SCOPINT_eq(v1,v2)                ((v1)==(v2))
#  define SCOPINT_ne(v1,v2)                ((v1)!=(v2))
#  define SCOPINT_lt(v1,v2)                ((v1)<(v2))
#  define SCOPINT_gt(v1,v2)                ((v1)>(v2))

/* Binary operators on 'openscop_int_t' */
#  define SCOPINT_increment(ref,val)       ((ref) = (val)+(openscop_int_t)(1))
#  define SCOPINT_addto(ref,val1,val2)     ((ref) = (val1)+(val2))
#  define SCOPINT_multo(ref,val1,val2)     ((ref) = (val1)*(val2))
#  define SCOPINT_add_int(ref,val,vint)    ((ref) = (val)+(openscop_int_t)(vint))
#  define SCOPINT_subtract(ref,val1,val2)  ((ref) = (val1)-(val2))
#  define SCOPINT_oppose(ref,val)          ((ref) = (-(val)))

/* Conditional operations on 'openscop_int_t' */
#  define SCOPINT_pos_p(val)               SCOPINT_gt(val,0)
#  define SCOPINT_neg_p(val)               SCOPINT_lt(val,0)
#  define SCOPINT_zero_p(val)              SCOPINT_eq(val,0)
#  define SCOPINT_notzero_p(val)           SCOPINT_ne(val,0)
#  define SCOPINT_one_p(val)               SCOPINT_eq(val,1)
#  define SCOPINT_mone_p(val)              SCOPINT_eq(val,-1)

# endif

#endif /* define OPENSCOP_MACROS_H */
