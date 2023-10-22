ifeq '$(findstring ;,$(PATH))' ';'
    detected_OS := Windows
else
    detected_OS := $(shell uname 2>/dev/null || echo Unknown)
    detected_OS := $(patsubst CYGWIN%,Cygwin,$(detected_OS))
    detected_OS := $(patsubst MSYS%,MSYS,$(detected_OS))
    detected_OS := $(patsubst MINGW%,MSYS,$(detected_OS))
endif

ifeq ($(detected_OS),Windows)
	LIBS := -lopengl32 -lshell32 -lgdi32 -lm -I./include
	EXT = exe
endif
ifeq ($(detected_OS),Darwin)        # Mac OS X
	LIBS := -I./include -lm -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo
	EXT = out
endif
ifeq ($(detected_OS),Linux)
    LIBS := -I./include -lX11 -lGLX -lm
	EXT = out
endif

all:
	gcc source/main.c -O3 -I./include $(LIBS) -o RSGL-2048.$(EXT)
	strip RSGL-2048.$(EXT)

debug:
	gcc source/main.c -I./include $(LIBS) -o RSGL-2048.$(EXT)
	./RSGL-2048.$(EXT)