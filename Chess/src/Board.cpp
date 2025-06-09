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

void Board::doMove(int fromRow, int fromCol, int toRow, int toCol) {
    auto piece = m_board[fromRow][fromCol];
    auto captured = m_board[toRow][toCol];

    // relocate in our matrix
    m_board[fromRow][fromCol] = nullptr;
    m_board[toRow][toCol] = piece;

    // tell the piece its new home
    piece->setPosition(toRow, toCol);

    // if it’s a king, update our king?trackers
    if (auto k = std::dynamic_pointer_cast<King>(piece)) {
        if (k->isWhite()) {
            m_whiteKingRow = toRow;
            m_whiteKingCol = toCol;
        }
        else {
            m_blackKingRow = toRow;
            m_blackKingCol = toCol;
        }
    }
}

Board::Board(const Board& other)
    : m_isWhiteTurn(other.m_isWhiteTurn),
    m_whiteKingRow(other.m_whiteKingRow), m_whiteKingCol(other.m_whiteKingCol),
    m_blackKingRow(other.m_blackKingRow), m_blackKingCol(other.m_blackKingCol)
{
    m_board.resize(8, std::vector<std::shared_ptr<Piece>>(8, nullptr));

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            auto const& p = other.m_board[r][c];
            if (p) {
                // Create a brand?new Piece of the same type, at the same coords
                m_board[r][c] = PieceFactory::createPiece(p->getSymbol(), r, c);
            }
        }
    }
}

int Board::validateMove(const std::string& source, const std::string& dest) {
    // Convert chess notation to board coordinates
    auto [srcRow, srcCol] = notationToCoordinates(source);
    auto [destRow, destCol] = notationToCoordinates(dest);

    // Basic rule validation
    int valid = validateBaseRule(srcRow, srcCol, destRow, destCol);
    if (valid != 0)
        return valid;

    valid = validatePieceMovement(srcRow, srcCol, destRow, destCol);
    if (valid != 0)
        return valid;

    // Save piece pointers
    std::shared_ptr<Piece> piece = m_board[srcRow][srcCol];
    std::shared_ptr<Piece> capturedPiece = m_board[destRow][destCol];

    // Save original piece position
    int oldRow = piece->getRow();
    int oldCol = piece->getCol();

    // Temporarily apply move
    m_board[destRow][destCol] = piece;
    m_board[srcRow][srcCol] = nullptr;
    piece->setPosition(destRow, destCol);

    bool selfCheck = false;

    if (piece->getSymbol() == 'k'|| piece->getSymbol() == 'K') {
        // Create a temporary simulated king
        King simulatedKing = *std::dynamic_pointer_cast<King>(piece);
        simulatedKing.setPosition(destRow, destCol);

        selfCheck = isKingInCheck(simulatedKing);
    }
    else {
        selfCheck = isKingInCheck(m_isWhiteTurn);
    }

    // Revert simulated move
    m_board[srcRow][srcCol] = piece;
    m_board[destRow][destCol] = capturedPiece;
    piece->setPosition(oldRow, oldCol);

    if (selfCheck)
        return 31;

    // Check if move causes check
    bool causesCheck = isKingInCheck(!m_isWhiteTurn);
    return causesCheck ? 41 : 42;
}


//==================================================================================

void Board::doMove(const std::string& source, const std::string& dest)
{
    auto [srcRow, srcCol] = notationToCoordinates(source);
    auto [destRow, destCol] = notationToCoordinates(dest);

    std::shared_ptr<Piece> piece = m_board[srcRow][srcCol];
    m_board[destRow][destCol] = piece;
    m_board[srcRow][srcCol] = nullptr;

    piece->setPosition(destRow, destCol);

    // Update king position if the king is moving
    if (std::dynamic_pointer_cast<King>(piece)) {
        if (piece->isWhite()) {
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
// function to check if the original king is in check
bool Board::isKingInCheck(bool isWhiteKing) const
{
	int kingRow = isWhiteKing ? m_whiteKingRow : m_blackKingRow;
	int kingCol = isWhiteKing ? m_whiteKingCol : m_blackKingCol;

	// Check if any opponent piece can attack the king
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			std::shared_ptr<Piece> piece = m_board[row][col];
			if (piece != nullptr && piece->isWhite() != isWhiteKing) {
				if (piece->isValidMove(kingRow, kingCol, m_board) && piece->isPathClear(kingRow,kingCol,m_board)){
					return true; // King is in check
				}
			}
		}
	}

	return false; // King is not in check
                   
}
//==================================================================================
// function to check if the tested new king which created in the function is in check after a possible move
bool Board::isKingInCheck(const King& king) const
{
    int kingRow = king.getRow();
    int kingCol = king.getCol();
    bool isWhiteKing = king.isWhite();

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            std::shared_ptr<Piece> piece = m_board[row][col];
            if (piece != nullptr && piece->isWhite() != isWhiteKing) {
                if (piece->isValidMove(kingRow, kingCol, m_board) &&
                    piece->isPathClear(kingRow, kingCol, m_board)) {
                    return true; // King is in check
                }
            }
        }
    }

    return false;
}

//==================================================================================

bool Board::getIsWhiteTurn() const
{
	return m_isWhiteTurn;
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

void Board::updateKingPos(std::shared_ptr<Piece> piece, const int& destRow, const int& destCol)
{
	// Update the king's position if the moved piece is a king
	if (piece->isWhite()) {
        m_whiteKingRow = destRow;
        m_whiteKingCol = destCol;
    }
    else {
        m_blackKingRow = destRow;
        m_blackKingCol = destCol;
	}

}
            
void Board::restoreBoard(std::shared_ptr<Piece> movedPiece, std::shared_ptr<Piece> capturedPiece, int srcRow, int srcCol, int destRow, int destCol, bool wasKingMove)
{   // Restore the original positions
}
//==================================================================================        
