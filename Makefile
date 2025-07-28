

all: 
	cmake -B build -G "MinGW Makefiles" -C build
	make -f build/Makefile

clean:
	rm -r -f build/*