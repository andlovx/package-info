#include <iostream>
#include "package.hpp"

int main(int argc, char **argv)
{
    Package p1, p2("hello");
    std::string p3(p2);

    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p2: " << p2 << std::endl;
    std::cout << "p3: " << p3 << std::endl;

    return 0;
}
