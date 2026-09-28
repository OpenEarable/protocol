// Generated from schemas/wireless-audio-configuration/protocol.yml. Do not edit by hand.
import 'dart:typed_data';
import 'protocol_runtime.dart';

/// BLE UUIDs for the wireless-audio-configuration protocol.
abstract final class WirelessAudioConfigurationBleUuids {
  /// BLE service UUID.
  static const String serviceUuid = '5bddd959-06f3-4029-85d3-5471b1eda18a';

  /// BLE UUID for the command characteristic.
  static const String commandCharacteristicUuid = '150c77b5-4d1e-4b87-a0d9-647001946358';

  /// BLE metadata for the command characteristic.
  static const ProtocolBleCharacteristicDefinition commandCharacteristic =
      ProtocolBleCharacteristicDefinition(
        name: 'command',
        uuid: commandCharacteristicUuid,
        properties: {
          ProtocolBleCharacteristicProperty.write,
        },
      );

  /// BLE UUID for the response characteristic.
  static const String responseCharacteristicUuid = '1ae8ed46-b23c-48ba-8e67-5713a4a4dc69';

  /// BLE metadata for the response characteristic.
  static const ProtocolBleCharacteristicDefinition responseCharacteristic =
      ProtocolBleCharacteristicDefinition(
        name: 'response',
        uuid: responseCharacteristicUuid,
        properties: {
          ProtocolBleCharacteristicProperty.indicate,
        },
      );

  /// BLE UUID for the runtime_state characteristic.
  static const String runtimeStateCharacteristicUuid = '922b3b49-cad3-44ce-a6b7-97abda85a8dd';

  /// BLE metadata for the runtime_state characteristic.
  static const ProtocolBleCharacteristicDefinition runtimeStateCharacteristic =
      ProtocolBleCharacteristicDefinition(
        name: 'runtime_state',
        uuid: runtimeStateCharacteristicUuid,
        properties: {
          ProtocolBleCharacteristicProperty.read,
          ProtocolBleCharacteristicProperty.notify,
        },
      );

  /// BLE UUID for the capabilities characteristic.
  static const String capabilitiesCharacteristicUuid = '1018f0be-9f05-4c73-a24b-944a20c57fe3';

  /// BLE metadata for the capabilities characteristic.
  static const ProtocolBleCharacteristicDefinition capabilitiesCharacteristic =
      ProtocolBleCharacteristicDefinition(
        name: 'capabilities',
        uuid: capabilitiesCharacteristicUuid,
        properties: {
          ProtocolBleCharacteristicProperty.read,
        },
      );

  /// Complete framework-neutral BLE service metadata.
  static const ProtocolBleServiceDefinition service =
      ProtocolBleServiceDefinition(
        uuid: serviceUuid,
        characteristics: [commandCharacteristic, responseCharacteristic, runtimeStateCharacteristic, capabilitiesCharacteristic],
      );
}

/// Payload accepted by WirelessAudioConfigurationAclConnectionPolicy.policy.
sealed class WirelessAudioConfigurationAclConnectionPolicyPolicy {}

/// Payload accepted by WirelessAudioConfigurationAclRadioPolicy.policy.
sealed class WirelessAudioConfigurationAclRadioPolicyPolicy {}

/// Payload accepted by WirelessAudioConfigurationConfigurationCommand.operation.
sealed class WirelessAudioConfigurationConfigurationCommandOperation {}

/// Payload accepted by WirelessAudioConfigurationConfigurationResponse.payload.
sealed class WirelessAudioConfigurationConfigurationResponsePayload {}

/// Leaves ACL connection parameter selection to the Bluetooth stack and peer; reserved must
/// be zero.
class WirelessAudioConfigurationControllerDefaultAclPolicy implements WirelessAudioConfigurationAclConnectionPolicyPolicy {
  /// Creates a WirelessAudioConfigurationControllerDefaultAclPolicy value.
  WirelessAudioConfigurationControllerDefaultAclPolicy({required this.reserved});

  final int reserved;

  /// Decodes a complete WirelessAudioConfigurationControllerDefaultAclPolicy value from [bytes].
  factory WirelessAudioConfigurationControllerDefaultAclPolicy.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationControllerDefaultAclPolicy._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationControllerDefaultAclPolicy _read(ProtocolReader reader) {
    final reserved = reader.uint8();
    return WirelessAudioConfigurationControllerDefaultAclPolicy(reserved: reserved);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(reserved);
  }
}

/// Requests one fixed ACL connection interval together with peripheral latency and
/// supervision timeout.
class WirelessAudioConfigurationFixedAclPolicy implements WirelessAudioConfigurationAclConnectionPolicyPolicy {
  /// Creates a WirelessAudioConfigurationFixedAclPolicy value.
  WirelessAudioConfigurationFixedAclPolicy({required this.interval_us, required this.peripheral_latency, required this.supervision_timeout_ms});

  final int interval_us;
  final int peripheral_latency;
  final int supervision_timeout_ms;

  /// Decodes a complete WirelessAudioConfigurationFixedAclPolicy value from [bytes].
  factory WirelessAudioConfigurationFixedAclPolicy.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationFixedAclPolicy._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationFixedAclPolicy _read(ProtocolReader reader) {
    final interval_us = reader.uint32();
    final peripheral_latency = reader.uint16();
    final supervision_timeout_ms = reader.uint32();
    return WirelessAudioConfigurationFixedAclPolicy(interval_us: interval_us, peripheral_latency: peripheral_latency, supervision_timeout_ms: supervision_timeout_ms);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint32(interval_us);
    writer.uint16(peripheral_latency);
    writer.uint32(supervision_timeout_ms);
  }
}

/// Requests an ACL connection interval within a preferred range together with peripheral
/// latency and supervision timeout.
class WirelessAudioConfigurationPreferredRangeAclPolicy implements WirelessAudioConfigurationAclConnectionPolicyPolicy {
  /// Creates a WirelessAudioConfigurationPreferredRangeAclPolicy value.
  WirelessAudioConfigurationPreferredRangeAclPolicy({required this.minimum_interval_us, required this.maximum_interval_us, required this.peripheral_latency, required this.supervision_timeout_ms});

