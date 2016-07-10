cex_parser: src/utils.cpp src/state.cpp src/cex_parser.cpp
	clang++ -std=c++11 -Wall -o cex_parser src/utils.cpp src/state.cpp src/cex_parser.cpp src/main.cpp
