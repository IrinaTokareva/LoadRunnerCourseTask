int i;
int j;
char tmp[128];
char tmp_2[128];
int resDeleted;

Action()
{
	
	lr_start_transaction("UC_05_CancelReservations");
	
	open_main_page_transaction();
	
	lr_think_time(7);

	login_transaction();
	
	open_itinerary_transaction(1);
	
	lr_think_time(4);

	lr_start_transaction("cancel_reservations");

	web_add_header("Origin", 
		"http://localhost:1080");
	
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
			sprintf(tmp_2, "deletedFlightIds_%i", j + 1);
			if (strcmp(lr_eval_string(tmp), lr_eval_string(tmp_2)) == 0) {
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
	
	logout_transaction();

	lr_end_transaction("UC_05_CancelReservations", LR_AUTO);

	return 0;
}