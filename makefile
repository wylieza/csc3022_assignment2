GCC = g++

VER = -std=c++11

xargs = MRI -x 1 output_x
dargs = MRI -d 1 1 output_d
blankargs = MRI

volimage: volimage.o
	$(GCC) -o volimage volimage.o $(VER)

volimage.o: volimage.cpp
	$(GCC) -c -o volimage.o volimage.cpp $(VER)

run: volimage
	./volimage ${args}

runx: volimage
	./volimage ${xargs}

rund: volimage
	./volimage ${dargs}

runblank: volimage
	./volimage ${blankargs}

clean:
	rm -rf volimage volimage.o