#include <iostream>
#include "package.hpp"

int main()
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
    p1.download("https://registry.npmjs.org/hello1/-/hello1.1.2.3.tgz");
    p1.project("https://hello1.mydomanin.org");
    p1.hash("sha512-Yqfm+XDx0+Prh3VSeEQCPU81yC+JWZ2pDPFSS4ZdpfZhp4MkFMaDC1UqseovEKwSUpnIL7+vK+Clp7bfh0iD7g==");

    std::cout << "p1: " << p1 << std::endl;

    return 0;
}
