#ifndef mys
#define mys
#include <string>
#include <vector>
#include <iostream>

namespace mys
{
  typedef void (*voidf)(string);
  struct dict{
    string value;
    voidf func;
  };
  vector<dict> dictv;
  void funcwrapper(string s)
  {
    for(const auto& v:dictv)
      if(v.value==s)
        v.func(s);
  }
  string content;
};

#endif
