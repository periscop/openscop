#
#   /*+------------------------------------------------------------------**
#    **                       OpenScop Library                           **
#    **------------------------------------------------------------------**
#    **                         extension.sh                             **
#    **------------------------------------------------------------------**
#    **                   First version: 28/05/2011                      **
#    **------------------------------------------------------------------**
#
#   
# ***************************************************************************
# * OpenScop: Structures and formats for polyhedral tools to talk together  *
# ***************************************************************************
# *   ,___,,_,__,,__,,__,,__,,_,__,,_,__,,__,,___,_,__,,_,__,               *
# *   /   / /  //  //  //  // /   / /  //  //   / /  // /  /|,_,            *
# *  /   / /  //  //  //  // /   / /  //  //   / /  // /  / / /\            *
# * |~~~|~|~~~|~~~|~~~|~~~|~|~~~|~|~~~|~~~|~~~|~|~~~|~|~~~|/_/  \           *
# * | G |C| P | = | L | P |=| = |C| = | = | = |=| = |=| C |\  \ /\          *
# * | R |l| o | = | e | l |=| = |a| = | = | = |=| = |=| L | \# \ /\         *
# * | A |a| l | = | t | u |=| = |n| = | = | = |=| = |=| o | |\# \  \        *
# * | P |n| l | = | s | t |=| = |d| = | = | = | |   |=| o | | \# \  \       *
# * | H | | y |   | e | o | | = |l|   |   | = | |   | | G | |  \  \  \      *
# * | I | |   |   | e |   | |   | |   |   |   | |   | |   | |   \  \  \     *
# * | T | |   |   |   |   | |   | |   |   |   | |   | |   | |    \  \  \    *
# * | E | |   |   |   |   | |   | |   |   |   | |   | |   | |     \  \  \   *
# * | * |*| * | * | * | * |*| * |*| * | * | * |*| * |*| * | /      \* \  \  *
# * | O |p| e | n | S | c |o| p |-| L | i | b |r| a |r| y |/        \  \ /  *
# * '---'-'---'---'---'---'-'---'-'---'---'---'-'---'-'---'          '--'   *
# *                                                                         *
# * Copyright (C) 2008 University Paris-Sud 11 and INRIA                    *
# *                                                                         *
# * (3-clause BSD license)                                                  *
# * Redistribution and use in source  and binary forms, with or without     *
# * modification, are permitted provided that the following conditions      *
# * are met:                                                                *
# *                                                                         *
# * 1. Redistributions of source code must retain the above copyright       *
# *    notice, this list of conditions and the following disclaimer.        *
# * 2. Redistributions in binary form must reproduce the above copyright    *
# *    notice, this list of conditions and the following disclaimer in the  *
# *    documentation and/or other materials provided with the distribution. *
# * 3. The name of the author may not be used to endorse or promote         *
# *    products derived from this software without specific prior written   *
# *    permission.                                                          *
# *                                                                         *
# * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR    *
# * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED          *
# * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE  *
# * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,      *
# * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES      *
# * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR      *
# * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)      *
# * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,     *
# * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING   *
# * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE      *
# * POSSIBILITY OF SUCH DAMAGE.                                             *
# *                                                                         *
# * OpenScop Library, a library to manipulate OpenScop formats and data     *
# * structures. Written by:                                                 *
# * Cedric Bastoul     <Cedric.Bastoul@u-psud.fr> and                       *
# * Louis-Noel Pouchet <Louis-Noel.pouchet@inria.fr>                        *
# *                                                                         *
# ***************************************************************************/

EXTENSIONS_DIR='./source/extensions'
EXTENSIONS_IN='./source/extension.c.in'
EXTENSIONS_TMP='./extension.tmp'
EXTENSIONS_OUT='./source/extension.c'

# ***************************************************************************

TEMPLATE_STRING[0]=
TEMPLATE_SUBSTITUTION[0]='@IDUMP1@'
TEMPLATE[0]='\
      case OPENSCOP_EXTENSION_TEMPLATE: {\
        fprintf(file, "|\\ttype = OPENSCOP_EXTENSION_TEMPLATE\\n");\
        break;\
      }'

# ***************************************************************************

TEMPLATE_STRING[1]=
TEMPLATE_SUBSTITUTION[1]='@IDUMP2@'
TEMPLATE[1]='\
      case OPENSCOP_EXTENSION_TEMPLATE: {\
        openscop_template_idump(\
            file,\
            (openscop_template_p)extension->extension,\
            level + 1);\
        break;\
      }'

# ***************************************************************************

TEMPLATE_STRING[2]=
TEMPLATE_SUBSTITUTION[2]='@SPRINT@'
TEMPLATE[2]='\
      case OPENSCOP_EXTENSION_TEMPLATE: {\
        string = openscop_template_sprint(\
                     (openscop_template_p)extension->extension);\
        break;\
      }'

# ***************************************************************************

TEMPLATE_STRING[3]=
TEMPLATE_SUBSTITUTION[3]='@SREAD@'
TEMPLATE[3]='\
  x = (void *)openscop_template_sread(extension_string);\
  openscop_extension_add(\&extension, OPENSCOP_EXTENSION_TEMPLATE, x);'

# ***************************************************************************

TEMPLATE_STRING[4]=
TEMPLATE_SUBSTITUTION[4]='@FREE@'
TEMPLATE[4]='\
      case OPENSCOP_EXTENSION_TEMPLATE: {\
        openscop_template_free(extension->extension);\
        break;\
      }'

# ***************************************************************************

TEMPLATE_STRING[5]=
TEMPLATE_SUBSTITUTION[5]='@COPY@'
TEMPLATE[5]='\
      case OPENSCOP_EXTENSION_TEMPLATE: {\
        x = (void *)openscop_template_clone(extension->extension);\
        break;\
      }'

# ***************************************************************************

TEMPLATE_STRING[6]=
TEMPLATE_SUBSTITUTION[6]='@EQUAL@'
TEMPLATE[6]='\
          case OPENSCOP_EXTENSION_TEMPLATE: {\
            equal = openscop_template_equal(x1->extension, x2->extension);\
            break;\
          }'

# ***************************************************************************

# For each file in the extension directory.
for i in ${EXTENSIONS_DIR}/*.c;
do
  # Get the extension name, lower case and upper case.
  EXTENSION_LO=`basename ${i%.c}`
  EXTENSION_UP=`echo ${EXTENSION_LO} | tr '[a-z]' '[A-Z]'`
  
  # Replace the extension name in the templates.
  for (( i = 0 ; i < ${#TEMPLATE[@]} ; i++ ))
  do
    TEMP1=`echo "${TEMPLATE[$i]}" | sed "s/TEMPLATE/${EXTENSION_UP}/g"`
    TEMP2=`echo "${TEMP1}" | sed "s/template/${EXTENSION_LO}/g"`
    TEMPLATE_STRING[$i]="${TEMPLATE_STRING[$i]}""${TEMP2}"
  done
done

# Substitute the generated code parts in the source.
cp ${EXTENSIONS_IN} ${EXTENSIONS_TMP}
for (( i = 0 ; i < ${#TEMPLATE[@]} ; i++ ))
do
  sed "s/${TEMPLATE_SUBSTITUTION[$i]}/${TEMPLATE_STRING[$i]}/g" \
      <${EXTENSIONS_TMP} >${EXTENSIONS_OUT}
  mv ${EXTENSIONS_OUT} ${EXTENSIONS_TMP}
done
mv ${EXTENSIONS_TMP} ${EXTENSIONS_OUT}
