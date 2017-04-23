#include <stdio.h>
#define GO_UP 1
#define GO_DN 2

#define MAX_FLOOR 4

int floor_button[MAX_FLOOR + 1] = {
	0, 1, 2, 1 + 2, 2
};

char *button_status_string[4] = {
	"NULL",
	"UP",
	"DOWN",
	"UP&DOWN"
};

int is_button_up(int status);
int is_button_down(int status);
void print_floor_button_status(int *floor_button, int max_floor);
int check_nearest_floor_button_up(int *floor_button, int currFloor, int max_floor);
int check_nearest_floor_button_down(int *floor_button, int currFloor,
   int max_floor);
int check_farest_floor_button_down(int *floor_button, int currFloor, int max_floor);
int check_farest_floor_button_up(int *floor_button, int currFloor, int max_floor);
int scan_floor(int *floor_button, int currFloor, int direction, int max_floor);

int main(void)
{
	int currFloor;
	int nextFloor;
	int direction;

	print_floor_button_status(floor_button, MAX_FLOOR);
	nextFloor = check_nearest_floor_button_up(floor_button, currFloor =
	   3, MAX_FLOOR);

	fprintf(stdout, "currFloor=%d\n", currFloor);
	fprintf(stdout, "nearest floor up: %d\n", nextFloor);

	nextFloor = check_nearest_floor_button_down(floor_button, currFloor, MAX_FLOOR);
	fprintf(stdout, "nearest floor down: %d\n", nextFloor);

	nextFloor = check_farest_floor_button_down(floor_button, currFloor, MAX_FLOOR);
	fprintf(stdout, "farest floor down: %d\n", nextFloor);

	nextFloor = check_farest_floor_button_up(floor_button, currFloor, MAX_FLOOR);
	fprintf(stdout, "farest floor up: %d\n", nextFloor);

	direction = GO_UP;
	fprintf(stdout, "%d objFloor=%d\n", direction, scan_floor(floor_button,
		  currFloor, direction, MAX_FLOOR));

	direction = GO_DN;
	fprintf(stdout, "%d objFloor=%d\n", direction, scan_floor(floor_button,
		  currFloor, direction, MAX_FLOOR));
}

int scan_floor(int *floor_button, int currFloor, int direction, int max_floor)
{
	int floor;

	if (direction == GO_UP) {
		floor = check_nearest_floor_button_up(floor_button, currFloor, max_floor);
		if (floor != 0)
			return floor;

		floor = check_farest_floor_button_down(floor_button, currFloor, max_floor);
		if (floor != 0)
			return floor;

	}
	else if (direction == GO_DN) {
		floor = check_nearest_floor_button_down(floor_button, currFloor, max_floor);
		if (floor != 0)
			return floor;

		floor = check_farest_floor_button_up(floor_button, currFloor, max_floor);
		if (floor != 0)
			return floor;
	}

	return 0;
}

int is_button_up(int status)
{
	return (status & 0x01) == 0 ? 0 : 1;
}

int is_button_down(int status)
{
	return (status & 0x02) == 0 ? 0 : 1;
}

int check_nearest_floor_button_up(int *floor_button, int currFloor, int max_floor)
{
	int i;

	for (i = currFloor + 1; i <= max_floor; i++) {
		if (is_button_up(floor_button[i]) == 1)
			return i;
	}

	return 0;
}

int check_nearest_floor_button_down(int *floor_button, int currFloor, int max_floor)
{
	int i;

	for (i = currFloor - 1; i >= 1; i--) {
		if (is_button_down(floor_button[i]) == 1)
			return i;
	}

	return 0;
}

int check_farest_floor_button_down(int *floor_button, int currFloor, int max_floor)
{
	int i;

	for (i = max_floor; i > currFloor; i--) {
		if (is_button_down(floor_button[i]) == 1)
			return i;
	}

	return 0;
}

int check_farest_floor_button_up(int *floor_button, int currFloor, int max_floor)
{
	int i;

	for (i = 1; i < currFloor; i++) {
		if (is_button_up(floor_button[i]) == 1)
			return i;
	}

	return 0;
}

void print_floor_button_status(int *floor_button, int max_floor)
{
	int i;

	fprintf(stdout, "floor button...\n");
	for (i = 1; i <= max_floor; i++) {
		fprintf(stdout, "%d %s\n", i, button_status_string[floor_button[i]]);
	}
	fprintf(stdout, "\n");

}
