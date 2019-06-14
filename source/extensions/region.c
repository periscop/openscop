
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                      extensions/loop.c                          **
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "osl/extensions/region.h"
#include "osl/macros.h"

static inline void osl_region_idump_indent(FILE* const file, int level);

/*****************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/

void osl_region_idump_indent(FILE* const file, int level) {
  for (int j = 0; j < level; ++j) {
    fprintf(file, "|\t");
  }
}

void osl_region_idump(FILE* const file, const osl_region_t* region, int level) {
  osl_region_idump_indent(file, level);

  if (region != NULL) {
    fprintf(file, "+-- osl_region_t\n");
  } else {
    fprintf(file, "+-- NULL region\n");
  }

  bool first = true;
  size_t count = 1;
  while (region) {
    if (!first) {
      osl_region_idump_indent(file, level);
      fprintf(file, "|   osl_region_t (node %zu)\n", count);
    } else {
      first = 0;
    }

    /* Blank line... */
    osl_region_idump_indent(file, level);
    fprintf(file, "\n");

    /* Location */
    osl_region_idump_indent(file, level);
    fprintf(file, "+--location: %d\n", region->location);

#define _osl_region_idump_text(field)                                \
  do {                                                               \
    osl_region_idump_indent(file, level);                            \
    fprintf(file, "+--%s_type: %d\n", #field, region->field##_type); \
    osl_region_idump_indent(file, level);                            \
    fprintf(file, "+--%s: %s\n", #field,                             \
            region->field ? region->field : "NULL");                 \
  } while (0)

    _osl_region_idump_text(prefix);
    _osl_region_idump_text(suffix);
    _osl_region_idump_text(prelude);
    _osl_region_idump_text(postlude);

#undef _osl_region_idump_text

    ++count;
    region = region->next;
  }

  /* Last line. */
  osl_region_idump_indent(file, level);
  fprintf(file, "\n");
}
void osl_region_dump(FILE* const file, const osl_region_t* region) {
  osl_region_idump(file, region, 0);
}

char* osl_region_sprint(const osl_region_t* region) {
  const size_t count = osl_region_count(region);

  char buffer[OSL_MAX_STRING];
  char* string = NULL;
  size_t step = 0;
  size_t high_water_mark = OSL_MAX_STRING;

  OSL_malloc(string, char*, high_water_mark * sizeof(char));
  string[0] = '\0';

  sprintf(buffer, "# Number of loops\n%d\n", (int)count);
  osl_util_safe_strcat(&string, buffer, &high_water_mark);

  while (region) {
    sprintf(buffer, "# ===========================================\n");
    osl_util_safe_strcat(&string, buffer, &high_water_mark);

    sprintf(buffer, "# Region number %d / %d \n", (int)++step, (int)count);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);

    sprintf(buffer, "# Location \n");
    osl_util_safe_strcat(&string, buffer, &high_water_mark);
    sprintf(buffer, "%d\n", region->location);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);

#define _osl_region_sprint_text(name, field)                   \
  do {                                                         \
    sprintf(buffer, "# %s (if any) \n", name);                 \
    osl_util_safe_strcat(&string, buffer, &high_water_mark);   \
    sprintf(buffer, "%d\n", region->field##_type);             \
    osl_util_safe_strcat(&string, buffer, &high_water_mark);   \
    if (region->field##_type) {                                \
      sprintf(buffer, "%s\n", region->field);                  \
      osl_util_safe_strcat(&string, buffer, &high_water_mark); \
    }                                                          \
  } while (0)

    _osl_region_sprint_text("Prefix", prefix);
    _osl_region_sprint_text("Suffix", suffix);
    _osl_region_sprint_text("Prelude", prelude);
    _osl_region_sprint_text("Postlude", postlude);

#undef _osl_region_sprint_text

    region = region->next;
  }

  OSL_realloc(string, char*, (strlen(string) + 1) * sizeof(char));
  return string;
}

/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/

osl_region_t* osl_region_sread(char** input) {
  if (!input) {
    OSL_debug("no region optional tag");
    return NULL;
  }

  const int count = osl_util_read_int(NULL, input);
  if (!count) return NULL;

  osl_region_t* const output = osl_region_malloc();
  osl_region_t* current = output;
  for (int i = 0; i < count; ++i) {
    current->location = osl_util_read_int(NULL, input);

    current->prefix_type = osl_util_read_int(NULL, input);
    if (current->prefix_type) {
      current->prefix = osl_util_read_line(NULL, input);
    }

    current->suffix_type = osl_util_read_int(NULL, input);
    if (current->suffix_type) {
      current->suffix = osl_util_read_line(NULL, input);
    }

    current->prelude_type = osl_util_read_int(NULL, input);
    if (current->prelude_type) {
      current->prelude = osl_util_read_line(NULL, input);
    }

    current->postlude_type = osl_util_read_int(NULL, input);
    if (current->postlude_type) {
      current->postlude = osl_util_read_line(NULL, input);
    }

    if (i + 1 < count) {
      current->next = osl_region_malloc();
      current = current->next;
    }
  }

  return output;
}

