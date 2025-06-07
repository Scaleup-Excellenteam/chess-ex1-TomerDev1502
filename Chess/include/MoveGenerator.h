#pragma once

#include <vector>
#include "Board.h"
#include "PriorityQueue.h"
#include "ScoredMove.h"

class MoveGenerator {
public:
    /// מחזיר עד maxCount מהמהלכים המומלצים (הכי גבוהים) עבור הצעד הנוכחי (whiteToMove)
    std::vector<ScoredMove>
        getBestMoves(const Board& board,
            bool whiteToMove,
            size_t maxCount = 5);

private:
    /// מחשב ציון עבור מהלך בודד (Depth=0)
    int evaluateMove(const std::vector<std::vector<std::shared_ptr<Piece>>>& mat,
        Move const& mv,
        bool whiteToMove) const;

    /// בודק האם הריבוע (row,col) מאוים ע"י הצבע שמצוין
    bool squareAttacked(const std::vector<std::vector<std::shared_ptr<Piece>>>& mat,
        int row,
        int col,
        bool byWhite) const;

    /// ערכי כלי בסיסיים
    int pieceValue(char symbol) const;
};
