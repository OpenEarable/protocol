// Generated from schemas/audio-response/protocol.yml. Do not edit by hand.
import 'dart:typed_data';
import 'protocol_runtime.dart';

/// BLE UUIDs for the audio-response protocol.
abstract final class AudioResponseBleUuids {
  /// BLE service UUID.
  static const String serviceUuid = '7467b395-9043-4453-bc5c-2d8e8b10680a';

  /// BLE UUID for the transfer_control characteristic.
  static const String transferControlCharacteristicUuid = '7467b398-9043-4453-bc5c-2d8e8b10680a';

  /// BLE metadata for the transfer_control characteristic.
  static const ProtocolBleCharacteristicDefinition transferControlCharacteristic =
      ProtocolBleCharacteristicDefinition(
        name: 'transfer_control',
        uuid: transferControlCharacteristicUuid,
        properties: {
          ProtocolBleCharacteristicProperty.write,
        },
      );

  /// BLE UUID for the transfer_data characteristic.
  static const String transferDataCharacteristicUuid = '7467b399-9043-4453-bc5c-2d8e8b10680a';

  /// BLE metadata for the transfer_data characteristic.
  static const ProtocolBleCharacteristicDefinition transferDataCharacteristic =
      ProtocolBleCharacteristicDefinition(
        name: 'transfer_data',
        uuid: transferDataCharacteristicUuid,
        properties: {
          ProtocolBleCharacteristicProperty.writeWithoutResponse,
        },
      );

  /// BLE UUID for the transfer_status characteristic.
  static const String transferStatusCharacteristicUuid = '7467b39a-9043-4453-bc5c-2d8e8b10680a';

  /// BLE metadata for the transfer_status characteristic.
  static const ProtocolBleCharacteristicDefinition transferStatusCharacteristic =
      ProtocolBleCharacteristicDefinition(
        name: 'transfer_status',
        uuid: transferStatusCharacteristicUuid,
        properties: {
          ProtocolBleCharacteristicProperty.notify,
        },
      );

  /// BLE UUID for the config characteristic.
  static const String configCharacteristicUuid = '7467b39b-9043-4453-bc5c-2d8e8b10680a';

  /// BLE metadata for the config characteristic.
  static const ProtocolBleCharacteristicDefinition configCharacteristic =
      ProtocolBleCharacteristicDefinition(
        name: 'config',
        uuid: configCharacteristicUuid,
        properties: {
          ProtocolBleCharacteristicProperty.write,
        },
      );

  /// BLE UUID for the result characteristic.
  static const String resultCharacteristicUuid = '7467b39c-9043-4453-bc5c-2d8e8b10680a';

  /// BLE metadata for the result characteristic.
  static const ProtocolBleCharacteristicDefinition resultCharacteristic =
      ProtocolBleCharacteristicDefinition(
        name: 'result',
        uuid: resultCharacteristicUuid,
        properties: {
          ProtocolBleCharacteristicProperty.notify,
        },
      );

  /// Complete framework-neutral BLE service metadata.
  static const ProtocolBleServiceDefinition service =
      ProtocolBleServiceDefinition(
        uuid: serviceUuid,
        characteristics: [transferControlCharacteristic, transferDataCharacteristic, transferStatusCharacteristic, configCharacteristic, resultCharacteristic],
      );
}

/// Starts uploading an audio sample buffer. The checksum is CRC-32/ISO-HDLC over all
/// little-endian encoded samples.
class AudioResponseTransferStart {
  /// Creates a AudioResponseTransferStart value.
  AudioResponseTransferStart({required this.transfer_id, required this.total_samples, required this.sampling_rate, required this.checksum});

  final int transfer_id;
  final int total_samples;
  final int sampling_rate;
  final int checksum;

