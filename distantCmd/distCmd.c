// distant command
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pvm3.h"
#define MSG_CMD 1
#define MSG_END 2

// EPATH est le repertoire courant defini a la compilation
// pour lancer l'execution d'un processus algotest :
//    cc = pvm_spawn(EPATH "/algotest", (char**)0, 0, "", 1, &tidFils);

int main(int argc, char * argv[])
{
	if(argc <= 3){
		printf("Utilisation: ./distCmd [machine distante] [cmd]\n");
		pvm_exit();
		exit(0);
	}
	
	int distant, cc;
	char * machine = argv[1];
	char cmd[1024] = "";
	
	//Prise de la commande entiere
	int i;
	for(i=2; i < argc; i++){
		strcat(cmd, " ");
		strcat(cmd, argv[i]);
	}
	
	//Lancement de fils
	pvm_catchout(stdout);
	cc = pvm_spawn(EPATH "/pvmshdist", (char**)0, PvmTaskHost, machine, 1, &distant);
	if(cc!=1){
		printf("Erreur lors de la création du processus fils.\n");
		pvm_exit();
		exit(0);
	}

	//Envoie de la commande
	pvm_initsend(PvmDataDefault);
	pvm_pkstr(cmd);
	pvm_send(distant, MSG_CMD);
	
	//Attente d'un ack de fin
	pvm_recv(distant, MSG_END);
	pvm_upkstr(cmd);
	
	pvm_exit();
	exit(0);
}

