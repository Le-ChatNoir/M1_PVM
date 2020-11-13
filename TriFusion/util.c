/* TP algorithmique parallele
 * master 1 FS
 * LL
 * 10/03/2010
 */

/* 
 * util.c
 * affichage/fusion/remplissage aleatoire
 * -- tri recursif & fusion
 */

#include <stdio.h>
#include "pvm3.h"
#include "msort.h"

/*
 * affiche des entiers sur 8 colonnes
 * la taille du tableau est donnee
 * par DATA (cf msort.h)
 */

void show_sort(int *data)
{
	int i;

	for (i=0; i<DATA; i++) {
		if (i % 8 == 0)
			printf("\n");
		printf("%3d	", data[i]);
	}
	printf("\n");
}

/*
 * remplit un tableau d'entiers aleatoirement
 * dans l'intervalle [0..99]
 * la taille du tableau est donnee
 * par DATA (cf msort.h)
 */
void set_random_data(int *data)
{
	int i;

	for (i=0; i<DATA; i++) 
		data[i] = rand()%100;
}

/*
 * fusionne 2 tableaux tries de 
 * tailles egales (nb_data)
 * le resultat est dans data
 */

void merge_data(int *data1, int *data2, int *data, int nb_data)
{
	int idx1, idx2, idx;

	idx1 = idx2 = idx = 0;

	while (idx1<nb_data && idx2<nb_data) 
		if (data1[idx1] < data2[idx2])
			data[idx++] = data1[idx1++];
		else
			data[idx++] = data2[idx2++];

	while (idx1<nb_data)
		data[idx++] = data1[idx1++];
	while (idx2<nb_data)
		data[idx++] = data2[idx2++];

}

