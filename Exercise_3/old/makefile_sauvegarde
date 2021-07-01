CC=gcc
CFLAGS=-W -Wall -pedantic
LDFLAGS=
EXEC = application_manager 
SRC = src/application_manager.c src/get_time.c
OBJS = obj/application_manager.o obj/get_time.o

all: application_manager get_time

#Exécutables

application_manager: application_manager.o
	$(CC) $(CFLAGS) obj/application_manager.o -o bin/application_manager

get_time: get_time.o
	$(CC) $(CFLAGS) obj/get_time.o -o bin/get_time

#Objets

application_manager.o: src/application_manager.c
	$(CC) $(CFLAGS) -c $< -o obj/application_manager.o

get_time.o: src/get_time.c
	$(CC) $(CFLAGS) -c $< -o obj/get_time.o


#Nettoyage

clean: 
	rm -f $(OBJS) 

mrproper: clean
	rm -f bin/$(EXEC)

