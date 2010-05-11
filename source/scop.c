
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                            scop.c                               **
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

# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <openscop/scop.h>


/*+****************************************************************************
 *                         Structure display functions                        *
 ******************************************************************************/


/**
 * openscop_scop_print_structure function:
 * Displays a openscop_scop_t structure (*scop) into a file (file, possibly
 * stdout) in a way that trends to be understandable without falling in a deep
 * depression or, for the lucky ones, getting a headache... It includes an
 * indentation level (level) in order to work with others print_structure
 * functions.
 * \param file   File where informations are printed.
 * \param scop   The scop whose information have to be printed.
 * \param level  Number of spaces before printing, for each line.
 **
 * - 30/04/2008: first version.
 */
void
openscop_scop_print_structure(FILE * file, openscop_scop_p scop, int level)
{
  int i, j;

  if (scop != NULL)
  {
    /* Go to the right level. */
    for (j = 0; j < level; j++)
      fprintf(file,"|\t");
    fprintf(file,"+-- openscop_scop_t\n");

    /* A blank line. */
    for (j = 0; j <= level+1; j++)
      fprintf(file,"|\t");
    fprintf(file,"\n");

    /* Print the context of the scop. */
    openscop_matrix_print_structure(file,scop->context,level+1);

    /* Print the original parameter names. */
    for (i = 0; i <= level; i++)
      fprintf(file,"|\t");
    if (scop->nb_parameters > 0)
    {
      fprintf(file,"+-- Original parameters strings:");
      for (i = 0; i < scop->nb_parameters; i++)
        fprintf(file," %s",scop->parameters[i]);
      fprintf(file,"\n");
    }
    else
      fprintf(file,"+-- No original parameters string\n");

    /* A blank line. */
    for (j = 0; j <= level+1; j++)
      fprintf(file,"|\t");
    fprintf(file,"\n");

    /* Print the original parameter names. */
    for (i = 0; i <= level; i++)
      fprintf(file,"|\t");
    if (scop->nb_arrays > 0)
    {
      fprintf(file,"+-- Accessed array strings:");
      for (i = 0; i < scop->nb_arrays; i++)
        fprintf(file," %s",scop->arrays[i]);
      fprintf(file,"\n");
    }
    else
      fprintf(file,"+-- No accessed array string\n");

    /* A blank line. */
    for (j = 0; j <= level+1; j++)
      fprintf(file,"|\t");
    fprintf(file,"\n");

    /* Print the statements. */
    openscop_statement_print_structure(file,scop->statement,level+1);
  }
  else
  {
    /* Go to the right level. */
    for (j = 0; j < level; j++)
      fprintf(file,"|\t");
    fprintf(file,"+-- NULL scop\n");
  }

  /* The last line. */
  for (j = 0; j <= level; j++)
    fprintf(file,"|\t");
  fprintf(file,"\n");
}


/**
 * openscop_scop_print function:
 * This function prints the content of a openscop_scop_t structure (*scop) into
 * a file (file, possibly stdout).
 * \param file   File where informations are printed.
 * \param scop   The scop whose information have to be printed.
 **
 * - 30/04/2008: first version.
 */
void
openscop_scop_print(FILE * file, openscop_scop_p scop)
{
  openscop_scop_print_structure(file,scop,0);
}



