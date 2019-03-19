/* bitcoin_functions.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "my_struct.h"
#include "HashTable.h"
#include "tree.h"


 /*
 Elegxoi oti dothikan ola taorismata pou prepei
 Pairnei ta orismata apo th grammi entolvon
 */
 void check_arguments(int argc,char *argv[],char **bitCoinBalancesFile, char **transactionsFile,int *nitCoinValue,
		     int *senderHashtableNumOfEntries, int *receiverHashtableNumOfEntries, int *bucketSize){

    char *arg;
    if(argc != 13 ){
        printf("\nError in arguments command line. \n\n");
        exit(EXIT_FAILURE);
    }

    while(--argc){
        arg = *++argv;
        if(!strcmp(arg, "-a")){
	  *bitCoinBalancesFile = malloc((strlen(*++argv) + 1) * sizeof(char));
	  strcpy(*bitCoinBalancesFile,*argv);
        }else if(!strcmp(arg, "-t")){
	    *transactionsFile = malloc((strlen(*++argv) + 1) * sizeof(char));
	    strcpy(*transactionsFile,*argv);
        }else if(!strcmp(arg, "-v")){
	    *nitCoinValue = atoi(*++argv);
        }else if(!strcmp(arg, "-h1")){
	    *senderHashtableNumOfEntries = atoi(*++argv);
	}else if(!strcmp(arg, "-h2")){
	    *receiverHashtableNumOfEntries = atoi(*++argv);
	}else if(!strcmp(arg, "-b")){
	    *bucketSize = atoi(*++argv);
	}
        if(argc > 1) argc--;
    }
    return;
 }


 /*
 Perneis thn trexousa wra kai imerominia
 */
 void current_date(int *day,int *month,int *year,int *tim,int *minute){

     time_t rawtime;
     struct tm * timeinfo;
     time(&rawtime);
     timeinfo = localtime(&rawtime);

     *day = timeinfo->tm_mday;
     *month = timeinfo->tm_mon + 1;
     *year = timeinfo->tm_year + 1900;
     *tim = timeinfo->tm_hour;
     *minute = timeinfo->tm_min;
     return;
 }



/*
  Metraei posoi users yparxoun kai posa bitcoin
  oi user sto a, ta bitcoin sto b
*/
void count_users_bitcoins(char *file,int *a,int *b){

 FILE *fp;
 if ((fp = fopen(file,"r")) == NULL){
     fprintf(stderr, "File %s doesnt exist?! \n", file);
     exit(EXIT_FAILURE);
 }

 int k, a1=0, b1=0;
 char A[60];
 while(1){
        if(fscanf(fp, "%s", A) != 1) break;
        a1++;
        while(1){
                if(fscanf(fp, "%d", &k) != 1) break;
//                printf("%d\n", k);
                b1++;
        }
 }

 fclose(fp);
 *a = a1;
 *b = b1;
 return;
}



