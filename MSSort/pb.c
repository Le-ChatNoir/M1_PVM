/* TP algorithmique parallele
 * LL
 * 03/03/18
 */

/* 
 * pb.c
 * - copie de tableau d'entiers
 * - (de)allocation de pb
 * - affichage
 * - envoi/reception de pb
 */

#include <stdio.h>
#include <malloc.h>
#include "pvm3.h"
#include "sort.h"

/*
 * (de)allocation d'un probleme
 */
pb_t *pb_alloc()
{
	pb_t *pb;

	pb = (pb_t *)malloc(sizeof(pb_t));
	pb->taille1 = pb->taille2 = pb->type = 0;
	pb->data1 = pb->data2 = NULL;

	return pb;
}

void pb_free(pb_t *pb)
{
	if (pb->data1) free(pb->data1);
	if (pb->data2) free(pb->data2);
	free(pb);
}

/*
 * affichage d'un probleme
 */
void pb_print(pb_t *pb)
{
	int i;

	printf("type: %s\n", pb->type==PB_TRI ? "Tri" : "Fusion");
	printf("tai1: %2d\n", pb->taille1);
	for (i=0; i<pb->taille1; i++) {
		if (i % 8 == 0) printf("\n");
		printf("%3d	", pb->data1[i]);
	}
	printf("\n");
	printf("tai2: %2d\n", pb->taille2);
	for (i=0; i<pb->taille2; i++) {
		if (i % 8 == 0) printf("\n");
		printf("%3d	", pb->data2[i]);
	}
	printf("\n");
}

/* 
 * envoi d'un probleme a un processus tid
 * le probleme est dealloue localement
 */
void send_pb(int tid, pb_t *pb)
{
	pvm_initsend(PvmDataDefault);
	pvm_pkint(&(pb->taille1), 1, 1);
	pvm_pkint(&(pb->taille2), 1, 1);
	pvm_pkint(&(pb->type), 1, 1);
	pvm_pkint(pb->data1, pb->taille1, 1);
	if (pb->taille2 > 0)
		pvm_pkint(pb->data2, pb->taille2, 1);
	pvm_send(tid, MSG_PB);

	pb_free(pb);
}

/*
 * reception d'un probleme venant d'un processus tid
 * allocation locale pour le probleme
 * met a jour le le tid de l'envoyeur dans sender 
 * (utile dans le cas ou la reception venait 
 * d'un processus indifferent (tid == -1))
 * retourne NULL si le message n'est pas de type MSG_PB
 */

pb_t *receive_pb(int tid, int *sender)
{
	/* tp3 */
	int bufid, bytes, msgtag;
	bufid = pvm_recv(tid, -1);
	pvm_bufinfo(bufid, &bytes, &msgtag, sender);
	
	if(msgtag != MSG_PB)
		return NULL;
		
	//Allocation de la mémoire pour le probleme en cours
	pb_t *pb = pb_alloc();
	
	//Depaquetage
	pvm_upkint(&(pb->taille1), 1, 1);
	pvm_upkint(&(pb->taille2), 1, 1);
	pvm_upkint(&(pb->type), 1, 1);
	pvm_upkint(pb->data1, pb->taille1, 1);
	if (pb->taille2 > 0)
		pvm_upkint(pb->data2, pb->taille2, 1);
	
	//Return du pb pour le maitre
	return pb;

}








