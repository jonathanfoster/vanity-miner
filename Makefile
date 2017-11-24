all: build

clean:
	rm -rf build
build: clean
	mkdir build
	g++ -o build/vanity-miner src/main.cpp $(pkg-config --cflags --libs libbitcoin)

