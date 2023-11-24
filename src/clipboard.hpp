#pragma once

#include <filesystem>

void copyFilesToClipboard(std::vector<std::filesystem::path> const &paths,
                          bool verbose = false);
