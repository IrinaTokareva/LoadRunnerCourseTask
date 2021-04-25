Action()
{
	
	lr_start_transaction("UC_04_BuyTickets");
	
	open_main_page_transaction();
	
	lr_think_time(7);

	login_transaction();

	open_flights_page_transaction();
	
	lr_think_time(10);

	search_flights_transaction(1);

	choose_flight_transaction();
	
	lr_think_time(21);

	lr_start_transaction("buy_ticket");

	web_revert_auto_header("Origin");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");
	
	web_reg_find("Text=<title>Reservation Made!</title>",
		LAST);
	
	web_reg_find("Text={firstName}{lastName}'s Flight Invoice",
	    LAST);
	
	web_reg_find("Text={seatType} Class tickets from {departureCity} to {arrivalCity}.",
	    LAST);
	
	web_reg_find("Text= Total Charged to Credit Card # {cardNumber}",
	    LAST);
	
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
		lr_end_transaction("buy_ticket", LR_AUTO);
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
		lr_end_transaction("buy_ticket", LR_AUTO);
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
		lr_end_transaction("buy_ticket", LR_AUTO);
	} else {
        lr_output_message("Buy ticket request is not implemented for number of passengers {passengersNum}");
        lr_end_transaction("buy_ticket", LR_FAIL);
    }
	
	logout_transaction();

	lr_end_transaction("UC_04_BuyTickets", LR_AUTO);

	return 0;
}