/*****************************************************************************
 *                    Memory allocation/deallocation function                *
 *****************************************************************************/

osl_region_t* osl_region_malloc(void) {
  osl_region_t* const region = malloc(sizeof *region);
  if (!region) {
    fprintf(stderr, "[osl] Error: memory overflow (%s).\n", __func__);
    exit(1);
  }

  region->location = 0;
  region->prefix_type = 0;
  region->suffix_type = 0;
  region->prelude_type = 0;
  region->postlude_type = 0;

  region->prefix = NULL;
  region->suffix = NULL;
  region->prelude = NULL;
  region->postlude = NULL;

  region->next = NULL;

  return region;
}

void osl_region_free(osl_region_t* region) {
  while (region) {
    osl_region_t* const tmp = region;

    /* Free strings. */
    if (region->prefix) free(region->prefix);
    if (region->suffix) free(region->suffix);
    if (region->prelude) free(region->prelude);
    if (region->postlude) free(region->postlude);

    /* Move along. */
    region = region->next;

    /* Do not forget to free the current region. */
    free(tmp);
  }
}

/*****************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/

osl_region_t* osl_region_clone_one(const osl_region_t* source) {
  osl_region_t* clone = osl_region_malloc();

  clone->location = source->location;
  clone->prefix_type = source->prefix_type;
  clone->suffix_type = source->suffix_type;
  clone->prelude_type = source->prelude_type;
  clone->postlude_type = source->postlude_type;
  OSL_strdup(clone->prefix, source->prefix);
  OSL_strdup(clone->suffix, source->suffix);
  OSL_strdup(clone->prelude, source->prelude);
  OSL_strdup(clone->postlude, source->postlude);

  return clone;
}

osl_region_t* osl_region_clone(const osl_region_t* source) {
  if (!source) return NULL;

  /* Clone the first region. */
  osl_region_t* const clone = osl_region_clone_one(source);
  osl_region_t* last = clone;

  /* Clone the remaining regions. */
  const osl_region_t* current = source->next;
  while (current) {
    last->next = osl_region_clone_one(current);
    last = last->next;
    current = current->next;
  }

  return clone;
}

bool osl_region_equal_one(const osl_region_t* r1, const osl_region_t* r2) {
  if (r1 == r2) return 1;

  if ((!r1 && r2) || (r1 && !r2)) return 0;

  /* Both r1 and r2 are non null pointers at this point. */
  bool equal = r1->location == r2->location &&
               r1->prefix_type == r2->prefix_type &&
               r1->suffix_type == r2->suffix_type &&
               r1->prelude_type == r2->prelude_type &&
               r1->postlude_type == r2->postlude_type;
  if (!equal) return equal;

#define _osl_region_equal_one_check_text(text)                     \
  do {                                                             \
    if (r1->text##_type) {                                         \
      equal = r1->text && r2->text && !strcmp(r1->text, r2->text); \
    } else {                                                       \
      equal = !r1->text && !r2->text;                              \
    }                                                              \
    if (!equal) return equal;                                      \
  } while (0)

  _osl_region_equal_one_check_text(prefix);
  _osl_region_equal_one_check_text(suffix);
  _osl_region_equal_one_check_text(prelude);
  _osl_region_equal_one_check_text(postlude);

#undef _osl_region_equal_one_check_text

  return equal;
}

bool osl_region_equal(const osl_region_t* r1, const osl_region_t* r2) {
  bool equal = osl_region_equal_one(r1, r2);

  if (equal)
    return osl_region_equal(r1->next, r2->next);
  else
    return equal;
}

size_t osl_region_count(const osl_region_t* region) {
  size_t count = 0;
  for (const osl_region_t* current = region; current; current = current->next)
    ++count;

  return count;
}

osl_interface_t* osl_region_interface(void) {
  osl_interface_t* const interface = osl_interface_malloc();

  OSL_strdup(interface->URI, OSL_URI_REGION);

  interface->idump = (osl_idump_f)osl_region_idump;
  interface->sprint = (osl_sprint_f)osl_region_sprint;
  interface->sread = (osl_sread_f)osl_region_sread;
  interface->malloc = (osl_malloc_f)osl_region_malloc;
  interface->free = (osl_free_f)osl_region_free;
  interface->clone = (osl_clone_f)osl_region_clone;
  interface->equal = (osl_equal_f)osl_region_equal;

  return interface;
}
