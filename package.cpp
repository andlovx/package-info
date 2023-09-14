#include <sstream>
#include "package.hpp"

Package::Package()
    : _license_type(LicenseType::OTHER)
{
}

Package::Package(std::string name)
    : _name(name),
      _license_type(LicenseType::OTHER)
{
}

void Package::name(std::string name)
{
    this->_name = name;
}

void Package::version(std::string version)
{
    this->_version = version;
}

void Package::license(std::string license)
{
    this->_license = license;
}

void Package::license(LicenseType type)
{
    this->_license_type = type;
}

void Package::url(std::string url)
{
    this->_url = url;
}

void Package::hash(std::string str)
{
    this->_hash = str;
}

void Package::hash(HashType type)
{
    this->_hash_type = type;
}

void Package::modified(std::string datetime)
{
    this->_modified = datetime;
}

const std::string &Package::name() const
{
    return _name;
}

const std::string &Package::version() const
{
    return _version;
}

const std::string &Package::license() const
{
    return _license;
}

LicenseType Package::license_type() const
{
    return _license_type;
}

const std::string &Package::url() const
{
    return this->_url;
}

const std::string &Package::hash() const
{
    return this->_hash;
}

const HashType Package::hash_type() const
{
    return _hash_type;
}

const std::string &Package::modified() const
{
    return this->_modified;
}

Package::operator std::string() const
{
    std::stringstream ss;

    ss << "{ "
       << "name: \"" << _name << "\", "
       << "version: \"" << _version << "\", "
       << "license: \"" << _license << "\", "
       << "url: \"" << _url << "\" "
       << "}";

    return ss.str();
}

std::ostream &operator<<(std::ostream &out, const Package &p)
{
    return out << "{ "
               << "name: \"" << p.name() << "\", "
               << "version: \"" << p.version() << "\", "
               << "license: \"" << p.license() << "\", "
               << "url: \"" << p.url() << "\" "
               << "}";
}

void PackageList::add(const Package &package)
{
    _packages.insert(std::pair(package.name(), package));
}

void PackageList::remove(const Package &package)
{
    _packages.erase(package.name());
}

void PackageList::remove(std::string name)
{
    _packages.erase(name);
}

Package PackageList::find(std::string name)
{
    return _packages.find(name)->second;
}

const Package &PackageList::find(std::string name) const
{
    return _packages.find(name)->second;
}

bool PackageList::exists(std::string name) const
{
    return _packages.count(name) != 0;
}
