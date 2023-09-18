#include "format.hpp"

const Formatter *Formatter::create(std::string type)
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
    out << "{\n\"packages\":[\n";
    for (auto package : list)
    {
        output(out, package.second);
    }
    out << "]\n}\n";
}

void JsonFormat::output(std::ostream &out, const Package &package) const
{
    out
        << "{"
        << "\"name\": \"" << package.name() << "\", "
        << "\"version\": \"" << package.version() << "\", "
        << "\"license\": \"" << package.license() << "\""
        << "},\n";
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
    out
        << "<name>" << package.name() << "</name>\n"
        << "<version>" << package.version() << "</version>\n"
        << "<license>" << package.license() << "</license>\n";
}

void CsvFormat::output(std::ostream &out, const PackageList &list) const
{
    out << "\"name\",\"version\",\"license\"\n";

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

    out << escape(package.name())
        << escape(package.version())
        << escape(package.license())
        << "\n";
}

void TabFormat::output(std::ostream &out, const PackageList &list) const
{
    out << "name\tversion\tlicense\n";

    for (auto package : list)
    {
        output(out, package.second);
    }
}

void TabFormat::output(std::ostream &out, const Package &package) const
{
    out << package.name() << "\t"
        << package.version() << "\t"
        << package.license() << "\n";
}
