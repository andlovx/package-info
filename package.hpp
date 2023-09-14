#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include <string>
#include <map>

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
    SHA512
};

class Package
{
public:
    Package();
    Package(std::string name);

    void name(std::string name);
    void version(std::string version);
    void license(std::string license);
    void license(LicenseType type);
    void url(std::string url);
    void hash(std::string str);
    void hash(HashType type);
    void modified(std::string datetime);

    const std::string &name() const;
    const std::string &version() const;
    const std::string &license() const;
    LicenseType license_type() const;
    const std::string &url() const;
    const std::string &hash() const;
    const HashType hash_type() const;
    const std::string &modified() const;

    operator std::string() const;

private:
    std::string _name;
    std::string _version;
    std::string _license;
    LicenseType _license_type;
    std::string _url;
    std::string _hash;
    HashType _hash_type;
    std::string _modified;
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

#endif // PACKAGE_HPP
