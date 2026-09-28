// Generated from schemas/wireless-audio-configuration/protocol.yml. Do not edit by hand.
#pragma once

#include "protocol_runtime.h"

#define WIRELESS_AUDIO_CONFIGURATION_BLE_SERVICE_UUID "5bddd959-06f3-4029-85d3-5471b1eda18a"
#define WIRELESS_AUDIO_CONFIGURATION_BLE_COMMAND_CHARACTERISTIC_UUID "150c77b5-4d1e-4b87-a0d9-647001946358"
#define WIRELESS_AUDIO_CONFIGURATION_BLE_COMMAND_CHARACTERISTIC_PROPERTIES (PROTOCOL_BLE_PROPERTY_WRITE)
#define WIRELESS_AUDIO_CONFIGURATION_BLE_RESPONSE_CHARACTERISTIC_UUID "1ae8ed46-b23c-48ba-8e67-5713a4a4dc69"
#define WIRELESS_AUDIO_CONFIGURATION_BLE_RESPONSE_CHARACTERISTIC_PROPERTIES (PROTOCOL_BLE_PROPERTY_INDICATE)
#define WIRELESS_AUDIO_CONFIGURATION_BLE_RUNTIME_STATE_CHARACTERISTIC_UUID "922b3b49-cad3-44ce-a6b7-97abda85a8dd"
#define WIRELESS_AUDIO_CONFIGURATION_BLE_RUNTIME_STATE_CHARACTERISTIC_PROPERTIES (PROTOCOL_BLE_PROPERTY_READ | PROTOCOL_BLE_PROPERTY_NOTIFY)
#define WIRELESS_AUDIO_CONFIGURATION_BLE_CAPABILITIES_CHARACTERISTIC_UUID "1018f0be-9f05-4c73-a24b-944a20c57fe3"
#define WIRELESS_AUDIO_CONFIGURATION_BLE_CAPABILITIES_CHARACTERISTIC_PROPERTIES (PROTOCOL_BLE_PROPERTY_READ)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Leaves ACL connection parameter selection to the Bluetooth stack and peer; reserved must
 * be zero.
 */
typedef struct wireless_audio_configuration_controller_default_acl_policy_t wireless_audio_configuration_controller_default_acl_policy_t;
struct wireless_audio_configuration_controller_default_acl_policy_t {
  uint8_t reserved;
};


/**
 * Requests one fixed ACL connection interval together with peripheral latency and
 * supervision timeout.
 */
typedef struct wireless_audio_configuration_fixed_acl_policy_t wireless_audio_configuration_fixed_acl_policy_t;
struct wireless_audio_configuration_fixed_acl_policy_t {
  uint32_t interval_us;
  uint16_t peripheral_latency;
  uint32_t supervision_timeout_ms;
};


/**
 * Increases the ACL interval by a fixed step after an audio underrun episode and decreases
 * it periodically while audio is stable.
 */
typedef struct wireless_audio_configuration_adaptive_linear_acl_policy_t wireless_audio_configuration_adaptive_linear_acl_policy_t;
struct wireless_audio_configuration_adaptive_linear_acl_policy_t {
  uint32_t minimum_interval_us;
  uint32_t maximum_interval_us;
  uint32_t underrun_increase_step_us;
  uint32_t recovery_decrease_step_us;
  uint32_t recovery_period_ms;
  uint32_t minimum_update_period_ms;
  uint16_t peripheral_latency;
  uint32_t supervision_timeout_ms;
};


typedef enum wireless_audio_configuration_acl_connection_policy_type_t {
  WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_CONTROLLER_DEFAULT_ACL_POLICY = 0,
  WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_FIXED_ACL_POLICY = 1,
  WIRELESS_AUDIO_CONFIGURATION_ACL_CONNECTION_POLICY_ADAPTIVE_LINEAR_ACL_POLICY = 2,
} wireless_audio_configuration_acl_connection_policy_type_t;

/**
 * A tagged ACL connection policy. Type 0 uses controller defaults, type 1 requests a fixed
 * interval, and type 2 uses linear underrun adaptation.
 */
