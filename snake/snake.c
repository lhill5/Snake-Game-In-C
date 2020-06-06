#include "defs.h"

int main(int argc, char **argv) {

	struct Coordinates snake;
	InitializeSnake(&snake);
	int key;
	bool quit = false, inBounds;

	srand((unsigned char)time(NULL));
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(0);
	start_color();
	keypad(stdscr, TRUE);
	printBoard();

	key = getch();
	while (key == -1) {
		key = getch();
	}

	snake.new_direction = key;
	while (!quit) {

		inBounds = checkBounds(&snake);
		if (!inBounds) {
			getch();
			endwin();
			printf("\nGAME OVER, snake hit boundary\n");
			exit(0);
		}
		if (runIntoSnake(&snake)) {
			getch();
			endwin();
			printf("\nGAME OVER, snake collision\n");
			exit(0);
		}
		printFood(&snake);
		if (ateFood(&snake)) {
			snake.food_x = (rand() % (width-4)) + 1;
			snake.food_y = (rand() % (height-2)) + 1;
			growSnake(&snake);
			printFood(&snake);
		}
		if ((key = getch()) != -1) {
			if (key == 'p' || key == 'P') {
				key = getch();
				while (key != 'p' && key != 'P') {
					key = getch();
					printBoard();
				}
			} else {
					snake.old_direction = snake.new_direction;
					snake.new_direction = key;
			}
		}
		if (!validDirection(snake.old_direction, snake.new_direction))
			snake.new_direction = snake.old_direction;

		if (snake.new_direction == LEFT || snake.new_direction == RIGHT)
			napms(30);
		else
			napms(75);

		switch (snake.new_direction) {

			case LEFT:
				clear();
				printBoard();
				refresh();
				goLeft(&snake);
				break;

			case RIGHT:
				clear();
				printBoard();
				refresh();
				goRight(&snake);
				break;
			case UP:
				clear();
				printBoard();
				refresh();
				goUp(&snake);
				break;
			case DOWN:
				clear();
				printBoard();
				refresh();
				goDown(&snake);
				break;
			default:
				quit = true;
				getch();
				endwin();
				break;
		}
	}
  return 0;
}

void goLeft(struct Coordinates *snake) {

	int i, n, end = snake->length - 1;
	init_pair(2, COLOR_WHITE, COLOR_WHITE);
	attron(COLOR_PAIR(2));

	int *x_coordinates = malloc(snake->length * sizeof(int));
	int *y_coordinates = malloc(snake->length * sizeof(int));

	for (n = 0, i = end - 1; i >= 0; n++, i--) {
		x_coordinates[n] = snake->x[i+1];
		y_coordinates[n] = snake->y[i+1];
	}
	for (n = 0, i = end - 1; i >= 0; n++, i--) {
		snake->x[i] = x_coordinates[n];
		snake->y[i] = y_coordinates[n];
	}
	snake->x[end] -= 1;
	for (i = 0; i < snake->length; i++) {
		mvprintw(snake->y[i], snake->x[i], "  ");
	}
	free(x_coordinates);
	free(y_coordinates);
	attroff(COLOR_PAIR(2));
}

void goRight(struct Coordinates *snake) {

	int i, n, end = snake->length - 1;
	init_pair(2, COLOR_WHITE, COLOR_WHITE);
	attron(COLOR_PAIR(2));

	int *x_coordinates = malloc(snake->length * sizeof(int));
	int *y_coordinates = malloc(snake->length * sizeof(int));

	for (n = 0, i = end - 1; i >= 0; n++, i--) {
		x_coordinates[n] = snake->x[i+1];
		y_coordinates[n] = snake->y[i+1];
	}
	for (n = 0, i = end - 1; i >= 0; n++, i--) {
		snake->x[i] = x_coordinates[n];
		snake->y[i] = y_coordinates[n];
	}
	snake->x[end] += 1;
	for (i = 0; i < snake->length; i++) {
		mvprintw(snake->y[i], snake->x[i], "  ");
	}
	free(x_coordinates);
	free(y_coordinates);
	attroff(COLOR_PAIR(2));
}

void goUp(struct Coordinates *snake) {

	int i, n, end = snake->length - 1;
	init_pair(2, COLOR_WHITE, COLOR_WHITE);
	attron(COLOR_PAIR(2));

	int *x_coordinates = malloc(snake->length * sizeof(int));
	int *y_coordinates = malloc(snake->length * sizeof(int));

	for (n = 0, i = end - 1; i >= 0; n++, i--) {
		x_coordinates[n] = snake->x[i+1];
		y_coordinates[n] = snake->y[i+1];
	}
	for (n = 0, i = end - 1; i >= 0; n++, i--) {
		snake->x[i] = x_coordinates[n];
		snake->y[i] = y_coordinates[n];
	}
	snake->y[end] -= 1;
	for (i = 0; i < snake->length; i++) {
		mvprintw(snake->y[i], snake->x[i], "  ");
	}
	free(x_coordinates);
	free(y_coordinates);
	attroff(COLOR_PAIR(2));
}

