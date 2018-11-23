PROYECTO=Cliente
CFLAGS=-Wall
LFLAGS=
CC=g++

all: $(PROYECTO)

%.o: %.cpp
	$(CC) -c $< $(CFLAGS) 

$(PROYECTO) : $(patsubst %.cpp,%.o,$(wildcard *.cpp))
	$(CC) $^ -o $@ $(LFLAGS) 
	rm *.o

.PHONY: clean

clean:
	rm -f *.o $(PROYECTO)
	


