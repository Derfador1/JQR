#ifndef battleship_header
	#define battleship_header


struct patrol {
	int patrol_boat;
};

struct sub {
	int submarine;
};

struct cru {
	int cruiser;
};

struct  dest {
	int destroyer;
};

struct battle {
	int battleship;
};

struct carrier {
	int aircraft_carrier;
};

int random_ship(char **array, int ship_length, char character);
void printboard(char **array);
int savefile(char **array, char * x);
int shipcount(char **array, int * shipcounter);
int hitmiss(char ** array);
int ship_set(char ** array);
int menu_actions(char ** array, char * x, int * shipcounter);

#endif
