Action()
{

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_url("WebTours", 
		"URL=http://10.0.0.10:1080/WebTours/", 
		"Resource=0", 
		"Referer=", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		LAST);

	web_url("header.html", 
		"URL=http://10.0.0.10:1080/WebTours/header.html", 
		"Resource=0", 
		"Referer=http://10.0.0.10:1080/WebTours/", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);

	web_url("welcome.pl", 
		"URL=http://10.0.0.10:1080/cgi-bin/welcome.pl?signOff=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://10.0.0.10:1080/WebTours/", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		LAST);

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_url("login.pl", 
		"URL=http://10.0.0.10:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://10.0.0.10:1080/WebTours/home.html", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		LAST);

	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_add_header("Origin", 
		"http://10.0.0.10:1080");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(9);

	web_submit_form("login.pl_2", 
		"Snapshot=t10.inf", 
		ITEMDATA, 
		"Name=username", "Value=jhgfd", ENDITEM, 
		"Name=password", "Value=hg", ENDITEM, 
		"Name=passwordConfirm", "Value=hg", ENDITEM, 
		"Name=firstName", "Value=ytrfds", ENDITEM, 
		"Name=lastName", "Value=tfds", ENDITEM, 
		"Name=address1", "Value=ygfds", ENDITEM, 
		"Name=address2", "Value=gfds", ENDITEM, 
		"Name=register.x", "Value=70", ENDITEM, 
		"Name=register.y", "Value=8", ENDITEM, 
		LAST);

	return 0;
}