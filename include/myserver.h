#ifndef myserver_h
#define myserver_h
#include "../server/server_http.hpp"
#include "../server/client_http.hpp"
#include <string>
using namespace std;


class myserver
{
  public:
    myserver(int, int);
    ~myserver();
    typedef void (*voidf)(string);
    void addContent(string);
    void mapFunction(string, voidf);
    void runServer();
  private:
    typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
    typedef SimpleWeb::Client<SimpleWeb::HTTP> HttpClient;
    int port, nrofthreads;
};

#endif
