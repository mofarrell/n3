#include <ncurses.h>
#include <string.h>

#define WIDTH 30
#define HEIGHT 10

int startX = 0;
int startY = 0;

char const *choices[] = { "Choice 1",
                    "Choice 2",
                    "Choice 3",
                    "Choice 4",
                    "Exit",
                  };

int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);
void report_choice(int mouse_x, int mouse_y, int *p_choice);

int main()
{
  int c, choice = 0;
  WINDOW *menu_win;
  MEVENT event;

  /* Initialize curses. */
  initscr();
  clear();
  noecho();
  cbreak(); //Disable line buffering

  /* Try to put the window in the middle of screen */
  startX = (80 - WIDTH)  / 2;
  startY = (24 - HEIGHT) / 2;
  
  attron(A_REVERSE);
  mvprintw(23, 1, "Click on Exit to quit (Works best in a virtua console)");
  refresh();
  attroff(A_REVERSE);

  /* Print the menu */
  menu_win = newwin(HEIGHT, WIDTH, startY, startX);
  print_menu(menu_win, 1);
  /* Get all the mouse events */
  mousemask(ALL_MOUSE_EVENTS, NULL);

  while(1) {
    c = wgetch(menu_win);
    switch(c) {
      case KEY_MOUSE:
        /* Left mouse */
        if (getmouse(&event) == OK) {
          report_choice(event.x + 1, event.y + 1, &choice);
          //Exit
          if (choice == -1) {
            goto end;
          }
          mvprintw(22, 1, "Choice made: %d and String chosen: \"%10s\"", choice, choices[choice - 1]);
          refresh();
        }
        print_menu(menu_win, choice);
        break;
      }
  }
end: 
  endwin();
  return 0;
}

void print_menu(WINDOW *menu_win, int highlight)
{
  int x, y, i;  

  x = 2;
  y = 2;
  box(menu_win, 0, 0);
  for(i = 0; i < n_choices; ++i)
  { if(highlight == i + 1)
    { wattron(menu_win, A_REVERSE); 
      mvwprintw(menu_win, y, x, "%s", choices[i]);
      wattroff(menu_win, A_REVERSE);
    }
    else
      mvwprintw(menu_win, y, x, "%s", choices[i]);
    ++y;
  }
  wrefresh(menu_win);
}

/* Report the choice according to mouse position */
void report_choice(int mouse_x, int mouse_y, int *p_choice)
{ 
  int i,j, choice;

  i = startX + 2;
  j = startY + 3;

  for(choice = 0; choice < n_choices; ++choice)
    if(mouse_y == j + choice && mouse_x >= i && mouse_x <= i + strlen(choices[choice]))
    { if(choice == n_choices - 1)
      *p_choice = -1;   
      else
        *p_choice = choice + 1; 
      break;
    }
}

