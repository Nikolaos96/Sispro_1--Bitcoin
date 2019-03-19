#ifndef __MYSTRUCT__
#define __MYSTRUCT__

typedef struct info_node * info_deikti;
typedef struct typos_komvou * typos_deikti;


info_deikti LIST_dimiourgia(info_deikti*,char name[]);
void eisagogi(info_deikti* linfo,int bitcoin_id,int value);

void emfanisi(info_deikti* linfo);
void lista_diagrafi(info_deikti* linfo);

void diagrafi_komvou(info_deikti* linfo, int komvos);
int take_balance(info_deikti* linfo);
int take_name(info_deikti* linfo,char * user);

int look_if_bitcoin_exist(info_deikti* linfo, int coin_id);
int set_sender_user_bitcoin(info_deikti* linfo,int *value);

void change_balance_bitcoin_receiver(info_deikti* linfo, int coin_id,int value);
int user_exist(info_deikti* linfo,int size,char *user);

#endif
