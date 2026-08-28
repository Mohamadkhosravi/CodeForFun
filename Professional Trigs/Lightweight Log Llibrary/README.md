# Logger

A tiny, header-only logging macro for embedded and C/C++ projects — with optional color-coded output.

## Why

Plain `printf` debugging works, but scrolling through walls of white text to find one error is painful. This adds color by severity (info / warning / error) so the important lines stand out immediately.

## Features

- Single header, no dependencies beyond `stdio.h`
- Color output via ANSI escape codes (toggle on/off with `COLOR_LOG`)
- Logs include file, function, and line number automatically
- Fully disable all logging at compile time with `DEBUG 0` — zero runtime cost
- Easy to redirect output (e.g. swap `printf` for `Serial.printf` on embedded targets)

## Usage

```cpp
#include "Logger.h"

void motor_check_temp(int temp) {
    if (temp > 80)
        LOG_WARN("temp high: %d", temp);
    if (temp > 100)
        LOG_ERR("motor overheating!");
}
```

## Configuration

| Macro | Purpose |
|---|---|
| `DEBUG` | Set to `0` to strip all logging at compile time |
| `COLOR_LOG` | Set to `0` to disable ANSI colors (e.g. for log files) |
| `LOGER` | Change the underlying print function (`printf`, `Serial.printf`, etc.) |

## Notes

This is intentionally minimal — no timestamps, no log levels beyond info/warn/error, no output redirection to files. If you need something heavier, this probably isn't it. If you just want readable terminal output fast, it might be exactly enough.
