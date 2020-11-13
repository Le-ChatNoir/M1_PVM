/* TP algorithmique parallele
 * maitrise
 * LL
 * 07/10/97
 */

/* 
 * msort.h
 * definitions -- tri recursif & fusion
 */

#define DATA		32 /* doit etre une puissance de 2 */
#define MSG_DATA	0
#define MSG_SORT	1

extern void show_sort();
extern void set_random_data();
extern void merge_data();
