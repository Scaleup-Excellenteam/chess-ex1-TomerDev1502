#pragma once

#include <vector>
#include <memory>
#include "Board.h"
#include "PriorityQueue.h"
#include "ScoredMove.h"

class MoveGenerator {
public:
    /// Return up to maxCount best moves for the side to move (whiteToMove).
    /// depth = number of plies to look ahead (0 = only immediate heuristic).
    std::vector<ScoredMove>
        getBestMoves(const Board& board,
            bool whiteToMove,
            size_t maxCount = 5,
            int depth = 0);

private:
    /// Heuristic for a single move (capture, threat, center control).
    int evaluateMove(
        const std::vector<std::vector<std::shared_ptr<Piece>>>& mat,
        const Move& mv,
        bool whiteToMove) const;

    /// True if (row,col) is attacked by any piece of the given color.
    bool squareAttacked(
        const std::vector<std::vector<std::shared_ptr<Piece>>>& mat,
        int row,
        int col,
        bool byWhite) const;

    /// Basic material values for captures.
    int pieceValue(char symbol) const;
};
