// Generated shared protocol runtime. Do not edit by hand.
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

/// Standard Bluetooth GATT characteristic properties.
///
/// The enum value names intentionally match Universal BLE's
/// `CharacteristicProperty` names.
enum ProtocolBleCharacteristicProperty {
  broadcast,
  read,
  writeWithoutResponse,
  write,
  notify,
  indicate,
  authenticatedSignedWrites,
  extendedProperties,
}

/// Framework-neutral BLE characteristic metadata.
class ProtocolBleCharacteristicDefinition {
  /// Creates immutable BLE characteristic metadata.
  const ProtocolBleCharacteristicDefinition({
    required this.name,
    required this.uuid,
    required this.properties,
  });

  /// Schema name of the characteristic.
  final String name;

  /// Bluetooth characteristic UUID.
  final String uuid;

  /// Standard GATT characteristic properties.
  final Set<ProtocolBleCharacteristicProperty> properties;

  /// Property names accepted by Universal BLE's
  /// `CharacteristicProperty.values.byName`.
  Set<String> get universalBlePropertyNames =>
      properties.map((property) => property.name).toSet();

  /// Whether a GATT client may read this characteristic.
  bool get isReadable =>
      properties.contains(ProtocolBleCharacteristicProperty.read);

  /// Whether a GATT client may write this characteristic.
  bool get isWritable =>
      properties.contains(ProtocolBleCharacteristicProperty.write) ||
      properties.contains(
        ProtocolBleCharacteristicProperty.writeWithoutResponse,
      ) ||
      properties.contains(
        ProtocolBleCharacteristicProperty.authenticatedSignedWrites,
      );

  /// Maps these properties to a framework enum with matching names.
  ///
  /// For Universal BLE, pass `CharacteristicProperty.values` and
  /// `(property) => property.name`.
  List<T> mapPropertiesByName<T>(
    Iterable<T> availableProperties,
    String Function(T property) nameOf,
  ) {
    final names = universalBlePropertyNames;
    return availableProperties
        .where((property) => names.contains(nameOf(property)))
        .toList();
  }
}

/// Framework-neutral BLE service metadata.
class ProtocolBleServiceDefinition {
  /// Creates immutable BLE service metadata.
  const ProtocolBleServiceDefinition({
    required this.uuid,
    required this.characteristics,
  });

  /// Bluetooth service UUID.
  final String uuid;

  /// Characteristics exposed by this service.
  final List<ProtocolBleCharacteristicDefinition> characteristics;
}

/// Writes little-endian protocol values into a byte buffer.
class ProtocolWriter {
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

  /// Writes an unsigned 64-bit integer, rejecting values outside its range.
  void uint64(BigInt value) => _integer64(value, false);

  /// Writes a signed 64-bit integer in two's-complement representation.
  void int64(BigInt value) => _integer64(value, true);

  void _integer64(BigInt value, bool signed) {
    final limit = BigInt.one << (signed ? 63 : 64);
    final minimum = signed ? -limit : BigInt.zero;
    if (value < minimum || value >= limit) {
      throw RangeError('value does not fit a 64-bit integer');
    }
    var bits = value.toUnsigned(64);
    final bytes = Uint8List(8);
    for (var index = 0; index < 8; index++) {
      bytes[index] = (bits & BigInt.from(255)).toInt();
      bits >>= 8;
    }
    _builder.add(bytes);
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

/// Reads little-endian protocol values from a byte buffer.
class ProtocolReader {
  ProtocolReader(Uint8List bytes)
      : _data = ByteData.sublistView(bytes),
        _bytes = bytes;

  final ByteData _data;
  final Uint8List _bytes;
  int _offset = 0;

  void _require(int length) {
    if (length < 0 || _offset + length > _bytes.length) {
      throw const ProtocolFormatException('unexpected end of input');
    }
  }

  /// Rejects element counts that cannot fit in the remaining input.
  void requireElements(int count, int minimumSize) {
    if (count < 0 || (minimumSize > 0 && count > (_bytes.length - _offset) ~/ minimumSize)) {
      throw const ProtocolFormatException('array exceeds remaining input');
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

  /// Reads an exact unsigned 64-bit integer on native and web targets.
  BigInt uint64() {
    _require(8);
    var value = BigInt.zero;
    for (var index = 7; index >= 0; index--) {
      value = (value << 8) | BigInt.from(_bytes[_offset + index]);
    }
    _offset += 8;
    return value;
  }

  /// Reads a signed 64-bit two's-complement integer.
  BigInt int64() => uint64().toSigned(64);

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

