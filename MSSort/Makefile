# generation de programme PVM
#  TP algorithmique parallele
#  maitrise
#  LL
#  07/10/97
# 

CC = gcc -g

# executable directory
BDIR = $(PWD)

# Programmes maitre et esclave
PROG = sortm sorts

#PVM_ROOT = /usr/share/pvm3
#PVM_ARCH = LINUXI386
#PVM_ROOT = /home/commun_depinfo/enseignants/lemarchand/TPPVMM1/PvmLinux/pvm3
#PVM_ARCH = LINUX64


#### do not edit #####

EXEC = $(PROG:%=$(BDIR)/%)

#PVM_LIB = $(PVM_ROOT)/lib/$(PVM_ARCH)/libpvm3.a
#CFLAGS =  -I$(PVM_ROOT)/include -D_POSIX_C_SOURCE=2 -DEPATH=\"$(BDIR)\"
# include $(PVM_ROOT)/conf/$(PVM_ARCH).def

PVM_LIB = -lpvm3
CFLAGS =  -DEPATH=\"$(BDIR)\"

#### generation rules #####

all: $(EXEC)
	
$(BDIR)/sortm: pb.o sortm.o 
	$(CC) -o $@ sortm.o pb.o $(PVM_LIB) $(ARCHLIB)

$(BDIR)/sorts: pb.o sorts.o 
	$(CC) -o $@ sorts.o pb.o $(PVM_LIB) $(ARCHLIB)

.c.o: sort.h
	$(CC) $(CFLAGS) $(ARCHCFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXEC)
