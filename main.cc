#include <iostream>
#include <vector>
#include <string>
//#include "server.h"
#include <boost/asio.hpp>
#include "boostserver.h"

using namespace std;
int main()
{
  try
  {
    boost::asio::io_service io_service;
    tcp_server server(io_service);
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}
