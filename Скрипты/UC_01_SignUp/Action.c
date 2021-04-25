char tmp[128];

Action()
{
	
	lr_start_transaction("UC_01_SignUp");

	open_main_page_transaction();

	lr_start_transaction("open_sign_up_page");

	web_set_sockets_option("SSL_VERSION", "2");
	
	web_reg_find("Text=First time registering? Please complete the form below.",
	    LAST);

	web_link("sign up now", 
		"Text=sign up now", 
		"Snapshot=t4.inf", 
		LAST);
	
	lr_end_transaction("open_sign_up_page", LR_AUTO);
	
	lr_think_time(11);
	
	lr_start_transaction("sign_up");

	web_add_header("Origin", 
		"http://localhost:1080");
	
	lr_save_string((char*)lr_short_guid_no_dashes_gen(), "guid");
	
	sprintf(tmp, "user%s", lr_eval_string("{guid}"));
	lr_save_string(tmp, "username");
	
	sprintf(tmp, "pass%s", lr_eval_string("{guid}"));
	lr_save_string(tmp, "password");

	web_reg_find("Text=Thank you, <b>{username}</b>, for registering and welcome to the Web Tours family.",
	    LAST);

	web_submit_form("login.pl_2", 
		"Snapshot=t5.inf", 
		ITEMDATA, 
		"Name=username", "Value={username}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=passwordConfirm", "Value={password}", ENDITEM, 
		"Name=firstName", "Value=Name{guid}", ENDITEM, 
		"Name=lastName", "Value=Surname{guid}", ENDITEM, 
		"Name=address1", "Value=address1-{guid}", ENDITEM, 
		"Name=address2", "Value=address2-{guid}", ENDITEM, 
		"Name=register.x", "Value=54", ENDITEM, 
		"Name=register.y", "Value=5", ENDITEM, 
		LAST);
	
	lr_end_transaction("sign_up", LR_AUTO);
	
	open_main_page_transaction();
	
	lr_think_time(7);
	
	login_transaction();

	lr_end_transaction("UC_01_SignUp", LR_AUTO);

	return 0;
}

char* lr_short_guid_no_dashes_gen(){
    typedef struct _GUID {
        unsigned long Data1;
        unsigned short Data2;
        unsigned short Data3;
        unsigned char Data4[8];
    } 
    GUID;
    GUID m_guid;
    char buf[50];
    char bufx[50];
    lr_load_dll("ole32.dll");
    CoCreateGuid(&m_guid);
    
    sprintf(buf, "%05lX",
    m_guid.Data1);

    return lr_eval_string(buf);
}