typedef struct wireless_audio_configuration_acl_connection_policy_t wireless_audio_configuration_acl_connection_policy_t;
struct wireless_audio_configuration_acl_connection_policy_t {
  wireless_audio_configuration_acl_connection_policy_type_t type;
  union {
    wireless_audio_configuration_controller_default_acl_policy_t controller_default_acl_policy;
    wireless_audio_configuration_fixed_acl_policy_t fixed_acl_policy;
    wireless_audio_configuration_adaptive_linear_acl_policy_t adaptive_linear_acl_policy;
  } policy;
};


/**
 * Optional ACL PHY and data length preferences selected by fields_present bits defined by
 * the protocol specification.
 */
typedef struct wireless_audio_configuration_acl_radio_preferences_t wireless_audio_configuration_acl_radio_preferences_t;
struct wireless_audio_configuration_acl_radio_preferences_t {
  uint16_t fields_present;
  uint8_t transmit_phy_mask;
  uint8_t receive_phy_mask;
  uint16_t transmit_max_data_octets;
  uint16_t transmit_max_time_us;
};


/**
 * Optional LC3 codec preferences for one or both audio directions, selected by
 * fields_present bits.
 */
typedef struct wireless_audio_configuration_lc3_preferences_t wireless_audio_configuration_lc3_preferences_t;
struct wireless_audio_configuration_lc3_preferences_t {
  uint16_t fields_present;
  uint8_t direction_mask;
  uint32_t sampling_frequency_hz;
  uint16_t frame_duration_us;
  uint16_t octets_per_frame;
  uint8_t frame_blocks_per_sdu;
  uint32_t channel_allocation;
};


/**
 * Optional Connected Isochronous Stream QoS preferences for one or both audio directions,
 * selected by fields_present bits.
 */
typedef struct wireless_audio_configuration_iso_qos_preferences_t wireless_audio_configuration_iso_qos_preferences_t;
struct wireless_audio_configuration_iso_qos_preferences_t {
  uint32_t fields_present;
  uint8_t direction_mask;
  uint32_t sdu_interval_us;
  uint8_t framing;
  uint8_t phy_mask;
  uint8_t retransmission_number;
  uint16_t maximum_sdu_octets;
  uint16_t maximum_transport_latency_ms;
  uint32_t presentation_delay_us;
  uint32_t minimum_presentation_delay_us;
  uint32_t maximum_presentation_delay_us;
  uint32_t preferred_minimum_presentation_delay_us;
  uint32_t preferred_maximum_presentation_delay_us;
};


/** Selects the ACL connection policy and optionally persists it across restarts. */
typedef struct wireless_audio_configuration_set_acl_connection_policy_t wireless_audio_configuration_set_acl_connection_policy_t;
struct wireless_audio_configuration_set_acl_connection_policy_t {
  uint8_t persist;
  wireless_audio_configuration_acl_connection_policy_t policy;
};


/** Sets ACL PHY and data length preferences and optionally persists them across restarts. */
typedef struct wireless_audio_configuration_set_acl_radio_preferences_t wireless_audio_configuration_set_acl_radio_preferences_t;
struct wireless_audio_configuration_set_acl_radio_preferences_t {
  uint8_t persist;
  wireless_audio_configuration_acl_radio_preferences_t preferences;
};


/** Sets LC3 codec preferences and optionally persists them across restarts. */
typedef struct wireless_audio_configuration_set_lc3_preferences_t wireless_audio_configuration_set_lc3_preferences_t;
struct wireless_audio_configuration_set_lc3_preferences_t {
  uint8_t persist;
  wireless_audio_configuration_lc3_preferences_t preferences;
};


/** Sets CIS QoS preferences and optionally persists them across restarts. */
typedef struct wireless_audio_configuration_set_iso_qos_preferences_t wireless_audio_configuration_set_iso_qos_preferences_t;
struct wireless_audio_configuration_set_iso_qos_preferences_t {
  uint8_t persist;
  wireless_audio_configuration_iso_qos_preferences_t preferences;
};


/** Requests the configured value for one section identified by its stable section ID. */
typedef struct wireless_audio_configuration_get_configuration_t wireless_audio_configuration_get_configuration_t;
struct wireless_audio_configuration_get_configuration_t {
  uint8_t section;
};


/**
 * Restores compiled defaults for the sections selected by section_mask, or every supported
 * section when the mask is zero.
 */
typedef struct wireless_audio_configuration_restore_defaults_t wireless_audio_configuration_restore_defaults_t;
struct wireless_audio_configuration_restore_defaults_t {
  uint32_t section_mask;
};


