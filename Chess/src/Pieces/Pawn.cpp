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

    bool return_val = false;
    int r = getRow();
    int c = getCol();
    int direction = isWhite() ? +1 : -1;
    int startRow = isWhite() ? 1 : 6;

    int rowDiff = destRow - r;
    int colDiff = std::abs(destCol - c);
    auto target = board[destRow][destCol];
   

    // 1) Single‐step forward into empty square
    if (colDiff == 0 && rowDiff == direction && !target) {
      //return true
         return_val = true;
    }

  

    // 2) Double‐step from starting rank: both the intermediate and landing squares must be empty
    if (colDiff == 0
        && rowDiff == 2 * direction
        && r == startRow
        && !board[r + direction][c]
        && !target)
    {
        //return true
         return_val = true;
    }

    // 3) Diagonal capture by one file and one rank
    if (colDiff == 1
        && rowDiff == direction
        && target
        && target->isWhite() != isWhite())
    {
        //return true
         return_val = true;
    }

    // All other pawn moves are illegal
    
    /*if (r == 1 && c == 2 && destRow == 5 && destCol == 2) {
        if (return_val)
        {
            std::cout << " true" << "\n";
        }
        else
            std::cout << " false" << "\n";

    }*/

    return return_val;
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
