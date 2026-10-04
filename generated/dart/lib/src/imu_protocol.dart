// Generated from schemas/imu/protocol.yml. Do not edit by hand.
import 'dart:typed_data';
import 'protocol_runtime.dart';

/// BLE only from firmware 2.3.0; six signed raw motion readings followed by three unchanged
/// compensated magnetometer floats. See README for exact scales and firmware selection.
class ImuCompactSample {
  /// Creates a ImuCompactSample value.
  ImuCompactSample({required this.accel_x, required this.accel_y, required this.accel_z, required this.gyro_x, required this.gyro_y, required this.gyro_z, required this.mag_x, required this.mag_y, required this.mag_z});

  final int accel_x;
  final int accel_y;
  final int accel_z;
  final int gyro_x;
  final int gyro_y;
  final int gyro_z;
  final double mag_x;
  final double mag_y;
  final double mag_z;

  /// Decodes a complete ImuCompactSample value from [bytes].
  factory ImuCompactSample.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = ImuCompactSample._read(reader);
    reader.finish();
    return value;
  }

  static ImuCompactSample _read(ProtocolReader reader) {
    final accel_x = reader.int16();
    final accel_y = reader.int16();
    final accel_z = reader.int16();
    final gyro_x = reader.int16();
    final gyro_y = reader.int16();
    final gyro_z = reader.int16();
    final mag_x = reader.float32();
    final mag_y = reader.float32();
    final mag_z = reader.float32();
    return ImuCompactSample(accel_x: accel_x, accel_y: accel_y, accel_z: accel_z, gyro_x: gyro_x, gyro_y: gyro_y, gyro_z: gyro_z, mag_x: mag_x, mag_y: mag_y, mag_z: mag_z);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.int16(accel_x);
    writer.int16(accel_y);
    writer.int16(accel_z);
    writer.int16(gyro_x);
    writer.int16(gyro_y);
    writer.int16(gyro_z);
    writer.float32(mag_x);
    writer.float32(mag_y);
    writer.float32(mag_z);
  }
}

