# Copilot Instructions for CRTL

CRTL is a portable, educational implementation of the ANSI C runtime library. This file helps AI assistants understand the codebase structure and conventions.

## Quick Start

### Building

**Using Make (primary method):**
```bash
make              # Build the test executable (crtl_test)
make clean        # Clean object files and executable
```

**Using CMake:**
```bash
mkdir build && cd build
cmake ..
make
```

### Running Tests

**Full test suite:**
```bash
make && ./crtl_test
```

**Individual test suites** - You can run individual test modules by editing test_main.c:
```c
void test_main(int argc, char *argv[])
{
    MODULE("String Functions");
    test_string();  // Run only string tests, comment out others
}
```

## Architecture

CRTL implements standard C library functions organized by functional area. The project structure is:

### Module Organization
Each library component has a dedicated pair of files:
- **string.h/string.c** - Memory and string operations (memcpy, strlen, strcmp, etc.)
- **stdio.h/stdio.c** - Standard input/output (printf, puts, putchar, etc.)
- **stdlib.h/stdlib.c** - General utilities (malloc, free, atoi, qsort, etc.)
- **ctype.h/ctype.c** - Character classification (isalpha, isdigit, tolower, etc.)
- **assert.h/assert.c** - Assertion checking
- **errno.h/errno.c** - Error handling
- **unistd.h/unistd.c** - POSIX API (read, write, close, etc.)
- **stdarg.h/stdarg.c** - Variable argument handling
- **syscall.c** - System call wrapper (platform-dependent)

### Test Structure
- **testy/** - Git submodule containing the testy test framework (https://github.com/mseminatore/testy)
- **test_main.c** - Central test runner that organizes and calls all test suite functions
- **test_*.c** - Test suites organized by module (test_string.c, test_stdlib.c, test_ctype.c, test_stdio.c)

Tests use the **testy framework**, which provides:
- `TEST(expression)` - Assert that expression is true (prints ✓ on pass, ❌ on fail)
- `SUITE(name)` - Print a test suite section header
- `MODULE(name)` - Group related test suites into a named module (shown in colored output)
- `COMMENT(text)` - Print descriptive comments between tests
- Color highlighting and VT100 terminal support for better output readability

## Key Conventions

### Header Guards
Use both `#pragma once` and traditional `#ifndef` guards:
```c
#pragma once
#ifndef __MODULE_H
#define __MODULE_H
// ...
#endif // #ifndef __MODULE_H
```

### File Headers
All source files include a copyright header:
```c
// Copyright 2022 Mark Seminatore. All rights reserved.
```

### Function Signatures
Follow ANSI C standard library signatures exactly. Implementations often need to handle edge cases around buffer sizes, null pointers, and empty strings.

### Static Test Functions
Group related tests into static functions called `test_*()` within test_*.c files. Use the `SUITE()` macro to denote test categories within a suite.

## Testing Approach

- Uses the **testy framework** (git submodule): a lightweight, educational test framework with colored output and terminal support
- Tests are organized into modules (String, Stdlib, Ctype, Stdio) and suites (individual function groups)
- Each module's tests exercise core functionality including edge cases (empty strings, null pointers, boundary conditions)
- Test coverage is growing but incomplete; some advanced features may lack tests
- Module-level organization with testy's `MODULE()` macro makes it easy to identify which library component is being tested

## Known Limitations & Issues

- **varargs on OSX x64** - Not yet working; affects syscall() on that platform
- **File IO** - Not yet implemented
- **syscall()** - Only partial implementations; not all system calls are wrapped
- **printf()** - Doesn't support float (%f) and some other format specifiers
- **Locale Support** - Not planned; C locale support is out of scope

See README.md for the full rationale and project goals.

## Contribution Guidelines

When adding new functions or tests:
1. Create tests in the appropriate test_*.c file (or new one if needed)
2. Implement the function in the corresponding .c file
3. Declare in the corresponding .h file
4. Ensure all new tests pass and maintain or improve code coverage
5. Update README.md if documenting new functionality or issues
6. Follow existing code style and naming conventions

Refer to CONTRIBUTING.md for detailed PR requirements.
