// Generated from schemas/imu/protocol.yml. Do not edit by hand.
#include "imu_protocol.h"

static protocol_status_t imu_compact_sample_write(protocol_writer_t *writer, const imu_compact_sample_t *message) {
  protocol_status_t status;
  status = protocol_write_int16(writer, message->accel_x);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_int16(writer, message->accel_y);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_int16(writer, message->accel_z);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_int16(writer, message->gyro_x);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_int16(writer, message->gyro_y);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_int16(writer, message->gyro_z);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_float(writer, message->mag_x);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_float(writer, message->mag_y);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_float(writer, message->mag_z);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t imu_compact_sample_read(protocol_reader_t *reader, imu_compact_sample_t *message) {
  protocol_status_t status;
  status = protocol_read_int16(reader, &message->accel_x);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_int16(reader, &message->accel_y);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_int16(reader, &message->accel_z);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_int16(reader, &message->gyro_x);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_int16(reader, &message->gyro_y);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_int16(reader, &message->gyro_z);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_float(reader, &message->mag_x);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_float(reader, &message->mag_y);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_float(reader, &message->mag_z);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t imu_compact_sample_encode(const imu_compact_sample_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = imu_compact_sample_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t imu_compact_sample_decode(imu_compact_sample_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = imu_compact_sample_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

