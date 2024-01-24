#include <curses.h>
#include <thread>
#include <chrono>
#include <mutex>

int main(void)
{
    bool done = FALSE;
    WINDOW *input, *output;
    char buffer[1024];
    std::mutex mtx;
    initscr();
    cbreak();
    echo();
    input = newwin(1, COLS, LINES - 1, 0);
    output = newwin(LINES - 1, COLS, 0, 0);
    wmove(output, LINES - 2, 0);    /* start at the bottom */
    scrollok(output, TRUE);
    std::thread thrd ([&](){
        while(!done) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                int x = getcurx(input);
                int y = getcury(input);
                waddstr(output, "this is a message\n");
                wmove(input, y, x);
                wrefresh(output);
                wrefresh(input);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

    });
    std::thread thrd1 ([&](){
        while (!done) {
                mvwprintw(input, 0, 0, "> ");
                if (wgetnstr(input, buffer, COLS - 4) != OK) {
                    break;
                }
                werase(input);
                {
                std::lock_guard<std::mutex> lock(mtx);
                
                waddstr(output, buffer);
                waddch(output, '\n');   /* result from wgetnstr has no newline */
                wrefresh(output);
                }
                done = (*buffer == 4);  /* quit on control-D */

        }

    });
    thrd.join();
    thrd1.join();
    endwin();
    return 0;
}
