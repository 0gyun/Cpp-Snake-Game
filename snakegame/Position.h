#ifndef __POSITION__
#define __POSITION__


struct Position{
    int y, x;
    Position(){};
    Position(int x, int y):x(x), y(y){};
    bool operator==(const Position& a){
        return (a.x == x && a.y == y);
    }
};

#endif