typedef enum wireless_audio_configuration_configuration_command_type_t {
  WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_SET_ACL_CONNECTION_POLICY = 0,
  WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_SET_ACL_RADIO_PREFERENCES = 1,
  WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_SET_LC3_PREFERENCES = 2,
  WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_SET_ISO_QOS_PREFERENCES = 3,
  WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_GET_CONFIGURATION = 4,
  WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_COMMAND_RESTORE_DEFAULTS = 5,
} wireless_audio_configuration_configuration_command_type_t;

/** A correlated wireless audio configuration command with a stable tagged operation. */
typedef struct wireless_audio_configuration_configuration_command_t wireless_audio_configuration_configuration_command_t;
struct wireless_audio_configuration_configuration_command_t {
  uint16_t request_id;
  wireless_audio_configuration_configuration_command_type_t type;
  union {
    wireless_audio_configuration_set_acl_connection_policy_t set_acl_connection_policy;
    wireless_audio_configuration_set_acl_radio_preferences_t set_acl_radio_preferences;
    wireless_audio_configuration_set_lc3_preferences_t set_lc3_preferences;
    wireless_audio_configuration_set_iso_qos_preferences_t set_iso_qos_preferences;
    wireless_audio_configuration_get_configuration_t get_configuration;
    wireless_audio_configuration_restore_defaults_t restore_defaults;
  } operation;
};


/** Reports the configured ACL connection policy and whether it is persistent. */
typedef struct wireless_audio_configuration_configured_acl_connection_policy_t wireless_audio_configuration_configured_acl_connection_policy_t;
struct wireless_audio_configuration_configured_acl_connection_policy_t {
  uint8_t persisted;
  wireless_audio_configuration_acl_connection_policy_t policy;
};


/** Reports configured ACL radio preferences and whether they are persistent. */
typedef struct wireless_audio_configuration_configured_acl_radio_preferences_t wireless_audio_configuration_configured_acl_radio_preferences_t;
struct wireless_audio_configuration_configured_acl_radio_preferences_t {
  uint8_t persisted;
  wireless_audio_configuration_acl_radio_preferences_t preferences;
};


/** Reports configured LC3 preferences and whether they are persistent. */
typedef struct wireless_audio_configuration_configured_lc3_preferences_t wireless_audio_configuration_configured_lc3_preferences_t;
struct wireless_audio_configuration_configured_lc3_preferences_t {
  uint8_t persisted;
  wireless_audio_configuration_lc3_preferences_t preferences;
};


/** Reports configured CIS QoS preferences and whether they are persistent. */
typedef struct wireless_audio_configuration_configured_iso_qos_preferences_t wireless_audio_configuration_configured_iso_qos_preferences_t;
struct wireless_audio_configuration_configured_iso_qos_preferences_t {
  uint8_t persisted;
  wireless_audio_configuration_iso_qos_preferences_t preferences;
};


/**
 * Reports whether a command was accepted and whether applying it requires a connection or
 * stream restart.
 */
typedef struct wireless_audio_configuration_command_result_t wireless_audio_configuration_command_result_t;
struct wireless_audio_configuration_command_result_t {
  uint8_t status;
  uint8_t error_domain;
  int32_t error_code;
  uint32_t restart_required_mask;
};


typedef enum wireless_audio_configuration_configuration_response_type_t {
  WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_COMMAND_RESULT = 0,
  WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_CONFIGURED_ACL_CONNECTION_POLICY = 1,
  WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_CONFIGURED_ACL_RADIO_PREFERENCES = 2,
  WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_CONFIGURED_LC3_PREFERENCES = 3,
  WIRELESS_AUDIO_CONFIGURATION_CONFIGURATION_RESPONSE_CONFIGURED_ISO_QOS_PREFERENCES = 4,
} wireless_audio_configuration_configuration_response_type_t;

/**
 * A response correlated to a configuration command. Type 0 is a command result and types 1
 * through 4 report one configuration section.
 */
