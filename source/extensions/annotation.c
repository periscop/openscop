/******************************************************************************
 **                            OpenScop Library                              **
 **--------------------------------------------------------------------------**
 **                         extensions/annotation.c                          **
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "osl/extensions/annotation.h"
#include "osl/macros.h"

static inline void osl_annotation_idump_indent(FILE* const file, int level);

static void osl_annotation_text_init(osl_annotation_text_t* text);
static void osl_annotation_text_clean(osl_annotation_text_t* text);

static osl_annotation_text_t osl_annotation_text_clone(
    const osl_annotation_text_t* source);
static bool osl_annotation_text_equal(const osl_annotation_text_t* t1,
                                      const osl_annotation_text_t* t2);
static int osl_annotation_text_append(osl_annotation_text_t* text,
                                      int line_type, char* line);
static void osl_annotation_text_idump(FILE* file,
                                      const osl_annotation_text_t* text,
                                      int level);
/******************************************************************************
 * osl_annotation_text_t functions                                            *
 ******************************************************************************/

int osl_annotation_text_append(osl_annotation_text_t* text, int line_type,
                               char* line) {
  const size_t count = text->count + 1;

  char** lines = realloc(text->lines, count * sizeof *lines);
  if (!lines)
    return 1;

  int* types = realloc(text->types, count * sizeof *types);
  if (!types)
    return 1;

  text->lines = lines;
  text->types = types;

  text->lines[text->count] = line;
  text->types[text->count] = line_type;
  text->count = count;

  return 0;
}

void osl_annotation_text_idump(FILE* const file,
                               const osl_annotation_text_t* text, int level) {
  for (size_t i = 0; i < text->count; ++i) {
    osl_annotation_idump_indent(file, level);
    fprintf(file, "+--type %zu: %d\n", i, text->types[i]);
    fprintf(file, "+--line %zu: %s\n", i, text->lines[i]);
  }
}

osl_annotation_text_t osl_annotation_text_clone(
    const osl_annotation_text_t* source) {
  osl_annotation_text_t destination = {
      .count = 0,
      .types = 0,
      .lines = 0,
  };
  for (size_t i = 0; i < source->count; ++i) {
    char* line = strdup(source->lines[i]);
    osl_annotation_text_append(&destination, source->types[i], line);
  }
  return destination;
}

void osl_annotation_text_init(osl_annotation_text_t* text) {
  text->count = 0;
  text->types = 0;
  text->lines = 0;
}

void osl_annotation_text_clean(osl_annotation_text_t* text) {
  if (text->lines) {
    for (size_t i = 0; i < text->count; ++i) {
      if (text->lines[i])
        free(text->lines[i]);
    }
    free(text->lines);
  }
  if (text->types) {
    free(text->types);
  }
}

bool osl_annotation_text_equal(const osl_annotation_text_t* t1,
                               const osl_annotation_text_t* t2) {
  if (t1 == t2)
    return true;

  if ((t1 && !t2) || (!t1 && t2) || (t1->count != t2->count)) {
    return false;
  }

  bool equal = true;
  for (size_t i = 0; equal && i < t1->count; ++i) {
    if (t1->types[i] != t2->types[i] || strcmp(t1->lines[i], t2->lines[i])) {
      equal = false;
    }
  }

  return equal;
}

void osl_annotation_append_prefix(osl_annotation_t* annotation, int prefix_type,
                                  char* prefix) {
  osl_annotation_text_append(&annotation->prefix, prefix_type, prefix);
}

void osl_annotation_append_suffix(osl_annotation_t* annotation, int suffix_type,
                                  char* suffix) {
  osl_annotation_text_append(&annotation->suffix, suffix_type, suffix);
}

/******************************************************************************
 * Structure display functions                                                *
 ******************************************************************************/

void osl_annotation_idump_indent(FILE* const file, int level) {
  for (int j = 0; j < level; ++j) {
    fprintf(file, "|\t");
  }
}

void osl_annotation_idump(FILE* const file, const osl_annotation_t* annotation,
                          int level) {
  osl_annotation_idump_indent(file, level);

  if (annotation != NULL) {
    fprintf(file, "+-- osl_annotation_t\n");
  } else {
    fprintf(file, "+-- NULL annotation\n");
  }

  /* Blank line... */
  osl_annotation_idump_indent(file, level);
  fprintf(file, "\n");

  osl_annotation_text_idump(file, &annotation->prefix, level + 2);
  osl_annotation_text_idump(file, &annotation->suffix, level + 2);

  /* Last line. */
  osl_annotation_idump_indent(file, level);
  fprintf(file, "\n");
}
void osl_annotation_dump(FILE* const file, const osl_annotation_t* annotation) {
  osl_annotation_idump(file, annotation, 0);
}

