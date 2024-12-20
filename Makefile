#variables
CC = gcc
CFLAGS = -Wall
TARGET = Simulation
OBJ = InterfaceGraphique.o ModelePhysique.o

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lm -lraylib
	rm -f $(OBJ)

InterfaceGraphique.o : InterfaceGraphique.c
	$(CC) $(CFLAGS) -c InterfaceGraphique.c

ModelePhysique.o : ModelePhysique.c
	$(CC) $(CFLAGS) -c ModelePhysique.c


clean:
	rm -f $(TARGET)
	rm -f $(OBJ)

l: $(TARGET)
	make clean
	make
	./Simulation