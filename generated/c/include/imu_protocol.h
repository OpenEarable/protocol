// Generated from schemas/imu/protocol.yml. Do not edit by hand.
#pragma once

#include "protocol_runtime.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * BLE only from firmware 2.3.0; six signed raw motion readings followed by three unchanged
 * compensated magnetometer floats. See README for exact scales and firmware selection.
 */
typedef struct imu_compact_sample_t imu_compact_sample_t;
struct imu_compact_sample_t {
  int16_t accel_x;
  int16_t accel_y;
  int16_t accel_z;
  int16_t gyro_x;
  int16_t gyro_y;
  int16_t gyro_z;
  float mag_x;
  float mag_y;
  float mag_z;
};


/**
 * Encode a binary representation of this message. BLE only from firmware 2.3.0; six signed
 * raw motion readings followed by three unchanged compensated magnetometer floats. See
 * README for exact scales and firmware selection.
 */
protocol_status_t imu_compact_sample_encode(const imu_compact_sample_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. BLE only from firmware 2.3.0; six
 * signed raw motion readings followed by three unchanged compensated magnetometer floats.
 * See README for exact scales and firmware selection.
 */
protocol_status_t imu_compact_sample_decode(imu_compact_sample_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

#ifdef __cplusplus
}
#endif

