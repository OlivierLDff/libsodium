[![Build Status](https://travis-ci.org/jedisct1/libsodium.svg?branch=master)](https://travis-ci.org/jedisct1/libsodium?branch=master)
[![Windows build status](https://ci.appveyor.com/api/projects/status/fu8s2elx25il98hj?svg=true)](https://ci.appveyor.com/project/jedisct1/libsodium)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/2397/badge.svg)](https://scan.coverity.com/projects/2397)
[![Azure build status](https://jedisct1.visualstudio.com/Libsodium/_apis/build/status/jedisct1.libsodium?branchName=stable)](https://jedisct1.visualstudio.com/Libsodium/_build/latest?definitionId=3&branchName=stable)

![libsodium](https://raw.github.com/jedisct1/libsodium/master/logo.png)
============

*Aim of this fork is to provide a CMake support for libsodium.*

Sodium is a new, easy-to-use software library for encryption,
decryption, signatures, password hashing and more.

It is a portable, cross-compilable, installable, packageable
fork of [NaCl](http://nacl.cr.yp.to/), with a compatible API, and an
extended API to improve usability even further.

Its goal is to provide all of the core operations needed to build
higher-level cryptographic tools.

Sodium supports a variety of compilers and operating systems,
including Windows (with MingW or Visual Studio, x86 and x64), iOS, Android,
as well as Javascript and Webassembly.

## CMake Configuration

In source and out of source build is supported. In source is preferred for simplicity.

```bash
# Clone the repository
git clone https://github.com/OlivierLDff/libsodium
# Enter the folder and create a build folder (build folder is added in .gitignore)
cd libsodium && mkdir build && cd build
# Run cmake
cmake ..
```

### Parameters

CMake support multiple options.

- **SODIUM_BUILD_SHARED** : "Build the library dynamically (ON/TRUE) or statically (OFF/FALSE)."
- **SODIUM_ENABLE_BLOCKING_RANDOM** : "Enable this switch only if /dev/urandom is totally broken on the target platform."
- **SODIUM_ENABLE_MINIMAL_BUILD** : "Only compile the minimum set of functions required for the high-level API."
- **SODIUM_ENABLE_TESTS** : "Enable testing."
- **SODIUM_DISABLE_ASM** : "Disable AMD64 assembly implementations."
- **SODIUM_DISABLE_PIE** : "Do not produce position independent executables."
- **SODIUM_DISABLE_SSP** : "Do not compile with -fstack-protector."

#### Windows specific option

- **SODIUM_USE_CONTROL_FLOW_GUARD** : "Enable /guard:cf for msvc"
- **SODIUM_USE_QSPECTRE** : "Enable /Qspectre options for msvc."

### Build

Depending on the generator use, you can use the generator specific command like `make` or `ninja` or `msbuild`. When building with a one release type generator you might need to add `-DCMAKE_BUILD_TYPE=Release` or `-DCMAKE_BUILD_TYPE=Debug`.

More generally you can simply use cmake build command.

```bash
## Equivalent of make all for any generator
cmake --build .
## Equivalent of make libsodium in debug mode
cmake --build . --target libsodium
## Equivalent of make libsodium in release mode
cmake --build . --target libsodium --config Release
```

The libsodium will be available in the `lib` folder

### Install

An install target is available for conveniance and will deploy libsodium on your system or any where you want.

```bash
## Specifify a custom install folder (optionnal)
cmake -DCMAKE_INSTALL_PREFIX="/path/to/my/install/dir" ..
## Equivalent of make install (Debug)
cmake --build . --target install --config Debug
## Equivalent of make install (Release)
cmake --build . --target install --config Release
```

You can choose the install directory by setting **CMAKE_INSTALL_PREFIX** when configuring the project.
By default on Unix system it is set to `/usr/local` and on Windows to `c:/Program Files/libsodium`.

In this folder you will find an include folder ready to be included by another application. This is a copy of the `include` folder of this repository.
A `lib` will be created with all the generated libraries. A `cmake` folder contain all the CMake scripts to find the package.

The installation prefix is also added to `CMAKE_SYSTEM_PREFIX_PATH` so that **find_package()**, **find_program()**, **find_library()**, **find_path()**, and **find_file()** will search the prefix for other software.

### Run Tests

To run the tests you need to compile the library as static, and set the `SODIUM_ENABLE_TEST` flag to ON. Testing is done using CTest framework.

```bash
## Enable the tests
cmake -DSODIUM_ENABLE_TESTS=ON ..
## Build all the tests and executables
cmake --build . --config Release
# Then run the tests
ctest -C Release
```

## Documentation

The documentation is available on Gitbook and built from the [libsodium-doc](https://github.com/jedisct1/libsodium-doc) repository:

* [libsodium documentation](https://download.libsodium.org/doc/) -
online, requires Javascript.
* [offline documentation](https://www.gitbook.com/book/jedisct1/libsodium/details)
in PDF format.

## Integrity Checking

The integrity checking instructions (including the signing key for libsodium)
are available in the [installation](https://download.libsodium.org/doc/installation#integrity-checking)
section of the documentation.

## Community

A mailing-list is available to discuss libsodium.

In order to join, just send a random mail to `sodium-subscribe` {at}
`pureftpd` {dot} `org`.

## Contributors

### Code Contributors

This project exists thanks to all the people who contribute. [[Contribute](CONTRIBUTING.md)].

<a href="https://github.com/jedisct1/libsodium/graphs/contributors"><img src="https://opencollective.com/libsodium/contributors.svg?width=890&button=false" /></a>

### Financial Contributors

Become a financial contributor and help us sustain our community. [[Contribute](https://opencollective.com/libsodium/contribute)]

#### Individuals

<a href="https://opencollective.com/libsodium"><img src="https://opencollective.com/libsodium/individuals.svg?width=890"></a>

#### Organizations

Support this project with your organization. Your logo will show up here with a link to your website. [[Contribute](https://opencollective.com/libsodium/contribute)]

<a href="https://opencollective.com/libsodium/organization/0/website"><img src="https://opencollective.com/libsodium/organization/0/avatar.svg"></a>



## License

[ISC license](https://en.wikipedia.org/wiki/ISC_license).
