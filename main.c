#include <ncurses.h>
#include <stdlib.h>

static void draw_eye(int cy, int cx, int dir_y, int dir_x)
{
    int pupil_x = cx + dir_x;
    int pupil_y = cy + dir_y;

    /* Contorno */
    mvaddch(cy - 3, cx - 4, '/');
    mvaddch(cy - 3, cx + 4, '\\');

    mvaddch(cy - 2, cx - 5, '(');
    mvaddch(cy - 1, cx - 5, '|');
    mvaddch(cy,     cx - 5, '|');
    mvaddch(cy + 1, cx - 5, '|');
    mvaddch(cy + 2, cx - 5, '|');

    mvaddch(cy - 2, cx + 5, ')');
    mvaddch(cy - 1, cx + 5, '|');
    mvaddch(cy,     cx + 5, '|');
    mvaddch(cy + 1, cx + 5, '|');
    mvaddch(cy + 2, cx + 5, '|');

    mvaddch(cy + 3, cx - 4, '\\');
    mvaddch(cy + 3, cx + 4, '/');

    /* Pupila */
    mvaddch(pupil_y, pupil_x, '@');
}

int main(void)
{
    int ch;
    int max_y, max_x;

    /* Dirección de la mirada */
    int dir_x = 0;
    int dir_y = 0;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);

    while (1) {
        getmaxyx(stdscr, max_y, max_x);

        ch = getch();

        switch (ch) {
            case KEY_UP:
                dir_x = 0;
                dir_y = -2;
                break;

            case KEY_DOWN:
                dir_x = 0;
                dir_y = 2;
                break;

            case KEY_LEFT:
                dir_x = -3;
                dir_y = 0;
                break;

            case KEY_RIGHT:
                dir_x = 3;
                dir_y = 0;
                break;

            case 'q':
            case 'Q':
                endwin();
                return EXIT_SUCCESS;

            default:
                break;
        }

        clear();

        int eye_y = max_y / 2;
        int left_eye_x = max_x / 2 - 8;
        int right_eye_x = max_x / 2 + 8;

        draw_eye(eye_y, left_eye_x, dir_y, dir_x);
        draw_eye(eye_y, right_eye_x, dir_y, dir_x);

        mvprintw(max_y - 1, 1,
                 "neyes | Arrows: See | q: Exit");

        refresh();

        napms(30);
    }

    endwin();
    return EXIT_SUCCESS;
}
