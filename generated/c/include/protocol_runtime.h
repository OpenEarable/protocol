// Generated shared protocol runtime. Do not edit by hand.
#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define PROTOCOL_BLE_PROPERTY_BROADCAST 0x01u
#define PROTOCOL_BLE_PROPERTY_READ 0x02u
#define PROTOCOL_BLE_PROPERTY_WRITE_WITHOUT_RESPONSE 0x04u
#define PROTOCOL_BLE_PROPERTY_WRITE 0x08u
#define PROTOCOL_BLE_PROPERTY_NOTIFY 0x10u
#define PROTOCOL_BLE_PROPERTY_INDICATE 0x20u
#define PROTOCOL_BLE_PROPERTY_AUTHENTICATED_SIGNED_WRITES 0x40u
#define PROTOCOL_BLE_PROPERTY_EXTENDED_PROPERTIES 0x80u

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  PROTOCOL_OK = 0,
  PROTOCOL_ERROR_BUFFER_TOO_SMALL = 1,
  PROTOCOL_ERROR_INVALID_DATA = 2,
} protocol_status_t;

typedef struct {
  uint8_t *buffer;
  size_t size;
  size_t offset;
} protocol_writer_t;

typedef struct {
  const uint8_t *buffer;
  size_t size;
  size_t offset;
} protocol_reader_t;

protocol_status_t protocol_write_uint8(protocol_writer_t *writer, uint8_t value);
protocol_status_t protocol_write_uint16(protocol_writer_t *writer, uint16_t value);
protocol_status_t protocol_write_uint32(protocol_writer_t *writer, uint32_t value);
protocol_status_t protocol_write_int8(protocol_writer_t *writer, int8_t value);
protocol_status_t protocol_write_int16(protocol_writer_t *writer, int16_t value);
protocol_status_t protocol_write_int32(protocol_writer_t *writer, int32_t value);
protocol_status_t protocol_write_float(protocol_writer_t *writer, float value);
protocol_status_t protocol_write_double(protocol_writer_t *writer, double value);
protocol_status_t protocol_read_uint8(protocol_reader_t *reader, uint8_t *value);
protocol_status_t protocol_read_uint16(protocol_reader_t *reader, uint16_t *value);
protocol_status_t protocol_read_uint32(protocol_reader_t *reader, uint32_t *value);
protocol_status_t protocol_read_int8(protocol_reader_t *reader, int8_t *value);
protocol_status_t protocol_read_int16(protocol_reader_t *reader, int16_t *value);
protocol_status_t protocol_read_int32(protocol_reader_t *reader, int32_t *value);
protocol_status_t protocol_read_float(protocol_reader_t *reader, float *value);
protocol_status_t protocol_read_double(protocol_reader_t *reader, double *value);
protocol_status_t protocol_write_bytes(protocol_writer_t *writer, const uint8_t *value, size_t length);
protocol_status_t protocol_read_bytes(protocol_reader_t *reader, uint8_t *value, size_t length);

#ifdef __cplusplus
}
#endif

