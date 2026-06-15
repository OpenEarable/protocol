import 'package:open_earable_protocols/open_earable_protocols.dart';

void main() {
  final start = AudioResponseTransferControl.start(
    AudioResponseTransferStart(
      transfer_id: 1,
      total_samples: 4,
      sampling_rate: 16000,
      checksum: 0x12345678,
    ),
  );
  final chunk = AudioResponseTransferChunk(
    transfer_id: 1,
    sample_offset: 0,
    sample_count: 4,
    samples: [0, 1000, 0, -1000],
  );

  print('start bytes: ${start.toBytes()}');
  print('chunk bytes: ${chunk.toBytes()}');
}
