#include <iostream>
#include <foo/Foo.hpp>

int main(int argc, char** argv) {
	FLAGS_logtostderr = true;
	gflags::ParseCommandLineFlags(&argc, &argv, true);
	// Initialize Google's logging library.
  google::InitGoogleLogging(argv[0]);

	foo::helloWorld();

	google::ShutdownGoogleLogging();

	return 0;
}
