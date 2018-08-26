#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    unsigned aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0, tabCnt = 0, newlineCnt = 0, ffCnt = 0, flCnt = 0, fiCnt = 0;
    char ch, prech;
    constexpr unsigned ival=512, jval=1024, kval=4096;

    unsigned bufsize;

    unsigned swt = 512;

    switch(swt) {

    case ival:

    bufsize = ival * sizeof(int);

    break;

    case jval:

    bufsize = jval * sizeof(int);

    break;

    case kval:

    bufsize = kval * sizeof(int);
        break;

    }

    return 0;
}