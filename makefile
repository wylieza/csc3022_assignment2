GCC = g++

VER = -std=c++11

volimage: volimage.o
	$(GCC) -o volimage volimage.o $(VER)

volimage.o: volimage.cpp
	$(GCC) -c -o volimage.o volimage.cpp $(VER)

run: volimage
	./volimage ${args}

clean:
	rm -rf volimage volimage.o