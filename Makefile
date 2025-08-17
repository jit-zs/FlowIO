

all: build/CMakeCache.txt
	cd build; make
build/CMakeCache.txt: $(wildcard src/*.cpp) $(wildcard test_src/*.cpp)
	cmake -B build/ -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
run:
	build/mutable_test
clean: 
	rm -r -f build/*