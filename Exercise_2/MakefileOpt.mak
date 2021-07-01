OBJS = main.o explorer.o premier.o my_system.o
HEADERS = my_system.h explorer.h premier.h
CC = gcc

#Exécutables

Prog_premiers : $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: explorer.h

explorer.o : $(HEADERS)

premier.o : premier.h

my_system.o : my_system.h

.c.o :
	gcc -c $<

clean :
	rm -f Prog_premiers $(OBJS)

# Commande qui permet de tester le bon fonctionnement
# make -f MakefileOpt puis ./Prog_premiers