  final int minimum_interval_us;
  final int maximum_interval_us;
  final int peripheral_latency;
  final int supervision_timeout_ms;

  /// Decodes a complete WirelessAudioConfigurationPreferredRangeAclPolicy value from [bytes].
  factory WirelessAudioConfigurationPreferredRangeAclPolicy.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationPreferredRangeAclPolicy._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationPreferredRangeAclPolicy _read(ProtocolReader reader) {
    final minimum_interval_us = reader.uint32();
    final maximum_interval_us = reader.uint32();
    final peripheral_latency = reader.uint16();
    final supervision_timeout_ms = reader.uint32();
    return WirelessAudioConfigurationPreferredRangeAclPolicy(minimum_interval_us: minimum_interval_us, maximum_interval_us: maximum_interval_us, peripheral_latency: peripheral_latency, supervision_timeout_ms: supervision_timeout_ms);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint32(minimum_interval_us);
    writer.uint32(maximum_interval_us);
    writer.uint16(peripheral_latency);
    writer.uint32(supervision_timeout_ms);
  }
}

/// Increases the ACL interval by a fixed step after an audio underrun episode and decreases
/// it periodically while audio is stable.
class WirelessAudioConfigurationAdaptiveLinearAclPolicy implements WirelessAudioConfigurationAclConnectionPolicyPolicy {
  /// Creates a WirelessAudioConfigurationAdaptiveLinearAclPolicy value.
  WirelessAudioConfigurationAdaptiveLinearAclPolicy({required this.minimum_interval_us, required this.maximum_interval_us, required this.underrun_increase_step_us, required this.recovery_decrease_step_us, required this.recovery_period_ms, required this.minimum_update_period_ms, required this.peripheral_latency, required this.supervision_timeout_ms});

  final int minimum_interval_us;
  final int maximum_interval_us;
  final int underrun_increase_step_us;
  final int recovery_decrease_step_us;
  final int recovery_period_ms;
  final int minimum_update_period_ms;
  final int peripheral_latency;
  final int supervision_timeout_ms;

  /// Decodes a complete WirelessAudioConfigurationAdaptiveLinearAclPolicy value from [bytes].
  factory WirelessAudioConfigurationAdaptiveLinearAclPolicy.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationAdaptiveLinearAclPolicy._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationAdaptiveLinearAclPolicy _read(ProtocolReader reader) {
    final minimum_interval_us = reader.uint32();
    final maximum_interval_us = reader.uint32();
    final underrun_increase_step_us = reader.uint32();
    final recovery_decrease_step_us = reader.uint32();
    final recovery_period_ms = reader.uint32();
    final minimum_update_period_ms = reader.uint32();
    final peripheral_latency = reader.uint16();
    final supervision_timeout_ms = reader.uint32();
    return WirelessAudioConfigurationAdaptiveLinearAclPolicy(minimum_interval_us: minimum_interval_us, maximum_interval_us: maximum_interval_us, underrun_increase_step_us: underrun_increase_step_us, recovery_decrease_step_us: recovery_decrease_step_us, recovery_period_ms: recovery_period_ms, minimum_update_period_ms: minimum_update_period_ms, peripheral_latency: peripheral_latency, supervision_timeout_ms: supervision_timeout_ms);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint32(minimum_interval_us);
    writer.uint32(maximum_interval_us);
    writer.uint32(underrun_increase_step_us);
    writer.uint32(recovery_decrease_step_us);
    writer.uint32(recovery_period_ms);
    writer.uint32(minimum_update_period_ms);
    writer.uint16(peripheral_latency);
    writer.uint32(supervision_timeout_ms);
  }
}

/// A tagged local ACL request policy; the peer or controller may negotiate different
/// effective parameters.
class WirelessAudioConfigurationAclConnectionPolicy {
  /// Creates a WirelessAudioConfigurationAclConnectionPolicy value.
  WirelessAudioConfigurationAclConnectionPolicy({required this.policy});

  /// Creates a WirelessAudioConfigurationAclConnectionPolicy containing WirelessAudioConfigurationControllerDefaultAclPolicy.
  factory WirelessAudioConfigurationAclConnectionPolicy.controllerDefaultAclPolicy(WirelessAudioConfigurationControllerDefaultAclPolicy command) =>
      WirelessAudioConfigurationAclConnectionPolicy(policy: command);

  /// Creates a WirelessAudioConfigurationAclConnectionPolicy containing WirelessAudioConfigurationFixedAclPolicy.
  factory WirelessAudioConfigurationAclConnectionPolicy.fixedAclPolicy(WirelessAudioConfigurationFixedAclPolicy command) =>
      WirelessAudioConfigurationAclConnectionPolicy(policy: command);

  /// Creates a WirelessAudioConfigurationAclConnectionPolicy containing WirelessAudioConfigurationPreferredRangeAclPolicy.
  factory WirelessAudioConfigurationAclConnectionPolicy.preferredRangeAclPolicy(WirelessAudioConfigurationPreferredRangeAclPolicy command) =>
      WirelessAudioConfigurationAclConnectionPolicy(policy: command);

  /// Creates a WirelessAudioConfigurationAclConnectionPolicy containing WirelessAudioConfigurationAdaptiveLinearAclPolicy.
  factory WirelessAudioConfigurationAclConnectionPolicy.adaptiveLinearAclPolicy(WirelessAudioConfigurationAdaptiveLinearAclPolicy command) =>
      WirelessAudioConfigurationAclConnectionPolicy(policy: command);

  final WirelessAudioConfigurationAclConnectionPolicyPolicy policy;

