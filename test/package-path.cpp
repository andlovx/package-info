#include <iostream>
#include <string>
#include "package.hpp"

int main(int argc, char **argv)
{
    std::string path = "/var/lib/app/node_modules/electron-squirrel-startup/node_modules/debug/package.json";

    if (argc > 1)
    {
        path = argv[1];
    }

    PackagePath package(path);

    for (std::string part : package)
    {
        std::cout << "Part: '" << part << "'\n";
    }

    std::cout << "Count 1: " << package.count("node_modules") << "\n";
    std::cout << "Count 2: " << package.count("missing") << "\n";

    std::cout << "Primary: " << package.is_primary() << "\n";
    std::cout << "Parent:  " << package.parent() << "\n";

    return 0;
}