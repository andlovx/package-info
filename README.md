# NPM package info

Scan directory for package.json and package-lock.json files and collects information about used packages (including version and license).

## Requirements

This program depends on "npm install" being runned in the directory to be scanned. C++ compiler with build tools needs to be installed too.

## Compile

Run make or compile directly from the command line.

```bash
make
```

Edit makefile or pass environment variables for building test drivers with debug information.

```bash
make -e WITH_DEBUG=1 WITH_TEST=0
```

## Execute

```bash
./package-info [<root-dir>]
```

### Notice

If root directory is missing, then current working directory is scanned.

## Author

Anders Lövgren (2023-09-13)
