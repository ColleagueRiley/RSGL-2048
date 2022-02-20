SOURCE = source/main.cpp
LIBS = -lRSGL
GXX = g++
OUTPUT = RSGL-2048

all:
	sudo cp res/fonts/SansPosterBold.ttf /usr/share/fonts
	$(GXX) $(SOURCE) $(LIBS) -o $(OUTPUT)

build:
	sudo cp res/fonts/SansPosterBold.ttf /usr/share/fonts
	$(GXX) $(SOURCE) $(LIBS) -o $(OUTPUT)

install:
	make
	sudo mv RSGL-2048 /usr/bin/
	cp res/2048.desktop ~/Desktop/
	cp res/2048.desktop ~/.local/share/applications/RSGL2048.desktop
