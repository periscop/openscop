
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                             int.c                               **
     **-----------------------------------------------------------------**
     **                   First version: 18/07/2011                     **
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

# include <stdlib.h>
# include <stdio.h>
# include <openscop/int.h>


/*+***************************************************************************
 *                                Basic Functions                            *
 *****************************************************************************/


/**
 * openscop_int_dump_precision function:
 * this function prints in a human readable fashion the precision
 * corresponding to the "precision" parameter.
 * \param[in] file      The file where to print the precision.
 * \param[in] precision The precision to print.
 */
void openscop_int_dump_precision(FILE * file, int precision) {

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      fprintf(file, "32 bits");
      break;
    case OPENSCOP_PRECISION_DP:
      fprintf(file, "64 bits");
      break;
#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      fprintf(file, "GMP");
      break;
#endif
    default:
      fprintf(file, "unknown precision %d", precision);
  }
}


int openscop_int_sizeof(int precision) {
  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      return sizeof(long int);

    case OPENSCOP_PRECISION_DP:
      return sizeof(long long int);

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      return sizeof(mpz_t);
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


void * openscop_int_address(int precision, void * base, int offset) {
  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      return (long int *)base + offset;

    case OPENSCOP_PRECISION_DP:
      return (long long int *)base + offset;

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      return (mpz_t *)base + offset;
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


void openscop_int_init(int precision, void * value_base, int value_offset) {
  void * value = openscop_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      *(long int *)value = 0;
      break;

    case OPENSCOP_PRECISION_DP:
      *(long long int *)value = 0;
      break;

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      mpz_init(*(mpz_t *)value);
      break;
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


void * openscop_int_malloc(int precision) {
  void * value;

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      value = malloc(sizeof(long int));
      break;

    case OPENSCOP_PRECISION_DP:
      value = malloc(sizeof(long long int));
      *(long long int *)value = 0;
      break;

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      value = malloc(sizeof(mpz_t));
      break;
#endif

    default:
      OPENSCOP_error("unknown precision");
  }

  openscop_int_init(precision, value, 0);
  return value;
}


void openscop_int_assign(int precision,
                         void * val1_base, int val1_offset,
                         void * val2_base, int val2_offset) {
  void * val1 = openscop_int_address(precision, val1_base, val1_offset);
  void * val2 = openscop_int_address(precision, val2_base, val2_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      *(long int *)val1 = *(long int *)val2;
      break;

    case OPENSCOP_PRECISION_DP:
      *(long long int *)val1 = *(long long int *)val2;
      break;

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      mpz_set(*(mpz_t *)val1, *(mpz_t *)val2);
      break;
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


void openscop_int_set_si(int precision, void * value_base, int value_offset,
                         int i) {
  void * value = openscop_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      *(long int *)value = (long int)i;
      break;

    case OPENSCOP_PRECISION_DP:
      *(long long int *)value = (long long int)i;
      break;

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      mpz_set_si(*(mpz_t *)value, i);
      break;
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


int openscop_int_get_si(int precision, void * value_base, int value_offset) {
  void * value = openscop_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      return *(int *)value;

    case OPENSCOP_PRECISION_DP:
      return *(int *)value;

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      return mpz_get_si(*(mpz_t *)value);
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


void openscop_int_init_set_si(int precision,
                              void * value_base, int value_offset, int i) {
  void * value = openscop_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      *(long int *)value = (long int)i;
      break;

    case OPENSCOP_PRECISION_DP:
      *(long long int *)value = (long long int)i;
      break;

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      mpz_init_set_si(*(mpz_t *)value, i);
      break;
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


void openscop_int_clear(int precision, void * value_base, int value_offset) {
  void * value = openscop_int_address(precision, value_base, value_offset);
  
  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      *(long int *)value = 0;
      break;

    case OPENSCOP_PRECISION_DP:
      *(long long int *)value = 0;
      break;

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      mpz_clear(*(mpz_t *)value);
      break;
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


/**
 * openscop_int_print function:
 * this function displays an integer value into a file (file, possibly stdout).
 * \param file      The file where the integer has to be printed.
 * \param precision The precision of the integer.
 * \param value     Address of the integer value.
 */
void openscop_int_print(FILE * file, int precision,
                        void * value_base, int value_offset) {
  void * value = openscop_int_address(precision, value_base, value_offset);
            
  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      fprintf(file, OPENSCOP_FMT_SP, *(long int *)value);
      break;

    case OPENSCOP_PRECISION_DP:
      fprintf(file, OPENSCOP_FMT_DP, *(long long int *)value);
      break;

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP: {
      char * str;
      str = mpz_get_str(0, 10, *(mpz_t *)value); //TODO: 10 -> #define
      fprintf(file, OPENSCOP_FMT_MP, str);
      free(str);
      break;
    }
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


/**
 * openscop_int_sprint function:
 * this function prints an integer value into a string.
 * \param string    The string where the integer has to be printed.
 * \param precision The precision of the integer.
 * \param value     Address of the integer value.
 */
void openscop_int_sprint(char * string, int precision,
                         void * value_base, int value_offset) {
  void * value = openscop_int_address(precision, value_base, value_offset);
            
  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      sprintf(string, OPENSCOP_FMT_SP, *(long int *)value);
      break;

    case OPENSCOP_PRECISION_DP:
      sprintf(string, OPENSCOP_FMT_DP, *(long long int *)value);
      break;

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP: {
      char * str;
      str = mpz_get_str(0, 10, *(mpz_t *)value); //TODO: 10 -> #define
      sprintf(string, OPENSCOP_FMT_MP, str);
      free(str);
      break;
    }
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


void openscop_int_sread(char * string, int precision,
                        void * value_base, int value_offset) {
  void * value = openscop_int_address(precision, value_base, value_offset);
  int nb_read;

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      nb_read = sscanf(string, OPENSCOP_FMT_TXT_SP, (long int *)value);
      if (nb_read == 0)
        OPENSCOP_error("failed to read an integer");
      break;

    case OPENSCOP_PRECISION_DP:
      nb_read = sscanf(string, OPENSCOP_FMT_TXT_DP, (long long int *)value);
      if (nb_read == 0)
        OPENSCOP_error("failed to read an integer");
      break;

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP: {
      long long int tmp;
      nb_read = sscanf(string, OPENSCOP_FMT_TXT_DP, &tmp);
      if (nb_read == 0)
        OPENSCOP_error("failed to read an integer");
      mpz_set_si(*(mpz_t *)value, tmp);
      break;
    }
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


/*+***************************************************************************
 *                            Arithmetic Operations                          *
 *****************************************************************************/


void openscop_int_increment(int precision,
                            void * result_base, int result_offset,
                            void * value_base,  int value_offset) {
  void * result = openscop_int_address(precision, result_base, result_offset);
  void * value  = openscop_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      *(long int *)result = *(long int *)value + (long int)1;
      break;

    case OPENSCOP_PRECISION_DP:
      *(long long int *)result = *(long long int *)value + (long long int)1;
      break;

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      mpz_add_ui(*(mpz_t *)result, *(mpz_t *)value, 1);
      break;
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


void openscop_int_add(int precision,
                      void * result_base, int result_offset,
                      void * val1_base,   int val1_offset,
                      void * val2_base,   int val2_offset) {
  void * result = openscop_int_address(precision, result_base, result_offset);
  void * val1   = openscop_int_address(precision, val1_base, val1_offset);
  void * val2   = openscop_int_address(precision, val2_base, val2_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      *(long int *)result = *(long int *)val1 + *(long int *)val2;
      break;

    case OPENSCOP_PRECISION_DP:
      *(long long int *)result = *(long long int *)val1 +
                                 *(long long int *)val2;
      break;

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      mpz_add(*(mpz_t *)result, *(mpz_t *)val1, *(mpz_t *)val2);
      break;
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


void openscop_int_add_ui(int precision,
                         void * result_base, int result_offset,
                         void * value_base,  int value_offset, int i) {
  void * result = openscop_int_address(precision, result_base, result_offset);
  void * value  = openscop_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      *(long int *)result = *(long int *)value + (long int)i;
      break;

    case OPENSCOP_PRECISION_DP:
      *(long long int *)result = *(long long int *)value + (long long int)i;
      break;

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      mpz_add_ui(*(mpz_t *)result, *(mpz_t *)value, (long int)i);
      break;
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


void openscop_int_mul(int precision,
                      void * result_base, int result_offset,
                      void * val1_base,   int val1_offset,
                      void * val2_base,   int val2_offset) {
  void * result = openscop_int_address(precision, result_base, result_offset);
  void * val1   = openscop_int_address(precision, val1_base, val1_offset);
  void * val2   = openscop_int_address(precision, val2_base, val2_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      *(long int *)result = *(long int *)val1 * *(long int *)val2;
      break;

    case OPENSCOP_PRECISION_DP:
      *(long long int *)result = *(long long int *)val1 *
                                 *(long long int *)val2;
      break;

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      mpz_mul(*(mpz_t *)result, *(mpz_t *)val1, *(mpz_t *)val2);
      break;
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


void openscop_int_mul_si(int precision,
                         void * result_base, int result_offset,
                         void * value_base,  int value_offset, int i) {
  void * result = openscop_int_address(precision, result_base, result_offset);
  void * value  = openscop_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      *(long int *)result = *(long int *)value * (long int)i;
      break;

    case OPENSCOP_PRECISION_DP:
      *(long long int *)result = *(long long int *)value * (long long int)i;
      break;

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      mpz_mul_si(*(mpz_t *)result, *(mpz_t *)value, i);
      break;
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


void openscop_int_sub(int precision,
                      void * result_base, int result_offset,
                      void * val1_base,   int val1_offset,
                      void * val2_base,   int val2_offset) {
  void * result = openscop_int_address(precision, result_base, result_offset);
  void * val1   = openscop_int_address(precision, val1_base, val1_offset);
  void * val2   = openscop_int_address(precision, val2_base, val2_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      *(long int *)result = *(long int *)val1 - *(long int *)val2;
      break;

    case OPENSCOP_PRECISION_DP:
      *(long long int *)result = *(long long int *)val1 -
                                 *(long long int *)val2;
      break;

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      mpz_sub(*(mpz_t *)result, *(mpz_t *)val1, *(mpz_t *)val2);
      break;
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


void openscop_int_oppose(int precision,
                         void * result_base, int result_offset,
                         void * value_base,  int value_offset) {
  void * result = openscop_int_address(precision, result_base, result_offset);
  void * value  = openscop_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      *(long int *)result = -*(long int *)value;
      break;

    case OPENSCOP_PRECISION_DP:
      *(long long int *)result = -*(long long int *)value;
      break;

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      mpz_neg(*(mpz_t *)result, *(mpz_t *)value);
      break;
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


/*+***************************************************************************
 *                            Conditional Operations                         *
 *****************************************************************************/


int openscop_int_eq(int precision,
                    void * val1_base, int val1_offset,
                    void * val2_base, int val2_offset) {
  void * val1 = openscop_int_address(precision, val1_base, val1_offset);
  void * val2 = openscop_int_address(precision, val2_base, val2_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      return (*(long int *)val1 == *(long int *)val2);

    case OPENSCOP_PRECISION_DP:
      return (*(long long int *)val1 == *(long long int *)val2);

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      return (mpz_cmp(*(mpz_t *)val1, *(mpz_t *)val2) == 0);
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


int openscop_int_ne(int precision,
                    void * val1_base, int val1_offset,
                    void * val2_base, int val2_offset) {
  void * val1 = openscop_int_address(precision, val1_base, val1_offset);
  void * val2 = openscop_int_address(precision, val2_base, val2_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      return (*(long int *)val1 != *(long int *)val2);

    case OPENSCOP_PRECISION_DP:
      return (*(long long int *)val1 != *(long long int *)val2);

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      return (mpz_cmp(*(mpz_t *)val1, *(mpz_t *)val2) != 0);
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


int openscop_int_pos(int precision, void * value_base, int value_offset) {
  void * value = openscop_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      return (*(long int *)value > 0);

    case OPENSCOP_PRECISION_DP:
      return (*(long long int *)value > 0);

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      return (mpz_sgn(*(mpz_t *)value) > 0);
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


int openscop_int_neg(int precision, void * value_base, int value_offset) {
  void * value = openscop_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      return (*(long int *)value < 0);

    case OPENSCOP_PRECISION_DP:
      return (*(long long int *)value < 0);

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      return (mpz_sgn(*(mpz_t *)value) < 0);
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


int openscop_int_zero(int precision, void * value_base, int value_offset) {
  void * value = openscop_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      return (*(long int *)value == 0);

    case OPENSCOP_PRECISION_DP:
      return (*(long long int *)value == 0);

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      return (mpz_sgn(*(mpz_t *)value) == 0);
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


int openscop_int_notzero(int precision, void * value_base, int value_offset) {
  void * value = openscop_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      return (*(long int *)value != 0);

    case OPENSCOP_PRECISION_DP:
      return (*(long long int *)value != 0);

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      return (mpz_sgn(*(mpz_t *)value) != 0);
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


int openscop_int_one(int precision, void * value_base, int value_offset) {
  void * value = openscop_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      return (*(long int *)value == (long int)1);

    case OPENSCOP_PRECISION_DP:
      return (*(long long int *)value == (long long int)1);

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      return (mpz_cmp_si(*(mpz_t *)value, 1) == 0);
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


int openscop_int_mone(int precision, void * value_base, int value_offset) {
  void * value = openscop_int_address(precision, value_base, value_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      return (*(long int *)value == (long int)-1);

    case OPENSCOP_PRECISION_DP:
      return (*(long long int *)value == (long long int)-1);

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      return (mpz_cmp_si(*(mpz_t *)value, -1) == 0);
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}


int openscop_int_divisible(int precision,
                           void * val1_base, int val1_offset,
                           void * val2_base, int val2_offset) {
  void * val1 = openscop_int_address(precision, val1_base, val1_offset);
  void * val2 = openscop_int_address(precision, val2_base, val2_offset);

  switch (precision) {
    case OPENSCOP_PRECISION_SP:
      return ((*(long int *)val1 % *(long int *)val2) == 0);

    case OPENSCOP_PRECISION_DP:
      return ((*(long long int *)val1 % *(long long int *)val2) == 0);

#ifdef OPENSCOP_GMP_IS_HERE
    case OPENSCOP_PRECISION_MP:
      return mpz_divisible_p(*(mpz_t *)val1, *(mpz_t *)val2);
#endif

    default:
      OPENSCOP_error("unknown precision");
  }
}
