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
#include "help_lib.h"

using namespace std;

typedef struct {

    bool POST_INFO;

}param_info;

int main(int argc, char const **argv)
{	
        param_info param;
        getHelp help_lib;

        string get_command;
        vector<string> args(argv, argv+argc);
	string login_name;
	string login_pass;
        
        for (size_t i = 1; i < args.size(); ++i) {
            
            if(args[i] == "-p")
                param.POST_INFO = true;
        }
        cout << endl;
        cout << "[-].. mySQL info " << endl;
	cout << "[+].. username: ";
	cin >> login_name;
	cout << "[+].. password: ";
	cin >> login_pass;
	cin.ignore();
	cout << endl;        
	
        sql_requests sql_info(login_name,login_pass);

        if(sql_info.sql_connect() != 0)
            cout << "[-].. connected successfully! " << endl;
        else
            cout << "[-].. faild to connect.. " << endl;
        
        //stcl.sqlConnect();
        //cout << "ID : " << sql_info.sql_get_id() << endl;

        
        for( ; ; ) {
            
            cout << "[operation]: ";
            cin >> get_command;
            cin.ignore();

            if ( get_command == "exit" )
                break;
            if (get_command == "help" )
                help_lib.show_help_msg();

            if ( get_command == "post" ) {
                sql_info.set_post_info();
                if(sql_info.sql_query())
                    cout << "[-].. posted successfully! " << endl;

            }
            else
                cout << "[~].. command not found ! " << endl;
        
        }

        //If true, print post info querys in terminal
        if(param.POST_INFO)
    	    sql_info.print_post_info();
         

        cout << "ID: " << sql_info.sql_get_id() << endl;
	
	return EXIT_SUCCESS;
	
}
