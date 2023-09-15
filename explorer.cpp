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

DirectoryExplorer::DirectoryExplorer(int filter)
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

void DirectoryExplorer::set_files(file_list &list, std::function<bool(const file_entry &file)> match) const
{
    fs::recursive_directory_iterator rdi(fs::canonical(_path));

    for (auto file : rdi)
    {
        if (is_filtered(file))
        {
            continue;
        }
        if (match(file))
        {
            list.push_back(file.path());
        }
    }
}

void DirectoryExplorer::set_files(file_list &list, std::function<bool(std::string)> match, const std::vector<std::string> &exclude) const
{
    fs::recursive_directory_iterator rdi(fs::canonical(_path));

    auto is_excluded = [&exclude](const std::string &path) -> bool
    {
        for (auto subdir : exclude)
        {
            if (path.find(subdir) != std::string::npos)
            {
                return true;
            }
        }

        return false;
    };

    for (auto file : rdi)
    {
        if (is_filtered(file))
        {
            continue;
        }
        if (is_excluded(file.path()))
        {
            continue;
        }
        if (use_fullname() && match(file.path()))
        {
            list.push_back(file.path());
        }
        if (!use_fullname() && match(file.path().filename()))
        {
            list.push_back(file.path());
        }
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

file_list DirectoryExplorer::get_files(std::regex match) const
{
    file_list list;
    set_files(list, match);
    return list;
}

file_list DirectoryExplorer::get_files(std::function<bool(const file_entry &file)> match) const
{
    file_list list;
    set_files(list, match);
    return list;
}

file_list DirectoryExplorer::get_files(std::function<bool(std::string)> match, const std::vector<std::string> &exclude) const
{
    file_list list;
    set_files(list, match, exclude);
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

void DirectoryExplorer::use_fullname(bool enable)
{
    _fullname = enable;
}

bool DirectoryExplorer::use_fullname() const
{
    return _fullname;
}

bool DirectoryExplorer::is_filtered(const file_entry &file) const
{
    static std::string dotdir(fs::path::preferred_separator + std::string("."));

    if (file.is_block_file() && !has_filter(BLOCK))
    {
        return true;
    }
    if (file.is_character_file() && !has_filter(CHARACTER))
    {
        return true;
    }
    if (file.is_directory() && !has_filter(DIRS))
    {
        return true;
    }
    if (file.is_fifo() && !has_filter(FIFO))
    {
        return true;
    }
    if (file.is_socket() && !has_filter(SOCKET))
    {
        return true;
    }
    if (file.is_symlink() && !has_filter(LINKS))
    {
        return true;
    }
    if (file.is_regular_file() && !has_filter(FILES))
    {
        return true;
    }
    if (file.path().generic_string()[0] == '.' && !has_filter(HIDDEN))
    {
        return true;
    }
    if (file.path().generic_string().find(dotdir) != std::string::npos && !has_filter(DOTDIR))
    {
        return true;
    }

    return false;
}
