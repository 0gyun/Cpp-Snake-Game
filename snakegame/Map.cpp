#include "Map.h"

void Map::draw_map(){
    for(int i = 0; i < map_list[level].size(); i++){
        for(int j = 0; j < map_list[level][i].size(); j++){
            if(map_list[level][i][j] == WALL || map_list[level][i][j] == IMMUNE_WALL)
                mvwprintw(game, i, j, "*");
            else if(map_list[level][i][j] == SNAKE_HEAD)
                mvwprintw(game, i, j, "O");
            else if(map_list[level][i][j] == SNAKE_BODY)
                mvwprintw(game, i, j, "X");
            else if(map_list[level][i][j] == GATE)
                mvwprintw(game, i, j, "#");
            else if(map_list[level][i][j] == HEAL_ITEM)
                mvwprintw(game, i, j, "H");
            else if(map_list[level][i][j] == POSION_ITEM)
                mvwprintw(game, i, j, "P");
            else if(map_list[level][i][j] == EMPTY)
                mvwprintw(game, i, j, " ");
        }
    }
}