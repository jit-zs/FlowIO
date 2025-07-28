

all: 
	cmake -B build/ -G "MinGW Makefiles"
	cd build; make

clean:
	rm -r -f build/*