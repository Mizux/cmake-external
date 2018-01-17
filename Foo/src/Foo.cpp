#include <foo/Foo.hpp>
#include <gflags/gflags.h>

#include <iostream>

namespace foo {
  void hello() {
		LOG(INFO) << "foo::hello()";
  }

void Foo::operator()() const {
	LOG(INFO) << "foo::Foo()()";
}
}

