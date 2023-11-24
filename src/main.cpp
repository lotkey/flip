#include "clipboard.hpp"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

void printUsage(std::string const &name);
template <typename Container, typename Predicate>
Container filter(Container const &container, Predicate const &p);

int main(int argc, char const *const *const argv) {
  std::vector<std::string> args(argv, argv + argc);
  auto name = std::filesystem::path(argv[0]).filename().string();

  if (args.size() == 1) {
    printUsage(name);
    std::exit(EXIT_SUCCESS);
  }

  auto help =
      std::find_if(args.begin(), args.end(), [](std::string const &arg) {
        return arg == "--help" || arg == "-h" || arg == "-?" || arg == "/?";
      }) != args.end();
  if (help) {
    printUsage(name);
    std::exit(EXIT_SUCCESS);
  }

  auto verbose =
      std::find_if(args.begin(), args.end(), [](std::string const &arg) {
        return !(arg == "--verbose" || arg == "-v");
      }) != args.end();

  args = filter(args, [](std::string const &arg) -> bool {
    return !(arg == "-v" || arg == "--verbose");
  });
  args.erase(args.begin()); // remove executable name

  bool allFilesExist = true;
  for (auto const &path : args) {
    if (!std::filesystem::exists(path)) {
      std::cout << "File not found: " << path << std::endl;
      allFilesExist = false;
    }
  }
  if (!allFilesExist) {
    std::exit(EXIT_FAILURE);
  }

  // convert strings to paths
  std::vector<std::filesystem::path> paths;
  std::transform(
      args.begin(), args.end(), std::back_inserter(paths),
      [](std::string const &arg) -> std::filesystem::path { return arg; });

  copyFilesToClipboard(paths, verbose);
}

template <typename Container, typename Predicate>
Container filter(Container const &container, Predicate const &p) {
  Container filtered;
  std::copy_if(std::begin(container), std::end(container),
               std::back_inserter(filtered), p);
  return filtered;
}

void printUsage(std::string const &name) {
  std::cout << "USAGE: " << name << " [OPTION]... FILE..." << std::endl;
  std::cout << "A Windows command-line tool to copy files to the clipboard."
            << std::endl;
  std::cout << std::endl;
  std::cout << "OPTIONS:" << std::endl;
  std::cout << "    -h, --help      Print the usage and exit" << std::endl;
  std::cout << "    -v, --verbose   Print verbose logs" << std::endl;
}