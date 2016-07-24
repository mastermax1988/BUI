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
    void runServer();
    enum pg {POST, GET};
    typedef void (*voidf)();
    typedef int (*intf1)(int);
    void callF(voidf);
    void callF2(intf1,int);
    void setF(voidf);
    //void addRes(pg,string, function);
  private:
    typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
    typedef SimpleWeb::Client<SimpleWeb::HTTP> HttpClient;
    int port, nrofthreads;
};

#endif