  /// Decodes a complete AudioResponseTransferStart value from [bytes].
  factory AudioResponseTransferStart.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = AudioResponseTransferStart._read(reader);
    reader.finish();
    return value;
  }

  static AudioResponseTransferStart _read(ProtocolReader reader) {
    final transfer_id = reader.uint16();
    final total_samples = reader.uint32();
    final sampling_rate = reader.uint32();
    final checksum = reader.uint32();
    return AudioResponseTransferStart(transfer_id: transfer_id, total_samples: total_samples, sampling_rate: sampling_rate, checksum: checksum);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint16(transfer_id);
    writer.uint32(total_samples);
    writer.uint32(sampling_rate);
    writer.uint32(checksum);
  }
}

/// Validates and makes a completely uploaded audio sample buffer available.
class AudioResponseTransferCommit {
  /// Creates a AudioResponseTransferCommit value.
  AudioResponseTransferCommit({required this.transfer_id});

  final int transfer_id;

  /// Decodes a complete AudioResponseTransferCommit value from [bytes].
  factory AudioResponseTransferCommit.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = AudioResponseTransferCommit._read(reader);
    reader.finish();
    return value;
  }

  static AudioResponseTransferCommit _read(ProtocolReader reader) {
    final transfer_id = reader.uint16();
    return AudioResponseTransferCommit(transfer_id: transfer_id);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint16(transfer_id);
  }
}

/// Aborts an active audio sample buffer upload.
class AudioResponseTransferAbort {
  /// Creates a AudioResponseTransferAbort value.
  AudioResponseTransferAbort({required this.transfer_id});

  final int transfer_id;

  /// Decodes a complete AudioResponseTransferAbort value from [bytes].
  factory AudioResponseTransferAbort.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = AudioResponseTransferAbort._read(reader);
    reader.finish();
    return value;
  }

  static AudioResponseTransferAbort _read(ProtocolReader reader) {
    final transfer_id = reader.uint16();
    return AudioResponseTransferAbort(transfer_id: transfer_id);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint16(transfer_id);
  }
}

/// A tagged transfer control command. Type 0 starts, type 1 commits, and type 2 aborts a
/// transfer.
class AudioResponseTransferControl {
  /// Creates a AudioResponseTransferControl value.
  AudioResponseTransferControl({required this.type, required this.command});

  final int type;
  final Object /* AudioResponseTransferStart, AudioResponseTransferCommit, AudioResponseTransferAbort */ command;

  /// Decodes a complete AudioResponseTransferControl value from [bytes].
  factory AudioResponseTransferControl.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = AudioResponseTransferControl._read(reader);
    reader.finish();
    return value;
  }

  static AudioResponseTransferControl _read(ProtocolReader reader) {
    final type = reader.uint8();
    final Object command;
    switch (type) {
      case 0:
        command = AudioResponseTransferStart._read(reader);
        break;
      case 1:
        command = AudioResponseTransferCommit._read(reader);
        break;
      case 2:
        command = AudioResponseTransferAbort._read(reader);
        break;
      default:
        throw ProtocolFormatException('unknown union discriminator $type');
    }
    return AudioResponseTransferControl(type: type, command: command);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(type);
    if (command is AudioResponseTransferStart) {
        if (type != 0) {
          throw const ProtocolFormatException('union discriminator does not match payload type');
        }
        (command as AudioResponseTransferStart)._write(writer);
        return;
    }
    if (command is AudioResponseTransferCommit) {
        if (type != 1) {
          throw const ProtocolFormatException('union discriminator does not match payload type');
        }
        (command as AudioResponseTransferCommit)._write(writer);
        return;
    }
    if (command is AudioResponseTransferAbort) {
        if (type != 2) {
          throw const ProtocolFormatException('union discriminator does not match payload type');
        }
        (command as AudioResponseTransferAbort)._write(writer);
        return;
    }
    throw ProtocolFormatException('unsupported union payload: ${command.runtimeType}');
  }
}

/// Uploads a contiguous section of an audio sample buffer.
class AudioResponseTransferChunk {
  /// Creates a AudioResponseTransferChunk value.
  AudioResponseTransferChunk({required this.transfer_id, required this.sample_offset, required this.sample_count, required this.samples});

  final int transfer_id;
  final int sample_offset;
  final int sample_count;
  final List<int> samples;

