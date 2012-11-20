#include <cstdlib>
#include <iostream>

#define LINUX

void clear_screen() {
#ifdef WINDOWS
    std::system ( "CLS" );
#else
    // Assume POSIX
    std::system ( "clear" );
#endif
}
