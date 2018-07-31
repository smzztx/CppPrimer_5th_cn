#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	char c;
	int aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0;

	while(cin >> c)
	{
		if (c == 'a')
            ++aCnt;
        else if (c == 'e')
            ++eCnt;
        else if (c == 'i')
            ++iCnt;
        else if (c == 'o')
            ++oCnt;
        else if (c == 'u')
            ++uCnt;
	}
	cout << "Number of vowel a: \t" << aCnt << '\n' << "Number of vowel e: \t"
         << eCnt << '\n' << "Number of vowel i: \t" << iCnt << '\n'
         << "Number of vowel o: \t" << oCnt << '\n' << "Number of vowel u: \t"
         << uCnt << endl;
	return 0;
}