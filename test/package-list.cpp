#include <iostream>
#include "package.hpp"

static void dump(int id, const PackageList &list)
{
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        std::cout << "package[" << id << "]: " << it->first << std::endl;
    }
}

int main()
{
    Package p1("hello1"), p2("hello2");

    PackageList list;
    list.add(p1);
    list.add(p2);
    dump(1, list);

    list.remove(p1);
    dump(2, list);

    list.add(p1);
    list.remove("hello2");
    dump(3, list);

    std::cout << "exist: " << list.exists("hello1") << std::endl;
    std::cout << "exist: " << list.exists("hello2") << std::endl;

    list.remove("hello1");
    std::cout << "exist: " << list.exists("hello1") << std::endl;

    return 0;
}
