#include <iostream>
#include "collector.hpp"

int main(int argc, char **argv)
{
    Collector collector;

    if (argc > 1)
    {
        collector.process(argv[1]);
    }
    else
    {
        collector.process();
    }

    for (auto package : collector.get_packages())
    {
        std::cout << "Package: " << package.first << std::endl;
    }
}
