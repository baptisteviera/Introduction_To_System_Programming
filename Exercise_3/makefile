CC=gcc
CFLAGS=-W -Wall -pedantic
LDFLAGS=

#Répertoires
SRCDIR = src
OBJDIR = obj
BINDIR = bin

EXEC = $(wildcard $(BINDIR)/*)
SRC = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: application_manager get_time network_manager power_manager

#Exécutables

power_manager: power_manager.o
	$(CC) $(CFLAGS) $(OBJDIR)/$< -o $(BINDIR)/$@

network_manager: network_manager.o
	$(CC) $(CFLAGS) $(OBJDIR)/$< -o $(BINDIR)/$@

application_manager: application_manager.o
	$(CC) $(CFLAGS) $(OBJDIR)/$< -o $(BINDIR)/$@

get_time: get_time.o
	$(CC) $(CFLAGS) $(OBJDIR)/$< -o $(BINDIR)/$@

#Objets

%.o: src/%.c
	$(CC) -c $< -o obj/$@ $(CFLAGS)

#Nettoyage

clean: 
	rm -f $(OBJS) 

mrproper: clean
	rm -f $(EXEC)

