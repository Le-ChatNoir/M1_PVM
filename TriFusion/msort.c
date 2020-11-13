/* TP algorithmique parallele
 * maitrise
 * LL
 * 23/03/18
 */

/* 
 * msort.c
 * algorithme principal
 * -- tri recursif & fusion
 */

#include "pvm3.h"
#include "msort.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>


void sort_rec(int *data, int n)
{
	// a vous !
	if (n<2) return;
	int n2 = n/2;
	int data1[n2], data2[n2], i;
	for(i=0; i<n2; i++){
		data1[i] = data[i];
		data2[i] = data[n2+i];
	}
	sort_rec(data1, n2);
	sort_rec(data2, n2);
	merge_data(data1, data2, data, n2);
}

main(int argc, char **argv)
{
	int mytid;		/* tid tache */
	int parent = pvm_parent();		/* tid du pere */
	int nb_data, n2;	/* taille donnees, taille / 2 */
	int tids[2];		/* tids fils */
	int data[DATA];		/* donnees */
	int data1[DATA];	/* donnees triees (1ere moitie) */
	int data2[DATA];	/* donnees triees (2eme moitie) */
	int i;
	int cc;

	//====INIT====
	
	if(parent == PvmNoParent){
		
		nb_data = DATA;
		set_random_data(data);
		show_sort(data);
			
	} else {
		//Attente de récéption d'un message de parent
		pvm_recv(parent, MSG_DATA);
		pvm_upkint(&nb_data, 1, 1);
		pvm_upkint(data, nb_data, 1);
	}
	
	//====CALCUL====
	if(nb_data>1){
		//Creation des deux fils
		cc = pvm_spawn(EPATH "/msort", (char**)0, 0, "", 2, tids);
		if(cc != 2)
			printf("Erreur lors de la création des fils\n");
			
		//Sepaation de data
		n2 = nb_data/2;
		
		
		//Envoi des données aux fils
		pvm_initsend(PvmDataDefault);
		pvm_pkint(&n2, 1, 1);
		pvm_pkint(data, n2, 1);
		pvm_send(tids[0], MSG_DATA);
		
		pvm_initsend(PvmDataDefault);
		pvm_pkint(&n2, 1, 1);
		pvm_pkint(data+n2, n2, 1);
		pvm_send(tids[1], MSG_DATA);
		
		//Reception des tablaux tries, utilisation de -1 pour dire qu'on recoit de n'importe qui
		pvm_recv(-1, MSG_SORT);
		pvm_upkint(data1, n2, 1);
		pvm_recv(-1, MSG_SORT);
		pvm_upkint(data2, n2, 1);
		
		merge_data(data1, data2, data, n2);
	}
	
	//====RETURN====
	if(parent == PvmNoParent){
		show_sort(data);
	} else {
		pvm_initsend(PvmDataDefault);
		pvm_pkint(data, nb_data, 1);
		pvm_send(parent, MSG_SORT);
	}




	pvm_exit();
	exit(0);
}
