# Out-of-source build in build/. Remove in-source CMake state so FetchContent
# runs in build/ and gets a complete Catch2 (avoids broken cpp20/_deps).
build:
	rm -rf CMakeCache.txt _deps
	mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && cmake --build .

test:
	cd build && ctest --output-on-failure

clean:
	rm -rf build _deps CMakeCache.txt CMakeFiles Makefile cmake_install.cmake CTestTestfile.cmake Testing generated-includes

# Format all C/C++ source and headers with clang-format (excludes build and deps).
fmt:
	find . -type f \( -name '*.c' -o -name '*.h' -o -name '*.cpp' -o -name '*.hpp' -o -name '*.cc' -o -name '*.cxx' \) \
	  ! -path './build/*' ! -path './_deps/*' ! -path './.git/*' -print0 | \
	  xargs -0 clang-format -i

.PHONY: build test clean fmt
