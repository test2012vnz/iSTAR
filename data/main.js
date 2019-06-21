var JSON_ISTARSYS = { TBS:'', TTAM_MAX:'', TBON_MAX:'', R_CAP:'', TANK_VOL:''};
var JSON_ISTARRL = {EN:'', TYPE:'', TON:'', TOFF:'', TIMEON:'', TIMEOFF:''};
var SCHEDULE = { NUM:'', SLOT:[{ TIMESTART:'', DURATION:'' }, { TIMESTART:'', DURATION:'' }, { TIMESTART:'', DURATION:'' }, { TIMESTART:'', DURATION:'' }, { TIMESTART:'', DURATION:'' }]};
var OTHER_SCHE = { NUM:'', SLOT:[{ TYPE:'', TIMESTART:'', DURATION:'', TIMEON:'', TIMEOFF:''}, { TYPE:'', TIMESTART:'', DURATION:'', TIMEON:'', TIMEOFF:''}, { TYPE:'', TIMESTART:'', DURATION:'', TIMEON:'', TIMEOFF:''},
                { TYPE:'', TIMESTART:'', DURATION:'', TIMEON:'', TIMEOFF:''}, { TYPE:'', TIMESTART:'', DURATION:'', TIMEON:'', TIMEOFF:''}]};
