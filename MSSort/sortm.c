/* TP algorithmique parallele
 * Master 1 FS
 * LL
 * 03/03/10
 */

/* 
 * sortm.c
 * algorithme maitre
 * -- tri recursif & fusion
 */

#include <stdio.h>
#include <malloc.h>
#include <strings.h>
#include <stdlib.h>
#include "pvm3.h"
#include "sort.h"

static pb_t *Q[PB];		/* la pile de problemes */
static int Q_nb;			/* l'index de tete de pile */

/*
 * remplit un tableau d'entiers aleatoirement
 * dans l'intervalle [0..99]
 * la taille du tableau est donnee
 * par DATA (cf sort.h)
 */
void set_random_data(int *data)
{
	int i;

	for (i=0; i<DATA; i++) 
		data[i] = rand()%100;
}

/*
 * initialise la file de problemes
 * chacun des PB problemes est un
 * probleme de tri de taille N
 * stocke dans le premier champ de
 * donnees de la structure.
 */

void init_queue(int *data)
{
	int i;

	for (i=0; i<PB; i++) {
		Q[i] 		= pb_alloc();
		Q[i]->type 	= PB_TRI;
		Q[i]->taille1 	= N;
		Q[i]->data1 	= (int *)malloc(N*sizeof(int));
		bcopy((char *)(data + i*N), (char *)(Q[i]->data1), N*sizeof(int));
	}
	Q_nb = PB;	
}

/*
 * empile ou depile dans la 
 * pile globale Q un probleme
 */

pb_t *depile()
{
	return Q_nb>0 ? Q[--Q_nb] : NULL;
}

void empile(pb_t *pb)
{
	if (Q_nb >= PB) {
		fprintf(stderr, "error -- stack overflow\n");
		pvm_exit();
		exit(-1);
	}
	Q[Q_nb++] = pb;
}

/*
 * programme maitre
 */

main(int argc, char **argv)
{
	int i;
	int tids[P];	/* tids fils */
	int data[DATA];	/* donnees */
	pb_t *pb;	/* probleme courant */
	int sender;

	set_random_data(data);	/* initialisation aleatoire */
	init_queue(data);	/* initialisation de la pile */
	/* lancement des P esclaves */
	pvm_catchout(stdout);
	pvm_spawn(EPATH "/sorts", (char**)0, 0, "", P, tids);

	/* envoi d'un probleme (de tri) a chaque esclave */
	for (i=0; Q_nb>0 && i<P; i++)
		send_pb(tids[i], depile());
	while (1) {
		// tp3
		pb = receive_pb(-1, &sender);
		//Tableau recu des esclaves est de taille DATA -> tableau complet retourne, donc fin du pb
		if(pb->taille1 == DATA) break;
		
		empile(pb);
		pb = depile();
		//Pb de type Tri, juste a envoyer a sender, l'esclave qui a precedemment envoye le result, donc inactif
		if(pb->type == PB_TRI) send_pb(sender, pb);
		//Pb de type fusion, depiller un 2eme pb
		if(pb->type == PB_FUS){
			pb_t *pb2 = depile();
			//Seulement un demi pb de fusion, pas de travail trouvable pour l'esclave inactif
			if(pb2 == NULL)
				empile(pb);
			//Si pb de tri,envoi du pb non resolu (de tri) et reempiler le 1/2 pb de fusion restant
			if(pb2->type == PB_TRI){
				send_pb(sender, pb2);
				empile(pb);
			}
			//On fusione les donnees des deux esclaves
			if(pb2->type == PB_FUS){
				pb->taille2 = pb2->taille1;
				pb->data2 = pb2->data1;
				send_pb(sender, pb);
				//Free pour eviter les pb memoire
				free(pb2);
			}
		}
	}

	pvm_initsend(PvmDataDefault);
	pvm_mcast(tids, P, MSG_END); /* fin esclaves */
	pb_print(pb);
	pb_free(pb);
	pvm_exit();
	exit(0);
}
