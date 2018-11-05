all: simulador monitor

monitor: monitor.o
	gcc -o monitor monitor.o -lpthread

simulador: simulador.o
	gcc -o simulador simulador.o -lpthread

clean:
	rm -f *.o *~ simulador monitor