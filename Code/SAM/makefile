
CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lserial -lgsl -lgslcblas -larmadillo
OTHER=-std=c++0x
INCFLAGS=-I/usr/local/include
SOURCES=$(wildcard *.cpp)
OBJECTS=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
EXECUTABLE=minibot


all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCFLAGS) $(OTHER) $< -o $@

clean:
	rm *.o