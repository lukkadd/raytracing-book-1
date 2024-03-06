CC=g++

DEPS = *.hpp
OBJ = *.o 
SOURCEDIR = ./src
DISTDIR = ./dist

SOURCES := $(wildcard $(SOURCEDIR)/*.cpp) $(wildcard $(SOURCEDIR)/*.hpp)


raytracer: 
	$(CC) $(SOURCES) -o $(DISTDIR)/raytracer

run: raytracer
	$(DISTDIR)/raytracer.exe  
