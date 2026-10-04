"""Cross-check generated PPG C bindings against fixed wire bytes."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest


class PpgCodecTest(unittest.TestCase):
    def test_c_wire_layout(self):
        cc = shutil.which('cc')
        if cc is None:
            self.skipTest('C compiler unavailable')
        source = r'''
#include <assert.h>
#include <string.h>
#include "ppg_protocol.h"
int main(void) {
    const uint8_t full[10] = {255,255,255,255,255,255,255,255,255,15};
    uint8_t out[16]; size_t size = 0;
    ppg_compact_sample_t packed = {0xffffffff, 0xffffffff, 0x0fff};
    assert(ppg_compact_sample_encode(&packed, out, sizeof(out), &size) == PROTOCOL_OK);
    assert(size == 10 && memcmp(full, out, 10) == 0);
    ppg_compact_sample_t decoded = {0};
    assert(ppg_compact_sample_decode(&decoded, full, 10, &size) == PROTOCOL_OK);
    assert(size == 10 && decoded.bits_0_31 == packed.bits_0_31);
    assert(decoded.bits_32_63 == packed.bits_32_63 && decoded.bits_64_79 == 0xfff);
    for (size_t n = 0; n < 10; ++n)
        assert(ppg_compact_sample_decode(&decoded, full, n, &size) != PROTOCOL_OK);
    ppg_legacy_sample_t legacy = {1, 2, 3, 4};
    const uint8_t old[16] = {1,0,0,0,2,0,0,0,3,0,0,0,4,0,0,0};
    assert(ppg_legacy_sample_encode(&legacy, out, sizeof(out), &size) == PROTOCOL_OK);
    assert(size == 16 && memcmp(old, out, 16) == 0);
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory)
            (path/'test.c').write_text(source)
            subprocess.run([cc, '-std=c99', '-Wall', '-Wextra', '-Werror',
                            '-Igenerated/c/include', str(path/'test.c'),
                            'generated/c/src/ppg_protocol.c',
                            'generated/c/src/protocol_runtime.c',
                            '-o', str(path/'test')], check=True)
            subprocess.run([str(path/'test')], check=True)
