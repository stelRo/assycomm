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


int main(int argc, char const *argv[])
{	
    
        vector<string> args(argv, argv+argc);
	string login_name;
	string login_pass;

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


  	for (size_t i = 1; i < args.size(); ++i) {

            if (args[i] == "-p") /*shows the queries */
                sql_info.print_post_info();
            else {
                cout << "Argument: " << argv[i] << " was not found!" << endl;
                exit(1);
            }
        }

        //cout << "ID: " << stcl.sqlGetId() << endl;
	
	return EXIT_SUCCESS;
	
}
