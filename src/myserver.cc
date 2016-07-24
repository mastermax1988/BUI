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
}

void myserver::runServer()
{
  HttpServer server(port, nrofthreads);
  
  server.resource["^/info$"]["GET"]=[](HttpServer::Response& response, shared_ptr<HttpServer::Request> request) {
        mys::funcwrapper();
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

  
  server.default_resource["GET"]=[](HttpServer::Response& response, shared_ptr<HttpServer::Request> request) {
        boost::filesystem::path web_root_path("web");
        if(!boost::filesystem::exists(web_root_path))
            cerr << "Could not find web root." << endl;
        else {
            auto path=web_root_path;
            path+=request->path;
            if(boost::filesystem::exists(path)) {
                if(boost::filesystem::canonical(web_root_path)<=boost::filesystem::canonical(path)) {
                    if(boost::filesystem::is_directory(path))
                        path+="/index.html";
                    if(boost::filesystem::exists(path) && boost::filesystem::is_regular_file(path)) {
                        ifstream ifs;
                        ifs.open(path.string(), ifstream::in | ios::binary);
                        
                        if(ifs) {
                            ifs.seekg(0, ios::end);
                            size_t length=ifs.tellg();
                            
                            ifs.seekg(0, ios::beg);
                            
                            response << "HTTP/1.1 200 OK\r\nContent-Length: " << length << "\r\n\r\n";
                            
                            //read and send 128 KB at a time
                            size_t buffer_size=131072;
                            vector<char> buffer;
                            buffer.reserve(buffer_size);
                            size_t read_length;
                            try {
                                while((read_length=ifs.read(&buffer[0], buffer_size).gcount())>0) {
                                    response.write(&buffer[0], read_length);
                                    response.flush();
                                }
                            }
                            catch(const exception &e) {
                                cerr << "Connection interrupted, closing file" << endl;
                            }

                            ifs.close();
                            return;
                        }
                    }
                }
            }
        }
        string content="Could not open path "+request->path;
        response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
    };

  
  thread server_thread([&server](){
        //Start server
        server.start();
    });
    
    //Wait for server to start so that the client can connect
    this_thread::sleep_for(chrono::seconds(1));
server_thread.join();

}

void myserver::setF(voidf f)
{
  mys::func = f;
}
void myserver::callF(voidf  f)
{
  f();
}

void myserver::callF2(intf1 f, int i)
{
  cout << f(i) << endl;
}

myserver::~myserver()
{
}
