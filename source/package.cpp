#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <nlohmann/json.hpp>
#include "package.hpp"

using json = nlohmann::json;

Package::Package()
    : _license_type(LicenseType::OTHER), _primary(true)
{
}

Package::Package(std::string name)
    : _name(name), _license_type(LicenseType::OTHER), _primary(true)
{
}

Package::Package(std::string name, std::string version, std::string download, std::string hash)
    : _name(name), _version(version), _download(download), _hash(hash), _license_type(LicenseType::OTHER), _primary(true)
{
}

void Package::name(std::string name)
{
    _name = name;
}

void Package::version(std::string version)
{
    _version = version;
}

void Package::license(std::string license)
{
    _license = license;
}

void Package::license(LicenseType type)
{
    _license_type = type;
}

void Package::project(std::string url)
{
    _project = url;
}

void Package::download(std::string url)
{
    _download = url;
}

void Package::hash(std::string str)
{
    _hash = str;
}

void Package::hash(HashType type)
{
    _hash_type = type;
}

void Package::modified(std::string datetime)
{
    _modified = datetime;
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

const std::string &Package::project() const
{
    return _project;
}

const std::string &Package::download() const
{
    return _download;
}

const std::string &Package::hash() const
{
    return _hash;
}

const HashType Package::hash_type() const
{
    return _hash_type;
}

const std::string &Package::modified() const
{
    return _modified;
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
       << "project: \"" << _project << "\" "
       << "download: \"" << _download << "\" "
       << "hash: \"" << _hash << "\" "
       << "}";

    return ss.str();
}

std::ostream &operator<<(std::ostream &out, const Package &p)
{
    return out << "{ "
               << "name: \"" << p.name() << "\", "
               << "version: \"" << p.version() << "\", "
               << "license: \"" << p.license() << "\", "
               << "project: \"" << p.project() << "\" "
               << "download: \"" << p.download() << "\" "
               << "hash: \"" << p.hash() << "\" "
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

std::string PackagePath::name() const
{
    std::string result;

    for (auto it = rbegin(); it != rend(); ++it)
    {
        if (*it == "node_modules")
        {
            return result.substr(0, result.length() - 1);
        }

        result = *it + '/' + result;
    }

    return "";
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

std::string PackagePath::join(char separator) const
{
    return join(std::string() + separator);
}

std::string PackagePath::join(std::string separator) const
{
    std::string path;

    for (auto it = begin(); it != end(); ++it)
    {
        path += *it + separator;
    }

    return path.substr(0, path.length() - separator.length());
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
        package.primary(false);
    }

    if (data.contains("homepage") && data["homepage"].is_string())
    {
        package.project(data["homepage"]);
    }
    if (data.contains("repository") && data["repository"].is_string())
    {
        package.project(data["repository"]);
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

PackageLock::PackageLock()
{
}

PackageLock::PackageLock(std::string path)
{
    read_lockfile(path);
}

void PackageLock::read_lockfile(std::string path)
{
    std::ifstream input(path);
    std::string result;

    for (std::string line; std::getline(input, line);)
    {
        result += line;
    }

    auto data = json::parse(result);

    if (data.contains("packages"))
    {
        auto packages = data["packages"];

        for (auto it = packages.begin(); it != packages.end(); ++it)
        {
            PackagePath pp(it.key());

            if (pp.size() == 0 ||
                pp[0] == ".." ||         // Skip internal packages.
                pp[0] != "node_modules") // Is this even possible?
            {
                continue;
            }

            auto value = it.value();

            if (!value.contains("version"))
            {
                value["version"] = "";
            }
            if (!value.contains("resolved"))
            {
                value["resolved"] = "";
            }
            if (!value.contains("integrity"))
            {
                value["integrity"] = "";
            }

            add_package(pp.name(), value["version"], value["resolved"], value["integrity"]);
        }
    }
}

bool PackageLock::has_package(std::string name) const
{
    return _list.exists(name);
}

void PackageLock::add_package(std::string name, std::string version, std::string resolved, std::string integrity)
{
    _list.add(Package(name, version, resolved, integrity));
}

std::string PackageLock::resolved(std::string name) const
{
    return _list.find(name).download();
}

std::string PackageLock::integrity(std::string name) const
{
    return _list.find(name).hash();
}

HashType PackageLock::hash_type(std::string name) const
{
    std::string str = integrity(name);
    std::regex pattern("(etag|md5|sha1|sha224|sha256|sha384|sha512).*");
    std::smatch matches;

    if (str.length() == 0 || !std::regex_match(str, matches, pattern))
    {
        return HashType::MISSING;
    }

    if (matches[1] == "etag")
    {
        return HashType::ETAG;
    }
    else if (matches[1] == "md5")
    {
        return HashType::MD5;
    }
    else if (matches[1] == "sha1")
    {
        return HashType::SHA1;
    }
    else if (matches[1] == "sha224")
    {
        return HashType::SHA224;
    }
    else if (matches[1] == "sha256")
    {
        return HashType::SHA256;
    }
    else if (matches[1] == "sha384")
    {
        return HashType::SHA384;
    }
    else if (matches[1] == "sha512")
    {
        return HashType::SHA512;
    }
    else
    {
        return HashType::UNKNOWN;
    }
}

const PackageList &PackageLock::get_list() const
{
    return _list;
}
