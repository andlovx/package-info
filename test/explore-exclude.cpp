#include <iostream>
#include "explorer.hpp"

int main(int argc, char **argv)
{
    DirectoryExplorer explorer(DirectoryExplorer::FILES | DirectoryExplorer::DOTDIR);
    explorer.set_exclude({"test", ".git"});

    if (argc > 1)
    {
        explorer.set_path(argv[1]);
    }

    auto listing = explorer.get_files();

    for (auto it = listing.begin(); it != listing.end(); ++it)
    {
        std::cout << "file: " << *it << std::endl;
    }

    return 0;
}
