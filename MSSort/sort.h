/* TP algorithmique parallele
 * maitrise
 * LL
 * 07/10/97
 */

/* 
 * sort.h
 * definitions -- tri recursif & fusion
 */

#define N		7		/* taille maximale d'un probleme de tri */
#define PB		11		/* nombre initial de pbs de tri (= DATA / N) */
#define DATA		77		/* taille des donnees initiales */

#define P		5		/* nombre d'esclaves */
// #define SLAVE	"sorts"		/* nom du programme esclave */

#define MSG_PB		0
#define MSG_END		1

#define PB_TRI 		0
#define PB_FUS 		1

/*
 * un probleme est soit 
 *   - un probleme de tri direct :
 *     TYPE == PB_TRI
 *     donnees dans data1, taille dans taille1
 *   - un probleme de fusion
 *     TYPE == PB_FUS
 *     donnees a fusionner et tailles dans
 *     dans data1/2 et taille1/2
 */

struct st_pb {			/* probleme de tri */
	int taille1, taille2;
	int type;
	int *data1;
	int *data2;
};

typedef struct st_pb pb_t;

/*
 * utilitaires dans pb.c
 */
extern void copy_int();
extern void print_pb();
extern pb_t *pb_alloc();
extern void pb_free();
extern void send_pb();
extern pb_t *receive_pb();


