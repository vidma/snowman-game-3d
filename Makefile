CC=g++
PROG3D=./prog3d
OBJET3D=./objet3d
LIBPROG3D=$(PROG3D)/libprog3dlib.a
LIBOBJET3D=$(OBJET3D)/libobjet3dlib.a
CFLAGS=-I$(PROG3D) -I$(OBJET3D)
LDFLAGS= -lglut -lGLU -lGL -L$(PROG3D) -lprog3dlib -L$(OBJET3D) -lobjet3dlib  -lIL -lGLEW
TARGET= $(wildcard *.cpp)
OBJ= $(TARGET:.cpp=.o) 

.PHONY:$(LIBPROG3D) $(LIBOBJET3D)

all: $(PROG3D)/libprog3dlib.a $(OBJET3D)/libobjet3dlib.a mr-propper uzd3
$(LIBPROG3D):
	make -C $(PROG3D)
	
$(LIBOBJET3D):
	make -C $(OBJET3D)

mr-propper:
	#rm -f navigation.o
	
uzd3: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
	

#navigation.o: navigation.cpp
#	$(CC) -o $@ -c $< $(CFLAGS) -L$(PROG3D) -lprog3dlib -L$(OBJET3D)

