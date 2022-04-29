all: 
	mkdir -p ./build/
	$(CXX) main.c -Iinclude -o ./build/main -g -ansi
