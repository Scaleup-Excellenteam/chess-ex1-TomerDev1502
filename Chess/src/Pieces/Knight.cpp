#include "Pieces/Knight.h"
#include "PieceFactory.h"

Knight::Knight(bool isWhite, int row, int col)
    : Piece(isWhite, row, col) {}

char Knight::getSymbol() const {
    return isWhite() ? 'N' : 'n';
}

bool Knight::isValidMove(int destRow, int destCol,
    const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const
{
    // Can't move to the same square
    if (destRow == getRow() && destCol == getCol())
        return false;

    int rowDiff = std::abs(destRow - getRow());
    int colDiff = std::abs(destCol - getCol());

    // Valid L-shaped knight move
    if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)))
        return false;

    // Can't capture own piece
    auto& dest = board[destRow][destCol];
    if (dest && dest->isWhite() == isWhite())
        return false;

    return true;
}

// Knights jump over pieces, so path is always "clear"
bool Knight::isPathClear(int destRow, int destCol,
    const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const
{
    return true;
}

bool Knight::isRegistered = PieceFactory::registerPiece('N', [](bool isWhite, int x, int y) {
    return std::make_shared<Knight>(isWhite, x, y);
});
