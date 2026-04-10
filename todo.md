# Missing Commonly-Used C Runtime Functions

## stdlib.h — Missing

| Function | Notes |
|----------|-------|
| `calloc`           | zero-initializing malloc — very common |
| `realloc`          | resize allocation — very common |
| `rand` / `srand`   | random numbers |
| `atol`             | string to `long` |
| `strtol` / `strtoul` | string to long with base; more robust than atoi |
| `qsort`            | general-purpose sort |
| `bsearch`          | binary search |
| `atexit`           | register exit-time callback |

---

## stdio.h — Missing

| Function | Notes |
|----------|-------|
| `snprintf` / `vsnprintf` | length-bounded printf — safety critical |
| `scanf` / `sscanf` / `fscanf` | input parsing |
| `fseek` / `ftell` / `rewind` | file positioning |
| `feof` / `ferror` / `clearerr` | stream status |
| `fflush`           | flush stream |
| `rename`           | rename file |
| `perror`           | print errno error string to stderr |

### printf format specifiers missing in vsprintf

| Specifier | Notes |
|-----------|-------|
| `%u`           | unsigned int |
| `%x` / `%X`   | hexadecimal |
| `%o`           | octal |
| `%p`           | pointer |
| `%f` / `%e` / `%g` | float (known issue) |
| width/precision | `%5d`, `%.2f`, `%-10s`, etc. |

---

## ctype.h — Missing

| Function | Notes |
|----------|-------|
| `isprint`  | printable characters |
| `isgraph`  | printable non-space |
| `ispunct`  | punctuation |
| `isxdigit` | hex digit (0–9, a–f, A–F) |
| `iscntrl`  | control characters |
| `isblank`  | C99: space or tab |

---

## Entire Headers Missing

| Header | Key functions |
|--------|--------------|
| `math.h`   | `sqrt`, `pow`, `fabs`, `floor`, `ceil`, `sin`, `cos`, `log`, `exp` |
| `time.h`   | `time`, `clock`, `difftime`, `mktime`, `localtime`, `strftime` |
| `setjmp.h` | `setjmp`, `longjmp` |
| `limits.h` | compile-time numeric limit macros (`INT_MAX`, `CHAR_MIN`, etc.) |

---

## Out of Scope (per README)

- `locale.h` — explicitly out of scope
- Float support (`%f`, `atof`, `strtod`, `math.h`) — non-trivial, known gap
- `signal.h` — requires OS-level support
