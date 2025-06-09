#include "Pieces/Pawn.h"
#include "PieceFactory.h"
#include <iostream>

Pawn::Pawn(bool isWhite, int row, int col)
    : Piece(isWhite, row, col) {}
//==============================================================================
char Pawn::getSymbol() const {
    return isWhite() ? 'P' : 'p';
}
//==============================================================================
bool Pawn::isValidMove(int destRow, int destCol,
    const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const
{

    int direction = isWhite() ? +1 : -1;    // White “down” the array, Black “up”
    int startRow = isWhite() ? 1 : 6;    // row 1 = rank B, row 6 = rank G
    int r = getRow(), c = getCol();

    int rowDiff = destRow - r;
    int colDiff = std::abs(destCol - c);
    auto target = board[destRow][destCol];

    // 1) Single?step straight into empty square
    if (colDiff == 0 && rowDiff == direction && !target) {
        return true;
    }

    // 2) Double?step from start rank: 
    //    both the square in front *and* the landing square must be empty
    if (colDiff == 0 && rowDiff == 2 * direction && r == startRow) {
        int midRow = r + direction;
        if (!board[midRow][c]   // path square clear
            && !target)            // landing square clear
        {
            return true;
        }
    }

    // 3) Diagonal capture by exactly one file, one rank
    if (colDiff == 1 && rowDiff == direction
        && target && target->isWhite() != isWhite())
    {
        return true;
    }

    // (Optional) en passant, promotion, etc. goes here…

    // everything else is illegal
    return false;
}

//==============================================================================
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
//==============================================================================
bool Pawn::isRegistered = PieceFactory::registerPiece('P', [](bool isWhite, int x, int y) {
    return std::make_shared<Pawn>(isWhite, x, y);
    });
