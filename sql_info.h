/*
 * sql_info.h ---- sql queries executed !
 * Copyright (c) 2015 Stelmach Ro
 *
 * Author: Stelmach Ro (xtasy) <stelmach.ro@gmail.com>
 *
 * This file is part of Assy Comm.
 *
 * */

#ifndef _SQL_INFO_H_
#define _SQL_INFO_H_

#include <iostream>
#include <string>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/connection.h>
#include "mysql_connection.h"

using namespace std;
using namespace sql;

class sql_requests {
    
    private:
        Driver *driver;
        Connection *connection;
        Statement *statement;
        ResultSet *result;
        PreparedStatement *pStatement;
        string informations;
        string sql_name;
        string sql_pass;
    public:
        sql_requests(string username, string password);
        long long sql_get_id();
        bool sql_connect();
        void set_post_info();
        void print_post_info();     
        bool sql_query();
};


#endif // _SQL_INFO_H_

