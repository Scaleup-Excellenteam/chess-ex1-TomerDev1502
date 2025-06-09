#pragma once

#include <ostream>
#include "ScoredMove.h"

/// Print a single ScoredMove using the internal row/column notation:
/// row letter 'a'..'h' corresponds to row 0..7 (top to bottom)
/// col digit  '1'..'8' corresponds to col 0..7 (left to right)
inline std::ostream& operator<<(std::ostream& os, ScoredMove const& sm) {
    char rowFrom = char('a' + sm.move.fromRow);
    char colFrom = char('1' + sm.move.fromCol);
    char rowTo = char('a' + sm.move.toRow);
    char colTo = char('1' + sm.move.toCol);
    return os << rowFrom << colFrom << rowTo << colTo;
}