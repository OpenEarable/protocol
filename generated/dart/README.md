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
final tone = AudioResponseTone(frequency: 440, duration: 1000);
final encoded = tone.toBytes();
final decoded = AudioResponseTone.fromBytes(encoded);
```

The bindings are generated from the schemas in the
[OpenEarable protocol repository](https://github.com/OpenEarable/protocol).
Do not edit files below `lib` by hand.
