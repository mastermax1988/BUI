#ifndef server_h
#define server_h
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

class server
{
  public:
    server(int p);
    ~server();
    void run();
  private:
    const int port;
};
#endif