var MAX_SCHEDULE = 5;
var Internet_List=[];
var istar_slottime = -1;
var other_slottime = [-1, -1, -1];
var current_device = 1;
var fr= new FileReader();
var myip="";
var ws = new WebSocket("ws://"+location.host+":81/" ); //   "ws://"+location.host+":81/"   "ws://localhost:81/"
var lang_list = {
"vi":{
  "lang": "Ngôn ngữ: ",
  "txt-devset-choose": "Chọn thiết bị :",
  "btn-confirm": "Xác nhận",
  "btn-set": "Cập nhật",
  "btn-add": "Thêm",
  "btn-delete": "Xóa",
  // stab menu
  "hwtest":"KIỂM TRA PHẦN CỨNG",
  "deviceset": "CÀI ĐẶT THIẾT BỊ",
  "conectset": "CÀI ĐẶT KẾT NỐI",
  "rs485set": "CÀI ĐẶT GIAO TIẾP 485",
  "devicecontent": "CÀI ĐẶT HỆ THỐNG",
  "logoutid": "ĐĂNG XUẤT",
  // kiem tra phan cung
  // serial settting
  "txt-hw-time-setting": "Cài đặt thời gian",
  "txt-setting-serial": "Cài đặt số Serial",
  // cai đặt kêt noi
  "txt-conset-wifi": "Cài đặt kết nối wifi",
  "btn-scan-wifi": "Quét",
  "btn-connect-wifi": "Kết nối",
  // rs485
  "txt-rs485-status": "Cài đặt kết nối RS485",
  //system tab
  "btn-istar-sys":"THÔNG SỐ HỆ THỐNG",
  "btn-istar-conv": "BƠM ĐỐI LƯU",
  "btn-istar-return": "BƠM ĐỐI LƯU",
  "btn-istar-heater": "TRỞ GIA NHIỆT",
  "btn-istar-schedule":"THỜI GIAN",
  //SYSTEM -PARAMEMTERS
  "txt-istar-sys": "Cài đặt thông số hệ thống",
  "txt-devset-max-coltemp": "Nhiệt độ tấm tối đa: ",
  "txt-devset-max-tanktemp":"Nhiệt độ bồn tối đa: ",
  "txt-devset-heater-pow": "Công suất điện trở: ",
  "txt-devset-tankvol":"Thể tích bồn: ",
  "txt-devset-tbs":"Nhiệt độ mong muốn: ",
  // conv
  "txt-istar-conv": "Cài đặt thông số bơm đối lưu",
  "txt-istar-return": "Cài đặt thông số bơm hồi",
  "txt-istar-heater": "Cài đặt thông số trở gia nhiệt",
  "txt-istar-schedule":"Cài đặt lịch thời gian",
  "txt-rl-enable": "Cho phép hoạt động",
  "rl-type-1": "Theo nhiệt độ",
  "rl-type-2": "Theo thời gian",
  "turn-on-conv": "Δt bật bơm đối lưu: ",
  "turn-off-conv": "Δt tắt bơm đối lưu: ",
  "pump-time-on": "Thời gian bơm chạy: ",
  "pump-time-off": "Thời gian bơm tắt: ",

  "txt-other-app": "Ứng dụng khác"

},
"en":{
  "lang": "Language: ",
  "txt-devset-choose": "Choose device :",
  "btn-confirm": "Confirm",
  "btn-set": "Update",
  "btn-add": "Add",
  "btn-delete": "Delete",
  // tab menu
  "hwtest": "HARDWARE TESTING",
  "deviceset": "DEVICE SETTING",
  "conectset": "CONNECTION SETTING",
  "rs485set": "STATUS",
  "devicecontent": "SYSTEM SETTING",
  "logoutid": "LOG OUT",
  // kiem tra phan cung
  // serial settting
  "txt-hw-time-setting": "Time settting",
  "txt-setting-serial": "Serial number setting",
  // cai đặt kêt noi
  "txt-conset-wifi": "Wifi setting",
  "btn-scan-wifi": "Scan",
  "btn-connect-wifi": "Connect",
  // rs485
  "txt-rs485-status": "RS485 setting",
  //system
  "btn-istar-sys":"SYSTEM",
  "btn-istar-conv": "CONVECTIONAL PUMP",
  "btn-istar-return": "RETURN PUMP",
  "btn-istar-heater": "HEATER",
  "btn-istar-schedule":"TIME SHCEDULE",
  //SYSTEM -PARAMEMTERS
  "txt-istar-sys": "System parameters setting",
  "txt-devset-max-coltemp": "Maximum colector temperature: ",
  "txt-devset-max-tanktemp":"Maximum tank temperature: ",
  "txt-devset-heater-pow": "Resistor power: ",
  "txt-devset-tankvol":"Tank volume: ",
  "txt-devset-tbs":"The desired temperature: ",
  //conv
  "txt-istar-conv": "Convectional pump parameters setting",
  "txt-istar-return": "Return pump parameters setting",
  "txt-istar-heater": "Heater parameters setting",
  "txt-istar-schedule":"Schedule",
  "txt-rl-enable": "Enable",
  "rl-type-1": "Operating under temperature", // with
  "rl-type-2": "Operating under time",
  "turn-on-conv": "Δt turn on: ",
  "turn-off-conv": "Δt turn off: ",
  "pump-time-on": "Time on: ",
  "pump-time-off": "Time off: ",

  "txt-other-app": "Other application"
}
};
function lang_change(){
  var lang = document.getElementById('lang_select').value;
  hdsdvi = document.getElementsByClassName('hdsd-vi');
  hdsden = document.getElementsByClassName('hdsd-en');
  if(lang=='vi'){
    for(i=0; i<hdsdvi.length; i++){
      hdsdvi[i].style.display = 'block';
      hdsden[i].style.display = 'none';
    }
    for(j=0; j<document.getElementsByClassName('lb1').length; j++)
      document.getElementsByClassName('lb1')[j].style.width = '150px';
    var keys = Object.keys(lang_list.vi);
    for(j=0; j<keys.length; j++)
      if(document.getElementById(keys[j]))
      document.getElementById(keys[j]).innerHTML = lang_list.vi[keys[j]];
      else if(document.getElementsByClassName(keys[j])){
        var parent = document.getElementsByClassName(keys[j]);
        for(i=0; i<parent.length; i++)
          parent[i].innerHTML = lang_list.vi[keys[j]];
      }
  }else if(lang=='en'){
    for(i=0; i<hdsdvi.length; i++){
      hdsdvi[i].style.display = 'none';
      hdsden[i].style.display = 'block';
    }
    for(j=0; j<document.getElementsByClassName('lb1').length; j++)
      document.getElementsByClassName('lb1')[j].style.width = '250px';
    var keys = Object.keys(lang_list.en);
    for(j=0; j<keys.length; j++)
      if(document.getElementById(keys[j]))
      document.getElementById(keys[j]).innerHTML = lang_list.en[keys[j]];
      else if(document.getElementsByClassName(keys[j])){
        var parent = document.getElementsByClassName(keys[j]);
        for(i=0; i<parent.length; i++)
          parent[i].innerHTML = lang_list.en[keys[j]];
      }
  }
}
function readFile(id, txt){
  f = document.getElementById(id);
    fr.onload= function(){
    document.getElementById(txt).textContent=this.result.substring(0, this.result.length-1);;
  }
  fr.readAsText(f.files[0]);
}
function logout(){
    var mes="m=99";
    http_post(mes,"Login Err","/c",99);
}
function ota_update(file_id){
  var formData = new FormData();
  formData.append("myFile", document.getElementById(file_id).files[0]);

  var xhr = new XMLHttpRequest();
  xhr.upload.addEventListener("progress", function(evt){
    if (evt.lengthComputable) {
        var per = evt.loaded / evt.total;
        document.getElementById('prg').innerHTML = "progress: "+ Math.round(per*100) + "%"; //bar
        document.getElementById('bar').style.width = Math.round(per*100)+"%";
        console.log(Math.round(per*100));
      }
    }, false);
  xhr.open("POST", "/update");
  xhr.send(formData);
}
function checkFirrmware(){
  var req = new XMLHttpRequest();
  req.open("POST", "https://api.dropboxapi.com/2/files/list_folder", false);
  req.setRequestHeader("Authorization", "Bearer P2J36BpEat4AAAAAAAAAKQYx0i4sfguQiRc9B3xrkpsuF9rfUdKrIydiaoAztrHH");
  req.setRequestHeader("Content-Type", "application/json");
  req.send(JSON.stringify({path:"/ota"}));

  var obj = JSON.parse(req.responseText)
  if(obj.entries.length == 0)
    console.log("File not found.")
  else{
    // for(i =0; i< obj.entries.length; i++){

    //   console.log(obj.entries[i].name, obj.entries[i].client_modified);
    //   var table = document.getElementById("table-firmware");
    //   var row = table.insertRow(i+1); 
    //   row.insertCell(0).innerHTML = obj.entries[i].name;
    //   row.insertCell(1).innerHTML = obj.entries[i].client_modified.substring(0,10);
    // }
    var Internet_Table="<tr><th>SSID</th><th>RSSID</th></tr>";
    document.getElementById("TBL-FIRM").innerHTML=Internet_Table;
    for(var i=0;i<obj.entries.length;i++){  //style='text-align: center'
        Internet_Table += "<tr><td>" + obj.entries[i].name + "</td><td >" + obj.entries[i].client_modified.substring(0,10) + "</td></tr>";
    }
    document.getElementById("TBL-FIRM").innerHTML=Internet_Table;
  }
    onRowClick("TBL-FIRM", function (row){
      var table = document.getElementById("TBL-FIRM"),
      rows = table.getElementsByTagName("tr"), i;
      for (i = 0; i < rows.length; i++){
        table.rows[i].style.backgroundColor=('transparent');
      }
      document.getElementById('txtFirmware').value = row.cells[0].innerHTML;
      row.style.backgroundColor='#3498DB';
    });
}
function FirmwareUpdate(){
  var mess = "{\"UPDATE_FIRMWARE\": \""+ document.getElementById('txtFirmware').value +"\"}";
  console.log(mess);
   ws.send(mess);
}
/**********************************************************************/
function http_post(mess,err,url,handle){
  var xhttp = new XMLHttpRequest();
  xhttp.onload=function(){
    if(this.readyState==4 && this.status==200){
      switch(handle){
        case 2:{
          Scan_SSID(this.responseXML);
        } break;
        case 3: case 4: case 5: case 9: case 10: case 15: case 16: case 17:
        case 18:
        {
          if(this.responseText == "update")
            alert("Thành công");
          else
            alert("Thất bại");
        }break;
        case 6: case 7: case 8: case 13: case 14:{
          if(this.responseText!=""){
            var obj = JSON.parse(this.responseText);
            PRODUCT = obj.PRODUCT
            if(PRODUCT==1){
              current_device = 1;
              document.getElementById('id-select-product').value = 1;
              selectProduct();
              update_istar(obj);
            }else if(PRODUCT==2){
              current_device = 2;
              document.getElementById('id-select-product').value = 2;
              selectProduct();
              update_other(obj);
            }
            if(handle!=14)
              alert("Thành công");
          }else
          alert("Thất bại");
        }break;
        case 99:{
          document.cookie = "username=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;";
          if(this.responseText = 'LOGOUT')
              location.replace("/");
        }break;
      }
    }else{
      alert(err + this.status);
    }
  }
  xhttp.ontimeout=function(){
    alert(err );
  }
  if(handle==2){
      xhttp.timeout = 10000;
  }else{
      xhttp.timeout = 5000;
  }
  xhttp.open("POST", url, true);
  xhttp.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
  xhttp.send(mess);
}
function ip_local(){
  var ip=[];
 window.RTCPeerConnection = window.RTCPeerConnection || window.mozRTCPeerConnection || window.webkitRTCPeerConnection || false;
 if (window.RTCPeerConnection){
  var pc = new RTCPeerConnection({iceServers:[]}), noop = function(){};
  pc.createDataChannel('');
  pc.createOffer(pc.setLocalDescription.bind(pc), noop);
  pc.onicecandidate = function(event){
   if (event && event.candidate && event.candidate.candidate){
    var s = event.candidate.candidate.split('\n');
    console.log(s);
    ip.push(s[0].split(' ')[4]);
   }
  }
 }
 return ip;
}
function sendSocketMsg(mess){
  ws.send("s=0&LED=1");
}
function TestComponents(component, num, state){
  var test_js = { TEST:'', NUM:'', STATE:''};
  test_js.TEST = component;
  test_js.NUM = num;
  test_js.STATE = state;
  ws.send(JSON.stringify(test_js));
}
function ChangeTest(){
  var test_en = document.getElementById('test-enable').checked?1:0;
  var mes = "{\"TEST_MODE\":"+test_en+"}";
  console.log(mes);
  ws.send(mes);
}
function Websocket(){
   if ("WebSocket" in window) {
       ws.onopen = function() {
          ws.send("open");
       };
       ws.onmessage = function (evt) { 
          var received_msg = evt.data;
          // console.log(received_msg);
          if(received_msg.substring(0,3)=="ips"){
            myip = received_msg.substring(4, received_msg.length)
          }
          else if(received_msg.substring(0,3)=="ipa"){
            if(received_msg.substring(4, received_msg.length) != myip){
              logout();
            }
          }
          else if(received_msg.substring(0,3)=="pkg"){
            var obj = JSON.parse(received_msg.substring(4, received_msg.length));
            var parent = document.getElementById('status-sys').children;
            var d = new Date(1970,0,1); 
            d.setSeconds(obj.TIME);
            parent[1].innerHTML = obj.FIRMWARE;
            parent[4].innerHTML = d.toLocaleTimeString();
            parent[7].innerHTML = Number(obj.LIVE_TIME/60) +" giờ";
            parent[10].innerHTML = obj.RESET_COUNT;

            parent = document.getElementById('status-connect').children;
            if(obj.WIFI_STATE!=0){
              parent[1].innerHTML = "Đã kết nối! "
              parent[3].innerHTML = obj.WIFI_SIGNAL;
            }else{
              parent[1].innerHTML = "Chưa kết nối! "
              parent[3].innerHTML = "0";
            }
            if(obj.MQTT_STATE!=0){
              parent[6].innerHTML = "Đã kết nối";
            }else parent[6].innerHTML = "Chưa kết nối";
            parent = document.getElementById("status-adc").children;
            parent[1].innerHTML = obj.ADC1 +"°C";
            parent[4].innerHTML = obj.ADC2 +"°C";
            parent[7].innerHTML = obj.ADC3 +"°C";
            // 
            d.setSeconds(obj.PCF8563);
            console.log(obj.PCF8563)
            parent = document.getElementById('checking-device').children;
            parent[1].innerHTML = d.toLocaleTimeString();

            if(obj.TEST_MODE==1){
              document.getElementById("test-enable").checked=true;;
            }else{
              document.getElementById("test-enable").checked = false;
            }
          }else if(received_msg.substring(0,3)=="log"){
              var d = new Date();
              var n = d.toTimeString();
            document.getElementById("logger").value = d.toTimeString().substring(0,8)+" | " + received_msg.substring(4, received_msg.length)
            +"\n"+ document.getElementById("logger").value ;
          }
          else if(received_msg.substring(0,4)=="TEST"){
            console.log(received_msg.substring(5,received_msg.length));
            var obj = JSON.parse(received_msg.substring(5, received_msg.length));
            var parent =  document.getElementById('adc-test').children;
            parent[0].children[1].innerHTML = obj["ADC"][0];;
            parent[2].children[1].innerHTML = obj["ADC"][1];;
            parent[4].children[1].innerHTML = obj["ADC"][2];;

          }
       };
       ws.onclose = function() { 
          console.log("Connection is closed..."); 
       };
    } else {
       console.log("WebSocket NOT supported by your Browser!");
    }
}
function theFocus(obj) {
    var tooltip = document.getElementById("tooltip");
    tooltip.innerHTML = obj.title;
    tooltip.style.display = "block";
    tooltip.style.top = obj.offsetTop + obj.offsetHeight + "px";
    tooltip.style.left = obj.offsetLeft + "px";
}

