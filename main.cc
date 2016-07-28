#include <iostream>
#include <vector>
#include <string>
#include "server.h"

using namespace std;
int main()
{
  cout << "new approach" << endl;
  server * myserver=new server(1234);
  myserver->run();
}
