#include <iostream>
#include <fstream>
#include <libgen.h>
#include "program.hpp"
#include "collector.hpp"
#include "format.hpp"

Options::Options()
{
    generic.root = ".";
    generic.format = "json";
    generic.hash = "md5";

    output.name = true;
    output.version = true;
    output.modified = false;
    output.project = false;

    runtime.debug = false;
    runtime.verbose = false;
}

Option::Option(std::string arg)
{
    std::string::size_type pos = arg.find('=');

    if (pos != std::string::npos)
    {
        key = arg.substr(0, pos);
        val = arg.substr(pos + 1);
    }
    else
    {
        key = arg;
    }
}

Program::Program()
{
}

Program::Program(char *name)
    : _name(basename(name))
{
}

Program::Program(std::string name)
    : _name(name)
{
}

Program::Program(int argc, char **argv)
{
    parse(argc, argv);
}

void Program::parse(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
    {
        Option option(argv[i]);

        //
        // Generic options:
        //
        if (option.key == "-h" ||
            option.key == "--help")
        {
            usage();
            exit(0);
        }
        else if (option.key == "-V")
        {
            version(std::cout);
            exit(1);
        }
        else if (option.key == "-d" ||
                 option.key == "--debug")
        {
            _options.runtime.debug = true;
        }
        else if (option.key == "-v" ||
                 option.key == "--verbose")
        {
            _options.runtime.verbose = true;
        }
        else if (option.key == "--root")
        {
            _options.generic.root = option.val;
        }
        else if (option.key == "--hash")
        {
            _options.generic.hash = option.val;
        }
        else if (option.key == "--format")
        {
            _options.generic.format = option.val;
        }
        else if (option.key == "--output")
        {
            _options.generic.output = option.val;
        }
        //
        // Include options:
        //
        else if (option.key == "--name")
        {
            _options.output.name = true;
        }
        else if (option.key == "--version")
        {
            _options.output.version = true;
        }
        else if (option.key == "--modified")
        {
            _options.output.modified = true;
        }
        else if (option.key == "--project")
        {
            _options.output.project = true;
        }
        //
        // Option aliases:
        //
        else if (option.key == "--json")
        {
            _options.generic.format = "json";
        }
        else if (option.key == "--xml")
        {
            _options.generic.format = "xml";
        }
        else if (option.key == "--csv")
        {
            _options.generic.format = "csv";
        }
        else if (option.key == "--tab")
        {
            _options.generic.format = "tab";
        }
        else if (option.key == "--sha1")
        {
            _options.generic.hash = "sha1";
        }
        else if (option.key == "--sha224")
        {
            _options.generic.hash = "sha224";
        }
        else if (option.key == "--sha256")
        {
            _options.generic.hash = "sha256";
        }
        else if (option.key == "--sha384")
        {
            _options.generic.hash = "sha384";
        }
        else if (option.key == "--sha512")
        {
            _options.generic.hash = "sha512";
        }
        else
        {
            throw std::invalid_argument("option '" + option.key + "' was unexpected");
        }
    }

    if (_options.runtime.debug)
    {
        std::cout << _options << "\n";
    }
}

void Program::run()
{
    Collector collector;

    collector.set_debug(_options.runtime.debug);
    collector.process(_options.generic.root);

    auto formatter = Formatter::create(_options.generic.format);

    if (_options.generic.output.empty())
    {
        formatter->output(std::cout, collector.get_packages());
    }
    else
    {
        std::ofstream stream(_options.generic.output);
        formatter->output(stream, collector.get_packages());
    }

    delete formatter;
}

std::string Program::name() const
{
    return _name;
}

std::string Program::version() const
{
    return "1.0.0";
}

void Program::version(std::ostream &out) const
{
    out << name() << " v" << version() << std::endl;
}

void Program::usage()
{
    std::cout
        << "Collect NPM package information\n"
        << "\n"
        << "Usage: " << _name << " [--root=path] [--hash=type] [--format=type] [--output=file] [...options]\n"
        << "\n"
        << "Options:\n"
        << "  --root=path:    Process directory path.\n"
        << "  --hash=type:    Compute package hash.\n"
        << "  --format=type:  Format output as i.e. JSON.\n"
        << "  --output=file:  Write output to file.\n"
        << "  -d,--debug:     Enabled debug mode.\n"
        << "  -v,--verbose:   Be more verbose.\n"
        << "  -h,--help:      This casual help.\n"
        << "  -V:             Show program version.\n"
        << "\n"
        << "Include:\n"
        << "  --name:         Include package name in output.\n"
        << "  --version:      Include package version in output.\n"
        << "  --modified:     Include modified date in output.\n"
        << "  --project:          Include distribution URL in output.\n"
        << "\n"
        << "Aliases:\n"
        << "  --json:         Alias for format=json\n"
        << "  --sha1:         Alias for hash=sha1\n"
        << "  --sha224:       Alias for hash=sha224\n"
        << "  --sha256:       Alias for hash=sha256\n"
        << "  --sha384:       Alias for hash=sha384\n"
        << "  --sha512:       Alias for hash=sha512\n"
        << "\n"
        << "Copyright (C) 2023 Xertified AB. "
        << "Released under GNU GPL version 3 license.\n";
}

std::ostream &operator<<(std::ostream &out, const Options &options)
{
    return out
           << "Generic:\n"
           << "      Root: " << options.generic.root << "\n"
           << "      Hash: " << options.generic.hash << "\n"
           << "    Format: " << options.generic.format << "\n"
           << "    Output: " << options.generic.output << "\n"
           << "Output:\n"
           << "      Name: " << options.output.name << "\n"
           << "   Version: " << options.output.version << "\n"
           << "  Modified: " << options.output.modified << "\n"
           << "       URL: " << options.output.project << "\n"
           << "Runtime:\n"
           << "     Debug: " << options.runtime.debug << "\n"
           << "   Verbose: " << options.runtime.verbose << "\n";
}
