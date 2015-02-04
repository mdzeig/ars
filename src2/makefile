CC=clang++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-stdlib=libc++
SOURCES=testbed.cc estimating_distribution.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=testme

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm $(OBJECTS)