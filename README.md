# CRTL

Welcome to CRTL! This project attempts to provide a basic and portable 
implementation of an ANSI C runtime library. It is not the intention of
this projectto provide 100% of the ANSCI C RTL. The primary support will
be the most commonly used C library functions. For example, C locale support
is not planned at this time.

# Platform and Architectures supported

The CRTL project development and testing is mainly done on Windows and 
Mac OSX. Linux support is an additional goal. The primary architectures 
supported are x86, x64, and ARM64.

# Testing

A very simple test harness and a range of unit tests are included with the 
library. This enables quick validation of implementation across various 
platforms. Unit test coverage is growing but not yet complete.

# Why CRTL?

This is primarily an educational exercise. I find that you really come to
understand the C programming language and its library functions in a deep
and meaningful way when you've actually done the work to implement a core 
library of functions.

At some point I also hope to be able to use this library with tiny C 
compilers that I write for microcontrollers that I use.
