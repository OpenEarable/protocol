"""Verify signed IMU fields and unchanged float32 magnetometer bytes."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest


class ImuCodecTest(unittest.TestCase):
    def test_c_wire_layout(self):
        cc = shutil.which('cc')
        if cc is None:
            self.skipTest('C compiler unavailable')
        source = r'''
#include <assert.h>
#include <string.h>
#include "imu_protocol.h"
int main(void) {
    const uint8_t expected[24] = {
        0,128,255,255,0,0,1,0,0,64,255,127,
        0,0,160,63,0,0,32,192,0,0,0,128};
    imu_compact_sample_t value = {-32768,-1,0,1,16384,32767,1.25f,-2.5f,-0.0f};
    uint8_t out[24]; size_t size;
    assert(imu_compact_sample_encode(&value, out, sizeof(out), &size) == PROTOCOL_OK);
    assert(size == 24 && memcmp(out, expected, sizeof(out)) == 0);
    imu_compact_sample_t decoded;
    assert(imu_compact_sample_decode(&decoded, out, sizeof(out), &size) == PROTOCOL_OK);
    assert(decoded.accel_x == -32768 && decoded.accel_y == -1 && decoded.accel_z == 0);
    assert(decoded.gyro_x == 1 && decoded.gyro_y == 16384 && decoded.gyro_z == 32767);
    assert(memcmp(&decoded.mag_x, &value.mag_x, 3 * sizeof(float)) == 0);
    for (size_t n = 0; n < 24; ++n)
        assert(imu_compact_sample_decode(&decoded, out, n, &size) != PROTOCOL_OK);
}
'''
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory)
            (path / 'test.c').write_text(source)
            subprocess.run([cc, '-std=c99', '-Wall', '-Wextra', '-Werror',
                            '-Igenerated/c/include', str(path / 'test.c'),
                            'generated/c/src/imu_protocol.c',
                            'generated/c/src/protocol_runtime.c',
                            '-o', str(path / 'test')], check=True)
            subprocess.run([str(path / 'test')], check=True)
