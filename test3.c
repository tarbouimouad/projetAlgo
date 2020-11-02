#include "dico.h"


int main(int argc, char const *argv[]) {

  dico d1 = create_dico();

  add_rec(d1,"bord",4);
  add_rec(d1,"bordeau",7);
  add_rec(d1,"bateau",6);
  add_rec(d1,"brule",5);

  dico d2 = create_dico();

  add_rec(d2,"bord",4);
  add_rec(d2,"bordeau",7);
  add_rec(d2,"bateau",6);
  add_rec(d2,"brule",5);
  printf("/***********************Egalité de deux dictionnaires***************************/\n");
  puts("");
  printf("On affiche le dictionnaire d1:\n");
  print_dico(d1);
  puts("");
  printf("On affiche le dictionnaire d2:\n" );
  print_dico(d2);
  puts("");
  printf("d1 = d2 ?: " );

  if (equals(d1 , d2)) {
    printf("Oui\n" );
  }
  else{printf("Non\n" );}
  puts("");

  printf("On supprime le mot 'bord' de d1\n" );
  remove_rec(d1,"bord",4);
  printf("On affiche le dictionnaire d1:\n" );
  print_dico(d1);
  puts("");

  printf("d1 = d2 ?: " );

  if (equals(d1 , d2)) {
    printf("Oui\n" );
  }
  else{printf("Non\n" );}
  puts("");
  printf("/*************************Fin Test**********************************************/\n");


  return 0;
}
