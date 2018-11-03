all: simulador

simulador: simulador.o
	gcc -o simulador simulador.o -lpthread

clean:
	rm -f *.o *~ simulador