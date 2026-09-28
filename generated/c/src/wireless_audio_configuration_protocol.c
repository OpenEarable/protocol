// Generated from schemas/wireless-audio-configuration/protocol.yml. Do not edit by hand.
#include "wireless_audio_configuration_protocol.h"

static protocol_status_t wireless_audio_configuration_controller_default_acl_policy_write(protocol_writer_t *writer, const wireless_audio_configuration_controller_default_acl_policy_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->reserved);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_controller_default_acl_policy_read(protocol_reader_t *reader, wireless_audio_configuration_controller_default_acl_policy_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->reserved);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_controller_default_acl_policy_encode(const wireless_audio_configuration_controller_default_acl_policy_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_controller_default_acl_policy_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_controller_default_acl_policy_decode(wireless_audio_configuration_controller_default_acl_policy_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_controller_default_acl_policy_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_fixed_acl_policy_write(protocol_writer_t *writer, const wireless_audio_configuration_fixed_acl_policy_t *message) {
  protocol_status_t status;
  status = protocol_write_uint32(writer, message->interval_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->peripheral_latency);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->supervision_timeout_ms);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_fixed_acl_policy_read(protocol_reader_t *reader, wireless_audio_configuration_fixed_acl_policy_t *message) {
  protocol_status_t status;
  status = protocol_read_uint32(reader, &message->interval_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->peripheral_latency);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->supervision_timeout_ms);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_fixed_acl_policy_encode(const wireless_audio_configuration_fixed_acl_policy_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_fixed_acl_policy_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_fixed_acl_policy_decode(wireless_audio_configuration_fixed_acl_policy_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_fixed_acl_policy_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_preferred_range_acl_policy_write(protocol_writer_t *writer, const wireless_audio_configuration_preferred_range_acl_policy_t *message) {
  protocol_status_t status;
  status = protocol_write_uint32(writer, message->minimum_interval_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->maximum_interval_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->peripheral_latency);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->supervision_timeout_ms);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_preferred_range_acl_policy_read(protocol_reader_t *reader, wireless_audio_configuration_preferred_range_acl_policy_t *message) {
  protocol_status_t status;
  status = protocol_read_uint32(reader, &message->minimum_interval_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->maximum_interval_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->peripheral_latency);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->supervision_timeout_ms);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_preferred_range_acl_policy_encode(const wireless_audio_configuration_preferred_range_acl_policy_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_preferred_range_acl_policy_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_preferred_range_acl_policy_decode(wireless_audio_configuration_preferred_range_acl_policy_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_preferred_range_acl_policy_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_adaptive_linear_acl_policy_write(protocol_writer_t *writer, const wireless_audio_configuration_adaptive_linear_acl_policy_t *message) {
  protocol_status_t status;
  status = protocol_write_uint32(writer, message->minimum_interval_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->maximum_interval_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->underrun_increase_step_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->recovery_decrease_step_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->recovery_period_ms);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->minimum_update_period_ms);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->peripheral_latency);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->supervision_timeout_ms);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_adaptive_linear_acl_policy_read(protocol_reader_t *reader, wireless_audio_configuration_adaptive_linear_acl_policy_t *message) {
  protocol_status_t status;
  status = protocol_read_uint32(reader, &message->minimum_interval_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->maximum_interval_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->underrun_increase_step_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->recovery_decrease_step_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->recovery_period_ms);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->minimum_update_period_ms);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->peripheral_latency);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->supervision_timeout_ms);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_adaptive_linear_acl_policy_encode(const wireless_audio_configuration_adaptive_linear_acl_policy_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_adaptive_linear_acl_policy_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_adaptive_linear_acl_policy_decode(wireless_audio_configuration_adaptive_linear_acl_policy_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_adaptive_linear_acl_policy_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

void wireless_audio_configuration_acl_connection_policy_set_policy_controller_default_acl_policy(wireless_audio_configuration_acl_connection_policy_t *message, wireless_audio_configuration_controller_default_acl_policy_t command) {
  if (message == NULL) {
    return;
  }
  message->type = WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_CONTROLLER_DEFAULT_ACL_POLICY;
  message->policy.controller_default_acl_policy = command;
}

wireless_audio_configuration_acl_connection_policy_t wireless_audio_configuration_acl_connection_policy_from_controller_default_acl_policy(wireless_audio_configuration_controller_default_acl_policy_t command) {
  wireless_audio_configuration_acl_connection_policy_t message = {0};
  wireless_audio_configuration_acl_connection_policy_set_policy_controller_default_acl_policy(&message, command);
  return message;
}

void wireless_audio_configuration_acl_connection_policy_set_policy_fixed_acl_policy(wireless_audio_configuration_acl_connection_policy_t *message, wireless_audio_configuration_fixed_acl_policy_t command) {
  if (message == NULL) {
    return;
  }
  message->type = WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_FIXED_ACL_POLICY;
  message->policy.fixed_acl_policy = command;
}

wireless_audio_configuration_acl_connection_policy_t wireless_audio_configuration_acl_connection_policy_from_fixed_acl_policy(wireless_audio_configuration_fixed_acl_policy_t command) {
  wireless_audio_configuration_acl_connection_policy_t message = {0};
  wireless_audio_configuration_acl_connection_policy_set_policy_fixed_acl_policy(&message, command);
  return message;
}

void wireless_audio_configuration_acl_connection_policy_set_policy_preferred_range_acl_policy(wireless_audio_configuration_acl_connection_policy_t *message, wireless_audio_configuration_preferred_range_acl_policy_t command) {
  if (message == NULL) {
    return;
  }
  message->type = WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_PREFERRED_RANGE_ACL_POLICY;
  message->policy.preferred_range_acl_policy = command;
}

wireless_audio_configuration_acl_connection_policy_t wireless_audio_configuration_acl_connection_policy_from_preferred_range_acl_policy(wireless_audio_configuration_preferred_range_acl_policy_t command) {
  wireless_audio_configuration_acl_connection_policy_t message = {0};
  wireless_audio_configuration_acl_connection_policy_set_policy_preferred_range_acl_policy(&message, command);
  return message;
}

void wireless_audio_configuration_acl_connection_policy_set_policy_adaptive_linear_acl_policy(wireless_audio_configuration_acl_connection_policy_t *message, wireless_audio_configuration_adaptive_linear_acl_policy_t command) {
  if (message == NULL) {
    return;
  }
  message->type = WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_ADAPTIVE_LINEAR_ACL_POLICY;
  message->policy.adaptive_linear_acl_policy = command;
}

wireless_audio_configuration_acl_connection_policy_t wireless_audio_configuration_acl_connection_policy_from_adaptive_linear_acl_policy(wireless_audio_configuration_adaptive_linear_acl_policy_t command) {
  wireless_audio_configuration_acl_connection_policy_t message = {0};
  wireless_audio_configuration_acl_connection_policy_set_policy_adaptive_linear_acl_policy(&message, command);
  return message;
}

protocol_status_t wireless_audio_configuration_acl_connection_policy_dispatch(const wireless_audio_configuration_acl_connection_policy_t *message, const wireless_audio_configuration_acl_connection_policy_handler_t *handler, void *context) {
  if (message == NULL || handler == NULL) {
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  switch (message->type) {
  case WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_CONTROLLER_DEFAULT_ACL_POLICY:
    if (handler->controller_default_acl_policy == NULL) {
      return PROTOCOL_ERROR_INVALID_DATA;
    }
    return handler->controller_default_acl_policy(context, &message->policy.controller_default_acl_policy);
  case WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_FIXED_ACL_POLICY:
    if (handler->fixed_acl_policy == NULL) {
      return PROTOCOL_ERROR_INVALID_DATA;
    }
    return handler->fixed_acl_policy(context, &message->policy.fixed_acl_policy);
  case WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_PREFERRED_RANGE_ACL_POLICY:
    if (handler->preferred_range_acl_policy == NULL) {
      return PROTOCOL_ERROR_INVALID_DATA;
    }
    return handler->preferred_range_acl_policy(context, &message->policy.preferred_range_acl_policy);
  case WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_ADAPTIVE_LINEAR_ACL_POLICY:
    if (handler->adaptive_linear_acl_policy == NULL) {
      return PROTOCOL_ERROR_INVALID_DATA;
    }
    return handler->adaptive_linear_acl_policy(context, &message->policy.adaptive_linear_acl_policy);
  default:
    return PROTOCOL_ERROR_INVALID_DATA;
  }
}

static protocol_status_t wireless_audio_configuration_acl_connection_policy_write(protocol_writer_t *writer, const wireless_audio_configuration_acl_connection_policy_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->type);
  if (status != PROTOCOL_OK) return status;
  switch (message->type) {
  case WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_CONTROLLER_DEFAULT_ACL_POLICY:
    status = wireless_audio_configuration_controller_default_acl_policy_write(writer, &message->policy.controller_default_acl_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_FIXED_ACL_POLICY:
    status = wireless_audio_configuration_fixed_acl_policy_write(writer, &message->policy.fixed_acl_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_PREFERRED_RANGE_ACL_POLICY:
    status = wireless_audio_configuration_preferred_range_acl_policy_write(writer, &message->policy.preferred_range_acl_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_ADAPTIVE_LINEAR_ACL_POLICY:
    status = wireless_audio_configuration_adaptive_linear_acl_policy_write(writer, &message->policy.adaptive_linear_acl_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  default:
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_acl_connection_policy_read(protocol_reader_t *reader, wireless_audio_configuration_acl_connection_policy_t *message) {
  protocol_status_t status;
  uint8_t raw_type;
  status = protocol_read_uint8(reader, &raw_type);
  if (status != PROTOCOL_OK) return status;
  message->type = (wireless_audio_configuration_acl_connection_policy_type_t)raw_type;
  switch (message->type) {
  case WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_CONTROLLER_DEFAULT_ACL_POLICY:
    status = wireless_audio_configuration_controller_default_acl_policy_read(reader, &message->policy.controller_default_acl_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_FIXED_ACL_POLICY:
    status = wireless_audio_configuration_fixed_acl_policy_read(reader, &message->policy.fixed_acl_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_PREFERRED_RANGE_ACL_POLICY:
    status = wireless_audio_configuration_preferred_range_acl_policy_read(reader, &message->policy.preferred_range_acl_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_ADAPTIVE_LINEAR_ACL_POLICY:
    status = wireless_audio_configuration_adaptive_linear_acl_policy_read(reader, &message->policy.adaptive_linear_acl_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  default:
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_acl_connection_policy_encode(const wireless_audio_configuration_acl_connection_policy_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_acl_connection_policy_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_acl_connection_policy_decode(wireless_audio_configuration_acl_connection_policy_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_acl_connection_policy_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_automatic_acl_radio_policy_write(protocol_writer_t *writer, const wireless_audio_configuration_automatic_acl_radio_policy_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->reserved);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_automatic_acl_radio_policy_read(protocol_reader_t *reader, wireless_audio_configuration_automatic_acl_radio_policy_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->reserved);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_automatic_acl_radio_policy_encode(const wireless_audio_configuration_automatic_acl_radio_policy_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_automatic_acl_radio_policy_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_automatic_acl_radio_policy_decode(wireless_audio_configuration_automatic_acl_radio_policy_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_automatic_acl_radio_policy_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_preferred_acl_radio_policy_write(protocol_writer_t *writer, const wireless_audio_configuration_preferred_acl_radio_policy_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->transmit_phy_mask);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->receive_phy_mask);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->transmit_max_data_octets);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->transmit_max_time_us);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_preferred_acl_radio_policy_read(protocol_reader_t *reader, wireless_audio_configuration_preferred_acl_radio_policy_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->transmit_phy_mask);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->receive_phy_mask);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->transmit_max_data_octets);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->transmit_max_time_us);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_preferred_acl_radio_policy_encode(const wireless_audio_configuration_preferred_acl_radio_policy_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_preferred_acl_radio_policy_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_preferred_acl_radio_policy_decode(wireless_audio_configuration_preferred_acl_radio_policy_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_preferred_acl_radio_policy_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

void wireless_audio_configuration_acl_radio_policy_set_policy_automatic_acl_radio_policy(wireless_audio_configuration_acl_radio_policy_t *message, wireless_audio_configuration_automatic_acl_radio_policy_t command) {
  if (message == NULL) {
    return;
  }
  message->type = WIRELESS_AUDIO_CONFIGURATION_ACL_RADIO_POLICY_AUTOMATIC_ACL_RADIO_POLICY;
  message->policy.automatic_acl_radio_policy = command;
}

wireless_audio_configuration_acl_radio_policy_t wireless_audio_configuration_acl_radio_policy_from_automatic_acl_radio_policy(wireless_audio_configuration_automatic_acl_radio_policy_t command) {
  wireless_audio_configuration_acl_radio_policy_t message = {0};
  wireless_audio_configuration_acl_radio_policy_set_policy_automatic_acl_radio_policy(&message, command);
  return message;
}

void wireless_audio_configuration_acl_radio_policy_set_policy_preferred_acl_radio_policy(wireless_audio_configuration_acl_radio_policy_t *message, wireless_audio_configuration_preferred_acl_radio_policy_t command) {
  if (message == NULL) {
    return;
  }
  message->type = WIRELESS_AUDIO_CONFIGURATION_ACL_RADIO_POLICY_PREFERRED_ACL_RADIO_POLICY;
  message->policy.preferred_acl_radio_policy = command;
}

wireless_audio_configuration_acl_radio_policy_t wireless_audio_configuration_acl_radio_policy_from_preferred_acl_radio_policy(wireless_audio_configuration_preferred_acl_radio_policy_t command) {
  wireless_audio_configuration_acl_radio_policy_t message = {0};
  wireless_audio_configuration_acl_radio_policy_set_policy_preferred_acl_radio_policy(&message, command);
  return message;
}

protocol_status_t wireless_audio_configuration_acl_radio_policy_dispatch(const wireless_audio_configuration_acl_radio_policy_t *message, const wireless_audio_configuration_acl_radio_policy_handler_t *handler, void *context) {
  if (message == NULL || handler == NULL) {
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  switch (message->type) {
  case WIRELESS_AUDIO_CONFIGURATION_ACL_RADIO_POLICY_AUTOMATIC_ACL_RADIO_POLICY:
    if (handler->automatic_acl_radio_policy == NULL) {
      return PROTOCOL_ERROR_INVALID_DATA;
    }
    return handler->automatic_acl_radio_policy(context, &message->policy.automatic_acl_radio_policy);
  case WIRELESS_AUDIO_CONFIGURATION_ACL_RADIO_POLICY_PREFERRED_ACL_RADIO_POLICY:
    if (handler->preferred_acl_radio_policy == NULL) {
      return PROTOCOL_ERROR_INVALID_DATA;
    }
    return handler->preferred_acl_radio_policy(context, &message->policy.preferred_acl_radio_policy);
  default:
    return PROTOCOL_ERROR_INVALID_DATA;
  }
}

static protocol_status_t wireless_audio_configuration_acl_radio_policy_write(protocol_writer_t *writer, const wireless_audio_configuration_acl_radio_policy_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->type);
  if (status != PROTOCOL_OK) return status;
  switch (message->type) {
  case WIRELESS_AUDIO_CONFIGURATION_ACL_RADIO_POLICY_AUTOMATIC_ACL_RADIO_POLICY:
    status = wireless_audio_configuration_automatic_acl_radio_policy_write(writer, &message->policy.automatic_acl_radio_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_ACL_RADIO_POLICY_PREFERRED_ACL_RADIO_POLICY:
    status = wireless_audio_configuration_preferred_acl_radio_policy_write(writer, &message->policy.preferred_acl_radio_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  default:
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_acl_radio_policy_read(protocol_reader_t *reader, wireless_audio_configuration_acl_radio_policy_t *message) {
  protocol_status_t status;
  uint8_t raw_type;
  status = protocol_read_uint8(reader, &raw_type);
  if (status != PROTOCOL_OK) return status;
  message->type = (wireless_audio_configuration_acl_radio_policy_type_t)raw_type;
  switch (message->type) {
  case WIRELESS_AUDIO_CONFIGURATION_ACL_RADIO_POLICY_AUTOMATIC_ACL_RADIO_POLICY:
    status = wireless_audio_configuration_automatic_acl_radio_policy_read(reader, &message->policy.automatic_acl_radio_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_ACL_RADIO_POLICY_PREFERRED_ACL_RADIO_POLICY:
    status = wireless_audio_configuration_preferred_acl_radio_policy_read(reader, &message->policy.preferred_acl_radio_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  default:
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_acl_radio_policy_encode(const wireless_audio_configuration_acl_radio_policy_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_acl_radio_policy_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_acl_radio_policy_decode(wireless_audio_configuration_acl_radio_policy_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_acl_radio_policy_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_unicast_server_qos_preferences_write(protocol_writer_t *writer, const wireless_audio_configuration_unicast_server_qos_preferences_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->direction_mask);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->unframed_supported);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->preferred_phy_mask);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->preferred_retransmission_number);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->maximum_transport_latency_ms);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->minimum_presentation_delay_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->maximum_presentation_delay_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->preferred_minimum_presentation_delay_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->preferred_maximum_presentation_delay_us);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_unicast_server_qos_preferences_read(protocol_reader_t *reader, wireless_audio_configuration_unicast_server_qos_preferences_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->direction_mask);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->unframed_supported);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->preferred_phy_mask);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->preferred_retransmission_number);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->maximum_transport_latency_ms);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->minimum_presentation_delay_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->maximum_presentation_delay_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->preferred_minimum_presentation_delay_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->preferred_maximum_presentation_delay_us);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_unicast_server_qos_preferences_encode(const wireless_audio_configuration_unicast_server_qos_preferences_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_unicast_server_qos_preferences_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_unicast_server_qos_preferences_decode(wireless_audio_configuration_unicast_server_qos_preferences_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_unicast_server_qos_preferences_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_set_acl_connection_policy_write(protocol_writer_t *writer, const wireless_audio_configuration_set_acl_connection_policy_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->persist);
  if (status != PROTOCOL_OK) return status;
  status = wireless_audio_configuration_acl_connection_policy_write(writer, &message->policy);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_set_acl_connection_policy_read(protocol_reader_t *reader, wireless_audio_configuration_set_acl_connection_policy_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->persist);
  if (status != PROTOCOL_OK) return status;
  status = wireless_audio_configuration_acl_connection_policy_read(reader, &message->policy);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_set_acl_connection_policy_encode(const wireless_audio_configuration_set_acl_connection_policy_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_set_acl_connection_policy_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_set_acl_connection_policy_decode(wireless_audio_configuration_set_acl_connection_policy_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_set_acl_connection_policy_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_set_acl_radio_policy_write(protocol_writer_t *writer, const wireless_audio_configuration_set_acl_radio_policy_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->persist);
  if (status != PROTOCOL_OK) return status;
  status = wireless_audio_configuration_acl_radio_policy_write(writer, &message->policy);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_set_acl_radio_policy_read(protocol_reader_t *reader, wireless_audio_configuration_set_acl_radio_policy_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->persist);
  if (status != PROTOCOL_OK) return status;
  status = wireless_audio_configuration_acl_radio_policy_read(reader, &message->policy);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_set_acl_radio_policy_encode(const wireless_audio_configuration_set_acl_radio_policy_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_set_acl_radio_policy_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_set_acl_radio_policy_decode(wireless_audio_configuration_set_acl_radio_policy_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_set_acl_radio_policy_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_set_unicast_server_qos_preferences_write(protocol_writer_t *writer, const wireless_audio_configuration_set_unicast_server_qos_preferences_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->persist);
  if (status != PROTOCOL_OK) return status;
  status = wireless_audio_configuration_unicast_server_qos_preferences_write(writer, &message->preferences);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_set_unicast_server_qos_preferences_read(protocol_reader_t *reader, wireless_audio_configuration_set_unicast_server_qos_preferences_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->persist);
  if (status != PROTOCOL_OK) return status;
  status = wireless_audio_configuration_unicast_server_qos_preferences_read(reader, &message->preferences);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_set_unicast_server_qos_preferences_encode(const wireless_audio_configuration_set_unicast_server_qos_preferences_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_set_unicast_server_qos_preferences_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_set_unicast_server_qos_preferences_decode(wireless_audio_configuration_set_unicast_server_qos_preferences_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_set_unicast_server_qos_preferences_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_get_configuration_write(protocol_writer_t *writer, const wireless_audio_configuration_get_configuration_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->section);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_get_configuration_read(protocol_reader_t *reader, wireless_audio_configuration_get_configuration_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->section);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_get_configuration_encode(const wireless_audio_configuration_get_configuration_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_get_configuration_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_get_configuration_decode(wireless_audio_configuration_get_configuration_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_get_configuration_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_restore_defaults_write(protocol_writer_t *writer, const wireless_audio_configuration_restore_defaults_t *message) {
  protocol_status_t status;
  status = protocol_write_uint32(writer, message->section_mask);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_restore_defaults_read(protocol_reader_t *reader, wireless_audio_configuration_restore_defaults_t *message) {
  protocol_status_t status;
  status = protocol_read_uint32(reader, &message->section_mask);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_restore_defaults_encode(const wireless_audio_configuration_restore_defaults_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_restore_defaults_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_restore_defaults_decode(wireless_audio_configuration_restore_defaults_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_restore_defaults_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

void wireless_audio_configuration_configuration_command_set_operation_set_acl_connection_policy(wireless_audio_configuration_configuration_command_t *message, wireless_audio_configuration_set_acl_connection_policy_t command) {
  if (message == NULL) {
    return;
  }
  message->type = WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_SET_ACL_CONNECTION_POLICY;
  message->operation.set_acl_connection_policy = command;
}

void wireless_audio_configuration_configuration_command_set_operation_set_acl_radio_policy(wireless_audio_configuration_configuration_command_t *message, wireless_audio_configuration_set_acl_radio_policy_t command) {
  if (message == NULL) {
    return;
  }
  message->type = WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_SET_ACL_RADIO_POLICY;
  message->operation.set_acl_radio_policy = command;
}

void wireless_audio_configuration_configuration_command_set_operation_set_unicast_server_qos_preferences(wireless_audio_configuration_configuration_command_t *message, wireless_audio_configuration_set_unicast_server_qos_preferences_t command) {
  if (message == NULL) {
    return;
  }
  message->type = WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_SET_UNICAST_SERVER_QOS_PREFERENCES;
  message->operation.set_unicast_server_qos_preferences = command;
}

void wireless_audio_configuration_configuration_command_set_operation_get_configuration(wireless_audio_configuration_configuration_command_t *message, wireless_audio_configuration_get_configuration_t command) {
  if (message == NULL) {
    return;
  }
  message->type = WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_GET_CONFIGURATION;
  message->operation.get_configuration = command;
}

void wireless_audio_configuration_configuration_command_set_operation_restore_defaults(wireless_audio_configuration_configuration_command_t *message, wireless_audio_configuration_restore_defaults_t command) {
  if (message == NULL) {
    return;
  }
  message->type = WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_RESTORE_DEFAULTS;
  message->operation.restore_defaults = command;
}

protocol_status_t wireless_audio_configuration_configuration_command_dispatch(const wireless_audio_configuration_configuration_command_t *message, const wireless_audio_configuration_configuration_command_handler_t *handler, void *context) {
  if (message == NULL || handler == NULL) {
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  switch (message->type) {
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_SET_ACL_CONNECTION_POLICY:
    if (handler->set_acl_connection_policy == NULL) {
      return PROTOCOL_ERROR_INVALID_DATA;
    }
    return handler->set_acl_connection_policy(context, &message->operation.set_acl_connection_policy);
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_SET_ACL_RADIO_POLICY:
    if (handler->set_acl_radio_policy == NULL) {
      return PROTOCOL_ERROR_INVALID_DATA;
    }
    return handler->set_acl_radio_policy(context, &message->operation.set_acl_radio_policy);
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_SET_UNICAST_SERVER_QOS_PREFERENCES:
    if (handler->set_unicast_server_qos_preferences == NULL) {
      return PROTOCOL_ERROR_INVALID_DATA;
    }
    return handler->set_unicast_server_qos_preferences(context, &message->operation.set_unicast_server_qos_preferences);
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_GET_CONFIGURATION:
    if (handler->get_configuration == NULL) {
      return PROTOCOL_ERROR_INVALID_DATA;
    }
    return handler->get_configuration(context, &message->operation.get_configuration);
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_RESTORE_DEFAULTS:
    if (handler->restore_defaults == NULL) {
      return PROTOCOL_ERROR_INVALID_DATA;
    }
    return handler->restore_defaults(context, &message->operation.restore_defaults);
  default:
    return PROTOCOL_ERROR_INVALID_DATA;
  }
}

static protocol_status_t wireless_audio_configuration_configuration_command_write(protocol_writer_t *writer, const wireless_audio_configuration_configuration_command_t *message) {
  protocol_status_t status;
  status = protocol_write_uint16(writer, message->request_id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->type);
  if (status != PROTOCOL_OK) return status;
  switch (message->type) {
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_SET_ACL_CONNECTION_POLICY:
    status = wireless_audio_configuration_set_acl_connection_policy_write(writer, &message->operation.set_acl_connection_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_SET_ACL_RADIO_POLICY:
    status = wireless_audio_configuration_set_acl_radio_policy_write(writer, &message->operation.set_acl_radio_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_SET_UNICAST_SERVER_QOS_PREFERENCES:
    status = wireless_audio_configuration_set_unicast_server_qos_preferences_write(writer, &message->operation.set_unicast_server_qos_preferences);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_GET_CONFIGURATION:
    status = wireless_audio_configuration_get_configuration_write(writer, &message->operation.get_configuration);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_RESTORE_DEFAULTS:
    status = wireless_audio_configuration_restore_defaults_write(writer, &message->operation.restore_defaults);
    if (status != PROTOCOL_OK) return status;
    break;
  default:
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_configuration_command_read(protocol_reader_t *reader, wireless_audio_configuration_configuration_command_t *message) {
  protocol_status_t status;
  status = protocol_read_uint16(reader, &message->request_id);
  if (status != PROTOCOL_OK) return status;
  uint8_t raw_type;
  status = protocol_read_uint8(reader, &raw_type);
  if (status != PROTOCOL_OK) return status;
  message->type = (wireless_audio_configuration_configuration_command_type_t)raw_type;
  switch (message->type) {
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_SET_ACL_CONNECTION_POLICY:
    status = wireless_audio_configuration_set_acl_connection_policy_read(reader, &message->operation.set_acl_connection_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_SET_ACL_RADIO_POLICY:
    status = wireless_audio_configuration_set_acl_radio_policy_read(reader, &message->operation.set_acl_radio_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_SET_UNICAST_SERVER_QOS_PREFERENCES:
    status = wireless_audio_configuration_set_unicast_server_qos_preferences_read(reader, &message->operation.set_unicast_server_qos_preferences);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_GET_CONFIGURATION:
    status = wireless_audio_configuration_get_configuration_read(reader, &message->operation.get_configuration);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_RESTORE_DEFAULTS:
    status = wireless_audio_configuration_restore_defaults_read(reader, &message->operation.restore_defaults);
    if (status != PROTOCOL_OK) return status;
    break;
  default:
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_configuration_command_encode(const wireless_audio_configuration_configuration_command_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_configuration_command_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_configuration_command_decode(wireless_audio_configuration_configuration_command_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_configuration_command_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_configured_acl_connection_policy_write(protocol_writer_t *writer, const wireless_audio_configuration_configured_acl_connection_policy_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->persisted);
  if (status != PROTOCOL_OK) return status;
  status = wireless_audio_configuration_acl_connection_policy_write(writer, &message->policy);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_configured_acl_connection_policy_read(protocol_reader_t *reader, wireless_audio_configuration_configured_acl_connection_policy_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->persisted);
  if (status != PROTOCOL_OK) return status;
  status = wireless_audio_configuration_acl_connection_policy_read(reader, &message->policy);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_configured_acl_connection_policy_encode(const wireless_audio_configuration_configured_acl_connection_policy_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_configured_acl_connection_policy_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_configured_acl_connection_policy_decode(wireless_audio_configuration_configured_acl_connection_policy_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_configured_acl_connection_policy_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_configured_acl_radio_policy_write(protocol_writer_t *writer, const wireless_audio_configuration_configured_acl_radio_policy_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->persisted);
  if (status != PROTOCOL_OK) return status;
  status = wireless_audio_configuration_acl_radio_policy_write(writer, &message->policy);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_configured_acl_radio_policy_read(protocol_reader_t *reader, wireless_audio_configuration_configured_acl_radio_policy_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->persisted);
  if (status != PROTOCOL_OK) return status;
  status = wireless_audio_configuration_acl_radio_policy_read(reader, &message->policy);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_configured_acl_radio_policy_encode(const wireless_audio_configuration_configured_acl_radio_policy_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_configured_acl_radio_policy_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_configured_acl_radio_policy_decode(wireless_audio_configuration_configured_acl_radio_policy_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_configured_acl_radio_policy_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_configured_unicast_server_qos_preferences_write(protocol_writer_t *writer, const wireless_audio_configuration_configured_unicast_server_qos_preferences_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->persisted);
  if (status != PROTOCOL_OK) return status;
  status = wireless_audio_configuration_unicast_server_qos_preferences_write(writer, &message->preferences);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_configured_unicast_server_qos_preferences_read(protocol_reader_t *reader, wireless_audio_configuration_configured_unicast_server_qos_preferences_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->persisted);
  if (status != PROTOCOL_OK) return status;
  status = wireless_audio_configuration_unicast_server_qos_preferences_read(reader, &message->preferences);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_configured_unicast_server_qos_preferences_encode(const wireless_audio_configuration_configured_unicast_server_qos_preferences_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_configured_unicast_server_qos_preferences_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_configured_unicast_server_qos_preferences_decode(wireless_audio_configuration_configured_unicast_server_qos_preferences_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_configured_unicast_server_qos_preferences_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_command_result_write(protocol_writer_t *writer, const wireless_audio_configuration_command_result_t *message) {
  protocol_status_t status;
  status = protocol_write_uint8(writer, message->status);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->error_domain);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_int32(writer, message->error_code);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->restart_required_mask);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_command_result_read(protocol_reader_t *reader, wireless_audio_configuration_command_result_t *message) {
  protocol_status_t status;
  status = protocol_read_uint8(reader, &message->status);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->error_domain);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_int32(reader, &message->error_code);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->restart_required_mask);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_command_result_encode(const wireless_audio_configuration_command_result_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_command_result_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_command_result_decode(wireless_audio_configuration_command_result_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_command_result_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

void wireless_audio_configuration_configuration_response_set_payload_command_result(wireless_audio_configuration_configuration_response_t *message, wireless_audio_configuration_command_result_t command) {
  if (message == NULL) {
    return;
  }
  message->type = WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_COMMAND_RESULT;
  message->payload.command_result = command;
}

void wireless_audio_configuration_configuration_response_set_payload_configured_acl_connection_policy(wireless_audio_configuration_configuration_response_t *message, wireless_audio_configuration_configured_acl_connection_policy_t command) {
  if (message == NULL) {
    return;
  }
  message->type = WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_CONFIGURED_ACL_CONNECTION_POLICY;
  message->payload.configured_acl_connection_policy = command;
}

void wireless_audio_configuration_configuration_response_set_payload_configured_acl_radio_policy(wireless_audio_configuration_configuration_response_t *message, wireless_audio_configuration_configured_acl_radio_policy_t command) {
  if (message == NULL) {
    return;
  }
  message->type = WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_CONFIGURED_ACL_RADIO_POLICY;
  message->payload.configured_acl_radio_policy = command;
}

void wireless_audio_configuration_configuration_response_set_payload_configured_unicast_server_qos_preferences(wireless_audio_configuration_configuration_response_t *message, wireless_audio_configuration_configured_unicast_server_qos_preferences_t command) {
  if (message == NULL) {
    return;
  }
  message->type = WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_CONFIGURED_UNICAST_SERVER_QOS_PREFERENCES;
  message->payload.configured_unicast_server_qos_preferences = command;
}

protocol_status_t wireless_audio_configuration_configuration_response_dispatch(const wireless_audio_configuration_configuration_response_t *message, const wireless_audio_configuration_configuration_response_handler_t *handler, void *context) {
  if (message == NULL || handler == NULL) {
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  switch (message->type) {
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_COMMAND_RESULT:
    if (handler->command_result == NULL) {
      return PROTOCOL_ERROR_INVALID_DATA;
    }
    return handler->command_result(context, &message->payload.command_result);
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_CONFIGURED_ACL_CONNECTION_POLICY:
    if (handler->configured_acl_connection_policy == NULL) {
      return PROTOCOL_ERROR_INVALID_DATA;
    }
    return handler->configured_acl_connection_policy(context, &message->payload.configured_acl_connection_policy);
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_CONFIGURED_ACL_RADIO_POLICY:
    if (handler->configured_acl_radio_policy == NULL) {
      return PROTOCOL_ERROR_INVALID_DATA;
    }
    return handler->configured_acl_radio_policy(context, &message->payload.configured_acl_radio_policy);
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_CONFIGURED_UNICAST_SERVER_QOS_PREFERENCES:
    if (handler->configured_unicast_server_qos_preferences == NULL) {
      return PROTOCOL_ERROR_INVALID_DATA;
    }
    return handler->configured_unicast_server_qos_preferences(context, &message->payload.configured_unicast_server_qos_preferences);
  default:
    return PROTOCOL_ERROR_INVALID_DATA;
  }
}

static protocol_status_t wireless_audio_configuration_configuration_response_write(protocol_writer_t *writer, const wireless_audio_configuration_configuration_response_t *message) {
  protocol_status_t status;
  status = protocol_write_uint16(writer, message->request_id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->type);
  if (status != PROTOCOL_OK) return status;
  switch (message->type) {
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_COMMAND_RESULT:
    status = wireless_audio_configuration_command_result_write(writer, &message->payload.command_result);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_CONFIGURED_ACL_CONNECTION_POLICY:
    status = wireless_audio_configuration_configured_acl_connection_policy_write(writer, &message->payload.configured_acl_connection_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_CONFIGURED_ACL_RADIO_POLICY:
    status = wireless_audio_configuration_configured_acl_radio_policy_write(writer, &message->payload.configured_acl_radio_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_CONFIGURED_UNICAST_SERVER_QOS_PREFERENCES:
    status = wireless_audio_configuration_configured_unicast_server_qos_preferences_write(writer, &message->payload.configured_unicast_server_qos_preferences);
    if (status != PROTOCOL_OK) return status;
    break;
  default:
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_configuration_response_read(protocol_reader_t *reader, wireless_audio_configuration_configuration_response_t *message) {
  protocol_status_t status;
  status = protocol_read_uint16(reader, &message->request_id);
  if (status != PROTOCOL_OK) return status;
  uint8_t raw_type;
  status = protocol_read_uint8(reader, &raw_type);
  if (status != PROTOCOL_OK) return status;
  message->type = (wireless_audio_configuration_configuration_response_type_t)raw_type;
  switch (message->type) {
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_COMMAND_RESULT:
    status = wireless_audio_configuration_command_result_read(reader, &message->payload.command_result);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_CONFIGURED_ACL_CONNECTION_POLICY:
    status = wireless_audio_configuration_configured_acl_connection_policy_read(reader, &message->payload.configured_acl_connection_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_CONFIGURED_ACL_RADIO_POLICY:
    status = wireless_audio_configuration_configured_acl_radio_policy_read(reader, &message->payload.configured_acl_radio_policy);
    if (status != PROTOCOL_OK) return status;
    break;
  case WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_CONFIGURED_UNICAST_SERVER_QOS_PREFERENCES:
    status = wireless_audio_configuration_configured_unicast_server_qos_preferences_read(reader, &message->payload.configured_unicast_server_qos_preferences);
    if (status != PROTOCOL_OK) return status;
    break;
  default:
    return PROTOCOL_ERROR_INVALID_DATA;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_configuration_response_encode(const wireless_audio_configuration_configuration_response_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_configuration_response_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_configuration_response_decode(wireless_audio_configuration_configuration_response_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_configuration_response_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_runtime_state_write(protocol_writer_t *writer, const wireless_audio_configuration_runtime_state_t *message) {
  protocol_status_t status;
  status = protocol_write_uint32(writer, message->sequence);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->validity_flags);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->connection_id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->stream_id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->direction);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->lifecycle_state);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->acl_interval_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->acl_peripheral_latency);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->acl_supervision_timeout_ms);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->transmit_phy);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->receive_phy);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->transmit_data_octets);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->receive_data_octets);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->lc3_sampling_frequency_hz);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->lc3_frame_duration_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->lc3_octets_per_frame);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->lc3_frame_blocks_per_sdu);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->lc3_channel_allocation);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->iso_sdu_interval_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->iso_framing);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->iso_phy);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->iso_retransmission_number);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->iso_maximum_sdu_octets);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->iso_maximum_transport_latency_ms);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->presentation_delay_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->audio_underrun_count);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->acl_adjustment_count);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_runtime_state_read(protocol_reader_t *reader, wireless_audio_configuration_runtime_state_t *message) {
  protocol_status_t status;
  status = protocol_read_uint32(reader, &message->sequence);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->validity_flags);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->connection_id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->stream_id);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->direction);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->lifecycle_state);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->acl_interval_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->acl_peripheral_latency);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->acl_supervision_timeout_ms);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->transmit_phy);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->receive_phy);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->transmit_data_octets);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->receive_data_octets);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->lc3_sampling_frequency_hz);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->lc3_frame_duration_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->lc3_octets_per_frame);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->lc3_frame_blocks_per_sdu);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->lc3_channel_allocation);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->iso_sdu_interval_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->iso_framing);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->iso_phy);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->iso_retransmission_number);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->iso_maximum_sdu_octets);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->iso_maximum_transport_latency_ms);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->presentation_delay_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->audio_underrun_count);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->acl_adjustment_count);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_runtime_state_encode(const wireless_audio_configuration_runtime_state_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_runtime_state_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_runtime_state_decode(wireless_audio_configuration_runtime_state_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_runtime_state_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_capabilities_write(protocol_writer_t *writer, const wireless_audio_configuration_capabilities_t *message) {
  protocol_status_t status;
  status = protocol_write_uint16(writer, message->protocol_version);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->supported_section_mask);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->supported_command_mask);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->supported_acl_policy_mask);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->supported_phy_mask);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->minimum_acl_interval_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->maximum_acl_interval_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->acl_interval_resolution_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->maximum_acl_peripheral_latency);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->minimum_acl_supervision_timeout_ms);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->maximum_acl_supervision_timeout_ms);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->minimum_acl_data_octets);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->maximum_acl_data_octets);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->minimum_acl_data_time_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->maximum_acl_data_time_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->supported_audio_direction_mask);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint8(writer, message->maximum_preferred_retransmission_number);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint16(writer, message->maximum_transport_latency_ms);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->minimum_presentation_delay_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->maximum_presentation_delay_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_write_uint32(writer, message->feature_flags);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

static protocol_status_t wireless_audio_configuration_capabilities_read(protocol_reader_t *reader, wireless_audio_configuration_capabilities_t *message) {
  protocol_status_t status;
  status = protocol_read_uint16(reader, &message->protocol_version);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->supported_section_mask);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->supported_command_mask);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->supported_acl_policy_mask);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->supported_phy_mask);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->minimum_acl_interval_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->maximum_acl_interval_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->acl_interval_resolution_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->maximum_acl_peripheral_latency);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->minimum_acl_supervision_timeout_ms);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->maximum_acl_supervision_timeout_ms);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->minimum_acl_data_octets);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->maximum_acl_data_octets);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->minimum_acl_data_time_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->maximum_acl_data_time_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->supported_audio_direction_mask);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint8(reader, &message->maximum_preferred_retransmission_number);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint16(reader, &message->maximum_transport_latency_ms);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->minimum_presentation_delay_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->maximum_presentation_delay_us);
  if (status != PROTOCOL_OK) return status;
  status = protocol_read_uint32(reader, &message->feature_flags);
  if (status != PROTOCOL_OK) return status;
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_capabilities_encode(const wireless_audio_configuration_capabilities_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written) {
  protocol_writer_t writer = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_capabilities_write(&writer, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_written != NULL) {
    *bytes_written = writer.offset;
  }
  return PROTOCOL_OK;
}

protocol_status_t wireless_audio_configuration_capabilities_decode(wireless_audio_configuration_capabilities_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read) {
  protocol_reader_t reader = { buffer, buffer_size, 0 };
  protocol_status_t status = wireless_audio_configuration_capabilities_read(&reader, message);
  if (status != PROTOCOL_OK) {
    return status;
  }
  if (bytes_read != NULL) {
    *bytes_read = reader.offset;
  }
  return PROTOCOL_OK;
}

