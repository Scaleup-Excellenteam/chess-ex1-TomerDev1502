#include "MoveGenerator.h"
#include <cctype>

std::vector<ScoredMove>
MoveGenerator::getBestMoves(const Board& board,
    bool whiteToMove,
    size_t maxCount)
{
    const auto& mat = board.getMatrix();
    PriorityQueue<ScoredMove, ScoredMoveComparator> pq;

    
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            auto const& cell = mat[r][c];
            if (!cell || cell->isWhite() != whiteToMove) continue;
            char sym = cell->getSymbol();

            for (int tr = 0; tr < 8; ++tr) {
                for (int tc = 0; tc < 8; ++tc) {
                    if (tr == r && tc == c) continue;
                    if (!cell->isValidMove(tr, tc, mat))   continue;
                    if (!cell->isPathClear(tr, tc, mat))   continue;

                    bool capture = (mat[tr][tc] && mat[tr][tc]->isWhite() != whiteToMove);
                    Move mv{ r, c, tr, tc, capture, whiteToMove, sym };
                    int score = evaluateMove(mat, mv, whiteToMove);
                    pq.push({ mv, score });
                }
            }
        }
    }

    
    std::vector<ScoredMove> best;
    while (!pq.empty() && best.size() < maxCount) {
        best.push_back(pq.poll());
    }
    return best;
}

int
MoveGenerator::evaluateMove(const std::vector<std::vector<std::shared_ptr<Piece>>>& mat,
    Move const& mv,
    bool whiteToMove) const
{
    int score = 0;

  
    if (mv.isCapture) {
        auto const& victim = mat[mv.toRow][mv.toCol];
        if (victim) score += pieceValue(victim->getSymbol());
    }

   
    auto temp = mat;
    temp[mv.toRow][mv.toCol] = temp[mv.fromRow][mv.fromCol];
    temp[mv.fromRow][mv.fromCol] = nullptr;
    if (squareAttacked(temp, mv.toRow, mv.toCol, !whiteToMove))
        score += 10;

   
    if (mv.toRow >= 2 && mv.toRow <= 5 &&
        mv.toCol >= 2 && mv.toCol <= 5)
    {
        score += 5;
    }

    return score;
}

bool
MoveGenerator::squareAttacked(const std::vector<std::vector<std::shared_ptr<Piece>>>& mat,
    int row,
    int col,
    bool byWhite) const
{
    
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            auto const& p = mat[r][c];
            if (!p || p->isWhite() != byWhite) continue;
            if (p->isValidMove(row, col, mat) &&
                p->isPathClear(row, col, mat))
            {
                return true;
            }
        }
    }
    return false;
}

int
MoveGenerator::pieceValue(char symbol) const
{
    switch (std::toupper(symbol)) {
    case 'P': return 1;
    case 'N':
    case 'B': return 3;
    case 'R': return 5;
    case 'Q': return 9;
    default:  return 0;
    }
}
