#include "cross-compatibility.h"
using namespace std;

void clear_screen() {
#if defined _WIN32 || defined _WIN64
    std::system ( "CLS" );
#else
    // Assume POSIX
    std::system ( "clear" );
#endif
}
/*
void debug_msg(char text) {
    #if !defined NDEBUG
        cout << text << endl;
    #endif
        cout << "Blaaaa!!!!";
}*/


