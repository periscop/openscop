
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

#include <stdlib.h>
#include <stdio.h>
#ifdef OSL_GMP_IS_HERE
# include <gmp.h>
#endif

#include <osl/macros.h>
#include <osl/int.h>


/*+***************************************************************************
 *                                Basic Functions                            *
 *****************************************************************************/


/**
 * osl_int_is_precision_supported function:
 * this function returns 1 if the precision provided as parameter is supported
 * by the library and 0 otherwise. Possible values for the precision
 * parameter are OSL_PRECISION_SP for 32 bits (single) precision,
 * OSL_PRECISION_DP for 64 bits (double) precision and OSL_PRECISION_MP for
 * multiple precision.
 * \param[in] precision The precision to check for.
 * \return 1 if the precision is supported, 0 otherwise.
 */
int osl_int_is_precision_supported(int precision) {
  switch (precision) {
    case OSL_PRECISION_SP:
      return 1;
    case OSL_PRECISION_DP:
      return 1;
#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return 1;
#endif
  }

  return 0;
}


/**
 * osl_int_dump_precision function:
 * this function prints in a human readable fashion the precision
 * corresponding to the "precision" parameter.
 * \param[in] file      The file where to print the precision.
 * \param[in] precision The precision to print.
 */
void osl_int_dump_precision(FILE * file, int precision) {
  switch (precision) {
    case OSL_PRECISION_SP:
      fprintf(file, "32 bits");
      break;
    case OSL_PRECISION_DP:
      fprintf(file, "64 bits");
      break;
#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      fprintf(file, "GMP");
      break;
#endif
    default:
      fprintf(file, "unknown precision %d", precision);
  }
}


