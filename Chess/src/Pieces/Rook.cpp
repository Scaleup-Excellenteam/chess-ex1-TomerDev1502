#include "Pieces/Rook.h"
#include "PieceFactory.h"

Rook::Rook(bool isWhite, int row, int col)
    : Piece(isWhite, row, col) {}

char Rook::getSymbol() const {
    return isWhite() ? 'R' : 'r';
}

bool Rook::isValidMove(int destRow, int destCol,
    const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const
{
    // Can't move to current position
    if (destRow == getRow() && destCol == getCol())
        return false;

    // Rook moves only in straight lines (row or column must match)
    if (destRow != getRow() && destCol != getCol())
        return false;

    // Destination has piece of same color
    auto& dest = board[destRow][destCol];
    if (dest && dest->isWhite() == isWhite())
        return false;

    // Make sure path is clear
    return isPathClear(destRow, destCol, board);
}

bool Rook::isPathClear(int destRow, int destCol,
    const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const
{
    int r = getRow();
    int c = getCol();

    // Moving vertically
    if (destCol == c) {
        int step = (destRow > r) ? 1 : -1;
        for (int i = r + step; i != destRow; i += step) {
            if (board[i][c]) return false;
        }
    }
    // Moving horizontally
    else if (destRow == r) {
        int step = (destCol > c) ? 1 : -1;
        for (int i = c + step; i != destCol; i += step) {
            if (board[r][i]) return false;
        }
    }
    else {
        // Not a valid rook move (this should be unreachable if isValidMove checks correctly)
        return false;
    }

    return true;
}
bool Rook::isRegistered = PieceFactory::registerPiece('R', [](bool isWhite, int x, int y) {
    return std::make_shared<Rook>(isWhite, x, y);
    });