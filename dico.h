#ifndef _DICOH_
#define _DICOH_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define NB_KEYS 26 //Alphabet


/* Structure noeud */
struct node {
    char first;
    bool end_of_word;
    struct node ** children;
};

/* Structure arbre */
typedef struct node * tree;

/* Structure dictionnaire = tableau d'arbres */
typedef struct node ** dico;


/*Structures necessaires pour l'itérateur*/
struct iterator_info {
    tree t;
    int index_word;
};

struct _iterator {
    char * word;
    struct iterator_info * stack;
    int index_stack;
};

typedef struct _iterator iterator;



/*Caractère et indice*/
unsigned get_index(char c);//Donne l'indice d'un caractère
char get_char(unsigned index);//Donne le caractère correponsant à 0=<indice<=25

/*Creation et destruction */
dico create_dico(); // creer un dictionnaire.
void destroy_dico(dico * d); // detruir un dictionnaire

/* Fonctions utilitaires*/
int max(unsigned * tab ,unsigned size); // Retourne le max d'un tableau d'entiers
char* nb_plus(int nb); // Affiche nb fois le caractère '+'

/*Quelques routines sur un dictionnaire*/
unsigned nb_children(tree t); // calcule le nombre de fils d'un noeud
unsigned nb_nodes(dico d);  // calcule le nombre de fils d'un dictionnaire
unsigned height(dico d);  // calcule l'hauteur d'un dictionnaire

/*Appartenance */
bool contains_iter(dico d, char * word, unsigned size); // teste si le "word" appartient au dictionnaire d, itérativement
bool contains_rec(dico d, char * word, unsigned size);  // teste si le "word" appartient au dictionnaire d, récursivement

/*Suppression*/
bool remove_iter(dico d, char * word, unsigned size); // supprime le mot "word" du dictionnaire ,elle retourne "true" s'il existe et "False" sinon.
bool remove_rec(dico d, char * word, unsigned size);  // idem d'une manière récursive

/*Addition */
bool add_iter(dico d, char * word, unsigned size); //ajoute le mot "word" dans le dictionnaire ,elle retourne "False" s'il existe déjà et "True" sinon.
bool add_rec(dico d, char * word, unsigned size);  //idem d'une manière récursive

/*Fonctions d'affichage */
void print_tree(tree t , int m); // affiche un arbre d'une manière lisible (+++++a*)
void print_prefix(dico d);       // affiche un dictionnaire d'une manière lisible (+++++a*)
/* Remplit la chaine de carcatère s par les lettres du dictionnaire préfixées du
nombre de '+' leur correpondant.    Exemple s = ["b","+o","++r","+++d",....] */
void sprint_tree(tree t , int decalage ,char ** s);
/* Cette fonction prend en paramètre le tableau de chaines de caractère s de la fonction précédente
et renvoie un autre tableau de chaine de caractères qui contient les mots du dictionnaire */
char ** rassemler_mots(char ** s ,int size , unsigned nb_mots);
void print_mots(char ** s, int size);
void print_dico(dico d);    // affiche les mots d'un dictionnaire


/*Egalité de dictionnaires*/
bool equals_tree(tree t1, tree t2); // teste l'égalité de deux arbres
bool equals(dico d1, dico d2);  // teste l'égalité de deux dicctionnaires




unsigned nb_words(dico d); // retourne le nombre de mot d'un dictionnaire


/***********Partie itérateur***************/
iterator * start_iterator(dico d);//Crée et initialise un itérateur
void destroy_iterator(iterator ** it); //detruit un itérateur
bool has_next(iterator * it);//Permet d'arrêter l'énumération quand tous les mots ont été fournis.
char * next (iterator * it); // Récupére un nouveau mot du dictionnaire


#endif