function theBlur(obj) {
    var tooltip = document.getElementById("tooltip");
    tooltip.style.display = "none";
    tooltip.style.top = "-9999px";
    tooltip.style.left = "-9999px";
}
function navState(evt, cityName) {
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("navcontent");
    for (i = 0; i < tabcontent.length; i++) {
        tabcontent[i].style.display = "none";
    }
    tablinks = document.getElementsByClassName("tablinks");
    for (i = 0; i < tablinks.length; i++) {
        tablinks[i].className = tablinks[i].className.replace(" active", "");
    }
    document.getElementById(cityName).style.display = "block";

    if(cityName=="device-setting"){
      document.getElementById('btn-istar-sys').click();
      document.getElementById('chose-device').style.display = "block";
    }else{
      document.getElementById('chose-device').style.display = "none";
    }
    if(cityName=="connection-setting"){
      document.getElementById('tab-wifi-content').click();
    }
    hdsdtab = document.getElementsByClassName("hdsd-content");
    for(i =0; i<hdsdtab.length; i++){
      if('hdsd-'+cityName == hdsdtab[i].id){
        hdsdtab[i].style.display = "block";
      }else{
        hdsdtab[i].style.display = "none";
      }
    }
    evt.currentTarget.className += " active";
}
function tabState(evt, cityName, tabs) {
  responsiveTab('tab','tab-istar');
  var i, tabcontent, tablinks;
  tabcontent = document.getElementsByClassName("tabcontent");
  for (i = 0; i < tabcontent.length; i++) {
    tabcontent[i].style.display = "none";
  }
  tablinks = document.getElementsByClassName(tabs); //fist_tab
  for (i = 0; i < tablinks.length; i++) {
    tablinks[i].className = tablinks[i].className.replace(" active", "");
    if(window.innerWidth<800 && tabs =="tabsystem"){
        document.getElementById(tablinks[0].id).innerHTML = evt.currentTarget.innerHTML;
    }
  }
  document.getElementById(cityName).style.display = "block";
  evt.currentTarget.className += " active";

  hdsdcontent = document.getElementsByClassName('hdsd-istar');
  for(i=0; i<hdsdcontent.length; i++){
    if('hdsd-'+cityName==hdsdcontent[i].id){
      hdsdcontent[i].style.display = "block";
    }else{
      hdsdcontent[i].style.display = "none";
    }
  }

  hdsdconnect = document.getElementsByClassName('hdsd-connection');
    for(i=0; i<hdsdconnect.length; i++){
    if('hdsd-'+cityName==hdsdconnect[i].id){
      hdsdconnect[i].style.display = "block";
    }else{
      hdsdconnect[i].style.display = "none";
    }
  }
  if(cityName=="diff-auto"){ // change color
    document.getElementById("btn-other-manu").style.backgroundColor = "#7ed6df";
    document.getElementById("btn-other-auto").style.backgroundColor = "#ff6666";
  }else if(cityName=="diff-manu"){
    document.getElementById("btn-other-auto").style.backgroundColor = "#7ed6df";
    document.getElementById("btn-other-manu").style.backgroundColor = "#ff6666";
  }
}
function responsiveTab(cl, id) {
  var lang = document.getElementById('lang_select').value;
  document.getElementById('btn-istar-sys').innerHTML = lang=="vi"?"THÔNG SỐ HỆ THỐNG":"SYSTEM";
  var x = document.getElementById(id);
  if (x.className === cl) {
    x.className += " responsive";
  } else {
    x.className = cl;
  }
}
function openNav() {
  if(document.getElementById("mySidenav").offsetWidth==0){
    document.getElementById("mySidenav").style.width = "250px";
    if(screen.width > 480)
      document.getElementById("main").style.marginLeft = "250px";
  }
  else{
    document.getElementById("mySidenav").style.width = "0";
    if(screen.width > 480)
      document.getElementById("main").style.marginLeft= "0";
  }
}
function openHDSD(){
  if(document.getElementById("nav-hdsd").offsetWidth==0){
    document.getElementById("nav-hdsd").style.width = "250px";
    document.getElementById('open-hdsd').innerHTML = "◀"; 
    document.getElementById('open-hdsd').style.left = "250px"; 
  }
  else{
    document.getElementById("nav-hdsd").style.width = "0px";
    document.getElementById('open-hdsd').innerHTML = "▶"; 
    document.getElementById('open-hdsd').style.left = "0px";
  }
}
function openModal(){
  var modal = document.getElementById("modalBox");
  modal.style.display = "block";
}
function close_modal(){
  var modal = document.getElementById("modalBox");
  modal.style.display = "none";
}
function getRating(type1, type2, name) {
  if(name == type1){
    if(screen.width < 480){
      document.getElementById(type1).style.display = "block";
      document.getElementById(type2).style.display = "none";
    }
    else{
          document.getElementById(type1).style.pointerEvents = 'auto';
          document.getElementById(type1).style.opacity = 1;
        document.getElementById(type2).style.pointerEvents = 'none';
        document.getElementById(type2).style.opacity = 0.4;
    }
  }else if(name == type2){
    if(screen.width < 480){
    document.getElementById(type1).style.display = "none";
    document.getElementById(type2).style.display = "block";
    }else{
          document.getElementById(type1).style.pointerEvents = 'none';
          document.getElementById(type1).style.opacity = 0.4;
        document.getElementById(type2).style.pointerEvents = 'auto';
        document.getElementById(type2).style.opacity = 1;
    }
  }
}
function raitingHidden(type1, type2, name){
  if(name==type1){
      document.getElementById(type1).style.display = "block";
      document.getElementById(type2).style.display = "none";
  }else if(name==type2){
      document.getElementById(type1).style.display = "none";
      document.getElementById(type2).style.display = "block";
  }
}
/**********************************************/
function div_dis(id, div_id){
  if(document.getElementById(id).checked){
      document.getElementById(div_id).style.pointerEvents = 'auto';
      document.getElementById(div_id).style.opacity = 1;
  }else{
      document.getElementById(div_id).style.pointerEvents = 'none';
      document.getElementById(div_id).style.opacity = 0.4;
  }
}
/**********************************************/
function onRowClick(tableId, callback) {
    var table = document.getElementById(tableId),
        rows = table.getElementsByTagName("tr"), i;
    for (i = 1; i < rows.length; i++) {
        table.rows[i].onclick = function (row) {
            return function () {
                callback(row);
            };
        }(table.rows[i]);
    }
};
function set_device_param(){
  var d = new Date();
  var parent=document.getElementById('device-setting-time0').children

  var obj = '{'+'"DAY":' + parent[6].value +','
         +'"MONTH":'+ parent[8].value +','
         +'"YEAR":'+ parent[10].value + ','
         +'"WDAY":'+ d.getDay() + ','
         +'"HOUR":'+ parent[0].value + ','
         +'"MINUTE":'+ parent[2].value + ','
         +'"SEC":'+ d.getSeconds() +'}';
  var mess="m=4&JSON="+obj;
  http_post(mess,"Set system err","/c",4);
}
function ScanButton(){
    var mes="m=2";
    // openModel();
    http_post(mes,"Scan Err","/c",2);
}
function SetWifi(){
    var SSID=document.getElementById("SSID").value;
    var PASS=document.getElementById("PASS").value;
    var mes="m=3&SSID="+SSID+"&PASS="+PASS;
    http_post(mes,"Set WIFI Err","/c",3);
}
function Scan_SSID(xml){
    console.log(xml);
    var i;
    var x=xml.getElementsByTagName("net");
    Internet_List.splice(0,Internet_List.length);
    Internet_List=new Array(x.length);
    for(i=0;i<x.length;i++){
        Internet_List[i]=new Array(2);
        Internet_List[i][0]=x[i].getElementsByTagName("ssid")[0].childNodes[0].nodeValue;
        Internet_List[i][1]=x[i].getElementsByTagName("rssi")[0].childNodes[0].nodeValue;
    }
    ScanShow();
}
function ScanShow(){
    var Internet_Table="<tr><th>SSID</th><th>RSSID</th></tr>";
    for(var i=0;i<Internet_List.length;i++){
        Internet_Table += "<tr><td>" + Internet_List[i][0] + "</td><td style='text-align: center'>" + Internet_List[i][1] + "</td></tr>";
    }
    document.getElementById("WIFI_SCAN").innerHTML=Internet_Table;

    onRowClick("WIFI_SCAN", function (row){
      var table = document.getElementById("WIFI_SCAN"),
      rows = table.getElementsByTagName("tr"), i;
      for (i = 0; i < rows.length; i++){
        table.rows[i].style.backgroundColor=('transparent');
      }
      row.style.backgroundColor='#3498DB';
      document.getElementById('SSID').value = row.cells[0].innerHTML;
    });
}
function SetMQTT(){
  var end_point = document.getElementById('end-point').value;
  var rootca = document.getElementById('root-ca').value;
  var certificate_key = document.getElementById('certificate').value;
  var private_key = document.getElementById('private-key').value;
  var mes = "m=18&ENDPOINT="+ encodeURIComponent(end_point);

  mes+="&ROOTCA="+ encodeURIComponent(rootca);
  mes+="&CERTIFICATE="+ encodeURIComponent(certificate_key);
  mes+="&PRIVATEKEY="+ encodeURIComponent(private_key);
  http_post(mes,"Set WIFI Err","/c",18);
}
function send_rs485_slave() {
  mes = "m=16&RS485ID="+document.getElementById("rs485-slave-id").value;
  http_post(mes,"Set product err","/c",16); 
}
function add_rs485_read_device(){
  var device = document.getElementById('rs485-list-device').value; 
  var id = document.getElementById('rs485-read-device-id').value;
  if(device == 0){
    device = "Đồng hồ MFM";
  } else  if(device == 1){
    device = "Đồng hồ DPM";
  }  else if(device == 2){
    device = "Inverter SolarBK";
  }
  var table = document.getElementById("table-rs485");
  var idx = 0;

  if(table.rows.length==1){
    idx = 1;
  }else if(table.rows.length>1){
    for(i=0; i<table.rows.length; i++){
      if(table.rows[i].cells[1].innerHTML == device){
        for(j = i; j<table.rows.length; j++){
          if(table.rows[i].cells[1].innerHTML != table.rows[j].cells[1].innerHTML){
            idx = j;
            break;
          }
        }
        break;
      }
    }
    if(idx == 0){
      idx = table.rows.length;
    }
  }
  var row = table.insertRow(idx); 
  row.insertCell(0).innerHTML = "";
  row.insertCell(1).innerHTML = device;
  row.insertCell(2).innerHTML = id;
  row.insertCell(3).innerHTML = "";

  var stt = 1;
  for(i=1; i<table.rows.length; i++){
    table.rows[i].cells[3].innerHTML = "<button  class=\"btn btn-delete\" onclick=\"delete_row_rs485("+(i)+")\">Xóa</button>";
    table.rows[i].cells[0].innerHTML = stt;
    if( (i<table.rows.length-1)&&table.rows[i].cells[1].innerHTML != table.rows[i+1].cells[1].innerHTML)
        stt=1;
      else stt++;
  }
  document.getElementById('rs485-read-device-id').value = "";
  device = document.getElementById('rs485-list-device').value; 
  mes = "m=17&delete=0&device="+device;
  mes+="&id="+id;
  http_post(mes,"Set product err","/c",17);
}
function send_rs485_master() {
  var total_device = getEntry('rs485-sample-', 20, true)+1;
  var list_device = "["
  for(j=0; j<20; j++){
    if(document.getElementById("rs485-sample-"+j)){
      var parent = document.getElementById("rs485-sample-"+j).children;
      list_device+= "{\"device\":"
      if(parent[0].value =="Đồng hồ MFM")
        list_device+=0;
      else if(parent[0].value =="Đồng hồ DPM")
        list_device+=1;
      else if(parent[0].value =="Inverter SolarBK")
        list_device+=2;

      list_device+=",\"id\":"+parent[1].value+"},";
    }
  }
  list_device=list_device.substring(0, list_device.length-1);
  list_device+="]"
  mes = "m=17&NUM="+total_device+"&RS485_LIST="+list_device;
  http_post(mes,"Set product err","/c",17);
}