  /// Decodes a complete WirelessAudioConfigurationAclConnectionPolicy value from [bytes].
  factory WirelessAudioConfigurationAclConnectionPolicy.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationAclConnectionPolicy._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationAclConnectionPolicy _read(ProtocolReader reader) {
    final policyType = reader.uint8();
    final WirelessAudioConfigurationAclConnectionPolicyPolicy policy;
    switch (policyType) {
      case 0:
        policy = WirelessAudioConfigurationControllerDefaultAclPolicy._read(reader);
        break;
      case 1:
        policy = WirelessAudioConfigurationFixedAclPolicy._read(reader);
        break;
      case 2:
        policy = WirelessAudioConfigurationPreferredRangeAclPolicy._read(reader);
        break;
      case 3:
        policy = WirelessAudioConfigurationAdaptiveLinearAclPolicy._read(reader);
        break;
      default:
        throw ProtocolFormatException('unknown union discriminator ${policyType}');
    }
    return WirelessAudioConfigurationAclConnectionPolicy(policy: policy);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    if (policy is WirelessAudioConfigurationControllerDefaultAclPolicy) {
      writer.uint8(0);
      (policy as WirelessAudioConfigurationControllerDefaultAclPolicy)._write(writer);
      return;
    }
    if (policy is WirelessAudioConfigurationFixedAclPolicy) {
      writer.uint8(1);
      (policy as WirelessAudioConfigurationFixedAclPolicy)._write(writer);
      return;
    }
    if (policy is WirelessAudioConfigurationPreferredRangeAclPolicy) {
      writer.uint8(2);
      (policy as WirelessAudioConfigurationPreferredRangeAclPolicy)._write(writer);
      return;
    }
    if (policy is WirelessAudioConfigurationAdaptiveLinearAclPolicy) {
      writer.uint8(3);
      (policy as WirelessAudioConfigurationAdaptiveLinearAclPolicy)._write(writer);
      return;
    }
    throw ProtocolFormatException('unsupported union payload: ${policy.runtimeType}');
  }
}

/// Leaves ACL PHY and data length selection to the Bluetooth stack; reserved must be zero.
class WirelessAudioConfigurationAutomaticAclRadioPolicy implements WirelessAudioConfigurationAclRadioPolicyPolicy {
  /// Creates a WirelessAudioConfigurationAutomaticAclRadioPolicy value.
  WirelessAudioConfigurationAutomaticAclRadioPolicy({required this.reserved});

  final int reserved;

  /// Decodes a complete WirelessAudioConfigurationAutomaticAclRadioPolicy value from [bytes].
  factory WirelessAudioConfigurationAutomaticAclRadioPolicy.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationAutomaticAclRadioPolicy._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationAutomaticAclRadioPolicy _read(ProtocolReader reader) {
    final reserved = reader.uint8();
    return WirelessAudioConfigurationAutomaticAclRadioPolicy(reserved: reserved);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(reserved);
  }
}

/// Requests ACL PHY and transmit data length preferences; zero values leave the
/// corresponding setting to the Bluetooth stack.
class WirelessAudioConfigurationPreferredAclRadioPolicy implements WirelessAudioConfigurationAclRadioPolicyPolicy {
  /// Creates a WirelessAudioConfigurationPreferredAclRadioPolicy value.
  WirelessAudioConfigurationPreferredAclRadioPolicy({required this.transmit_phy_mask, required this.receive_phy_mask, required this.transmit_max_data_octets, required this.transmit_max_time_us});

  final int transmit_phy_mask;
  final int receive_phy_mask;
  final int transmit_max_data_octets;
  final int transmit_max_time_us;

  /// Decodes a complete WirelessAudioConfigurationPreferredAclRadioPolicy value from [bytes].
  factory WirelessAudioConfigurationPreferredAclRadioPolicy.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationPreferredAclRadioPolicy._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationPreferredAclRadioPolicy _read(ProtocolReader reader) {
    final transmit_phy_mask = reader.uint8();
    final receive_phy_mask = reader.uint8();
    final transmit_max_data_octets = reader.uint16();
    final transmit_max_time_us = reader.uint16();
    return WirelessAudioConfigurationPreferredAclRadioPolicy(transmit_phy_mask: transmit_phy_mask, receive_phy_mask: receive_phy_mask, transmit_max_data_octets: transmit_max_data_octets, transmit_max_time_us: transmit_max_time_us);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(transmit_phy_mask);
    writer.uint8(receive_phy_mask);
    writer.uint16(transmit_max_data_octets);
    writer.uint16(transmit_max_time_us);
  }
}

/// A tagged local ACL radio policy. Type 0 is automatic and type 1 requests explicit
/// preferences.
class WirelessAudioConfigurationAclRadioPolicy {
  /// Creates a WirelessAudioConfigurationAclRadioPolicy value.
  WirelessAudioConfigurationAclRadioPolicy({required this.policy});

  /// Creates a WirelessAudioConfigurationAclRadioPolicy containing WirelessAudioConfigurationAutomaticAclRadioPolicy.
  factory WirelessAudioConfigurationAclRadioPolicy.automaticAclRadioPolicy(WirelessAudioConfigurationAutomaticAclRadioPolicy command) =>
      WirelessAudioConfigurationAclRadioPolicy(policy: command);

  /// Creates a WirelessAudioConfigurationAclRadioPolicy containing WirelessAudioConfigurationPreferredAclRadioPolicy.
  factory WirelessAudioConfigurationAclRadioPolicy.preferredAclRadioPolicy(WirelessAudioConfigurationPreferredAclRadioPolicy command) =>
      WirelessAudioConfigurationAclRadioPolicy(policy: command);

  final WirelessAudioConfigurationAclRadioPolicyPolicy policy;

  /// Decodes a complete WirelessAudioConfigurationAclRadioPolicy value from [bytes].
  factory WirelessAudioConfigurationAclRadioPolicy.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationAclRadioPolicy._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationAclRadioPolicy _read(ProtocolReader reader) {
    final policyType = reader.uint8();
    final WirelessAudioConfigurationAclRadioPolicyPolicy policy;
    switch (policyType) {
      case 0:
        policy = WirelessAudioConfigurationAutomaticAclRadioPolicy._read(reader);
        break;
      case 1:
        policy = WirelessAudioConfigurationPreferredAclRadioPolicy._read(reader);
        break;
      default:
        throw ProtocolFormatException('unknown union discriminator ${policyType}');
    }
    return WirelessAudioConfigurationAclRadioPolicy(policy: policy);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    if (policy is WirelessAudioConfigurationAutomaticAclRadioPolicy) {
      writer.uint8(0);
      (policy as WirelessAudioConfigurationAutomaticAclRadioPolicy)._write(writer);
      return;
    }
    if (policy is WirelessAudioConfigurationPreferredAclRadioPolicy) {
      writer.uint8(1);
      (policy as WirelessAudioConfigurationPreferredAclRadioPolicy)._write(writer);
      return;
    }
    throw ProtocolFormatException('unsupported union payload: ${policy.runtimeType}');
  }
}

