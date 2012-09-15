#include <iostream>
#include <cstring>
using namespace std;

bool isCorrect(char *step) {

int spaceCount = 0;
char c = 0, row = -1;
char cols[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
char rows[] = {'0', '1', '2', '3' ,'4' ,'5', '6', '7', '8', '9'};
bool isCorrectC = 0, isCorrectR = 0;

while (*step) {
	if (*step == ' ')
		spaceCount++;
}
//cout << buf << endl << strlen(buf) << endl << spaceCount << endl;
if ((strlen(step) - spaceCount) != 2)  
	return 0; 

cin >> c >> row;
//cout << "c=" << c << " row=" << row << endl;
for (int i = 0; i < 8; i++ ) {
//cout << "cols " << cols[i] <<endl;
	if (c == cols[i]){
	isCorrectC = 1;
	break;
	}
}
for (int i = 0; i < 10; i++ ) {
	//cout << "rows " << rows[i] <<endl;
	if (row == rows[i]){
	isCorrectR = 1;
	break;
	}
}
//cout <<"isCorrectR "<< isCorrectR << " isCorrectC "<<isCorrectC<<endl;
if (!isCorrectC + !isCorrectR)
	return 0;
	else return 1;

}