char* osl_annotation_sprint(const osl_annotation_t* annotation) {
  char buffer[OSL_MAX_STRING];
  char* string = NULL;
  size_t high_water_mark = OSL_MAX_STRING;

  OSL_malloc(string, char*, high_water_mark * sizeof(char));
  string[0] = '\0';

  sprintf(buffer, "# ===========================================\n");
  osl_util_safe_strcat(&string, buffer, &high_water_mark);

#define _osl_annotation_sprint_text(name, field)               \
  do {                                                         \
    sprintf(buffer, "# %s count \n", name);                    \
    osl_util_safe_strcat(&string, buffer, &high_water_mark);   \
    sprintf(buffer, "%d\n", (int)annotation->field.count);     \
    osl_util_safe_strcat(&string, buffer, &high_water_mark);   \
    sprintf(buffer, "# %s lines (if any)\n", name);            \
    osl_util_safe_strcat(&string, buffer, &high_water_mark);   \
    for (size_t i = 0; i < annotation->field.count; ++i) {     \
      sprintf(buffer, "%d ", annotation->field.types[i]);      \
      osl_util_safe_strcat(&string, buffer, &high_water_mark); \
      sprintf(buffer, "%s\n", annotation->field.lines[i]);     \
      osl_util_safe_strcat(&string, buffer, &high_water_mark); \
    }                                                          \
  } while (0)

  _osl_annotation_sprint_text("Prefix", prefix);
  _osl_annotation_sprint_text("Suffix", suffix);

#undef _osl_annotation_sprint_text

  OSL_realloc(string, char*, (strlen(string) + 1) * sizeof(char));
  return string;
}

/******************************************************************************
 * Reading functions                                                          *
 ******************************************************************************/

osl_annotation_t* osl_annotation_sread(char** input) {
  if (!input) {
    OSL_debug("no annotation optional tag");
    return NULL;
  }

  osl_annotation_t* const output = osl_annotation_malloc();

#define osl_annotation_sread_text(field)                           \
  do {                                                             \
    size_t count = (size_t)osl_util_read_int(NULL, input);         \
    for (size_t j = 0; j < count; ++j) {                           \
      const int line_type = osl_util_read_int(NULL, input);        \
      char* const line = osl_util_read_line(NULL, input);          \
      osl_annotation_text_append(&output->field, line_type, line); \
    }                                                              \
  } while (0)

  osl_annotation_sread_text(prefix);
  osl_annotation_sread_text(suffix);

  return output;
}

/******************************************************************************
 * Memory allocation/deallocation functions                                   *
 ******************************************************************************/

osl_annotation_t* osl_annotation_malloc(void) {
  osl_annotation_t* const annotation = malloc(sizeof *annotation);
  if (!annotation) {
    fprintf(stderr, "[osl] Error: memory overflow (%s).\n", __func__);
    exit(1);
  }

  osl_annotation_text_init(&annotation->prefix);
  osl_annotation_text_init(&annotation->suffix);

  return annotation;
}

void osl_annotation_free(osl_annotation_t* annotation) {
  osl_annotation_text_clean(&annotation->prefix);
  osl_annotation_text_clean(&annotation->suffix);
  free(annotation);
}

/*****************************************************************************
 * Processing functions                                                      *
 *****************************************************************************/

osl_annotation_t* osl_annotation_clone(const osl_annotation_t* const source) {
  osl_annotation_t* const clone = osl_annotation_malloc();

  clone->prefix = osl_annotation_text_clone(&source->prefix);
  clone->suffix = osl_annotation_text_clone(&source->suffix);

  return clone;
}

bool osl_annotation_equal(const osl_annotation_t* const r1,
                          const osl_annotation_t* const r2) {
  if (r1 == r2)
    return 1;

  if ((!r1 && r2) || (r1 && !r2))
    return 0;

  /* Both r1 and r2 are non null pointers at this point. */
  bool equal = osl_annotation_text_equal(&r1->prefix, &r2->prefix) &&
               osl_annotation_text_equal(&r1->suffix, &r2->suffix);

  return equal;
}

osl_interface_t* osl_annotation_interface(void) {
  osl_interface_t* const interface = osl_interface_malloc();

  OSL_strdup(interface->URI, OSL_URI_ANNOTATION);

  interface->idump = (osl_idump_f)osl_annotation_idump;
  interface->sprint = (osl_sprint_f)osl_annotation_sprint;
  interface->sread = (osl_sread_f)osl_annotation_sread;
  interface->malloc = (osl_malloc_f)osl_annotation_malloc;
  interface->free = (osl_free_f)osl_annotation_free;
  interface->clone = (osl_clone_f)osl_annotation_clone;
  interface->equal = (osl_equal_f)osl_annotation_equal;

  return interface;
}
