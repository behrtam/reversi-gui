// Copyright 2015 Tammo Behrends

#ifndef REVERSI_UTILS_H
#define REVERSI_UTILS_H


#include <algorithm>
#include <type_traits>


template<typename Enum>
auto as_integer(Enum const value) {
    return static_cast<typename std::underlying_type<Enum>::type>(value);
}

// template<class C, class T>
// inline bool contains(const C& v, const T& x) {
//     return std::end(v) != std::find(std::begin(v), std::end(v), x);
// }

#endif  // REVERSI_UTILS_H
