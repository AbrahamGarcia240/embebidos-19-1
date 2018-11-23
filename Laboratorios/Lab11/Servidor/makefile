#Archivo Makefile simple 

PROYECTO = imagen
DESTDIR = /usr/local/bin
CFLAGS = -Wall 
LDFLAGS = -lm -lpthread
CC = gcc
objects = *.o

all: $(PROYECTO)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO): server.o procesamiento.o imagen.o funcionesprocesamiento.o funhilo.o procesamiento.o
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: clean

install: all
	if [ ! -d $(DESTDIR) ]; then \
		sudo mkdir $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)

uninstall: 
	sudo rm $(DESTDIR)/$(PROYECTO)

clean:
	rm -f *.o $(PROYECTO)

print: *.c
	lpr -p $?
	touch print

objects:= $(wildcard *.o)