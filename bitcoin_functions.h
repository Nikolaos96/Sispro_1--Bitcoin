#ifndef __BITCOIN_FUNCTION__
#define __BITCOIN_FUNCTION__

#include "my_struct.h"
#include "tree.h"
#include "HashTable.h"

void check_arguments(int argc,char *argv[],char **bitCoinBalancesFile, char **transactionsFile,int *nitCoinValue,
                     int *senderHashtableNumOfEntries, int *receiverHashtableNumOfEntries, int *bucketSize);


void current_date(int *day,int *month,int *year,int *tim,int *minute);
void count_users_bitcoins(char *file,int *a,int *b);
void check_for_defference_users(char *file,int users);


int check_for_defference_transaction(char *file);
int hash_function(char* x, int size);


int sheck_date(int last_day,int last_month,int last_year,int last_time,int last_minute,  int day,int month,int year,int tim,int minute);
int walletStatus_function(info_deikti *my_list,int size,char *user);


int bitcoin_position_tree(int *array,int size,int bitcoin);


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
			   int *array_coins, int s_array_coins);



void transactions_function_command(deiktis_ht *senderHT,   int s_senderHT,
                                   deiktis_ht *receiverHT, int s_receiverHT,
                                   info_deikti *my_struct, int s_mystruct,
                                   typos_tree *tree,       int s_tree,
                                   int eggrafes_bucket,
                                   int *array_coins, int s_array_coins,

                                   int *last_day, int *last_month, int *last_year,
                                   int *last_time, int *last_minute,

                                   char *tranId, char *sender, char *receiver, int value,
                                   int day, int month, int year, int time, int minute );


int pro_file(char *file);


void transactions_function_command_file(char *file,
                                         deiktis_ht *senderHT,   int s_senderHT,
                                         deiktis_ht *receiverHT, int s_receiverHT,
                                         info_deikti *my_struct,int s_mystruct,
                                         typos_tree *tree, int s_tree,
                                         int eggrafes_bucket,

                                         int *array_coins, int s_array_coins,

                                         int *last_day, int *last_month, int *last_year,
                                         int *last_time, int *last_minute,
                                         int *max);



void bitCoinStatus_function(typos_tree *tree,int s_tree,int bitcoin,int *array,int s_array);
void traceCoin_function(typos_tree *tree,int s_tree,int bitcoin,int *array,int s_array);


void exit_function(deiktis_ht *senderHT,   int s_senderHT,
                   deiktis_ht *receiverHT, int s_receiverHT,
                   info_deikti *my_struct, int s_mystruct,
                   typos_tree *tree,       int s_tree,
                   int eggrafes_bucket );


int bitcoin_exist(int *array,int size,int bitcoin);
int pro(char *token);

#endif