/// Local preferences returned by the Unicast Server after a standard ASCS Config Codec
/// operation; these do not configure the CIS.
class WirelessAudioConfigurationUnicastServerQosPreferences {
  /// Creates a WirelessAudioConfigurationUnicastServerQosPreferences value.
  WirelessAudioConfigurationUnicastServerQosPreferences({required this.direction_mask, required this.unframed_supported, required this.preferred_phy_mask, required this.preferred_retransmission_number, required this.maximum_transport_latency_ms, required this.minimum_presentation_delay_us, required this.maximum_presentation_delay_us, required this.preferred_minimum_presentation_delay_us, required this.preferred_maximum_presentation_delay_us});

  final int direction_mask;
  final int unframed_supported;
  final int preferred_phy_mask;
  final int preferred_retransmission_number;
  final int maximum_transport_latency_ms;
  final int minimum_presentation_delay_us;
  final int maximum_presentation_delay_us;
  final int preferred_minimum_presentation_delay_us;
  final int preferred_maximum_presentation_delay_us;

  /// Decodes a complete WirelessAudioConfigurationUnicastServerQosPreferences value from [bytes].
  factory WirelessAudioConfigurationUnicastServerQosPreferences.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationUnicastServerQosPreferences._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationUnicastServerQosPreferences _read(ProtocolReader reader) {
    final direction_mask = reader.uint8();
    final unframed_supported = reader.uint8();
    final preferred_phy_mask = reader.uint8();
    final preferred_retransmission_number = reader.uint8();
    final maximum_transport_latency_ms = reader.uint16();
    final minimum_presentation_delay_us = reader.uint32();
    final maximum_presentation_delay_us = reader.uint32();
    final preferred_minimum_presentation_delay_us = reader.uint32();
    final preferred_maximum_presentation_delay_us = reader.uint32();
    return WirelessAudioConfigurationUnicastServerQosPreferences(direction_mask: direction_mask, unframed_supported: unframed_supported, preferred_phy_mask: preferred_phy_mask, preferred_retransmission_number: preferred_retransmission_number, maximum_transport_latency_ms: maximum_transport_latency_ms, minimum_presentation_delay_us: minimum_presentation_delay_us, maximum_presentation_delay_us: maximum_presentation_delay_us, preferred_minimum_presentation_delay_us: preferred_minimum_presentation_delay_us, preferred_maximum_presentation_delay_us: preferred_maximum_presentation_delay_us);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(direction_mask);
    writer.uint8(unframed_supported);
    writer.uint8(preferred_phy_mask);
    writer.uint8(preferred_retransmission_number);
    writer.uint16(maximum_transport_latency_ms);
    writer.uint32(minimum_presentation_delay_us);
    writer.uint32(maximum_presentation_delay_us);
    writer.uint32(preferred_minimum_presentation_delay_us);
    writer.uint32(preferred_maximum_presentation_delay_us);
  }
}

/// Selects the ACL connection policy and optionally persists it across restarts.
class WirelessAudioConfigurationSetAclConnectionPolicy implements WirelessAudioConfigurationConfigurationCommandOperation {
  /// Creates a WirelessAudioConfigurationSetAclConnectionPolicy value.
  WirelessAudioConfigurationSetAclConnectionPolicy({required this.persist, required this.policy});

  final int persist;
  final WirelessAudioConfigurationAclConnectionPolicy policy;

  /// Decodes a complete WirelessAudioConfigurationSetAclConnectionPolicy value from [bytes].
  factory WirelessAudioConfigurationSetAclConnectionPolicy.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationSetAclConnectionPolicy._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationSetAclConnectionPolicy _read(ProtocolReader reader) {
    final persist = reader.uint8();
    final policy = WirelessAudioConfigurationAclConnectionPolicy._read(reader);
    return WirelessAudioConfigurationSetAclConnectionPolicy(persist: persist, policy: policy);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(persist);
    policy._write(writer);
  }
}

/// Sets the local ACL PHY and data length request policy and optionally persists it across
/// restarts.
class WirelessAudioConfigurationSetAclRadioPolicy implements WirelessAudioConfigurationConfigurationCommandOperation {
  /// Creates a WirelessAudioConfigurationSetAclRadioPolicy value.
  WirelessAudioConfigurationSetAclRadioPolicy({required this.persist, required this.policy});

  final int persist;
  final WirelessAudioConfigurationAclRadioPolicy policy;

  /// Decodes a complete WirelessAudioConfigurationSetAclRadioPolicy value from [bytes].
  factory WirelessAudioConfigurationSetAclRadioPolicy.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationSetAclRadioPolicy._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationSetAclRadioPolicy _read(ProtocolReader reader) {
    final persist = reader.uint8();
    final policy = WirelessAudioConfigurationAclRadioPolicy._read(reader);
    return WirelessAudioConfigurationSetAclRadioPolicy(persist: persist, policy: policy);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(persist);
    policy._write(writer);
  }
}

/// Sets preferences returned during future ASCS codec configuration operations and
/// optionally persists them across restarts.
class WirelessAudioConfigurationSetUnicastServerQosPreferences implements WirelessAudioConfigurationConfigurationCommandOperation {
  /// Creates a WirelessAudioConfigurationSetUnicastServerQosPreferences value.
  WirelessAudioConfigurationSetUnicastServerQosPreferences({required this.persist, required this.preferences});

