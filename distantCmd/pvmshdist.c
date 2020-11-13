// distant command
#include <stdio.h>
#include <stdlib.h>
#include "pvm3.h"
#define MSG_CMD 1
#define MSG_END 2

int main(){
	char cmd[1024];
	int pere = pvm_parent();
	//Reception commande
	pvm_recv(pere, MSG_CMD);
	pvm_upkstr(cmd);
	system(cmd);
	
	//Envoie de la commande ack
	pvm_initsend(PvmDataDefault);
	pvm_pkstr("");
	pvm_send(pere, MSG_END);
	
	pvm_exit();
	exit(0);
}
