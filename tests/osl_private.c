/* Regression tests for scalar expansion metadata and generic serialization. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <osl/osl.h>

#define CHECK(test) do { \
  if (!(test)) { \
    fprintf(stderr, "private: failed at line %d: %s\n", __LINE__, #test); \
    exit(1); \
  } \
} while (0)

int main(void) {
  char input[] = "# count\n2\n4 1 2 # acc\n9 3 1\n";
  char* cursor = input;
  char* text;
  osl_private_p priv = osl_private_sread(&cursor);
  osl_private_p clone = osl_private_clone(priv);
  osl_private_p reverse = osl_private_malloc();
  osl_private_p empty = osl_private_malloc();
  osl_private_p parsed;
  osl_generic_p generic, copy, reread;
  osl_interface_p registry = osl_interface_get_default_registry();
  FILE* file = tmpfile();
  CHECK(file != NULL);
  CHECK(priv->nb_variables == 2);
  CHECK(priv->array_id[0] == 4 && priv->stmt_id[0] == 1 && priv->nb_dims[0] == 2);
  CHECK(priv->array_id[1] == 9 && priv->stmt_id[1] == 3 && priv->nb_dims[1] == 1);
  CHECK(osl_private_equal(priv, clone));
  clone->nb_dims[0]++;
  CHECK(!osl_private_equal(priv, clone));
  CHECK(priv->nb_dims[0] == 2);
  osl_private_add(reverse, 9, 3, 1);
  osl_private_add(reverse, 4, 1, 2);
  CHECK(osl_private_equal(priv, reverse));
  CHECK(!osl_private_equal(priv, empty));
  CHECK(!osl_private_equal(priv, NULL));
  CHECK(osl_private_equal(NULL, NULL));
  CHECK(osl_private_clone(NULL) == NULL);
  CHECK(osl_private_sprint(NULL) == NULL);
  CHECK(osl_private_sread(NULL) == NULL);
  osl_private_free(NULL);
  text = osl_private_sprint(empty);
  cursor = text;
  parsed = osl_private_sread(&cursor);
  CHECK(osl_private_equal(empty, parsed));
  free(text);
  osl_private_free(parsed);
  osl_private_dump(file, priv);
  osl_private_dump(file, NULL);
  CHECK(osl_interface_lookup(registry, OSL_URI_PRIVATE) != NULL);
  generic = osl_generic_shell(priv, osl_private_interface());
  copy = osl_generic_clone(generic);
  CHECK(osl_generic_equal(generic, copy));
  text = osl_generic_sprint(generic);
  cursor = text;
  reread = osl_generic_sread(&cursor, registry);
  CHECK(osl_generic_equal(generic, reread));
  free(text);
  osl_generic_free(generic);
  osl_generic_free(copy);
  osl_generic_free(reread);
  osl_interface_free(registry);
  osl_private_free(clone);
  osl_private_free(reverse);
  osl_private_free(empty);
  fclose(file);
  return 0;
}
