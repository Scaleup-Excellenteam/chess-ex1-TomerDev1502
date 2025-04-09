#pragma once

#include <string>
#include <vector>
#include <memory>

class Board; // Forward declaration

class Piece {
public:
    Piece(bool isWhite, int row, int col)
        : m_isWhite(isWhite), m_row(row), m_col(col) {}
    virtual ~Piece() = default;

    virtual bool isValidMove(int destRow, int destCol,
        const std::vector<std::vector<std::shared_ptr<Piece>>>& Board) const = 0;
    virtual bool isPathClear(int destRow, int destCol,
        const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const = 0;
    virtual char getSymbol() const = 0;

    bool isWhite() const { return m_isWhite; }

    int getRow() const { return m_row; };
    int getCol() const { return m_col; };

    void setPosition(int row, int col) { m_row = row; m_col = col; }

protected:
    bool m_isWhite;

private:
    int m_row;
    int m_col;
};
