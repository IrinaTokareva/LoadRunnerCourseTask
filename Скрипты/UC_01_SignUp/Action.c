Action()
{
	
	lr_start_transaction("UC_01_SignUp");
	
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

	lr_start_transaction("open_sign_up_page");

	web_set_sockets_option("SSL_VERSION", "2");
	
	web_reg_find("Text=First time registering? Please complete the form below.",
	    LAST);

	web_url("login.pl", 
		"URL=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/home.html", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("open_sign_up_page", LR_AUTO);
	
	lr_start_transaction("sign_up");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(11);
	
	lr_save_string((char*)lr_guid_no_dashes_gen(), "guid");
	
	web_reg_find("Text=Thank you, <b>user{guid}</b>, for registering and welcome to the Web Tours family.",
	    LAST);

	web_submit_form("login.pl_2", 
		"Snapshot=t5.inf", 
		ITEMDATA, 
		"Name=username", "Value=user{guid}", ENDITEM, 
		"Name=password", "Value=pass{guid}", ENDITEM, 
		"Name=passwordConfirm", "Value=pass{guid}", ENDITEM, 
		"Name=firstName", "Value=Name{guid}", ENDITEM, 
		"Name=lastName", "Value=Surname{guid}", ENDITEM, 
		"Name=address1", "Value=address1-{guid}", ENDITEM, 
		"Name=address2", "Value=address2-{guid}", ENDITEM, 
		"Name=register.x", "Value=54", ENDITEM, 
		"Name=register.y", "Value=5", ENDITEM, 
		LAST);
	
	lr_end_transaction("sign_up", LR_AUTO);

	lr_end_transaction("UC_01_SignUp", LR_AUTO);

	return 0;
}

char* lr_guid_no_dashes_gen(){
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

    sprintf(buf, "%08lX%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X",
    m_guid.Data1, m_guid.Data2, m_guid.Data3,
    m_guid.Data4[0], m_guid.Data4[1], m_guid.Data4[2], m_guid.Data4[3],
    m_guid.Data4[4], m_guid.Data4[5], m_guid.Data4[6], m_guid.Data4[7]);

    return lr_eval_string(buf);
}