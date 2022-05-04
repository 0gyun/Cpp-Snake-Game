#include "Snake.h"
#include<vector>

void Gate::make_gate(){
    Position gate1, gate2, tmp;

    int i = rand() % walls.size();
    tmp = walls[i];
    walls[i] = walls.back();
    gate1 = tmp;
    
    gate2 = walls[rand() % (walls.size()-1)];
    gates = std::make_pair(gate1, gate2);
    map_list[level][gate1.y][gate1.x] = GATE;
    map_list[level][gate2.y][gate2.x] = GATE;
    gate_appear = true;
}

void Snake::init_snake()
{
    for(int i = 3; i >= 1; i--)
    {
        snake.push_back(Position(i+1,1));
        map_list[level][1][1+i] = (i==3) ? SNAKE_HEAD : SNAKE_BODY;
    }
    direction = 'r';
    gate_num = heal_num = poison_num = 0;
    no_gate_time = time(NULL);
    draw_map();
    wrefresh(game);
}

void Snake::get_heal()
{
    snake.push_back(poop);
    mvwprintw(game, poop.y, poop.x, "X");
    ++now_len;
    ++heal_num;
    if(max_len < now_len)
        max_len = now_len;
}

void Snake::get_poison()
{
    poop = *snake.rbegin();
    snake.pop_back();
    wmove(game, poop.y, poop.x);
    waddch(game, ' ');
    map_list[level][poop.y][poop.x] = EMPTY;
    now_len--;
    ++poison_num;
}

void Snake::die()
{
    draw_map();
    mvwprintw(game, GAME_HEIGHT/2, GAME_WIDTH/2-5, "<GAME OVER>");
    direction = 'o';
    wrefresh(game);
}



void Snake::moving(){
    while(kbhit())
    {    
        int key = wgetch(game);
        switch (key)
        {
        case KEY_LEFT:
            if(direction == 'r')
            {
                die();
                return;
            }
            direction = 'l';
            break;

        case KEY_RIGHT:
            if(direction == 'l')
            {
                die();
                return;
            }
            direction = 'r';
            break;

        case KEY_UP:
            if(direction == 'd')
            {
                die();
                return;
            }
            direction = 'u';
            break;

        case KEY_DOWN:
            if(direction == 'u')
            {
                die();
                return;
            }
            direction = 'd';
            break;
        
        case 113:
        case 81:
            direction = 'q';
            mvwprintw(game, GAME_HEIGHT/2, GAME_WIDTH/2-5, "<GAME QUIT>");
            wrefresh(game);
            return;

        default:
            break;
        }
    }

    // 이동
    if(direction == 'r')
        snake.push_front(Position(snake[0].x+1, snake[0].y));
    else if(direction == 'u')
        snake.push_front(Position(snake[0].x, snake[0].y-1));
    else if(direction == 'l')
        snake.push_front(Position(snake[0].x-1, snake[0].y));
    else if(direction == 'd')
        snake.push_front(Position(snake[0].x, snake[0].y+1));
    
    
    // 이동을 표시
    if(map_list[level][snake[0].y][snake[0].x] == WALL || map_list[level][snake[0].y][snake[0].x] == SNAKE_BODY || map_list[level][snake[0].y][snake[0].x] == IMMUNE_WALL)
    {
        die();
        return;
    }
    else if(map_list[level][snake[0].y][snake[0].x] == HEAL_ITEM)
    {
        get_heal();
    }
    else if(map_list[level][snake[0].y][snake[0].x] == POSION_ITEM)
    {
        if(now_len -1 < 3){
            die();
            return;
        }
        else
            get_poison();
    }
    else if(map_list[level][snake[0].y][snake[0].x] == GATE){
        entrance = snake[0];
        snake.pop_front();
        gate_in();
    }

    // 머리랑 몸부분 정리
    map_list[level][snake[0].y][snake[0].x] = SNAKE_HEAD;
    map_list[level][snake[1].y][snake[1].x] = SNAKE_BODY;
    poop = *snake.rbegin();
    snake.pop_back();
    map_list[level][poop.y][poop.x] = EMPTY;
    wmove(game, poop.y, poop.x);
    waddch(game, ' ');

    // gate 닫기
    if(poop == exit_gate && in_gate == true){
        map_list[level][gates.first.y][gates.first.x] = WALL;
        map_list[level][gates.second.y][gates.second.x] = WALL;
        gate_appear = false;
        no_gate_time = time(NULL);
        gate_num++;
        in_gate = false;
    }

    draw_map();
    wrefresh(game);
}

void Snake::gate_in(){
    exit = (gates.first == entrance) ? gates.second : gates.first;
    exit_gate.x = exit.x; exit_gate.y = exit.y;
    in_gate = true;
    if(exit.y == 0 || exit.y == GAME_HEIGHT-1)
    {
        if(exit.y == 0){
            direction = 'd';
            exit_gate.y++;
        }
        else{
            direction = 'u';
            exit_gate.y--;
        }
    }
    else if(exit.x == 0 || exit.x == GAME_WIDTH-1)
    {
        if(exit.x == 0){
            direction = 'r';
            exit_gate.x++;
        }
        else{
            direction = 'l';
            exit_gate.x--;
        }
    }
    else{
        int up = map_list[level][exit.y-1][exit.x];
        int down = map_list[level][exit.y+1][exit.x];
        int left = map_list[level][exit.y][exit.x-1];
        int right = map_list[level][exit.y][exit.x+1];
        switch (direction)
        {
        case 'u':
            if(up == 0){exit_gate.y--;}
            else if(right == 0){exit_gate.x++; direction = 'r';}
            else if(left == 0){exit_gate.x--; direction = 'l';}
            else if(down == 0){exit_gate.y++; direction = 'd';}
            break;
        
        case 'r':
            if(right == 0){exit_gate.x++;}
            else if(down == 0){exit_gate.y++; direction = 'd';}
            else if(up == 0){exit_gate.y--; direction = 'u';}
            else if(left == 0){exit_gate.x--; direction = 'l';}
            break;

        case 'l':
            if(left == 0){exit_gate.x--;}
            else if(up == 0){exit_gate.y--; direction = 'u';}
            else if(down == 0){exit_gate.y++; direction = 'd';}
            else if(right == 0){exit_gate.x++; direction = 'r';}
            break;

        case 'd':
            if(down == 0){exit_gate.y++;}
            else if(left == 0){exit_gate.x--; direction = 'l';}
            else if(right == 0){exit_gate.x++; direction = 'r';}
            else if(up == 0){exit_gate.y--; direction = 'u';}
            break;


        default:
            break;
        }
    }
    snake.push_front(exit_gate);
}
