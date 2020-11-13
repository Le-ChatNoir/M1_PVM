#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "pvm3.h"

int main()
{
	int ptid;
	char buf[100];

	ptid = pvm_parent();

	strcpy(buf, "hello, world from ");
	gethostname(buf + strlen(buf), 64);
	//while (1);
	printf("dans le fils\n");
	pvm_initsend(PvmDataDefault);
	pvm_pkstr(buf);
	pvm_send(ptid, 1); 

	pvm_exit();
	exit(0);
}


