#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <iostream>
#include "package.hpp"
#include "program.hpp"

using FormatFilter = Options::Output;

class Formatter
{
public:
    Formatter();
    Formatter(const FormatFilter &filter);

    virtual ~Formatter() {}

    virtual void output(std::ostream &out, const PackageList &list) const = 0;
    virtual void output(std::ostream &out, const Package &package) const = 0;

    virtual void set_filter(const FormatFilter &filter);

    static Formatter *create(std::string type);

protected:
    FormatFilter _filter;
};

class JsonFormat : public Formatter
{
public:
    void output(std::ostream &out, const PackageList &list) const;
    void output(std::ostream &out, const Package &package) const;
};

class XmlFormat : public Formatter
{
public:
    void output(std::ostream &out, const PackageList &list) const;
    void output(std::ostream &out, const Package &package) const;
};

class CsvFormat : public Formatter
{
public:
    void output(std::ostream &out, const PackageList &list) const;
    void output(std::ostream &out, const Package &package) const;
};

class TabFormat : public Formatter
{
public:
    void output(std::ostream &out, const PackageList &list) const;
    void output(std::ostream &out, const Package &package) const;
};

#endif // FORMAT_HPP
