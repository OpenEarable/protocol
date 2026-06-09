# OpenEarable Protocols C Library

Generated C99 binary protocol bindings for OpenEarable devices.

## CMake

Add this directory to a CMake project and link the exported target:

```cmake
add_subdirectory(path/to/protocol/generated/c open_earable_protocols)
target_link_libraries(your_target PRIVATE OpenEarable::Protocols)
```

Applications can also install the package and use:

```cmake
find_package(OpenEarableProtocols CONFIG REQUIRED)
target_link_libraries(your_target PRIVATE OpenEarable::Protocols)
```

## Make

Build the static library:

```sh
make -C path/to/protocol/generated/c
```

To compile the sources directly in another Make project:

```make
OPEN_EARABLE_PROTOCOLS_DIR := path/to/protocol/generated/c
include $(OPEN_EARABLE_PROTOCOLS_DIR)/protocol_sources.mk

CPPFLAGS += -I$(OPEN_EARABLE_PROTOCOLS_DIR)
SOURCES += $(OPEN_EARABLE_PROTOCOLS_SOURCES)
```

The generated runtime is included exactly once in both source manifests.

## Zephyr and west

This repository contains root-level Zephyr module metadata. Add the protocol
repository to the application's west manifest:

```yaml
manifest:
  projects:
    - name: open-earable-protocols
      url: https://github.com/OpenEarable/protocol.git
      revision: v0.1.0
      path: modules/lib/open-earable-protocols
```

After `west update`, Zephyr compiles the generated sources automatically.
Application source files can include protocol headers directly:

```c
#include <audio_response_protocol.h>
```
