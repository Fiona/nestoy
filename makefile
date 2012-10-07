EXECUTABLE=nestoy
SOURCES=main.cpp \
Core.cpp 

CC=g++
CFLAGS=-c -Wall

#SDLFLAGS=-Wl,-Bstatic `sdl-config --static-libs` -lSDL_image -lSDL_ttf -lfreetype -lz -Wl,-Bdynamic -lGL
OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o 
