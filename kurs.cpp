#include <ncurses.h>

#define BOARDWI 16
#define BOARDHI 8

WINDOW * Wboard;
WINDOW * msg;
WINDOW * in;
WINDOW * digitRow;
WINDOW * digitCol;

class figure
{
char color;
public:
	figure(char clr) : color(clr) {}
	~figure() {}
	virtual chtype getSym() = 0;
	char getColor() { return color; }
};

class pawn:public figure {

public:
	pawn(char clr) : figure(clr) {}
	~pawn() {}
	 chtype getSym() { if(this->getColor() == 'W') return 'p'; else return 'P' | A_BOLD; }
	
};

class bishop:public figure {
public:
	bishop(char clr) : figure(clr) {}
	~bishop() {}
	 chtype getSym() { if(this->getColor() == 'W') return 'b'; else return 'B'| A_BOLD;; }

};

class rook:public figure {
public:
	rook(char clr) : figure(clr) {}
	~rook() {}
	 chtype getSym() { if(this->getColor() == 'W') return 'r'; else return 'R'| A_BOLD;; }

};

class knight:public figure {
public:
	knight(char clr) : figure(clr) {}
	~knight() {}
	 chtype getSym() { if(this->getColor() == 'W') return 'h'; else return 'H'| A_BOLD;; }

};

class king:public figure {
public:
	king(char clr) : figure(clr) {}
	~king() {}
	 chtype getSym() { if(this->getColor() == 'W') return 'k'; else return 'K'| A_BOLD;; }

};

class queen:public figure {
public:
	queen(char clr) : figure(clr) {}
	~queen() {}
	 chtype getSym() { if(this->getColor() == 'W') return 'q'; else return 'Q'| A_BOLD;; }

};

class board {
public:
	figure * fBoard[8][8];
	
	board() {
		for (int i = 0; i < 8; i++) 
			for (int j = 0; j < 8; j++) 
				fBoard[i][j] = 0;
			//Place black figures
			for (int i = 0; i < 8; i++) 
				fBoard[1][i] = new pawn('B');
			
			fBoard[0][0] = new rook('B');
			fBoard[0][1] = new knight('B');
			fBoard[0][2] = new bishop('B');
			fBoard[0][3] = new queen('B');
			fBoard[0][4] = new king('B');
			fBoard[0][5] = new bishop('B');
			fBoard[0][6] = new knight('B');
			fBoard[0][7] = new rook('B');
		
			//Place white figures
			for (int i = 0; i < 8; i++) 
				fBoard[6][i] = new pawn('W');
			
			fBoard[7][0] = new rook('W');
			fBoard[7][1] = new knight('W');
			fBoard[7][2] = new bishop('W');
			fBoard[7][3] = new queen('W');
			fBoard[7][4] = new king('W');
			fBoard[7][5] = new bishop('W');
			fBoard[7][6] = new knight('W');
			fBoard[7][7] = new rook('W');
	}

	~board() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				delete fBoard[i][j];
				fBoard[i][j] = 0;
			}
		}
	}

	void print() {
			
		for(int i = 0; i < 8; i++)
			for(int j = 0; j < 8; j++) 
				if(fBoard[j][i]!=0)
					mvwaddch(Wboard, j, i*2, fBoard[j][i]->getSym());


		for(int i = 0 ; i < 8; i++) {
			wprintw(digitRow, "%d ", i+1);
			wprintw(digitCol, "%d|", 8-i);
		}
	wrefresh(Wboard);	
	wrefresh(digitRow);	
	wrefresh(digitCol);
	}
	
};

class game {
	board ChessBoard;
	char playerColor;
public:
	game() : playerColor('W') {}
	~game() {}

	void start() {
		initscr();
		Wboard = newwin(BOARDHI, BOARDWI, 3, 13);
		in = newwin(10,11,3,30);
		digitRow = newwin(1,16,2,13);
		digitCol = newwin(8,2,3,11);
		do {
			getNextMove(ChessBoard.fBoard);
			reverseColor();
		} while(1);
		endwin();
	}
	
	void getNextMove(figure * gBoard[8][8]) {
	int startM, endM, startX, startY, endX, endY;
	werase(in);
	ChessBoard.print();
	
	waddstr(in, "StartXY:");
	wscanw(in, "%d", &startM);
	
	startX = startM / 10 - 1;
	startY = startM % 10 - 1;
	
	waddstr(in, "EndXY:");	
	wscanw(in, "%d", &endM);
	
	endX = endM / 10 - 1;
	endY = endM % 10 - 1;

	gBoard[7-endY][endX]= gBoard[7-startY][startX];
	gBoard[startY][startX] = 0;
	}

	void reverseColor() {
		playerColor = (playerColor=='W')?('B'):('W');
	}
	
};

int main(void) {

game thegame;

thegame.start();

return(0);
}


