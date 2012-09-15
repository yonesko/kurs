#include <stdio.h>

void screenClear(){
printf ("%c[2J", 27);
}

void screenOrigin(){
printf ("%c[H", 27);
}

void screenGoTo(int i, int j){
printf ("%c[%d;%dH",27, i, j);
}
