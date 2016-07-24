#include "../include/htmlgenerator.h"
#include <iostream>
namespace htmlgenerator
{
  form _form;
}
void htmlgenerator::newForm(string m)
{
  _form.method=m;
  _form.formContent=vector<string>(0);
}

void htmlgenerator::addInput(string v)
{
  string s="<input name=\"c\" value=\"" + v + "\" type=\"submit\">";
  _form.formContent.push_back(s);
}

string htmlgenerator::getForm()
{
  string s="<form method=\"" + _form.method + "\" action=\"/str\">";
  for(const auto& c:_form.formContent)
    s+=c;
  s+="</form>";
  return s;
}
