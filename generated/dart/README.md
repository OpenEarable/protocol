# OpenEarable Protocols

Generated Dart and Flutter-compatible binary protocol bindings for OpenEarable
devices.

## Usage

Import the package library:

```dart
import 'package:open_earable_protocols/open_earable_protocols.dart';
```

Protocol classes encode values with `toBytes()` and decode complete binary
messages with their `fromBytes()` factory. Decoding malformed data throws
`ProtocolFormatException`.

```dart
final chunk = AudioResponseTransferChunk(
  transfer_id: 1,
  sample_offset: 0,
  sample_count: 4,
  samples: [0, 1000, 0, -1000],
);
final encoded = chunk.toBytes();
final decoded = AudioResponseTransferChunk.fromBytes(encoded);
```

The bindings are generated from the schemas in the
[OpenEarable protocol repository](https://github.com/OpenEarable/protocol).
Do not edit files below `lib` by hand.
