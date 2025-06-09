// Chess 
#include "Chess.h"
#include "Board.h"
#include "PriorityQueue.h"


int main()
{
    std::string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    //std::string board = "##QBK#####################################R#############r#r#####";
    Board objectBoard(board);
    Chess a(board);
    

    int codeResponse = 0;
    std::string res = a.getInput();
    while (res != "exit")
    {
        /*
        codeResponse value :
        Illegal movements :
        11 - there is not piece at the source
        12 - the piece in the source is piece of your opponent
        13 - there one of your pieces at the destination
        21 - illegal movement of that piece
        31 - this movement will cause you checkmate

        legal movements :
        41 - the last movement was legal and cause check
        42 - the last movement was legal, next turn
        */

        { // existing validation & move
            std::string source = res.substr(0, 2);
            std::string dest = res.substr(2, 2);
            codeResponse = objectBoard.validateMove(source, dest);
            if (codeResponse == 41 || codeResponse == 42) {
                objectBoard.doMove(source, dest);
            }
        }

        a.setCodeResponse(codeResponse);
        res = a.getInput();
    }

    std::cout << std::endl << "Exiting " << std::endl;
    return 0;
}