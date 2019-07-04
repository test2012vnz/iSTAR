#include "dropbox.h"


HTTPUpdateResult dropbox::ota(const String& path, const String& currentVersion)
{
    HTTPClient http;
    if(endpoint_download=="")
    	return HTTP_UPDATE_FAILED;
    if(!http.begin(endpoint_download))
    {
        return HTTP_UPDATE_FAILED;
    }
    http.addHeader("Authorization", "Bearer " + token);
    http.addHeader("Dropbox-API-Arg", "{\"path\": \"/ota/"+path+"\"}");      
    return HTTPUpdate::handleUpdate(http, currentVersion, false);
}

String dropbox::getFileString(const String& path){
    HTTPClient http;
    if(endpoint_download=="")
        return "";
    if(http.begin(endpoint_download)){
        http.addHeader("Authorization", "Bearer " + token);
        http.addHeader("Dropbox-API-Arg", "{\"path\": \"/"+path+"\"}");      
    }
    int httpResponseCode = http.POST("");   //Send the actual POST request
    String response;
    if(httpResponseCode>0){
        response = http.getString();
    }
    http.end();  
    return response;
}
String dropbox::getListFolderString(const String& folder){
    HTTPClient http;
    if(endpoint_download=="")
        return "";
    if(http.begin(endpoint_folder)){
      http.addHeader("Authorization", "Bearer "+token);
      http.addHeader("Content-Type", "application/json");
    } 
    String response;
    int httpResponseCode = http.POST("{\"path\":\"/"+folder+"\"}");
    if(httpResponseCode>0)
        response = http.getString();
    http.end();  
    return response;
}
