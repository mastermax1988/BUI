#include "server.h"
#include <iostream>
#include <boost/array.hpp>
#include "tcp_connection.hpp"

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
   

  boost::array< char, 128> buf; 
   
    cout << "written" << endl;
read(socket, boost::asio::buffer(buf, 512), ignored_error);
    for(const auto c:buf)
      cout << c;
    cout << endl << "done" << endl;
    
    boost::asio::write(socket, boost::asio::buffer(content), ignored_error);
  }
}