typedef struct wireless_audio_configuration_configuration_response_t wireless_audio_configuration_configuration_response_t;
struct wireless_audio_configuration_configuration_response_t {
  uint16_t request_id;
  wireless_audio_configuration_configuration_response_type_t type;
  union {
    wireless_audio_configuration_command_result_t command_result;
    wireless_audio_configuration_configured_acl_connection_policy_t configured_acl_connection_policy;
    wireless_audio_configuration_configured_acl_radio_preferences_t configured_acl_radio_preferences;
    wireless_audio_configuration_configured_lc3_preferences_t configured_lc3_preferences;
    wireless_audio_configuration_configured_iso_qos_preferences_t configured_iso_qos_preferences;
  } payload;
};


/**
 * Reports effective ACL parameters and negotiated LE Audio configuration for one
 * connection and stream; fields without a corresponding validity flag are zero.
 */
typedef struct wireless_audio_configuration_runtime_state_t wireless_audio_configuration_runtime_state_t;
struct wireless_audio_configuration_runtime_state_t {
  uint32_t sequence;
  uint32_t validity_flags;
  uint16_t connection_id;
  uint8_t stream_id;
  uint8_t direction;
  uint8_t lifecycle_state;
  uint32_t acl_interval_us;
  uint16_t acl_peripheral_latency;
  uint32_t acl_supervision_timeout_ms;
  uint8_t transmit_phy;
  uint8_t receive_phy;
  uint16_t transmit_data_octets;
  uint16_t receive_data_octets;
  uint32_t lc3_sampling_frequency_hz;
  uint16_t lc3_frame_duration_us;
  uint16_t lc3_octets_per_frame;
  uint8_t lc3_frame_blocks_per_sdu;
  uint32_t lc3_channel_allocation;
  uint32_t iso_sdu_interval_us;
  uint8_t iso_framing;
  uint8_t iso_phy;
  uint8_t iso_retransmission_number;
  uint16_t iso_maximum_sdu_octets;
  uint16_t iso_maximum_transport_latency_ms;
  uint32_t presentation_delay_us;
  uint32_t audio_underrun_count;
  uint32_t acl_adjustment_count;
};


/**
 * Reports supported configuration sections, policy types, radio features, and value ranges
 * for this firmware build and controller.
 */
typedef struct wireless_audio_configuration_capabilities_t wireless_audio_configuration_capabilities_t;
struct wireless_audio_configuration_capabilities_t {
  uint16_t protocol_version;
  uint32_t supported_section_mask;
  uint32_t supported_command_mask;
  uint32_t supported_acl_policy_mask;
  uint8_t supported_phy_mask;
  uint32_t minimum_acl_interval_us;
  uint32_t maximum_acl_interval_us;
  uint32_t acl_interval_resolution_us;
  uint16_t maximum_acl_peripheral_latency;
  uint32_t minimum_acl_supervision_timeout_ms;
  uint32_t maximum_acl_supervision_timeout_ms;
  uint16_t maximum_acl_data_octets;
  uint16_t supported_lc3_sampling_frequency_mask;
  uint8_t supported_lc3_frame_duration_mask;
  uint16_t minimum_lc3_octets_per_frame;
  uint16_t maximum_lc3_octets_per_frame;
  uint8_t maximum_lc3_frame_blocks_per_sdu;
  uint8_t maximum_iso_retransmission_number;
  uint16_t maximum_iso_sdu_octets;
  uint16_t maximum_iso_transport_latency_ms;
  uint32_t minimum_presentation_delay_us;
  uint32_t maximum_presentation_delay_us;
  uint32_t feature_flags;
};


/** Typed handlers used to dispatch acl_connection_policy.policy. */
typedef struct wireless_audio_configuration_acl_connection_policy_handler_t {
  protocol_status_t (*controller_default_acl_policy)(void *context, const wireless_audio_configuration_controller_default_acl_policy_t *command);
  protocol_status_t (*fixed_acl_policy)(void *context, const wireless_audio_configuration_fixed_acl_policy_t *command);
  protocol_status_t (*adaptive_linear_acl_policy)(void *context, const wireless_audio_configuration_adaptive_linear_acl_policy_t *command);
} wireless_audio_configuration_acl_connection_policy_handler_t;

