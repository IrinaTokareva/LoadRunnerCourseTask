int i;
int j;
char tmp[128];
char *deletedFlightIds[3];
int resDeleted;

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
		"Snapshot=t27.inf", 
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
		"Snapshot=t30.inf", 
		ITEMDATA, 
		"Name=username", "Value={username}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		LAST);
	
	lr_end_transaction("login", LR_AUTO);

	lr_start_transaction("open_itinerary");
	
	web_reg_save_param_regexp(
		"ParamName=flightIds",
		"RegExp=input type\=\"hidden\" name\=\"flightID\" value\=\"(.*?)\"",
		"Ordinal=All",
		SEARCH_FILTERS,
		LAST);
	
	web_reg_find("Text={firstName} {lastName}\n 's Flight Transaction Summary",
		LAST);

	web_image("Itinerary Button", 
		"Alt=Itinerary Button", 
		"Snapshot=t10.inf", 
		LAST);
	
	for (i = 0; i < atoi(lr_eval_string("{reservationsNum}")); i++) {
		sprintf(tmp, "{flightIds_%i}", i + 1);
		deletedFlightIds[i] = lr_eval_string(tmp);
	}
	
	lr_end_transaction("open_itinerary", LR_AUTO);

	lr_start_transaction("cancel_reservations");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(4);
	
	web_reg_save_param_regexp(
		"ParamName=newFlightIds",
		"RegExp=input type\=\"hidden\" name\=\"flightID\" value\=\"(.*?)\"",
		"Ordinal=All",
		SEARCH_FILTERS,
		LAST);
	
	if (atoi(lr_eval_string("{reservationsNum}")) == 1) {
		web_submit_form("itinerary.pl", 
		"Snapshot=t11.inf", 
		ITEMDATA, 
		"Name=1", "Value=on", ENDITEM, 
		"Name=removeFlights.x", "Value=10", ENDITEM, 
		"Name=removeFlights.y", "Value=10", ENDITEM,
		LAST);
	} else if (atoi(lr_eval_string("{reservationsNum}")) == 2) {
		web_submit_form("itinerary.pl", 
		"Snapshot=t12.inf", 
		ITEMDATA, 
		"Name=1", "Value=on", ENDITEM, 
		"Name=2", "Value=on", ENDITEM, 
		"Name=removeFlights.x", "Value=10", ENDITEM, 
		"Name=removeFlights.y", "Value=10", ENDITEM,
		LAST);
	} else if (atoi(lr_eval_string("{reservationsNum}")) == 3) {
		web_submit_form("itinerary.pl", 
		"Snapshot=t13.inf", 
		ITEMDATA, 
		"Name=1", "Value=on", ENDITEM, 
		"Name=2", "Value=on", ENDITEM, 
		"Name=3", "Value=on", ENDITEM, 
		"Name=removeFlights.x", "Value=10", ENDITEM, 
		"Name=removeFlights.y", "Value=10", ENDITEM,
		LAST);
	}
	
	resDeleted = 0;
	for (i = 0; i < atoi(lr_eval_string("{newFlightIds_count}")); i++) {
		sprintf(tmp, "{newFlightIds_%i}", i + 1);
		for (j = 0; j < atoi(lr_eval_string("{reservationsNum}")); j++) {
			if (strcmp(lr_eval_string(tmp), deletedFlightIds[j]) == 0) {
				resDeleted = 1;
				continue;
			}
		}
	}
	
	if (resDeleted == 0) {
		lr_end_transaction("cancel_reservations", LR_AUTO);
	} else {
		lr_end_transaction("cancel_reservations", LR_FAIL);
	}
	
	lr_start_transaction("logout");
	
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