#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <locale>
#include <ncursesw/ncurses.h>

#include "levelGenerator.h"

int launchGame(int argc, char* argv[])
{
    
    std::locale::global(std::locale("")); // Set the global locale to the user's preferred locale
    std::wcout.imbue(std::locale()); // Set the wide character output stream to use the global locale
    setlocale(LC_ALL, "");

    initscr();
    start_color();
    cbreak();
    noecho();
    //keypad(stdscr, TRUE);

    // Enable Unicode support
    if (!has_colors() || !can_change_color() || !has_ic()) {
        endwin();
        return 1;
    }
    if (use_default_colors() == ERR) {
        endwin();
        return 1;
    }

    levelGenerator level(1);
    level.generatePreview("preview.png", 10);
    level.print(level.getPlayerPos().x, level.getPlayerPos().y, 20, 20);

    getch();    // Wait for a key press
    endwin();   // End ncurses
    return 0;
}

#endif
