#include <iostream>
#include <vector>
#include "include/myserver.h"

using namespace std;

//main program

void examplefunction()
{
  cout << "hello world" << endl;
}
int ex(int i)
{
  return i*i;
}
int main()
{
  myserver  * server=new myserver(8080,4);
  server->callF(&examplefunction);
  server->callF2(&ex,5);
  server->setF(&examplefunction);
  server->runServer();
  cout << "server terminaded" << endl;
  return 0;
}
