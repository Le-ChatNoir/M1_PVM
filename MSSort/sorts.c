/* TP algorithmique parallele
 * Master 1 FS
 * LL
 * 03/03/10
 */

/* 
 * sorts.c
 * algorithme esclave
 * -- tri fusion maitre esclave
 */

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "pvm3.h"
#include "sort.h"

/*
 * trie un tableau de taille N
 * compare_int pour qsort
 */

static int compare_int(a, b) int *a, *b; { return *a - *b; }
void sort_data(pb_t *pb)
{
	qsort(pb->data1, N, sizeof(int), compare_int);
	pb->type = PB_FUS;
}

/*
 * fusion (cf tp1)
 */

void merge_data(pb_t *pb)
{
	int idx1, idx2, idx;
	int *data;

	data = (int *)malloc((pb->taille1+pb->taille2)*sizeof(int));
	idx1 = idx2 = idx = 0;

	while (idx1<pb->taille1 && idx2<pb->taille2) 
		if (pb->data1[idx1] < pb->data2[idx2])
			data[idx++] = pb->data1[idx1++];
		else
			data[idx++] = pb->data2[idx2++];

	while (idx1<pb->taille1)
		data[idx++] = pb->data1[idx1++];
	while (idx2<pb->taille2)
		data[idx++] = pb->data2[idx2++];

	free(pb->data1);
	pb->data1 = data;
	free(pb->data2);
	pb->data2 = NULL;
	pb->taille1 += pb->taille2;
	pb->taille2 = 0;
}

/*
 * programme esclave
 */

main()
{
	int parent = pvm_parent();
	int sender, cc, typeMSG;

	/* tp3 */

	while (1) {
		// a vous
		//Reception des messages du maitre
		pb_t *pb = receive_pb(parent, &sender);
		if(pb == NULL) break;
		
		//Tri des donnees
		if(pb->type == PB_TRI)
			sort_data(pb);
		
		//Fusion des donnees
		if(pb->type == PB_FUS)
			merge_data(pb);
		
		send_pb(parent, pb);
	}

	pvm_exit();
	exit(0);

}

