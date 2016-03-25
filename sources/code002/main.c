#include <conio/conio2.h>

int main(void)
{
  textcolor(LIGHTGREEN);
  textbackground(RED);
  gotoxy(30,12);
  cprintf("Hello World!");
  getch();

  return 0;
}

