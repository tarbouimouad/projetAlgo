#include "dico.h"

int main(int argc, char const *argv[]) {
  printf("/****************************Iterateur************************************/\n");
  puts("");

  dico d = create_dico();

  add_rec(d,"bord",4);
  add_rec(d,"bordeau",7);
  add_rec(d,"bateau",6);
  add_rec(d,"brule",5);
  add_iter(d,"brille",6);
  add_iter(d,"ours",4);
  add_iter(d,"ourse",5);
  add_iter(d,"ourson",6);
  add_iter(d,"oursonne",8);

  iterator * dit = start_iterator(d);
  while (has_next(dit)) printf("-%s", next(dit));
  destroy_iterator(&dit);
  puts("");
  puts("");
  printf("/****************************Fin Test************************************/\n");
  return 0;
}
