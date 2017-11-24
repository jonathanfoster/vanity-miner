all:
	g++ -std=c++11 -o vanity-miner src/main.cpp $(shell pkg-config --cflags --libs libbitcoin)

