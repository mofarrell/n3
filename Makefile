CC=g++
CFLAGS=-c -Wall -I /System/Library/Frameworks/OpenGL.framework/Headers #-DTLF_FONTS
LDFLAGS=-framework OpenGL -lncurses
SOURCES=main.cpp shader.cpp renderer.cpp display.cpp objloader.cpp apirunner/game.cpp apirunner/player.cpp apirunner/gamecube.cpp #figlet/figlet.c figlet/zipio.c figlet/inflate.c figlet/utf8.c figlet/crc.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=n3

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *~ *.o n3