  final int persist;
  final WirelessAudioConfigurationUnicastServerQosPreferences preferences;

  /// Decodes a complete WirelessAudioConfigurationSetUnicastServerQosPreferences value from [bytes].
  factory WirelessAudioConfigurationSetUnicastServerQosPreferences.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationSetUnicastServerQosPreferences._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationSetUnicastServerQosPreferences _read(ProtocolReader reader) {
    final persist = reader.uint8();
    final preferences = WirelessAudioConfigurationUnicastServerQosPreferences._read(reader);
    return WirelessAudioConfigurationSetUnicastServerQosPreferences(persist: persist, preferences: preferences);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(persist);
    preferences._write(writer);
  }
}

/// Requests the configured value for one section identified by its stable section ID.
class WirelessAudioConfigurationGetConfiguration implements WirelessAudioConfigurationConfigurationCommandOperation {
  /// Creates a WirelessAudioConfigurationGetConfiguration value.
  WirelessAudioConfigurationGetConfiguration({required this.section});

  final int section;

  /// Decodes a complete WirelessAudioConfigurationGetConfiguration value from [bytes].
  factory WirelessAudioConfigurationGetConfiguration.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationGetConfiguration._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationGetConfiguration _read(ProtocolReader reader) {
    final section = reader.uint8();
    return WirelessAudioConfigurationGetConfiguration(section: section);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(section);
  }
}

/// Restores compiled defaults for the sections selected by section_mask, or every supported
/// section when the mask is zero.
class WirelessAudioConfigurationRestoreDefaults implements WirelessAudioConfigurationConfigurationCommandOperation {
  /// Creates a WirelessAudioConfigurationRestoreDefaults value.
  WirelessAudioConfigurationRestoreDefaults({required this.section_mask});

  final int section_mask;

  /// Decodes a complete WirelessAudioConfigurationRestoreDefaults value from [bytes].
  factory WirelessAudioConfigurationRestoreDefaults.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationRestoreDefaults._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationRestoreDefaults _read(ProtocolReader reader) {
    final section_mask = reader.uint32();
    return WirelessAudioConfigurationRestoreDefaults(section_mask: section_mask);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint32(section_mask);
  }
}

/// A correlated wireless audio configuration command with a stable tagged operation.
class WirelessAudioConfigurationConfigurationCommand {
  /// Creates a WirelessAudioConfigurationConfigurationCommand value.
  WirelessAudioConfigurationConfigurationCommand({required this.request_id, required this.operation});

  final int request_id;
  final WirelessAudioConfigurationConfigurationCommandOperation operation;

  /// Decodes a complete WirelessAudioConfigurationConfigurationCommand value from [bytes].
  factory WirelessAudioConfigurationConfigurationCommand.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationConfigurationCommand._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationConfigurationCommand _read(ProtocolReader reader) {
    final request_id = reader.uint16();
    final operationType = reader.uint8();
    final WirelessAudioConfigurationConfigurationCommandOperation operation;
    switch (operationType) {
      case 0:
        operation = WirelessAudioConfigurationSetAclConnectionPolicy._read(reader);
        break;
      case 1:
        operation = WirelessAudioConfigurationSetAclRadioPolicy._read(reader);
        break;
      case 2:
        operation = WirelessAudioConfigurationSetUnicastServerQosPreferences._read(reader);
        break;
      case 3:
        operation = WirelessAudioConfigurationGetConfiguration._read(reader);
        break;
      case 4:
        operation = WirelessAudioConfigurationRestoreDefaults._read(reader);
        break;
      default:
        throw ProtocolFormatException('unknown union discriminator ${operationType}');
    }
    return WirelessAudioConfigurationConfigurationCommand(request_id: request_id, operation: operation);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint16(request_id);
    if (operation is WirelessAudioConfigurationSetAclConnectionPolicy) {
      writer.uint8(0);
      (operation as WirelessAudioConfigurationSetAclConnectionPolicy)._write(writer);
      return;
    }
    if (operation is WirelessAudioConfigurationSetAclRadioPolicy) {
      writer.uint8(1);
      (operation as WirelessAudioConfigurationSetAclRadioPolicy)._write(writer);
      return;
    }
    if (operation is WirelessAudioConfigurationSetUnicastServerQosPreferences) {
      writer.uint8(2);
      (operation as WirelessAudioConfigurationSetUnicastServerQosPreferences)._write(writer);
      return;
    }
    if (operation is WirelessAudioConfigurationGetConfiguration) {
      writer.uint8(3);
      (operation as WirelessAudioConfigurationGetConfiguration)._write(writer);
      return;
    }
    if (operation is WirelessAudioConfigurationRestoreDefaults) {
      writer.uint8(4);
      (operation as WirelessAudioConfigurationRestoreDefaults)._write(writer);
      return;
    }
    throw ProtocolFormatException('unsupported union payload: ${operation.runtimeType}');
  }
}

/// Reports the configured ACL connection policy and whether it is persistent.
class WirelessAudioConfigurationConfiguredAclConnectionPolicy implements WirelessAudioConfigurationConfigurationResponsePayload {
  /// Creates a WirelessAudioConfigurationConfiguredAclConnectionPolicy value.
  WirelessAudioConfigurationConfiguredAclConnectionPolicy({required this.persisted, required this.policy});

  final int persisted;
  final WirelessAudioConfigurationAclConnectionPolicy policy;

  /// Decodes a complete WirelessAudioConfigurationConfiguredAclConnectionPolicy value from [bytes].
  factory WirelessAudioConfigurationConfiguredAclConnectionPolicy.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationConfiguredAclConnectionPolicy._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationConfiguredAclConnectionPolicy _read(ProtocolReader reader) {
    final persisted = reader.uint8();
    final policy = WirelessAudioConfigurationAclConnectionPolicy._read(reader);
    return WirelessAudioConfigurationConfiguredAclConnectionPolicy(persisted: persisted, policy: policy);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(persisted);
    policy._write(writer);
  }
}