/** Set acl_connection_policy.policy to controller_default_acl_policy. */
void wireless_audio_configuration_acl_connection_policy_set_policy_controller_default_acl_policy(wireless_audio_configuration_acl_connection_policy_t *message, wireless_audio_configuration_controller_default_acl_policy_t command);
/** Build a acl_connection_policy message containing controller_default_acl_policy. */
wireless_audio_configuration_acl_connection_policy_t wireless_audio_configuration_acl_connection_policy_from_controller_default_acl_policy(wireless_audio_configuration_controller_default_acl_policy_t command);
/** Set acl_connection_policy.policy to fixed_acl_policy. */
void wireless_audio_configuration_acl_connection_policy_set_policy_fixed_acl_policy(wireless_audio_configuration_acl_connection_policy_t *message, wireless_audio_configuration_fixed_acl_policy_t command);
/** Build a acl_connection_policy message containing fixed_acl_policy. */
wireless_audio_configuration_acl_connection_policy_t wireless_audio_configuration_acl_connection_policy_from_fixed_acl_policy(wireless_audio_configuration_fixed_acl_policy_t command);
/** Set acl_connection_policy.policy to adaptive_linear_acl_policy. */
void wireless_audio_configuration_acl_connection_policy_set_policy_adaptive_linear_acl_policy(wireless_audio_configuration_acl_connection_policy_t *message, wireless_audio_configuration_adaptive_linear_acl_policy_t command);
/** Build a acl_connection_policy message containing adaptive_linear_acl_policy. */
wireless_audio_configuration_acl_connection_policy_t wireless_audio_configuration_acl_connection_policy_from_adaptive_linear_acl_policy(wireless_audio_configuration_adaptive_linear_acl_policy_t command);
/** Dispatch acl_connection_policy.policy to its typed handler. */
protocol_status_t wireless_audio_configuration_acl_connection_policy_dispatch(const wireless_audio_configuration_acl_connection_policy_t *message, const wireless_audio_configuration_acl_connection_policy_handler_t *handler, void *context);

/** Typed handlers used to dispatch configuration_command.operation. */
typedef struct wireless_audio_configuration_configuration_command_handler_t {
  protocol_status_t (*set_acl_connection_policy)(void *context, const wireless_audio_configuration_set_acl_connection_policy_t *command);
  protocol_status_t (*set_acl_radio_preferences)(void *context, const wireless_audio_configuration_set_acl_radio_preferences_t *command);
  protocol_status_t (*set_lc3_preferences)(void *context, const wireless_audio_configuration_set_lc3_preferences_t *command);
  protocol_status_t (*set_iso_qos_preferences)(void *context, const wireless_audio_configuration_set_iso_qos_preferences_t *command);
  protocol_status_t (*get_configuration)(void *context, const wireless_audio_configuration_get_configuration_t *command);
  protocol_status_t (*restore_defaults)(void *context, const wireless_audio_configuration_restore_defaults_t *command);
} wireless_audio_configuration_configuration_command_handler_t;

/** Set configuration_command.operation to set_acl_connection_policy. */
void wireless_audio_configuration_configuration_command_set_operation_set_acl_connection_policy(wireless_audio_configuration_configuration_command_t *message, wireless_audio_configuration_set_acl_connection_policy_t command);
/** Set configuration_command.operation to set_acl_radio_preferences. */
void wireless_audio_configuration_configuration_command_set_operation_set_acl_radio_preferences(wireless_audio_configuration_configuration_command_t *message, wireless_audio_configuration_set_acl_radio_preferences_t command);
/** Set configuration_command.operation to set_lc3_preferences. */
void wireless_audio_configuration_configuration_command_set_operation_set_lc3_preferences(wireless_audio_configuration_configuration_command_t *message, wireless_audio_configuration_set_lc3_preferences_t command);
/** Set configuration_command.operation to set_iso_qos_preferences. */
void wireless_audio_configuration_configuration_command_set_operation_set_iso_qos_preferences(wireless_audio_configuration_configuration_command_t *message, wireless_audio_configuration_set_iso_qos_preferences_t command);
/** Set configuration_command.operation to get_configuration. */
void wireless_audio_configuration_configuration_command_set_operation_get_configuration(wireless_audio_configuration_configuration_command_t *message, wireless_audio_configuration_get_configuration_t command);
/** Set configuration_command.operation to restore_defaults. */
void wireless_audio_configuration_configuration_command_set_operation_restore_defaults(wireless_audio_configuration_configuration_command_t *message, wireless_audio_configuration_restore_defaults_t command);
/** Dispatch configuration_command.operation to its typed handler. */
protocol_status_t wireless_audio_configuration_configuration_command_dispatch(const wireless_audio_configuration_configuration_command_t *message, const wireless_audio_configuration_configuration_command_handler_t *handler, void *context);

