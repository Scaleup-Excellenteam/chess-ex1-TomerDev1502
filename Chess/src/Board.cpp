#include "Board.h"


//builds the tools board matrics
Board::Board(const std::string& initialBoard)
{
    // Initialize an 8x8 board
    m_board.resize(8, std::vector<std::shared_ptr<Piece>>(8, nullptr));
    m_isWhiteTurn = true;

    // Initialize the board using the factory
    int index = 0;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            char symbol = initialBoard[index++]; // moving on the string
            if (symbol != '#') {
                m_board[row][col] = PieceFactory::createPiece(symbol, row, col);

                // Track kings' positions
                if (symbol == 'K') {
                    m_whiteKingRow = row;
                    m_whiteKingCol = col;
                }
                else if (symbol == 'k') {
                    m_blackKingRow = row;
                    m_blackKingCol = col;
                }
            }
        }
    }
}