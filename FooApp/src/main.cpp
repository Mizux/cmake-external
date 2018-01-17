#include <iostream>
#include <cstdint>
#include <fstream>
#include <gflags/gflags.h>
#include <glog/logging.h>

int main(int argc, char** argv) {
	FLAGS_logtostderr = true;
	gflags::ParseCommandLineFlags(&argc, &argv, true);
	// Initialize Google's logging library.
  google::InitGoogleLogging(argv[0]);

	LOG(INFO) << "Hello World !";

	google::ShutdownGoogleLogging();

	return 0;
}
