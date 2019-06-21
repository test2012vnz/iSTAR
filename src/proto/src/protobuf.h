#ifndef PROTOBUF_H
#define PROTOBUF_H
#include "Arduino.h"

#include "inc.h"

class proto{
public:
	proto();
	bool encode(const pb_field_t fields[],const void *src_struct);
	bool decode(const pb_field_t fields[],void *dest_struct);
	uint8_t data[2000];
	size_t length;
private:
	pb_ostream_t stream_encode;
	pb_istream_t stream_decode;
};

#endif
