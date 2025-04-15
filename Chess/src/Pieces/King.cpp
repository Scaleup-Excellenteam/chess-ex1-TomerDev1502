#include "Pieces/King.h"

King::King(bool isWhite, int row, int col) : Piece(isWhite, row, col)
{
	
}
//==================================================================================

bool King::isValidMove(int destRow, int destCol,
	const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const
{
	// Check if the destination is within one square in any direction
	int rowDiff = std::abs(destRow - getRow());
	int colDiff = std::abs(destCol - getCol());

	if ((rowDiff <= 1 && colDiff <= 1) && (rowDiff + colDiff > 0)) {
		return true;
	}
	return false;
}

//==================================================================================			
bool King::isPathClear(int destRow, int destCol,
	const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const
{
	// The King can move to any square, and the check is alredy done in Boared::validatePieceMovement	
	return true;
}
//==================================================================================						
char King::getSymbol() const
{
	return m_isWhite ? 'K' : 'k';
}
//==================================================================================	
bool King::isRegistered = PieceFactory::registerPiece('K', [](bool isWhite, int row, int col) {
	return std::make_shared<King>(isWhite, row, col);
	});