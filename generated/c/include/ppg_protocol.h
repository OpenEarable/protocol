// Generated from schemas/ppg/protocol.yml. Do not edit by hand.
#pragma once

#include "protocol_runtime.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Unchanged SD/.oe sample and BLE sample before firmware 2.3.0. Channel order is red,
 * infrared, green, ambient.
 */
typedef struct ppg_legacy_sample_t ppg_legacy_sample_t;
struct ppg_legacy_sample_t {
  uint32_t red;
  uint32_t infrared;
  uint32_t green;
  uint32_t ambient;
};


/**
 * BLE only from firmware 2.3.0. Concatenate red, infrared, green, ambient as four unsigned
 * 19-bit values, least significant bit first. The high four bits of bits_64_79 are zero.
 * See README for bit extraction and firmware selection.
 */
typedef struct ppg_compact_sample_t ppg_compact_sample_t;
struct ppg_compact_sample_t {
  uint32_t bits_0_31;
  uint32_t bits_32_63;
  uint16_t bits_64_79;
};


/**
 * Encode a binary representation of this message. Unchanged SD/.oe sample and BLE sample
 * before firmware 2.3.0. Channel order is red, infrared, green, ambient.
 */
protocol_status_t ppg_legacy_sample_encode(const ppg_legacy_sample_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Unchanged SD/.oe sample and BLE sample
 * before firmware 2.3.0. Channel order is red, infrared, green, ambient.
 */
protocol_status_t ppg_legacy_sample_decode(ppg_legacy_sample_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. BLE only from firmware 2.3.0.
 * Concatenate red, infrared, green, ambient as four unsigned 19-bit values, least
 * significant bit first. The high four bits of bits_64_79 are zero. See README for bit
 * extraction and firmware selection.
 */
protocol_status_t ppg_compact_sample_encode(const ppg_compact_sample_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. BLE only from firmware 2.3.0.
 * Concatenate red, infrared, green, ambient as four unsigned 19-bit values, least
 * significant bit first. The high four bits of bits_64_79 are zero. See README for bit
 * extraction and firmware selection.
 */
protocol_status_t ppg_compact_sample_decode(ppg_compact_sample_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

#ifdef __cplusplus
}
#endif