/// Reports the configured local ACL radio policy and whether it is persistent.
class WirelessAudioConfigurationConfiguredAclRadioPolicy implements WirelessAudioConfigurationConfigurationResponsePayload {
  /// Creates a WirelessAudioConfigurationConfiguredAclRadioPolicy value.
  WirelessAudioConfigurationConfiguredAclRadioPolicy({required this.persisted, required this.policy});

  final int persisted;
  final WirelessAudioConfigurationAclRadioPolicy policy;

  /// Decodes a complete WirelessAudioConfigurationConfiguredAclRadioPolicy value from [bytes].
  factory WirelessAudioConfigurationConfiguredAclRadioPolicy.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationConfiguredAclRadioPolicy._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationConfiguredAclRadioPolicy _read(ProtocolReader reader) {
    final persisted = reader.uint8();
    final policy = WirelessAudioConfigurationAclRadioPolicy._read(reader);
    return WirelessAudioConfigurationConfiguredAclRadioPolicy(persisted: persisted, policy: policy);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(persisted);
    policy._write(writer);
  }
}

/// Reports the preferences returned by the server during ASCS codec configuration and
/// whether they are persistent.
class WirelessAudioConfigurationConfiguredUnicastServerQosPreferences implements WirelessAudioConfigurationConfigurationResponsePayload {
  /// Creates a WirelessAudioConfigurationConfiguredUnicastServerQosPreferences value.
  WirelessAudioConfigurationConfiguredUnicastServerQosPreferences({required this.persisted, required this.preferences});

  final int persisted;
  final WirelessAudioConfigurationUnicastServerQosPreferences preferences;

  /// Decodes a complete WirelessAudioConfigurationConfiguredUnicastServerQosPreferences value from [bytes].
  factory WirelessAudioConfigurationConfiguredUnicastServerQosPreferences.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationConfiguredUnicastServerQosPreferences._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationConfiguredUnicastServerQosPreferences _read(ProtocolReader reader) {
    final persisted = reader.uint8();
    final preferences = WirelessAudioConfigurationUnicastServerQosPreferences._read(reader);
    return WirelessAudioConfigurationConfiguredUnicastServerQosPreferences(persisted: persisted, preferences: preferences);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(persisted);
    preferences._write(writer);
  }
}

/// Reports whether a command was accepted and whether applying it requires a connection or
/// stream restart.
class WirelessAudioConfigurationCommandResult implements WirelessAudioConfigurationConfigurationResponsePayload {
  /// Creates a WirelessAudioConfigurationCommandResult value.
  WirelessAudioConfigurationCommandResult({required this.status, required this.error_domain, required this.error_code, required this.restart_required_mask});

  final int status;
  final int error_domain;
  final int error_code;
  final int restart_required_mask;

  /// Decodes a complete WirelessAudioConfigurationCommandResult value from [bytes].
  factory WirelessAudioConfigurationCommandResult.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationCommandResult._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationCommandResult _read(ProtocolReader reader) {
    final status = reader.uint8();
    final error_domain = reader.uint8();
    final error_code = reader.int32();
    final restart_required_mask = reader.uint32();
    return WirelessAudioConfigurationCommandResult(status: status, error_domain: error_domain, error_code: error_code, restart_required_mask: restart_required_mask);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint8(status);
    writer.uint8(error_domain);
    writer.int32(error_code);
    writer.uint32(restart_required_mask);
  }
}

/// A response correlated to a configuration command. Type 0 is a command result and types 1
/// through 3 report one policy section.
class WirelessAudioConfigurationConfigurationResponse {
  /// Creates a WirelessAudioConfigurationConfigurationResponse value.
  WirelessAudioConfigurationConfigurationResponse({required this.request_id, required this.payload});

  final int request_id;
  final WirelessAudioConfigurationConfigurationResponsePayload payload;

  /// Decodes a complete WirelessAudioConfigurationConfigurationResponse value from [bytes].
  factory WirelessAudioConfigurationConfigurationResponse.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationConfigurationResponse._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationConfigurationResponse _read(ProtocolReader reader) {
    final request_id = reader.uint16();
    final payloadType = reader.uint8();
    final WirelessAudioConfigurationConfigurationResponsePayload payload;
    switch (payloadType) {
      case 0:
        payload = WirelessAudioConfigurationCommandResult._read(reader);
        break;
      case 1:
        payload = WirelessAudioConfigurationConfiguredAclConnectionPolicy._read(reader);
        break;
      case 2:
        payload = WirelessAudioConfigurationConfiguredAclRadioPolicy._read(reader);
        break;
      case 3:
        payload = WirelessAudioConfigurationConfiguredUnicastServerQosPreferences._read(reader);
        break;
      default:
        throw ProtocolFormatException('unknown union discriminator ${payloadType}');
    }
    return WirelessAudioConfigurationConfigurationResponse(request_id: request_id, payload: payload);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint16(request_id);
    if (payload is WirelessAudioConfigurationCommandResult) {
      writer.uint8(0);
      (payload as WirelessAudioConfigurationCommandResult)._write(writer);
      return;
    }
    if (payload is WirelessAudioConfigurationConfiguredAclConnectionPolicy) {
      writer.uint8(1);
      (payload as WirelessAudioConfigurationConfiguredAclConnectionPolicy)._write(writer);
      return;
    }
    if (payload is WirelessAudioConfigurationConfiguredAclRadioPolicy) {
      writer.uint8(2);
      (payload as WirelessAudioConfigurationConfiguredAclRadioPolicy)._write(writer);
      return;
    }
    if (payload is WirelessAudioConfigurationConfiguredUnicastServerQosPreferences) {
      writer.uint8(3);
      (payload as WirelessAudioConfigurationConfiguredUnicastServerQosPreferences)._write(writer);
      return;
    }
    throw ProtocolFormatException('unsupported union payload: ${payload.runtimeType}');
  }
}

