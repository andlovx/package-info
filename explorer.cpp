#include <filesystem>
#include "explorer.hpp"

namespace fs = std::filesystem;
using file_list = DirectoryExplorer::file_list;

DirectoryExplorer::DirectoryExplorer()
    : _path(fs::current_path())
{
}

DirectoryExplorer::DirectoryExplorer(std::string path)
    : _path(path)
{
}

DirectoryExplorer::DirectoryExplorer(Filter filter)
    : _path(fs::current_path()),
      _filter(filter)
{
}

void DirectoryExplorer::set_path(std::string path)
{
    _path = path;
}

void DirectoryExplorer::set_files(file_list &list) const
{
    set_files(list, std::regex(".*"));
}

void DirectoryExplorer::set_files(file_list &list, std::string name) const
{
    set_files(list, std::regex(name));
}

void DirectoryExplorer::set_files(file_list &list, std::regex match) const
{
    set_files(list, [&match](std::string filename)
              { return std::regex_match(filename, match); });
}

void DirectoryExplorer::set_files(file_list &list, std::function<bool(std::string)> match) const
{
    fs::recursive_directory_iterator rdi(fs::canonical(_path));

    for (auto file : rdi)
    {
        if (!match(file.path().filename()))
        {
            continue;
        }
        if (file.is_block_file() && !has_filter(BLOCK))
        {
            continue;
        }
        if (file.is_character_file() && !has_filter(CHARACTER))
        {
            continue;
        }
        if (file.is_directory() && !has_filter(DIRS))
        {
            continue;
        }
        if (file.is_fifo() && !has_filter(FIFO))
        {
            continue;
        }
        if (file.is_socket() && !has_filter(SOCKET))
        {
            continue;
        }
        if (file.is_symlink() && !has_filter(LINKS))
        {
            continue;
        }
        if (file.is_regular_file() && !has_filter(FILES))
        {
            continue;
        }
        if (file.path().generic_string()[0] == '.' && !has_filter(HIDDEN))
        {
            continue;
        }

        list.push_back(file.path());
    }
}

file_list DirectoryExplorer::get_files() const
{
    file_list list;
    set_files(list);
    return list;
}

file_list DirectoryExplorer::get_files(std::string name) const
{
    file_list list;
    set_files(list, name);
    return list;
}

file_list DirectoryExplorer::get_files(std::function<bool(std::string)> match) const
{
    file_list list;
    set_files(list, match);
    return list;
}

int DirectoryExplorer::get_filter() const
{
    return _filter;
}

void DirectoryExplorer::set_filter(int filter)
{
    _filter = filter;
}

void DirectoryExplorer::set_filter(Filter filter)
{
    _filter = filter;
}

void DirectoryExplorer::add_filter(int filter)
{
    _filter |= filter;
}

void DirectoryExplorer::add_filter(Filter filter)
{
    _filter |= filter;
}

void DirectoryExplorer::remove_filter(int filter)
{
    _filter &= ~filter;
}

void DirectoryExplorer::remove_filter(Filter filter)
{
    _filter &= ~filter;
}

bool DirectoryExplorer::has_filter(Filter filter) const
{
    return (_filter & filter) != 0;
}

file_list DirectoryExplorer::get_files(std::regex match) const
{
    file_list list;
    set_files(list, match);
    return list;
}
