// Funktionen um Windows und Linux Kompatibilität zu ermöglichen

#ifndef CLEARSCREEN_H
#define CLEARSCREEN_H

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

void clear_screen();

//void debug_msg(char text);

#endif

/// Debug Output
    #if defined DEBUG
        #define debug_msg(text); cout << text << endl;
    #else //Assume Release
        #define debug_msg(text);
    #endif


/// Debug Pause um Debug Output lesen zu können
    #if defined DEBUG
        #define debug_pause(); cin.ignore(); cin.get();
    #else //Assume Release
        #define debug_pause();
    #endif


#if defined _WIN32 || defined _WIN64
    #define linuxzusatz 0
#else
    #define linuxzusatz 1
#endif