/*
 Elegxeio oti to arxeio me ta onomata kai ta bitcoin
 den periexei 2 onomata 2 fores
*/
void check_for_defference_users(char *file,int users){
 FILE *fp;
 if ((fp = fopen(file,"r")) == NULL){
     fprintf(stderr, "File %s doesnt exist?! \n", file);
     exit(EXIT_FAILURE);
 }

 char **userId;
 int i, kk = 0, k ,j;
 userId = (char**) malloc(users * sizeof(char*));
 for(i = 0 ; i < users ; i++) userId[i] = (char*) malloc(60 * sizeof(char));

 char A[60];
 for(i = 0 ; i < users ; i++){
        if(fscanf(fp, "%s", A) != 1) break;
        if(kk == 0) { strcpy(userId[0],A); kk++; }
        else{
            for(j = 0 ; j < kk ; j++){
                if(!strcmp(userId[j],A)){ printf("Exist same names { %s }\n\n", A); exit(EXIT_FAILURE); }
            }
            strcpy(userId[kk],A);
            kk++;
        }
        while(1){
                if(fscanf(fp, "%d", &k) != 1) break;
        }
 }
 fclose(fp);

 for(i = 0 ; i < users ; i++) free(userId[i]);
 free(userId);
 return;
}



 /*
  Elegxei oti kathe sinalagi exei diaforetiko id
 */
 int check_for_defference_transaction(char *file){

    FILE *fp;
    if ((fp = fopen(file,"r")) == NULL){
        fprintf(stderr, "File %s doesnt exist?! \n", file);
        exit(EXIT_FAILURE);
    }

    char ch, B[120], *pch;
    int lines = 0, i, j;
    while(!feof(fp)){
        ch = fgetc(fp);
        if(ch == '\n') lines++;
    }
    fclose(fp);


    fp = fopen(file,"r");
    char **transId = malloc(lines * sizeof(char*));
    for(i = 0 ; i < lines ; i ++) transId[i] = malloc(30 * sizeof(char));

    for(i = 0 ; i < lines ; i++){
        fgets(B,100,fp);
        pch = strtok (B," ,'(");
//        printf("trans id is: %s\n", B);
        if(i == 0) strcpy(transId[i],B);
        else{
            for(j = 0 ; j < i ; j++){
                if( !strcmp(transId[j],B) ){ printf("\nError - Exist same transactions with id { %s } \n\n", B); exit(EXIT_FAILURE); }
            }
            strcpy(transId[i],B);
         }
     }

     fclose(fp);
     for(i = 0 ; i < lines ; i ++) free(transId[i]);
     free(transId);
     return lines;
 }



 /*
  Universal hash function for string
 */
 int hash_function(char* x, int size){
     int h = 12, a, i;
     a=3243;
     for (i=0 ; i < strlen(x) ; ++i)
	h = ((h*a) + x[i]) % size;

     return h % size;
 }



 /*
 Elegxoi tin teleutaia imerominia me me tin epomeni kainourgia
 An diladi h epomeni sinalagi einai metagenesterh tis proigoumenis
 */
 int sheck_date(int last_day,int last_month,int last_year,int last_time,int last_minute,  int day,int month,int year,int tim,int minute){

    if(year >last_year) return 1;
    else if(year == last_year){
	if(month > last_month) return 1;
	else if(month == last_month){
	    if(day > last_day) return 1;
	    else if(day == last_day){
		if(tim > last_time) return 1;
		else if(tim == last_time){
			if(minute > last_minute) return 1;
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
 Epistrefei to ypoloipo kapoiou xrhsth
 Polyplokotita O(n)
 */
 int walletStatus_function(info_deikti *my_list,int size,char *user){// emfanizei to tatal balance tou user me onoma user

    int i;
    for(i = 0 ; i < size ; i++){
        if(take_name(&my_list[i],user)) break;
    }
    if(i < size) return take_balance(&my_list[i]);

    printf("User does not exist. \n");
    return -1;
 }



 /*
 Vriskei se poia thesh tou pinaka deikton tree einai kapoio bitcoin
 Polyplokotita O(n)
 */
 int bitcoin_position_tree(int *array,int size,int bitcoin){

     int i;
     for(i = 0 ; i < size ; i++){
        if(array[i] == bitcoin) return i;
    }
    return -1;
 }



 /*
 Arxikopoihsh domon me tis arxikes sinalages
 */
 void transactions_function_file(char *file,
			   deiktis_ht *senderHT,   int s_senderHT,
			   deiktis_ht *receiverHT, int s_receiverHT,
			   info_deikti *my_struct,int s_mystruct,
			   typos_tree *tree, int s_tree,
			   int eggrafes_bucket,
			   int lines_trans_file,
			   int *last_day, int *last_month, int *last_year,
			   int *last_time, int *last_minute,
			   int *max, int first_run,
			   int *array_coins, int s_array_coins )
{

	FILE *fp;
	int i, j, value, day, month, year, time, minute;
	char sender[70], receiver[70], str[200], *token, tranId[30];

	fp = fopen(file,"r");
	for(i = 0 ; i < lines_trans_file ; i++){
		fgets(str, sizeof(str), (FILE*) fp);

		token = strtok(str, " ,.-:;");
		strcpy(tranId,token);	token = strtok(NULL, " ,.-:;");
		strcpy(sender,token);	token = strtok(NULL, " ,.-:;");
		strcpy(receiver,token); token = strtok(NULL, " ,.-:;");
		value = atoi(token);	token = strtok(NULL, " ,.-:;");
		day = atoi(token);	token = strtok(NULL, " ,.-:;");
		month = atoi(token);	token = strtok(NULL, " ,.-:;");
		year = atoi(token);	token = strtok(NULL, " ,.-:;");
		time = atoi(token);	token = strtok(NULL, " ,.-:;");
		minute = atoi(token);

		if(!strcmp(sender,receiver)){
		//	printf("H sinalagi akironete giati yparxei idios aposteleas kai paraliptis \n");
			continue;
		}
		if(user_exist(&my_struct[0],s_mystruct,sender) == 0){
		//    printf("O xristis %s den yparxei.H sinalagi akironete \n", sender);
		    continue;
		}
		if(user_exist(&my_struct[0],s_mystruct,receiver) == 0){
                //    printf("O xristis %s den yparxei.H sinalagi akironete \n", receiver);
		    continue;
                }
		if(i == 0 && first_run == 1){
			*last_day = day;
			*last_month = month;
			*last_year = year;
			*last_time = time;
			*last_minute = minute;
		}
		if(i != 0 || first_run != 1){
			if(sheck_date((int)*last_day,(int)*last_month,(int)*last_year,(int)*last_time,(int)*last_minute,  day,month,year,time,minute) == 0){
		//		printf("H sinalagi akironete epeidi i imerominia einai lathos \n");
				continue;
			}
			*last_day = day;
			*last_month = month;
			*last_year = year;
			*last_time = time;
			*last_minute = minute;
		}
		if(walletStatus_function(&my_struct[0],s_mystruct,sender) < value){
		//	printf("O xristis den exei eparkes ypoloipo gia tin sinalagi \n");
			continue;
		}
		if(atoi(tranId) > (int)*max) *max = atoi(tranId);

		int index1 = hash_function(sender,s_senderHT);
		int index2 = hash_function(receiver,s_receiverHT);

		trans_node * tran = NULL;
		tran = eisagogi_trans(&senderHT[index1],eggrafes_bucket,sender,receiver,tranId, value,day,month,year,time,minute);
		for(j = 0 ; j < s_mystruct ; j++){
			if(take_name(&my_struct[j],sender) == 1){ index1 = j; break; }
		}


		trans_node * tran2 = NULL;
		tran2 = eisagogi_trans(&receiverHT[index2],eggrafes_bucket,receiver,sender,tranId, value,day,month,year,time,minute);
		for(j = 0 ; j < s_mystruct ; j++){
			if(take_name(&my_struct[j],receiver) == 1){ index2 = j; break; }
		}

		int coin, before_value = value;
		while(value > 0){
			coin = set_sender_user_bitcoin(&my_struct[index1],&value);
			before_value -= value;

			int pos = bitcoin_position_tree(&array_coins[0], s_array_coins, coin);
			g_lock = 1;
			if(pos >= 0){
			    g_val = before_value;
			    Tree_eisagogi_meta(&tree[pos], sender, receiver, tran, tran2, pos);
			}else
			    printf("Bitcoin does not exist. \n");

			if(look_if_bitcoin_exist(&my_struct[index2],coin) == 1) change_balance_bitcoin_receiver(&my_struct[index2],coin,before_value);
			else eisagogi(&my_struct[index2],coin,before_value);

			before_value = value;
		}
	}
	fclose(fp);
	printf("\nFirst transactions OK \n\n");
	return;
 }



 /*
 Paromia me tin proigoumeni gia otan deinei o xrhsths mia sinallagh
 */
 void transactions_function_command(deiktis_ht *senderHT,   int s_senderHT,
                           	   deiktis_ht *receiverHT, int s_receiverHT,
                            	   info_deikti *my_struct, int s_mystruct,
                           	   typos_tree *tree,       int s_tree,
        	      		   int eggrafes_bucket,
				   int *array_coins, int s_array_coins,

				   int *last_day, int *last_month, int *last_year,
                           	   int *last_time, int *last_minute,

				   char *tranId, char *sender, char *receiver, int value,
				   int day, int month, int year, int time, int minute )
 {
	int i,j;

	if(!strcmp(sender,receiver)){
            printf("Cancellation of a transaction.Exist same sneder and receiver. \n");
            return ;
        }
        if(user_exist(&my_struct[0],s_mystruct,sender) == 0){
            printf("User %s does not exist.Cancellation of a transaction \n", sender);
            return;
        }
        if(user_exist(&my_struct[0],s_mystruct,receiver) == 0){
            printf("User %s does not exist.Cancellation of a transaction \n", receiver);
            return;
        }
	if(sheck_date((int)*last_day,(int)*last_month,(int)*last_year,(int)*last_time,(int)*last_minute,  day,month,year,time,minute) == 0){
            printf("Cancellation of a transaction.Error date or time \n");
            return;
        }
	*last_day = day;
        *last_month = month;
        *last_year = year;
        *last_time = time;
        *last_minute = minute;
	if(walletStatus_function(&my_struct[0],s_mystruct,sender) < value){
            printf("Cancellation of a transaction.The user does not have sufficient balance. \n");
            return;
        }

	 int index1 = hash_function(sender,s_senderHT);
         int index2 = hash_function(receiver,s_receiverHT);


         trans_node * tran = eisagogi_trans(&senderHT[index1],eggrafes_bucket,sender,receiver,tranId, value,day,month,year,time,minute);
         for(j = 0 ; j < s_mystruct ; j++){
             if(take_name(&my_struct[j],sender) == 1){ index1 = j; break; }
         }

	 trans_node * tran2 = eisagogi_trans(&receiverHT[index2],eggrafes_bucket,receiver,sender,tranId, value,day,month,year,time,minute);
         for(j = 0 ; j < s_mystruct ; j++){
             if(take_name(&my_struct[j],receiver) == 1){ index2 = j; break; }
	 }


	 int coin, before_value = value, vall = value;
	 while(value > 0){
             coin = set_sender_user_bitcoin(&my_struct[index1],&value);
             before_value -= value;

             int pos = bitcoin_position_tree(&array_coins[0], s_array_coins, coin);
             g_lock = 1;
             if(pos >= 0){
                 g_val = before_value;
                 Tree_eisagogi_meta(&tree[pos], sender, receiver, tran, tran2, pos);
             }else
                 printf("Bitcoin does not exist. \n");

             if(look_if_bitcoin_exist(&my_struct[index2],coin) == 1) change_balance_bitcoin_receiver(&my_struct[index2],coin,before_value);
             else eisagogi(&my_struct[index2],coin,before_value);

             before_value = value;
         }

         printf("Transaction  %s %s %s %d  %d-%d-%d  %d:%d   -  OK \n\n", tranId,sender,receiver,vall,day,month,year,time,minute);
	 return;
 }



 /*
  Epistrefei to plithos ton sinallagwn enos arxeiou
 */
 int pro_file(char *file){
    int sum = 0;
    char c;
    FILE *fp;

    fp = fopen(file,"r");
    if(fp == NULL) return -1;

    while((c = fgetc(fp)) != EOF){
        if(c == ';') sum++;
    }
    fclose(fp);
    return sum;
 }



 /*
 Promoia me tis parapano
 */
 void transactions_function_command_file(char *file,
                           		 deiktis_ht *senderHT,   int s_senderHT,
                           		 deiktis_ht *receiverHT, int s_receiverHT,
                           		 info_deikti *my_struct,int s_mystruct,
                           		 typos_tree *tree, int s_tree,
                           	 	 int eggrafes_bucket,

					 int *array_coins, int s_array_coins,

                                   	 int *last_day, int *last_month, int *last_year,
                                   	 int *last_time, int *last_minute,
					 int *max)
 {

	FILE *fp;
	int i, j;
	int prot = pro_file(file);
	char tranId[25], sender[60], receiver[60], str[250], c, *token;
	int value, day, month, year, tim, minute;
	if(prot == -1){ printf("File does not exist!? \n"); return; }


	fp = fopen(file,"r");
	for(i = 0 ; i < prot ; i++){

	    if(i == 0){ printf("Press enter to continue first transaction  "); getchar(); }
	    else{ printf("Press enter to continue next transaction  "); getchar(); }

	    fscanf(fp, "%[^;]s", str);
	    fscanf(fp, "%c", &c);
	    fscanf(fp, "%c", &c);

	    sprintf(tranId, "%d", (int)*max);
	    (*max)++;
	    token = strtok(str, " ,.-:;");
	    strcpy(sender,token);	token = strtok(NULL, " ,.-:;");
	    strcpy(receiver,token);	token = strtok(NULL, " ,.-:;");
	    value = atoi(token);	token = strtok(NULL, " ,.-:;");
	    if(token == NULL){
		current_date(&day, &month, &year, &tim, &minute);
	    }else{
	        day = atoi(token);	token = strtok(NULL, " ,.-:;");
	        month = atoi(token);	token = strtok(NULL, " ,.-:;");
	        year = atoi(token);	token = strtok(NULL, " ,.-:;");
	        tim = atoi(token);	token = strtok(NULL, " ,.-:;");
	        minute = atoi(token);

		if(sheck_date((int)*last_day,(int)*last_month,(int)*last_year,(int)*last_time,(int)*last_minute,  day,month,year,tim,minute) == 0){
	            printf("Cancellation of a transaction.Eror date or time. \n");
        	    continue;
        	}
	     }

	    *last_day = day;
            *last_month = month;
            *last_year = year;
            *last_time = tim;
            *last_minute = minute;

	    if(!strcmp(sender,receiver)){
                printf("Cancellation of a transaction.Same sender and receiver \n");
                continue;
            }
       	    if(user_exist(&my_struct[0],s_mystruct,sender) == 0){
                printf("User %s does not exist.Cancellation of a transaction. \n", sender);
            	continue;
            }
            if(user_exist(&my_struct[0],s_mystruct,receiver) == 0){
                printf("User %s does not exist.Cancellation of a transaction. \n", receiver);
                continue;
            }
	    if(walletStatus_function(&my_struct[0],s_mystruct,sender) < value){
                printf("Cancellation of a transaction.The user does not have sufficient balance. \n");
                continue;
            }

	    int index1 = hash_function(sender,s_senderHT);
	    int index2 = hash_function(receiver,s_receiverHT);


            trans_node * tran = eisagogi_trans(&senderHT[index1],eggrafes_bucket,sender,receiver,tranId, value,day,month,year,tim,minute);
            for(j = 0 ; j < s_mystruct ; j++){
                if(take_name(&my_struct[j],sender) == 1){ index1 = j; break; }
            }

            trans_node * tran2 = eisagogi_trans(&receiverHT[index2],eggrafes_bucket,receiver,sender,tranId, value,day,month,year,tim,minute);
       	    for(j = 0 ; j < s_mystruct ; j++){
                if(take_name(&my_struct[j],receiver) == 1){ index2 = j; break; }
            }


	    int coin, before_value = value, vall = value;
            while(value > 0){
                coin = set_sender_user_bitcoin(&my_struct[index1],&value);
                before_value -= value;

                int pos = bitcoin_position_tree(&array_coins[0], s_array_coins, coin);
                g_lock = 1;
                if(pos >= 0){
                    g_val = before_value;
                    Tree_eisagogi_meta(&tree[pos], sender, receiver, tran, tran2, pos);
                }else
                    printf("Bitcoin does not exist. \n");

                if(look_if_bitcoin_exist(&my_struct[index2],coin) == 1) change_balance_bitcoin_receiver(&my_struct[index2],coin,before_value);
                else eisagogi(&my_struct[index2],coin,before_value);

                before_value = value;
            }

            printf("Transaction  %s %s %s %d  %d-%d-%d  %d:%d   -  OK \n\n", tranId,sender,receiver,vall,(int)day,(int)month,(int)year,(int)tim,(int)minute);
	}

	fclose(fp);
	return;
 }



 /*
 Gia tin entoli bitCoinStatus
 Emfanizei gia kapoio bitcoin tis sinalages pou simetexei kai to unspent an exei
 */
 void bitCoinStatus_function(typos_tree *tree,int s_tree,int bitcoin,int *array,int s_array){

	int pos = bitcoin_position_tree(&array[0],s_array,bitcoin);
	int sum = 0;
	not_null_pointers_nodes(&tree[pos],&sum);
	printf("bitcoin : %d, transactions : %d, ", bitcoin, sum - g_array[pos]);


	int value = 0, exist = 0;
	char user[30];
	strcpy(user,take_name_tree(&tree[pos]));

	check_tree(&tree[pos],user,&exist);
	if(exist == 0) unspent(&tree[pos],&value,user);

	printf("unspent : %d \n", value);

	return;
 }



 /*
 Gia tin entoli traceCoin
 Emfanizei ta stoixeia ton sinalagwn pou empleketai kapoio bitcoin
 */
 void traceCoin_function(typos_tree *tree,int s_tree,int bitcoin,int *array,int s_array){

	int pos = bitcoin_position_tree(&array[0],s_array,bitcoin);
	trans_tree(&tree[pos]);
	return;
 }



 /*
  Diagrafei oles tis domes dedomenwn tis askhseis diladi:
  ta 2 hash_table,to dedro kai tin domi mou pou exei tou xristes kai ta bitcoin pou exoun
 */
 void exit_function(deiktis_ht *senderHT,   int s_senderHT,
                   deiktis_ht *receiverHT, int s_receiverHT,
                   info_deikti *my_struct, int s_mystruct,
                   typos_tree *tree,       int s_tree,
		   int eggrafes_bucket )
 {
    int i;
    for(i = 0 ; i < s_mystruct ; i++) lista_diagrafi(&my_struct[i]);

    for(i = 0 ; i < s_senderHT ; i++) HashTable_diagrafi(&senderHT[i],eggrafes_bucket);

    for(i = 0 ; i < s_receiverHT ; i++) HashTable_diagrafi(&receiverHT[i],eggrafes_bucket);

    for(i = 0 ; i < s_tree ; i++) Tree_katastrofi(&tree[i]);

 }



 /*
 Epistrefei 1 an exei kapoios xrhsths to bitcoin
 diaforetika 0
 */
 int bitcoin_exist(int *array,int size,int bitcoin){

    int i;
    for(i = 0 ; i < size ; i++){
	if(array[i] == bitcoin) return 1;
    }
    return 0;
 }



 /*
  Epistrefei to plithos ton erwthmaton apo to string token
 */
 int pro(char *token){
	int i, sum = 0;
	for(i = 0 ; i < strlen(token) ; i++){
		if(token[i] == ';') sum++;
	}
	return sum;
 }