/// Read-only observation of effective ACL parameters and the LC3 and ISO QoS values
/// negotiated through PACS and ASCS for one connection and stream; fields without a
/// corresponding validity flag are zero.
class WirelessAudioConfigurationRuntimeState {
  /// Creates a WirelessAudioConfigurationRuntimeState value.
  WirelessAudioConfigurationRuntimeState({required this.sequence, required this.validity_flags, required this.connection_id, required this.stream_id, required this.direction, required this.lifecycle_state, required this.acl_interval_us, required this.acl_peripheral_latency, required this.acl_supervision_timeout_ms, required this.transmit_phy, required this.receive_phy, required this.transmit_data_octets, required this.receive_data_octets, required this.lc3_sampling_frequency_hz, required this.lc3_frame_duration_us, required this.lc3_octets_per_frame, required this.lc3_frame_blocks_per_sdu, required this.lc3_channel_allocation, required this.iso_sdu_interval_us, required this.iso_framing, required this.iso_phy, required this.iso_retransmission_number, required this.iso_maximum_sdu_octets, required this.iso_maximum_transport_latency_ms, required this.presentation_delay_us, required this.audio_underrun_count, required this.acl_adjustment_count});

  final int sequence;
  final int validity_flags;
  final int connection_id;
  final int stream_id;
  final int direction;
  final int lifecycle_state;
  final int acl_interval_us;
  final int acl_peripheral_latency;
  final int acl_supervision_timeout_ms;
  final int transmit_phy;
  final int receive_phy;
  final int transmit_data_octets;
  final int receive_data_octets;
  final int lc3_sampling_frequency_hz;
  final int lc3_frame_duration_us;
  final int lc3_octets_per_frame;
  final int lc3_frame_blocks_per_sdu;
  final int lc3_channel_allocation;
  final int iso_sdu_interval_us;
  final int iso_framing;
  final int iso_phy;
  final int iso_retransmission_number;
  final int iso_maximum_sdu_octets;
  final int iso_maximum_transport_latency_ms;
  final int presentation_delay_us;
  final int audio_underrun_count;
  final int acl_adjustment_count;

  /// Decodes a complete WirelessAudioConfigurationRuntimeState value from [bytes].
  factory WirelessAudioConfigurationRuntimeState.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationRuntimeState._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationRuntimeState _read(ProtocolReader reader) {
    final sequence = reader.uint32();
    final validity_flags = reader.uint32();
    final connection_id = reader.uint16();
    final stream_id = reader.uint8();
    final direction = reader.uint8();
    final lifecycle_state = reader.uint8();
    final acl_interval_us = reader.uint32();
    final acl_peripheral_latency = reader.uint16();
    final acl_supervision_timeout_ms = reader.uint32();
    final transmit_phy = reader.uint8();
    final receive_phy = reader.uint8();
    final transmit_data_octets = reader.uint16();
    final receive_data_octets = reader.uint16();
    final lc3_sampling_frequency_hz = reader.uint32();
    final lc3_frame_duration_us = reader.uint16();
    final lc3_octets_per_frame = reader.uint16();
    final lc3_frame_blocks_per_sdu = reader.uint8();
    final lc3_channel_allocation = reader.uint32();
    final iso_sdu_interval_us = reader.uint32();
    final iso_framing = reader.uint8();
    final iso_phy = reader.uint8();
    final iso_retransmission_number = reader.uint8();
    final iso_maximum_sdu_octets = reader.uint16();
    final iso_maximum_transport_latency_ms = reader.uint16();
    final presentation_delay_us = reader.uint32();
    final audio_underrun_count = reader.uint32();
    final acl_adjustment_count = reader.uint32();
    return WirelessAudioConfigurationRuntimeState(sequence: sequence, validity_flags: validity_flags, connection_id: connection_id, stream_id: stream_id, direction: direction, lifecycle_state: lifecycle_state, acl_interval_us: acl_interval_us, acl_peripheral_latency: acl_peripheral_latency, acl_supervision_timeout_ms: acl_supervision_timeout_ms, transmit_phy: transmit_phy, receive_phy: receive_phy, transmit_data_octets: transmit_data_octets, receive_data_octets: receive_data_octets, lc3_sampling_frequency_hz: lc3_sampling_frequency_hz, lc3_frame_duration_us: lc3_frame_duration_us, lc3_octets_per_frame: lc3_octets_per_frame, lc3_frame_blocks_per_sdu: lc3_frame_blocks_per_sdu, lc3_channel_allocation: lc3_channel_allocation, iso_sdu_interval_us: iso_sdu_interval_us, iso_framing: iso_framing, iso_phy: iso_phy, iso_retransmission_number: iso_retransmission_number, iso_maximum_sdu_octets: iso_maximum_sdu_octets, iso_maximum_transport_latency_ms: iso_maximum_transport_latency_ms, presentation_delay_us: presentation_delay_us, audio_underrun_count: audio_underrun_count, acl_adjustment_count: acl_adjustment_count);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint32(sequence);
    writer.uint32(validity_flags);
    writer.uint16(connection_id);
    writer.uint8(stream_id);
    writer.uint8(direction);
    writer.uint8(lifecycle_state);
    writer.uint32(acl_interval_us);
    writer.uint16(acl_peripheral_latency);
    writer.uint32(acl_supervision_timeout_ms);
    writer.uint8(transmit_phy);
    writer.uint8(receive_phy);
    writer.uint16(transmit_data_octets);
    writer.uint16(receive_data_octets);
    writer.uint32(lc3_sampling_frequency_hz);
    writer.uint16(lc3_frame_duration_us);
    writer.uint16(lc3_octets_per_frame);
    writer.uint8(lc3_frame_blocks_per_sdu);
    writer.uint32(lc3_channel_allocation);
    writer.uint32(iso_sdu_interval_us);
    writer.uint8(iso_framing);
    writer.uint8(iso_phy);
    writer.uint8(iso_retransmission_number);
    writer.uint16(iso_maximum_sdu_octets);
    writer.uint16(iso_maximum_transport_latency_ms);
    writer.uint32(presentation_delay_us);
    writer.uint32(audio_underrun_count);
    writer.uint32(acl_adjustment_count);
  }
}

