# OpenEarable 2 Firmware Integration

The generated C bindings are provided as a CMake library. A firmware project
must add `generated/c` explicitly and link `OpenEarable::Protocols` to the
target that uses the protocol bindings.

## Pinned west dependency

The protocol repository can be pinned in the `projects` list in
`open-earable-2/west.yml`:

```yaml
manifest:
  version: "0.10"
  projects:
    - name: open-earable-protocols
      url: https://github.com/OpenEarable/protocol.git
      revision: v0.1.0
      path: modules/lib/open-earable-protocols

    - name: sdk-nrf
      path: nrf
      url: https://github.com/nrfconnect/sdk-nrf.git
      revision: v3.0.1
      import: true
```

Use a released tag or immutable commit hash for `revision`. Then update the
workspace:

```sh
west update
```

West fetches the repository but does not add it to the build automatically.
After defining the firmware target, add the generated C library and link it:

```cmake
add_subdirectory(
  "${CMAKE_CURRENT_SOURCE_DIR}/../modules/lib/open-earable-protocols/generated/c"
  "${CMAKE_CURRENT_BINARY_DIR}/open-earable-protocols"
)
target_link_libraries(app PRIVATE OpenEarable::Protocols)
```

Adjust the repository path to match the firmware workspace. Linking the target
also exposes the generated public headers.

Firmware source files can include and use a generated protocol directly:

```c
#include <audio_response_protocol.h>

uint8_t encoded[32];
int16_t samples[] = {0, 1000, 0, -1000};
size_t encoded_size;
audio_response_transfer_chunk_t chunk = {
    .transfer_id = 1,
    .sample_offset = 0,
    .sample_count = 4,
    .samples = samples,
};

protocol_status_t status = audio_response_transfer_chunk_encode(
    &chunk,
    encoded,
    sizeof(encoded),
    &encoded_size
);
```

## Local protocol development

For local development, point the same `add_subdirectory` call at the local
protocol checkout instead of the west-managed checkout. The protocol
repository is not a Zephyr module and must not be passed through
`ZEPHYR_EXTRA_MODULES`.

Regenerate bindings in the protocol repository before rebuilding:

```sh
.venv/bin/python -m protocol_generator --language c
```
