/**
 * main.cpp ---- main functions executed ! 
 * Copyright (c) 2015 Stelmach Ro 
 * 
 * Author: Stelmach Ro (xtasy) <stelmach.ro@gmail.com>
 *
 * This file is part of Assy Comm.
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <iostream>
#include <vector>
#include <string>

#include "mysql_connection.h"
#include "sql_info.h"
#include "post_info.h"
#include "conflib.h"

using namespace std;

typedef struct {

    bool POST_INFO;

}param_info;


int main(int argc, char const **argv)
{	
        param_info param;
        vector<string> args(argv, argv+argc);
	string login_name;
	string login_pass;
        
        for (size_t i = 1; i < args.size(); ++i) {
            
            if(args[i] == "-p")
                param.POST_INFO = true;
        }
        
	cout << "mySQL name: ";
	cin >> login_name;
	cout << "Password: ";
	cin >> login_pass;
	cin.ignore();
	cout << endl;        
	
        sql_requests sql_info(login_name,login_pass);

        if(sql_info.sql_connect() != 0)
            cout << "Connected.." << "\n";
        else
            cout << "Faild to Connect.. " << "\n";
        
        //stcl.sqlConnect();
        cout << "ID : " << sql_info.sql_get_id() << endl;
	sql_info.set_post_info();

	sql_info.sql_query();
        
        //If true, post post info querys in terminal
        if(param.POST_INFO)
    	    sql_info.print_post_info();
         

        //cout << "ID: " << stcl.sqlGetId() << endl;
	
	return EXIT_SUCCESS;
	
}
