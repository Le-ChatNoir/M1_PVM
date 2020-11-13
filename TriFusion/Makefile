# generation de programme PVM
#  TP algorithmique parallele
#  Master
#  LL
#  03/03/16
# 

PROG = msort
SRC = msort util

#PVM_ROOT = /usr/share/pvm3
#PVM_ARCH = LINUXI386
#PVM_ROOT = /home/commun_depinfo/enseignants/lemarchand/TPPVMM1/PvmLinux/pvm3
#PVM_ARCH = LINUX64


# executable directory
BDIR =$(PWD)

# your compiler
CC = gcc 

EXEC = $(BDIR)/$(PROG)
PSRC = $(SRC:%=%.c)
POBJ = $(SRC:%=%.o)

#### do not edit #####

#PVM_LIB = $(PVM_ROOT)/lib/$(PVM_ARCH)/libpvm3.a
#CFLAGS =  -I$(PVM_ROOT)/include -D_POSIX_C_SOURCE=2 -DEPATH=\"$(BDIR)\"
#include $(PVM_ROOT)/conf/$(PVM_ARCH).def

PVM_LIB = -lpvm3
CFLAGS =  -DEPATH=\"$(BDIR)\"

#### generation rules #####

$(PROG) : $(EXEC)
	
$(EXEC): $(POBJ)
	$(CC) -o $(EXEC) $(POBJ) $(PVM_LIB) $(ARCHLIB)

.c.o:
	$(CC) $(CFLAGS) $(ARCHCFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXEC)
