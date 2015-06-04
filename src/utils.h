// Copyright 2015 Tammo Behrends

#ifndef REVERSI_UTILS_H
#define REVERSI_UTILS_H


#include <type_traits>

template <typename Enum>
auto as_integer(Enum const value) {
    return static_cast<typename std::underlying_type<Enum>::type>(value);
}


#endif  // REVERSI_UTILS_H
