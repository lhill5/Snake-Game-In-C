#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define height 24
#define width 80

#define LEFT KEY_LEFT
#define RIGHT KEY_RIGHT
#define UP KEY_UP
#define DOWN KEY_DOWN

struct Coordinates {
	int length;
	char *body;
	int old_direction;
	int new_direction;
	int food_x;
	int food_y;
	int *x;
	int *y;
};

void printBoard(), player();
void goLeft(struct Coordinates *snake);
void goRight(struct Coordinates *snake);
void goUp(struct Coordinates *snake);
void goDown(struct Coordinates *snake);
char *getSnake(struct Coordinates *snake);
void InitializeSnake(struct Coordinates *snake);
bool vertical(struct Coordinates *snake);
bool horizontal(struct Coordinates *snake);
bool validDirection(int old_direction, int new_direction);
bool checkBounds(struct Coordinates *snake);
void printFood(struct Coordinates *snake);
bool ateFood(struct Coordinates *snake);
void growSnake(struct Coordinates *snake);
bool runIntoSnake(struct Coordinates *snake);
