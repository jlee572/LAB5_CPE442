CC=g++
PROGRAM_NAME=sobel_filter
CFLAGS=-Wall -g
LDFLAGS=-lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lm 
C_HEADERS=sobel.hpp grayscale.hpp
C_SOURCES=main.cpp sobel.cpp grayscale.cpp

all: $(C_HEADERS) $(C_SOURCES)
	$(CC) -o $(PROGRAM_NAME) $(CFLAGS) $(C_SOURCES) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o
	rm -f $(PROGRAM_NAME)
