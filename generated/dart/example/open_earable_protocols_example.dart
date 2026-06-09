import 'package:open_earable_protocols/open_earable_protocols.dart';

void main() {
  final tone = AudioResponseTone(frequency: 440, duration: 1000);
  final encoded = tone.toBytes();
  final decoded = AudioResponseTone.fromBytes(encoded);

  print('${decoded.frequency} Hz for ${decoded.duration} ms');
}