void goDown(struct Coordinates *snake) {

	int i, n, end = snake->length - 1;
	init_pair(2, COLOR_WHITE, COLOR_WHITE);
	attron(COLOR_PAIR(2));

	int *x_coordinates = malloc(snake->length * sizeof(int));
	int *y_coordinates = malloc(snake->length * sizeof(int));

	for (n = 0, i = end - 1; i >= 0; n++, i--) {
		x_coordinates[n] = snake->x[i+1];
		y_coordinates[n] = snake->y[i+1];
	}
	for (n = 0, i = end - 1; i >= 0; n++, i--) {
		snake->x[i] = x_coordinates[n];
		snake->y[i] = y_coordinates[n];
	}
	snake->y[end] += 1;
	for (i = 0; i < snake->length; i++) {
		mvprintw(snake->y[i], snake->x[i], "  ");
	}
	free(x_coordinates);
	free(y_coordinates);
	attroff(COLOR_PAIR(2));
}

void InitializeSnake(struct Coordinates *snake) {

	int i;
	snake->length = 2;
	snake->old_direction = RIGHT;
	snake->new_direction = RIGHT;

	snake->food_x = (rand() % (width-4)) + 1;
	snake->food_y = (rand() % (height-2)) + 1;

	snake->x = malloc(snake->length * sizeof(int));
	snake->y = malloc(snake->length * sizeof(int));

	for (i = 0; i < snake->length; i++) {
		snake->x[i] = (width / 2) + i;
		snake->y[i] = (height / 2);
	}
}

void printBoard() {

	int row, col;
	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	attron(COLOR_PAIR(1));

	for (row = 0; row < height; row++) {
		for (col = 0; col < width; col++) {
			if (row == 0 || row == (height - 1))
				mvprintw(row, col, " ");
			else if (col == 0 || col == (width - 1))
				mvprintw(row, col," ");
		}
		printw("\n");
	}
	attroff(COLOR_PAIR(1));
}

void printFood(struct Coordinates *snake) {

	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	attron(COLOR_PAIR(1));

	mvprintw(snake->food_y, snake->food_x, "  ");
	attroff(COLOR_PAIR(1));
}

bool ateFood(struct Coordinates *snake) {
	int i;
	for (i = 0; i < snake->length; i++) {
		if (snake->x[i] == snake->food_x || snake->x[i] == snake->food_x + 1)
			if (snake->y[i] == snake->food_y)
				return true;
	}
	return false;
}

void growSnake(struct Coordinates *snake) {

	int i, length, end = snake->length;

	snake->length += 1;
	length = snake->length;
	snake->x = realloc(snake->x, length * sizeof(int));
	snake->y = realloc(snake->y, length * sizeof(int));
	if (snake->x == NULL || snake->y == NULL) {
		getch();
		endwin();
		printf("Error re-allocating memory\n");
		exit(0);
	}

	if (snake->new_direction == RIGHT) {
		snake->x[end] = snake->x[end-1] + 1;
		snake->y[end] = snake->y[end-1];
	} else if (snake->new_direction == LEFT) {
			snake->x[end] = snake->x[end-1] - 1;
			snake->y[end] = snake->y[end-1];
	} else if (snake->new_direction == UP) {
			snake->x[end] = snake->x[end-1];
			snake->y[end] = snake->y[end-1] - 1;
	} else if (snake->new_direction == DOWN) {
			snake->x[end] = snake->x[end-1];
			snake->y[end] = snake->y[end-1] + 1;
	}

	for (i = 0; i < snake->length; i++) {
		mvprintw(snake->y[i], snake->x[i], "  ");
	}
}

bool validDirection(int old_direction, int new_direction) {

	if (old_direction == LEFT && new_direction == RIGHT) {
			return false;
	} else if (old_direction == RIGHT && new_direction == LEFT) {
			return false;
	} else if (old_direction == UP && new_direction == DOWN) {
			return false;
	} else if (old_direction == DOWN && new_direction == UP) {
		return false;
	} else {
		return true;
	}
}

bool checkBounds(struct Coordinates *snake) {

	int i;
	for (i = 0; i < snake->length; i++) {
		if (snake->x[i] == 0 || snake->x[i] == width-2) {
			return false;
		} else if (snake->y[i] == 0 || snake->y[i] == height-1) {
			return false;
		}
	}
	return true;
}

bool runIntoSnake(struct Coordinates *snake) {

	int i, n;
	for (i = 0; i < snake->length - 1; i++) {
		for (n = i + 1; n < snake->length; n++) {
			if (snake->x[i] == snake->x[n])
				if (snake->y[i] == snake->y[n])
					return true;
		}
	}
	return false;
}

/*
bool vertical(struct Coordinates *snake) {

	bool vertical_snake = true;
	int i;
	for (i = 0; i < snake->length - 1; i++) {
		if (snake->x[i] != snake->x[i + 1]) {
			vertical_snake = false;
		}
	}
	return vertical_snake;
}
bool horizontal(struct Coordinates *snake) {

	bool horizontal_snake = true;
	int i;
	for (i = 0; i < snake->length - 1; i++) {
		if (snake->y[i] != snake->y[i + 1]) {
			horizontal_snake = false;
		}
	}
	return horizontal_snake;
}
*/
