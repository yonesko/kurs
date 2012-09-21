#include <ncurses.h>




int main(int argc, char *argv[])
{	
	WINDOW *win;
	initscr();

		
 	refresh();
	
	win = newwin(10, 10, 10, 10);
	box(win, 0, 0);
	
	wprintw(win, "GFF");
	wrefresh(win);

	getch();
	endwin();		
	return 0;
}