/** Typed handlers used to dispatch configuration_response.payload. */
typedef struct wireless_audio_configuration_configuration_response_handler_t {
  protocol_status_t (*command_result)(void *context, const wireless_audio_configuration_command_result_t *command);
  protocol_status_t (*configured_acl_connection_policy)(void *context, const wireless_audio_configuration_configured_acl_connection_policy_t *command);
  protocol_status_t (*configured_acl_radio_preferences)(void *context, const wireless_audio_configuration_configured_acl_radio_preferences_t *command);
  protocol_status_t (*configured_lc3_preferences)(void *context, const wireless_audio_configuration_configured_lc3_preferences_t *command);
  protocol_status_t (*configured_iso_qos_preferences)(void *context, const wireless_audio_configuration_configured_iso_qos_preferences_t *command);
} wireless_audio_configuration_configuration_response_handler_t;

/** Set configuration_response.payload to command_result. */
void wireless_audio_configuration_configuration_response_set_payload_command_result(wireless_audio_configuration_configuration_response_t *message, wireless_audio_configuration_command_result_t command);
/** Set configuration_response.payload to configured_acl_connection_policy. */
void wireless_audio_configuration_configuration_response_set_payload_configured_acl_connection_policy(wireless_audio_configuration_configuration_response_t *message, wireless_audio_configuration_configured_acl_connection_policy_t command);
/** Set configuration_response.payload to configured_acl_radio_preferences. */
void wireless_audio_configuration_configuration_response_set_payload_configured_acl_radio_preferences(wireless_audio_configuration_configuration_response_t *message, wireless_audio_configuration_configured_acl_radio_preferences_t command);
/** Set configuration_response.payload to configured_lc3_preferences. */
void wireless_audio_configuration_configuration_response_set_payload_configured_lc3_preferences(wireless_audio_configuration_configuration_response_t *message, wireless_audio_configuration_configured_lc3_preferences_t command);
/** Set configuration_response.payload to configured_iso_qos_preferences. */
void wireless_audio_configuration_configuration_response_set_payload_configured_iso_qos_preferences(wireless_audio_configuration_configuration_response_t *message, wireless_audio_configuration_configured_iso_qos_preferences_t command);
/** Dispatch configuration_response.payload to its typed handler. */
protocol_status_t wireless_audio_configuration_configuration_response_dispatch(const wireless_audio_configuration_configuration_response_t *message, const wireless_audio_configuration_configuration_response_handler_t *handler, void *context);

/**
 * Encode a binary representation of this message. Leaves ACL connection parameter
 * selection to the Bluetooth stack and peer; reserved must be zero.
 */
