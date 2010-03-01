CC=g++
TARGET= $(wildcard *.cpp)
OBJ= $(TARGET:.cpp=.o) 


all: libprog3dlib.a
libprog3dlib.a: $(OBJ)
	ar rvu $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

