#include <cstring>
#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>
using namespace std;
#define BOARDX 16
#define BOARDY 8
WINDOW * board;
WINDOW * win;
WINDOW * msg;

class figure {
protected:
int x, y;
int symbol;
public:
void setxy(int i, int j) {x = i; y = j;}
int getx(){return x;}
int gety(){return y;}
int gets(){return symbol;}
figure getf(){return *this;}
figure(){symbol = 0;}
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

class player {
pawn p[8];
bishop b[2];
rook r[2];
knight h[2];
queen theq;
king thek;
bool isBlack;
public:
void show() {	
	for(int i = 0; i < 8; i++)
		
		mvwaddch(board, p[i].gety(), p[i].getx(), (isBlack)?(toupper(p[i].gets())):(p[i].gets()) );
	for(int i = 0; i < 2; i++) {
		mvwaddch(board, b[i].gety(), b[i].getx(), (isBlack)?(toupper(b[i].gets())):(b[i].gets()) );
		mvwaddch(board, r[i].gety(), r[i].getx(), (isBlack)?(toupper(r[i].gets())):(r[i].gets()) );
		mvwaddch(board, h[i].gety(), h[i].getx(), (isBlack)?(toupper(h[i].gets())):(h[i].gets()) );
	}
	mvwaddch(board, theq.gety(), theq.getx(), (isBlack)?(toupper(theq.gets())):(theq.gets()) );
	mvwaddch(board, thek.gety(), thek.getx(), (isBlack)?(toupper(thek.gets())):(thek.gets()) );	
}

void setFig(bool x) {
		isBlack = x;
		for (int i = 0; i < 8; i++)
			p[i].setxy(i*2, (isBlack)?(1):(6) );
		for (int i = 0; i < 2; i++) {
			b[i].setxy( (2+i*3)*2, (isBlack)?(0):(7) );	
			r[i].setxy( (i*7)*2, (isBlack)?(0):(7) );	
			h[i].setxy( (1+i*5)*2, (isBlack)?(0):(7) );
		}
		theq.setxy( 6, (isBlack == 1)?(0):(7) );
		thek.setxy( 8, (isBlack == 1)?(0):(7) );
	}

int step(int x, int y) {
	figure fig;
	int err, loop = 1, c;	
	for (int i = 0; i < 8; i++)
		if ( p[i].gety() == y && p[i].getx() == x)
			fig = p[i].getf();
	for (int i = 0; i < 2; i++) {
		if(b[i].gety() == y && b[i].getx() == x)
			fig = b[i].getf();
		if(r[i].gety() == y && r[i].getx() == x)
			fig = r[i].getf();
		if(h[i].gety() == y && h[i].getx() == x)
			fig = h[i].getf();
	}
		if (theq.gety() == y && theq.getx() == x)
			fig = theq.getf();
		if (thek.gety() == y && thek.getx() == x)
			fig = thek.getf();	

		if(fig.gets() == 0) return err = -1;

		
		
	
}

};

class game {
	player pw, pb;
public:
	void play() {

	pb.setFig(1);
	pw.setFig(0);

	int c, x=8, y=6, loop = 1, sy = 0, sx = 0, ssy, ssx, num = 0; 
	bool turn = 1, step = 0;//turn = 1 (White's turn)
	char * status[] = {"White's turn", "You have no any figure here", "Black's turn"};

	initscr();
	cbreak(); 
	noecho();
	
	msg = newwin(0, 0, 15, 0);
	box(msg, 0, 0);
	mvwprintw(msg, 1, COLS/2 - strlen(status[num])/2, status[num]);
	wrefresh(msg);
	win = newwin(BOARDY+2, BOARDX+2, 3, COLS/2-BOARDX/2);
	box(win, 0, 0);
	board = subwin(win ,BOARDY, BOARDX, 3+1, COLS/2-BOARDX/2+1);
	

	keypad(board, TRUE);
	wrefresh(win);
	
	werase(board);	
	werase(msg);
	
	pb.show();
	pw.show();

	wmove(board, y, x);

	while( loop ){
		c = wgetch(board);
		switch(c) {
		case KEY_UP:
			(y>0)?(y--):(y=BOARDY-1);
			wmove(board, y,x);
		break;
		case KEY_DOWN:
			(y<BOARDY-1)?(y++):(y=0);
			wmove(board, y,x);
		break;
		case KEY_LEFT:
			(x>0)?(x-=2):(x=BOARDX-2);
			wmove(board, y,x);
		break;
		case KEY_RIGHT:
			(x<BOARDX-2)?(x+=2):(x=0);
			wmove(board, y,x);
		break;
		case 'q':
			loop = 0;
		break;
		case ' ':
			if (turn) {
			pw.step(x, y);
			}
			else {
			}
		break;
		}//end switch
	wrefresh(msg);
	wrefresh(board);
	}//end while
	delwin(board);
	delwin(msg);
}//end play
};

int main(void) {

game thegame;

thegame.play();	

endwin();

return(0);
}


