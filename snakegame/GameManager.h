#ifndef __ITEM__
#define __ITEM__

#include "Snake.h"
#include <cstdlib>
#include <list>

struct Game:public Snake
{
    std::pair<Position, time_t> item;
    std::list<std::pair<Position, time_t>> item_list;
    time_t item_last_create_time;
    Game();
    void make_wall_vector();
    void create_item();
    void delete_item();

};



#endif