protocol_status_t wireless_audio_configuration_controller_default_acl_policy_encode(const wireless_audio_configuration_controller_default_acl_policy_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Leaves ACL connection parameter
 * selection to the Bluetooth stack and peer; reserved must be zero.
 */
protocol_status_t wireless_audio_configuration_controller_default_acl_policy_decode(wireless_audio_configuration_controller_default_acl_policy_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Requests one fixed ACL connection
 * interval together with peripheral latency and supervision timeout.
 */
protocol_status_t wireless_audio_configuration_fixed_acl_policy_encode(const wireless_audio_configuration_fixed_acl_policy_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Requests one fixed ACL connection
 * interval together with peripheral latency and supervision timeout.
 */
protocol_status_t wireless_audio_configuration_fixed_acl_policy_decode(wireless_audio_configuration_fixed_acl_policy_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Increases the ACL interval by a fixed
 * step after an audio underrun episode and decreases it periodically while audio is
 * stable.
 */
protocol_status_t wireless_audio_configuration_adaptive_linear_acl_policy_encode(const wireless_audio_configuration_adaptive_linear_acl_policy_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Increases the ACL interval by a fixed
 * step after an audio underrun episode and decreases it periodically while audio is
 * stable.
 */
protocol_status_t wireless_audio_configuration_adaptive_linear_acl_policy_decode(wireless_audio_configuration_adaptive_linear_acl_policy_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. A tagged ACL connection policy. Type 0
 * uses controller defaults, type 1 requests a fixed interval, and type 2 uses linear
 * underrun adaptation.
 */
protocol_status_t wireless_audio_configuration_acl_connection_policy_encode(const wireless_audio_configuration_acl_connection_policy_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. A tagged ACL connection policy. Type 0
 * uses controller defaults, type 1 requests a fixed interval, and type 2 uses linear
 * underrun adaptation.
 */
protocol_status_t wireless_audio_configuration_acl_connection_policy_decode(wireless_audio_configuration_acl_connection_policy_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Optional ACL PHY and data length
 * preferences selected by fields_present bits defined by the protocol specification.
 */
protocol_status_t wireless_audio_configuration_acl_radio_preferences_encode(const wireless_audio_configuration_acl_radio_preferences_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Optional ACL PHY and data length
 * preferences selected by fields_present bits defined by the protocol specification.
 */
protocol_status_t wireless_audio_configuration_acl_radio_preferences_decode(wireless_audio_configuration_acl_radio_preferences_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Optional LC3 codec preferences for one
 * or both audio directions, selected by fields_present bits.
 */
protocol_status_t wireless_audio_configuration_lc3_preferences_encode(const wireless_audio_configuration_lc3_preferences_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Optional LC3 codec preferences for one
 * or both audio directions, selected by fields_present bits.
 */
protocol_status_t wireless_audio_configuration_lc3_preferences_decode(wireless_audio_configuration_lc3_preferences_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Optional Connected Isochronous Stream
 * QoS preferences for one or both audio directions, selected by fields_present bits.
 */
protocol_status_t wireless_audio_configuration_iso_qos_preferences_encode(const wireless_audio_configuration_iso_qos_preferences_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Optional Connected Isochronous Stream
 * QoS preferences for one or both audio directions, selected by fields_present bits.
 */
protocol_status_t wireless_audio_configuration_iso_qos_preferences_decode(wireless_audio_configuration_iso_qos_preferences_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Selects the ACL connection policy and
 * optionally persists it across restarts.
 */
protocol_status_t wireless_audio_configuration_set_acl_connection_policy_encode(const wireless_audio_configuration_set_acl_connection_policy_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Selects the ACL connection policy and
 * optionally persists it across restarts.
 */
protocol_status_t wireless_audio_configuration_set_acl_connection_policy_decode(wireless_audio_configuration_set_acl_connection_policy_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Sets ACL PHY and data length preferences
 * and optionally persists them across restarts.
 */
protocol_status_t wireless_audio_configuration_set_acl_radio_preferences_encode(const wireless_audio_configuration_set_acl_radio_preferences_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Sets ACL PHY and data length
 * preferences and optionally persists them across restarts.
 */
protocol_status_t wireless_audio_configuration_set_acl_radio_preferences_decode(wireless_audio_configuration_set_acl_radio_preferences_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Sets LC3 codec preferences and
 * optionally persists them across restarts.
 */
protocol_status_t wireless_audio_configuration_set_lc3_preferences_encode(const wireless_audio_configuration_set_lc3_preferences_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Sets LC3 codec preferences and
 * optionally persists them across restarts.
 */
protocol_status_t wireless_audio_configuration_set_lc3_preferences_decode(wireless_audio_configuration_set_lc3_preferences_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Sets CIS QoS preferences and optionally
 * persists them across restarts.
 */
protocol_status_t wireless_audio_configuration_set_iso_qos_preferences_encode(const wireless_audio_configuration_set_iso_qos_preferences_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Sets CIS QoS preferences and
 * optionally persists them across restarts.
 */
protocol_status_t wireless_audio_configuration_set_iso_qos_preferences_decode(wireless_audio_configuration_set_iso_qos_preferences_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Requests the configured value for one
 * section identified by its stable section ID.
 */
protocol_status_t wireless_audio_configuration_get_configuration_encode(const wireless_audio_configuration_get_configuration_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Requests the configured value for one
 * section identified by its stable section ID.
 */
protocol_status_t wireless_audio_configuration_get_configuration_decode(wireless_audio_configuration_get_configuration_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Restores compiled defaults for the
 * sections selected by section_mask, or every supported section when the mask is zero.
 */
protocol_status_t wireless_audio_configuration_restore_defaults_encode(const wireless_audio_configuration_restore_defaults_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Restores compiled defaults for the
 * sections selected by section_mask, or every supported section when the mask is zero.
 */
protocol_status_t wireless_audio_configuration_restore_defaults_decode(wireless_audio_configuration_restore_defaults_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. A correlated wireless audio
 * configuration command with a stable tagged operation.
 */
protocol_status_t wireless_audio_configuration_configuration_command_encode(const wireless_audio_configuration_configuration_command_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. A correlated wireless audio
 * configuration command with a stable tagged operation.
 */
protocol_status_t wireless_audio_configuration_configuration_command_decode(wireless_audio_configuration_configuration_command_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Reports the configured ACL connection
 * policy and whether it is persistent.
 */
protocol_status_t wireless_audio_configuration_configured_acl_connection_policy_encode(const wireless_audio_configuration_configured_acl_connection_policy_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Reports the configured ACL connection
 * policy and whether it is persistent.
 */
protocol_status_t wireless_audio_configuration_configured_acl_connection_policy_decode(wireless_audio_configuration_configured_acl_connection_policy_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Reports configured ACL radio preferences
 * and whether they are persistent.
 */
protocol_status_t wireless_audio_configuration_configured_acl_radio_preferences_encode(const wireless_audio_configuration_configured_acl_radio_preferences_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Reports configured ACL radio
 * preferences and whether they are persistent.
 */
protocol_status_t wireless_audio_configuration_configured_acl_radio_preferences_decode(wireless_audio_configuration_configured_acl_radio_preferences_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Reports configured LC3 preferences and
 * whether they are persistent.
 */
protocol_status_t wireless_audio_configuration_configured_lc3_preferences_encode(const wireless_audio_configuration_configured_lc3_preferences_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Reports configured LC3 preferences and
 * whether they are persistent.
 */
protocol_status_t wireless_audio_configuration_configured_lc3_preferences_decode(wireless_audio_configuration_configured_lc3_preferences_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Reports configured CIS QoS preferences
 * and whether they are persistent.
 */
protocol_status_t wireless_audio_configuration_configured_iso_qos_preferences_encode(const wireless_audio_configuration_configured_iso_qos_preferences_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Reports configured CIS QoS preferences
 * and whether they are persistent.
 */
protocol_status_t wireless_audio_configuration_configured_iso_qos_preferences_decode(wireless_audio_configuration_configured_iso_qos_preferences_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Reports whether a command was accepted
 * and whether applying it requires a connection or stream restart.
 */
protocol_status_t wireless_audio_configuration_command_result_encode(const wireless_audio_configuration_command_result_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Reports whether a command was accepted
 * and whether applying it requires a connection or stream restart.
 */
protocol_status_t wireless_audio_configuration_command_result_decode(wireless_audio_configuration_command_result_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. A response correlated to a configuration
 * command. Type 0 is a command result and types 1 through 4 report one configuration
 * section.
 */
protocol_status_t wireless_audio_configuration_configuration_response_encode(const wireless_audio_configuration_configuration_response_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. A response correlated to a
 * configuration command. Type 0 is a command result and types 1 through 4 report one
 * configuration section.
 */
protocol_status_t wireless_audio_configuration_configuration_response_decode(wireless_audio_configuration_configuration_response_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Reports effective ACL parameters and
 * negotiated LE Audio configuration for one connection and stream; fields without a
 * corresponding validity flag are zero.
 */
protocol_status_t wireless_audio_configuration_runtime_state_encode(const wireless_audio_configuration_runtime_state_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Reports effective ACL parameters and
 * negotiated LE Audio configuration for one connection and stream; fields without a
 * corresponding validity flag are zero.
 */
protocol_status_t wireless_audio_configuration_runtime_state_decode(wireless_audio_configuration_runtime_state_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

/**
 * Encode a binary representation of this message. Reports supported configuration
 * sections, policy types, radio features, and value ranges for this firmware build and
 * controller.
 */
protocol_status_t wireless_audio_configuration_capabilities_encode(const wireless_audio_configuration_capabilities_t *message, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);
/**
 * Decode a binary representation into this message. Reports supported configuration
 * sections, policy types, radio features, and value ranges for this firmware build and
 * controller.
 */
protocol_status_t wireless_audio_configuration_capabilities_decode(wireless_audio_configuration_capabilities_t *message, const uint8_t *buffer, size_t buffer_size, size_t *bytes_read);

#ifdef __cplusplus
}
#endif

