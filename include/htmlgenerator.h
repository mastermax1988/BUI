#ifndef htmlgen
#define htmlgen 

#include <string>
#include <vector>

using namespace std;
namespace htmlgenerator
{
 struct form
 {
   string method;
   vector<string> formContent;
  };
  void newForm(string);//method
  void addInput(string); //value
  string getForm();
  extern form _form;
};

#endif
