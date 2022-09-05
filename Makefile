OUTPUT = RSGL-2048
GXX = g++
SOURCE = source/*.cpp
APPIMAGE = -appImage -b $(OUTPUT) -r res -o $(OUTPUT)
LIBS = $(shell RSGL-static)

build:
	$(GXX) $(SOURCE) $(LIBS) -o $(OUTPUT)
	make buildAppImage

buildAppImage:
	RSGL-static $(APPIMAGE)

install:
	sudo cp $(OUTPUT).appImage /usr/bin

installDesktopFile: # no sudo
	cp res/2048.desktop ~/Desktop/
	cp res/2048.desktop ~/.local/share/applications/RSGL2048.desktop