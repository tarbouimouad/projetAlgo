#include "dico.h"

/****************************************************/
unsigned get_index(char c) { return c - 'a'; }

char get_char(unsigned index) { return index + 'a'; }

/*****************************************************/

dico create_dico(){
  dico d = malloc(NB_KEYS * sizeof(tree));

  return d;
}
/*****************************************************/
void destroy_dico(dico * d){
  free(d[0]);
  d[0] = NULL;
}

/*****************************************************/

unsigned nb_children (tree t){
  unsigned nb_fils = 0;
  if (t == NULL || t->children == NULL ) return 0;

  for (size_t i = 0; i < NB_KEYS; i++) {
    if (t->children[i] != NULL )
          nb_fils++;
      }
  return nb_fils;

}

/*****************************************************/

unsigned nb_nodes_tree(tree t){

  unsigned nb_nodes = 0;
  if (t == NULL) return 0;
  else{
    for (size_t i = 0; i < 26; i++) {
      if (t->children[i] != NULL)
        nb_nodes += nb_nodes_tree(t->children[i]);

      }
    return 1 + nb_nodes;
  }
}
/*****************************************************/

unsigned nb_nodes(dico d){
  int nb = 0;
  for (size_t i = 0; i < 26; i++) {
    nb += nb_nodes_tree(d[i]);
  }
  return nb;
}

/*******************************************************/
int max(unsigned * tab ,unsigned size){

  int max = tab[0];
  for (size_t i = 1; i < size; i++) {
    if (max < tab[i]) {
      max = tab[i];
    }
  }
  return max;
}

/*****************************************************/

unsigned height_tree(tree t){
  if (t == NULL)
    return 0;
  else{
    unsigned * tab = malloc(nb_children(t)*sizeof(unsigned));
    unsigned *p = tab;
    for (size_t i = 0; i < 26; i++) {
      if (t->children[i] != NULL)
        {
          *p = height_tree(t->children[i]);
          p++;
        }
      }

    return 1 + max(tab, nb_children(t));
  }
}

/*****************************************************/

unsigned height(dico d){
  unsigned tab[26];
  for (size_t i = 0; i < 26; i++) {
    tab[i] = height_tree(d[i]);
  }
  return max(tab, 26);
}


/*******************************************************/
char* nb_plus(int nb){

  if (nb ==0) return "";
  char* s= malloc((nb+1)*sizeof(char));
  for (size_t i = 0; i < nb; i++) {
    s[i] = '+';
  }
  s[nb]='\0';
  return s;
}

/*****************************************************/
void print_tree(tree t , int decalage){

  if (t == NULL ) return;
  else{

    char * plus = nb_plus(decalage);

    if(t->end_of_word == 1) printf("%s[%c]%c*\n",nb_plus(decalage) ,t->first,t->first);
    else  printf("%s[%c]%c\n",nb_plus(decalage) ,t->first,t->first);
    if(plus != "")
          free(plus);
    for (size_t i = 0; i < NB_KEYS; i++) {
      print_tree(t->children[i] , decalage+1);
    }
  }
}
/*****************************************************/
void print_prefix(dico d){
  if (d == NULL) return;
  for (size_t i = 0; i < NB_KEYS; i++) {
    if(d[i] != NULL)
      print_tree(d[i] , 0);
  }
}

/*********************************************************/

bool equals_tree(tree t1, tree t2){
  if (t1 == NULL && t2 == NULL)
    return true;
  else if((t1 == NULL && t2 !=NULL) || (t2 == NULL && t1 !=NULL))
    return false;
  else if(t1->first != t2->first || t1->end_of_word != t2->end_of_word)
    return false;

  else
    {
      bool equal = true;

      for (size_t i = 0; i < NB_KEYS; i++) {

        equal &= equals_tree( t1->children[i],  t2->children[i]);
        if( equal == 0) return false;

      }
      return equal ;
    }
}

/*****************************************************/

bool equals(dico d1, dico d2){
  bool equal = true ;
  for (size_t i = 0; i < NB_KEYS; i++) {
    equal &= equals_tree(d1[i], d2[i]);
  }
  return equal;

}

/*************************************************/

bool contains_iter(dico d, char * word, unsigned size){
  tree t = d[get_index(word[0])];

  for (size_t i = 0; i < size -1; i++) {
    if (t ==NULL ) return false;
    t = t->children[get_index(word[i+1])];
  }
  if (t == NULL || t->end_of_word == 0) return false;
  return true;
}

