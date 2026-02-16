build:
	mkdir -p build
	cd build
	cmake .. -DCMAKE_BUILD_TYPE=Release
	cmake --build .

test:
	/build
	ctest --output-on-failure

clean:
	rm -f build _deps

.PHONY: build test clean
