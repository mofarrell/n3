CC=g++
CFLAGS=-c -Wall -I /System/Library/Frameworks/OpenGL.framework/Headers
LDFLAGS=-framework OpenGL -lncurses
SOURCES=main.cpp shader.cpp renderer.cpp display.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=n3

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *~ *.o n3

