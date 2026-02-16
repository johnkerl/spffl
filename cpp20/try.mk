build:
	mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && cmake --build .

test:
	cd build && ctest --output-on-failure

clean:
	rm -rf build _deps

.PHONY: build test clean