static
void
openscop_scop_print_dot_scop_(FILE * file, openscop_scop_p scop,
			     int castle, int arraystag)
{
  int i;

  if (castle)
  {
    fprintf(file,"#                                                     \n");
    fprintf(file,"#          <|                                         \n");
    fprintf(file,"#           A                                         \n");
    fprintf(file,"#          /.\\                                       \n");
    fprintf(file,"#     <|  [\"\"M#                                     \n");
    fprintf(file,"#      A   | #            Clan McCloog Castle         \n");
    fprintf(file,"#     /.\\ [\"\"M#           [Generated by the OpenScop ");
    fprintf(file,"Library %s %s bits]\n",OPENSCOP_RELEASE, OPENSCOP_VERSION);
    fprintf(file,"#    [\"\"M# | #  U\"U#U                              \n");
    fprintf(file,"#     | #  | #  \\ .:/                                \n");
    fprintf(file,"#     | #  | #___| #                                  \n");
    fprintf(file,"#     | \"--'     .-\"                                \n");
    fprintf(file,"#   |\"-\"-\"-\"-\"-#-#-##                            \n");
    fprintf(file,"#   |     # ## ######                                 \n");
    fprintf(file,"#    \\       .::::'/                                 \n");
    fprintf(file,"#     \\      ::::'/                                  \n");
    fprintf(file,"#   :8a|    # # ##                                    \n");
    fprintf(file,"#   ::88a      ###                                    \n");
    fprintf(file,"#  ::::888a  8a ##::.                                 \n");
    fprintf(file,"#  ::::::888a88a[]::::                                \n");
    fprintf(file,"# :::::::::SUNDOGa8a::::. ..                          \n");
    fprintf(file,"# :::::8::::888:Y8888:::::::::...                     \n");
    fprintf(file,"#::':::88::::888::Y88a______________________________");
    fprintf(file,"________________________\n");
    fprintf(file,"#:: ::::88a::::88a:Y88a                             ");
    fprintf(file,"     __---__-- __\n");
    fprintf(file,"#' .: ::Y88a:::::8a:Y88a                            ");
    fprintf(file,"__----_-- -------_-__\n");
    fprintf(file,"#  :' ::::8P::::::::::88aa.                   _ _- -");
    fprintf(file,"-  --_ --- __  --- __--\n");
    fprintf(file,"#.::  :::::::::::::::::::Y88as88a...s88aa.\n");
  }
  else
  {
    fprintf(file,"# [File generated by ScopLib %s %s bits]\n",
            OPENSCOP_RELEASE,OPENSCOP_VERSION);
  }

  fprintf(file,"\n");
  fprintf(file,"SCoP\n");
  fprintf(file,"\n");
  fprintf(file,"# =============================================== Global\n");
  fprintf(file,"# Language\n");
  fprintf(file,"C\n");
  fprintf(file,"\n");

  fprintf(file,"# Context\n");
  openscop_matrix_print_dot_scop(file,scop->context,OPENSCOP_TYPE_DOMAIN,
				0,NULL,
				scop->nb_parameters,scop->parameters,
				scop->nb_arrays,scop->arrays);
  fprintf(file,"\n");

  if (scop->nb_parameters > 0)
  {
    fprintf(file,"# Parameter names are provided\n");
    fprintf(file,"1\n");
    fprintf(file,"# Parameter names\n");
    for (i = 0; i < scop->nb_parameters; i++)
      fprintf(file,"%s ",scop->parameters[i]);
    fprintf(file,"\n");
    fprintf(file,"\n");
  }
  else
  {
    fprintf(file,"# Parameter names are not provided\n");
    fprintf(file,"0\n");
    fprintf(file,"\n");
  }

  fprintf(file,"# Number of statements\n");
  fprintf(file,"%d\n",openscop_statement_number(scop->statement));
  fprintf(file,"\n");

  openscop_statement_print_dot_scop(file,scop->statement,
				   scop->nb_parameters,scop->parameters,
				   scop->nb_arrays,scop->arrays);

  fprintf(file,"# =============================================== Options\n");
  if (scop->optiontags)
    fprintf(file, "%s", scop->optiontags);
  if (arraystag)
    {
      /* If the <array> tag is present in the option tags, don't dump it. */
      char* content = openscop_scop_tag_content (scop, "<arrays>", "</arrays>");
      if (! content)
	{
	  /* It isn't, so dump the list of arrays. */
	  fprintf(file, "<arrays>\n");
	  fprintf(file, "%d\n", scop->nb_arrays);
	  for (i = 0; i < scop->nb_arrays; ++i)
	    fprintf(file, "%d %s\n", i + 1, scop->arrays[i]);
	  fprintf(file, "</arrays>\n");
	}
      else
	free(content);
    }
}


/**
 * openscop_scop_print_dot_scop function:
 * This function prints the content of a openscop_scop_t structure (*scop)
 * into a file (file, possibly stdout) for the .scop format.
 * \param file    File where informations are printed.
 * \param scop    The scop whose information have to be printed.
 **
 * - 02/05/2008: first version.
 */
