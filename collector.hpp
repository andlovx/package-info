#ifndef COLLECTOR_HPP
#define COLLECTOR_HPP

#include "package.hpp"

class Collector
{
public:
    void process();
    void process(std::string root);
    const PackageList &get_packages() const;
    void set_debug(bool enable);

private:
    PackageList _packages;
    PackageExplorer _explorer;
    bool _debug = false;
};

#endif // COLLECTOR_HPP
