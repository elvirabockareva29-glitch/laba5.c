//команда сборки - make, собирает программу
CC = gcc
CFLAGS = -Wall

all: app

app: main.o hospital.o
 $(CC) main.o hospital.o -o app

main.o: main.c hospital.h
 $(CC) $(CFLAGS) -c main.c

hospital.o: hospital.c hospital.h
 $(CC) $(CFLAGS) -c hospital.c

clean:
 rm -f *.o app