void
openscop_scop_print_dot_scop(FILE * file, openscop_scop_p scop)
{
  openscop_scop_print_dot_scop_(file, scop, 0, 0);
}

/**
 * openscop_scop_print_dot_scop_castle function:
 * This function prints the content of a openscop_scop_t structure (*scop)
 * into a file (file, possibly stdout) for the .scop format, with the castle.
 * \param file    File where informations are printed.
 * \param scop    The scop whose information have to be printed.
 **
 * - 02/05/2008: first version.
 */
void
openscop_scop_print_dot_scop_options(FILE * file, openscop_scop_p scop,
				    int options)
{
  int castle = 0;
  int arraystag = 0;
  if ((options & OPENSCOP_SCOP_PRINT_CASTLE) != 0)
    castle = 1;
  if ((options & OPENSCOP_SCOP_PRINT_ARRAYSTAG) != 0)
    arraystag = 1;
  openscop_scop_print_dot_scop_(file, scop, castle, arraystag);
}


/******************************************************************************
 *                               Reading function                             *
 ******************************************************************************/

/**
 * Internal function. Read 'nb_strings' strings on the input 'file'.
 *
 * \FIXME should be placed somewhere else, it's duplicated in statement.c.
 */
static
char**
openscop_scop_read_strings(FILE* file, int nb_strings)
{
  char str[OPENSCOP_MAX_STRING];
  char tmp[OPENSCOP_MAX_STRING];
  char* s;
  char** res = NULL;
  int i;
  int count;

  /* Skip blank/commented lines. */
  while (fgets(str, OPENSCOP_MAX_STRING, file) == 0 || str[0] == '#' ||
	 isspace(str[0]))
    ;
  s = str;

  /* Allocate the array of string. Make it NULL-terminated. */
  res = (char**) malloc(sizeof(char*) * (nb_strings + 1));
  res[nb_strings] = NULL;

  /* Read the desired number of strings. */
  for (i = 0; i < nb_strings; ++i)
    {
      for (count = 0; *s && ! isspace(*s) && *s != '#'; ++count)
	tmp[count] = *(s++);
      tmp[count] = '\0';
      res[i] = strdup(tmp);
      if (*s != '#')
	++s;
    }

  return res;
}


/**
 * Internal function. Read an int on the input 'file'.
 *
 * \FIXME should be placed somewhere else, it's duplicated in statement.c.
 */
static
int
openscop_scop_read_int(FILE* file, char** str)
{
  char s[OPENSCOP_MAX_STRING];
  int res;
  int i = 0;
  int read_int = 0;

  if (file != NULL && str != NULL)
    {
      fprintf(stderr, "[Scoplib] Error: only one of the two parameters of"
	      " scop_read_int can be non-NULL\n");
      exit (1);
    }

  if (file != NULL)
    {
      /* Parse from a file. */
      /* Skip blank/commented lines. */
      while (fgets(s, OPENSCOP_MAX_STRING, file) == 0 || s[0] == '#' ||
	     isspace(s[0]))
	;
      sscanf(s, "%d", &res);
    }
  if (str != NULL)
    {
      /* Parse from a string. */
      /* Skip blank/commented lines. */
      do
	{
	  while (*str && **str && isspace(**str))
	    ++(*str);
	  if (**str == '#')
	    {
	      while (**str && **str != '\n')
		++(*str);
	    }
	  else
	    {
	      /* Build the chain to analyze. */
	      while (**str && !isspace(**str) && **str != '\n')
		s[i++] = *((*str)++);
	      s[i] = '\0';
	      sscanf(s, "%d", &res);
	      read_int = 1;
	    }
	}
      while (! read_int);
    }

  return res;
}


/**
 * openscop_scop_generate_names function:
 * This function generates an array of size 'nb' of chars of the form
 * "seedXX" where XX goes from 1 to nb.
 * \param seed		The template for the created names
 * \param nb		The number of created items.
 */
