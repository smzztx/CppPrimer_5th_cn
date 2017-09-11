#include <vector>
#include <string>

#define BOOST_REGEX_NO_LIB
#define BOOST_DATE_TIME_SOURCE
#define BOOST_SYSTEM_NO_LIB
#include "SuperTerminal.h"

int main()
{
    try
    {
        SuperTerminal sp("COM1");
        sp.write_to_serial("serialPort");
        sp.read_from_serial();
        sp.call_handle();
        getchar();
        return 0;
    }
    catch (std::exception &e)
    {
        cout << e.what();
        getchar();
    }
}
