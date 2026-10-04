// Generated from schemas/ppg/protocol.yml. Do not edit by hand.
import 'dart:typed_data';
import 'protocol_runtime.dart';

/// Unchanged SD/.oe sample and BLE sample before firmware 2.3.0. Channel order is red,
/// infrared, green, ambient.
class PpgLegacySample {
  /// Creates a PpgLegacySample value.
  PpgLegacySample({required this.red, required this.infrared, required this.green, required this.ambient});

  final int red;
  final int infrared;
  final int green;
  final int ambient;

  /// Decodes a complete PpgLegacySample value from [bytes].
  factory PpgLegacySample.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = PpgLegacySample._read(reader);
    reader.finish();
    return value;
  }

  static PpgLegacySample _read(ProtocolReader reader) {
    final red = reader.uint32();
    final infrared = reader.uint32();
    final green = reader.uint32();
    final ambient = reader.uint32();
    return PpgLegacySample(red: red, infrared: infrared, green: green, ambient: ambient);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint32(red);
    writer.uint32(infrared);
    writer.uint32(green);
    writer.uint32(ambient);
  }
}

/// BLE only from firmware 2.3.0. Concatenate red, infrared, green, ambient as four unsigned
/// 19-bit values, least significant bit first. The high four bits of bits_64_79 are zero.
/// See README for bit extraction and firmware selection.
class PpgCompactSample {
  /// Creates a PpgCompactSample value.
  PpgCompactSample({required this.bits_0_31, required this.bits_32_63, required this.bits_64_79});

  final int bits_0_31;
  final int bits_32_63;
  final int bits_64_79;

  /// Decodes a complete PpgCompactSample value from [bytes].
  factory PpgCompactSample.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = PpgCompactSample._read(reader);
    reader.finish();
    return value;
  }

  static PpgCompactSample _read(ProtocolReader reader) {
    final bits_0_31 = reader.uint32();
    final bits_32_63 = reader.uint32();
    final bits_64_79 = reader.uint16();
    return PpgCompactSample(bits_0_31: bits_0_31, bits_32_63: bits_32_63, bits_64_79: bits_64_79);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint32(bits_0_31);
    writer.uint32(bits_32_63);
    writer.uint16(bits_64_79);
  }
}

