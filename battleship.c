#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define ROW 10
#define COL 10
#define numb_ships 6


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

int random_ship(char array[][COL], int ship_length, char character);
void printboard(char array[][COL]);
int savefile(char array[][COL], char * x);
int shipcount(char array[][COL]);

int main (int argc, char * argv[])
{
	if (argc == 2)
	{
		printf("happy\n");
	}
	char * x;

	x = argv[1];

	srand(time(NULL));

	int number = rand()%1+10;

	printf("Size %d\n", number);
	
	char array[10][10]; //randomize row and col

	memset(array, 'X', sizeof(array));

	char character;
	int ship_length;

	//function to set structure values

	struct patrol pat;
	struct sub subm;
	struct cru crus;
	struct dest des;
	struct battle bat;
	struct carrier car;

	pat.patrol_boat = 2;
	subm.submarine = 2;
	crus.cruiser = 3;
	des.destroyer = 3;
	bat.battleship = 4;
	car.aircraft_carrier = 5;

	printf("Size of patrol boat: %d\n", pat.patrol_boat);
	printf("Size of submarine: %d\n", subm.submarine);
	printf("Size of cruiser: %d\n", crus.cruiser);
	printf("Size of destroyer: %d\n", des.destroyer);
	printf("Size of battleship: %d\n", bat.battleship);
	printf("Size of aircraft carrier: %d\n", car.aircraft_carrier);
	printf("\n");

	ship_length = pat.patrol_boat;
	character = 'P';
	while(random_ship(array, ship_length, character) != 1);

	ship_length = subm.submarine;
	character = 'S';
	while(random_ship(array, ship_length, character) != 1);

	ship_length = crus.cruiser;
	character = 'C';
	while(random_ship(array, ship_length, character) != 1);

	ship_length = des.destroyer;
	character = 'D';
	while(random_ship(array, ship_length, character) != 1);

	ship_length = bat.battleship;
	character = 'B';
	while(random_ship(array, ship_length, character) != 1);

	ship_length = car.aircraft_carrier;
	character = 'A';
	while(random_ship(array, ship_length, character) != 1);

	shipcount(array);
	printboard(array);
	savefile(array, x);
}

int shipcount(char array[][COL])
{
	int patrolboat;
	for (int j = 0; j < ROW; j++)
	{
		for (int i = 0; i < COL; i++)
		{
			if (array[j][i] == 'P')
			{
				patrolboat = 1;
				return patrolboat;
			}
		}
	}

	return 10000000;
}

int savefile(char array[][COL], char * x)
{
	FILE *fp;
	fp = fopen(x, "w+");

	for (int j = 0; j < ROW; j++)
	{
		for (int i = 0; i < COL; i++)
		{
			fprintf(fp, "%c", array[j][i]);
		}
		fprintf(fp, "\n");
	}

	fclose(fp);

	return 1;
}

void printboard(char array[][COL])
{
	int i;
	int j;

	for (j = 0; j < ROW; j++)
	{

		for (i = 0; i < COL; i++)
		{
			printf("%c ", array[j][i]);
		}
		printf("\n");		
	}
}

int random_ship(char array[][COL], int ship_length, char character)
{
	int horizantal;
	int i;

	horizantal = rand()%2;

	if (horizantal == 0)
	{
		int col_rand = rand()%10;//vertical
		int row_rand = rand()%10;

		for (i = 0; i < ship_length; i++)
		{
			if (row_rand <= 5)
			{			
				if (array[col_rand][row_rand+i] != 'X')
				{
					return 0;
				}
			}
			else
			{
				if (array[col_rand][row_rand-i] != 'X')
				{
					return 0;
				}
			}
		}

		for (int apple = 0; apple < ship_length; apple++)
		{
			if (row_rand <= 5)
			{
				array[col_rand][row_rand+apple] = character;

			}
			else
			{
				array[col_rand][row_rand-apple] = character;
			}
		}
		return 1;
	}
	else
	{
		int col_rand = rand()%10;//vertical
		int row_rand = rand()%10;

		for (i = 0; i < ship_length; i++)
		{
			if (col_rand <= 5)
			{			
				if (array[col_rand+i][row_rand] != 'X')
				{
					return 0;
				}
			}
			else
			{
				if (array[col_rand-i][row_rand] != 'X')
				{
					return 0;
				}
			}
			
		}

		for (int apples = 0; apples < ship_length; apples++)
		{
			if (col_rand <= 5)
			{
				array[col_rand+apples][row_rand] = character;
			}
			else
			{
				array[col_rand-apples][row_rand] = character;
			}
		}

		return 1;
	}
}
