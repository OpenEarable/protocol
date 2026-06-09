# OpenEarable 2 Firmware Integration

The `open-earable-2` firmware is a Zephyr application managed by west. This
protocol repository contains `zephyr/module.yml`, so Zephyr can discover and
compile the generated C bindings automatically.

## Pinned west dependency

Add the protocol repository to the `projects` list in `open-earable-2/west.yml`:

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

No changes to the firmware's root `CMakeLists.txt` are required. Zephyr loads
the module, compiles all generated protocol sources, and adds the generated C
directory to the include path.

Firmware source files can include and use a generated protocol directly:

```c
#include <audio_response_protocol.h>

uint8_t encoded[32];
size_t encoded_size;
audio_response_tone_t tone = {
    .frequency = 440,
    .duration = 1000,
};

protocol_status_t status = audio_response_tone_encode(
    &tone,
    encoded,
    sizeof(encoded),
    &encoded_size
);
```

## Local protocol development

Before the protocol repository is added to the west manifest, pass it as an
extra Zephyr module when configuring the firmware:

```sh
west build open-earable-2 \
  --build-dir open-earable-2/build \
  -- \
  -DZEPHYR_EXTRA_MODULES=/absolute/path/to/protocol
```

Regenerate bindings in the protocol repository before rebuilding:

```sh
.venv/bin/python -m protocol_generator --language c
```
