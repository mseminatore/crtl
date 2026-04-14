# Missing Commonly-Used C Runtime Functions

## stdio.h — Missing

| Function | Notes |
|----------|-------|
| `snprintf` / `vsnprintf` | length-bounded printf — safety critical |
| `scanf` / `sscanf` / `fscanf` | input parsing |
| `fseek` / `ftell` / `rewind` | file positioning |
| `fflush`           | flush stream |

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

## Entire Headers Missing

| Header | Key functions |
|--------|--------------|
| `math.h`   | `sqrt`, `pow`, `fabs`, `floor`, `ceil`, `sin`, `cos`, `log`, `exp` |
| `time.h`   | `time`, `clock`, `difftime`, `mktime`, `localtime`, `strftime` |
| `setjmp.h` | `setjmp`, `longjmp` |

---

## Out of Scope (per README)

- `locale.h` — explicitly out of scope
- Float support (`%f`, `atof`, `strtod`, `math.h`) — non-trivial, known gap
- `signal.h` — requires OS-level support
