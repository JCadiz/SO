all: compilar cifrar descifrar

compilar:
	gcc -o pipes Pipes.c

cifrar:
	./pipes c archivo.txt

descifrar:
	./pipes d cifrado.txt

clean: 
	rm pipes cifrado.txt descifrado.txt