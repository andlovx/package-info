#include <iostream>
#include "format.hpp"

int main(int argc, char **argv)
{
    Package package1, package2;
    PackageList list;
    std::string format = "xml";

    if (argc > 1)
    {
        format = argv[1];
    }

    package1.name("package1");
    package1.version("1.2.3");
    package1.license("MIT");

    package2.name("package2");
    package2.version("1.0.0");
    package2.license("GPL-3");

    list.add(package1);
    list.add(package2);

    std::cout << "Create output formatter for " << format << "\n";
    const Formatter *formatter = Formatter::create(format);

    std::cout << "[1]:" << std::endl;
    formatter->output(std::cout, package1);
    std::cout << std::endl;

    std::cout << "[2]:" << std::endl;
    formatter->output(std::cout, list);

    delete formatter;
    return 0;
}
