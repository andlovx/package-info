#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <string>

struct Option
{
    Option(std::string arg);

    std::string key;
    std::string val;
};

struct Options
{
    Options();

    struct Generic
    {
        std::string root;   // The work directory
        std::string hash;   // Compute package hash
        std::string format; // Output format
        std::string output; // Output file
    } generic;

    struct Output
    {
        bool name;
        bool version;
        bool modified;
        bool url;
    } output;

    struct Runtime
    {
        bool debug;
        bool verbose;
    } runtime;
};

class Program
{
public:
    Program();
    Program(char *name);
    Program(std::string name);
    Program(int argc, char **argv);

    void parse(int argc, char **argv);
    void run();

    std::string name() const;
    std::string version() const;
    void version(std::ostream &out) const;

private:
    void usage();

    std::string _name;
    Options _options;
};

std::ostream &operator<<(std::ostream &out, const Options &options); // For debug

#endif // PROGRAM_HPP
