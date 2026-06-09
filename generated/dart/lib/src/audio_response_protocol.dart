// Generated from schemas/audio-response/protocol.yml. Do not edit by hand.
import 'dart:typed_data';
import 'protocol_runtime.dart';

/// Buffer message for the audio-response protocol.
class AudioResponseBuffer {
  /// Creates a AudioResponseBuffer value.
  AudioResponseBuffer({required this.length, required this.sampling_rate, required this.buffer});

  final int length;
  final int sampling_rate;
  final Uint8List buffer;

  /// Decodes a complete AudioResponseBuffer value from [bytes].
  factory AudioResponseBuffer.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = AudioResponseBuffer._read(reader);
    reader.finish();
    return value;
  }

  static AudioResponseBuffer _read(ProtocolReader reader) {
    final length = reader.uint16();
    final sampling_rate = reader.uint16();
    final buffer = reader.bytes(length);
    return AudioResponseBuffer(length: length, sampling_rate: sampling_rate, buffer: buffer);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint16(length);
    writer.uint16(sampling_rate);
    if (buffer.length != length) {
      throw ProtocolFormatException('buffer length does not match length');
    }
    writer.bytes(buffer);
  }
}

/// Tone message for the audio-response protocol.
class AudioResponseTone {
  /// Creates a AudioResponseTone value.
  AudioResponseTone({required this.frequency, required this.duration});

  final int frequency;
  final int duration;

  /// Decodes a complete AudioResponseTone value from [bytes].
  factory AudioResponseTone.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = AudioResponseTone._read(reader);
    reader.finish();
    return value;
  }

  static AudioResponseTone _read(ProtocolReader reader) {
    final frequency = reader.uint16();
    final duration = reader.uint16();
    return AudioResponseTone(frequency: frequency, duration: duration);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint16(frequency);
    writer.uint16(duration);
  }
}

/// AudioResponse message for the audio-response protocol.
class AudioResponseAudioResponse {
  /// Creates a AudioResponseAudioResponse value.
  AudioResponseAudioResponse({required this.points, required this.frequencies, required this.response});

  final int points;
  final List<int> frequencies;
  final List<int> response;

  /// Decodes a complete AudioResponseAudioResponse value from [bytes].
  factory AudioResponseAudioResponse.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = AudioResponseAudioResponse._read(reader);
    reader.finish();
    return value;
  }

  static AudioResponseAudioResponse _read(ProtocolReader reader) {
    final points = reader.uint8();
    final frequencies = List<int>.generate(
      points,
      (_) => reader.uint16(),
    );
    final response = List<int>.generate(
      points,
      (_) => reader.uint16(),
    );
    return AudioResponseAudioResponse(points: points, frequencies: frequencies, response: response);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
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

/// Sound message for the audio-response protocol.
class AudioResponseSound {
  /// Creates a AudioResponseSound value.
  AudioResponseSound({required this.type, required this.data});

  final int type;
  final Object /* AudioResponseBuffer, AudioResponseTone */ data;

  /// Decodes a complete AudioResponseSound value from [bytes].
  factory AudioResponseSound.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = AudioResponseSound._read(reader);
    reader.finish();
    return value;
  }

  static AudioResponseSound _read(ProtocolReader reader) {
    final type = reader.uint8();
    final Object data;
    switch (type) {
      case 0:
        data = AudioResponseBuffer._read(reader);
        break;
      case 1:
        data = AudioResponseTone._read(reader);
        break;
      default:
        throw ProtocolFormatException('unknown union discriminator $type');
    }
    return AudioResponseSound(type: type, data: data);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(type);
    if (data is AudioResponseBuffer) {
        if (type != 0) {
          throw const ProtocolFormatException('union discriminator does not match payload type');
        }
        (data as AudioResponseBuffer)._write(writer);
        return;
    }
    if (data is AudioResponseTone) {
        if (type != 1) {
          throw const ProtocolFormatException('union discriminator does not match payload type');
        }
        (data as AudioResponseTone)._write(writer);
        return;
    }
    throw ProtocolFormatException('unsupported union payload: ${data.runtimeType}');
  }
}

