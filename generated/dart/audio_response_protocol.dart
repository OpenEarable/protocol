// Generated from schemas/audio-response/protocol.yml. Do not edit by hand.
import 'dart:typed_data';


/// Error thrown when binary protocol data is malformed.
class ProtocolFormatException implements Exception {
  /// Creates a protocol format error with a human-readable [message].
  const ProtocolFormatException(this.message);

  /// Description of the malformed data.
  final String message;

  @override
  String toString() => 'ProtocolFormatException: $message';
}

class _Writer {
  final BytesBuilder _builder = BytesBuilder(copy: false);

  void uint8(int value) => _builder.add([value & 0xff]);

  void int8(int value) => _builder.add([value & 0xff]);

  void uint16(int value) {
    final data = ByteData(2)..setUint16(0, value, Endian.little);
    _builder.add(data.buffer.asUint8List());
  }

  void int16(int value) {
    final data = ByteData(2)..setInt16(0, value, Endian.little);
    _builder.add(data.buffer.asUint8List());
  }

  void uint32(int value) {
    final data = ByteData(4)..setUint32(0, value, Endian.little);
    _builder.add(data.buffer.asUint8List());
  }

  void int32(int value) {
    final data = ByteData(4)..setInt32(0, value, Endian.little);
    _builder.add(data.buffer.asUint8List());
  }

  void float32(double value) {
    final data = ByteData(4)..setFloat32(0, value, Endian.little);
    _builder.add(data.buffer.asUint8List());
  }

  void float64(double value) {
    final data = ByteData(8)..setFloat64(0, value, Endian.little);
    _builder.add(data.buffer.asUint8List());
  }

  void bytes(Uint8List value) => _builder.add(value);

  Uint8List takeBytes() => _builder.takeBytes();
}

class _Reader {
  _Reader(Uint8List bytes)
      : _data = ByteData.sublistView(bytes),
        _bytes = bytes;

  final ByteData _data;
  final Uint8List _bytes;
  int _offset = 0;

  void _require(int length) {
    if (_offset + length > _bytes.length) {
      throw const ProtocolFormatException('unexpected end of input');
    }
  }

  int uint8() {
    _require(1);
    return _data.getUint8(_offset++);
  }

  int int8() {
    _require(1);
    return _data.getInt8(_offset++);
  }

  int uint16() {
    _require(2);
    final value = _data.getUint16(_offset, Endian.little);
    _offset += 2;
    return value;
  }

  int int16() {
    _require(2);
    final value = _data.getInt16(_offset, Endian.little);
    _offset += 2;
    return value;
  }

  int uint32() {
    _require(4);
    final value = _data.getUint32(_offset, Endian.little);
    _offset += 4;
    return value;
  }

  int int32() {
    _require(4);
    final value = _data.getInt32(_offset, Endian.little);
    _offset += 4;
    return value;
  }

  double float32() {
    _require(4);
    final value = _data.getFloat32(_offset, Endian.little);
    _offset += 4;
    return value;
  }

  double float64() {
    _require(8);
    final value = _data.getFloat64(_offset, Endian.little);
    _offset += 8;
    return value;
  }

  Uint8List bytes(int length) {
    _require(length);
    final value = Uint8List.sublistView(_bytes, _offset, _offset + length);
    _offset += length;
    return value;
  }

  void finish() {
    if (_offset != _bytes.length) {
      throw ProtocolFormatException('trailing ${_bytes.length - _offset} byte(s)');
    }
  }
}

/// Buffer message for the audio-response protocol.
class AudioResponseBuffer {
  /// Creates a AudioResponseBuffer value.
  AudioResponseBuffer({required this.length, required this.sampling_rate, required this.buffer});

  final int length;
  final int sampling_rate;
  final Uint8List buffer;

  /// Decodes a complete AudioResponseBuffer value from [bytes].
  factory AudioResponseBuffer.fromBytes(Uint8List bytes) {
    final reader = _Reader(bytes);
    final value = AudioResponseBuffer._read(reader);
    reader.finish();
    return value;
  }

  static AudioResponseBuffer _read(_Reader reader) {
    final length = reader.uint16();
    final sampling_rate = reader.uint16();
    final buffer = reader.bytes(length);
    return AudioResponseBuffer(length: length, sampling_rate: sampling_rate, buffer: buffer);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = _Writer();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(_Writer writer) {
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
    final reader = _Reader(bytes);
    final value = AudioResponseTone._read(reader);
    reader.finish();
    return value;
  }

  static AudioResponseTone _read(_Reader reader) {
    final frequency = reader.uint16();
    final duration = reader.uint16();
    return AudioResponseTone(frequency: frequency, duration: duration);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = _Writer();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(_Writer writer) {
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
    final reader = _Reader(bytes);
    final value = AudioResponseAudioResponse._read(reader);
    reader.finish();
    return value;
  }

  static AudioResponseAudioResponse _read(_Reader reader) {
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
    final writer = _Writer();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(_Writer writer) {
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
    final reader = _Reader(bytes);
    final value = AudioResponseSound._read(reader);
    reader.finish();
    return value;
  }

  static AudioResponseSound _read(_Reader reader) {
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
    final writer = _Writer();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(_Writer writer) {
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

