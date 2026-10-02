// Generated from schemas/audio-configuration/protocol.yml. Do not edit by hand.
import 'dart:typed_data';
import 'protocol_runtime.dart';

/// BLE UUIDs for the audio-configuration protocol.
abstract final class AudioConfigurationBleUuids {
  /// BLE service UUID.
  static const String serviceUuid = '1410df95-5f68-4ebb-a7c7-5e0fb9ae7557';

  /// BLE UUID for the audio_mode characteristic.
  static const String audioModeCharacteristicUuid = '1410df96-5f68-4ebb-a7c7-5e0fb9ae7557';

  /// BLE metadata for the audio_mode characteristic.
  static const ProtocolBleCharacteristicDefinition audioModeCharacteristic =
      ProtocolBleCharacteristicDefinition(
        name: 'audio_mode',
        uuid: audioModeCharacteristicUuid,
        properties: {
          ProtocolBleCharacteristicProperty.read,
          ProtocolBleCharacteristicProperty.write,
        },
      );

  /// BLE UUID for the microphone_selection characteristic.
  static const String microphoneSelectionCharacteristicUuid = '1410df97-5f68-4ebb-a7c7-5e0fb9ae7557';

  /// BLE metadata for the microphone_selection characteristic.
  static const ProtocolBleCharacteristicDefinition microphoneSelectionCharacteristic =
      ProtocolBleCharacteristicDefinition(
        name: 'microphone_selection',
        uuid: microphoneSelectionCharacteristicUuid,
        properties: {
          ProtocolBleCharacteristicProperty.read,
          ProtocolBleCharacteristicProperty.write,
        },
      );

  /// BLE UUID for the audio_channel characteristic.
  static const String audioChannelCharacteristicUuid = '1410df98-5f68-4ebb-a7c7-5e0fb9ae7557';

  /// BLE metadata for the audio_channel characteristic.
  static const ProtocolBleCharacteristicDefinition audioChannelCharacteristic =
      ProtocolBleCharacteristicDefinition(
        name: 'audio_channel',
        uuid: audioChannelCharacteristicUuid,
        properties: {
          ProtocolBleCharacteristicProperty.read,
        },
      );

  /// BLE UUID for the microphone_gain characteristic.
  static const String microphoneGainCharacteristicUuid = '1410df99-5f68-4ebb-a7c7-5e0fb9ae7557';

  /// BLE metadata for the microphone_gain characteristic.
  static const ProtocolBleCharacteristicDefinition microphoneGainCharacteristic =
      ProtocolBleCharacteristicDefinition(
        name: 'microphone_gain',
        uuid: microphoneGainCharacteristicUuid,
        properties: {
          ProtocolBleCharacteristicProperty.read,
          ProtocolBleCharacteristicProperty.write,
        },
      );

  /// Complete framework-neutral BLE service metadata.
  static const ProtocolBleServiceDefinition service =
      ProtocolBleServiceDefinition(
        uuid: serviceUuid,
        characteristics: [audioModeCharacteristic, microphoneSelectionCharacteristic, audioChannelCharacteristic, microphoneGainCharacteristic],
      );
}

/// Audio mode: 0 normal, 1 transparency, 2 ANC.
class AudioConfigurationAudioMode {
  /// Creates a AudioConfigurationAudioMode value.
  AudioConfigurationAudioMode({required this.mode});

  final int mode;

  /// Decodes a complete AudioConfigurationAudioMode value from [bytes].
  factory AudioConfigurationAudioMode.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = AudioConfigurationAudioMode._read(reader);
    reader.finish();
    return value;
  }

  static AudioConfigurationAudioMode _read(ProtocolReader reader) {
    final mode = reader.uint8();
    return AudioConfigurationAudioMode(mode: mode);
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

/// Encoder microphone: 0 left, 1 right.
class AudioConfigurationMicrophoneSelection {
  /// Creates a AudioConfigurationMicrophoneSelection value.
  AudioConfigurationMicrophoneSelection({required this.microphone});

  final int microphone;

  /// Decodes a complete AudioConfigurationMicrophoneSelection value from [bytes].
  factory AudioConfigurationMicrophoneSelection.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = AudioConfigurationMicrophoneSelection._read(reader);
    reader.finish();
    return value;
  }

  static AudioConfigurationMicrophoneSelection _read(ProtocolReader reader) {
    final microphone = reader.uint8();
    return AudioConfigurationMicrophoneSelection(microphone: microphone);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(microphone);
  }
}

/// Assigned audio channel.
class AudioConfigurationAudioChannel {
  /// Creates a AudioConfigurationAudioChannel value.
  AudioConfigurationAudioChannel({required this.channel});

  final int channel;

  /// Decodes a complete AudioConfigurationAudioChannel value from [bytes].
  factory AudioConfigurationAudioChannel.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = AudioConfigurationAudioChannel._read(reader);
    reader.finish();
    return value;
  }

  static AudioConfigurationAudioChannel _read(ProtocolReader reader) {
    final channel = reader.uint8();
    return AudioConfigurationAudioChannel(channel: channel);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(channel);
  }
}

/// Raw DMIC gain registers in outer then inner microphone order.
class AudioConfigurationMicrophoneGain {
  /// Creates a AudioConfigurationMicrophoneGain value.
  AudioConfigurationMicrophoneGain({required this.outer, required this.inner});

  final int outer;
  final int inner;

  /// Decodes a complete AudioConfigurationMicrophoneGain value from [bytes].
  factory AudioConfigurationMicrophoneGain.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = AudioConfigurationMicrophoneGain._read(reader);
    reader.finish();
    return value;
  }

  static AudioConfigurationMicrophoneGain _read(ProtocolReader reader) {
    final outer = reader.uint8();
    final inner = reader.uint8();
    return AudioConfigurationMicrophoneGain(outer: outer, inner: inner);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(outer);
    writer.uint8(inner);
  }
}

