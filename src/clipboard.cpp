#include "clipboard.hpp"
#include "print.hpp"

#include <numeric>

void copyFilesToClipboard(std::vector<std::filesystem::path> const &paths,
                          bool verbose) {
  std::vector<std::string> pathsStr;

  std::transform(paths.begin(), paths.end(), std::back_inserter(pathsStr),
                 [&](std::filesystem::path const &path) -> std::string {
                   return std::filesystem::absolute(path).string();
                 });
  if (verbose) {
    std::cout << "Copying files: " << pathsStr << std::endl;
  }

  auto filenameList =
      std::accumulate(pathsStr.begin(), pathsStr.end(), std::vector<char>(),
                      [](std::vector<char> &sum, std::string const &path) {
                        sum.insert(sum.end(), path.begin(), path.end());
                        sum.push_back('\0');
                        return sum;
                      });
  filenameList.push_back('\0');
  if (verbose) {
    std::cout << "Filename list: " << filenameList << std::endl;
  }

  auto listSizeBytes = sizeof(char) * filenameList.size();

  HDROP hdrop =
      static_cast<HDROP>(GlobalAlloc(GHND, listSizeBytes + sizeof(DROPFILES)));
  DROPFILES *dropfiles = static_cast<DROPFILES *>(GlobalLock(hdrop));
  dropfiles->pFiles = sizeof(DROPFILES);
  dropfiles->fWide = false;

  char *listStart = reinterpret_cast<char *>(&dropfiles[1]);
  memcpy(listStart, filenameList.data(), listSizeBytes);
  GlobalUnlock(hdrop);
  if (verbose) {
    std::cout << "dropfiles: " << (*dropfiles) << std::endl;
  }

  auto globalHandle = GetDesktopWindow();
  if (globalHandle == nullptr) {
    std::cout << "failed to get current window" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  if (!OpenClipboard(globalHandle)) {
    std::cout << "failed to open clipboard" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  if (!EmptyClipboard()) {
    std::cout << "failed to empty clipboard" << std::endl;
    CloseClipboard();
    std::exit(EXIT_FAILURE);
  }

  SetClipboardData(CF_HDROP, hdrop);

  if (!CloseClipboard()) {
    std::cout << "failed to close clipboard" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}