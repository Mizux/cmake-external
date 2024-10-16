#include <iostream>
#include <string>
#include <vector>

#include <absl/log/log.h>
#include <absl/flags/parse.h>
#include <absl/strings/str_join.h>

#include <foo/Foo.hpp>
#include <bar/Bar.hpp>

int main(int argc, char* argv[]) {
  absl::ParseCommandLine(argc, argv);

  {
    const std::vector<std::string> v = {"foo","bar","baz"};
    std::string s = absl::StrJoin(v, "-");
    LOG(INFO) << "Joined string: " << s << "\n";
  }

  foo::Foo::staticFunction(int{0});
  bar::Bar::staticFunction(int{1});
  std::cout << std::endl;

  return 0;
}
