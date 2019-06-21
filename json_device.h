String nested_json(String src, String dst, String key=""){
  if(key=="")
    return src;
  String js = "";
  int idx = src.indexOf(key);
  if(idx>=0){
    int idx_t;
    int k=-1; 
    for(idx_t=idx; idx_t<src.length(); idx_t++){
      if(src[idx_t]=='['){
        if(k++==-1){
          idx = idx_t;
        }
      }else if(src[idx_t]==']'){
        if(k==0)
          break;
        else k--;
      }
    }
    js = src.substring(0, idx_t);
    if(idx_t-idx>1)
      js+= ",";
    js += dst + "]";
    js += src.substring(idx_t+1, src.length());
  }else{
    js = src.substring(0, src.length()-1) +",";
    js+="\""+key+"\":";
    if(dst=="")
      js+="[]";
    else{
      js+= "["+dst+"]";
    }
    js+= "}";
  }
  return js;
}
String conv_json(String src){
  String js = "{"+src+"}";
  js.replace("{","{\"");
  js.replace(":","\":");
  return js;
}
unsigned int toWiFiQuality(int32_t rssi)
{
  unsigned int qu;
  if (rssi <= -100)
    qu = 0;
  else if (rssi >= -50)
    qu = 100;
  else
    qu = 2 * (rssi + 100);
  return qu;
}

String getJsonVal(String src, String key){
  String js = "";
  int idx = src.indexOf(key);
  if(idx>=0){
    idx = idx+key.length()+1;
    if(src[idx] ==':'){
      int l_idx;
      switch(src[idx+1]){
        case '"':{
          l_idx = src.substring(idx+2, src.length()).indexOf('"');
          idx++;
        }break;
        case '[':{
          l_idx = src.substring(idx+1, src.length()).indexOf(']');
          l_idx++;
        }break;
        case '{':{
          // l_idx = src.substring(idx+2, src.length()).indexOf('}');
          // idx++;
        }break;
        default:{
          l_idx  = src.substring(idx+1, src.length()).indexOf(",");
          if(l_idx<0)
            l_idx  = src.substring(idx+1, src.length()).indexOf("}");
        }
      }
      l_idx+=++idx;
      js = src.substring(idx, l_idx);
      js.replace(" ","");
    }
  }
  return js;
}
String getArrVal(String src, int num){
  int idx=0;
  int l_idx;
  src = src.substring(1, src.length()-1);
  String str="";

    for(int i=0; i<=num; i++){
      idx = src.indexOf(",");
      str = src.substring(0, idx);
      switch(str[0]){
        case '"':{
          l_idx = src.indexOf('"');
          idx = l_idx++;
        }break;
        case '{':{
          l_idx = src.indexOf('}');
          idx = l_idx++;
          idx++;
        }break;
        default:{

        }
      }
      str = src.substring(0, l_idx);
      src= src.substring(++idx, src.length());
    }

  return str;
}