#include "Pieces/Queen.h"
#include "PieceFactory.h"

Queen::Queen(bool isWhite, int row, int col)
    : Piece(isWhite, row, col) {}
//======================================================================
char Queen::getSymbol() const {
    return isWhite() ? 'Q' : 'q';
}
//======================================================================
bool Queen::isValidMove(int destRow, int destCol,
    const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const
{
    if (destRow == getRow() && destCol == getCol())
        return false;

    bool movingDiagonally = std::abs(destRow - getRow()) == std::abs(destCol - getCol());
    bool movingStraight = (destRow == getRow() || destCol == getCol());

    if (!movingDiagonally && !movingStraight)
        return false;

    auto& dest = board[destRow][destCol];
    if (dest && dest->isWhite() == isWhite())
        return false;

    return isPathClear(destRow, destCol, board);
}
//======================================================================
bool Queen::isPathClear(int destRow, int destCol,
    const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const
{
    int r = getRow();
    int c = getCol();

    int rowStep = (destRow > r) ? 1 : (destRow < r ? -1 : 0);
    int colStep = (destCol > c) ? 1 : (destCol < c ? -1 : 0);

    int i = r + rowStep;
    int j = c + colStep;

    while (i != destRow || j != destCol) {
        if (board[i][j]) return false;
        i += rowStep;
        j += colStep;
    }

    return true;
}
//======================================================================
bool Queen::isRegistered = PieceFactory::registerPiece('Q', [](bool isWhite, int x, int y) {
    return std::make_shared<Queen>(isWhite, x, y);
    });
