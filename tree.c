/* tree.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"



 /*
 Komvos dedrou.Periexei to onoma tou xristi pou exei arxika to bitcoin h to onoma
 enos pou to apokta meta.
 to poso pou exei arxika to bitcoin h to poso pou apokta meta tin sinalagi o xristis.
 2 deiktes gia aristero kai dexi paidi.Mporei kapoios komvos na min exei kai ta 2 paidia.
 2 deiktes gia ta hash Table.
 */
 typedef struct typos_komboy{
	char *user_id;
	int value;

	typos_tree apaidi;
	typos_tree dpaidi;

	trans_node * send;
	trans_node * receiv;
 } typos_komboy;



 void Tree_dimiourgia(typos_tree *tree){

	*tree=NULL;
 }



 /*
 Diagrafei olo to dendro
 */
 void Tree_katastrofi(typos_tree *tree){

	if(Tree_keno(*tree))
		return;

	Tree_katastrofi(&(*tree)->apaidi);
	Tree_katastrofi(&(*tree)->dpaidi);
	free((*tree)->user_id);
	free(*tree);
	*tree=NULL;
 }



 /*
 Epistrefei 1 an o deiktis pou deixnei se kapoio dendro einai NULL diladi
 den yparxei dendro.Diaforetika 0.
 */
 int Tree_keno(typos_tree tree){
 	return (tree==NULL);
 }



 /*
 Dimiourgei ton arxiko komvo kathe bitcoin.
 Diladi poios exei arxika to kathe bitcoin.
 */
 void Tree_eisagogi_arxi(typos_tree *tree,char *name,int val){

	if(Tree_keno(*tree)){
		*tree=malloc(sizeof(typos_komboy));

		(*tree)->user_id = malloc((strlen(name) + 1) * sizeof(char));
		strcpy((*tree)->user_id, name);
		(*tree)->value = val;

		(*tree)->apaidi=NULL;
		(*tree)->dpaidi=NULL;

		(*tree)->send = NULL;
		(*tree)->receiv = NULL;
	}
 }



 /*
 Prosthetei komvous sto dendro kapoiou bitcoin.
 Diasxizei to dendro tou bitcoin pou dinei o sender ston receiver kai otan vrei
 */
 void Tree_eisagogi_meta(typos_tree *tree,char *sender,char *receiver,trans_node *tran1, trans_node *tran2, int pos){

	if(Tree_keno(*tree))
                return;

        Tree_eisagogi_meta(&(*tree)->apaidi,sender,receiver, tran1, tran2, pos);
        Tree_eisagogi_meta(&(*tree)->dpaidi,sender,receiver, tran1, tran2, pos);
        if((*tree)->apaidi == NULL && (*tree)->dpaidi == NULL && strcmp((*tree)->user_id,sender) == 0 && g_val > 0)
        {

		if(g_val >= (*tree)->value){// dimiourgite mono o aristeros komvos
		    g_val -= (*tree)->value;

		    typos_tree new1 = malloc(sizeof(typos_komboy));
		    new1->value = (*tree)->value;
		    new1->user_id = malloc((strlen(receiver)+1) * sizeof(char));
		    strcpy(new1->user_id,receiver);
		    new1->apaidi = NULL;
		    new1->dpaidi = NULL;

		    if(g_lock == 1){
		        new1->send = tran1;
		        new1->receiv = tran2;
			g_lock = 0;
		    }else{
			new1->send = NULL;
			new1->receiv = NULL;
			g_array[pos] += 1;
		    }
		    (*tree)->apaidi = new1;
		    (*tree)->dpaidi = NULL;

 		}else{// kai oi 2 komvoi

		    typos_tree new1 = malloc(sizeof(typos_komboy));
		    typos_tree new2 = malloc(sizeof(typos_komboy));

		    new1->value = g_val;
		    new2->value = (*tree)->value - g_val;

		    g_val = 0;

		    new1->user_id = malloc((strlen(receiver)+1) * sizeof(char));
		    strcpy(new1->user_id,receiver);

		    if(g_lock == 1){
                        new1->send = tran1;
                        new1->receiv = tran2;
                        g_lock = 0;
                    }else{
                        new1->send = NULL;
                        new1->receiv = NULL;
			g_array[pos] += 1;
                    }
		    (*tree)->apaidi = new1;

		    new2->user_id = malloc((strlen(sender)+1) * sizeof(char));
		    strcpy(new2->user_id,sender);
		    new2->apaidi = NULL;
		    new2->dpaidi = NULL;

		    new2->send = NULL;
		    new2->receiv = NULL;
		    (*tree)->dpaidi = new2;
		}
	}
 }



 /*
 arithmos sinalagon pou simetexei to bitcoin
 */
 void not_null_pointers_nodes(typos_tree *tree,int *sum){// prepei to sum na einai 0 otan to kalesw

	if(Tree_keno(*tree))
                return;

	not_null_pointers_nodes(&(*tree)->apaidi,&(*sum));
	not_null_pointers_nodes(&(*tree)->dpaidi,&(*sum));

	if(((*tree)->apaidi != NULL  && (*tree)->dpaidi != NULL) || (*tree)->apaidi != NULL) (*sum)++;
 }



 /*
 Efoson yparxei ypoloipo se kapoio bitcoin to vriskei kai to pairnei
 */
 void unspent(typos_tree *tree,int *value,char *user){// poso tou bitcoin pou den exei xrisimopoiithei

	if(Tree_keno(*tree))
	    return;

	unspent(&(*tree)->dpaidi,&(*value),user);
	if((*tree)->apaidi == NULL && (*tree)->dpaidi == NULL && strcmp((*tree)->user_id,user) == 0)
	    *value = (*tree)->value;
 }



 /*
 Koitaei an yparxei komvos poy exei mono ena paidi kai o user einai o arxikos.
 Tote auto simainei oti den exei meinei katholou ypoloipo apo to bitcoin
 */
 void check_tree(typos_tree *tree,char *user, int *exist){

	if(Tree_keno(*tree))
	    return;

	check_tree(&(*tree)->dpaidi,user,&(*exist));
	if((*tree)->apaidi != NULL && (*tree)->dpaidi == NULL && strcmp((*tree)->user_id,user) == 0)
	    *exist = 1;
 }



 /*
 Epistrefei to user_id kapoiou komvou
 */
 char * take_name_tree(typos_tree *tree){
	return (*tree)->user_id;
 }



 /*
 Ektyponei tis sinalages kapoiou bitcoin
 Den yparxei epanalipsi sta apotelesmata
 */
 void trans_tree(typos_tree *tree){

	if(Tree_keno(*tree))
                return;

	trans_tree(&(*tree)->apaidi);
        trans_tree(&(*tree)->dpaidi);
	if((*tree)->send != NULL && (*tree)->receiv != NULL){
		trans_node *tt = (*tree)->send;
		trans_node *tt2 = (*tree)->receiv;

		printf("%s %s %s %d ", tt->trans_id,tt2->sender_receiver_user,tt->sender_receiver_user, tt->value);
		printf("%d-%d-%d  %d:%d  \n", tt->day, tt->month, tt->year ,tt->time, tt->minute);
	}
 }



 /*
 for debug
 */
 void emfa(typos_tree *tree){

        if(Tree_keno(*tree))
                return;

        emfa(&(*tree)->apaidi);
        emfa(&(*tree)->dpaidi);
           printf("\n%s\n", (*tree)->user_id);
           printf("%d\n\n",(*tree)->value);
	   if((*tree)->send != NULL && (*tree)->receiv != NULL){


		trans_node *tt = (*tree)->send;
                trans_node *tt2 = (*tree)->receiv;

//		printf("%s %s %s %d ", tt->trans_id,tt2->sender_receiver_user,tt->sender_receiver_user, tt->value);
  //              printf("%d-%d-%d  %d:%d  \n", tt->day, tt->month, tt->year ,tt->time, tt->minute);
	 }
 }
