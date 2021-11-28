SOURCE = source/main.cpp
LIBS = source/bin/libRSGL.so
GXX = g++
OUTPUT = 2048

all:
	$(GXX) $(SOURCE) $(LIBS) -o $(OUTPUT)
	
linux:
	$(GXX) $(SOURCE) $(LIBS) -o $(OUTPUT)
