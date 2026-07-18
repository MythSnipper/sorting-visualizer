.PHONY: build

#tools used
CC = gcc
CXX = g++
LD = ld
STRIP = strip

CXXFLAGS =\
	-std=c++20 \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-Wno-unused-variable \
	-Iinclude \
	-O0 \
	-fsanitize=address,undefined \
	-fno-omit-frame-pointer \
	-g \
	$(shell pkg-config --cflags sdl2)

CXXFLAGS_L =\
	$(shell pkg-config --libs sdl2)

LDFLAGS =\


givesudo:
	sudo echo give me sudo

clean:
	rm -rf build

#build code into build directory
build:
	mkdir -p build
	$(CXX) $(CXXFLAGS) src/main.cpp src/visualizer.cpp src/sorts.cpp $(CXXFLAGS_L) -o build/sortingvisuals

	$(STRIP) build/sortingvisuals

run: build
	printf "Running program:\n"
	./build/sortingvisuals
