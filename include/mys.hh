#ifndef mys
#define mys

namespace mys
{
  typedef void (*voidf)();
  voidf func;
  void funcwrapper()
  {
    func();
  }
};

#endif
