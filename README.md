# NPM package info

Scan directory for package-lock.json files and collects information about used packages (including version and license).

## Requirements

This program depends on having the "npm" command globally installed. C++ compiler with build tools needs to be installed too.

## Compile

```bash
g++ -o package-info -Wall -O2 *.cpp
```

## Execute

```bash
./package-info [<root-dir>]
```

### Notice

If root directory is missing, then current working directory is scanned.

## Author

Anders Lövgren (2023-09-13)
