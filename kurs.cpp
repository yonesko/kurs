#include <iostream>
#include <fstream>
#include "screen.h"
#include "functions.h"
#include <cstring>
using namespace std;

class board {
char board1[600];
public:
	board(const char *fileName){
char ch;
	ifstream in(fileName, ios::binary);

	if (!in)
		cerr << "Can't open \"board\".\n";	
	else {
		int i;
		for (i = 0; !in.eof(); i++) {
			in.get(ch);
			board1[i] = ch;
		}
		board1[i] = '\0';
	}		
	in.close();
}
	
	void show(void) {
	cout << board1;
	}	
};




int main(void) {

board chessBoard("board");
char buf[10];

cin.get(buf, 10);
if (isCorrect(buf))
	cout << "Correct" << endl;
	else
	cout << "Incorrect" << endl;

return(0);
}
