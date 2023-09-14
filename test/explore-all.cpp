#include <iostream>
#include "explorer.hpp"

int main(int argc, char **argv)
{
    DirectoryExplorer explorer;

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
