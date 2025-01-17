CC = gcc
CFLAGS = -Wall
TARGET = Solares
OBJ = InterfaceGraphique.o ModelePhysique.o Parsing.o

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lm -lraylib 

static : $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) /usr/lib/libraylib.a -lm -pthread -ldl -lGL -lX11

InterfaceGraphique.o : InterfaceGraphique.c
	$(CC) $(CFLAGS) -c InterfaceGraphique.c

ModelePhysique.o : ModelePhysique.c
	$(CC) $(CFLAGS) -c ModelePhysique.c

Parsing.o : Parsing.c
	$(CC) $(CFLAGS) -c Parsing.c

clean:
	rm -f $(TARGET)
	rm -f $(OBJ)

l: $(TARGET)
	make clean
	make
	./Solares