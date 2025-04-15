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

int Board::validateMove(const std::string& source, const std::string& dest)
{   
    // Convert chess notation to board coordinates
    auto [srcRow, srcCol] = notationToCoordinates(source);
    auto [destRow, destCol] = notationToCoordinates(dest);

    int valid = 0;

    valid = this->validateBaseRule(srcRow, srcCol, destRow, destCol);
    if (valid != 0) {
        return valid;
    }

    valid = this->validatePieceMovement(srcRow, srcCol, destRow, destCol);
    if (valid != 0) {
        return valid;
    }

    std::shared_ptr<Piece> piece = m_board[srcRow][srcCol];
    // Execute the move temporarily
    std::shared_ptr<Piece> capturedPiece = this->m_board[destRow][destCol];
    this->m_board[destRow][destCol] = piece;
    this->m_board[srcRow][srcCol] = nullptr;

    // Update piece position
    int oldRow = piece->getRow();
    int oldCol = piece->getCol();
    piece->setPosition(destRow, destCol);

    // Update king position if the king is moving
    int oldKingRow = -1, oldKingCol = -1;
    bool isKingMoving = this->isKingMoving(piece);
   

    /*
     if (isKingMoving) {
        updateKingPos(piece, oldKingRow, oldKingCol, destRow, destCol);
    }

    bool selfCheck = this->isKingInCheck(m_isWhiteTurn);
    if (selfCheck) {
        restoreBoardPos(piece, capturedPiece, srcRow, srcCol, destRow, destCol, isKingMoving);
        return 31;
    }
    bool causesCheck = isKingInCheck(!m_isWhiteTurn);
    */
    

    // Restore the board and piece position
   // restoreBoardPos(piece, capturedPiece, srcRow, srcCol, destRow, destCol, isKingMoving);
    // Return appropriate code
    // return causesCheck ? 41 : 42;

	return 42; // Valid move
}
//==================================================================================

void Board::doMove(const std::string& source, const std::string& dest)
{
	// Convert chess notation to board coordinates
	auto [srcRow, srcCol] = notationToCoordinates(source);
	auto [destRow, destCol] = notationToCoordinates(dest);

	// Execute the move
	std::shared_ptr<Piece> piece = m_board[srcRow][srcCol];
	m_board[destRow][destCol] = piece;
	m_board[srcRow][srcCol] = nullptr;

	// Update piece position
	piece->setPosition(destRow, destCol);

	// Switch turn
	m_isWhiteTurn = !m_isWhiteTurn;

	
/*
*  auto [srcRow, srcCol] = notationToCoordinates(source);
    auto [destRow, destCol] = notationToCoordinates(dest);

    std::shared_ptr<Piece> piece = m_board[srcRow][srcCol];
    m_board[destRow][destCol] = piece;
    m_board[srcRow][srcCol] = nullptr;

    // Update piece position
    piece->setPosition(destRow, destCol);

    // Update king position if the king is moving
    if (std::dynamic_pointer_cast<King>(piece)) {
        if (piece->getIsWhite()) {
            m_whiteKingRow = destRow;
            m_whiteKingCol = destCol;
        }
        else {
            m_blackKingRow = destRow;
            m_blackKingCol = destCol;
        }
    }

    // Switch turn
    m_isWhiteTurn = !m_isWhiteTurn;
*/
   

}
        

//==================================================================================
std::pair<int, int> Board::notationToCoordinates(const std::string& notation) const
{
	char file = toupper(notation[0]);  // A-H
	char rank = notation[1];           // 1-8

	int row = file - 'A';
	int col = rank - '1';

	return { row, col };
}
//==================================================================================
int Board::validateBaseRule(int srcRow, int srcCol, int destRow, int destCol) const
{
    std::shared_ptr<Piece> piece = m_board[srcRow][srcCol];

    // Check that there is a piece at the source
    if (piece == nullptr) {
        return 11; // No piece at source
    }

    // Check if the piece belongs to the current player
    if (piece->isWhite() != m_isWhiteTurn) {
        return 12; // Piece belongs to opponent
    }

    // Check if destination has a piece of the same color
    if (m_board[destRow][destCol] != nullptr && m_board[destRow][destCol]->isWhite() == m_isWhiteTurn) {
        return 13; // Destination has a piece of the same color
    }

    return 0;
}
//==================================================================================
int Board::validatePieceMovement(int srcRow, int srcCol, int destRow, int destCol) const
{
	std::shared_ptr<Piece> piece = m_board[srcRow][srcCol];

	// Check if the move is valid for the piece
	if (!piece->isValidMove(destRow, destCol, m_board)) {
		return 21; // Invalid move for the piece
	}

	// Check if the path is clear
	if (!piece->isPathClear(destRow, destCol, m_board)) {
		return 21; // Path is not clear
	}

	return 0;//valid
}
//==================================================================================        
bool Board::isKingMoving(std::shared_ptr<Piece> piece) const
{
	return (piece->getSymbol() == 'K' && m_isWhiteTurn) || (piece->getSymbol() == 'k' && !m_isWhiteTurn);
}
//==================================================================================        
