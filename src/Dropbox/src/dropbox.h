#ifndef DROPBOX_H
#define DROPBOX_H

#include <HTTPClient.h>
#include <HTTPUpdate.h>

class dropbox : public HTTPUpdate
{
public:
	dropbox(){}
	~dropbox(){}

	String endpoint = "https://content.dropboxapi.com/2/files/download";
	String token = "P2J36BpEat4AAAAAAAAALCEabwSwWM6JXMwZ6dac5JaVkut4F8IdI_287_kKxgpH";

	HTTPUpdateResult ota(const String& path, const String& currentVersion="");
};

#endif