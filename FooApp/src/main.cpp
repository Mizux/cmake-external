#include <iostream>
#include <cstdint>
#include <fstream>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <zlib.h>

#include "foo.pb.h"

void AddFoo(foo::Foo* fooPtr, const std::string& key, std::int32_t value);

int main(int argc, char** argv) {
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	// Write a Message
	{
		foo::FooList fooList;
		AddFoo(fooList.add_foos(), "bar", 3);
		AddFoo(fooList.add_foos(), "baz", 5);
		AddFoo(fooList.add_foos(), "bop", 7);
		// Write the new address book back to disk.
		std::fstream out("foo.txt", std::ios::out | std::ios::trunc | std::ios::binary);
		if (!fooList.SerializeToOstream(&out)) {
			std::cerr << "Failed to write /tmp/foo.txt." << std::endl;
			return -1;
		}
	}

	// Read a Message
	{
		foo::FooList fooList;
		std::fstream in("foo.txt", std::ios::in | std::ios::binary);
		if (!fooList.ParseFromIstream(&in) || fooList.foos_size() != 3) {
			std::cerr << "Failed to read /tmp/foo.txt." << std::endl;
			return -2;
		}

		for (std::size_t i=0; i < 3; ++i) {
			std::cout << "hello " << fooList.foos(i).key()
				<< ":" << fooList.foos(i).value() << std::endl;
		}
	}

	// Optional:  Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}

void AddFoo(foo::Foo* fooPtr, const std::string& key, std::int32_t value) {
	fooPtr->set_key(key.c_str());
	fooPtr->set_value(value);
}
