cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(crtl VERSION 1.0)

# add the includes
include_directories(${PROJECT_SOURCE_DIR})

# add the library
add_library(crtl
  assert.c
  ctype.c
  errno.c
  math.c
  malloc/mm.c
  stdarg.c
  stdio.c
  stdlib.c
  string.c
  syscall.c
  unistd.c
)

# add the executable with test infrastructure
add_executable(crtl_test
  test_main.c
  testy/test_main.c
  test_string.c
  test_stdlib.c
  test_stdio.c
  test_ctype.c
  test_math.c
)

# Prevent GCC/Clang from substituting built-in implementations (e.g. memset,
# calloc, atexit) for our custom CRTL implementations at -O2/-O3.  Without
# this, the optimizer may assume standard-library semantics (e.g. atexit always
# returns 0) and eliminate test loops that rely on our bounded implementation.
target_compile_options(crtl PRIVATE -fno-builtin)
target_compile_options(crtl_test PRIVATE -fno-builtin)

target_link_libraries(crtl_test PRIVATE crtl)

enable_testing()
add_test(NAME crtl_tests COMMAND crtl_test)
