#include <iostream>
#include "explorer.hpp"
#include "package.hpp"

int main(int argc, char **argv)
{
    DirectoryExplorer explorer;
    PackageLock lock;

    if (argc > 1)
    {
        explorer.set_path(argv[1]);
    }

    auto listing = explorer.get_files("package-lock.json");

    for (auto it = listing.begin(); it != listing.end(); ++it)
    {
        std::cout << "file: " << *it << std::endl;
        lock.read_lockfile(*it);
    }

    for (auto package : lock.get_list())
    {
        std::cout << "name: " << package.first << ": " << package.second << std::endl;
    }

    return 0;
}
