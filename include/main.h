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
    level.generatePreview("preview.png", 1);

    bool end = false;
    while(!end)
    {
        level.print(level.getPlayerPos().x, level.getPlayerPos().y, 80, 40);
        int input = getch();
        clear();
        if(input == 68 || input == 97) 
        { 
            coords pos = level.getPlayerPos();
            level.setPlayerPos(pos.x - 1, pos.y);
        }
        else if(input == 67 || input == 100) 
        { 
            coords pos = level.getPlayerPos();
            level.setPlayerPos(pos.x + 1, pos.y);
        }
        else if(input == 65 || input == 119) 
        { 
            coords pos = level.getPlayerPos();
            level.setPlayerPos(pos.x, pos.y - 1);
        }
        else if (input == 66 || input == 115) 
        { 
            coords pos = level.getPlayerPos();
            level.setPlayerPos(pos.x, pos.y + 1);
        }
        else if(input == 'q')
        {
            end=true;
        }
        else 
        { 
            mvprintw(0, 0, "%d", input);
        }

    }
    
    endwin();   // End ncurses
    return 0;
}

#endif
