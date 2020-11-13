
# generation de programme PVM
#  TP algorithmique parallele
#  master 1
#  LL
#  18/01/2017
# 

# executable directory
BDIR =$(PWD)

# your compiler
CC = gcc 

#PVM_ROOT = /usr/share/pvm3
#PVM_ARCH = LINUXI386

#PVM_ROOT = /home/commun_depinfo/enseignants/lemarchand/TPPVMM1/PvmLinux/pvm3
#PVM_ARCH = LINUX64


#### do not edit #####

#PVM_LIB = $(PVM_ROOT)/lib/$(PVM_ARCH)/libpvm3.a

PVM_LIB = -lpvm3

#CFLAGS =  -I$(PVM_ROOT)/include -DEPATH=\"$(BDIR)\"
CFLAGS =  -DEPATH=\"$(BDIR)\"
#include $(PVM_ROOT)/conf/$(PVM_ARCH).def

all: hello hello_other

clean:
	rm -f *.o $(BDIR)/hello $(BDIR)/hello_other

.c:
	$(CC) $(CFLAGS) -o $(BDIR)/$@ $< $(PVM_LIB) $(ARCHLIB)
