default: liblodepng libclickwise cwut

cwc: ./lib/libclickwise ./src/cwc_main.cpp
	g++ -o ./bin/cwc ./src/cwc_main.cpp -Idependencies/SFML/include -Lbuild/lib -lclickwise -Ldependencies/built/lib -lsfml-graphics -lsfml-window -lsfml-system

cwut: ./lib/libclickwise ./src/main.cpp
	g++ -o ./bin/cwut ./src/main.cpp -Lbuild/lib/ -lclickwise

./lib/libclickwise: ./build/int/lodepng.o ./build/int/lodepng_util.o ./build/int/clickwise.o ./build/int/clocktalk.o
	ar rcs ./lib/libclickwise /build/int/lodepng.o ./build/int/lodepng_util.o ./build/int/clickwise.o ./build/int/clocktalk.o

./build/int/clickwise.o:
	g++ -c -o ./build/int/clickwise.o ./src/clickwise.cpp

./build/int/clocktalk.o:
	g++ -c -o ./build/int/clocktalk.o ./src/clocktalk.cpp

./lib/liblodepng: ./build/int/lodepng.o ./build/int/lodepng_util.o
	ar rcs ./lib/liblodepng ./build/int/liblodepng.o ./build/int/lodepng_util.o

./build/int/lodepng.o: ./dependencies/lodepng/lodepng.cpp
	g++ -c -o ./build/int/lodepng.o ./dependencies/lodepng/lodepng.cpp

./build/int/lodepng_util.o: ./dependencies/lodepng/lodepng_util.cpp
	g++ -c -o ./build/int/lodepng_util.o ./dependencies/lodepng/lodepng_util.cpp

clean:
	rm -rf ./build/int
	rm -rf ./lib
	rm -rf ./bin

rebuild: