"""Executable tests for record arrays and caller-owned C decode buffers."""
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

from protocol_generator import generate, load_protocol
from protocol_generator.errors import SchemaError

SCHEMA = '''protocol: records
version: 1
messages:
  envelope:
    fields:
      - name: count
        type: uint8
      - name: packets
        type: packet[count]
  packet:
    fields:
      - name: count
        type: uint8
      - name: modes
        type: mode[count]
      - name: trailer
        type: uint8
  mode:
    fields:
      - name: id
        type: uint8
      - name: name_length
        type: uint8
      - name: name
        type: bytes[name_length]
'''


class RecordArrayTests(unittest.TestCase):
    """Check nested codecs, capacity errors, schema order, and recursion."""

    def test_record_codecs(self):
        """Exercise nested arrays, empty lists, truncation, and bounded writes."""
        with tempfile.TemporaryDirectory() as directory:
            temp = Path(directory)
            schemas = temp / 'schemas' / 'records'
            schemas.mkdir(parents=True)
            (schemas / 'protocol.yml').write_text(SCHEMA)
            protocol = load_protocol(schemas / 'protocol.yml')
            self.assertEqual([message.name for message in protocol.messages], ['mode', 'packet', 'envelope'])
            output = temp / 'generated'
            generate(temp / 'schemas', output)
            c = r'''
#include "records_protocol.h"
#include <string.h>
#define CHECK(condition) do { if (!(condition)) return __LINE__; } while (0)
int main(void) {
    const uint8_t expected[] = {2, 1, 1, 'A', 2, 2, 'B', 'B', 99};
    uint8_t a[] = {'A'}, bb[] = {'B', 'B'};
    records_mode_t source[] = {
      {.id=1, .name_length=1, .name=a}, {.id=2, .name_length=2, .name=bb}
    };
    records_packet_t packet = {.count=2, .modes=source, .trailer=99};
    uint8_t bytes[32]; size_t used;
    CHECK(records_packet_encode(&packet, bytes, sizeof(bytes), &used) == PROTOCOL_OK);
    CHECK(used == sizeof(expected) && !memcmp(bytes, expected, used));
    uint8_t first[2] = {0xAA, 0xAA}, second[3] = {0xAA, 0xAA, 0xAA};
    records_mode_t destination[] = {
      {.name=first, .name_capacity=1}, {.name=second, .name_capacity=2}
    };
    records_packet_t decoded = {.modes=destination, .modes_capacity=2};
    CHECK(records_packet_decode_bounded(&decoded, expected, sizeof(expected), &used) == PROTOCOL_OK);
    CHECK(decoded.count == 2 && decoded.trailer == 99 && destination[0].id == 1 && destination[1].id == 2);
    CHECK(first[0] == 'A' && first[1] == 0xAA && second[0] == 'B' && second[1] == 'B' && second[2] == 0xAA);
    decoded.modes_capacity = 1; first[0] = 0xAA;
    CHECK(records_packet_decode(&decoded, expected, sizeof(expected), NULL) == PROTOCOL_ERROR_BUFFER_TOO_SMALL);
    CHECK(first[0] == 0xAA);
    decoded.modes_capacity = 2; destination[0].name_capacity = 0;
    CHECK(records_packet_decode(&decoded, expected, sizeof(expected), NULL) == PROTOCOL_ERROR_BUFFER_TOO_SMALL);
    CHECK(first[0] == 0xAA);
    destination[0].name_capacity = 1;
    destination[0].name = NULL;
    CHECK(records_packet_decode_bounded(&decoded, expected, sizeof(expected), NULL) == PROTOCOL_ERROR_INVALID_DATA);
    destination[0].name = first;
    decoded.modes = NULL;
    CHECK(records_packet_decode_bounded(&decoded, expected, sizeof(expected), NULL) == PROTOCOL_ERROR_INVALID_DATA);
    decoded.modes = destination;
    for (size_t length=0; length<sizeof(expected); length++) {
      CHECK(records_packet_decode_bounded(&decoded, expected, length, NULL) != PROTOCOL_OK);
      CHECK(records_packet_encode(&packet, bytes, length, NULL) != PROTOCOL_OK);
    }
    records_packet_t empty = {.count=0, .trailer=99};
    const uint8_t empty_bytes[] = {0, 99};
    CHECK(records_packet_encode(&empty, bytes, sizeof(bytes), &used) == PROTOCOL_OK && used == 2);
    CHECK(records_packet_decode_bounded(&empty, empty_bytes, 2, NULL) == PROTOCOL_OK);
    records_envelope_t envelope = {.count=1, .packets=&packet};
    CHECK(records_envelope_encode(&envelope, bytes, sizeof(bytes), &used) == PROTOCOL_OK);
    CHECK(used == sizeof(expected)+1 && bytes[0] == 1 && !memcmp(bytes+1, expected, sizeof(expected)));
    records_envelope_t target = {.packets=&decoded, .packets_capacity=1};
    CHECK(records_envelope_decode_bounded(&target, bytes, used, NULL) == PROTOCOL_OK);
    CHECK(target.count == 1 && decoded.trailer == 99);
    target.packets_capacity = 0;
    CHECK(records_envelope_decode_bounded(&target, bytes, used, NULL) == PROTOCOL_ERROR_BUFFER_TOO_SMALL);
    CHECK(records_packet_decode_bounded(NULL, expected, sizeof(expected), NULL) == PROTOCOL_ERROR_INVALID_DATA);
    return 0;
}
'''
            (temp / 'main.c').write_text(c)
            subprocess.run(['cc', '-std=c99', '-Wall', '-Wextra', '-Werror',
                            '-I' + str(output / 'c/include'), str(temp / 'main.c'),
                            str(output / 'c/src/protocol_runtime.c'), str(output / 'c/src/records_protocol.c'),
                            '-o', str(temp / 'check')], check=True)
            subprocess.run([str(temp / 'check')], check=True)
            dart = r'''
import 'dart:typed_data';
import 'generated/dart/lib/src/records_protocol.dart';
void check(bool value) { if (!value) throw StateError('record codec check failed'); }
void main() {
  final expected = Uint8List.fromList([2, 1, 1, 65, 2, 2, 66, 66, 99]);
  final packet = RecordsPacket(count: 2, modes: [
    RecordsMode(id: 1, name_length: 1, name: Uint8List.fromList([65])),
    RecordsMode(id: 2, name_length: 2, name: Uint8List.fromList([66, 66]))
  ], trailer: 99);
  check(packet.toBytes().join(',') == expected.join(','));
  final decoded = RecordsPacket.fromBytes(expected);
  check(decoded.count == 2 && decoded.trailer == 99 && decoded.modes[0].id == 1 && decoded.modes[1].name.join(',') == '66,66');
  for (var length=0; length<expected.length; length++) {
    var rejected = false;
    try { RecordsPacket.fromBytes(Uint8List.sublistView(expected, 0, length)); } catch (_) { rejected = true; }
    check(rejected);
  }
  check(RecordsPacket(count: 0, modes: [], trailer: 99).toBytes().join(',') == '0,99');
  var rejected = false;
  try { RecordsPacket(count: 1, modes: packet.modes, trailer: 99).toBytes(); } catch (_) { rejected = true; }
  check(rejected);
  final envelope = RecordsEnvelope(count: 1, packets: [packet]);
  check(envelope.toBytes().join(',') == '1,${expected.join(',')}');
  check(RecordsEnvelope.fromBytes(envelope.toBytes()).packets[0].trailer == 99);
}
'''
            (temp / 'check.dart').write_text(dart)
            executable = os.environ.get('PROTOCOL_DART', 'dart')
            if shutil.which(executable):
                subprocess.run([executable, str(temp / 'check.dart')], check=True)
            else:
                self.skipTest('C checks passed; Dart SDK is unavailable')

    def test_rejects_recursive_records(self):
        """Reject both direct and indirect recursive layouts before emission."""
        with tempfile.TemporaryDirectory() as directory:
            schema = Path(directory) / 'protocol.yml'
            for target in ('packet', 'envelope'):
                schema.write_text(SCHEMA.replace('type: mode[count]', f'type: {target}[count]'))
                with self.subTest(target=target), self.assertRaisesRegex(SchemaError, 'recursive'):
                    load_protocol(schema)

    def test_rejects_capacity_field_collisions(self):
        """Prevent schema names from shadowing generated storage metadata."""
        with tempfile.TemporaryDirectory() as directory:
            schema = Path(directory) / 'protocol.yml'
            schema.write_text(SCHEMA.replace('name: trailer', 'name: modes_capacity'))
            with self.assertRaisesRegex(SchemaError, 'reserved for decode storage'):
                load_protocol(schema)

    def test_signed_record_count(self):
        """Negative record counts must fail before indexing source or destination."""
        with tempfile.TemporaryDirectory() as directory:
            temp = Path(directory)
            schemas = temp / 'schemas' / 'signed'
            schemas.mkdir(parents=True)
            (schemas / 'protocol.yml').write_text("""protocol: signed
version: 1
messages:
  item:
    fields:
      - name: value
        type: uint8
  packet:
    fields:
      - name: count
        type: int8
      - name: items
        type: item[count]
""")
            output = temp / 'generated'
            generate(temp / 'schemas', output)
            code = """#include "signed_protocol.h"
int main(void) {
    signed_item_t item = {.value=42};
    signed_packet_t packet = {.count=-1, .items=&item, .items_capacity=1};
    uint8_t bytes[4] = {255};
    if (signed_packet_encode(&packet, bytes, sizeof(bytes), NULL) != PROTOCOL_ERROR_INVALID_DATA) return 1;
    if (signed_packet_decode_bounded(&packet, bytes, 1, NULL) != PROTOCOL_ERROR_INVALID_DATA) return 2;
    if (item.value != 42) return 3;
    return 0;
}
"""
            (temp / 'main.c').write_text(code)
            subprocess.run(['cc', '-std=c99', '-Wall', '-Wextra', '-Werror',
                            '-I' + str(output / 'c/include'), str(temp / 'main.c'),
                            str(output / 'c/src/protocol_runtime.c'), str(output / 'c/src/signed_protocol.c'),
                            '-o', str(temp / 'check')], check=True)
            subprocess.run([str(temp / 'check')], check=True)
