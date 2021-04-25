#ifndef _LR_COURSE_LIB_H_
#define _LR_COURSE_LIB_H_

int i;
int j;
char tmp[128];
char tmp_2[128];

void open_main_page_transaction() {
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
}

void login_transaction() {
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
}

void open_flights_page_transaction() {
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
}

void search_flights_transaction(int chooseFlight) {
    lr_start_transaction("search_flights");

    web_add_auto_header("Origin", 
        "http://localhost:1080");

    if (chooseFlight == 1) {
        web_reg_save_param_regexp(
            "ParamName=flightNums",
            "RegExp=name\=\"outboundFlight\" value\=\"(.*?)\"",
            "Ordinal=All",
             SEARCH_FILTERS,
             LAST);
    }
	
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

    if (chooseFlight == 1) {
        lr_save_string(lr_paramarr_random("flightNums"), "flightNum");
    }

    lr_end_transaction("search_flights", LR_AUTO);
}

void choose_flight_transaction() {
    lr_start_transaction("choose_flight");
	
    web_reg_find("Text=<title>Flight Reservation</title>",
        LAST);

    web_submit_form("reservations.pl_2", 
        "Snapshot=t7.inf", 
        ITEMDATA, 
        "Name=outboundFlight", "Value={flightNum}", ENDITEM, 
        "Name=reserveFlights.x", "Value=59", ENDITEM, 
        "Name=reserveFlights.y", "Value=6", ENDITEM, 
        LAST);

    lr_end_transaction("choose_flight", LR_AUTO);
}

void open_itinerary_transaction(int delete_smth_afterwards) {
    lr_start_transaction("open_itinerary");

    if (delete_smth_afterwards == 1) {
        web_reg_save_param_regexp(
            "ParamName=flightIds",
            "RegExp=input type\=\"hidden\" name\=\"flightID\" value\=\"(.*?)\"",
            "Ordinal=All",
            SEARCH_FILTERS,
            LAST);
    }

    web_reg_find("Text={firstName} {lastName}\n 's Flight Transaction Summary",
        LAST);

    web_image("Itinerary Button", 
        "Alt=Itinerary Button", 
        "Snapshot=t10.inf", 
        LAST);

    if (delete_smth_afterwards == 1) {
        for (i = 0; i < atoi(lr_eval_string("{reservationsNum}")); i++) {
            sprintf(tmp, "{flightIds_%i}", i + 1);
            sprintf(tmp_2, "deletedFlightIds_%i", i + 1);
            lr_save_string(lr_eval_string(tmp), tmp_2);
        }
    }

    lr_end_transaction("open_itinerary", LR_AUTO);
}

void logout_transaction() {
    lr_start_transaction("logout");
	
    web_reg_find("Text=Welcome to the Web Tours site.",
        LAST);

    web_image("SignOff Button", 
        "Alt=SignOff Button", 
        "Snapshot=t5.inf", 
        LAST);

    lr_end_transaction("logout", LR_AUTO);
}

#endif // _LR_COURSE_LIB_H_