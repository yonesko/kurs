#include <fstream>
//#include "functions.h"
#include <cstring>
#include <ncurses.h>
#include <stdlib.h>
using namespace std;
#define BOARDX 16
#define BOARDY 8

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
	void show(WINDOW * win) {	
		for(int i = 0; i < 8; i++)
			mvwaddch(win, p[i].y, p[i].x, p[i].symbol);
		for(int i = 0; i < 2; i++) {
			mvwaddch(win, b[i].y, b[i].x, b[i].symbol);
			mvwaddch(win, r[i].y, r[i].x, r[i].symbol);
			mvwaddch(win, h[i].y, h[i].x, h[i].symbol);
		}
		mvwaddch(win, theq.y, theq.x, theq.symbol);
		mvwaddch(win, thek.y, thek.x, thek.symbol);	
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
	void show(WINDOW * win) {	
		for(int i = 0; i < 8; i++)
			mvwaddch(win, p[i].y, p[i].x, p[i].symbol | A_BOLD);
		for(int i = 0; i < 2; i++) {
			mvwaddch(win, b[i].y, b[i].x, b[i].symbol | A_BOLD);
			mvwaddch(win, r[i].y, r[i].x, r[i].symbol | A_BOLD);
			mvwaddch(win, h[i].y, h[i].x, h[i].symbol | A_BOLD);
		}
		mvwaddch(win, theq.y, theq.x, theq.symbol | A_BOLD);
		mvwaddch(win, thek.y, thek.x, thek.symbol | A_BOLD);	
	}	
};

class game {
	playerWhite pw;
	playerBlack pb;
public:
	void play() {

	
	WINDOW * board;
	WINDOW * msg;
	int c, x=8, y=6, loop = 1;
	char status[] = {"Hello bro"};
	
	if(!(initscr())){
   		fprintf(stderr,"type: initscr() failed\n\n");
  		 exit (1);
	}
	cbreak(); 
	noecho();
	
	msg = newwin(0, 0, 15, 0);
	box(msg, 0, 0);
	mvwprintw(msg, 1, COLS/2 - strlen(status)/2, status);
	wrefresh(msg);
	
	board = newwin(BOARDY, BOARDX, 3, COLS/2-BOARDX/2);
	keypad(board, TRUE);
	pb.show(board);
	pw.show(board);

	wmove(board, y, x);

	while( loop ){
		c = wgetch(board);
		switch(c) {
		case KEY_UP:
		case 'w':
		(y>0)?(y--):(y=BOARDY-1);
		wmove(board, y,x);
		break;
		case 's':
		case KEY_DOWN:
		(y<BOARDY-1)?(y++):(y=0);
		wmove(board, y,x);
		break;
		case 'a':
		case KEY_LEFT:
		(x>0)?(x-=2):(x=BOARDX-2);
		wmove(board, y,x);
		break;
		case 'd':
		case KEY_RIGHT:
		(x<BOARDX-2)?(x+=2):(x=0);
		wmove(board, y,x);
		break;
		case 'q':
		loop = 0;
		break;
		case 'e':
		werase(msg);
		strcpy(status, "Omg");
		mvwprintw(msg, 1, COLS/2 - strlen(status)/2, status);
		break;
		}
		wrefresh(msg);

	}	
	delwin(board);
	delwin(msg);
	}
	
};

int main(void) {

game thegame;

thegame.play();	

endwin();

return(0);
}

