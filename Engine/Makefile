ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname -s)
endif

ifeq ($(detected_OS), Windows)
    target = eternal2d.exe
    libraries_path = windows
endif
ifeq ($(detected_OS), Linux)
    target = eternal2d
    libraries_path = linux
endif
ifeq ($(detected_OS), Darwin)
    target = eternal2d
    libraries_path = mac
endif

SRCS := ./src/Engine/*.cpp ./src/Engine/Components/*.cpp ./src/Engine/Bindings/*.cpp ./ThirdParty/src/Box2D/*/*.cpp ./ThirdParty/src/Box2D/*/*/*.cpp
EDITOR_SRCS := ./src/Editor/Exporter.cpp

target_location = Eternal2D/$(libraries_path)/$(target)

$(target_location): $(SRCS) ./include/Engine/*.hpp ./include/Engine/Components/*.hpp
	clang++ -std=c++14 $(SRCS) -L./ThirdParty/lib/$(libraries_path) -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image -I./include -I./ThirdParty/include -I./include/Engine -I./include/Engine/Components `python3-config --includes` `python3-config --ldflags` -o $(target_location)

editor: $(EDITOR_SRCS)
	clang++ -shared -std=c++14 $(EDITOR_SRCS) -I./include/Engine/ -I./ThirdParty/include `python3-config --includes` `python3-config --ldflags` -fPIC -o Eternal2D/Editor/exporter`python3-config --extension-suffix`
