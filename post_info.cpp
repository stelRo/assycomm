/*
 * post_info.cpp ---- settings and values for sql querys!
 * Copyright (c) 2015 Stelmach Ro
 *
 * Author: Stelmach Ro (xtasy) <stelmach.ro@gmail.com>
 *
 * This file is part of Assy Comm.
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <string>

#include "conflib.h"
#include "post_info.h"

#define MAX_CONTENT 1000

using namespace std;

assycom::assycom() {
}

assycom::~assycom() {
    
    delete [] post_content;
}

void assycom::read_text() {
    
    post_content = new string[MAX_CONTENT];
    
    if(post_content == NULL) {
        cout << "Allocation Error" << endl;
        exit(1);
    }

    cin.ignore();
    getline(cin, *post_content);
}

string assycom::return_values(string file_path) {
	ConfigFile cfg(file_path); // file call for config.cfg configuration file ! 
	string command; // Magic string , sql query will be placed here 
	string systemDateAndTime; // System date and locl time placed here , in following format : yy-mm-dd hh:mm:ss 
	systemDateAndTime = return_system_date();

	string post_com;

	//All Cals with Values from config.cfg file for sql query! 
	string post_author = cfg.getValueOfKey<string>("post_author");
	string post_date = cfg.getValueOfKey<string>("post_date");
	string post_date_gmt = cfg.getValueOfKey<string>("post_date_gmt");
	string post_excerpt = cfg.getValueOfKey<string>("post_excerpt");
	string post_status = cfg.getValueOfKey<string>("post_status");
	string comment_status = cfg.getValueOfKey<string>("comment_status");
	string ping_status = cfg.getValueOfKey<string>("ping_status");
	string post_password = cfg.getValueOfKey<string>("post_password");
	string to_ping = cfg.getValueOfKey<string>("to_ping");
	string pinged = cfg.getValueOfKey<string>("pinged");
	string post_modified = cfg.getValueOfKey<string>("post_modified");
	string post_modified_gmt = cfg.getValueOfKey<string>("post_modified_gmt");
	string post_content_filtered = cfg.getValueOfKey<string>("post_content_filtered");
	string post_parent = cfg.getValueOfKey<string>("post_parent");
	string guid = cfg.getValueOfKey<string>("guid");
	string menu_order = cfg.getValueOfKey<string>("menu_order");
	string post_type = cfg.getValueOfKey<string>("post_type");
	string post_mine_type = cfg.getValueOfKey<string>("post_mime_type");
	string comment_count = cfg.getValueOfKey<string>("comment_count");
	
	string table_name = cfg.getValueOfKey<string>("table_name");


	/* -------------------- */
	char q = '\''; //Single Quation Mark
	char c = ',';  // Comma
	
	/* --------------------- */

	string defSta = "INSERT INTO " + table_name 
		+ "(post_author,post_date,post_date_gmt,post_content,post_title,post_status,comment_status,ping_status,post_name,post_modified,post_modified_gmt,post_parent,guid,menu_order,post_type,comment_count)" + " VALUES";

	


	//if sys_date = true in config.cfg for values below , return systemDateAndTime Local time
	//otherwise return NULL! 
	
	if(post_date == "sys_date")
		post_date = systemDateAndTime;
	else
		post_date = "NULL";

	if(post_date_gmt == "sys_date")
		post_date_gmt = systemDateAndTime;
	else
		post_date_gmt = "NULL";

	if(post_modified == "sys_date")
		post_modified = systemDateAndTime;
	else
		post_modified = "NULL";

	if(post_modified_gmt == "sys_date")
		post_modified_gmt = systemDateAndTime;
	else
		post_modified_gmt = "NULL";

	//Comment status , true = open, otherwise closed.
	if(post_comment_status)//true
		post_com = "open";
	else					//false
		post_com = "close";

//Command for mySql Service query, to insert values into the table
	command = 
		defSta + '(' + post_author + c + q + post_date + q + c + q + post_date_gmt + q + c + q 
		 + *post_content + q + c + q + post_title + q + c + q + post_status + q + c + q + post_com 
		+ q + c + q + ping_status + q + c + q + post_name  + q + c + q + post_modified  + q + c + q + 
		 post_modified_gmt + q + c + q + post_parent  + q + c + q + guid  + q + c +  menu_order + c + q + 
		post_type  + q + c + comment_count +')';
		
		return command;
}

void assycom::user_define(string title,bool comment_status,string post_name) {
	post_title = title;
	post_name = post_name;
	post_comment_status = comment_status;
}
string assycom::return_system_date(void) {

	//Get the system date and time
	time_t t = time(0);
	struct tm *now = localtime(&t);
	string sysdate;

	//Calling from <ctime> or <time.h> system date and time, and converting to string from int with ostrinstream!
	//Converting from int to string
	int day = now->tm_mday;				ostringstream day_;				day_ << day;
	int month = now->tm_mon + 1;		ostringstream month_;			month_ << month;
	int year = now->tm_year + 1900;		ostringstream year_;			year_ << year;
	int hour = now->tm_hour;			ostringstream hour_;			hour_ << hour;
	int min = now->tm_min;				ostringstream min_;				min_ << min;
	int sec = now->tm_sec;				ostringstream sec_;				sec_ << sec;

	//return string for sys_date value
	sysdate = year_.str() + '-' + month_.str() + '-' + day_.str() + ' ' + hour_.str() + ':' + min_.str() + ':' + sec_.str();

	return sysdate;
}
