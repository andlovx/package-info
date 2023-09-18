#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <nlohmann/json.hpp>
#include "package.hpp"

using json = nlohmann::json;

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

void Package::parent(std::string package)
{
    _parent = package;
}

void Package::primary(bool primary)
{
    _primary = primary;
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

const bool Package::primary() const
{
    return _primary;
}

const std::string &Package::parent() const
{
    return _parent;
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

PackagePath::PackagePath()
{
}

PackagePath::PackagePath(std::string path)
{
    update(path);
}

void PackagePath::update(std::string path)
{
    std::istringstream ss(path);
    clear();

    for (std::string part; std::getline(ss, part, '/');)
    {
        if (!part.empty())
        {
            push_back(part);
        }
    }
}

int PackagePath::count(const std::string &find) const
{
    return std::count_if(begin(), end(), [&find](const std::string &part)
                         { return find == part; });
}

bool PackagePath::is_primary() const
{
    return count("node_modules") == 1;
}

std::string PackagePath::parent() const
{
    for (auto it = begin(); it != end(); ++it)
    {
        if (*it == "node_modules")
        {
            return *++it;
        }
    }

    return "";
}

Package PackageExplorer::discover(const std::string &path) const
{
    PackagePath pp(path);
    Package package;
    std::string content;

    readfile(path.c_str(), content);
    auto data = json::parse(content);

    if (data.contains("name") && data["name"].is_string())
    {
        package.name(std::string(data["name"]));
    }

    if (data.contains("version") && data["version"].is_string())
    {
        package.version(std::string(data["version"]));
    }

    if (data.contains("license") && data["license"].is_string())
    {
        package.license(std::string(data["license"]));
    }

    if (data.contains("licenses") && data["licenses"].is_array())
    {
        package.license(std::string(data["licenses"][0]["type"]));
    }

    if (data.contains("licenses") && data["licenses"].is_object())
    {
        package.license(std::string(data["licenses"]["type"]));
    }

    if (!pp.is_primary())
    {
        package.parent(pp.parent());
    }

    if (data.contains("homepage") && data["homepage"].is_string())
    {
        package.url(data["homepage"]);
    }
    if (data.contains("repository") && data["repository"].is_string())
    {
        package.url(data["repository"]);
    }

    return package;
}

void PackageExplorer::readfile(const char *file, std::string &result) const
{
    std::ifstream input(file);
    result = "";

    for (std::string line; std::getline(input, line);)
    {
        result += line;
    }
}
