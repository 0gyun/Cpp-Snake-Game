CC = g++
CCFLAGS = -std=c++11

LDLIBS = -lncursesw

OBJS = main.o Map.o kbhit.o Snake.o GameManager.o Board.o

TARGET = SnakeGame

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $^ $(LDLIBS) $(CFLAGS)
	
Map.o : Map.cpp Window.h GameSetting.h
	$(CC) $(CCFLAGS) -c $<

kbhit.o : kbhit.cpp kbhit.h
	$(CC) $(CCFLAGS) -c $<

Snake.o : Snake.cpp Map.h Window.h Position.h kbhit.h
	$(CC) $(CCFLAGS) -c $<

GameManager.o : GameManager.cpp Snake.h Map.h Window.h Position.h kbhit.h
	$(CC) $(CCFLAGS) -c $<

Board.o : Board.cpp Board.h Snake.h Missions.h Map.h Window.h Position.h kbhit.h
	$(CC) $(CCFLAGS) -c $<

main.o : main.cpp Board.h Snake.h Missions.h Map.h Window.h Position.h kbhit.h
	$(CC) $(CCFLAGS) -c $<

clear:
	rm -f $(TARGET) $(OBJS)

run :
	./$(TARGET)