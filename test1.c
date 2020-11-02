#include "dico.h"


int main(int argc, char const *argv[]) {
  printf("/*******************Affichage prefixé d'un dictionnaire********************/\n");
  
  puts("");
  printf("On crée un dictionnaire d\n" );
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
  printf("On ajoute les mots bordeau, bord, bateau, brule, brille, ours, ourse, ourson et oursonne\n" );
  puts("");
  printf("Ce dictionnaire contient %d noeuds ,a une hauteur de %d et possède %d mot(s)\n",nb_nodes(d),height(d),nb_words(d));
  puts("");
  printf("On affiche le dictionnaire\n");
  print_prefix(d);
  printf("/*************************Fin Test************************************/\n");

}
