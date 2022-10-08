# CRTL

Welcome to CRTL! This project attempts to provide a basic and portable 
implementation of an ANSI C runtime library. It is not the intention of
this project to provide 100% of the ANSCI C RTL. The primary support will
be the most commonly used C library functions. For example, C locale support
is not planned at this time.

## Platform and Architectures supported

The CRTL project development and testing is mainly done on Windows and 
Mac OSX. Linux support is an additional goal. The primary architectures 
supported are x86, x64, and ARM64.

## Project Goals and Non-Goals

This project has a small set of defined goals. These are:

1. Provide implementations of the most common ANSI C runtime functions
2. Prioritize correctness and portability
3. Pursue performance where practical
4. Support Windows, MacOS and Linux

There are also some explicit non-goals for the project. These are:

1. Implement every single function
2. Guarantee optimal performance
3. Support every OS / hardware configuration

## Known Issues

There are several known/open issues at this time. Not all open issues
are listed here, these are just some key examples.

* varargs and therefore syscall() on OSX IA-64 is not yet working
* Not all syscall functions implemented
* File IO is not yet implemented
* printf() does not yet support %f

## Testing

A very simple test harness and a range of unit tests are included with the 
library. This enables quick validation of implementation across various 
platforms. Unit test coverage is growing but not yet complete.

## Why CRTL?

This is primarily an educational exercise. I find that you really come to
understand the C programming language and its library functions in a deep
and meaningful way when you've actually done the work to implement a core 
library of functions.

At some point I also hope to be able to use this library with tiny C 
compilers that I write for microcontrollers that I use.

## Contributing

Contributions are welcome, particularly bug fixes and enhancements!
Refer to our [Contribution Guidelines](https://github.com/mseminatore/crtl/blob/master/CONTRIBUTING.md) for details.

> Please note that Project owners reserve the right to accept or reject any PR
> for any reason.

## Code of Conduct

Before contributing or participating to this community please be sure to 
familiarize yourself with our project 
[CODE OF CONDUCT](https://github.com/mseminatore/crtl/blob/master/CODE_OF_CONDUCT.md). 
These guidelines are intended to govern interactions with and within the community.

# Warranty Disclaimer

You may use this library with the understanding that doing so is 
**AT YOUR OWN RISK**. No warranty, express or implied, is made with regards 
to the fitness or safety of this code for any purpose.
