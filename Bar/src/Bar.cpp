#include <bar/Bar.hpp>

#include <iostream>

namespace bar {
  void world() {
    std::cout << "bar::world" << std::endl;
  }

void Bar::operator()() const {
	std::cout << "Bar()" << std::endl;
}
}

