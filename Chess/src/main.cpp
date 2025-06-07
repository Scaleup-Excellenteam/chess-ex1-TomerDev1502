// Chess 
#include "Chess.h"
#include "Board.h"
#include "PriorityQueue.h"

int main()
{
	PriorityQueue<int> q;             // now templated
	q.push(10);
	q.push(5);
	q.push(20);
	std::cout << q.poll() << "\n";    // still prints 20

	try {
		q.push(1);
		q.push(2);
		q.push(3);
		q.push(4);
		q.push(5);
		q.push(6);                    // should throw
	}
	catch (const std::exception& ex) {
		std::cout << "Caught: " << ex.what() << "\n";
	}
	return 0;
	//string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr"; 
	////string board = "##QBK#####################################R#############r#r#####";
	//Chess a(board);

	//Board objectBoard(board);
	//int codeResponse = 0;
	//string res = a.getInput();
	//while (res != "exit")
	//{
	//	/* 
	//	codeResponse value : 
	//	Illegal movements : 
	//	11 - there is not piece at the source  
	//	12 - the piece in the source is piece of your opponent
	//	13 - there one of your pieces at the destination 
	//	21 - illegal movement of that piece 
	//	31 - this movement will cause you checkmate

	//	legal movements : 
	//	41 - the last movement was legal and cause check 
	//	42 - the last movement was legal, next turn 
	//	*/

	//	/**/ 
	//	{ // put your code here instead that code
	//		std::string source = res.substr(0, 2);
	//		std::string dest = res.substr(2, 2);
	//		codeResponse = objectBoard.validateMove(source, dest);
	//		if (codeResponse == 41 || codeResponse == 42) {
	//			objectBoard.doMove(source, dest);
	//		}
	//	}
	//	/**/

	//	a.setCodeResponse(codeResponse);
	//	res = a.getInput(); 
	//}

	//cout << endl << "Exiting " << endl; 
}