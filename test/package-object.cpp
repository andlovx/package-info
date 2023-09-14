#include <iostream>
#include "package.hpp"

int main(int argc, char **argv)
{
    Package p1, p2("hello2");
    std::string p3(p2);

    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p2: " << p2 << std::endl;
    std::cout << "p3: " << p3 << std::endl;

    p1.name("hello1");
    p1.license(LicenseType::APACHE);
    p1.license("Apache License Version 2");
    p1.version("1.2.3");
    p1.url("https://registry.npmjs.org/hello1/-/hello1.1.2.3.tgz");

    std::cout << "p1: " << p1 << std::endl;

    return 0;
}
