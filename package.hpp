#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include <string>
#include <map>
#include <vector>

enum LicenseType
{
    MIT,
    GNU,
    APACHE,
    OTHER
};

enum HashType
{
    ETAG,
    MD5,
    SHA1,
    SHA224,
    SHA256,
    SHA384,
    SHA512,
    MISSING,
    UNKNOWN
};

class Package
{
public:
    Package();
    Package(std::string name);
    Package(std::string name, std::string version, std::string download = "", std::string hash = "");

    void name(std::string name);
    void version(std::string version);
    void license(std::string license);
    void license(LicenseType type);
    void project(std::string url);
    void download(std::string url);
    void hash(std::string str);
    void hash(HashType type);
    void modified(std::string datetime);
    void primary(bool primary);
    void parent(std::string package);

    const std::string &name() const;
    const std::string &version() const;
    const std::string &license() const;
    LicenseType license_type() const;
    const std::string &project() const;
    const std::string &download() const;
    const std::string &hash() const;
    const HashType hash_type() const;
    const std::string &modified() const;
    const bool primary() const;
    const std::string &parent() const;

    operator std::string() const;

private:
    std::string _name;
    std::string _version;
    std::string _project;
    std::string _download;
    std::string _hash;
    std::string _license;
    LicenseType _license_type;
    HashType _hash_type;
    std::string _modified;
    std::string _parent;
    bool _primary;
};

std::ostream &operator<<(std::ostream &, const Package &);

class PackageList
{
public:
    using container = std::map<std::string, Package>;
    using iterator = container::iterator;
    using const_iterator = container::const_iterator;

    void add(const Package &package);
    void remove(const Package &package);
    void remove(std::string name);

    Package find(std::string name);
    const Package &find(std::string name) const;
    bool exists(std::string name) const;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

private:
    container _packages;
};

inline PackageList::iterator PackageList::begin()
{
    return _packages.begin();
}

inline PackageList::iterator PackageList::end()
{
    return _packages.end();
}

inline PackageList::const_iterator PackageList::begin() const
{
    return _packages.begin();
}

inline PackageList::const_iterator PackageList::end() const
{
    return _packages.end();
}

class PackagePath : public std::vector<std::string>
{
public:
    PackagePath();
    PackagePath(std::string path);

    void update(std::string path);
    int count(const std::string &find) const;
    bool is_primary() const;

    std::string name() const;
    std::string parent() const;

    std::string join(char separator) const;
    std::string join(std::string separator) const;
};

class PackageExplorer
{
public:
    Package discover(const std::string &path) const;

private:
    void readfile(const char *file, std::string &result) const;
};

class PackageLock
{
public:
    PackageLock();
    PackageLock(std::string path);

    void read_lockfile(std::string path);
    bool has_package(std::string name) const;
    void add_package(std::string name, std::string version, std::string resolved, std::string integrity);

    std::string resolved(std::string name) const;
    std::string integrity(std::string name) const;
    HashType hash_type(std::string name) const;

    const PackageList &get_list() const;

private:
    PackageList _list;
};

#endif // PACKAGE_HPP
