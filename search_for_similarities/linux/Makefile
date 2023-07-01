CC=g++
CFLAGS=-c -Wall -std=c++17
LDFLAGS= "-pthread"

SOURCES= Application.cpp SlidingWindow.cpp SmithWaterman.cpp Alignment.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE= Application

all: $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o ./$@

.cpp.o:
	$(CC) $(CFLAGS) $< -o ./$@

clean:
	rm -rf *.o