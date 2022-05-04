#ifndef __SNAKE__
#define __SNAKE__

#include "Map.h"
#include "kbhit.h"
#include "Position.h"
#include <ctime>
#include <deque>

struct Gate:public Position, public Map
{
    std::pair<Position, Position> gates;
    Position entrance, exit;
    std::vector<Position> walls;
    bool gate_appear = false;
    Gate(){};
    void make_gate();
};


struct Snake : public Gate
{
    std::deque<Position> snake;
    Position poop;
    Position exit_gate;
    time_t no_gate_time;
    char direction;
    int now_len, max_len, heal_num = 0, poison_num = 0, gate_num = 0;
    bool clear_Stage = false, in_gate = false;

    Snake(){clear_Stage = false; max_len = 3; now_len = 3;}
    void init_snake();
    void get_heal();
    void get_poison();
    void gate_in();
    void moving();
    void die();
};


#endif