function SetSerialNumber(){
  var ssnumber = document.getElementById('serial-number').value;
  if(ssnumber!=""){
  mes = "m=15&SERIAL="+ssnumber;
  http_post(mes,"Set product err","/c",15);
  }else {alert("Số serial không được trống!")}
}
/**********************************************/
function matchExpression( str ) {
    var rgularExp = {
        containsNumber : /\d+/,
        containsAlphabet : /[a-zA-Z]/,

        onlyLetters : /^[A-Za-z]+$/,
        onlyNumbers : /^[0-9]+$/,
        onlyMixOfAlphaNumeric : /^([0-9]+[a-zA-Z]+|[a-zA-Z]+[0-9]+)[0-9a-zA-Z]*$/
    }
    return rgularExp.onlyNumbers.test(str);
}
function toggleMe(a) {
   var e = document.getElementById(a);
   var toggleIcon = document.getElementById('toggle-icon');
   if(!e) return true;
   if(e.style.display == "none") {
      e.style.display = "block";
   }
   else {
      e.style.display = "none";
   }
   return true;
}
function vadiate_istar_rl_form(id, type){
  var parent = document.getElementById(id+type).children;
  if(type){   // chia type
    for(j=1; j< 6; j+=4){
      if(parent[j].value=='' || !matchExpression(parent[j].value)) // them gioi han nhiet do
        return false;
    }
  }
  return true;
}
function vadiate_istar_schedule(){
  var parent = document.getElementById('istar-slot-time').children;
  var i=0;
  for(i=1; i<parent.length; i++){
    var child = parent[i].children;
    for(j=0; j<child.length; j++){
      if(child[j].type=='text' && (child[j].value=='' || !matchExpression(child[j].value))){
        return false;
      }
      if((j==1 || j==5)&& child[j].value >=24)
        return false;
      if((j==3 || j==7)&& child[j].value >=60)
        return false;
    }
  }
  return true;
}
function vadiate_other_istar_form(id){
  var parent = document.getElementById(id).children;
  for(k=0; k< 8; k++){  // check time // k
    if(parent[k].type=='text'&&(parent[k].value=='' || !matchExpression(parent[k].value)))
      return false;
    if((k==1 ||k==5) &&parent[k].value >=24)
      return false;
    if((k==3||k==7)&&parent[k].value>=60)
      return false;
  }
  if(parent[8].value=='2'){
    var child=parent[11].children;
    var child_1 =child[0].children;
  }
  return true;
}
function duplicate(coppy_id, id) {
    var original = document.getElementById(coppy_id);
    var clone = original.cloneNode(true);
    clone.id = id; 
    original.parentNode.appendChild(clone);
}
function getEntry(parent_id, entry, p=false){
  if(!p){
    for(i = 0; i<entry; i++){   // get slot_number
        if(!document.getElementById(parent_id+i))
          return i; 
    }
    return -1;
  }else{
    var count  = -1;
    for(i = 0; i<entry; i++){ 
        if(document.getElementById(parent_id+i))
          count++;
    }
    return count;
  }
}
function SetProduct() {
  var p = document.getElementById('id-select-product').value;
  var mes = "m=13&PRODUCT=";
  if(p==1){
    mes+=1;
    // hidden_element('ISTAR', 1);
  }else if(p==2){
    mes+=2;
    // hidden_element('OTHER', 1);
  }else{
    mes+=0;
  }
  http_post(mes,"Set product err","/c",13);
}
function selectProduct() {
  var val = document.getElementById('id-select-product').value;
  if(val != current_device)
    return;
  if(val=='1'){
    document.getElementById('other-content').style.display = "none";
    document.getElementById('istar-content').style.display = "block";
    document.getElementById('hdsd-other').style.display = "none";
    document.getElementById('hdsd-istar').style.display = "block";
  }else if(val=='2'){
    document.getElementById('istar-content').style.display = "none";
    document.getElementById('other-content').style.display = "block";
    document.getElementById('hdsd-istar').style.display = "none";
    document.getElementById('hdsd-other').style.display = "block";
  }
}
function addSlotTime(i){
  if(i=="ISTAR" && istar_slottime < 4){
    var idx = getEntry('istar-slot-time-', 5);
    if(idx < 5&& idx>-1){
      duplicate('istar-slot-time-','istar-slot-time-'+idx);
      document.getElementById('istar-slot-time-'+idx).style.visibility="visible";
      document.getElementById('istar-slot-time-'+idx).style.display="block";
      var child = document.getElementById('istar-slot-time-'+idx).children;
      child[8].setAttribute('onclick', "deleteSlotTime('ISTAR',"+idx+")");
    }
  }
  else if(other_slottime[i]<4){
    var idx = getEntry('other-rl'+i+'-slot-', 5);
    if(idx < 5&& idx>-1){
      duplicate('other-rl'+i+'-slot-','other-rl'+i+'-slot-'+idx);
      document.getElementById('other-rl'+i+'-slot-'+idx).style.visibility="visible";
      document.getElementById('other-rl'+i+'-slot-'+idx).style.display="block";
      var child = document.getElementById('other-rl'+i+'-slot-'+idx).children;
      child[8].setAttribute('id','other-rl'+i+'-select-'+idx);
      child[9].setAttribute('onclick','deleteSlotTime('+i+','+idx+')'); // button
      child[11].setAttribute('id', 'other-rl'+i+'-hidden-'+idx); //id+'-'+i
      child[8].setAttribute('onchange',"other_select_type('"+ child[8].id +"','"+ child[11].id +"')"); // button
    }
  }
}
function deleteSlotTime(i, other_index=-1){
  chang_state = 0;
  if(i=="ISTAR"){
    var x =  document.getElementById('istar-slot-time');
    x.removeChild(document.getElementById('istar-slot-time-'+other_index));
  }
  else{
    var x =  document.getElementById('other-relay'+i); //parent
    x.removeChild(document.getElementById('other-rl'+i+'-slot-'+other_index));
  }
}
function change_attributeOther(id,i){
  var parent = document.getElementById(id).children;
  var child_1 = parent[0].children;
  child_1[0].setAttribute('onclick',"return toggleMe('colapse-relay"+i+"')");
  parent[1].setAttribute('id','colapse-relay'+i);
  child_2 = parent[1].children;
  child_2[1].setAttribute('onclick','addSlotTime('+i+')');
  child_2[2].setAttribute('id', 'other-relay'+i);
  child_2[3].setAttribute('onclick','OTHERsetData('+i+')');
  child_3= child_2[2].children;
  child_3[0].setAttribute('id', 'other-rl'+i+'-slot-');
  child_4 = child_3[0].children;
  child_4[9].setAttribute('onclick', 'deleteSlotTime('+i+')')
}
function other_select_type(selectid, element_id){
  var ele = document.getElementById(selectid).value;
  var parent = document.getElementById(element_id).children;
  if(ele==2){
    document.getElementById(element_id).style.display='block';
    parent[0].style.display = 'block';
    parent[1].style.display = 'none';
  }else if(ele==4){
    document.getElementById(element_id).style.display='block';
    parent[0].style.display = 'none';
    parent[1].style.display = 'block';
  }else{
    document.getElementById(element_id).style.display='none';
  }
}
/**********************************************/
/**********************************************/
function ISTARsetDefaultParameters(){
  var parent = document.getElementById("istar-system-content").children;
  JSON_ISTARSYS.TTAM_MAX = parent[1].value;
  JSON_ISTARSYS.TBON_MAX = parent[5].value;
  JSON_ISTARSYS.R_CAP = parent[9].value;
  JSON_ISTARSYS.TANK_VOL = parent[13].value;
  JSON_ISTARSYS.TBS = parent[17].value;
  var mess ="m=5&JSON="+  JSON.stringify(JSON_ISTARSYS);
  http_post(mess,"Set system err","/c",5);
}
function ISTARsetConvPump(){
  JSON_ISTARRL.EN = document.getElementById('enable-rl1').checked?1:0;
  if(document.getElementById("raito-conv-type1").checked){
    if(!vadiate_istar_rl_form('convolution-pump-type',1)){
      alert('Giá trị nhập vào không chính xác');
      return;
    }
    JSON_ISTARRL.TYPE = 1;
    var arr = document.getElementById('convolution-pump-type1').children;
    JSON_ISTARRL.TON = arr[1].value;
    JSON_ISTARRL.TOFF = arr[5].value;
  }
  else if(document.getElementById("raito-conv-type2").checked){
    if(!vadiate_istar_rl_form('convolution-pump-type',2)){
      alert('Giá trị nhập vào không chính xác');
      return;
    }
    JSON_ISTARRL.TYPE = 2;
    var arr = document.getElementById('convolution-pump-type2').children;
    JSON_ISTARRL.TIMEON = arr[1].value*60;
    JSON_ISTARRL.TIMEOFF = arr[5].value*60;
  }
  var mess ="m=6&JSON="+  JSON.stringify(JSON_ISTARRL);
  http_post(mess,"Set system err","/c",6);
}
function ISTARsetReturnPump(){
  JSON_ISTARRL.EN = document.getElementById('enable-rl2').checked?1:0;
  if(document.getElementById("raito-return-type1").checked){
    if(!vadiate_istar_rl_form('return-pump-type',1)){
      alert('Giá trị nhập vào không chính xác');
      return;
    }
    JSON_ISTARRL.TYPE = 1;
    var arr = document.getElementById('return-pump-type1').children;
    JSON_ISTARRL.TON = arr[1].value;
    JSON_ISTARRL.TOFF = arr[5].value;
  }
  else if(document.getElementById("raito-return-type2").checked){
    if(!vadiate_istar_rl_form('return-pump-type',2)){
      alert('Giá trị nhập vào không chính xác');
      return;
    }
    JSON_ISTARRL.TYPE = 2;
    var arr = document.getElementById('return-pump-type2').children;
    JSON_ISTARRL.TIMEON = arr[1].value*60;
    JSON_ISTARRL.TIMEOFF = arr[5].value*60;
  }
  var mess ="m=7&JSON="+  JSON.stringify(JSON_ISTARRL);
  http_post(mess,"Set system err","/c",7);
}
function ISTARsetHeater(){
  JSON_ISTARRL.EN = document.getElementById('enable-rl3').checked?1:0;
  JSON_ISTARRL.TON = document.getElementById('HT_ON').value;
  var mess ="m=8&JSON="+  JSON.stringify(JSON_ISTARRL);
  http_post(mess,"Set system err","/c",8);
}
function ISTARsetTime(){
  if(!vadiate_istar_schedule()){
    alert("Giá trị nhập vào không chính xác");
    return;
  }
  var a=[];
  for(j=0; j<5; j++)
    if(document.getElementById('istar-slot-time-'+j)){
      a.push(j);
    }
  SCHEDULE.NUM = a.length;
  for(i = 0; i< a.length; i++){
    parent = document.getElementById('istar-slot-time-'+a[i]).children;
    SCHEDULE.SLOT[i].TIMESTART = parent[1].value*3600 + parent[3].value*60;
    SCHEDULE.SLOT[i].DURATION =(parent[5].value*3600+ parent[7].value*60)-(parent[1].value*3600+ parent[3].value*60);
    if(SCHEDULE.SLOT[i].DURATION < 0 )
      SCHEDULE.SLOT[i].DURATION = 86400 - Math.abs(SCHEDULE.SLOT[i].DURATION);
  }
  for(i=a.length; i<MAX_SCHEDULE; i++){
    SCHEDULE.SLOT[i].TIMESTART = 0;
    SCHEDULE.SLOT[i].DURATION = 0;
  }
  var mess ="m=9&JSON="+  JSON.stringify(SCHEDULE);
  http_post(mess,"Set system err","/c",9);
}
function OTHERsetData(i){   // i number of relay
  var a=[];
  for(j=0; j<MAX_SCHEDULE; j++){
    if(document.getElementById('other-rl'+i+'-slot-'+j)){
      a.push(j);
      if(!vadiate_other_istar_form('other-rl'+i+'-slot-'+j)){
        alert('Giá trị nhập vào không chính xác');
        return;
      }
    }
  }
  OTHER_SCHE.NUM = a.length;
  for(j = 0; j<a.length; j++){
    var parent = document.getElementById('other-rl'+i+'-slot-'+a[j]).children;
    OTHER_SCHE.SLOT[j].TYPE = parent[8].value;
    OTHER_SCHE.SLOT[j].TIMESTART =  parent[1].value*3600 + parent[3].value*60;
    OTHER_SCHE.SLOT[j].DURATION = (parent[5].value*3600+ parent[7].value*60)-(parent[1].value*3600+ parent[3].value*60);
    if(OTHER_SCHE.SLOT[j].DURATION<0)
      OTHER_SCHE.SLOT[j].DURATION = 86400 - Math.abs(OTHER_SCHE.SLOT[j].DURATION);
    var child = parent[11].children;
    var child_1 = child[0].children;  // time
    OTHER_SCHE.SLOT[j].TIMEON = child_1[1].value*60;
    OTHER_SCHE.SLOT[j].TIMEOFF = child_1[3].value*60;
    var child_2 = child[1].children;  // conpile string//
  }
  for(j=a.length; j<MAX_SCHEDULE; j++){
    OTHER_SCHE.SLOT[j].TIMESTART =0;
    OTHER_SCHE.SLOT[j].DURATION =0;
  }
  var mess ="m="+(6+i)+"&JSON="+  JSON.stringify(OTHER_SCHE);
  http_post(mess,"other set err","/c",6);
}
function other_setManual(){
  var mes = "m=10&MANUAL=1";
  document.getElementById('manual-rl1').checked?mes+="&MANNUAL_RL1=1":mes+="&MANNUAL_RL1=0";
  document.getElementById('manual-rl2').checked?mes+="&MANNUAL_RL2=1":mes+="&MANNUAL_RL2=0";
  document.getElementById('manual-rl3').checked?mes+="&MANNUAL_RL3=1":mes+="&MANNUAL_RL3=0";
  http_post(mes,"Set conv pump err","/c",10);
}
function sort_list(list){
  var list_device =[];
  for(i=0; i<3; i++){
    for(j=0; j<list.length-1; j++){
      if(list[j+1]==i){
        list_device.push(list[j]);
        list_device.push(list[j+1]);
      }
      j++;
    }
  }
  return list_device;
}
function add_rs485_device(){
  // var table = document.getElementById("table-rs485");
  // var row = table.insertRow(table.rows.length);
  // row.insertCell(0).innerHTML = table.rows.length;

    // var i = getEntry('rs485-sample-', 20);
    // if(i>-1){
    //     duplicate('rs485-sample-','rs485-sample-'+i);
    //     document.getElementById('rs485-sample-'+i).style.visibility="visible";
    //     document.getElementById('rs485-sample-'+i).style.display="block";
    //     change_attributeRS485('rs485-sample-'+i, i);
    // }
    // document.getElementById("rs485-read-device-id").value="";
}
function delete_row_rs485(i){
  var table = document.getElementById("table-rs485");
  var device="";
  var id = table.rows[i].cells[2].innerHTML;
  if(table.rows[i].cells[1].innerHTML=="Đồng hồ MFM"){
    device = 0;
  }else if(table.rows[i].cells[1].innerHTML=="Đồng hồ DPM"){
    device = 1;
  }else if(table.rows[i].cells[1].innerHTML=="Inverter SolarBK"){
    device =2;
  }
  table.deleteRow(i);
  stt = 1;
  for(i =1; i<table.rows.length; i++){
    table.rows[i].cells[3].innerHTML = "<button  class=\"btn btn-delete\" onclick=\"delete_row_rs485("+(i)+")\">Xóa</button>";
    table.rows[i].cells[0].innerHTML = stt;
    
    if( (i<table.rows.length-1)&&table.rows[i].cells[1].innerHTML != table.rows[i+1].cells[1].innerHTML)
      stt=1;
    else stt++;
  }
  mes = "m=17&delete=1&device="+device;
  mes+="&id="+id;
  http_post(mes,"Set product err","/c",17);
}
function update_rs485(obj) {
  if(obj.MODE==2 || obj.MODE==0){
    document.getElementById('raito-rs485-sl').checked =true;
    raitingHidden('rs485-slave','rs485-master','rs485-slave');
    document.getElementById("rs485-slave-id").value = obj.SLAVE_ID;
  }else if(obj.MODE==1){
    document.getElementById('raito-rs485-ma').checked =true;
    raitingHidden('rs485-master','rs485-slave','rs485-master');
    var k=0;
    for(j=0; j<20;j++){
      if(document.getElementById('rs485-sample-'+j))
        remove_rs485_device(j);
    }
  obj.DEVICES = sort_list(obj.DEVICES);
  var table = document.getElementById("table-rs485");
  var stt = 1;

  for(r=0; r < obj.NUM; r++){
    var row = table.insertRow(r+1);
    if(obj.DEVICES[k+1]!=obj.DEVICES[k-1])
      stt=1;
    row.insertCell(0).innerHTML = stt;

    if(obj.DEVICES[k+1]==0)
      row.insertCell(1).innerHTML ="Đồng hồ MFM";
    else if(obj.DEVICES[k+1]==1)
      row.insertCell(1).innerHTML ="Đồng hồ DPM";
    else if(obj.DEVICES[k+1]==2)
       row.insertCell(1).innerHTML = "Inverter SolarBK";

    row.insertCell(2).innerHTML = obj.DEVICES[k];
    row.insertCell(3).innerHTML = "<button  class=\"btn btn-delete\" onclick=\"delete_row_rs485("+(r+1)+")\">Xóa</button>";
    k+=2;
    stt++;
  }
  }

}
function update_istar(obj){
  document.getElementById("serial-number").value = obj.SERIAL_NUMBER;
  update_rs485(obj.RS485);
  var arr = document.getElementById("istar-system-content").children;
  arr[1].value = obj.SYSTEM.TT_MAX;
  arr[5].value = obj.SYSTEM.TBON_MAX;
  arr[9].value = obj.SYSTEM.RCAP;
  arr[13].value = obj.SYSTEM.TANK_VOL;
  arr[17].value = obj.SYSTEM.TBS;
  for(i=0; i<3; i++){
    if(obj.SYSTEM.RELAY_EN&(1<<i)){
      document.getElementById('enable-rl'+(i+1)).checked=true;
    }else{
      document.getElementById('enable-rl'+(i+1)).checked=false;
    }
  }
  if(obj.CONV.TYPE==2){
    document.getElementById('raito-conv-type2').checked =true;
    getRating('raito-conv-type2-content','raito-conv-type1-content','raito-conv-type2-content');
  }
  else{
    document.getElementById('raito-conv-type1').checked =true;
    getRating('raito-conv-type1-content','raito-conv-type2-content','raito-conv-type1-content');
  }
  arr = document.getElementById('convolution-pump-type1').children;
  arr[1].value = obj.CONV.TON;
  arr[5].value = obj.CONV.TOFF
  arr = document.getElementById('convolution-pump-type2').children;
  arr[1].value = obj.CONV.TIMEON/60;
  arr[5].value = obj.CONV.TIMEOFF/60;
  //reuturn
  if(obj.RETURN.TYPE==2){
    document.getElementById('raito-return-type2').checked =true;
    getRating('raito-return-type2-content','raito-return-type1-content','raito-return-type2-content');
  }
  else{
    document.getElementById('raito-return-type1').checked =true;
    getRating('raito-return-type1-content','raito-return-type2-content','raito-return-type1-content');
  }
  arr = document.getElementById('return-pump-type1').children;
  arr[1].value = obj.RETURN.TON;
  arr[5].value = obj.RETURN.TOFF;
  arr = document.getElementById('return-pump-type2').children;
  arr[1].value = obj.RETURN.TIMEON/60;
  arr[5].value = obj.RETURN.TIMEOFF/60;
  //heater
  document.getElementById('HT_ON').value=obj.HEATER.TON;
  //time schedule
  var p = getEntry('istar-slot-time-',5,  true) +1;
  var numb = obj.TIMECHEDULE.NUM;
  for(i=0;i<numb-p; i++){
    addSlotTime('ISTAR');
  }
  var j = 0;
  for(i=0; i<numb; i++){
    var d = new Date();
    arr = document.getElementById('istar-slot-time-'+i).children;
    arr[1].value = parseInt(Number(obj.TIMECHEDULE.SCHEDULE[j])/3600);
    arr[3].value = parseInt((Number(obj.TIMECHEDULE.SCHEDULE[j])%3600/60));
    d.setHours(arr[1].value);
    d.setMinutes(arr[3].value);
    d.setMinutes(d.getMinutes() + parseInt(Number(obj.TIMECHEDULE.SCHEDULE[j+1])/60));
    arr[5].value = d.getHours();
    arr[7].value = d.getMinutes();
    j+=2;
  }
}
function update_other(obj){
  update_rs485(obj.RS485);
  var i=0;
  document.getElementById("serial-number").value = obj.SERIAL_NUMBER;
  for(i = 0; i< 3; i++){
    var num = obj.OTHERSLOT[i].NUM;
    var idx = getEntry('other-rl'+i+'-slot-', 5, true);
    if(obj.MANUAL==1)
      num = 0;
    for(j = (idx+1); j< num; j++){
      addSlotTime(i);
    }
      
    for(j=0; j<num; j++) { // create template{
      var d = new Date();
      var parent = document.getElementById('other-rl'+i+'-slot-'+j).children;
      parent[8].value = obj.OTHERSLOT[i].SLOT[j].TYPE;//type
      parent[1].value = parseInt(Number(obj.OTHERSLOT[i].SLOT[j].TIMESTAR)/3600);
      parent[3].value = parseInt((Number(obj.OTHERSLOT[i].SLOT[j].TIMESTAR)%3600/60));
      d.setHours(parent[1].value);
      d.setMinutes(parent[3].value);
      d.setMinutes(d.getMinutes() + parseInt(Number(obj.OTHERSLOT[i].SLOT[j].DURATION)/60));
      parent[5].value = d.getHours();
      parent[7].value = d.getMinutes();
      other_select_type('other-rl'+i+'-select-'+j, 'other-rl'+i+'-hidden-'+j);
      if(parent[8].value==2){
        var parent = document.getElementById('other-rl'+i+'-hidden-'+j).children;
        var child = parent[0].children;
        child[1].value = obj.OTHERSLOT[i].SLOT[j].TIMEON/60;
        child[3].value = obj.OTHERSLOT[i].SLOT[j].TIMEOFF/60;
      }else if(parent[8].value ==4){
          //
      }
    }
    // manual
    if(obj.MANUAL==0){
      document.getElementById('btn-other-auto').click();
      document.getElementById('manual-rl'+(i+1)).checked =false;
    }
    else{
      document.getElementById('btn-other-manu').click();
        if(obj.MANUALDATA&(1<<i))
            document.getElementById('manual-rl'+(i+1)).checked =true;
        else
            document.getElementById('manual-rl'+(i+1)).checked =false;
    }
  }
}
/**********************************************/
function repair_page() {
  selectProduct();
  for(i=1; i<3; i++){
    duplicate('collapsible-rl0', 'collapsible-rl'+i);
    change_attributeOther('collapsible-rl'+i, i);
  }
  var parent = document.getElementById('collapsible-rl1').children;
  var child = parent[0].children;
  child[0].innerText = "RELAY 2 (300W)"
  parent = document.getElementById('collapsible-rl2').children;
  child = parent[0].children;
  child[0].innerText = "RELAY 3 (300W)"
}
function onResizeScreen(){
  if(window.innerWidth < 1300){
    document.getElementById('lang-content').style.display = "none";
    document.getElementById("mySidenav").style.width = "0px";
    document.getElementById("main").style.marginLeft = "0px";
    //openNav();
  }else{
    if(window.innerWidth>800){
      document.getElementById("mySidenav").style.width = "250px";
      document.getElementById("main").style.marginLeft = "250px";
    }
      //openNav();
     document.getElementById('lang-content').style.display = "block";
  }

}
/**********************************************/
var isFocused = false;
var IntervalTime = setInterval(myTimer, 1000);
//
function myTimer() {
  var d = new Date();
  if(!isFocused){
    for(i = 0; i<1; i++){
      var parent = document.getElementById('device-setting-time'+i).children;
      parent[0].value = d.getHours();
      parent[2].value = d.getMinutes();
      parent[4].value = d.getSeconds();
      parent[6].value = d.getDate();
      parent[8].value =  d.getMonth()+1;
      parent[10].value = d.getFullYear();
    }
  }
}

