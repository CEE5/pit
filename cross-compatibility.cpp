y#include "cross-compatibility.h"
using namespace std;

void clear_screen() {
#if defined _WIN32 || defined _WIN64
    std::system ( "CLS" );
#else
    // Assume POSIX
    std::system ( "clear" );
#endif
}


