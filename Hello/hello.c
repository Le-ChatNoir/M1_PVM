#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "pvm3.h"

int main()
{
	int cc, tid;
	char buf[100];

	printf("i'm t%x\n", pvm_mytid());
	pvm_catchout(stdout); 
	// EPATH est le repertoire courant defini a la compilation
	cc = pvm_spawn(EPATH "/hello_other", (char**)0, 0, "", 1, &tid);

	if (cc == 1) {
		cc = pvm_recv(-1, -1);
		pvm_bufinfo(cc, (int*)0, (int*)0, &tid);
		pvm_upkstr(buf);
		printf("from t%x: %s\n", tid, buf);

	} else
		printf("can't start hello_other\n");

	pvm_exit();
	exit(0);
}

