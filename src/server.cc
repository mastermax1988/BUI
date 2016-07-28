#include "server.h"
#include <iostream>

using namespace std;
server::server(int p):port(p)
{

}

void server::run()
{
  boost::asio::io_service io_service;
  tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));
  for (;;)
  {
    tcp::socket socket(io_service);
    acceptor.accept(socket);
    
    std::string content = "HTTP/1.1 200 OK\r\n\r\n<html><body><a href=\"https://www.google.de\">tolle Suchmaschine</a></html>";

    boost::system::error_code ignored_error;
    boost::asio::write(socket, boost::asio::buffer(content), ignored_error);
    cout << ignored_error << endl;
  }
}
