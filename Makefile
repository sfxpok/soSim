all: simulador monitor

monitor: monitor.o
	gcc -g -o monitor monitor.o -lpthread

simulador: simulador.o
	gcc -g -o simulador simulador.o -lpthread

clean:
	rm -f *.o *~ simulador monitor
