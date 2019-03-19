//File: lista.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_struct.h"

 /*
 H domi pou epeleksa gia na apothikeusw tis plirofories gia kathe xrhsth kai ta
 bitcoin pou exei einai enas pinakas apo listes opou kathe lista exei komvo kefali.
 O komvos kefali krataei tis to userid kai to sinoliko poso pou exei apo ta bitcoin.
 O komvos kefaliexei 2 deiktes arxi kai telos gia tin lista me ta bitcoin tou xrhsth.
 H poliplokotita gia na vroume kapoio xrhsth an exoume n xrhstes einai O(n).
 H poliplokotita gia na vroume ena bitcoin kapoiou xristh an autos exei k bitcoins
 einai O(k).
 */



 /*
 Komvos kefali me ta stoixeia tou xristi
 */
 typedef struct info_node{
	char *user_id;
	int total_balance;
 	int size;
	typos_deikti arxi;
	typos_deikti telos;
 }info_node;



 /*
 Komvos gia bitcoin
 */
 typedef struct typos_komvou{
	int bitcoin_id;
 	int initial_value;
	int balance_bitcoin;
	typos_deikti epomenos;
	typos_deikti proigoumenos;
 }typos_komvou;



 /*
 Dimiourgei ton komvo kefali gia kapoio user
 */
 info_deikti LIST_dimiourgia(info_deikti* lista,char name[]){

 	info_deikti linfo;
 	linfo = malloc(sizeof(info_node));

	linfo->user_id = malloc((strlen(name)+1) * sizeof(char));
	strcpy(linfo->user_id,name);
	linfo->total_balance = 0;

 	linfo->size = 0;
 	linfo->arxi = NULL;
	linfo->telos = NULL;
//	printf("Dimiourgeia user_id\n");
 	return linfo;
 }



 /*
 Eisagwgh bitcoin gia kapoio user sti lista tou meta bitcoin pou exei
 */
 void eisagogi(info_deikti* linfo,int coin_id,int value){

 	typos_deikti prosorinos;
 	prosorinos = malloc(sizeof(typos_komvou));

 	prosorinos->bitcoin_id = coin_id;
	prosorinos->initial_value = value;
	prosorinos->balance_bitcoin = value;

 	if((*linfo)->size == 0){
 		(*linfo)->arxi = prosorinos;
		(*linfo)->telos = prosorinos;
		prosorinos->epomenos = NULL;
		prosorinos->proigoumenos = NULL;

 	}
 	if((*linfo)->size > 0){
		prosorinos->proigoumenos = (*linfo)->telos;
		prosorinos->epomenos = NULL;
 		(*linfo)->telos->epomenos = prosorinos;
		(*linfo)->telos = prosorinos;
 	}
	(*linfo)->total_balance += value;
 	(*linfo)->size++;
 }



 /*
 Emfanizei plirofories gia kapoio xrhsth
 Einai gia debug
 */
 void emfanisi(info_deikti* linfo){
	printf("Onoma user  %s\n", (*linfo)->user_id);
//	printf("Sinoliko poso sto portofoli  %d\n", (*linfo)->total_balance);
//	printf("Megethos listas apo bitcoin   %d\n", (*linfo)->size);

	typos_deikti mapas = (*linfo)->arxi;
	printf(" \n ");
 	while(mapas != NULL){
 		printf("bitcoin id           %d\n", mapas->bitcoin_id);
//		printf("bitcoin arxiki timi  %d\n", mapas->initial_value);
//		printf("bitcoin ypoloipo     %d\n", mapas->balance_bitcoin);
		mapas = mapas->epomenos;
 	}
	printf(" \n ");
 }



 /*
 Diagrafei ton komvo kefali kai tin lista apo ta bitcoin
 gia kapoio user
 */
 void lista_diagrafi(info_deikti* linfo){

 	typos_deikti mapas = (*linfo)->arxi;
	typos_deikti mapas2;

 	while(mapas != NULL){
		mapas2 = mapas;
		mapas = mapas->epomenos;
		free(mapas2);
	}
	free((*linfo)->user_id);
	(*linfo)->arxi = NULL;
	(*linfo)->telos = NULL;
	(*linfo)->size = 0;
	free(*linfo);
	(*linfo) = NULL;
 }



 /*
 Diagrafei ena bitcoin kapoiou user.Diladi ena komvo apo tin lista me ta
 bitcoins
 */
 void diagrafi_komvou(info_deikti* linfo, int coin_id){

	typos_deikti mapas = (*linfo)->arxi;
	typos_deikti mapas2;

	if(mapas != NULL){
	    //Prepei na dei an o user exei auto to bitcoin
	    if(look_if_bitcoin_exist(linfo,coin_id) == 1){
	        while(mapas->bitcoin_id != coin_id){
		    mapas = mapas->epomenos;
	        }
	    }else{
		printf("O user den to exei auto to bitcoin \n");
		return;
	    }
	}else{
	    printf("Den exei kanena bitcoin  \n");
	    return;
	}
	mapas2 = mapas;
	if(mapas2 == (*linfo)->arxi && mapas2 == (*linfo)->telos){
		free(mapas2);
		(*linfo)->arxi = NULL;
		(*linfo)->telos = NULL;
		(*linfo)->size--;
	}else if(mapas2 == (*linfo)->arxi){
		(*linfo)->arxi = (*linfo)->arxi->epomenos;
		(*linfo)->arxi->proigoumenos = NULL;
		free(mapas2);
	}else if(mapas2 == (*linfo)->telos){
		(*linfo)->telos = (*linfo)->telos->proigoumenos;
		(*linfo)->telos->epomenos = NULL;
		free(mapas2);
	}else{
		mapas2->proigoumenos->epomenos = mapas2->epomenos;
		mapas2->epomenos->proigoumenos = mapas2->proigoumenos;
		free(mapas2);
	}
	(*linfo)->size--;

 }



 /*
 Epistrefei to sinoliko ypoloipo kapoiou user
 */
 int take_balance(info_deikti* linfo){
	return (*linfo)->total_balance;
 }



 /*
 Epistrefei 1 an o komvos exei ton user pou theloume.
 Xrisimopoieite otan theloume na vroume se poia thesi tou pinaka apo komvous kefales
 yparxei kapoiow user
 */
 int take_name(info_deikti* linfo, char *user){
    if(!strcmp((*linfo)->user_id,user)) return 1;
    else return 0;
 }



 /*
 Koitaei an kapoiow xrhsthhs exei ena sigkekrimeno bitcoin.
 An to exei epistrefei 1.Diaforetika 0.
 */
 int look_if_bitcoin_exist(info_deikti* linfo, int coin_id){ // epistreefei 1 an o user exei to bitcoin me id coin_id allios 0

	typos_deikti mapas = (*linfo)->arxi;
	if(mapas != NULL){
            while(mapas != NULL){
		if(mapas->bitcoin_id == coin_id) return 1;
                mapas = mapas->epomenos;
            }
        }

 	return 0;
 }



 /*
 Kanei set se sto prwto bitcoin tis listas kapoiou xrhsth.
 Mporei na digrapsei auto to bitcoin.
 */
 int set_sender_user_bitcoin(info_deikti* linfo,int *value){

 	typos_deikti mapas = (*linfo)->arxi;
	int poso = (int)*value;

	if(mapas->balance_bitcoin > poso){	// katharizw me tin mia
	    *value = 0;
	    mapas->balance_bitcoin -= poso;
	    (*linfo)->total_balance -= poso;
	    return mapas->bitcoin_id;
	}else if(mapas->balance_bitcoin == poso){// katharizw me tin mia
	    *value = 0;
	    mapas->balance_bitcoin -= poso;
	    int k = mapas->bitcoin_id;
	    diagrafi_komvou(linfo,mapas->bitcoin_id);
	    (*linfo)->total_balance -= poso;
	    return k;
	}else{			// den katharizw me tin mia the lei kai allo bitcoin
	    *value = (poso - mapas->balance_bitcoin);
	    int k = mapas->bitcoin_id;
	    (*linfo)->total_balance -= mapas->balance_bitcoin;
	    diagrafi_komvou(linfo,mapas->bitcoin_id);
	    return k;
	}
 }



 /*
 Allazei to ypoloipo enos bitcoin kapoiou xrhsth kata thn diarkeia mias sinalagis
 */
 void change_balance_bitcoin_receiver(info_deikti* linfo, int coin_id,int value){

	typos_deikti mapas = (*linfo)->arxi;
	(*linfo)->total_balance += value;

        if(mapas != NULL){
            //Prepei na dei an o user exei auto to bitcoin
            if(look_if_bitcoin_exist(linfo,coin_id) == 1){
                while(mapas->bitcoin_id != coin_id){
                    mapas = mapas->epomenos;
                }
            }else{
                printf("O user den to exei auto to bitcoin \n");
                return;
            }
        }else{
            printf("Den exei kanena bitcoin  \n");
            return;
        }
	mapas->balance_bitcoin += value;
 }



 /*
 Vriskei an ypaxei kapoios xrhsths ston pinaka me tou komvous kefales.
 An nai epistrefei 1.Diaforetika 0.
 */
 int user_exist(info_deikti* linfo,int size,char *user){
     int i;
     for(i = 0 ; i < size ; i++){
	if(take_name(&linfo[i],user)) return 1;
     }
     return 0;
 }
