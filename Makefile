all:
	gcc main.c hospital.c -o app

clean:
	rm -f app
