// Generated from schemas/led/protocol.yml. Do not edit by hand.
import 'dart:typed_data';
import 'protocol_runtime.dart';

/// BLE UUIDs for the led protocol.
abstract final class LedBleUuids {
  /// BLE service UUID.
  static const String serviceUuid = '81040a2e-4819-11ee-be56-0242ac120002';

  /// BLE UUID for the rgb characteristic.
  static const String rgbCharacteristicUuid = '81040e7a-4819-11ee-be56-0242ac120002';

  /// BLE metadata for the rgb characteristic.
  static const ProtocolBleCharacteristicDefinition rgbCharacteristic =
      ProtocolBleCharacteristicDefinition(
        name: 'rgb',
        uuid: rgbCharacteristicUuid,
        properties: {
          ProtocolBleCharacteristicProperty.read,
          ProtocolBleCharacteristicProperty.write,
          ProtocolBleCharacteristicProperty.notify,
        },
      );

  /// BLE UUID for the state characteristic.
  static const String stateCharacteristicUuid = '81040e7b-4819-11ee-be56-0242ac120002';

  /// BLE metadata for the state characteristic.
  static const ProtocolBleCharacteristicDefinition stateCharacteristic =
      ProtocolBleCharacteristicDefinition(
        name: 'state',
        uuid: stateCharacteristicUuid,
        properties: {
          ProtocolBleCharacteristicProperty.read,
          ProtocolBleCharacteristicProperty.write,
          ProtocolBleCharacteristicProperty.notify,
        },
      );

  /// Complete framework-neutral BLE service metadata.
  static const ProtocolBleServiceDefinition service =
      ProtocolBleServiceDefinition(
        uuid: serviceUuid,
        characteristics: [rgbCharacteristic, stateCharacteristic],
      );
}

/// Custom color in red, green, blue order.
class LedRgb {
  /// Creates a LedRgb value.
  LedRgb({required this.red, required this.green, required this.blue});

  final int red;
  final int green;
  final int blue;

  /// Decodes a complete LedRgb value from [bytes].
  factory LedRgb.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = LedRgb._read(reader);
    reader.finish();
    return value;
  }

  static LedRgb _read(ProtocolReader reader) {
    final red = reader.uint8();
    final green = reader.uint8();
    final blue = reader.uint8();
    return LedRgb(red: red, green: green, blue: blue);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(red);
    writer.uint8(green);
    writer.uint8(blue);
  }
}

/// Indication mode: 0 state indication, 1 custom.
class LedState {
  /// Creates a LedState value.
  LedState({required this.mode});

  final int mode;

  /// Decodes a complete LedState value from [bytes].
  factory LedState.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = LedState._read(reader);
    reader.finish();
    return value;
  }

  static LedState _read(ProtocolReader reader) {
    final mode = reader.uint8();
    return LedState(mode: mode);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(mode);
  }
}

