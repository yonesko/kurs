#include <ncurses.h>




int main(int argc, char *argv[])
{	
	WINDOW *win;
	initscr();
	clear();
	noecho();	
	cbreak(); 
	int c;
	int x = 0, y = 0, my, mx;
	
	win = newwin(10, 10, 10, 10);
	box(win, 0, 0);
	keypad(win, TRUE);
	
	refresh();
	
while( (c = wgetch(win)) != KEY_F(2) ){
		wrefresh(win);
		switch(c){
		case KEY_UP:
		(y>0)?(y--):(y=9);
		wmove(win, y,x);
		
		break;
		case KEY_DOWN:
		y++;
		wmove(win, y,x);
		break;
		case KEY_LEFT:
		x--;
		wmove(win, y,x);
		break;
		case KEY_RIGHT:
		x++;
		wmove(win, y,x);
		break;
		}
	}	

	endwin();		
	return 0;
}



