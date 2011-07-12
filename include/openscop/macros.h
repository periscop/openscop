
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
# define OPENSCOP_MAX_STRING            2048
# define OPENSCOP_MAX_ARRAYS            128

# define OPENSCOP_TYPE_GENERIC          0
# define OPENSCOP_TYPE_STRING           1
# define OPENSCOP_TYPE_CONTEXT	        2
# define OPENSCOP_TYPE_DOMAIN           3
# define OPENSCOP_TYPE_SCATTERING       4
# define OPENSCOP_TYPE_ACCESS	        5
# define OPENSCOP_TYPE_READ             6
# define OPENSCOP_TYPE_WRITE            7
# define OPENSCOP_TYPE_MAY_WRITE        8

# define OPENSCOP_FAKE_ARRAY            "fakearray"

# define OPENSCOP_STRING_UNDEFINED      "UNDEFINED"
# define OPENSCOP_STRING_CONTEXT        "CONTEXT"
# define OPENSCOP_STRING_DOMAIN         "DOMAIN"
# define OPENSCOP_STRING_SCATTERING     "SCATTERING"
# define OPENSCOP_STRING_READ           "READ"
# define OPENSCOP_STRING_WRITE          "WRITE"
# define OPENSCOP_STRING_MAY_WRITE      "MAY_WRITE"

/*+***************************************************************************
 *                               UTILITY MACROS                              *
 *****************************************************************************/

# define OPENSCOP_info(msg)                                 \
         do {                                               \
           fprintf(stderr,"[OpenScop] Info: "msg".\n");     \
         } while (0)

# define OPENSCOP_warning(msg)                              \
         do {                                               \
           fprintf(stderr,"[OpenScop] Warning: "msg".\n");  \
         } while (0)

# define OPENSCOP_error(msg)                                \
         do {                                               \
           fprintf(stderr,"[OpenScop] Error: "msg".\n");    \
           exit(1);                                         \
         } while (0)

# define OPENSCOP_malloc(ptr,type,size)                     \
         do {                                               \
           if (((ptr) = (type)malloc(size)) == NULL)        \
             OPENSCOP_error("memory overflow");             \
         } while (0)

# define OPENSCOP_realloc(ptr,type,size)                    \
         do {                                               \
           if (((ptr) = (type)realloc(ptr,size)) == NULL)   \
             OPENSCOP_error("memory overflow");             \
         } while (0)


/*+***************************************************************************
 *                            OPENSCOP GMP MACROS                            *
 *****************************************************************************/
# ifdef OPENSCOP_INT_T_IS_MP
/* Basic Macros */
#  define OPENSCOP_INT_init(val)                mpz_init(val)
#  define OPENSCOP_INT_assign(v1,v2)            mpz_set(v1,v2)
#  define OPENSCOP_INT_set_si(val,i)            mpz_set_si(val,i)
#  define OPENSCOP_INT_get_si(val)              mpz_get_si(val)
#  define OPENSCOP_INT_init_set_si(val,i)       mpz_init_set_si(val,i)
#  define OPENSCOP_INT_clear(val)               mpz_clear(val)
#  define OPENSCOP_INT_dump(Dst,fmt,val)        \
          do {                                  \
            char *str;                          \
            str = mpz_get_str(0,10,val);        \
            fprintf(Dst,fmt,str);               \
            free(str);                          \
          } while (0)
#  define OPENSCOP_INT_sprint(Dst,fmt,val)      \
          do {                                  \
            char * str;                         \
            str = mpz_get_str(0,10,val);        \
            sprintf(Dst,fmt,str);               \
            free(str);                          \
          } while (0)

/* Boolean operators on 'openscop_int_t' */
#  define OPENSCOP_INT_eq(v1,v2)                (mpz_cmp(v1,v2) == 0)
#  define OPENSCOP_INT_ne(v1,v2)                (mpz_cmp(v1,v2) != 0)

