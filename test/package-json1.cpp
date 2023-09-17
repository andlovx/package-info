#include <iostream>
#ifdef HAVE_STRUCT_MAPPING_H
#include <fstream>
#include <sstream>
#include "struct_mapping.h"

//
// Test driver for JSON parsing using struct_mapping. This C++ library
// seems to have problem with parsing strings with escape sequences and
// wildcard characters.
//
// For example, mapping package.json from "html-escaper" and "highlight-words"
// causes exception, while "agent-base" works. Expected output when running
// without arguments:
//
//  Package: {
//      name: agent-base
//      version: 6.0.2
//      license: MIT
//  }
//
// Repository: https://github.com/bk192077/struct_mapping/tree/master
//

namespace json = struct_mapping;

struct Package
{
    std::string name;
    std::string version;
    std::string license;
};

static void readfile(const char *file, std::string &result)
{
    std::ifstream input(file);
    result = "";

    for (std::string line; std::getline(input, line);)
    {
        result += line + "\n";
    }
}

static std::ostream &operator<<(std::ostream &out, const Package &package)
{
    return out << "{\n"
               << "  name: " << package.name << "\n"
               << "  version: " << package.version << "\n"
               << "  license: " << package.license << "\n"
               << "}";
}

int main(int argc, char **argv)
{
    std::string doc = R"(
{
    "name": "package-name",
    "version": "1.2.3",
    "license": "MIT"    
}
    )";
    Package package;

    if (argc > 1)
    {
        readfile(argv[1], doc);
    }

    json::reg(&Package::name, "name");
    json::reg(&Package::version, "version");
    json::reg(&Package::license, "license");

    std::istringstream data(doc);
    json::map_json_to_struct(package, data);

    std::cout << "DOC: " << doc << std::endl;
    std::cout << "PACKAGE: " << package << std::endl;

    return 0;
}
#else
int main()
{
    std::cout << "Install the struct_mapping library for running this test.\n";
    return 0;
}
#endif // HAVE_STRUCT_MAPPING_H
