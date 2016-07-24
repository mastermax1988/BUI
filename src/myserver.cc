#include "../include/myserver.h"
#include <iostream>
#include "../include/mys.hh"
//Added for the default_resource example
#include <fstream>
#include <boost/filesystem.hpp>

using namespace std;

myserver::myserver(int p, int t)
{
  port=p;
  nrofthreads=t;
  mys::content="";
}

void myserver::addContent(string s)
{
  mys::content+=s;
}
void myserver::mapFunction(string s, voidf f)
{
  mys::dictv.push_back({s,f});
}
void myserver::runServer()
{
  HttpServer server(port, nrofthreads);
  server.resource["^/info$"]["GET"]=[](HttpServer::Response& response, shared_ptr<HttpServer::Request> request) {
        stringstream content_stream;
        content_stream << "<h1>Request from " << request->remote_endpoint_address << " (" << request->remote_endpoint_port << ")</h1>";
        content_stream << request->method << " " << request->path << " HTTP/" << request->http_version << "<br>";
        for(auto& header: request->header) {
            content_stream << header.first << ": " << header.second << "<br>";
        }
        
        //find length of content_stream (length received using content_stream.tellp())
        content_stream.seekp(0, ios::end);
        
        response <<  "HTTP/1.1 200 OK\r\nContent-Length: " << content_stream.tellp() << "\r\n\r\n" << content_stream.rdbuf();
    };

  server.resource["^/str$"]["POST"]=[](HttpServer::Response& response, shared_ptr<HttpServer::Request> request) {
      //Retrieve string:
        auto content=request->content.string();
        content=content.substr(2,content.length()-2);
        mys::funcwrapper(content); 
        content= "<html>\r\n<script>\r\nwindow.history.back();\r\n</script>\r\n</html>";
        response << "HTTP/1.1 200 OK\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
    };

  server.default_resource["GET"]=[](HttpServer::Response& response, shared_ptr<HttpServer::Request> request) {
    response << "HTTP/1.1 200 OK\r\nContent-Length: " << mys::content.length() << "\r\n\r\n" << mys::content;
        return;
    };

  
  thread server_thread([&server](){
        //Start server
        server.start();
    });
    
    //Wait for server to start so that the client can connect
    this_thread::sleep_for(chrono::seconds(1));
server_thread.join();

}



myserver::~myserver()
{
}
