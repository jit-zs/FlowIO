

all: 
	cmake -B build/ -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
	cd build; make
	build/mutable_test
clean:
	rm -r -f build/*