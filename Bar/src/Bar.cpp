#include <bar/Bar.hpp>

#include <iostream>

namespace bar {
  void world() {
		LOG(INFO) << "bar::world()";
  }

void Bar::operator()() const {
	LOG(INFO) << "bar::Bar()()";
}
}

