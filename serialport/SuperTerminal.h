/************************************************************************/
/* 功能：boost实现串口通信类                                            */
/* 作者: kernelmain QQ:835609451                                        */
/* 版本：v0.1 build at 2014.3.25                                        */
/************************************************************************/

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>

using namespace std;
using namespace boost::asio;

typedef string anytype;

class SuperTerminal
{
public:
    SuperTerminal(const anytype &port_name);
    ~SuperTerminal();

private:
    bool init_port(const anytype port, const unsigned int char_size);

public:
    void write_to_serial(const anytype data);
    void read_from_serial();
    void handle_read(char buf[], boost::system::error_code ec,std::size_t bytes_transferred);
    void call_handle();

private:
    io_service m_ios;
    serial_port *pSerialPort;
    anytype m_port;
    boost::system::error_code m_ec;
};
