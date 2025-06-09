#include "MoveGenerator.h"
#include <string>

std::vector<ScoredMove>
MoveGenerator::getBestMoves(const Board& board,
    bool whiteToMove,
    size_t maxCount,
    int depth)
{
    // Grab the 8ª8 grid of pieces
    const auto& mat = board.getMatrix();
    // Bounded PQ that keeps only top maxCount moves
    PriorityQueue<ScoredMove, ScoredMoveComparator> pq(maxCount);

    // 1) Gather and score all legal moves
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            auto const& cell = mat[r][c];
            if (!cell || cell->isWhite() != whiteToMove) continue;
            char sym = cell->getSymbol();

            // Try every destination
            for (int tr = 0; tr < 8; ++tr) {
                for (int tc = 0; tc < 8; ++tc) {
                    if (tr == r && tc == c) continue;
                    if (!cell->isValidMove(tr, tc, mat))   continue;
                    if (!cell->isPathClear(tr, tc, mat))   continue;

                    bool capture = (mat[tr][tc] && mat[tr][tc]->isWhite() != whiteToMove);
                    Move mv{ r, c, tr, tc, capture, whiteToMove, sym };

                    // Base heuristic (Depth=0)
                    int baseScore = evaluateMove(mat, mv, whiteToMove);
                    int totalScore = baseScore;

                    // --- 1-ply lookahead: subtract opponent's reply ---
                    if (depth > 0) {
                        Board b1(board);
                        std::string src, dst;
                        src.push_back(char('A' + r));
                        src.push_back(char('1' + c));
                        dst.push_back(char('A' + tr));
                        dst.push_back(char('1' + tc));
                        b1.doMove(src, dst);

                        auto opp = getBestMoves(b1, !whiteToMove, 1, depth - 1);
                        if (!opp.empty())
                            totalScore -= opp[0].score;
                    }

                    // --- 2-ply lookahead: add your next response ---
                    if (depth > 1) {
                        Board b1(board);
                        std::string src1, dst1;
                        src1.push_back(char('A' + r));
                        src1.push_back(char('1' + c));
                        dst1.push_back(char('A' + tr));
                        dst1.push_back(char('1' + tc));
                        b1.doMove(src1, dst1);

                        auto opp = getBestMoves(b1, !whiteToMove, 1, depth - 1);
                        if (!opp.empty()) {
                            auto const& opm = opp[0].move;
                            Board b2(b1);
                            std::string src2, dst2;
                            src2.push_back(char('A' + opm.fromRow));
                            src2.push_back(char('1' + opm.fromCol));
                            dst2.push_back(char('A' + opm.toRow));
                            dst2.push_back(char('1' + opm.toCol));
                            b2.doMove(src2, dst2);

                            auto self = getBestMoves(b2, whiteToMove, 1, depth - 2);
                            if (!self.empty())
                                totalScore += self[0].score;
                        }
                    }

                    pq.push({ mv, totalScore });
                }
            }
        }
    }

    // 2) Extract the top maxCount moves
    std::vector<ScoredMove> best;
    while (!pq.empty() && best.size() < maxCount) {
        best.push_back(pq.poll());
    }
    return best;
}

int MoveGenerator::evaluateMove(
    const std::vector<std::vector<std::shared_ptr<Piece>>>& mat,
    const Move& mv,
    bool whiteToMove) const
{
    int score = 0;

    // a) Capture value
    if (mv.isCapture) {
        auto const& victim = mat[mv.toRow][mv.toCol];
        if (victim)
            score += pieceValue(victim->getSymbol());
    }

    // b) Threat: simulate move on a temp matrix
    auto tempMat = mat;
    tempMat[mv.toRow][mv.toCol] = tempMat[mv.fromRow][mv.fromCol];
    tempMat[mv.fromRow][mv.fromCol] = nullptr;
    if (squareAttacked(tempMat, mv.toRow, mv.toCol, !whiteToMove))
        score += 10;

    // c) Center control bonus
    if (mv.toRow >= 2 && mv.toRow <= 5 &&
        mv.toCol >= 2 && mv.toCol <= 5)
    {
        score += 5;
    }

    return score;
}

bool MoveGenerator::squareAttacked(
    const std::vector<std::vector<std::shared_ptr<Piece>>>& mat,
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
                return true;
        }
    }
    return false;
}

int MoveGenerator::pieceValue(char symbol) const
{
    switch (std::toupper(symbol)) {
    case 'P': return 1;
    case 'N': case 'B': return 3;
    case 'R': return 5;
    case 'Q': return 9;
    default:  return 0;
    }
}
