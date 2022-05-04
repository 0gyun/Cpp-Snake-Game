#include "GameManager.h"
#include <ctime>

Game::Game(){
    srand(time(NULL));
    item_last_create_time = time(NULL);
}

void Game::make_wall_vector(){
    walls.clear();
    for(int y = 0; y < map_list[level].size(); y++){
        for(int x = 0; x < map_list[level][y].size(); x++){
            if(map_list[level][y][x] == WALL && map_list[level][y][x] != IMMUNE_WALL)
                walls.push_back(Position(x, y));
        }
    }
}

void Game::delete_item(){
    time_t now = time(NULL);
    if(item_list.empty()) return;
    item = item_list.front();
    if((now - item_last_create_time) >= 5){
        item_list.pop_front();
        map_list[level][item.first.y][item.first.x] = EMPTY;
    }
}

void Game::create_item(){
    time_t start = time(NULL);
    if(item_list.size() < 3){
        if((start - item_last_create_time) >= 1){
            while(1){
                int tmp_x = rand() % GAME_WIDTH;
                int tmp_y = rand() % GAME_HEIGHT;
                if(map_list[level][tmp_y][tmp_x] == EMPTY){
                    item_list.push_back(std::pair<Position, clock_t>(Position(tmp_x, tmp_y), start));
                    map_list[level][tmp_y][tmp_x] = rand()%2 + HEAL_ITEM;
                    break;
                }
            }
            item_last_create_time = start;
        }
    }
}
