// Copyright 2015 Tammo Behrends

#ifndef REVERSI_SQUARE_H
#define REVERSI_SQUARE_H


// typedef std::pair<int, int> Square;

typedef struct Square {
    int x, y;
} Square;

inline bool operator==(const Square &lhs, const Square &rhs) {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

inline bool operator!=(const Square &lhs, const Square &rhs) {
    return !(lhs == rhs);
}


#endif  // REVERSI_SQUARE_H
