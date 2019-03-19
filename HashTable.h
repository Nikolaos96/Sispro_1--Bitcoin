#ifndef __HASHTABLE__
#define __HASHTABLE__

typedef struct hash_table    * deiktis_ht;
typedef struct bucket * deiktis_b;
typedef struct trans_list trans_node;


typedef struct trans_list{
	char trans_id[25];
	char *sender_receiver_user;
	int  value;

	int day;
	int month;
	int year;
	int time;
	int minute;

	trans_node * next_tran;
} trans_list;



typedef struct dedomena_deikti{
        char *userId;

	trans_node * trans;
} dedomena_deikti;



deiktis_ht HashTable_dimiourgia(deiktis_ht*);
void dimoiourgeia_arxikwn_bucket(deiktis_ht* linfo,int plithos_eggrafon);

void eisagogi_user(deiktis_ht* linfo,char *user,int plithos_eggrafon);
void emfanisi_ht(deiktis_ht* linfo, int plithis_eggrafon);

void HashTable_diagrafi(deiktis_ht* linfo,int plithis_eggrafon);
trans_node * eisagogi_trans(deiktis_ht* linfo,int plithis_eggrafon,char *user,char *user_trans,char *trans_id,int value,int day,int month,int year,int time,int minute);

int date1(int last_day,int last_month,int last_year,int last_time,int last_minute,  int day,int month,int year,int tim,int minute);
int ttime(int t1,int m1,int t2,int m2);
void find_Earnings_Payments(deiktis_ht* linfo,int plithos_eggrafon,char *user, int time1,int minute1,int day1,int month1,int year1,int time2,int minute2,int day2,int month2,int year2,int kk);
#endif
