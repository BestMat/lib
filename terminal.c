// Nagapillaiyar

#include <ncurses.h>

#define false 0

// Creates new window
WINDOW *create_newwin(
    int height,
    int width,
    int start_y,
    int start_x,
    int win_no)
{
  int color_pair = win_no == 1 ? 2 : 3;
  WINDOW *window;
  window = newwin(height, width, start_y, start_x);
  wattron(window, COLOR_PAIR(color_pair));
  box(window, 0, 0);
  wattron(window, COLOR_PAIR(color_pair));
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
  init_pair(2, COLOR_CYAN, COLOR_BLACK); // Top Win
  init_pair(3, COLOR_CYAN, COLOR_BLACK); // Bot Win
  init_pair(4, COLOR_RED, COLOR_BLACK);
  init_pair(5, COLOR_GREEN, COLOR_BLACK);

  // Creating top window:
  int width = cols;       // cols / 2 -> left window
  int height = rows / 2;  // rows     -> left window
  int start_x = 0;
  int start_y = 0;

  int top_x = 0;
  int top_y = 0;
  int bot_x = 0;
  int bot_y = 0;

  WINDOW *top = create_newwin(
      height,
      width,
      start_y,
      start_x,
      1
  );
  
  // Creating bottom window:
  width = cols;           // cols / 2 -> right window
  height = rows / 2;      // rows     -> right window
  start_y = height; 

  bot_y = start_y;

  WINDOW *bot = create_newwin(
      height,
      width,
      start_y,
      start_x,
      2
  );

  // Display text on windows:
  wattron(top, COLOR_PAIR(4));
  wprintw(top, "Window TOP");
  wattroff(top, COLOR_PAIR(4));
  wattron(top, COLOR_PAIR(1));
  mvwprintw(top, 1, 2, "Hello from TOP!");
  wrefresh(top);
  wattroff(top, COLOR_PAIR(1));
  
  wattron(bot, COLOR_PAIR(4));
  wprintw(bot, "Window BOT");
  wattroff(bot, COLOR_PAIR(4));
  wattron(bot, COLOR_PAIR(1));
  mvwprintw(bot, 1, 2, "Hello from BOT!");
  wrefresh(bot);
  wattroff(bot, COLOR_PAIR(1));

  int topx = 2;
  int topy = 2;
  int botx = 2;
  int boty = 2;

  WINDOW *cur_win = bot;
  int cur_win_no = 2;

  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  wrefresh(cur_win);

  while (true) {
    char key = getch();
    if (key == 'q') break;
    if (key == 'd') {
      if (cur_win_no == 1) {
        getmaxyx(stdscr, rows, cols);
        wattron(cur_win, COLOR_PAIR(5));
        mvwprintw(
            cur_win,
            topy,
            topx,
            "Debug: MAX ROWS = %d",
            rows
        );
        mvwprintw(
            cur_win,
            ++topy,
            topx,
            "Debug: MAX COLS = %d",
            cols
        );
        wattroff(cur_win, COLOR_PAIR(5));
        wrefresh(cur_win);

        topy += 2;
      } else if (cur_win_no == 2) {
        getmaxyx(stdscr, rows, cols);
        wattron(cur_win, COLOR_PAIR(5));
        mvwprintw(
            cur_win,
            boty,
            botx,
            "Debug: MAX ROWS = %d",
            rows
        );
        mvwprintw(
            cur_win,
            ++boty,
            botx,
            "Debug: MAX COLS = %d",
            cols
        );
        wattroff(cur_win, COLOR_PAIR(5));
        wrefresh(cur_win);

        boty += 2;
      }
    } else if (key == 't') {
      cur_win = top;
      cur_win_no = 1;
      init_pair(2, COLOR_BLUE, COLOR_BLACK);
      init_pair(3, COLOR_CYAN, COLOR_BLACK);
      wrefresh(cur_win);
    } else if (key == 'b') {
      cur_win = bot;
      cur_win_no = 2;
      init_pair(2, COLOR_CYAN, COLOR_BLACK);
      init_pair(3, COLOR_BLUE, COLOR_BLACK);
      wrefresh(cur_win);
    }
  }

  delwin(top);
  delwin(bot);

  endwin();

  return 0;
}
