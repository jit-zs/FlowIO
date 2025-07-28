

all: 
	cmake -B build -G "MinGW Makefiles"
	make -f build/makefile

clean:
	rm -r -f build/*