void osl_int_init(int precision, osl_int_p variable) {
  switch (precision) {
    case OSL_PRECISION_SP:
      variable->sp = 0;
      break;

    case OSL_PRECISION_DP:
      variable->dp = 0;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      OSL_malloc(variable->mp, void*, sizeof(mpz_t)); 
      mpz_init(*((mpz_t*)variable->mp));
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


osl_int_p osl_int_malloc(int precision) {
  osl_int_p variable;

  OSL_malloc(variable, osl_int_p, sizeof(osl_int_t));
  osl_int_init(precision, variable);
  return variable;
}


/**
 * variable = value;
 */
void osl_int_assign(int precision, osl_int_p variable, osl_int_t value) {
  switch (precision) {
    case OSL_PRECISION_SP:
      variable->sp = value.sp;
      break;

    case OSL_PRECISION_DP:
      variable->dp = value.dp;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_set(*((mpz_t*)variable->mp), *((mpz_t*)value.mp));
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * variable = i;
 */
void osl_int_set_si(int precision, osl_int_p variable, int i) {
  switch (precision) {
    case OSL_PRECISION_SP:
      variable->sp = (long int)i;
      break;

    case OSL_PRECISION_DP:
      variable->dp = (long long int)i;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_set_si(*((mpz_t*)variable->mp), i);
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * return value;
 */
int osl_int_get_si(int precision, osl_int_t value) {
  switch (precision) {
    case OSL_PRECISION_SP:
      return value.sp;

    case OSL_PRECISION_DP:
      return (int)value.dp;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return mpz_get_si(*((mpz_t*)value.mp));
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * variable = i; // including initialization for GMP
 */
void osl_int_init_set_si(int precision, osl_int_p variable, int i) {
  switch (precision) {
    case OSL_PRECISION_SP:
      variable->sp = (long int)i;
      break;

    case OSL_PRECISION_DP:
      variable->dp = (long long int)i;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      OSL_malloc(variable->mp, void*, sizeof(mpz_t)); 
      mpz_init_set_si(*((mpz_t*)variable->mp), i);
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * var1 <=> var2;
 */
void osl_int_swap(int precision, osl_int_p var1, osl_int_p var2) {
  switch (precision) {
    case OSL_PRECISION_SP: {
      long int temp = var1->sp;
      var1->sp = var2->sp;
      var2->sp = temp;
      break;
    }

    case OSL_PRECISION_DP: {
      long long int temp = var1->dp;
      var1->dp = var2->dp;
      var2->dp = temp;
      break;
    }

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP: {
      mpz_t temp;
      mpz_init(temp);
      mpz_set(temp, *((mpz_t*)var1->mp));
      mpz_set(*((mpz_t*)var1->mp), *((mpz_t*)var2->mp));
      mpz_set(*((mpz_t*)var2->mp), temp);
      mpz_clear(temp);
      break;
    }
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * variable = 0; // Including cleaning for GMP
 */
void osl_int_clear(int precision, osl_int_p variable) {
  switch (precision) {
    case OSL_PRECISION_SP:
      variable->sp = 0;
      break;

    case OSL_PRECISION_DP:
      variable->dp = 0;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_clear(*((mpz_t*)variable->mp));
      free(variable->mp);
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


void osl_int_free(int precision, osl_int_p variable) {
  osl_int_clear(precision, variable);
  free(variable);
}


/**
 * osl_int_print function:
 * this function displays an integer value into a file (file, possibly stdout).
 * \param file      The file where the integer has to be printed.
 * \param precision The precision of the integer.
 * \param value     The integer element to print.
 */
void osl_int_print(FILE * file, int precision, osl_int_t value) {
  char string[OSL_MAX_STRING];
  
  osl_int_sprint(string, precision, value);
  fprintf(file, "%s", string);
}


/**
 * osl_int_sprint function:
 * this function prints an integer value into a string, it uses the
 * OpenScop Library formats OSL_FMT_* to format the printing.
 * \param string    The string where the integer has to be printed.
 * \param precision The precision of the integer.
 * \param value     The integer element to print.
 */
void osl_int_sprint(char * string, int precision, osl_int_t value) {
  switch (precision) {
    case OSL_PRECISION_SP:
      sprintf(string, OSL_FMT_SP, value.sp);
      break;

    case OSL_PRECISION_DP:
      sprintf(string, OSL_FMT_DP, value.dp);
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP: {
      char * str;
      str = mpz_get_str(0, 10, *((mpz_t*)value.mp)); //TODO: 10 -> #define
      sprintf(string, OSL_FMT_MP, str);
      free(str);
      break;
    }
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * osl_int_sprint_txt function:
 * this function is similar to osl_int_sprintf but it prints the value
 * using OSL_TMT_TXT_* formats.
 * \see osl_int_sprintf
 */
void osl_int_sprint_txt(char * string, int precision, osl_int_t value) {
  switch (precision) {
    case OSL_PRECISION_SP:
      sprintf(string, OSL_FMT_TXT_SP, value.sp);
      break;

    case OSL_PRECISION_DP:
      sprintf(string, OSL_FMT_TXT_DP, value.dp);
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP: {
      char * str;
      str = mpz_get_str(0, 10, *((mpz_t*)value.mp)); //TODO: 10 -> #define
      sprintf(string, OSL_FMT_TXT_MP, str);
      free(str);
      break;
    }
#endif

    default:
      OSL_error("unknown precision");
  }
}


void osl_int_sread(char ** string, int precision, osl_int_p variable) {
  int nb_read = 0;

  switch (precision) {
    case OSL_PRECISION_SP:
      nb_read = sscanf(*string, OSL_FMT_TXT_SP, &(variable->sp));
      if (nb_read == 0)
        OSL_error("failed to read an integer");
      break;

    case OSL_PRECISION_DP:
      nb_read = sscanf(*string, OSL_FMT_TXT_DP, &(variable->dp));
      if (nb_read == 0)
        OSL_error("failed to read an integer");
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP: {
      long long int tmp;
      nb_read = sscanf(*string, OSL_FMT_TXT_DP, &tmp);
      if (nb_read == 0)
        OSL_error("failed to read an integer");
      mpz_set_si(*((mpz_t*)variable->mp), tmp);
      break;
    }
#endif

    default:
      OSL_error("unknown precision");
  }

  // Update the position in the input string.
  *string = *string + nb_read;
}


/*+***************************************************************************
 *                            Arithmetic Operations                          *
 *****************************************************************************/


/**
 * variable <- value + 1;
 */
void osl_int_increment(int precision, osl_int_p variable, osl_int_t value) {
  switch (precision) {
    case OSL_PRECISION_SP:
      variable->sp = value.sp + 1;
      break;

    case OSL_PRECISION_DP:
      variable->dp = value.dp + (long long int)1;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_add_ui(*((mpz_t*)variable->mp), *((mpz_t*)value.mp), 1);
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * variable <- value - 1;
 */
void osl_int_decrement(int precision, osl_int_p variable, osl_int_t value) {
  switch (precision) {
    case OSL_PRECISION_SP:
      variable->sp = value.sp - 1;
      break;

    case OSL_PRECISION_DP:
      variable->dp = value.dp - (long long int)1;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP: {
      mpz_t one;
      mpz_init_set_si(one, 1);
      mpz_sub(*((mpz_t*)variable->mp), *((mpz_t*)value.mp), one);
      mpz_clear(one);
      break;
    }
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * variable <- val1 + val2;
 */
void osl_int_add(int precision,
                 osl_int_p variable, osl_int_t val1, osl_int_t val2) {
  switch (precision) {
    case OSL_PRECISION_SP:
      variable->sp = val1.sp + val2.sp;
      break;

    case OSL_PRECISION_DP:
      variable->dp = val1.dp + val2.dp;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_add(*((mpz_t*)variable->mp), *((mpz_t*)val1.mp), *((mpz_t*)val2.mp));
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * variable <- value + i;
 */
void osl_int_add_si(int precision,
                    osl_int_p variable, osl_int_t value, int i) {
  switch (precision) {
    case OSL_PRECISION_SP:
      variable->sp = value.sp + (long int)i;
      break;

    case OSL_PRECISION_DP:
      variable->dp = value.dp + (long long int)i;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP: {
      mpz_t si;
      mpz_init_set_si(si, i);
      mpz_add(*((mpz_t*)variable->mp), *((mpz_t*)value.mp), si);
      mpz_clear(si);
      break;
    }
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * variable <- val1 * val2;
 */
void osl_int_mul(int precision,
                 osl_int_p variable, osl_int_t val1, osl_int_t val2) {
  switch (precision) {
    case OSL_PRECISION_SP:
      variable->sp = val1.sp * val2.sp;
      break;

    case OSL_PRECISION_DP:
      variable->dp = val1.dp * val2.dp;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_mul(*((mpz_t*)variable->mp), *((mpz_t*)val1.mp), *((mpz_t*)val2.mp));
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * variable <- value * i;
 */
void osl_int_mul_si(int precision,
                    osl_int_p variable, osl_int_t value, int i) {
  switch (precision) {
    case OSL_PRECISION_SP:
      variable->sp = value.sp * (long int)i;
      break;

    case OSL_PRECISION_DP:
      variable->dp = value.dp * (long long int)i;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_mul_si(*((mpz_t*)variable->mp), *((mpz_t*)value.mp), i);
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * variable <- val1 - val2;
 */
void osl_int_sub(int precision,
                 osl_int_p variable, osl_int_t val1, osl_int_t val2) {
  switch (precision) {
    case OSL_PRECISION_SP:
      variable->sp = val1.sp - val2.sp;
      break;

    case OSL_PRECISION_DP:
      variable->dp = val1.dp - val2.dp;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_sub(*((mpz_t*)variable->mp), *((mpz_t*)val1.mp), *((mpz_t*)val2.mp));
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * variable <- -value;
 */
void osl_int_oppose(int precision, osl_int_p variable, osl_int_t value) {
  switch (precision) {
    case OSL_PRECISION_SP:
      variable->sp = -value.sp;
      break;

    case OSL_PRECISION_DP:
      variable->dp = -value.dp;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_neg(*((mpz_t*)variable->mp), *((mpz_t*)value.mp));
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * variable <- | value |;
 */
void osl_int_abs(int precision, osl_int_p variable, osl_int_t value) {
  switch (precision) {
    case OSL_PRECISION_SP:
      variable->sp = (value.sp > 0) ? value.sp : -value.sp;
      break;

    case OSL_PRECISION_DP:
      variable->dp = (value.dp > 0) ? value.dp : -value.dp;
      break;

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      mpz_abs(*((mpz_t*)variable->mp), *((mpz_t*)value.mp));
      break;
#endif

    default:
      OSL_error("unknown precision");
  }
}


/*+***************************************************************************
 *                            Conditional Operations                         *
 *****************************************************************************/


/**
 * (val1 == val2)
 */
int osl_int_eq(int precision, osl_int_t val1, osl_int_t val2) {
  switch (precision) {
    case OSL_PRECISION_SP:
      return (val1.sp == val2.sp);

    case OSL_PRECISION_DP:
      return (val1.dp == val2.dp);

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return (mpz_cmp(*((mpz_t*)val1.mp), *((mpz_t*)val2.mp)) == 0);
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * (val1 != val2)
 */
int osl_int_ne(int precision, osl_int_t val1, osl_int_t val2) {
  return !osl_int_eq(precision, val1, val2);
}


/**
 * (value > 0)
 */
int osl_int_pos(int precision, osl_int_t value) {
  switch (precision) {
    case OSL_PRECISION_SP:
      return (value.sp > 0);

    case OSL_PRECISION_DP:
      return (value.dp > 0);

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return (mpz_sgn(*((mpz_t*)value.mp)) > 0);
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * (value < 0)
 */
int osl_int_neg(int precision, osl_int_t value) {
  switch (precision) {
    case OSL_PRECISION_SP:
      return (value.sp < 0);

    case OSL_PRECISION_DP:
      return (value.dp < 0);

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return (mpz_sgn(*((mpz_t*)value.mp)) < 0);
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * (value == 0)
 */
int osl_int_zero(int precision, osl_int_t value) {
  switch (precision) {
    case OSL_PRECISION_SP:
      return (value.sp == 0);

    case OSL_PRECISION_DP:
      return (value.dp == 0);

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return (mpz_sgn(*((mpz_t*)value.mp)) == 0);
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * (value == 1)
 */
int osl_int_one(int precision, osl_int_t value) {
  switch (precision) {
    case OSL_PRECISION_SP:
      return (value.sp == (long int)1);

    case OSL_PRECISION_DP:
      return (value.dp == (long long int)1);

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return (mpz_cmp_si(*((mpz_t*)value.mp), 1) == 0);
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * (value == -1)
 */
int osl_int_mone(int precision, osl_int_t value) {
  switch (precision) {
    case OSL_PRECISION_SP:
      return (value.sp == (long int)-1);

    case OSL_PRECISION_DP:
      return (value.dp == (long long int)-1);

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return (mpz_cmp_si(*((mpz_t*)value.mp), -1) == 0);
#endif

    default:
      OSL_error("unknown precision");
  }
}


/**
 * ((val1 % val2) == 0)
 */
int osl_int_divisible(int precision, osl_int_t val1, osl_int_t val2) {
  switch (precision) {
    case OSL_PRECISION_SP:
      return ((val1.sp % val2.sp) == 0);

    case OSL_PRECISION_DP:
      return ((val1.dp % val2.dp) == 0);

#ifdef OSL_GMP_IS_HERE
    case OSL_PRECISION_MP:
      return mpz_divisible_p(*((mpz_t*)val1.mp), *((mpz_t*)val2.mp));
#endif

    default:
      OSL_error("unknown precision");
  }
}
