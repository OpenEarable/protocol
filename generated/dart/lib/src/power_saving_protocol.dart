// Generated from schemas/power-saving/protocol.yml. Do not edit by hand.
import 'dart:typed_data';
import 'protocol_runtime.dart';

/// BLE UUIDs for the power-saving protocol.
abstract final class PowerSavingBleUuids {
  /// BLE service UUID.
  static const String serviceUuid = 'd63fd1f0-5f68-4ebb-a7c7-5e0fb9ae7557';

  /// BLE UUID for the mode characteristic.
  static const String modeCharacteristicUuid = 'd63fd1f1-5f68-4ebb-a7c7-5e0fb9ae7557';

  /// BLE metadata for the mode characteristic.
  static const ProtocolBleCharacteristicDefinition modeCharacteristic =
      ProtocolBleCharacteristicDefinition(
        name: 'mode',
        uuid: modeCharacteristicUuid,
        properties: {
          ProtocolBleCharacteristicProperty.read,
          ProtocolBleCharacteristicProperty.write,
        },
      );

  /// BLE UUID for the supported_modes characteristic.
  static const String supportedModesCharacteristicUuid = 'd63fd1f2-5f68-4ebb-a7c7-5e0fb9ae7557';

  /// BLE metadata for the supported_modes characteristic.
  static const ProtocolBleCharacteristicDefinition supportedModesCharacteristic =
      ProtocolBleCharacteristicDefinition(
        name: 'supported_modes',
        uuid: supportedModesCharacteristicUuid,
        properties: {
          ProtocolBleCharacteristicProperty.read,
        },
      );

  /// Complete framework-neutral BLE service metadata.
  static const ProtocolBleServiceDefinition service =
      ProtocolBleServiceDefinition(
        uuid: serviceUuid,
        characteristics: [modeCharacteristic, supportedModesCharacteristic],
      );
}

/// Selected automatic power-off mode identified by its supported-mode ID.
class PowerSavingMode {
  /// Creates a PowerSavingMode value.
  PowerSavingMode({required this.id});

  final int id;

  /// Decodes a complete PowerSavingMode value from [bytes].
  factory PowerSavingMode.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = PowerSavingMode._read(reader);
    reader.finish();
    return value;
  }

  static PowerSavingMode _read(ProtocolReader reader) {
    final id = reader.uint8();
    return PowerSavingMode(id: id);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(id);
  }
}

/// Supported mode ID and its display name without a terminating NUL.
class PowerSavingModeDescription {
  /// Creates a PowerSavingModeDescription value.
  PowerSavingModeDescription({required this.id, required this.name_length, required this.name});

  final int id;
  final int name_length;
  final Uint8List name;

  /// Decodes a complete PowerSavingModeDescription value from [bytes].
  factory PowerSavingModeDescription.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = PowerSavingModeDescription._read(reader);
    reader.finish();
    return value;
  }

  static PowerSavingModeDescription _read(ProtocolReader reader) {
    final id = reader.uint8();
    final name_length = reader.uint8();
    final name = reader.bytes(name_length);
    return PowerSavingModeDescription(id: id, name_length: name_length, name: name);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(id);
    writer.uint8(name_length);
    if (name.length != name_length) {
      throw ProtocolFormatException('name length does not match name_length');
    }
    writer.bytes(name);
  }
}

/// Supported automatic power-off modes in display order.
class PowerSavingSupportedModes {
  /// Creates a PowerSavingSupportedModes value.
  PowerSavingSupportedModes({required this.count, required this.modes});

  final int count;
  final List<PowerSavingModeDescription> modes;

  /// Decodes a complete PowerSavingSupportedModes value from [bytes].
  factory PowerSavingSupportedModes.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = PowerSavingSupportedModes._read(reader);
    reader.finish();
    return value;
  }

  static PowerSavingSupportedModes _read(ProtocolReader reader) {
    final count = reader.uint8();
    reader.requireElements(count, 2);
    final modes = List<PowerSavingModeDescription>.generate(
      count,
      (_) => PowerSavingModeDescription._read(reader),
    );
    return PowerSavingSupportedModes(count: count, modes: modes);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(count);
    if (modes.length != count) {
      throw ProtocolFormatException('modes length does not match count');
    }
    for (final value in modes) {
      value._write(writer);
    }
  }
}

