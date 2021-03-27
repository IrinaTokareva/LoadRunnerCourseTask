Action()
{

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_url("WebTours", 
		"URL=http://10.0.0.10:1080/WebTours/", 
		"Resource=0", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	web_url("header.html", 
		"URL=http://10.0.0.10:1080/WebTours/header.html", 
		"Resource=0", 
		"Referer=http://10.0.0.10:1080/WebTours/", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	web_url("welcome.pl", 
		"URL=http://10.0.0.10:1080/cgi-bin/welcome.pl?signOff=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://10.0.0.10:1080/WebTours/", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_add_header("Origin", 
		"http://10.0.0.10:1080");

	web_submit_form("login.pl", 
		"Snapshot=t4.inf", 
		ITEMDATA, 
		"Name=username", "Value=jojo", ENDITEM, 
		"Name=password", "Value=bean", ENDITEM, 
		LAST);

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_image("Search Flights Button", 
		"Alt=Search Flights Button", 
		"Snapshot=t5.inf", 
		LAST);

	web_add_header("Origin", 
		"http://10.0.0.10:1080");

	lr_think_time(4);

	web_submit_form("reservations.pl", 
		"Snapshot=t6.inf", 
		ITEMDATA, 
		"Name=depart", "Value=Denver", ENDITEM, 
		"Name=departDate", "Value=03/24/2021", ENDITEM, 
		"Name=arrive", "Value=Portland", ENDITEM, 
		"Name=returnDate", "Value=03/25/2021", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=roundtrip", "Value=<OFF>", ENDITEM, 
		"Name=seatPref", "Value=None", ENDITEM, 
		"Name=seatType", "Value=Coach", ENDITEM, 
		LAST);

	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t7.inf", 
		LAST);

	return 0;
}