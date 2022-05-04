#ifndef __BOARD__
#define __BOARD__

#include "Snake.h"
#include "Missions.h"

struct Board : public Snake, public Missions
{
    int snake_length_score = 0, max_snake_length_score = 0, heal_score = 0, poison_score = 0, gate_score = 0;
    bool blength = false, bheal = false, bpoison = false, bgate = false;
    Board(Snake& s);
    void update_boards(Snake& s);
};

#endif