#ifndef EXPLORER_HPP
#define EXPLORER_HPP

#include <string>
#include <vector>
#include <functional>
#include <regex>
#include <filesystem>

class DirectoryExplorer
{
public:
    using file_list = std::vector<std::string>;
    using file_entry = std::filesystem::directory_entry;

    enum Filter // Inclusive filter
    {
        HIDDEN = 0x1,
        FILES = 0x2,
        DIRS = 0x4,
        LINKS = 0x8,
        BLOCK = 0x10,
        CHARACTER = 0x20,
        FIFO = 0x40,
        SOCKET = 0x80,
        DOTDIR = 0x100,

        ALL = HIDDEN | FILES | DIRS | LINKS |
              BLOCK | CHARACTER | FIFO | SOCKET |
              DOTDIR,

        DEFAULT = ALL
    };

    DirectoryExplorer();
    DirectoryExplorer(std::string path);
    DirectoryExplorer(Filter filter);
    DirectoryExplorer(int filter);

    void set_path(std::string path);

    void set_files(file_list &list) const;
    void set_files(file_list &list, std::string name) const;
    void set_files(file_list &list, std::regex match) const;
    void set_files(file_list &list, std::function<bool(const file_entry &file)> match) const;
    void set_files(file_list &list, std::function<bool(std::string name)> match,
                   const std::vector<std::string> &exclude = std::vector<std::string>()) const;

    file_list get_files() const;
    file_list get_files(std::string name) const;
    file_list get_files(std::regex match) const;
    file_list get_files(std::function<bool(const file_entry &file)> match) const;
    file_list get_files(std::function<bool(std::string name)> match,
                        const std::vector<std::string> &exclude = std::vector<std::string>()) const;

    int get_filter() const;
    void set_filter(int filter);
    void set_filter(Filter filter);
    void add_filter(int filter);
    void add_filter(Filter filter);
    void remove_filter(int filter);
    void remove_filter(Filter filter);
    bool has_filter(Filter filter) const;

    void use_fullname(bool enable);
    bool use_fullname() const;

private:
    bool is_filtered(const file_entry &) const;

    bool _fullname = false;
    std::string _path;
    int _filter = DEFAULT;
};

#endif // EXPLORER_HPP
