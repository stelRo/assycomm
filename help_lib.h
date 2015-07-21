/**
 * help_lib.h ---- help functions error handling and exceptions!
 *
 * Copyright (c) 2015 Stelmach Ro 
 * 
 * Author: Stelmach Ro (xtasy) <stelmach.ro@gmail.com>
 *
 * This file is part of Assy Comm.
 * 
 */

#ifndef _GET_HELP_H_
#define _GET_HELP_H_

/* Terminal colors */

namespace Color {
    enum Code {
        FG_BOLD     = 1,
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_YELLOW    = 33,
        FG_BLUE     = 34,
        FG_CYAN     = 36,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };

class Modifier {
private:
    Code code;
public:
    Modifier(Code pCode) : code(pCode) {}
    friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

class getHelp {
    public:
       void show_help_msg();
};




#endif //_GET_HELP_H_
