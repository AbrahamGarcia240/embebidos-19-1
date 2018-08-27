PROYECTO=muestreo
DESTDIR=/usr/local/bin
CFLAGS=-Wall
LDFLAGS=-lm
CC=gcc


all: $(PROYECTO)

muestreo.o: muestreo.c
	$(CC) -c muestreo.c  $(CFLAGS)

procesamiento.o: procesamiento.c
	$(CC) -c procesamiento.c $(CFLAGS)

archivos.o: archivos.c
	$(CC) -c archivos.c $(CFLAGS)

$(PROYECTO): muestreo.o procesamiento.o archivos.o
	$(CC) muestreo.o procesamiento.o archivos.o -o $@ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o muestreo

install: all
	if [ ! -d $(DESTDIR) ] ; then \
		sudo mkdir $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)