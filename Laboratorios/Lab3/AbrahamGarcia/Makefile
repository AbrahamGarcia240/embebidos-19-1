PROYECTO=muestreo
DESTDIR=/usr/local/bin
CFLAGS=-Wall
LDFLAGS=-lm
CC=gcc
#objects = muestreo.o procesamiento.o archivos.o
objects = $(wildcard *.c)
#el uso de caracteres wildcard; funciones para analizis y sustitucion de cadenas
all: $(PROYECTO)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

#muestreo.o: muestreo.c
#	$(CC) -c muestreo.c  $(CFLAGS)

#procesamiento.o: procesamiento.c
#	$(CC) -c procesamiento.c $(CFLAGS)

#archivos.o: archivos.c
#	$(CC) -c archivos.c $(CFLAGS)


$(PROYECTO): $(objects:.c=.o)
	$(CC) $^ -o $@ $(LDFLAGS)

#$^ toma toda la lista de dependencias
#$@ toma el nombre del objetivo


.PHONY: clean

clean:
	rm -f *.o $(PROYECTO)

install: all
	if [ ! -d $(DESTDIR) ] ; then \
		sudo mkdir $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)