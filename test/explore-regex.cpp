#include <iostream>
#include "explorer.hpp"

int main(int argc, char **argv)
{
    DirectoryExplorer explorer;
    std::string match = ".*\\.cpp|.*\\.hpp";

    if (argc > 1)
    {
        explorer.set_path(argv[1]);
    }
    if (argc > 2)
    {
        match = argv[2];
    }

    auto listing = explorer.get_files(std::regex(match));

    for (auto it = listing.begin(); it != listing.end(); ++it)
    {
        std::cout << "file: " << *it << std::endl;
    }

    return 0;
}
