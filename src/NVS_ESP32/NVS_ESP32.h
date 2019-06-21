#ifndef NVS_ESP32_H
#define NVS_ESP32_H
#include "Arduino.h"


class NVS_EPPROM
{
	public:
	//NVS_ESP32(const char* name);
	size_t NVS_SetString(const char* name, const char* key, char* in);
	size_t NVS_GetString(const char* name, const char* key, char* out,size_t max_size);
	size_t NVS_SetUInt(const char* name, const char* key, uint32_t in);
	uint32_t NVS_GetUInt(const char* name, const char* key);
	size_t NVS_SetULong64(const char* name, const char* key, uint64_t in);
	uint64_t NVS_GetULong64(const char* name, const char* key);
	private:
	char n[15];

};
#endif