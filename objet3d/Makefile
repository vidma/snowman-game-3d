CC=g++
CFLAGS=-I../prog3d/
TARGET= $(wildcard *.cpp)
OBJ= $(TARGET:.cpp=.o) 


all: libobjet3dlib.a
libobjet3dlib.a: $(OBJ)
	ar rvu $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

