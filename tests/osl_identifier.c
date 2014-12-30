#include <osl/osl.h>
#include <osl/extensions/identifier.h>

#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *fr = fopen("test_identifier.scop", "r");
  FILE *fw = fopen("/tmp/output.scop", "w");

  osl_scop_p scop = osl_scop_read(fr);
  osl_scop_dump(stderr, scop);
  osl_scop_print(fw, scop);
  osl_scop_free(scop);

  fclose(fr);
  fclose(fw);
  return 0;
}
