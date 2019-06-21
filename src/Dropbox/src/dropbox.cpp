#include "dropbox.h"


HTTPUpdateResult dropbox::ota(const String& path, const String& currentVersion)
{
    HTTPClient http;
    if(endpoint=="")
    	return HTTP_UPDATE_FAILED;
    if(!http.begin(endpoint))
    {
        return HTTP_UPDATE_FAILED;
    }
    http.addHeader("Authorization", "Bearer " + token);
    http.addHeader("Dropbox-API-Arg", "{\"path\": \"/ota/"+path+"\"}");      
    return HTTPUpdate::handleUpdate(http, currentVersion, false);
}
