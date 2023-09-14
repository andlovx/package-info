#include <iostream>
#include "explorer.hpp"

static void dump(std::string label, DirectoryExplorer explorer)
{
    std::cout
        << label << " [" << explorer.get_filter() << "]: {\n"
        << "    hidden: " << explorer.has_filter(DirectoryExplorer::HIDDEN) << ",\n"
        << "    files: " << explorer.has_filter(DirectoryExplorer::FILES) << ",\n"
        << "    dirs: " << explorer.has_filter(DirectoryExplorer::DIRS) << ",\n"
        << "    links: " << explorer.has_filter(DirectoryExplorer::LINKS) << "\n"
        << "}\n\n";
}

int main()
{
    DirectoryExplorer explorer;
    dump("default filter", explorer);

    explorer.add_filter(DirectoryExplorer::HIDDEN);
    dump("filter 1", explorer);

    explorer.add_filter(DirectoryExplorer::FILES);
    dump("filter 2", explorer);

    explorer.remove_filter(DirectoryExplorer::DIRS);
    dump("filter 3", explorer);

    explorer.remove_filter(DirectoryExplorer::DIRS | DirectoryExplorer::HIDDEN);
    dump("filter 4", explorer);

    explorer.remove_filter(DirectoryExplorer::ALL);
    dump("filter 5", explorer);

    explorer.add_filter(DirectoryExplorer::FILES | DirectoryExplorer::LINKS);
    dump("filter 6", explorer);

    explorer.set_filter(DirectoryExplorer::HIDDEN);
    dump("filter 7", explorer);

    explorer.set_filter(DirectoryExplorer::FILES | DirectoryExplorer::DIRS);
    dump("filter 8", explorer);

    return 0;
}
