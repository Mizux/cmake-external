#pragma once

#include <glog/logging.h>

namespace foo {
  void helloWorld();

	class Foo {
		public:
			void operator()() const;
	};
}

