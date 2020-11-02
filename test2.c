#include "dico.h"


int main(int argc, char const *argv[]) {

  printf("/**********************Ajout,suppression....**********************************/\n");

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

  printf("On affiche le dictionnaire\n");
  puts("");
  print_dico(d);
  printf("/__________________________________________________/\n");
  printf("On supprime le mot 'bordeau', la suppression est effective?: ");

  if (remove_rec(d,"bordeau",7) ) {
    printf("oui\n" );
    }
  else{printf("non\n" ); }
  puts("");
  printf("On affiche le dictionnaire\n");
  puts("");
  print_dico(d);
  printf("/__________________________________________________/\n");
  printf("On supprime le mot 'borde', la suppression est effective?: ");
  if (remove_iter(d,"borde",5) ) {
    printf("oui\n" );
    }
  else{printf("non\n" ); }
  puts("");
  printf("Le mot 'bord' appartient-il au dictionnaire d ? " );
  if (contains_rec(d,"bord",4) ) {
    printf("oui\n" );
    }
  else{printf("non\n" ); }
  puts("");
  printf("Le mot 'couscous' appartient-il au dictionnaire d ? " );
  if (contains_iter(d,"couscous",8) ) {
    printf("oui\n" );
    }
  else{printf("non\n" ); }
  puts("");


  printf("On affiche le dictionnaire\n");
  puts("");
  print_dico(d);
  printf("/*************************Fin Test************************************/\n");

  return 0;
}
