//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "boostserver.h"
#include <boost/array.hpp>
#include <iostream>
using namespace std;
using boost::asio::ip::tcp;



tcp::socket& tcp_connection::socket()
{
  return socket_;
}

void tcp_connection::start()
{
  string con = "<html><body><a href=\"https://www.google.de\">tolle Suchmaschine</a></html>";
  int conl=con.length();
  message_ = "HTTP/1.1 200 OK\r\nContent-Length: " + to_string(conl) + "\r\n\r\n" + con;

  boost::asio::async_write(socket_, boost::asio::buffer(message_), boost::bind(&tcp_connection::handle_write, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

  boost::shared_ptr<boost::array<char, 128>> buf(new boost::array<char, 128>); 
  boost::asio::async_read(socket_, boost::asio::buffer(*buf),boost::bind(&tcp_connection::handle_read, shared_from_this(), buf, boost::asio::placeholders::error));

}


void tcp_connection::handle_read(boost::shared_ptr<boost::array<char, 128> >buf, boost::system::error_code const&)
{
  cout << buf->data() << endl;
}

tcp_connection::tcp_connection(boost::asio::io_service& io_service)  : socket_(io_service)
{

}

void tcp_connection::handle_write(const boost::system::error_code& e/*error*/, size_t i/*bytes_transferred*/)
{
}


tcp_server::tcp_server(boost::asio::io_service& io_service) : acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234))
{
  start_accept();
}

void tcp_server::start_accept()
{
  tcp_connection::pointer new_connection =
    tcp_connection::create(acceptor_.get_io_service());

  acceptor_.async_accept(new_connection->socket(),
      boost::bind(&tcp_server::handle_accept, this, new_connection,
        boost::asio::placeholders::error));
}

void tcp_server::handle_accept(tcp_connection::pointer new_connection,const boost::system::error_code& error)
{
  if (!error)
  {
    new_connection->start();
    start_accept();
  }
}


