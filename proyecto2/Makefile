all: compilar reporte pantalla clean

compilar:
	gcc -c recorrer.c recorrer.h
	gcc recorrer.o els.c -o els

reporte:
	./els reporte.txt /home/jesus/Documents/UCAB

pantalla:
	./els /home/jesus/Documents/UCAB

clean:
	rm els *.txt recorrer.o recorrer.h.gch