# OpenEarable Protocols C Library

Generated C99 binary protocol bindings for OpenEarable devices.

## CMake

Add this directory to a CMake project and link the exported target:

```cmake
add_subdirectory(path/to/protocol/generated/c open_earable_protocols)
target_link_libraries(your_target PRIVATE OpenEarable::Protocols)
```

The target requires C99, compiles every generated source under `src`, and
publishes `include` as its header search path. Consumer source files can include
protocol headers directly:

```c
#include <audio_response_protocol.h>
```

This generated package supports CMake `add_subdirectory` integration only. It
does not provide Make files, install rules, a `find_package` configuration, or
automatic Zephyr module discovery.
