Action()
{
	
	lr_start_transaction("UC_02_LoginAndLogout");

	open_main_page_transaction();
	
	lr_think_time(7);
	
	login_transaction();
	
	open_flights_page_transaction();
	
	lr_think_time(10);

	search_flights_transaction(0);

	lr_end_transaction("UC_02_LoginAndLogout", LR_AUTO);

	return 0;
}