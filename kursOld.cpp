#include <cstring>
#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>
using namespace std;
#define BOARDX 16
#define BOARDY 8

class figure {
public:
int x, y;
int symbol;
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
	int step(int y, int x) {
		for (int i = 0; i < 8; i++)
			if ( p[i].y == y && p[i].x == x )
				return p[i].symbol;
		for (int i = 0; i < 2; i++) {
			if(b[i].y == y && b[i].x == x)
				return b[i].symbol;
			if(r[i].y == y && r[i].x == x)
				return r[i].symbol;
			if(h[i].y == y && h[i].x == x)
				return h[i].symbol;
		}
			if (theq.y == y && theq.x == x)
				return theq.symbol;
			if (thek.y == y && thek.x == x)
				return thek.symbol;
		return 0;
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
			mvwaddch(win, p[i].y, p[i].x, toupper(p[i].symbol) );
		for(int i = 0; i < 2; i++) {
			mvwaddch(win, b[i].y, b[i].x, toupper(b[i].symbol) );
			mvwaddch(win, r[i].y, r[i].x, toupper(r[i].symbol) );
			mvwaddch(win, h[i].y, h[i].x,toupper( h[i].symbol) );
		}
		mvwaddch(win, theq.y, theq.x, toupper(theq.symbol) );
		mvwaddch(win, thek.y, thek.x, toupper(thek.symbol) );	
	}
	int step(int y, int x) {
		for (int i = 0; i < 8; i++)
			if ( p[i].y == y && p[i].x == x )
				return p[i].symbol;
		for (int i = 0; i < 2; i++) {
			if(b[i].y == y && b[i].x == x)
				return b[i].symbol;
			if(r[i].y == y && r[i].x == x)
				return r[i].symbol;
			if(h[i].y == y && h[i].x == x)
				return h[i].symbol;
		}
			if (theq.y == y && theq.x == x)
				return theq.symbol;
			if (thek.y == y && thek.x == x)
				return thek.symbol;
		return 0;
	}	
};

class game {
	playerWhite pw;
	playerBlack pb;
public:
	void play() {

	
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
					s = pw.step(y, x);
					if (s == 0) {
						werase(msg);
						box(msg, 0, 0);
						mvwprintw(msg, 1, COLS/2 - strlen(status[1])/2, status[1]);
					}
					else
					{num = 2; step = !step;}
				}
				else {
					s = toupper(pb.step(y, x));
					if (s == 0) {
						werase(msg);
						box(msg, 0, 0);
						mvwprintw(msg, 1, COLS/2 - strlen(status[1])/2, status[1]);
					}
					else
					{num = 0; step = !step;}
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


