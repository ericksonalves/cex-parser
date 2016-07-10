#include <exception>
#include <iostream>
#include "cex_parser.h"

int main(int argc, const char** argv)
{
    try {
        cex_parser cex_parser(argc, argv);
        std::cout << cex_parser.get_interleaving() << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
