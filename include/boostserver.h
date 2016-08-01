#ifndef boosts_h
#define boosts_h

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/asio/socket_base.hpp>
using boost::asio::ip::tcp;

class tcp_connection  : public boost::enable_shared_from_this<tcp_connection>
{
public:
  typedef boost::shared_ptr<tcp_connection> pointer;

  inline static pointer create(boost::asio::io_service& io_service)
  {
    return pointer(new tcp_connection(io_service));
  }

  tcp::socket& socket();

  void start();
private:
  tcp_connection(boost::asio::io_service& io_service);

  void handle_write(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/);

  void handle_read(boost::shared_ptr<boost::array<char, 128>> buf, const boost::system::error_code& error);
  tcp::socket socket_;
  std::string message_;
};

class tcp_server
{
public:
  tcp_server(boost::asio::io_service& io_service);

private:
  void start_accept();

  void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error);

  tcp::acceptor acceptor_;
};

#endif
