default: debug #release

mkdir-build:
	@mkdir -p build

rebuild: clean release 

compile:
	@cd build && make -s -j

clean:
	@rm -rf build

cmake-debug: mkdir-build
	@cd build && cmake -DCMAKE_BUILD_TYPE=Debug ..

cmake-release: mkdir-build
	@cd build && cmake -DCMAKE_BUILD_TYPE=Release ..

debug: cmake-debug compile

release: cmake-release compile

.PHONY: mkdir-build rebuild compile clean cmake-debug cmake-release debug release