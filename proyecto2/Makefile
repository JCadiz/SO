main: els.c recorrer.o
	gcc -g -Wall -o els els.c recorrer.o

recorrer.o: recorrer.c recorrer.h
	gcc -c recorrer.c recorrer.h

reporte:
	./els reporte.txt /home/jesus/Documents/UCAB

pantalla:
	./els /home/jesus/Documents/UCAB

clean:
	rm els *.txt recorrer.o recorrer.h.gch