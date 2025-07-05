// Nagapillaiyar

#include <ncurses.h>

#define false 0

// Creates new window
WINDOW *create_newwin(
    int height,
    int width,
    int start_y,
    int start_x)
{
  WINDOW *window;
  window = newwin(height, width, start_y, start_x);
  wattron(window, COLOR_PAIR(2));
  box(window, 0, 0);
  wattron(window, COLOR_PAIR(2));
  wrefresh(window);

  return window;
}

int main() {
  initscr();
  refresh();

  noecho();
  curs_set(false);

  int rows = 0;
  int cols = 0;

  getmaxyx(stdscr, rows, cols);

  if (has_colors() == false) {
    endwin();
  }

  start_color();

  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);

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
  wattron(top, COLOR_PAIR(1));
  wprintw(top, "Window TOP");
  mvwprintw(top, 1, 2, "Hello from TOP!");
  wrefresh(top);
  wattroff(top, COLOR_PAIR(1));
  
  wattron(bot, COLOR_PAIR(1));
  wprintw(bot, "Window BOT");
  mvwprintw(bot, 1, 2, "Hello from BOT!");
  wrefresh(bot);
  wattroff(bot, COLOR_PAIR(1));

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
