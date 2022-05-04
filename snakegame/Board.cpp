#include "Board.h"

Board::Board(Snake& snake){
    snake_length_score = snake.now_len;
    max_snake_length_score = snake.max_len;
    heal_score = snake.heal_num;
    poison_score = snake.poison_num;
    gate_score = snake.gate_num;
    mvwprintw(snake.score, 3, 7, "%d / %d", snake_length_score, max_snake_length_score);
    mvwprintw(snake.score, 5, 7, "%d", heal_score);
    mvwprintw(snake.score, 7, 7, "%d", poison_score);
    mvwprintw(snake.score, 9, 7, "%d", gate_score);
    wrefresh(snake.score);


    int level = snake.level;
    mvwprintw(snake.mission, 3, 7, "%d", missions[level][0]);
    mvwprintw(snake.mission, 5, 7, "%d", missions[level][1]);
    mvwprintw(snake.mission, 7, 7, "%d", missions[level][2]);
    mvwprintw(snake.mission, 9, 7, "%d", missions[level][3]);
    wrefresh(snake.mission);
}

void Board::update_boards(Snake& snake){
    if(snake_length_score != snake.now_len)
    {
        snake_length_score = snake.now_len;
        if(max_snake_length_score != snake.max_len)
        {
            max_snake_length_score = snake.max_len;
        }
        mvwprintw(snake.score, 3, 7, "%d / %d ", snake_length_score, max_snake_length_score);
    }
    if(heal_score != snake.heal_num)
    {
        heal_score = snake.heal_num;
        mvwprintw(snake.score, 5, 7, "%d", heal_score);
    }
    else if(poison_score != snake.poison_num)
    {
        poison_score = snake.poison_num;
        mvwprintw(snake.score, 7, 7, "%d", poison_score);
    }
    else if(gate_score != snake.gate_num)
    {
        gate_score = snake.gate_num;
        mvwprintw(snake.score, 9, 7, "%d", gate_score);
    }
    wrefresh(snake.score);

    if(snake.clear_Stage != true)
    {
        if(max_snake_length_score == missions[snake.level][0])
        {
            mvwprintw(snake.mission, 3, 10, "V");
            blength = true;
        }
        if(heal_score == missions[snake.level][1])
        {
            mvwprintw(snake.mission, 5, 10, "V");
            bheal = true;
        }
        if(poison_score == missions[snake.level][2])
        {
            mvwprintw(snake.mission, 7, 10, "V");
            bpoison = true;
        }
        if(gate_score == missions[snake.level][3])
        {
            mvwprintw(snake.mission, 9, 10, "V");
            bgate = true;
        }
    }
    if(bheal && bgate && bpoison && blength)
        snake.clear_Stage = true;
    wrefresh(snake.mission);
}