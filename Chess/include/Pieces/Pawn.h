#pragma once

#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(bool isWhite, int row, int col);
    char getSymbol() const override;

    bool isValidMove(int destRow, int destCol,
        const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const override;

    bool isPathClear(int destRow, int destCol,
        const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const override;

private:
    static bool isRegistered;
};
