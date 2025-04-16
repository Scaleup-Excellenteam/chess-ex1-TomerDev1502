#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Pieces/Piece.h"
#include "PieceFactory.h"
#include "Pieces/King.h"

class Board {
public:
    // Constructs and initializes the board using a flat string (row-major, 64 chars)
    Board(const std::string& initialBoard);

    

    // Validates a move and returns a protocol code (e.g., 42, 13, 31...)
    int validateMove(const std::string& source, const std::string& dest);

    // Executes a validated move
    void doMove(const std::string& source, const std::string& dest);

  

private:
    std::vector<std::vector<std::shared_ptr<Piece>>> m_board;
    bool m_isWhiteTurn;

    int m_whiteKingRow, m_whiteKingCol,
        m_blackKingRow, m_blackKingCol;

    // --- Internal validation helpers ---

    // Converts standard chess notation (e.g., "e2") to coordinates (row, col)
    std::pair<int, int> notationToCoordinates(const std::string& notation) const;

    // Checks if the king of the given color is in check
    bool isKingInCheck(bool isWhiteKing) const;

    bool isKingInCheck(const King& king) const;
    // Gets current turn
    bool getIsWhiteTurn() const;

    int validateBaseRule(int srcRow, int srcCol, int destRow, int destCol) const;

    int validatePieceMovement(int srcRow, int srcCol, int destRow, int destCol) const;

    bool isKingMoving(std::shared_ptr<Piece> piece) const;

    

    void updateKingPos(std::shared_ptr<Piece> piece, const int& destRow, const int& destCol);

    void restoreBoard(std::shared_ptr<Piece> movedPiece, std::shared_ptr<Piece> capturedPiece,
        int srcRow, int srcCol, int destRow, int destCol, bool wasKingMove);
};
