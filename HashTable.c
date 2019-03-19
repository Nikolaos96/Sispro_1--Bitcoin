//File: Hash_Table.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTable.h"



 /*
  Pinakas deiktwn - Hash_Table me oliki apokripsi
 */
 typedef struct hash_table{
	deiktis_b arxi;
 }hash_table;



 /*
  Komvos gia ta bucket tou Hash_Table
  Ta Dedomena einai oi user
  H metavliti adeia_thesi mas leei kathe stigmi poses adeies theseis exei to bucket
  Kai o epomenos einai deiktis gia to epomeno bucket yperxilisis
 */
 typedef struct bucket{
 	dedomena_deikti * Dedomena;
	int adeia_thesi;

	deiktis_b epomenos;
 }bucket;



 /*
  Dimiourgeia diktwn gia to Hash_Table
 */
 deiktis_ht HashTable_dimiourgia(deiktis_ht* lista){// Dimiourgia hash_Table

     deiktis_ht linfo;
     linfo = malloc(sizeof(hash_table));
     linfo->arxi = NULL;
     return linfo;
 }



 /*
  Dimiourgeia arxikwn bucket gia kathe thesi tou Hash_Table
 */
 void dimoiourgeia_arxikwn_bucket(deiktis_ht* linfo,int plithos_eggrafon){ // gia kathe deikti tou hash table arxika bucket

     deiktis_b prosorinos = malloc(sizeof(bucket));
     prosorinos->Dedomena = malloc(plithos_eggrafon * sizeof(dedomena_deikti));
     prosorinos->adeia_thesi = plithos_eggrafon;
     prosorinos->epomenos = NULL;
    (*linfo)->arxi = prosorinos;

     return;
 }



 /*
  Eisagwgh user sto Hast_Table.Pernei ws orisma ton deikti tou arxikou bucket,ton xristi
  pros eisagwgh kai to plithos ton xriston pou xorane se ena bucket
  Phgenei sto teleutaio bucket tis lista apo bucket kai ean exei thesi kanei tin eisagwgi
  diaforetika dimiourgei kainourgio bucket kai kanei tin eisagwgh
 */
 void eisagogi_user(deiktis_ht* linfo,char *user,int plithos_eggrafon){

     deiktis_b bucket = (*linfo)->arxi;
     if(bucket == NULL){ printf("First bucket is NULL \n"); return; }

     while(bucket->epomenos != NULL) bucket = bucket->epomenos; // to bucket einai to teleutaio;

     if(bucket->adeia_thesi > 0){
	 bucket->Dedomena[plithos_eggrafon - bucket->adeia_thesi].userId  = malloc((strlen(user)+1) * sizeof(char));
	 strcpy(bucket->Dedomena[plithos_eggrafon - bucket->adeia_thesi].userId, user);
	 bucket->Dedomena[plithos_eggrafon - bucket->adeia_thesi].trans = NULL;

	 bucket->adeia_thesi--;
//	 printf("Eisagwgh se yparxon bucket \n\n");
     }else{
	 deiktis_b new_bucket = malloc(sizeof(deiktis_b));
	 new_bucket->Dedomena = malloc(plithos_eggrafon * sizeof(dedomena_deikti));
	 new_bucket->adeia_thesi = plithos_eggrafon;
	 new_bucket->epomenos = NULL;
	 bucket->epomenos = new_bucket;


	 new_bucket->Dedomena[0].userId = malloc((strlen(user)+1) * sizeof(char));
	 strcpy(new_bucket->Dedomena[0].userId, user);
	 new_bucket->Dedomena[0].trans = NULL;
	 new_bucket->adeia_thesi--;

//	 printf("Eisagwgi se neo bucket \n\n");
     }
     return;
 }



 /*
  Emfanizei ola ta dedomena gia ena bucket h mia lista apo bucket
  Einai gia debug
 */
 void emfanisi_ht(deiktis_ht* linfo,int plithis_eggrafon){

	deiktis_b mapas = (*linfo)->arxi;
	int i;
	while(mapas != NULL){
	    for(i = 0 ; i < plithis_eggrafon - mapas->adeia_thesi ; i++){
		printf("%s \n", mapas->Dedomena[i].userId);

		trans_node *tran = mapas->Dedomena[i].trans;
		while(tran != NULL){
		    printf("id sinalagis %s \n", tran->trans_id);
		    printf("ston i apo %s\n", tran->sender_receiver_user);
		    printf("poso %d\n", tran->value);
		    printf("%d ", tran->day);
		    printf("- %d ", tran->month);
		    printf("- %d  ", tran->year);
		    printf("%d:", tran->time);
		    printf("%d\n\n", tran->minute);

		   tran = tran->next_tran;
		}
	    }
	    mapas = mapas->epomenos;
	}
	return;
 }



 /*
  Diagrafei olla ta bucket apo kapoia thesi tou Hash_Table kai tis listes
  me tis sinalages se auto to bucket
 */
 void HashTable_diagrafi(deiktis_ht* linfo,int plithis_eggrafon){

     deiktis_b mapas = (*linfo)->arxi;
     deiktis_b mapas2;

     int i;
     while(mapas != NULL){
         mapas2 = mapas;
	 mapas = mapas->epomenos;
	 for(i = 0 ; i < plithis_eggrafon - mapas2->adeia_thesi ; i++){
	     free(mapas2->Dedomena[i].userId);
	     trans_node *tran = mapas2->Dedomena[i].trans;
	     trans_node *tran2;
             while(tran != NULL){
		 tran2 = tran;
		 tran = tran->next_tran;
		 free(tran2->sender_receiver_user);
		 free(tran2);
	     }
	 }
	 free(mapas2->Dedomena);
	 free(mapas2);
     }
     (*linfo)->arxi = NULL;
     free(*linfo);
     //(*linfo) = NULL;
     return;
 }



 /*
  Eisagh mias sinalaghs sti lista ton sinalagwn tou xrhsth user
  Vriskei to xrhsth sti lista apo ta bucket kai vazei sti lista tou ta stoixeia mias sinalagis
 */
 trans_node * eisagogi_trans(deiktis_ht* linfo,int plithis_eggrafon,char *user,char *user_trans,char *trans_id,int value,int day,int month,int year,int time,int minute){

    deiktis_b bucket = (*linfo)->arxi;
    int i;

  while(bucket != NULL){
    for(i = 0 ; i < plithis_eggrafon - bucket->adeia_thesi ; i++){
	if(!strcmp(bucket->Dedomena[i].userId,user)){
	    trans_node *tran = bucket->Dedomena[i].trans;

	    if(tran == NULL){
		trans_node *new_tran = malloc(sizeof(trans_list));

		strcpy(new_tran->trans_id,trans_id);
                new_tran->sender_receiver_user = malloc((strlen(user_trans)+1) * sizeof(char));
                strcpy(new_tran->sender_receiver_user,user_trans);

		new_tran->value = value;
		new_tran->day = day;
                new_tran->month = month;
                new_tran->year = year;
                new_tran->time = time;
                new_tran->minute = minute;
                new_tran->next_tran = NULL;

		bucket->Dedomena[i].trans = new_tran;
//		printf("Egine h prwth eisagwgi sti lista tou %s \n", user);
		return new_tran;

	    }else{
		while(tran->next_tran != NULL) tran = tran->next_tran;
		trans_node *new_tran = malloc(sizeof(trans_list));

		strcpy(new_tran->trans_id,trans_id);
		new_tran->sender_receiver_user = malloc((strlen(user_trans)+1) * sizeof(char));
		strcpy(new_tran->sender_receiver_user,user_trans);

		new_tran->value = value;
		new_tran->day = day;
		new_tran->month = month;
		new_tran->year = year;
		new_tran->time = time;
		new_tran->minute = minute;
		new_tran->next_tran = NULL;

		tran->next_tran = new_tran;
//		printf("H eisagwgh egine sti lista tou %s \n", user);
		return new_tran;
	    }
	}
    }
    bucket = bucket->epomenos;
  }
  printf("Den vrika ton %s sto hash table.Den egine i eisagwgh \n\n", user);

 }



 /*
 Sigkrinei imerominies kai wra
 */
 int date1(int last_day,int last_month,int last_year,int last_time,int last_minute,  int day,int month,int year,int tim,int minute){

     if(year >last_year) return 1;
    else if(year == last_year){
        if(month > last_month) return 1;
        else if(month == last_month){
            if(day > last_day) return 1;
            else if(day == last_day){
                if(tim > last_time) return 1;
                else if(tim == last_time){
                        if(minute >= last_minute) return 1;
                        else return 0;
                }else
                    return 0;
            }else
                return 0;
        }else
            return 0;
    }else
        return 0;
 }


 /*
 Sigkrinei mia wra me mia alli
 */
 int ttime(int t1,int m1,int t2,int m2){

     if(t2 > t1) return 1;
     else if(t2 == t1){
	 if(m2 >= m1) return 1;
	 else return 0;
     }else return 0;
 }

 /*
  Emfanizei oles tis sinalages enos xristi eite toy dwseis imeromini kai wra eite oxi eite mono wra
  Kai sinalges pou o xristis einai apostoleas kai paraliptis analoga tin periptwsh
 */
 void find_Earnings_Payments(deiktis_ht* linfo,int plithos_eggrafon,char *user, int time1,int minute1,int day1,int month1,int year1,int time2,int minute2,int day2,int month2,int year2,int kk){

     deiktis_b mapas = (*linfo)->arxi;
     deiktis_b mapas2 = NULL;
     int i, stop = 0, position;

     while(mapas != NULL){
         for(i = 0 ; i < plithos_eggrafon - mapas->adeia_thesi ; i++){
	     if(!strcmp(mapas->Dedomena[i].userId,user)){
		 mapas2= mapas;
		 position = i;
		 stop = 1;
		 break;
	     }
	}
	if(stop) break;
	mapas = mapas->epomenos;
     }
     if(mapas2 == NULL){
	 printf("User does not exist %s \n\n", user);
	 return;
     }


     if(mapas2->Dedomena[position].trans == NULL){
	 printf("O xristis %s den exei sinalages \n\n", user);
	 return;
     }
     trans_node *tran = mapas2->Dedomena[position].trans;
     trans_node *new_tran = tran;
     int sum = 0;

     while(new_tran != NULL){
         sum += new_tran->value;
         new_tran = new_tran->next_tran;
     }


     if(kk == 1){// den exei dothoi imeromini kai wra
	 while(tran != NULL){
	     printf("Transaction id : %s \n", tran->trans_id);
	     printf("Receiver userId : %s \n", tran->sender_receiver_user);
 	     printf("Value : %d \n", tran->value);
	     printf("Date : %d-%d-%d \n", tran->day,tran->month,tran->year);
	     printf("Time : %d:%d  \n\n", tran->time,tran->minute);

	     tran = tran->next_tran;
	 }
	 printf("\nTotal money : %d \n\n", sum);

     }else if(kk == 2){// exoun dothei kai wres kai imerominies

	 while(tran != NULL){
	     if(date1(day1,month1,year1,time1,minute1, tran->day,tran->month,tran->year,tran->time,tran->minute) == 1 &&
                date1(tran->day,tran->month,tran->year,tran->time,tran->minute,day2,month2,year2,time2,minute2) == 1){
                 printf("Transaction id : %s \n", tran->trans_id);
                 printf("Receiver userId : %s \n", tran->sender_receiver_user);
                 printf("Value : %d \n", tran->value);
                 printf("Date : %d-%d-%d \n", tran->day,tran->month,tran->year);
                 printf("Time : %d:%d  \n\n", tran->time,tran->minute);
	     }
             tran = tran->next_tran;
         }
         printf("\nTotal money : %d \n\n", sum);

     }else{// k == 3 exei dwthoi mono wres

	  while(tran != NULL){
		if((ttime(time1,minute1,tran->time,tran->minute) == 1) && (ttime(tran->time,tran->minute,time2,minute2) == 1)){
		    printf("Transaction id : %s \n", tran->trans_id);
		    printf("Receiver userId : %s \n", tran->sender_receiver_user);
		    printf("Value : %d \n", tran->value);
		    printf("Date : %d-%d-%d \n", tran->day,tran->month,tran->year);
		    printf("Time : %d:%d  \n\n", tran->time,tran->minute);
		}
		tran = tran->next_tran;
	  }
	  printf("\nTotal money : %d \n\n", sum);
    }
 }
