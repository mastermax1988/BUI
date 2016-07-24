#include <iostream>
#include <vector>
#include "include/myserver.h"
#include "include/htmlgenerator.h"
#include <string>

using namespace std;
typedef void (*voidf)(string);

//main program

void examplefunction(string s)
{ 
  cout << s << endl;
}
void newForm(string s)
{
  htmlgenerator::newForm(s);
}
void addFormToServer(myserver * server)
{
  server->addContent(htmlgenerator::getForm());
}
void addFormInput(myserver * server, string s, voidf f)
{
  htmlgenerator::addInput(s);
  server->mapFunction(s,f);
}

int main()
{
  myserver  * server=new myserver(8080,4);
  newForm("POST");
  addFormInput(server,"test",&examplefunction);
  addFormInput(server,"test2",&examplefunction); 
  addFormToServer(server);
  newForm("POST");
  addFormInput(server,"test3",&examplefunction);
  addFormInput(server,"test4",&examplefunction); 
  addFormToServer(server);
  server->runServer();
  return 0;
}