char**
openscop_scop_generate_names(char* seed, int nb)
{
  char** res = NULL;
  char buff[strlen(seed) + 16];
  int i;

  if (nb)
    {
      res = (char**) malloc(sizeof(char*)* nb);
      if (res == NULL)
	{
	  fprintf(stderr, "[Scoplib] Memory Overflow.\n");
	  exit(1);
	}
      for (i = 0; i < nb; ++i)
	{
	  sprintf(buff, "%s%d", seed, i + 1);
	  res[i] = strdup(buff);
	}
    }

  return res;
}


/**
 * openscop_scop_tag_content function:
 * This function returns a freshly allocated string containing the
 * content, in the optional tags section, between the tag 'tag' and
 * the tag 'endtag'. If the tag 'tag' is not found, returns NULL.
 */
char*
openscop_scop_tag_content(openscop_scop_p scop, char* tag, char* endtag)
{
  return openscop_scop_tag_content_from_string(scop->optiontags, tag, endtag);
}


/**
 * openscop_scop_tag_content_from_string function:
 * This function returns a freshly allocated string containing the
 * content, in the given string 'str', between the tag 'tag' and
 * the tag 'endtag'. If the tag 'tag' is not found, returns NULL.
 */
char*
openscop_scop_tag_content_from_string(char* str, char* tag, char* endtag)
{
  int i;
  char* start;
  char* stop;
  int size = 0;
  int lentag;
  char* res = NULL;

  if (str)
    {
      start = str;
      lentag = strlen(tag);
      for (; start && *start && strncmp(start, tag, lentag); ++start)
	;
      /* The tag 'tag' was not found.*/
      if (! *start)
	return NULL;
      start += lentag;
      stop = start;
      lentag = strlen(endtag);
      for (size = 0; *stop && strncmp(stop, endtag, lentag); ++stop, ++size)
	;
      /* the tag 'endtag' was not found. */
      if (! *stop)
	return NULL;
      res = (char*) malloc((size + 1) * sizeof(char));
      if (res == NULL)
	{
	  fprintf(stderr, "[Scoplib] Error: memory exhausted\n");
	  exit(1);
	}
      /* Copy the chain between the two tags. */
      for (++start, i = 0; start != stop; ++start, ++i)
	res[i] = *start;
      res[i] = '\0';
    }

  return res;
}


/**
 * openscop_scop_read function:
 * This function reads a openscop_scop_t structure from an input stream
 * (possibly stdin) corresponding to a openscop SCoP dump.
 * \param file		The input stream
 */
