#pragma once

#include <ShlObj.h>
#include <Windows.h>

#include <iostream>
#include <type_traits>
#include <vector>

std::ostream &operator<<(std::ostream &os, POINT const &pt);
std::ostream &operator<<(std::ostream &os, DROPFILES const &dropfiles);
template <typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> const &v);

inline std::ostream &operator<<(std::ostream &os, POINT const &pt) {
  return os << "{x: " << pt.x << ", y: " << pt.y << "}";
}

inline std::ostream &operator<<(std::ostream &os, DROPFILES const &dropfiles) {
  return os << "{pFiles: " << dropfiles.pFiles << ", pt: " << dropfiles.pt
            << ", fNC: " << dropfiles.fNC << ", fWide: " << dropfiles.fWide
            << "}";
}

template <typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> const &v) {
  os << "[";

  bool tail = false;
  for (auto const &item : v) {
    if (tail) {
      os << ", ";
    }
    os << item;
    tail = true;
  }

  return os << "]";
}
