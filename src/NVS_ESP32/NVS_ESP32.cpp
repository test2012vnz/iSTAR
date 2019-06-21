#include "NVS_ESP32.h"
#include <Preferences.h>
#include "string.h"

Preferences preferences;

size_t NVS_EPPROM::NVS_SetString(const char* name, const char* key, char* in){
	vTaskDelay(1);
	preferences.begin(name,false);
	preferences.putString(key, in);
	preferences.end();
}

size_t NVS_EPPROM::NVS_GetString(const char* name, const char* key, char* out,size_t max_size){
	memset(out,0,max_size);
	vTaskDelay(1);
	preferences.begin(name,true);
	preferences.getString(key, out,max_size);
	preferences.end();
}

size_t NVS_EPPROM::NVS_SetUInt(const char* name, const char* key, uint32_t in){
	vTaskDelay(1);
	preferences.begin(name,false);
	preferences.putUInt(key, in);
	preferences.end();
}

uint32_t NVS_EPPROM::NVS_GetUInt(const char* name, const char* key){
	vTaskDelay(1);
	uint32_t out;
	preferences.begin(name,true);
	out=preferences.getUInt(key);
	preferences.end();
	return out;
}

size_t NVS_EPPROM::NVS_SetULong64(const char* name, const char* key, uint64_t in){
	vTaskDelay(1);
	preferences.begin(name,false);
	preferences.putULong64(key, in);
	preferences.end();
}

uint64_t NVS_EPPROM::NVS_GetULong64(const char* name, const char* key){
	vTaskDelay(1);
	uint32_t out;
	preferences.begin(name,true);
	out=preferences.getULong64(key);
	preferences.end();
	return out;
}