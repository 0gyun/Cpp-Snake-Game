#include "Snake.h"
#include "Board.h"
#include "GameManager.h"
#include <unistd.h>
using namespace std;

int main(){
    int level = 0;
    while(1)
    {
        Game snake;
        snake.set_level(level++);
        Board board(snake);
        snake.init_snake();
        snake.make_wall_vector();
        while(!snake.clear_Stage){
            snake.moving();
            board.update_boards(snake);
            snake.create_item();
            snake.delete_item();
            usleep(200000);
            if(!snake.gate_appear){
                time_t gate_check = time(NULL);
                if((gate_check - snake.no_gate_time)>= 5){
                    snake.make_gate();
                }
            }
            if(snake.direction == 'q' || snake.direction == 'o')
            {
                getch();
                snake.end_Game();
                return 0;
            }
        }
        snake.stage_clear_window(level);
        if(level == snake.num_of_maps){
            snake.end_Game();
            break;
        }
    }
}