openscop_scop_p
openscop_scop_read(FILE* file)
{
  char tmpbuff[OPENSCOP_MAX_STRING];
  openscop_scop_p scop = NULL;
  openscop_statement_p stmt = NULL;
  openscop_statement_p prev = NULL;
  int nb_statements;
  char** tmp;
  int i;
  char* content;

  if (file == NULL)
    return NULL;

  scop = openscop_scop_malloc();

  /* Backup the arrays of the program. Buffer is reajustable. */
  int nb_arr = OPENSCOP_MAX_STRING;
  char** arrays = (char**) malloc (sizeof(char*) * nb_arr);
  for (i = 0; i < nb_arr; ++i)
    arrays[i] = NULL;

  /* Ensure the file is a .scop. */
  tmp = openscop_scop_read_strings(file, 1);
  if (strcmp(*tmp, "SCoP"))
    {
      fprintf(stderr, "[Scoplib] Error. The file is not a .scop\n");
      exit (1);
    }
  free(*tmp);
  free(tmp);

  /* Read the language. */
  char** language =  openscop_scop_read_strings(file, 1);
  if (strcmp(*language, "C") && strcmp(*language, "JAVA") &&
      strcmp(*language, "C#"))
    {
      fprintf(stderr, "[Scoplib] Error. The language is not recognized\n");
      exit (1);
    }
  /* language is not used so far. */
  free(*language);
  free(language);

  /* Read the context. */
  scop->context  = openscop_matrix_read (file);
  scop->nb_parameters = scop->context->NbColumns - 2;

  /* Read the parameter names, if any. */
  if (openscop_scop_read_int(file, NULL) > 0)
    scop->parameters = openscop_scop_read_strings (file, scop->nb_parameters);
  else
    scop->parameters = openscop_scop_generate_names("M", scop->nb_parameters);

  /* Read the number of statements. */
  nb_statements = openscop_scop_read_int (file, NULL);

  for (i = 0; i < nb_statements; ++i)
    {
      /* Read each statement. */
      stmt = openscop_statement_read (file, scop->nb_parameters,
				  &arrays, &nb_arr);
      if (scop->statement == NULL)
	scop->statement = stmt;
      else
	prev->next = stmt;
      prev = stmt;
    }

  /* Read the remainder of the file, and store it in the optiontags
     field. */
  /* Skip blank lines. */
  while (! feof(file) &&
	 (fgets(tmpbuff, OPENSCOP_MAX_STRING, file) == 0 ||
	  tmpbuff[0] == '#' || isspace(tmpbuff[0]) || tmpbuff[0] != '<'))
    ;
  /* Store the remainder of the file, if any. */
  if (tmpbuff[0])
    {
      int count = strlen(tmpbuff);
      int pos = 0;
      int bufs = OPENSCOP_MAX_STRING;
      scop->optiontags = (char*) malloc(bufs * sizeof(char));
      do
	{
	  scop->optiontags = (char*) realloc
	    (scop->optiontags, (bufs += count) * sizeof(char));
	  for (i = 0; i < count; ++i)
	    scop->optiontags[pos++] = tmpbuff[i];
	}
      while ((count = fread(tmpbuff, sizeof(char), OPENSCOP_MAX_STRING, file))
	     > 0);
    }

  /* Count the number of referenced arrays/variables. */
  scop->nb_arrays = 0;
  for (stmt = scop->statement; stmt; stmt = stmt->next)
    {
      if (stmt->read)
	for (i = 0; i < stmt->read->NbRows; ++i)
	  if (scop->nb_arrays < SCOPINT_get_si(stmt->read->p[i][0]))
	    scop->nb_arrays = SCOPINT_get_si(stmt->read->p[i][0]);
      if (stmt->write)
	for (i = 0; i < stmt->write->NbRows; ++i)
	  if (scop->nb_arrays < SCOPINT_get_si(stmt->write->p[i][0]))
	    scop->nb_arrays = SCOPINT_get_si(stmt->write->p[i][0]);
    }

  /* Allocate the array names array. */
  scop->arrays = (char**) malloc(sizeof(char*) * (scop->nb_arrays + 1));
  for (i = 0; i < scop->nb_arrays; ++i)
    scop->arrays[i] = NULL;

  /* Populate the array list with referenced in the <array> tag, if
     any. */
  if ((content = openscop_scop_tag_content(scop, "<arrays>", "</arrays>")))
    {
      char* start = content;
      int n_arr = openscop_scop_read_int(NULL, &content);
      char buff2[OPENSCOP_MAX_STRING];
      int idx_array;
      i = 0;
      while (n_arr--)
	{
	  /* Skip blank or commented lines. */
	  while (*content == '#' || *content == '\n')
	    {
	      for (; *content != '\n'; ++content)
		;
	      ++content;
	    }
	  /* Get the variable id. */
	  for (i = 0; *content && ! isspace(*content); ++i, ++content)
	    buff2[i] = *content;
	  buff2[i] = '\0';
	  sscanf (buff2, "%d", &idx_array);
	  /* Get the variable name. */
	  while (*content && isspace(*content))
	    ++content;
	  for (i = 0; *content && ! isspace(*content); ++i, ++content)
	    buff2[i] = *content;
	  buff2[i] = '\0';
	  /* array is in 0-basis. */
	  if (arrays[idx_array - 1])
	    free(arrays[idx_array - 1]);
	  arrays[idx_array - 1] = strdup(buff2);
	  /* Go to the end of line. */
	  while (*content && *content != '\n')
	    ++content;
	}
      content = start;
    }

  /* Fill the array of array names. */
  char** tmparrays = openscop_scop_generate_names("var", scop->nb_arrays);
  for (i = 0; i < scop->nb_arrays; ++i)
    {
      if (arrays[i] == NULL || arrays[i][0] == '\0')
	{
	  /* Use a generated name in case no array name was parsed. */
	  scop->arrays[i] = tmparrays[i];
	  if (arrays[i])
	    free(arrays[i]);
	}
      else
	{
	  /* Use the parsed array name. */
	  scop->arrays[i] = arrays[i];
	  free(tmparrays[i]);
	}
    }
  scop->arrays[i] = NULL;
  free(arrays);
  free(tmparrays);


  return scop;
}



