#include <fstream>
//#include "functions.h"
#include <cstring>
#include <ncurses.h>
using namespace std;


class figure {
public:
int x, y;
chtype symbol;
void setxy(int i, int j) {x = i; y = j;}
};

class pawn:public figure {
public:
pawn(){symbol = 'p'; x = y = 0;}
};

class bishop:public figure {
public:
bishop(){symbol = 'b'; x = y = 0;}
};

class rook:public figure {
public:
rook(){symbol = 'r'; x = y = 0;}
};

class knight:public figure {
public:
knight(){symbol = 'h'; x = y = 0;}
};

class king:public figure {
public:
king(){symbol = 'k'; x = y = 0;}
};

class queen:public figure {
public:
queen(){symbol = 'q'; x = y = 0;}
};

class playerWhite {
	pawn p[8];
	bishop b[2];
	rook r[2];
	knight h[2];
	queen theq;
	king thek;
public:
	playerWhite() {
		for(int i = 0; i < 8; i++)
			p[i].setxy(i*2, 6);
		for(int i = 0; i < 2; i++) {
			b[i].setxy(4+i*6, 7);
			r[i].setxy(i*14, 7);
			h[i].setxy(2+i*10, 7);
		}
		theq.setxy(6, 7);
		thek.setxy(8, 7);
	}
	void show() {	
		for(int i = 0; i < 8; i++)
			mvaddch(p[i].y, p[i].x, p[i].symbol);
		for(int i = 0; i < 2; i++) {
			mvaddch(b[i].y, b[i].x, b[i].symbol);
			mvaddch(r[i].y, r[i].x, r[i].symbol);
			mvaddch(h[i].y, h[i].x, h[i].symbol);
		}
		mvaddch(theq.y, theq.x, theq.symbol);
		mvaddch(thek.y, thek.x, thek.symbol);	
	}	
};

class playerBlack {
	pawn p[8];
	bishop b[2];
	rook r[2];
	knight h[2];
	queen theq;
	king thek;
public:
	playerBlack() {
		for(int i = 0; i < 8; i++)
			p[i].setxy(i*2, 1);
		for(int i = 0; i < 2; i++) {
			b[i].setxy(4+i*6, 0);
			r[i].setxy(i*14, 0);
			h[i].setxy(2+i*10, 0);
		}
		theq.setxy(6, 0);
		thek.setxy(8, 0);
	}
	void show() {	
		for(int i = 0; i < 8; i++)
			mvaddch(p[i].y, p[i].x, p[i].symbol | A_BOLD);
		for(int i = 0; i < 2; i++) {
			mvaddch(b[i].y, b[i].x, b[i].symbol | A_BOLD);
			mvaddch(r[i].y, r[i].x, r[i].symbol | A_BOLD);
			mvaddch(h[i].y, h[i].x, h[i].symbol | A_BOLD);
		}
		mvaddch(theq.y, theq.x, theq.symbol | A_BOLD);
		mvaddch(thek.y, thek.x, thek.symbol | A_BOLD);	
	}	
};

class game {
	playerWhite pw;
	playerBlack pb;
public:
	void play() {
	chtype c;
	initscr();
	cbreak(); 
	noecho();
	keypad(scr, TRUE);

	pb.show();
	pw.show();
	WINDOW * scr = newwin(5,COLS,15,0);		
	box(scr, 0 , 0);
	mvwaddstr(scr, 1, 1, "White's turn!");
	wnoutrefresh(stdscr);
	wnoutrefresh(scr);
	doupdate();
	
	for(;;)
	{
		switch (c)
		{
		case KEY_UP:
		printw("dfg");
		break;
		}	 
	}	

	endwin();
	}
};

int main(void) {

game thegame;

thegame.play();	
					
endwin();
return(0);
}
