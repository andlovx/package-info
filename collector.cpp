#include <iostream>
#include <filesystem>
#include "collector.hpp"
#include "explorer.hpp"
#include "package.hpp"

void Collector::process()
{
    process(std::filesystem::current_path());
}

void Collector::process(std::string root)
{
    DirectoryExplorer explorer(root);
    DirectoryExplorer::file_list list;
    DirectoryExplorer::file_list lock;
    Package package;
    PackageLock lockfile;

    explorer.set_filter(DirectoryExplorer::FILES);
    explorer.set_exclude({".git", ".svn"});
    explorer.set_files(list, "package.json");
    explorer.set_files(lock, "package-lock.json");

    for (auto file : lock)
    {
        lockfile.read_lockfile(file);
    }

    for (auto file : list)
    {
        if (_debug)
        {
            std::cout << "Processing: " << file << std::endl;
        }

        try
        {
            package = _explorer.discover(file);

            if (package.name().empty() ||
                package.version().empty())
            {
                continue;
            }
            if (lockfile.has_package(package.name()))
            {
                package.hash(lockfile.integrity(package.name()));
                package.hash(lockfile.hash_type(package.name()));
            }

            _packages.add(package);
        }
        catch (const std::exception &exception)
        {
            std::cerr << "error: " << exception.what() << std::endl;
            std::cerr << "error: failed process " << file << std::endl;
            continue;
        }

        if (_debug)
        {
            std::cout << "Discovered: " << package << std::endl;
        }
    }
}

const PackageList &Collector::get_packages() const
{
    return _packages;
}

void Collector::set_debug(bool enable)
{
    _debug = enable;
}
