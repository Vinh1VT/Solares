#variables
CC = gcc
CFLAGS = -Wall
Target = Simulation
OBJ = InterfaceGraphique.o ModelePhysique.o

$(Target) : $(OBJ)
	$(CC) $(OBJ) -o $(Target) -lm -lraylib

InterfaceGraphique.o : InterfaceGraphique.c
	$(CC) $(CFLAGS) -c InterfaceGraphique.c

ModelePhysique.o : ModelePhysique.c
	$(CC) $(CFLAGS) -c ModelePhysique.c


clean:
	rm -f $(OBJ) $(Target)
