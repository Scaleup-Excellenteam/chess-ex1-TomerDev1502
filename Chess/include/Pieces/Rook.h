#pragma once
#include "Piece.h"
#include "PieceFactory.h"   

class Rook : public Piece {
public:
    Rook(bool isWhite, int row, int col);

    bool isValidMove(int destRow, int destCol,
        const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const override;

    bool isPathClear(int destRow, int destCol,
        const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const override;

    char getSymbol() const override;

private:
	static bool isRegistered;   
};