/* Binary operators on 'openscop_int_t' */
#  define OPENSCOP_INT_increment(ref,val)       mpz_add_ui(ref,val,1)
#  define OPENSCOP_INT_addto(ref,val1,val2)     mpz_add(ref,val1,val2)
#  define OPENSCOP_INT_multo(ref,val1,val2)     mpz_mul(ref,val1,val2)
#  define OPENSCOP_INT_add_int(ref,val,vint)    mpz_add_ui(ref,val,(long)vint)
#  define OPENSCOP_INT_subtract(ref,val1,val2)  mpz_sub(ref,val1,val2)
#  define OPENSCOP_INT_oppose(ref,val)          mpz_neg(ref,val)
#  define OPENSCOP_INT_fdiv(ref,n,d)            mpz_fdiv_q(ref,n,d)

/* Conditional operations on 'openscop_int_t' */
#  define OPENSCOP_INT_pos_p(val)               (mpz_sgn(val) >  0)
#  define OPENSCOP_INT_neg_p(val)               (mpz_sgn(val) <  0)
#  define OPENSCOP_INT_zero_p(val)              (mpz_sgn(val) == 0)
#  define OPENSCOP_INT_notzero_p(val)           (mpz_sgn(val) != 0)
#  define OPENSCOP_INT_one_p(val)               (mpz_cmp_si(val,1)  == 0)
#  define OPENSCOP_INT_mone_p(val)              (mpz_cmp_si(val,-1) == 0)
#  define OPENSCOP_INT_divisible(val1,val2)     mpz_divisible_p(val1,val2)

/*+***************************************************************************
 *                         OPENSCOP BASIC TYPES MACROS                       *
 *****************************************************************************/
# else
/* Basic Macros */
#  define OPENSCOP_INT_init(val)                val = 0
#  define OPENSCOP_INT_assign(v1,v2)            v1  = v2
#  define OPENSCOP_INT_set_si(val,i)            val = (openscop_int_t)i
#  define OPENSCOP_INT_get_si(val)              val
#  define OPENSCOP_INT_init_set_si(val,i)       val = (openscop_int_t)i
#  define OPENSCOP_INT_clear(val)               val = 0
#  define OPENSCOP_INT_dump(Dst,fmt,val)        fprintf(Dst,fmt,val)
#  define OPENSCOP_INT_sprint(Dst,fmt,val)      sprintf(Dst,fmt,val)

/* Boolean operators on 'openscop_int_t' */
#  define OPENSCOP_INT_eq(v1,v2)                (v1 == v2)
#  define OPENSCOP_INT_ne(v1,v2)                (v1 != v2)
#  define OPENSCOP_INT_lt(v1,v2)                (v1 < v2)
#  define OPENSCOP_INT_gt(v1,v2)                (v1 > v2)

/* Binary operators on 'openscop_int_t' */
#  define OPENSCOP_INT_increment(ref,val)       ref = val + (openscop_int_t)1
#  define OPENSCOP_INT_addto(ref,val1,val2)     ref = val1 + val2
#  define OPENSCOP_INT_multo(ref,val1,val2)     ref = val1 * val2
#  define OPENSCOP_INT_add_int(ref,val,vint)    ref = val+(openscop_int_t)vint
#  define OPENSCOP_INT_subtract(ref,val1,val2)  ref = val1 - val2
#  define OPENSCOP_INT_oppose(ref,val)          ref = -val
#  define OPENSCOP_INT_fdiv(ref,n,d)            ref = n / d

/* Conditional operations on 'openscop_int_t' */
#  define OPENSCOP_INT_pos_p(val)               OPENSCOP_INT_gt(val,0)
#  define OPENSCOP_INT_neg_p(val)               OPENSCOP_INT_lt(val,0)
#  define OPENSCOP_INT_zero_p(val)              OPENSCOP_INT_eq(val,0)
#  define OPENSCOP_INT_notzero_p(val)           OPENSCOP_INT_ne(val,0)
#  define OPENSCOP_INT_one_p(val)               OPENSCOP_INT_eq(val,1)
#  define OPENSCOP_INT_mone_p(val)              OPENSCOP_INT_eq(val,-1)
#  define OPENSCOP_INT_divisible(val1,val2)     ((val1 % val2) == 0)

# endif

#endif /* define OPENSCOP_MACROS_H */
