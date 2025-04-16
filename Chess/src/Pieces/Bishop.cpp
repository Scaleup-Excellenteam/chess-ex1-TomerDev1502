#include "Pieces/Bishop.h"


Bishop::Bishop(bool isWhite, int row, int col)
    : Piece(isWhite, row, col) {}
    
//==================================================================================
char Bishop::getSymbol() const {
    return isWhite() ? 'B' : 'b';
}
//==================================================================================
bool Bishop::isValidMove(int destRow, int destCol,
    const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const
{
    // Can't move to current position
    if (destRow == getRow() && destCol == getCol())
        return false;

    // Bishop moves diagonally → abs(row difference) == abs(col difference)
    if (std::abs(destRow - getRow()) != std::abs(destCol - getCol()))
        return false;

    // Destination has piece of same color
    auto& dest = board[destRow][destCol];
    if (dest && dest->isWhite() == isWhite())
        return false;

    // Make sure path is clear
    return isPathClear(destRow, destCol, board);
}
//==================================================================================
bool Bishop::isPathClear(int destRow, int destCol,
    const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const
{
    int r = getRow();
    int c = getCol();

    int rowStep = (destRow > r) ? 1 : -1;
    int colStep = (destCol > c) ? 1 : -1;

    int i = r + rowStep;
    int j = c + colStep;

    while (i != destRow && j != destCol) {
        if (board[i][j]) return false;
        i += rowStep;
        j += colStep;
    }

    return true;
}
//==================================================================================
// Register the piece in the factory with symbol 'B'
bool Bishop::isRegistered = PieceFactory::registerPiece('B', [](bool isWhite, int x, int y) {
    return std::make_shared<Bishop>(isWhite, x, y);
    });
