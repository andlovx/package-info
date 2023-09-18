#include "format.hpp"

namespace
{
    std::string n2("  ");
    std::string n4("    ");
    std::string n6("      ");
}

Formatter::Formatter()
{
}

Formatter::Formatter(const FormatFilter &filter)
    : _filter(filter)
{
}

void Formatter::set_filter(const FormatFilter &filter)
{
    _filter = filter;
}

Formatter *Formatter::create(std::string type)
{
    if (type == "xml")
    {
        return new XmlFormat();
    }
    else if (type == "json")
    {
        return new JsonFormat();
    }
    else if (type == "tab")
    {
        return new TabFormat();
    }
    else if (type == "csv")
    {
        return new CsvFormat();
    }
    else
    {
        throw std::invalid_argument("unknown format type " + type);
    }
}

void JsonFormat::output(std::ostream &out, const PackageList &list) const
{
    out << "{\n"
        << n2 << "\"packages\": [\n";

    for (auto package : list)
    {
        output(out, package.second);
    }
    out << n2 << "]\n"
        << "}\n";
}

void JsonFormat::output(std::ostream &out, const Package &package) const
{
    out << n4 << "{\n";

    if (_filter.name)
    {
        out << n6 << "\"name\": \"" << package.name() << "\",\n";
    }
    if (_filter.version)
    {
        out << n6 << "\"version\": \"" << package.version() << "\",\n";
    }
    if (_filter.license)
    {
        out << n6 << "\"license\": \"" << package.license() << "\",\n";
    }
    if (_filter.project)
    {
        out << n6 << "\"project\": \"" << package.project() << "\",\n";
    }
    if (_filter.download)
    {
        out << n6 << "\"download\": \"" << package.download() << "\",\n";
    }
    if (_filter.hash)
    {
        out << n6 << "\"hash\": \"" << package.hash() << "\",\n";
    }
    if (_filter.modified)
    {
        out << n6 << "\"modified\": \"" << package.modified() << "\",\n";
    }
    if (_filter.primary)
    {
        out << n6 << "\"primary\": \"" << package.primary() << "\",\n";
    }
    if (_filter.parent)
    {
        out << n6 << "\"parent\": \"" << package.parent() << "\",\n";
    }

    out << n4 << "},\n";
}

void XmlFormat::output(std::ostream &out, const PackageList &list) const
{
    out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    out << "<packages>\n";
    for (auto package : list)
    {
        output(out, package.second);
    }
    out << "</packages>\n";
}

void XmlFormat::output(std::ostream &out, const Package &package) const
{
    out << n2 << "<package>\n";

    if (_filter.name)
    {
        out << n4 << "<name>" << package.name() << "</name>\n";
    }
    if (_filter.version)
    {
        out << n4 << "<version>" << package.version() << "</version>\n";
    }
    if (_filter.license)
    {
        out << n4 << "<license>" << package.license() << "</license>\n";
    }
    if (_filter.project)
    {
        out << n4 << "<project>" << package.project() << "</project>\n";
    }
    if (_filter.download)
    {
        out << n4 << "<download>" << package.download() << "</download>\n";
    }
    if (_filter.hash)
    {
        out << n4 << "<hash>" << package.hash() << "</hash>\n";
    }
    if (_filter.modified)
    {
        out << n4 << "<modified>" << package.modified() << "</modified>\n";
    }
    if (_filter.primary)
    {
        out << n4 << "<primary>" << package.primary() << "</primary>\n";
    }
    if (_filter.parent)
    {
        out << n4 << "<parent>" << package.parent() << "</parent>\n";
    }

    out << n2 << "</package>\n";
}

void CsvFormat::output(std::ostream &out, const PackageList &list) const
{
    if (_filter.name)
    {
        out << "\"name\""
            << ",";
    }
    if (_filter.version)
    {
        out << "\"version\""
            << ",";
    }
    if (_filter.license)
    {
        out << "\"license\""
            << ",";
    }
    if (_filter.project)
    {
        out << "\"project\""
            << ",";
    }
    if (_filter.download)
    {
        out << "\"download\""
            << ",";
    }
    if (_filter.hash)
    {
        out << "\"hash\""
            << ",";
    }
    if (_filter.modified)
    {
        out << "\"modified\""
            << ",";
    }
    if (_filter.primary)
    {
        out << "\"primary\""
            << ",";
    }
    if (_filter.parent)
    {
        out << "\"parent\""
            << ",";
    }

    for (auto package : list)
    {
        output(out, package.second);
    }
}

void CsvFormat::output(std::ostream &out, const Package &package) const
{
    auto escape = [](std::string input)
    {
        std::string result = "\"";

        for (auto it = input.begin(); it != input.end(); ++it)
        {
            if (*it == '"')
            {
                result += "\"\"";
            }
            else
            {
                result += *it;
            }
        }

        result += "\"";
        return result;
    };

    if (_filter.name)
    {
        out << escape(package.name()) << ",";
    }
    if (_filter.version)
    {
        out << escape(package.version()) << ",";
    }
    if (_filter.license)
    {
        out << escape(package.license()) << ",";
    }
    if (_filter.project)
    {
        out << escape(package.project()) << ",";
    }
    if (_filter.download)
    {
        out << escape(package.download()) << ",";
    }
    if (_filter.hash)
    {
        out << escape(package.hash()) << ",";
    }
    if (_filter.modified)
    {
        out << escape(package.modified()) << ",";
    }
    if (_filter.primary)
    {
        out << package.primary() << ",";
    }
    if (_filter.parent)
    {
        out << escape(package.parent()) << ",";
    }

    out << "\n";
}

void TabFormat::output(std::ostream &out, const PackageList &list) const
{
    if (_filter.name)
    {
        out << "name\t";
    }
    if (_filter.version)
    {
        out << "version\t";
    }
    if (_filter.license)
    {
        out << "license\t";
    }
    if (_filter.project)
    {
        out << "project\t";
    }
    if (_filter.download)
    {
        out << "download\t";
    }
    if (_filter.hash)
    {
        out << "hash\t";
    }
    if (_filter.modified)
    {
        out << "modified\t";
    }
    if (_filter.primary)
    {
        out << "primary\t";
    }
    if (_filter.parent)
    {
        out << "parent\t";
    }

    for (auto package : list)
    {
        output(out, package.second);
    }
}

void TabFormat::output(std::ostream &out, const Package &package) const
{
    if (_filter.name)
    {
        out << package.name() << "\t";
    }
    if (_filter.version)
    {
        out << package.version() << "\t";
    }
    if (_filter.license)
    {
        out << package.license() << "\t";
    }
    if (_filter.project)
    {
        out << package.project() << "\t";
    }
    if (_filter.download)
    {
        out << package.download() << "\t";
    }
    if (_filter.hash)
    {
        out << package.hash() << "\t";
    }
    if (_filter.modified)
    {
        out << package.modified() << "\t";
    }
    if (_filter.primary)
    {
        out << package.primary() << "\t";
    }
    if (_filter.parent)
    {
        out << package.parent() << "\t";
    }

    out << "\n";
}