/*****************************************************/
bool add_iter(dico  d, char * word, unsigned size){
  bool ajoute = false;

  tree t = d[get_index(word[0])];
  if (t == NULL){
    ajoute = true;
    t = malloc(sizeof(tree));
    t->first = word[0];
    if(size == 1) t->end_of_word = 1;
    else t->end_of_word = 0;
    t->children=create_dico();
    d[get_index(word[0])] = t;

  }


  for (size_t i = 0; i < size -1 ; i++) {
    tree a = t->children[get_index(word[i+1])];
    if(a == NULL){

      ajoute = true;
      a = malloc(sizeof(*d[get_index(word[0])]));
      a->first = word[i+1];
      a->end_of_word = 0;
      a->children=create_dico();
      t->children[get_index(word[i+1])] = a;

    }

    t = t->children[get_index(word[i+1])];
  }


  t->end_of_word = 1;

  return ajoute;
}

/*****************************************************/

bool remove_iter(dico d, char * word, unsigned size){

  if(contains_iter(d, word, size) == 0) return false;

  tree t = d[get_index(word[0])];
  dico trees = malloc(size*sizeof(tree));   // tableau contenant tous les noeud du mots.

  for (size_t i = 0; i < size-1 ; i++) {
    trees[i] = t;
    t = t->children[get_index(word[i+1])];
  }
  trees[size-1]=t;


  if (nb_children(trees[size-1]) !=0){
    trees[size-1]->end_of_word = 0;
    free(trees);
    return true;
    }

  else{

    trees[size-1]->end_of_word = 0;

    for (int i = size -2; i > -1; i--) {
      if(nb_children(trees[i+1]) ==0 && trees[i]->children[get_index(word[i+1])]->end_of_word == 0){

        destroy_dico(&(trees[i]->children[get_index(word[i+1])]->children));
        free(trees[i]->children[get_index(word[i+1])]);
        trees[i]->children[get_index(word[i+1])] = NULL;

      }
      else {
        free(trees);
        return true;
      }
    }

    if(nb_children(d[get_index(word[0])]) == 0 && d[get_index(word[0])]->end_of_word == 0){

      destroy_dico(&(d[get_index(word[0])]->children));
      free(d[get_index(word[0])]);
      d[get_index(word[0])] = NULL;
    }
    else {
      free(trees);
      return true;
    }
  }
  free(trees);
  return true;
}

/****************************************************/

bool contains_rec(dico d, char * word, unsigned size){

  tree t = d[get_index(word[0])];
  if(t == NULL) return false;
  else if(size == 1 && t->end_of_word == 0) return false;
  else if(size == 1 && t->end_of_word == 1) return true;
  return contains_rec(t->children, word+1, size-1);

}

/*****************************************************/
bool add_rec(dico  d, char * word, unsigned size){
  bool added = false;
  tree t = d[get_index(word[0])];
  if(size == 1){
    if(t == NULL){
      added = true;
      t = malloc(sizeof(tree));
      t->end_of_word = 1;
      t->first = word[0];
      t->children = create_dico();
      d[get_index(word[0])] = t;

    }

    return added;

  }
  else {
    if(t == NULL){
      added = true;
      t = malloc(sizeof(*d[get_index(word[0])]));
      t->end_of_word = 0;
      t->first = word[0];
      t->children = create_dico();
      d[get_index(word[0])] = t;
    }

    return added & add_rec(t->children,word +1,size -1);
  }
}

/*****************************************************/

bool remove_rec(dico d, char * word, unsigned size){

  if(!contains_rec(d, word, size)) return false;
  if(size == 1){
    if(nb_children(d[get_index(word[0])]) == 0)
    {
      destroy_dico(&(d[get_index(word[0])]->children));
      free(d[get_index(word[0])]);
      d[get_index(word[0])] = NULL;
      return true;
    }
    else{
      d[get_index(word[0])]->end_of_word = 0;
      return true;
    }
  }
  else{

    remove_rec( d[get_index(word[0])]->children, word+1,  size-1);

    if(nb_children(d[get_index(word[0])]) == 0 && d[get_index(word[0])]->end_of_word==0)
    {
      destroy_dico(&(d[get_index(word[0])]->children));
      free(d[get_index(word[0])]);
      d[get_index(word[0])] = NULL;
      return true;
    }
    return true;


  }
}



/*******************************************************/
unsigned nb_words_tree(tree t){
  if(t == NULL) return 0;

  unsigned nb_mots = 0;

  for (size_t i = 0; i < NB_KEYS; i++) {
    nb_mots += nb_words_tree(t->children[i]);
    }
  if (t->end_of_word == 1) return 1 + nb_mots;
  return nb_mots;
}

