#include "protobuf.h"

proto::proto()
{
    memset(data, 0, 2000);
 
}

bool proto::encode(const pb_field_t fields[], const void *src_struct)
{
    bool status;
    stream_encode = pb_ostream_from_buffer(data, sizeof(data));
    status = pb_encode(&stream_encode, fields, src_struct);
    if (!status)
    {
        log_e("Protobuf encode err: %s", PB_GET_ERROR(&stream_encode));
    }
    length = stream_encode.bytes_written;
    return status;
}

bool proto::decode(const pb_field_t fields[], void *dest_struct)
{
    bool status;
    stream_decode = pb_istream_from_buffer(data, sizeof(data));
    status=pb_decode(&stream_decode,fields,dest_struct);
    if(!status){
    	Serial.println("Protobuf decode err: "+String(PB_GET_ERROR(&stream_decode)));
    }
    return status;
}



