#include <foo/Foo.hpp>
#include <gflags/gflags.h>
#include <glog/logging.h>

#include <iostream>

namespace foo {
  void hello() {
    std::cout << "foo::hello" << std::endl;
  }

void Foo::operator()() const {
	std::cout << "Foo()" << std::endl;
}
}

