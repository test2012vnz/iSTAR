
function http_handle(handle){

}
function http_post(mess,err,url,handle){
	var xhttp = new XMLHttpRequest();
	xhttp.onload=function(){
		if(this.readyState==4 && this.status==200){
			
			switch(handle){
				case 0:
				if(this.responseText!="err")
					document.getElementById(this.responseText).submit();
				else
					document.cookie = "username=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;";
				break;
				case 1:
				if(this.responseText!="err"){
					setCookie("username",this.responseText,30);
					document.getElementById("login").submit();
				}
				else{
					alert("Sai thông tin đăng nhập");
				}
				break;
			}
		}else{
			alert(err + this.status);
		}
	}
	xhttp.ontimeout=function(){
		alert(err );
	}
	xhttp.timeout = 10000;
	xhttp.open("POST", url, true);

	xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
	xhttp.send(mess);
}

function setCookie(cname,cvalue,exdays) {
	var d = new Date();
	d.setTime(d.getTime() + (exdays*24*60*60*1000));
	var expires = "expires=" + d.toGMTString();
	document.cookie = cname + "=" + cvalue + ";" + expires + ";path=/";
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

function checkCookie() {
	var user=getCookie("username");
	if (user != "") {
		var mes='m=0'+'&user='+user;
		http_post(mes,"","/c",0);
	}
}

function Login(){
	var user=document.getElementById("user").value;
	var pass=document.getElementById("pass").value;

	if(user!="" && pass!=""){
		var mes="m=1&user="+user+"&pass="+pass;
		http_post(mes,"Login Err","/c",1);
	}
}
  	checkCookie();