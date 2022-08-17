OUTPUT = RSGL-2048
GXX = g++
SOURCE = source/*.cpp
LIBS = $(shell RSGL-static)

build:
	mkdir -p build
	$(GXX) $(SOURCE) $(LIBS) -o build/$(OUTPUT)
	cp -r res ./build

installDesktopFile: # no sudo
	cp res/2048.desktop ~/Desktop/
	cp res/2048.desktop ~/.local/share/applications/RSGL2048.desktop

install:
	chmod +x $(OUTPUT)
	cp $(OUTPUT) /usr/bin
	mkdir -p /usr/share/$(OUTPUT)
	cp -r build/* /usr/share/$(OUTPUT)
	sudo cp RSGL-2048 /usr/bin