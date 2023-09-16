#include <iostream>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>

//
// Test driver using Niels Lohmann library: JSON for Modern C++. Install
// on Debian using "apt-get install nlohmann-json3-dev".
//
// Repository: https://github.com/nlohmann/json/
//

using json = nlohmann::json;

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
    return out << "Package: {\n"
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

    json data = json::parse(doc);

    package.name = data["name"];
    package.version = data["version"];
    package.license = data["license"];

    std::cout << "JSON: " << doc << std::endl;
    std::cout << package << std::endl;

    return 0;
}
