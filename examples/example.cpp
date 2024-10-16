#include <iostream>

#include <foo/Foo.hpp>
#include <bar/Bar.hpp>

int main(int /*argc*/, char** /*argv*/) {
  foo::freeFunction(0);
  bar::freeFunction(1);
  std::cout << std::endl;

  foo::Foo::staticFunction(int{0});
  bar::Bar::staticFunction(int{1});
  std::cout << std::endl;

  return 0;
}
