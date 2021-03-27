Action()
{
	
	lr_start_transaction("UC_03_SearchFlights");
	
	lr_start_transaction("open_main_page");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");
	
	web_reg_find("Text=Welcome to the Web Tours site.",
		LAST);

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"Resource=0", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("open_main_page", LR_AUTO);

	lr_start_transaction("login");

	web_set_sockets_option("SSL_VERSION", "2");

	web_add_header("Origin", 
		"http://localhost:1080");
	
	web_reg_find("Text=Welcome, <b>{username}</b>, to the Web Tours reservation pages.",
		LAST);

	web_submit_form("login.pl", 
		"Snapshot=t4.inf", 
		ITEMDATA, 
		"Name=username", "Value={username}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		LAST);
	
	lr_end_transaction("login", LR_AUTO);

	lr_start_transaction("open_flights_page");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");
	
	web_reg_save_param_regexp(
		"ParamName=cities",
		"RegExp=value\=\"(.*?)\">.*?</option>",
		"Ordinal=All",
		SEARCH_FILTERS,
		LAST);
	
	web_reg_save_param_regexp(
		"ParamName=seatPrefs",
		"RegExp=name\=\"seatPref\" value\=\"(.*?)\".*?</label>",
		"Ordinal=All",
		SEARCH_FILTERS,
		LAST);
	
	web_reg_save_param_regexp(
		"ParamName=seatTypes",
		"RegExp=name\=\"seatType\" value\=\"(.*?)\".*?</label>",
		"Ordinal=All",
		SEARCH_FILTERS,
		LAST);
	
	web_reg_find("Text=<title>Flight Selections</title>",
		LAST);
	
	web_reg_find("Text=Departure City :",
		LAST);

	web_image("Search Flights Button", 
		"Alt=Search Flights Button", 
		"Snapshot=t5.inf", 
		LAST);
	
	lr_save_string(lr_paramarr_random("cities"), "departureCity");
	lr_save_string(lr_paramarr_random("cities"), "arrivalCity");
	while (strcmp(lr_eval_string("{departureCity}"), lr_eval_string("{arrivalCity}")) == 0)
	{
		lr_save_string(lr_paramarr_random("cities"), "arrivalCity");
	}
	
	lr_save_string(lr_paramarr_random("seatPrefs"), "seatPref");
	lr_save_string(lr_paramarr_random("seatTypes"), "seatType");
	
	lr_end_transaction("open_flights_page", LR_AUTO);

	lr_start_transaction("search_flights");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(4);
	
	web_reg_find("Text=Flight departing from <B>{departureCity}</B> to <B>{arrivalCity}</B> on <B>{departureDate}</B>",
		LAST);

	web_submit_form("reservations.pl", 
		"Snapshot=t6.inf", 
		ITEMDATA, 
		"Name=depart", "Value={departureCity}", ENDITEM, 
		"Name=departDate", "Value={departureDate}", ENDITEM, 
		"Name=arrive", "Value={arrivalCity}", ENDITEM, 
		"Name=returnDate", "Value={arrivalDate}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=roundtrip", "Value=<OFF>", ENDITEM, 
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM,
		"Name=findFlights.x", "Value=10", ENDITEM, 
		"Name=findFlights.y", "Value=10", ENDITEM,
		LAST);
	
	lr_end_transaction("search_flights", LR_AUTO);
	
	lr_start_transaction("logout");
	
	web_reg_find("Text=Welcome to the Web Tours site.",
		LAST);

	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t7.inf", 
		LAST);
	
	lr_end_transaction("logout", LR_AUTO);

	lr_end_transaction("UC_03_SearchFlights", LR_AUTO);

	return 0;
}