repair_page();
Websocket();
window.addEventListener("resize", onResizeScreen);
document.onreadystatechange = function () {
  var state = document.readyState
  if (state == 'interactive') {
       document.getElementById('container').style.display="none";
  } else if (state == 'complete') {
    lang_change();
    http_post("m=14","Send default json frame","/c",14);
        if(window.innerWidth < 1300)
          document.getElementById('lang-content').style.display = "none";
        document.getElementById('loading').style.display="none";
        document.getElementById('container').style.display="block";
        document.getElementById('devicecontent').click();
        document.getElementById('tab-wifi-content').click();
         document.getElementById('btn-sidebar').click();
    // document.getElementById("mySidenav").style.width = "0px";
    // document.getElementById("main").style.marginLeft = "0px";
        if(getCookie("username")=='bWFudQ=='){
          var x = document.getElementById('mySidenav');
          x.removeChild(document.getElementById('hwtest'));
          x.removeChild(document.getElementById('deviceset'));
          x.removeChild(document.getElementById('rs485set'));
          document.getElementById("devicecontent").click();
        }
        else {
          document.getElementById("devicecontent").click();
        }
  }
}

function getCookie(cname) {
  var name = cname + "=";
  var decodedCookie = decodeURIComponent(document.cookie);
  var ca = decodedCookie.split(';');
  for(var i = 0; i < ca.length; i++) {
    var c = ca[i];
    while (c.charAt(0) == ' ') {
      c = c.substring(1);
    }
    if (c.indexOf(name) == 0) {
      return c.substring(name.length, c.length);
    }
  }
  return "";
}
window.onload = function() {
  var parent = document.getElementsByClassName('time-field');
  for(i=0; i<parent.length; i++){
    parent[i].onfocus = function(){
      isFocused=true;
    };
    parent[i].onblur = function(){
      isFocused = false;
    };
  }
}

document.getElementById("uploadBtn").onchange = function () {
    document.getElementById("uploadFile").value = this.value.replace(/^.*(\\|\/|\:)/, '');;
};