  /// Decodes a complete AudioResponseTransferChunk value from [bytes].
  factory AudioResponseTransferChunk.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = AudioResponseTransferChunk._read(reader);
    reader.finish();
    return value;
  }

  static AudioResponseTransferChunk _read(ProtocolReader reader) {
    final transfer_id = reader.uint16();
    final sample_offset = reader.uint32();
    final sample_count = reader.uint16();
    final samples = List<int>.generate(
      sample_count,
      (_) => reader.int16(),
    );
    return AudioResponseTransferChunk(transfer_id: transfer_id, sample_offset: sample_offset, sample_count: sample_count, samples: samples);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint16(transfer_id);
    writer.uint32(sample_offset);
    writer.uint16(sample_count);
    if (samples.length != sample_count) {
      throw ProtocolFormatException('samples length does not match sample_count');
    }
    for (final value in samples) {
      writer.int16(value);
    }
  }
}

/// Reports transfer progress, available chunk credits, or an error.
class AudioResponseTransferStatus {
  /// Creates a AudioResponseTransferStatus value.
  AudioResponseTransferStatus({required this.transfer_id, required this.status, required this.next_sample_offset, required this.credits});

  final int transfer_id;
  final int status;
  final int next_sample_offset;
  final int credits;

  /// Decodes a complete AudioResponseTransferStatus value from [bytes].
  factory AudioResponseTransferStatus.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = AudioResponseTransferStatus._read(reader);
    reader.finish();
    return value;
  }

  static AudioResponseTransferStatus _read(ProtocolReader reader) {
    final transfer_id = reader.uint16();
    final status = reader.uint8();
    final next_sample_offset = reader.uint32();
    final credits = reader.uint16();
    return AudioResponseTransferStatus(transfer_id: transfer_id, status: status, next_sample_offset: next_sample_offset, credits: credits);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint16(transfer_id);
    writer.uint8(status);
    writer.uint32(next_sample_offset);
    writer.uint16(credits);
  }
}

/// Starts an audio response measurement using a committed audio sample buffer.
class AudioResponseConfig {
  /// Creates a AudioResponseConfig value.
  AudioResponseConfig({required this.id, required this.transfer_id, required this.volume});

  final int id;
  final int transfer_id;
  final double volume;

  /// Decodes a complete AudioResponseConfig value from [bytes].
  factory AudioResponseConfig.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = AudioResponseConfig._read(reader);
    reader.finish();
    return value;
  }

  static AudioResponseConfig _read(ProtocolReader reader) {
    final id = reader.uint8();
    final transfer_id = reader.uint16();
    final volume = reader.float32();
    return AudioResponseConfig(id: id, transfer_id: transfer_id, volume: volume);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(id);
    writer.uint16(transfer_id);
    writer.float32(volume);
  }
}

/// A message containing audio response data. Each point represents a frequency and its
/// corresponding response value.
class AudioResponseResult {
  /// Creates a AudioResponseResult value.
  AudioResponseResult({required this.id, required this.points, required this.frequencies, required this.response});

  final int id;
  final int points;
  final List<int> frequencies;
  final List<int> response;

  /// Decodes a complete AudioResponseResult value from [bytes].
  factory AudioResponseResult.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = AudioResponseResult._read(reader);
    reader.finish();
    return value;
  }

  static AudioResponseResult _read(ProtocolReader reader) {
    final id = reader.uint8();
    final points = reader.uint8();
    final frequencies = List<int>.generate(
      points,
      (_) => reader.uint16(),
    );
    final response = List<int>.generate(
      points,
      (_) => reader.uint16(),
    );
    return AudioResponseResult(id: id, points: points, frequencies: frequencies, response: response);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(id);
    writer.uint8(points);
    if (frequencies.length != points) {
      throw ProtocolFormatException('frequencies length does not match points');
    }
    for (final value in frequencies) {
      writer.uint16(value);
    }
    if (response.length != points) {
      throw ProtocolFormatException('response length does not match points');
    }
    for (final value in response) {
      writer.uint16(value);
    }
  }
}

