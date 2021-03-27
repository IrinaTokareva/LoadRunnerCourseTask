int i;
char tmp[128];

Action()
{
	
	lr_start_transaction("UC_04_BuyTickets");
	
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

	web_add_auto_header("Origin", 
		"http://localhost:1080");
	
	web_reg_save_param_regexp(
		"ParamName=flightNums",
		"RegExp=name\=\"outboundFlight\" value\=\"(.*?)\"",
		"Ordinal=All",
		SEARCH_FILTERS,
		LAST);
	
//	web_reg_save_param_regexp(
//		"ParamName=flightPrices",
//		"RegExp=>\$\s*(.*?)<",
//		"Ordinal=All",
//		SEARCH_FILTERS,
//		LAST);
	
	web_reg_find("Text=Flight departing from <B>{departureCity}</B> to <B>{arrivalCity}</B> on <B>{departureDate}</B>",
		LAST);

	web_submit_form("reservations.pl", 
		"Snapshot=t6.inf", 
		ITEMDATA, 
		"Name=depart", "Value={departureCity}", ENDITEM, 
		"Name=departDate", "Value={departureDate}", ENDITEM, 
		"Name=arrive", "Value={arrivalCity}", ENDITEM, 
		"Name=returnDate", "Value={arrivalDate}", ENDITEM, 
		"Name=numPassengers", "Value={passengersNum}", ENDITEM, 
		"Name=roundtrip", "Value=<OFF>", ENDITEM, 
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM,
		"Name=findFlights.x", "Value=10", ENDITEM, 
		"Name=findFlights.y", "Value=10", ENDITEM, 
		LAST);
	
	lr_save_string(lr_paramarr_random("flightNums"), "flightNum");
	
//	for (i = 0; i < atoi(lr_eval_string("{flightNums_count}")); i++) {
//		sprintf(tmp, "{flightNums_%i}", i + 1);
//		if (strcmp(lr_eval_string(tmp), lr_eval_string("{flightNum}")) == 0) {
//			sprintf(tmp, "{flightPrices_%i}", i + 1);
//			lr_save_string((char*)(atoi(lr_eval_string("passengersNum")) * atoi(lr_eval_string(tmp))), "flightTotal");
//		}
//	}
	
	lr_end_transaction("search_flights", LR_AUTO);

	lr_start_transaction("choose_flight");
	
	web_reg_find("Text=<title>Flight Reservation</title>",
		LAST);
	
//	web_reg_find("Text=Total for {passengersNum} ticket(s) is \= $ {flightTotal}",
//		LAST);

	web_submit_form("reservations.pl_2", 
		"Snapshot=t7.inf", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={flightNum}", ENDITEM, 
		"Name=reserveFlights.x", "Value=59", ENDITEM, 
		"Name=reserveFlights.y", "Value=6", ENDITEM, 
		LAST);
	
	lr_end_transaction("choose_flight", LR_AUTO);

	lr_start_transaction("buy_ticket");

	web_revert_auto_header("Origin");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(21);
	
	web_reg_find("Text=<title>Reservation Made!</title>",
		LAST);
	
	web_reg_find("Text={firstName}{lastName}'s Flight Invoice",
	    LAST);
	
	web_reg_find("Text={seatType} Class tickets from {departureCity} to {arrivalCity}.",
	    LAST);
	
	web_reg_find("Text= Total Charged to Credit Card # {cardNumber}",
	    LAST);
	
//	web_reg_find("Text=<b> ${flightTotal} </b>",
//	    LAST);
	
	if (atoi(lr_eval_string("{passengersNum}")) == 3) {
		web_submit_form("reservations.pl_3", 
		"Snapshot=t8.inf", 
		ITEMDATA, 
		"Name=firstName", "Value={firstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={street}", ENDITEM, 
		"Name=address2", "Value={address}", ENDITEM, 
		"Name=pass1", "Value={firstName} {lastName}", ENDITEM, 
		"Name=pass2", "Value=Passenger 2", ENDITEM, 
		"Name=pass3", "Value=Passenger 3", ENDITEM, 
		"Name=creditCard", "Value={cardNumber}", ENDITEM, 
		"Name=expDate", "Value={expDate}", ENDITEM, 
		"Name=saveCC", "Value=<OFF>", ENDITEM, 
		"Name=buyFlights.x", "Value=10", ENDITEM, 
		"Name=buyFlights.y", "Value=10", ENDITEM, 
		LAST);
	} else if (atoi(lr_eval_string("{passengersNum}")) == 4) {
		web_submit_form("reservations.pl_3",
		"Snapshot=t9.inf", 
		ITEMDATA, 
		"Name=firstName", "Value={firstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={street}", ENDITEM, 
		"Name=address2", "Value={address}", ENDITEM, 
		"Name=pass1", "Value={firstName} {lastName}", ENDITEM, 
		"Name=pass2", "Value=Passenger 2", ENDITEM, 
		"Name=pass3", "Value=Passenger 3", ENDITEM, 
		"Name=pass4", "Value=Passenger 4", ENDITEM, 
		"Name=creditCard", "Value={cardNumber}", ENDITEM, 
		"Name=expDate", "Value={expDate}", ENDITEM, 
		"Name=saveCC", "Value=<OFF>", ENDITEM, 
		"Name=buyFlights.x", "Value=10", ENDITEM, 
		"Name=buyFlights.y", "Value=10", ENDITEM, 
		LAST);
	} else if (atoi(lr_eval_string("{passengersNum}")) == 5) {
		web_submit_form("reservations.pl_3",
		"Snapshot=t10.inf", 
		ITEMDATA, 
		"Name=firstName", "Value={firstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={street}", ENDITEM, 
		"Name=address2", "Value={address}", ENDITEM, 
		"Name=pass1", "Value={firstName} {lastName}", ENDITEM, 
		"Name=pass2", "Value=Passenger 2", ENDITEM, 
		"Name=pass3", "Value=Passenger 3", ENDITEM, 
		"Name=pass4", "Value=Passenger 4", ENDITEM, 
		"Name=pass5", "Value=Passenger 5", ENDITEM, 
		"Name=creditCard", "Value={cardNumber}", ENDITEM, 
		"Name=expDate", "Value={expDate}", ENDITEM, 
		"Name=saveCC", "Value=<OFF>", ENDITEM, 
		"Name=buyFlights.x", "Value=10", ENDITEM, 
		"Name=buyFlights.y", "Value=10", ENDITEM, 
		LAST);
	}
	
	lr_end_transaction("buy_ticket", LR_AUTO);
	
	lr_start_transaction("logout");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(7);
	
	web_reg_find("Text=Welcome to the Web Tours site.",
		LAST);
	
	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t12.inf", 
		LAST);
	
	lr_end_transaction("logout", LR_AUTO);

	lr_end_transaction("UC_04_BuyTickets", LR_AUTO);

	return 0;
}