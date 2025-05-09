#include "packet_codec.h"

#include "packet_factory.h"

write_stream packet_codec::encode(const std::shared_ptr<packet>& packet) {
	write_stream stream;
	stream.write_as<unsigned char>(packet->get_id());
	packet->encode(stream);

	return stream;
}

std::shared_ptr<packet> packet_codec::decode(read_stream& stream) {
	auto packet_id = stream.read_as<unsigned char>();
	auto packet = packet_factory::create_packet(packet_id);
	if (packet == nullptr) {
		PLOGE.printf("An invalid packet detected: %d", packet_id);
		return nullptr;
	}

	packet->decode(stream);
	return packet;
}
