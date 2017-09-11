/************************************************************************/
/* 功能：boost实现串口通信类                                            */
/* 作者: kernelmain QQ:835609451                                        */
/* 版本：v0.1 build at 2014.3.25                                        */
/************************************************************************/
#include "SuperTerminal.h"

SuperTerminal::SuperTerminal(const anytype & port_name):pSerialPort(NULL)
{
    pSerialPort = new serial_port(m_ios);
    if (pSerialPort)
    {
        init_port(port_name,8);
    }
}

SuperTerminal::~SuperTerminal()
{
    if (pSerialPort)
    {
        delete pSerialPort;
    }
}

bool SuperTerminal::init_port(const anytype port, const unsigned int char_size)
{
    if (!pSerialPort)
    {
        return false;
    }

    pSerialPort->open(port,m_ec);

    pSerialPort->set_option(serial_port::baud_rate(115200),m_ec);
    pSerialPort->set_option(serial_port::flow_control(serial_port::flow_control::none),m_ec);
    pSerialPort->set_option(serial_port::parity(serial_port::parity::none),m_ec);
    pSerialPort->set_option(serial_port::stop_bits(serial_port::stop_bits::one),m_ec);
    pSerialPort->set_option(serial_port::character_size(char_size),m_ec);

    return true;
}

void SuperTerminal::write_to_serial(const anytype data)
{
    if (!pSerialPort)
    {
        return;
    }

    size_t len = write(*pSerialPort, buffer(data),m_ec);
    cout << len << "\t" <<  data << endl;
}

void SuperTerminal::handle_read(char buf[], boost::system::error_code ec,std::size_t bytes_transferred)
{
    cout << "\nhandle_read: " ;
    cout.write(buf, bytes_transferred);
}

void SuperTerminal::read_from_serial()
{
    char v[10];
    async_read(*pSerialPort, buffer(v), boost::bind(&SuperTerminal::handle_read,this,v,_1, _2));
}

void SuperTerminal::call_handle()
{
    m_ios.run();
}
