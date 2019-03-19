/* bitcoin.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bitcoin_functions.h"
#include "HashTable.h"
#include "my_struct.h"
#include "tree.h"


int main(int argc,char *argv[]){
 char *bitCoinBalancesFile, *transactionsFile;
 int bitCoinValue, senderHashtableNumOfEntries, receiverHashtableNumOfEntries, bucketSize;

 // Pernei ta orismata apo tin grammi entoli kai ta vazei se metavlites
 check_arguments(argc,argv,&bitCoinBalancesFile,&transactionsFile,&bitCoinValue,&senderHashtableNumOfEntries,&receiverHashtableNumOfEntries,&bucketSize);

 int crowd_users, crowd_bitcoins, i, j, lines_trans_file;
 count_users_bitcoins(bitCoinBalancesFile,&crowd_users,&crowd_bitcoins); // Vriskei posa bitcoin kai posoi users yparxoun

 check_for_defference_users(bitCoinBalancesFile,crowd_users);		 // Elegxei oti oloi oi  user einai diaforetikoi
 lines_trans_file = check_for_defference_transaction(transactionsFile);  // Elegxei oti oles oi sinalages exoun diaforetiko id kai epistrefei poses einai

 int plithos_eggrafon_bucket, bucket_size;				// Ypologizei to megethos tou bucket
 bucket_size = sizeof(deiktis_b) + (sizeof(dedomena_deikti)+50);
 plithos_eggrafon_bucket = bucketSize / bucket_size;
 if(plithos_eggrafon_bucket <= 0){ printf("The bucket does not have enough size. \n"); return 1; }



 info_deikti *my_list;							// Dimiourgei tin domi gia tous xristes
 my_list = malloc(crowd_users * sizeof(info_deikti));
 if(my_list == NULL){
     printf("\nError memory my_list. \n\n");
     return 1;
 }


 typos_tree *tree;							// Dimiourgei ta dedra gia ta bitcoin
 tree = malloc(crowd_bitcoins * sizeof(typos_tree));
 if(tree == NULL){
     printf("\nError memory tree. \n\n");
     return 1;
 }
 for(i = 0 ; i < crowd_bitcoins ; i++) Tree_dimiourgia(&tree[i]);


 deiktis_ht *senderHashTable, *receiverHashTable;			// Ta 2 hash_Table
 senderHashTable = malloc(senderHashtableNumOfEntries * sizeof(deiktis_ht));
 if(senderHashTable == NULL) { printf("Error malloc memory senderHashTable. \n\n"); return 1; }
 for(i = 0 ; i < senderHashtableNumOfEntries ; i++){
     senderHashTable[i] = HashTable_dimiourgia(&senderHashTable[i]);
     dimoiourgeia_arxikwn_bucket(&senderHashTable[i],plithos_eggrafon_bucket);
 }


 receiverHashTable = malloc(receiverHashtableNumOfEntries * sizeof(deiktis_ht));
 if(receiverHashTable == NULL) { printf("Error malloc memory receiverHashTable. \n\n"); return 1; }
 for(i = 0 ; i < receiverHashtableNumOfEntries ; i++){
     receiverHashTable[i] = HashTable_dimiourgia(&receiverHashTable[i]);
     dimoiourgeia_arxikwn_bucket(&receiverHashTable[i],plithos_eggrafon_bucket);
 }



 int *array_coin = malloc(crowd_bitcoins * sizeof(int));		 // enas pinakas me ola ta coinId - einai parallilos me to dendro
 if(array_coin == NULL){ printf("Error malloc array_coin. \n"); return 1;}// Diladi to coin sti thesi 5 tou pinaka autou antistixei stin 5h thesi tou tree

// printf("Bitcoins : %d \nTransactions : %d \nUsers : %d \nValue bitcoin : %d\nSize_SenderHT : %d \nSize_ReceiverHT : %d \nSize_bucket : %d \nTrans File OK\nCoins File OK\n\n", crowd_bitcoins, lines_trans_file, crowd_users, bitCoinValue,senderHashtableNumOfEntries,receiverHashtableNumOfEntries,plithos_eggrafon_bucket);

 g_array = calloc(crowd_bitcoins, sizeof(int));				// global array ton xreiazomai argotera gia to tree
 if(g_array == NULL){ printf("Error malloc g_array. \n"); return 1; }



//  To parakatw for kanei isagwgh ton xrhston kai ton bitcoin pou exoun sti domi pou exei tis plirofories gia kathe xrhsth.
//  Dimiourgei ton proto komvo dendrou gia kathe bitcoin.
//  Elegxei oti ola ta bitcoin einai diaforetika.
//  Kanei eisagwgh ton xrhston sta hash table

 FILE *fp;
 fp = fopen(bitCoinBalancesFile,"r");
 char name[60];
 int coin_id, value, tree_elem = 0,   error;

 for(i = 0 ; i < crowd_users ; i++){
     if(fscanf(fp, "%s", name) != 1) break;

     my_list[i] = LIST_dimiourgia(&my_list[i],name);
     eisagogi_user(&senderHashTable[hash_function(name,senderHashtableNumOfEntries)],     name,plithos_eggrafon_bucket);
     eisagogi_user(&receiverHashTable[hash_function(name,receiverHashtableNumOfEntries)], name,plithos_eggrafon_bucket);

     while(1){
	if(fscanf(fp, "%d", &coin_id) != 1) break;
	value = bitCoinValue;
	if(tree_elem == 0){
	    array_coin[tree_elem] = coin_id;
	    Tree_eisagogi_arxi(&tree[tree_elem],name,value);
	    tree_elem++;
	}else{
	    for(j = 0 ; j < tree_elem ; j++){
		if(array_coin[j] == coin_id){
		     printf("Bitcoin %d exist.Exit of programm. \n", coin_id);
		     return 1;
		}
	    }
	    array_coin[tree_elem] = coin_id;
	    Tree_eisagogi_arxi(&tree[tree_elem],name,value);
	    tree_elem++;
	}
	eisagogi(&my_list[i],coin_id,value);
    }
 }
 fclose(fp);
 int last_day, last_month, last_year, last_time, last_minute, max = -1;

 // Arxikopoisi domon me to arxeio sinalagon
 transactions_function_file(transactionsFile, &senderHashTable[0],senderHashtableNumOfEntries, &receiverHashTable[0],receiverHashtableNumOfEntries,
                         &my_list[0],crowd_users, &tree[0],crowd_bitcoins, plithos_eggrafon_bucket,lines_trans_file,
 			   &last_day, &last_month, &last_year, &last_time, &last_minute, &max, 1, &array_coin[0], crowd_bitcoins);


 // Akolouthei to while opou dinontai ta erwtimata
 max++;
 char str[1000], *token;
 while(1){
     printf("\nGive me a command : ");
     fgets(str, sizeof(str), stdin);
     if(!strcmp(str,"\n")){ printf("Error command.\n"); continue; }
     int protaseis = pro(str);
     token = strtok(str, " ,.-:;\n");
     if(!strcmp(token,"/requestTransaction")){
         token = strtok(NULL, " ,.-:;\n");
	 if(token == NULL) continue;
	 char sender[60], receiver[60], id[25];
	 int amount, day, month, year, tim, second;

	 sprintf(id, "%d", max);
	 max++;
	 strcpy(sender,token);	     token = strtok(NULL, " ,.-:;\n");
	 strcpy(receiver,token);     token = strtok(NULL, " ,.-:;\n");
	 amount = atoi(token);       token = strtok(NULL, " ,.-:;\n");
	 if(token != NULL){ // exei dwsei kai imerominia kai wra
	     printf("Given date and time. \n");
	     day = atoi(token);      token = strtok(NULL, " ,.-:;\n");
             month = atoi(token);    token = strtok(NULL, " ,.-:;\n");
	     year = atoi(token);     token = strtok(NULL, " ,.-:;\n");
	     tim = atoi(token);      token = strtok(NULL, " ,.-:;\n");
	     second = atoi(token);
	  }else{	// an den dwsei imerominia kai wra pare ta trexonta
	      printf("Not given date and time. \n");
	      current_date(&day, &month, &year, &tim, &second);
	  }
          transactions_function_command(&senderHashTable[0],senderHashtableNumOfEntries, &receiverHashTable[0],receiverHashtableNumOfEntries,
                         		&my_list[0],crowd_users, &tree[0],crowd_bitcoins, plithos_eggrafon_bucket, &array_coin[0], crowd_bitcoins,
   				        &last_day, &last_month, &last_year, &last_time, &last_minute, id, sender, receiver, amount,
   			    	        day, month, year, tim, second );

     }else if(!strcmp(token,"/requestTransactions")){
	 token = strtok(NULL, " ,-:;\n");
	 if(token == NULL) continue;
         char st[30];
         if(token != NULL) strcpy(st,token);
	 else continue;
         token = strtok(NULL, " ,-:;\n");
         if(token == NULL){ //Dothhike arxeio
             transactions_function_command_file(st,&senderHashTable[0],senderHashtableNumOfEntries, &receiverHashTable[0],receiverHashtableNumOfEntries,
 					        &my_list[0],crowd_users, &tree[0],crowd_bitcoins, plithos_eggrafon_bucket, &array_coin[0], crowd_bitcoins,
					        &last_day, &last_month, &last_year, &last_time, &last_minute, &max);
             printf("\nTransactions from the file were completed. \n\n");
         }else{		// Dothikan poles sinallages
             int l;
             for(l = 0 ; l < protaseis ; l++){
                 char sender[60], receiver[60], id[25];
                 int amount, day, month, year, tim, second;
		 sprintf(id, "%d", max);
         	 max++;
		 if(l == 0){ printf("Press enter to continue for first transaction  "); getchar(); }
		 else{ printf("Press enter to continue for next transaction "); getchar(); }

                 if(l == 0){ strcpy(sender,st);}
                 else { strcpy(sender,token);	token = strtok(NULL," ,.-:;\n");}

                 strcpy(receiver,token);     token = strtok(NULL, " ,.-:;\n");
                 amount = atoi(token);       token = strtok(NULL, " ,.-:;\n");

		 if(token != NULL){
		     if(atoi(token) == 0){
		         current_date(&day, &month, &year, &tim, &second);
		     }else{
                         day = atoi(token);      token = strtok(NULL, " ,.-:;\n");
                         month = atoi(token);    token = strtok(NULL, " ,.-:;\n");
                         year = atoi(token);     token = strtok(NULL, " ,.-:;\n");
                         tim = atoi(token);      token = strtok(NULL, " ,.-:;\n");
                         second = atoi(token);   token = strtok(NULL, " ,.-:;\n");
		     }
		 }else{
		     current_date(&day, &month, &year, &tim, &second);
		 }

		 transactions_function_command(&senderHashTable[0],senderHashtableNumOfEntries, &receiverHashTable[0],receiverHashtableNumOfEntries,
                                               &my_list[0],crowd_users, &tree[0],crowd_bitcoins, plithos_eggrafon_bucket, &array_coin[0], crowd_bitcoins,
                                               &last_day, &last_month, &last_year, &last_time, &last_minute, id, sender, receiver, amount,
                                               day, month, year, tim, second );
             }
        }
     }else if(!strcmp(token,"/findEarnings") || !strcmp(token,"/findPayments")){
         int Earnings = 0;
     	 if(!strcmp(token,"/findEarnings"))Earnings = 1;
	 token = strtok(NULL, " ,.-:;\n");
	 if(token == NULL) continue;
	 char walletId[60];
	 strcpy(walletId,token);
	 token = strtok(NULL, " ,.-:;\n");
         if(user_exist(&my_list[0],crowd_users,walletId)){
	     if(token == NULL) { // Ta emfanizei ola epeidi den dothikan stoixei gia imeromini kai wra
		 printf("Not given date and time. \n");
	     	 if(Earnings) find_Earnings_Payments(&receiverHashTable[hash_function(walletId,receiverHashtableNumOfEntries)],plithos_eggrafon_bucket,walletId,0,0,0,0,0,0,0,0,0,0,1);
	     	 else 	      find_Earnings_Payments(&senderHashTable[hash_function(walletId,senderHashtableNumOfEntries)],plithos_eggrafon_bucket,walletId,0,0,0,0,0,0,0,0,0,0,1);
	     }else{ // emfanizei mono auta pou einai endiamesa stis imerominies
		 int a, b, c, d;
		 a = atoi(token);	token = strtok(NULL, " ,.-:;\n");
	 	 b = atoi(token);	token = strtok(NULL, " ,.-:;\n");
		 c = atoi(token);	token = strtok(NULL, " ,.-:;\n");
		 d = atoi(token);	token = strtok(NULL, " ,.-:;\n");
		 if(token == NULL){// exei dwsei mono wra
		     int time1_t = a, time1_min = b;
		     int time2_t = c, time2_min = d;
		     if(Earnings) find_Earnings_Payments(&receiverHashTable[hash_function(walletId,receiverHashtableNumOfEntries)],plithos_eggrafon_bucket,walletId,time1_t,time1_min,0,0,0,time2_t,time2_min,0,0,0,3);
		     else	  find_Earnings_Payments(&senderHashTable[hash_function(walletId,senderHashtableNumOfEntries)],plithos_eggrafon_bucket,walletId,time1_t,time1_min,0,0,0,time2_t,time2_min,0,0,0,3);
		    printf("Given only time. \n");
		 }else{// exei dwsei kai wra kai imerominia
	             int time1_t = a;
	     	     int time1_min = b;
		     int year1_day = c;
		     int year1_month = d;
		     int year1_year = atoi(token);	token = strtok(NULL, " ,.-:;\n");
		     int time2_t = atoi(token);		token = strtok(NULL, " ,.-:;\n");
	     	     int time2_min = atoi(token);	token = strtok(NULL, " ,.-:;\n");
	     	     int year2_day = atoi(token);	token = strtok(NULL, " ,.-:;\n");
		     int year2_month = atoi(token);	token = strtok(NULL, " ,.-:;\n");
		     int year2_year = atoi(token);

	 	     if(Earnings) find_Earnings_Payments(&receiverHashTable[hash_function(walletId,receiverHashtableNumOfEntries)],plithos_eggrafon_bucket,walletId,time1_t,time1_min,year1_day,year1_month,year1_year,time2_t,time2_min,year2_day,year2_month,year2_year,2);
		     else 	  find_Earnings_Payments(&senderHashTable[hash_function(walletId,senderHashtableNumOfEntries)],plithos_eggrafon_bucket,walletId,time1_t,time1_min,year1_day,year1_month,year1_year,time2_t,time2_min,year2_day,year2_month,year2_year,2);

		     printf("Given date and time. \n");
		 }
	     }
	 }else
	      printf("User does not exist. \n");

     }else if(!strcmp(token,"/walletStatus")){

         token = strtok(NULL, " ,.-:\n");
	 if(token == NULL) continue;
	 char walletId[60];
	 strcpy(walletId,token);
	 if( user_exist(&my_list[0],crowd_users,walletId) )
	     printf("Total balance of %s is %d \n\n", walletId,walletStatus_function(&my_list[0],crowd_users,walletId));
	 else printf("User does not exist. \n");

     }else if(!strcmp(token,"/bitCoinStatus")){

         token = strtok(NULL, " ,.-:\n");
	 if(token == NULL) continue;
	 int bitCoinId = atoi(token);
	 if( bitcoin_exist(&array_coin[0],crowd_bitcoins,bitCoinId))
	     bitCoinStatus_function(&tree[0], crowd_bitcoins, bitCoinId, &array_coin[0], crowd_bitcoins);
	 else printf("Bitcoin does not exist. \n");

     }else if(!strcmp(token,"/traceCoin")){

	 token = strtok(NULL, " ,.-:\n");
	 if(token == NULL) continue;
	 int bitCoinId = atoi(token);
	 if( bitcoin_exist(&array_coin[0],crowd_bitcoins,bitCoinId))
	     traceCoin_function(&tree[0],crowd_bitcoins, bitCoinId, &array_coin[0], crowd_bitcoins);
	 else printf("Bitcoin does not exist. \n");

     }else if(!strcmp(token,"/exit")){

	 printf("Exit of program.\n\nGoodbye\n\n");
	 exit_function(&senderHashTable[0],senderHashtableNumOfEntries, &receiverHashTable[0],receiverHashtableNumOfEntries,
		       &my_list[0],crowd_users, &tree[0],crowd_bitcoins, plithos_eggrafon_bucket);
         break;

     }else
	printf("Error.Give command again. \n");
 }

    free(g_array);
    free(my_list);
    free(tree);
    free(senderHashTable);
    free(receiverHashTable);
    free(array_coin);
    free(bitCoinBalancesFile);
    free(transactionsFile);

    return 0;
    //exit(0);
}
