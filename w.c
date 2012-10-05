#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{	

	int q[8][8];

	for(int i =0;i<8;i++)
		for(int j =0;j<8;j++)
	q[i][j] = i*j;

for(int i =0;i<8;i++){
		for(int j =0;j<8;j++)
	cout<<q[j][i];
cout << endl;
}

	return 0;
}