/*+****************************************************************************
 *                   Memory allocation/deallocation functions                 *
 ******************************************************************************/


/**
 * openscop_scop_malloc function:
 * This function allocates the memory space for a openscop_scop_t structure and
 * sets its fields with default values. Then it returns a pointer to the
 * allocated space.
 **
 * - 30/04/2008: first version.
 */
openscop_scop_p
openscop_scop_malloc()
{
  openscop_scop_p scop;

  scop = (openscop_scop_p)malloc(sizeof(openscop_scop_t));
  if (scop == NULL)
  {
    fprintf(stderr, "[Scoplib] Memory Overflow.\n");
    exit(1);
  }

  scop->context       = NULL;
  scop->nb_parameters = 0;
  scop->parameters    = NULL;
  scop->nb_arrays     = 0;
  scop->arrays        = NULL;
  scop->statement     = NULL;
  scop->optiontags    = NULL;
  scop->usr	      = NULL;

  return scop;
}


/**
 * openscop_scop_free function:
 * This function frees the allocated memory for a openscop_scop_t structure.
 * \param scop The pointer to the scop we want to free.
 **
 * - 30/04/2008: first version.
 */
void
openscop_scop_free(openscop_scop_p scop)
{
 int i;

  if (scop != NULL)
  {
    openscop_matrix_free(scop->context);
    if (scop->parameters != NULL)
    {
      for (i = 0; i < scop->nb_parameters; i++)
        free(scop->parameters[i]);
      free(scop->parameters);
    }
    if (scop->arrays != NULL)
    {
      for (i = 0; i < scop->nb_arrays; i++)
        free(scop->arrays[i]);
      free(scop->arrays);
    }
    openscop_statement_free(scop->statement);
    free(scop->optiontags);
    free(scop);
  }
}



/**
 * openscop_scop_dup function:
 * This function returns a fresh identical (non shadow) copy of the
 * input scop.
 * \param scop   The scop whose information have to be printed.
 **
 */
openscop_scop_p
openscop_scop_dup(openscop_scop_p scop)
{
  int i;
  openscop_statement_p stm;
  openscop_statement_p tmp = NULL;
  openscop_scop_p ret = openscop_scop_malloc();
  ret->context = openscop_matrix_copy(scop->context);
  ret->nb_parameters = scop->nb_parameters;
  ret->parameters = (char**) malloc(sizeof(char*) * ret->nb_parameters);
  for (i = 0; i < ret->nb_parameters; ++i)
    ret->parameters[i] = strdup(scop->parameters[i]);
  ret->nb_arrays = scop->nb_arrays;
  ret->arrays = (char**) malloc(sizeof(char*) * ret->nb_arrays);
  for (i = 0; i < ret->nb_arrays; ++i)
    ret->arrays[i] = strdup(scop->arrays[i]);

  for (stm = scop->statement; stm; stm = stm->next)
    {
      openscop_statement_p newstm = openscop_statement_malloc();
      newstm->domain = openscop_matrix_copy(stm->domain);
      newstm->schedule = openscop_matrix_copy(stm->schedule);
      newstm->read = openscop_matrix_copy(stm->read);
      newstm->write = openscop_matrix_copy(stm->write);
      newstm->nb_iterators = stm->nb_iterators;
      newstm->iterators = (char**) malloc(sizeof(char*) * newstm->nb_iterators);
      for (i = 0; i < newstm->nb_iterators; ++i)
	newstm->iterators[i] = strdup(stm->iterators[i]);
      newstm->body = strdup (stm->body);
      if (ret->statement == NULL)
	ret->statement = tmp = newstm;
      else
	{
	  tmp->next = newstm;
	  tmp = tmp->next;
	}
    }
  if (scop->optiontags)
    ret->optiontags = strdup(scop->optiontags);
  ret->usr = scop->usr;

  return ret;
}