/// Reports supported custom policy sections and value ranges for this firmware build and
/// controller; standard LC3 capabilities are exposed through PACS.
class WirelessAudioConfigurationCapabilities {
  /// Creates a WirelessAudioConfigurationCapabilities value.
  WirelessAudioConfigurationCapabilities({required this.protocol_version, required this.supported_section_mask, required this.supported_command_mask, required this.supported_acl_policy_mask, required this.supported_phy_mask, required this.minimum_acl_interval_us, required this.maximum_acl_interval_us, required this.acl_interval_resolution_us, required this.maximum_acl_peripheral_latency, required this.minimum_acl_supervision_timeout_ms, required this.maximum_acl_supervision_timeout_ms, required this.minimum_acl_data_octets, required this.maximum_acl_data_octets, required this.minimum_acl_data_time_us, required this.maximum_acl_data_time_us, required this.supported_audio_direction_mask, required this.maximum_preferred_retransmission_number, required this.maximum_transport_latency_ms, required this.minimum_presentation_delay_us, required this.maximum_presentation_delay_us, required this.feature_flags});

  final int protocol_version;
  final int supported_section_mask;
  final int supported_command_mask;
  final int supported_acl_policy_mask;
  final int supported_phy_mask;
  final int minimum_acl_interval_us;
  final int maximum_acl_interval_us;
  final int acl_interval_resolution_us;
  final int maximum_acl_peripheral_latency;
  final int minimum_acl_supervision_timeout_ms;
  final int maximum_acl_supervision_timeout_ms;
  final int minimum_acl_data_octets;
  final int maximum_acl_data_octets;
  final int minimum_acl_data_time_us;
  final int maximum_acl_data_time_us;
  final int supported_audio_direction_mask;
  final int maximum_preferred_retransmission_number;
  final int maximum_transport_latency_ms;
  final int minimum_presentation_delay_us;
  final int maximum_presentation_delay_us;
  final int feature_flags;

  /// Decodes a complete WirelessAudioConfigurationCapabilities value from [bytes].
  factory WirelessAudioConfigurationCapabilities.fromBytes(Uint8List bytes) {
    final reader = ProtocolReader(bytes);
    final value = WirelessAudioConfigurationCapabilities._read(reader);
    reader.finish();
    return value;
  }

  static WirelessAudioConfigurationCapabilities _read(ProtocolReader reader) {
    final protocol_version = reader.uint16();
    final supported_section_mask = reader.uint32();
    final supported_command_mask = reader.uint32();
    final supported_acl_policy_mask = reader.uint32();
    final supported_phy_mask = reader.uint8();
    final minimum_acl_interval_us = reader.uint32();
    final maximum_acl_interval_us = reader.uint32();
    final acl_interval_resolution_us = reader.uint32();
    final maximum_acl_peripheral_latency = reader.uint16();
    final minimum_acl_supervision_timeout_ms = reader.uint32();
    final maximum_acl_supervision_timeout_ms = reader.uint32();
    final minimum_acl_data_octets = reader.uint16();
    final maximum_acl_data_octets = reader.uint16();
    final minimum_acl_data_time_us = reader.uint16();
    final maximum_acl_data_time_us = reader.uint16();
    final supported_audio_direction_mask = reader.uint8();
    final maximum_preferred_retransmission_number = reader.uint8();
    final maximum_transport_latency_ms = reader.uint16();
    final minimum_presentation_delay_us = reader.uint32();
    final maximum_presentation_delay_us = reader.uint32();
    final feature_flags = reader.uint32();
    return WirelessAudioConfigurationCapabilities(protocol_version: protocol_version, supported_section_mask: supported_section_mask, supported_command_mask: supported_command_mask, supported_acl_policy_mask: supported_acl_policy_mask, supported_phy_mask: supported_phy_mask, minimum_acl_interval_us: minimum_acl_interval_us, maximum_acl_interval_us: maximum_acl_interval_us, acl_interval_resolution_us: acl_interval_resolution_us, maximum_acl_peripheral_latency: maximum_acl_peripheral_latency, minimum_acl_supervision_timeout_ms: minimum_acl_supervision_timeout_ms, maximum_acl_supervision_timeout_ms: maximum_acl_supervision_timeout_ms, minimum_acl_data_octets: minimum_acl_data_octets, maximum_acl_data_octets: maximum_acl_data_octets, minimum_acl_data_time_us: minimum_acl_data_time_us, maximum_acl_data_time_us: maximum_acl_data_time_us, supported_audio_direction_mask: supported_audio_direction_mask, maximum_preferred_retransmission_number: maximum_preferred_retransmission_number, maximum_transport_latency_ms: maximum_transport_latency_ms, minimum_presentation_delay_us: minimum_presentation_delay_us, maximum_presentation_delay_us: maximum_presentation_delay_us, feature_flags: feature_flags);
  }

  /// Encodes this value to the protocol binary representation.
  Uint8List toBytes() {
    final writer = ProtocolWriter();
    _write(writer);
    return writer.takeBytes();
  }

  void _write(ProtocolWriter writer) {
    writer.uint16(protocol_version);
    writer.uint32(supported_section_mask);
    writer.uint32(supported_command_mask);
    writer.uint32(supported_acl_policy_mask);
    writer.uint8(supported_phy_mask);
    writer.uint32(minimum_acl_interval_us);
    writer.uint32(maximum_acl_interval_us);
    writer.uint32(acl_interval_resolution_us);
    writer.uint16(maximum_acl_peripheral_latency);
    writer.uint32(minimum_acl_supervision_timeout_ms);
    writer.uint32(maximum_acl_supervision_timeout_ms);
    writer.uint16(minimum_acl_data_octets);
    writer.uint16(maximum_acl_data_octets);
    writer.uint16(minimum_acl_data_time_us);
    writer.uint16(maximum_acl_data_time_us);
    writer.uint8(supported_audio_direction_mask);
    writer.uint8(maximum_preferred_retransmission_number);
    writer.uint16(maximum_transport_latency_ms);
    writer.uint32(minimum_presentation_delay_us);
    writer.uint32(maximum_presentation_delay_us);
    writer.uint32(feature_flags);
  }
}

