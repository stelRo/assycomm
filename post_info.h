/**
 * post_info.h ---- setting and values for sql queryes!
 * Copyright (c) 2015 Stelmach Ro
 *
 * Author: Stelmach Ro (xtasy) <stelmach.ro@gmail.com>
 *
 * This file is part of Assy Comm.
 *
 * */


#ifndef _POST_INFO_H_
#define _POST_INFO_H_

#include <iostream>
#include <string>

using namespace std;

class assycom {
    
    private:
        string post_title;
        string *post_content;
        string post_name;
        bool post_comment_status;

    public:
        assycom();
        ~assycom();
        string return_values(string file_path);
        string return_system_date();
        void read_text();
        void user_define(string title, bool comment_status, string get_post_name);
       
};


#endif // _POST_INFO_H_
