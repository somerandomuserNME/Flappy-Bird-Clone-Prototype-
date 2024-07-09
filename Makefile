all:
	g++ -I src/include -L src/lib -o main src/main.cpp src/renderwindow.cpp src/entity.cpp src/math.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image