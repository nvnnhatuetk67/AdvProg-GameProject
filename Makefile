+All:
	 g++ -w -Idata\include -Ldata\lib -o game src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf 