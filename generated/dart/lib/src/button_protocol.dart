// Generated from schemas/button/protocol.yml. Do not edit by hand.
import 'dart:typed_data';
import 'protocol_runtime.dart';

/// BLE UUIDs for the button protocol.
abstract final class ButtonBleUuids {
  /// BLE service UUID.
  static const String serviceUuid = '29c10bdc-4773-11ee-be56-0242ac120002';

  /// BLE UUID for the state characteristic.
  static const String stateCharacteristicUuid = '29c10f38-4773-11ee-be56-0242ac120002';

  /// BLE metadata for the state characteristic.
  static const ProtocolBleCharacteristicDefinition stateCharacteristic =
      ProtocolBleCharacteristicDefinition(
        name: 'state',
        uuid: stateCharacteristicUuid,
        properties: {
          ProtocolBleCharacteristicProperty.read,
          ProtocolBleCharacteristicProperty.notify,
        },
      );

  /// Complete framework-neutral BLE service metadata.
  static const ProtocolBleServiceDefinition service =
      ProtocolBleServiceDefinition(
        uuid: serviceUuid,
        characteristics: [stateCharacteristic],
      );
}

/// Button action: 0 released, 1 pressed.
class ButtonState {
  /// Creates a ButtonState value.
  ButtonState({required this.action});

  final int action;

  /// Decodes a complete ButtonState value from [bytes].
  factory ButtonState.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = ButtonState._read(reader);
    reader.finish();
    return value;
  }

  static ButtonState _read(ProtocolReader reader) {
    final action = reader.uint8();
    return ButtonState(action: action);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(action);
  }
}

