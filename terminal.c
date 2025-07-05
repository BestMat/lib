// Nagapillaiyar

#include <ncurses.h>

// Creates new window
WINDOW *create_newwin(
    int height,
    int width,
    int start_y,
    int start_x)
{
  WINDOW *window;
  window = newwin(height, width, start_y, start_x);
  box(window, 0, 0);
  wrefresh(window);

  return window;
}

int main() {
  initscr();
  refresh();

  int rows = 0;
  int cols = 0;

  getmaxyx(stdscr, rows, cols);

  // Creating top window:
  int width = cols;
  int height = rows / 2;
  int start_x = 0; 
  int start_y = 0; 

  WINDOW *top = create_newwin(height, width, start_y, start_x);
  
  // Creating bottom window:
  width = cols;
  height = rows / 2;
  start_y = height; 

  WINDOW *bot = create_newwin(height, width, start_y, start_x);

  // Display text on windows:
  wprintw(top, "Window TOP");
  mvwprintw(top, 1, 2, "Hello from TOP!");
  wrefresh(top);
  wprintw(bot, "Window BOT");
  mvwprintw(bot, 1, 2, "Hello from BOT!");
  wrefresh(bot);

  while (true) {
    char key = getch();
    if (key == 'q') break;
    if (key == 'd') {
      getmaxyx(stdscr, rows, cols);
      printw("MAX ROWS = %d\n", rows);
      printw("MAX COLS = %d\n\n", cols);
    } 
  }

  delwin(top);
  delwin(bot);

  endwin();

  return 0;
}
