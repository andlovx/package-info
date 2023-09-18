#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <iostream>
#include "package.hpp"

class Formatter
{
public:
    virtual ~Formatter() {}

    virtual void output(std::ostream &out, const PackageList &list) const = 0;
    virtual void output(std::ostream &out, const Package &package) const = 0;

    static const Formatter *create(std::string type);
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
