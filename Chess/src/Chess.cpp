#include "Chess.h"
#include <iostream>
#include <string>
#include "MoveGenerator.h"
#include "MovePrinter.h"


using namespace std;

#ifdef _WIN32

// clear the screen "cls"
void Chess::clear() const 
{
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

// create the GUI - ASCII art
void Chess::setFrames() 
{ 
	for (size_t row = 0; row < _SIZE; ++row)
		for (size_t col = 0; col < _SIZE; ++col)
			m_board[row][col] = 32;

	m_board[0][0] = 201;  m_board[0][20] = 187;
	m_board[20][0] = 200; m_board[20][20] = 188;

	for (size_t i = 1; i < 20; ++i)
	{
		m_board[0][i] = 205;
		m_board[20][i] = 205;
		m_board[i][0] = 186;
		m_board[i][20] = 186;
	} 

	m_board[2][2] = 218;  m_board[2][18] = 191;
	m_board[18][2] = 192; m_board[18][18] = 217;

	for (size_t i = 4; i < 17; i += 2)
	{
		m_board[2][i] = 194;
		m_board[18][i] = 193;
		m_board[i][2] = 195;
		m_board[i][18] = 180;
	}

	for (size_t i = 2; i < 19; i += 2)
		for (size_t j = 3; j < 19; j += 2)
			m_board[i][j] = 196;

	for (size_t i = 3; i < 18; i += 2)
		for (size_t j = 2; j < 19; j += 2)
			m_board[i][j] = 179;

	for (size_t i = 4; i < 17; i += 2)
		for (size_t j = 4; j < 17; j += 2)
			m_board[i][j] = 197;

	for (size_t i = 4; i < 17; i += 2)
		m_board[2][i] = 194;
	for (size_t i = 4; i < 17; i += 2)
		m_board[18][i] = 193;
	for (size_t i = 4; i < 17; i += 2)
		m_board[i][2] = 195;
	for (size_t i = 4; i < 17; i += 2)
		m_board[i][18] = 180;

	for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
		m_board[1][i] = m_board[19][i] = ('1' + t);

	for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
		m_board[i][1] = m_board[i][19] = ('A' + t);
}

void Chess::setPieces()
{
	for (size_t row = 0, t = 0; row < 8; ++row)
		for (size_t col = 0; col < 8; ++col, ++t)
			m_board[(3 + (row * 2))][(3 + (col * 2))] = ((m_boardString[t] == '#') ? 32 : m_boardString[t]);
}

#else // non-Windows

void Chess::clear() const
{
	cout << "\033[2J\033[3J\033[H";
}

void Chess::setFrames()
{
	for (size_t row = 0; row < _SIZE; ++row)
		for (size_t col = 0; col < _SIZE; ++col)
			m_board[row][col] = ' ';

	m_board[0][0] = '+';
	m_board[0][20] = '+';
	m_board[20][0] = '+';
	m_board[20][20] = '+';

	for (size_t i = 1; i < 20; ++i)
	{
		m_board[0][i] = '-';
		m_board[20][i] = '-';
		m_board[i][0] = '|';
		m_board[i][20] = '|';
	}

	m_board[2][2] = '+';
	m_board[2][18] = '+';
	m_board[18][2] = '+';
	m_board[18][18] = '+';

	for (size_t i = 4; i < 17; i += 2)
	{
		m_board[2][i] = '+';
		m_board[18][i] = '+';
		m_board[i][2] = '+';
		m_board[i][18] = '+';
	}

	for (size_t i = 2; i < 19; i += 2)
		for (size_t j = 3; j < 19; j += 2)
			m_board[i][j] = '-';

	for (size_t i = 3; i < 18; i += 2)
		for (size_t j = 2; j < 19; j += 2)
			m_board[i][j] = '|';

	for (size_t i = 4; i < 17; i += 2)
		for (size_t j = 4; j < 17; j += 2)
			m_board[i][j] = '+';

	for (size_t i = 4; i < 17; i += 2)
		m_board[2][i] = '+';
	for (size_t i = 4; i < 17; i += 2)
		m_board[18][i] = '+';
	for (size_t i = 4; i < 17; i += 2)
		m_board[i][2] = '+';
	for (size_t i = 4; i < 17; i += 2)
		m_board[i][18] = '+';

	for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
		m_board[1][i] = m_board[19][i] = ('1' + t);

	for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
		m_board[i][1] = m_board[i][19] = ('A' + t);
}

void Chess::setPieces()
{
	for (size_t row = 0, t = 0; row < 8; ++row)
		for (size_t col = 0; col < 8; ++col, ++t)
			m_board[(3 + (row * 2))][(3 + (col * 2))] = ((m_boardString[t] == '#') ? ' ' : m_boardString[t]);
}

#endif // WINDOWS

// print the only the board to screen 
void Chess::show() const 
{
	for (size_t row = 0; row < _SIZE; ++row)
	{
		for (size_t col = 0; col < _SIZE; ++col)
			cout << m_board[row][col];
		cout << endl;
	}
}
// clear screen and print the board and the relevant msg 
void Chess::displayBoard() const
{
	//clear();
	show();
	cout << m_msg<< m_errorMsg;
	
}
// print the who is turn before getting input 
void Chess::showAskInput() const 
{
	if (m_turn)
		cout << "Player 1 (White - Capital letters) >> ";
	else
		cout << "Player 2 (Black - Small letters)   >> ";
}
// check if the source and dest are the same 
bool Chess::isSame() const 
{
	return ((m_input[0] == m_input[2]) && (m_input[1] == m_input[3]));
} 
// check if the input is lockations at board
bool Chess::isValid() const
{
	return ((('A' <= m_input[0]) && (m_input[0] <= 'H')) || (('a' <= m_input[0]) && (m_input[0] <= 'h')) &&
		(('1' <= m_input[1]) && (m_input[1] <= '8')) &&
		(('A' <= m_input[2]) && (m_input[2] <= 'H')) || (('a' <= m_input[2]) && (m_input[2] <= 'h')) &&
		(('1' <= m_input[3]) && (m_input[3] <= '8')));
}
	
// check if the input is exit or quit  
bool Chess::isExit() const 
{
	return ((m_input == "exit") || (m_input == "quit") || (m_input == "EXIT") || (m_input == "QUIT"));
}
// execute the movement on board 
void Chess::excute()
{
	int row = (m_input[0] - 'a');
	int col = (m_input[1] - '1');
	char pieceInSource = m_boardString[(row * 8) + col]; 
	m_boardString[(row * 8) + col] = '#'; 

	row = (m_input[2] - 'a');
	col = (m_input[3] - '1');
	m_boardString[(row * 8) + col] = pieceInSource; 

	setPieces(); 
}
// check the response code and switch turn if needed 
void Chess::doTurn()
{
	m_errorMsg = "\n"; 
	switch (m_codeResponse)
	{
	case 11:
	{
		m_msg = "there is not piece at the source \n";
		break;
	}
	case 12:
	{
		m_msg = "the piece in the source is piece of your opponent \n";
		break;
	}
	case 13:
	{
		m_msg = "there one of your pieces at the destination \n";
		break;
	}
	case 21:
	{
		m_msg = "illegal movement of that piece \n";
		break;
	}
	case 31:
	{
		m_msg = "this movement will cause you checkmate \n";
		break;
	}
	case 41:
	{
		excute();
		m_turn = !m_turn;
		m_msg = "the last movement was legal and cause check \n";
		break;
	}
	case 42:
	{
		excute();
		m_turn = !m_turn;
		m_msg = "the last movement was legal \n";
		break;
	}
	}
}

// C'tor
Chess::Chess(const string& start,const Board &board)
	: m_boardString(start), m_codeResponse(-1), depth(0), m_turn(true), m_boardObject(board)
{
	setFrames();
	setPieces();
}

// get the source and destination 
string Chess::getInput()
{
	static bool isFirst = true;

	if (isFirst) {
		cout << "Enter search depth (0–2): ";
		cin >> depth;
		if (depth < 0 || depth > 2) {
			cout << "Invalid depth. Using default depth of 0.\n";
			depth = 0;
		}
		isFirst = false;
	}
	else {
		doTurn();
	}

	// 1) Draw
	displayBoard();

	// 2) Recommend top 3 moves
	Board tmp(m_boardObject);
	MoveGenerator gen;
	auto best = gen.getBestMoves(tmp, m_turn, /*maxCount=*/3, depth);
	cout << "most recommanded move : ";
	for (size_t i = 0; i < best.size() && i < 3; ++i) {
		cout << best[i].toString();
		if (i + 1 < best.size() && i + 1 < 3) cout << ' ';
	}
	cout << '\n';

	// 3) Prompt & read
	showAskInput();
	cin >> m_input;
	if (isExit()) return "exit";

	// 4) Validate loop
	while (!isValid() || isSame()) {
		m_errorMsg = !isValid()
			? "Invalid input !! \n"
			: "The source and the destination are the same !! \n";
		displayBoard();
		showAskInput();
		cin >> m_input;
		if (isExit()) return "exit";
	}

	// 5) Normalize uppercase letters to lowercase for Board
	if (m_input != "exit") {
		if ('A' <= m_input[0] && m_input[0] <= 'H')
			m_input[0] = char(m_input[0] - 'A' + 'a');
		if ('A' <= m_input[2] && m_input[2] <= 'H')
			m_input[2] = char(m_input[2] - 'A' + 'a');
	}

	return m_input;
}


void Chess::setCodeResponse(int codeResponse)
{
	if (((11 <= codeResponse) && (codeResponse <= 13)) ||
		((21 == codeResponse) || (codeResponse == 31)) ||
		((41 == codeResponse) || (codeResponse == 42)))
		m_codeResponse = codeResponse;
}