// Funktionen um Windows und Linux Kompatibilität zu ermöglichen

#ifndef CLEARSCREEN_H
#define CLEARSCREEN_H

#include <cstdlib>
#include <iostream>

void clear_screen();

#endif





#if defined _WIN32 || defined _WIN64
    #define linuxzusatz 0
#else
    #define linuxzusatz 1
#endif
