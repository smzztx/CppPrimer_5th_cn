#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    unsigned aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0, tabCnt = 0, newlineCnt = 0, ffCnt = 0, flCnt = 0, fiCnt = 0;
    char ch, prech = '\0';
    while (cin >> std::noskipws >> ch)
    {
        switch (ch) {
            case 'a':
            case 'A':
                ++aCnt;
                break;
            case 'e':
            case 'E':
                ++eCnt;
                break;
            case 'i':
                if(prech == 'f') ++fiCnt;
            case 'I':
                ++iCnt;
                break;
            case 'o':
            case 'O':
                ++oCnt;
                break;
            case 'u':
            case 'U':
                ++uCnt;
                break;
            case '\n':
                ++newlineCnt;
                break;
            case '\t':
            case '\v':
                ++tabCnt;
                break;
            case 'f':
                if(prech == 'f') ++ffCnt;
                break;
            case 'l':
                if(prech == 'f') ++flCnt;
                break;
        }
        prech = ch;
    }
    cout << "Number of vowel a(A): \t" << aCnt << '\n'
         << "Number of vowel e(E): \t" << eCnt << '\n'
         << "Number of vowel i(I): \t" << iCnt << '\n'
         << "Number of vowel o(O): \t" << oCnt << '\n'
         << "Number of vowel u(U): \t" << uCnt << '\n'
         << "Number of newline: \t" << newlineCnt << '\n'
         << "Number of tab: \t" << tabCnt << '\n'
         << "Number of fi: \t" << fiCnt << '\n'
         << "Number of ff: \t" << ffCnt << '\n'
         << "Number of fl: \t" << flCnt << endl;

    return 0;
}