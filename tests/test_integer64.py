"""Executable compatibility tests for signed and unsigned 64-bit codecs."""
import os
from pathlib import Path
import shutil
import struct
import subprocess
import tempfile
import unittest

from protocol_generator import generate, load_protocol
from protocol_generator.errors import SchemaError

SCHEMA = '''protocol: integer64
version: 1
messages:
  values:
    description: Exact signed and unsigned 64-bit values.
    fields:
      - name: unsigned_value
        type: uint64
      - name: signed_value
        type: int64
      - name: count
        type: uint8
      - name: samples
        type: int64[count]
'''


class Integer64Tests(unittest.TestCase):
    """Generate temporary bindings and compare them with independent wire vectors."""

    def test_c_and_dart_vectors(self):
        """Preserve extrema, values above 2^53, arrays, and little-endian order."""
        cases = [(0, 0), (2**64 - 1, -(2**63)), (2**63, 2**63 - 1),
                 (2**53 + 1, -1), (0x0102030405060708, -1000)]
        with tempfile.TemporaryDirectory() as directory:
            temp = Path(directory)
            schemas = temp / 'schemas' / 'integer64'
            schemas.mkdir(parents=True)
            (schemas / 'protocol.yml').write_text(SCHEMA)
            output = temp / 'generated'
            generate(temp / 'schemas', output)
            c = '#include "integer64_protocol.h"\n#include <string.h>\nint main(void) {\n'
            dart = "import 'dart:typed_data';\nimport 'generated/dart/lib/src/integer64_protocol.dart';\nvoid main() {\n"
            for unsigned, signed in cases:
                expected = struct.pack('<QqBqq', unsigned, signed, 2, -(2**63), 2**63 - 1)
                values = ','.join(map(str, expected))
                signed_literal = 'INT64_MIN' if signed == -(2**63) else f'INT64_C({signed})'
                c += f'''{{
                  const uint8_t expected[] = {{{values}}};
                  int64_t samples[] = {{INT64_MIN, INT64_MAX}};
                  integer64_values_t message = {{UINT64_C({unsigned}), {signed_literal}, 2, samples, 2}};
                  uint8_t bytes[sizeof(expected)]; size_t used;
                  if (integer64_values_encode(&message, bytes, sizeof(bytes), &used) != PROTOCOL_OK || used != sizeof(expected) || memcmp(bytes, expected, used)) return 1;
                  message.unsigned_value = 0; message.signed_value = 0; samples[0] = 0; samples[1] = 0;
                  if (integer64_values_decode_bounded(&message, expected, sizeof(expected), &used) != PROTOCOL_OK || used != sizeof(expected)) return 2;
                  if (message.unsigned_value != UINT64_C({unsigned}) || message.signed_value != {signed_literal} || samples[0] != INT64_MIN || samples[1] != INT64_MAX) return 3;
                  for (size_t length = 0; length < sizeof(expected); length++) {{
                    if (integer64_values_decode(&message, expected, length, NULL) == PROTOCOL_OK) return 4;
                    if (integer64_values_encode(&message, bytes, length, NULL) == PROTOCOL_OK) return 5;
                  }}
                }}\n'''
                dart += f'''{{
                  final expected = Uint8List.fromList([{values}]);
                  final message = Integer64Values(unsigned_value: BigInt.parse('{unsigned}'), signed_value: BigInt.parse('{signed}'), count: 2, samples: [-(BigInt.one << 63), (BigInt.one << 63) - BigInt.one]);
                  final bytes = message.toBytes();
                  if (bytes.join(',') != expected.join(',')) throw StateError('encoded bytes');
                  final decoded = Integer64Values.fromBytes(expected);
                  if (decoded.unsigned_value != message.unsigned_value || decoded.signed_value != message.signed_value || decoded.samples.join(',') != message.samples.join(',')) throw StateError('decoded fields');
                  for (var length = 0; length < expected.length; length++) {{
                    var rejected = false;
                    try {{ Integer64Values.fromBytes(Uint8List.sublistView(expected, 0, length)); }} catch (_) {{ rejected = true; }}
                    if (!rejected) throw StateError('truncated input');
                  }}
                }}\n'''
            c += 'return 0; }\n'
            (temp / 'main.c').write_text(c)
            subprocess.run(['cc', '-std=c99', '-Wall', '-Wextra', '-Werror',
                            '-I' + str(output / 'c/include'), str(temp / 'main.c'),
                            str(output / 'c/src/protocol_runtime.c'),
                            str(output / 'c/src/integer64_protocol.c'), '-o', str(temp / 'check')], check=True)
            subprocess.run([str(temp / 'check')], check=True)
            dart += '''
              for (final value in [BigInt.from(-1), BigInt.one << 64]) {
                var rejected = false;
                try { Integer64Values(unsigned_value: value, signed_value: BigInt.zero, count: 0, samples: []).toBytes(); } on RangeError { rejected = true; }
                if (!rejected) throw StateError('unsigned overflow');
              }
              for (final value in [-(BigInt.one << 63) - BigInt.one, BigInt.one << 63]) {
                var rejected = false;
                try { Integer64Values(unsigned_value: BigInt.zero, signed_value: value, count: 0, samples: []).toBytes(); } on RangeError { rejected = true; }
                if (!rejected) throw StateError('signed overflow');
              }
            }\n'''
            (temp / 'check.dart').write_text(dart)
            executable = os.environ.get('PROTOCOL_DART', 'dart')
            if shutil.which(executable):
                subprocess.run([executable, str(temp / 'check.dart')], check=True)
            else:
                self.skipTest('C checks passed; Dart SDK is unavailable')

    def test_rejects_64_bit_length_fields(self):
        """Reject unsupported control widths rather than emit invalid Dart code."""
        with tempfile.TemporaryDirectory() as directory:
            schema = Path(directory) / 'protocol.yml'
            schema.write_text(SCHEMA.replace('type: uint8', 'type: uint64'))
            with self.assertRaises(SchemaError):
                load_protocol(schema)

    def test_rejects_64_bit_union_tags(self):
        """Keep union discriminators within the supported C/Dart control widths."""
        with tempfile.TemporaryDirectory() as directory:
            schema = Path(directory) / 'protocol.yml'
            for scalar in ('uint64', 'int64'):
                schema.write_text(f"""protocol: tagged
version: 1
messages:
  empty:
    fields: []
  command:
    fields:
      - name: payload
        type: union
        tag_type: {scalar}
        variants:
          0: empty
""")
                with self.subTest(scalar=scalar), self.assertRaisesRegex(SchemaError, 'at most 32 bits'):
                    load_protocol(schema)
