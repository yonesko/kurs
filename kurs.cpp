#include <cstring>
#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>
using namespace std;
#define BOARDX 16
#define BOARDY 8

class figure {
protected:
int x, y;
int symbol;
public:
void setxy(int i, int j) {x = i; y = j;}
int getx(){return x;}
int gety(){return y;}
int gets(){return symbol;}
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
void show(WINDOW * win) {	
	for(int i = 0; i < 8; i++)
		mvwaddch(win, p[i].gety(), p[i].getx(), (isBlack)?(toupper(p[i].gets())):(p[i].gets()) );
	for(int i = 0; i < 2; i++) {
		mvwaddch(win, b[i].gety(), b[i].getx(), (isBlack)?(toupper(b[i].gets())):(b[i].gets()) );
		mvwaddch(win, r[i].gety(), r[i].getx(), (isBlack)?(toupper(r[i].gets())):(r[i].gets()) );
		mvwaddch(win, h[i].gety(), h[i].getx(), (isBlack)?(toupper(h[i].gets())):(h[i].gets()) );
	}
	mvwaddch(win, theq.gety(), theq.getx(), (isBlack)?(toupper(theq.gets())):(theq.gets()) );
	mvwaddch(win, thek.gety(), thek.getx(), (isBlack)?(toupper(thek.gets())):(thek.gets()) );	
}

int isExists(int y, int x) {
	for (int i = 0; i < 8; i++)
		if ( p[i].gety() == y && p[i].getx() == x )
			return p[i].gets();
	for (int i = 0; i < 2; i++) {
		if(b[i].gety() == y && b[i].getx() == x)
			return b[i].gets();
		if(r[i].gety() == y && r[i].getx() == x)
			return r[i].gets();
		if(h[i].gety() == y && h[i].getx() == x)
			return h[i].gets();
	}
		if (theq.gety() == y && theq.getx() == x)
			return theq.gets();
		if (thek.gety() == y && thek.getx() == x)
			return thek.gets();
	return -1;
}

player() {
		for(int i = 0; i < 8; i++)
			p[i].setxy(i*2, (isBlack)?(1):(6) );
		for(int i = 0; i < 2; i++) {
			b[i].setxy(4+i*6, (isBlack)?(0):(7) );
			r[i].setxy(i*14, (isBlack)?(0):(7) );
			h[i].setxy(2+i*10, (isBlack)?(0):(7) );
		}
		theq.setxy(6, (isBlack)?(0):(7) );
		thek.setxy(8, (isBlack)?(0):(7) );
	}
void setClr(bool x) { isBlack = x; }

};

class game {
	player pw, pb;
public:
	void play() {

	pb.setClr(1);
	pw.setClr(0);
	WINDOW * board;
	WINDOW * msg;
	int c, x=8, y=6, loop = 1, sy = 0, sx = 0, ssy, ssx, num = 0; 
	int s = 0;
	bool turn = 1, step = 0;//turn = 1 (White's turn)
	char * status[] = {"White's turn", "You have no any figure here", "Black's turn"};

	if(!(initscr())){
   		fprintf(stderr,"type: initscr() failed\n\n");
  		 exit (1);
	}
	cbreak(); 
	noecho();
	
	msg = newwin(0, 0, 15, 0);
	box(msg, 0, 0);
	mvwprintw(msg, 1, COLS/2 - strlen(status[num])/2, status[num]);
	wrefresh(msg);
	
	board = newwin(BOARDY, BOARDX, 3, COLS/2-BOARDX/2);
	keypad(board, TRUE);
	
	for (int i = 0; i < BOARDX; i++)
		for (int j = 0; j < BOARDY; j++)
			mvwaddch(board, j, i, ' ');
	
	werase(board);	
	werase(msg);
	
	pb.show(board);
	pw.show(board);

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
			if (step) {
				ssx = x; ssy = y; // start step coord
				waddch(board, s);
				mvwaddch(board, sy, sx, ' ');
				wmove(board, ssy, ssx);
				turn = !turn;
				step = !step;

				werase(msg);
				box(msg, 0, 0);
				mvwprintw(msg, 1, COLS/2 - strlen(status[num])/2, status[num]);
				//waddch(msg , s);
				
				
			}//end if
			else {
				
				if (turn) { 
					num = 2; step = !step;
				}
				else {
					num = 0; step = !step;
				}
				sy = y; sx = x; // start step coord
		
		
			}//end else
		wrefresh(msg);
		wrefresh(board);
		break;
		}//end switch
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


