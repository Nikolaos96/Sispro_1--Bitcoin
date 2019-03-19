#ifndef __TREE__
#define __TREE__
#include "HashTable.h"

typedef struct typos_komboy * typos_tree;

int g_val;
int g_lock;
int *g_array;


void Tree_dimiourgia(typos_tree *tree);
void Tree_katastrofi(typos_tree *tree);

int Tree_keno(typos_tree tree);
void Tree_eisagogi_arxi(typos_tree *tree,char *name,int val);

void Tree_eisagogi_meta(typos_tree *tree,char *sender,char *receiver,trans_node *tran1,trans_node *tran2, int pos);
int Tree_periexomeno(typos_tree *tree);

void not_null_pointers_nodes(typos_tree *tree,int *sum);
void unspent(typos_tree *tree,int *value,char *user);

void check_tree(typos_tree *tree,char *user, int *exist);
char * take_name_tree(typos_tree *tree);

void trans_tree(typos_tree *tree);
void emfa(typos_tree *tree);

#endif
