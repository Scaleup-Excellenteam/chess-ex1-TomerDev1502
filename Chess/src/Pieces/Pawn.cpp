#include "Pieces/Pawn.h"
#include "PieceFactory.h"

Pawn::Pawn(bool isWhite, int row, int col)
    : Piece(isWhite, row, col) {}

char Pawn::getSymbol() const {
    return isWhite() ? 'P' : 'p';
}

bool Pawn::isValidMove(int destRow, int destCol,
    const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const
{
    int direction = isWhite() ? 1 : -1;
    int startRow = isWhite() ? 1 : 6;

    int rowDiff = destRow - getRow();
    int colDiff = std::abs(destCol - getCol());

    std::shared_ptr<Piece> target = board[destRow][destCol];

    // Move forward 1
    if (colDiff == 0 && rowDiff == direction && !target) {
        return true;
    }

    // Move forward 2 from starting position
    if (colDiff == 0 && rowDiff == 2 * direction && getRow() == startRow && !target) {
        return true;
    }

    // Diagonal capture
    if (colDiff == 1 && rowDiff == direction && target && target->isWhite() != isWhite()) {
        return true;
    }

    return false;
}

bool Pawn::isPathClear(int destRow, int destCol,
    const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const
{
    int direction = isWhite() ? 1 : -1;

    if (destCol == getCol()) {
        // Moving 2 squares forward? Must check both
        if (std::abs(destRow - getRow()) == 2) {
            int midRow = getRow() + direction;
            if (board[midRow][getCol()] != nullptr || board[destRow][getCol()] != nullptr)
                return false;
        }
        // Moving 1 square forward? Just check dest
        else if (board[destRow][getCol()] != nullptr) {
            return false;
        }
    }

    // Diagonal captures already handled in isValidMove (only allowed if enemy present)
    return true;
}

bool Pawn::isRegistered = PieceFactory::registerPiece('P', [](bool isWhite, int x, int y) {
    return std::make_shared<Pawn>(isWhite, x, y);
    });
