#ifndef __WINDOW__
#define __WINDOW__

#include "GameSetting.h"
#include <ncurses.h>
#include <locale.h>

struct Window
{
    WINDOW *game, *mission, *score;
    Window(){
        setlocale(LC_ALL, "");
        initscr();
        curs_set(0);
        noecho();
        resize_term(TERM_HEIGHT, TERM_WIDTH);


        border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
        mvprintw(0,TERM_WIDTH/2 - 6, "<Snake Game>");
        refresh();

        game = newwin(GAME_HEIGHT+1,GAME_WIDTH+1, 1, 2);
        keypad(game, TRUE);
        wrefresh(game);

        mission = newwin(MISSION_HEIGHT+1, MISSION_WIDTH+1, 1, GAME_WIDTH+3);
        wborder(mission ,ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
        mvwprintw(mission, 1, MISSION_WIDTH/2 - 6,"<Mission List>");
        mvwprintw(mission, 3, 2,"B :           ");
        mvwprintw(mission, 5, 2,"+ :           ");
        mvwprintw(mission, 7, 2,"- :           ");
        mvwprintw(mission, 9, 2,"G :           ");
        wrefresh(mission);

        score = newwin(SCORE_HEIGHT+1, SCORE_WIDTH+1, MISSION_HEIGHT+2, GAME_WIDTH+3);
        wborder(score ,ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
        mvwprintw(score, 1, SCORE_WIDTH/2-3, "<Score>");
        mvwprintw(score, 3, 2,"B :           ");
        mvwprintw(score, 5, 2,"+ :           ");
        mvwprintw(score, 7, 2,"- :           ");
        mvwprintw(score, 9, 2,"G :           ");
        wrefresh(score);
    }

    void stage_clear_window(int level){
        wclear(game);

        if(level == STAGE_NUM)
            mvwprintw(game, GAME_HEIGHT/2, GAME_WIDTH/2 - 6, "<Game Clear!>");
        else 
            mvwprintw(game, GAME_HEIGHT/2, GAME_WIDTH/2 - 16, "<Stage %d clear!, Press any key.>", level);
        wrefresh(game);
        getch();
    }

    void end_Game(){
        delwin(game);
        delwin(score);
        delwin(mission);
        endwin();
    }
};

#endif