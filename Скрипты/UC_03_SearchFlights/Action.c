Action()
{
	
	lr_start_transaction("UC_03_SearchFlights");
	
	open_main_page_transaction();
	
	lr_think_time(7);

	login_transaction();

	open_flights_page_transaction();
	
	lr_think_time(10);

	search_flights_transaction(1);
	
	choose_flight_transaction();
	
	open_itinerary_transaction(0);
	
	logout_transaction();

	lr_end_transaction("UC_03_SearchFlights", LR_AUTO);

	return 0;
}