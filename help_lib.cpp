/**
 * help_lib.cpp ---- help functions error handling and exceptions!
 *
 * Copyright (c) 2015 Stelmach Ro 
 * 
 * Author: Stelmach Ro (xtasy) <stelmach.ro@gmail.com>
 *
 * This file is part of Assy Comm.
 * 
 */

#include <iostream>
#include "help_lib.h"

using namespace std;

void getHelp::show_help_msg() 
{
    cout << "\t post" << "\t\t - start a post seccion [comments allowed] " << endl;
    cout << "\t post-lc" << "\t\t - start a post seccion [comments now allowed] " << endl;
    cout << "\t exit" << "\t\t - exit applicaton" << endl; 
    cout << "\t about" << "\t\t - shows information about the applicaton" << endl;
}
