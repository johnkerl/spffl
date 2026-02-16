# Out-of-source build in build/. Remove in-source CMake state so FetchContent
# runs in build/ and gets a complete Catch2 (avoids broken cpp20/_deps).
build:
	rm -rf CMakeCache.txt _deps
	mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && cmake --build .

test:
	cd build && ctest --output-on-failure

clean:
	rm -rf build _deps CMakeCache.txt CMakeFiles Makefile cmake_install.cmake CTestTestfile.cmake Testing generated-includes

.PHONY: build test clean