unsigned nb_words(dico d){
  unsigned nb_words = 0;
  for (size_t i = 0; i < NB_KEYS; i++) {
    nb_words += nb_words_tree(d[i]);
  }
  return nb_words;
}


/**************************************************************/


int indice = 0; // variable globale qui nous aide dans la fonction suivante.

void sprint_tree(tree t , int decalage ,char ** s){


  if (t == NULL )
    return;
  else{

    char * plus = nb_plus(decalage);

    if(t->end_of_word == 1)
      sprintf(s[indice],"%s%c*\0",plus ,t->first);
    else
      sprintf(s[indice],"%s%c\0",plus ,t->first);
    if(plus != "") // car s'il n'ya pas de + à afficher la fonction nb_plus return "" .
      free(plus);
    for (size_t i = 0; i < 26; i++) {
      if(t->children[i] != NULL)
        {
          indice++;
          sprint_tree(t->children[i] , decalage+1, s);
        }
    }
  }
}

/*****************************************************/
char ** rassemler_mots(char ** s ,int size , unsigned nb_mots){

  char ** mots = malloc(nb_mots*sizeof(*mots));

  for (size_t i = 0; i < nb_mots; i++) {
    mots[i] = malloc(50*sizeof(char));
    }

  int k=0;
  if(s[0][1] == '*'){
    s[0][1] = '\0';
    strcpy(mots[k], s[0]);
    k++;
    }
  for (size_t i = 0; i < size-1; i++) {
    int j = 0;
    while(s[i+1][j] == '+'){
      s[i+1][j] = s[i][j];
      j++;
    }
    if (s[i+1][j+1] == '*') {
      s[i+1][j+1] = '\0';
      strcpy(mots[k], s[i+1]);
      k++;
    }
  }
  for (size_t i = 0; i < size; i++) {
    free(s[i]);
    s[i] = NULL;
  }
  return mots;
}

/*****************************************************/
void print_mots(char ** s, int size){
  size_t i = 0;
  for ( i = 0 ; i < size-1 ; i++) {
    printf("%s, ", s[i] );
  }
  printf("%s\n", s[size -1]);
}

/*****************************************************/

void print_dico(dico d){

  for (size_t i = 0; i < NB_KEYS; i++) {
    if(d[i] != NULL )
    {
      unsigned nb_nodes = nb_nodes_tree(d[i]);
      unsigned nb_mots = nb_words_tree(d[i]);

      char ** s = malloc(nb_nodes*sizeof(*s));
      for (size_t i = 0; i < nb_nodes; i++) {
        s[i] = malloc(50*sizeof(char));
      }
      sprint_tree(d[i],0,s);
      char ** mots = rassemler_mots(s ,nb_nodes, nb_mots);

      print_mots(mots, nb_mots);
      free(s); // *(s+i) sont sésalouées par la fonction rassemler_mots;
      s=NULL;
      for (size_t i = 0; i < nb_mots; i++) {
        free(mots[i]);
        mots[i] = NULL;
      }
      free(mots);
      mots = NULL;
      indice = 0; // variable gobale utilisée dans la première fonction

    }
  }
}

/******************************************************/

iterator * start_iterator(dico d){
  iterator * it = malloc(sizeof(*it));
  it->word = malloc(height(d)*sizeof(char));
  it->stack = malloc(nb_nodes(d)*sizeof(*(it->stack)));
  it->index_stack = 0;
  for (size_t i = 0; i < 26; i++) {
    if(d[i] != NULL){
      it->stack[it->index_stack].t = d[i];
      it->stack[it->index_stack].index_word = 0;
      it->index_stack = it->index_stack + 1;
    }
  }
  return it;
}
/*****************************************************/

char * next (iterator * it){
  struct iterator_info paire_tree;
  do{

  it->index_stack--;
  paire_tree = it->stack[it->index_stack];
  it->word[paire_tree.index_word] = paire_tree.t->first;
  it->word[paire_tree.index_word+1] = '\0';

  for (size_t i = 0; i < 26; i++) {
    if (paire_tree.t->children[i] != NULL) {
      it->stack[it->index_stack].t = paire_tree.t->children[i];
      it->stack[it->index_stack].index_word = paire_tree.index_word +1;
      it->index_stack++;
    }

  }
  }
  while(paire_tree.t->end_of_word != 1);

  return it->word;

}
/*****************************************************/

bool has_next(iterator * it){

  if (it->index_stack == 0) return false;
  return true;
}

/*****************************************************/
void destroy_iterator(iterator ** it){

  free((*it)->word);
  (*it)->word =NULL;

  free((*it)->stack);
  (*it)->stack =NULL;

  free(*it);
  *it = NULL;

}
