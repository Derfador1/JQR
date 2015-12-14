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

int random_ship(char array[][COL], int ship_length, char x);

int main (void)
{
	srand(time(NULL));

	int x = rand()%1+10;

	printf("Size %d\n", x);
	
	char array[10][10]; //randomize row and col

	memset(array, '0', sizeof(array));

	int i = 0;
	int j = 0;
	char character;
	int ship_length;
	int count = 0;

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

	while(1)
	{
		if (count == 0)
		{
			ship_length = pat.patrol_boat;
			character = 'P';
			random_ship(array, ship_length, character);
			count++;
		}
		else if (count == 1)
		{
			ship_length = subm.submarine;
			character = 'S';
			random_ship(array, ship_length, character);
			count++;
		}
		else if (count == 2)
		{
			ship_length = crus.cruiser;
			character = 'C';
			random_ship(array, ship_length, character);
			count++;
		}
		else if (count == 3)
		{
			ship_length = des.destroyer;
			character = 'D';
			random_ship(array, ship_length, character);
			count++;
		}
		else if (count == 4)
		{
			ship_length = bat.battleship;
			character = 'B';
			random_ship(array, ship_length, character);
			count++;
		}
		else if (count == 5)
		{
			ship_length = car.aircraft_carrier;
			character = 'A';
			random_ship(array, ship_length, character);
			count++;
		}
		else
		{
			break;
		}
	}

	//function to print out grid

	for (j = 0; j < ROW; j++)
	{

		for (i = 0; i < COL; i++)
		{
			printf("%c ", array[j][i]);

		
			if ((i % 9 == 0) && (i != 0))
			{
				//printf("end");
			}
			

		}

		printf("\n");		
	}
}

int random_ship(char array[][COL], int ship_length, char x)
{
	int horizantal;
	int overlap;
	int j;
	int i;

	horizantal = rand()%2;

	printf("Horizantal %d\n", horizantal);

	if (horizantal == 0)
	{
		int col_rand = rand()%10;//vertical
		int row_rand = rand()%10;

		for (j = 0; j < col_rand; j++)
		{
			for (i = 0; i < ship_length; i++)
			{
				if ((array[col_rand][row_rand+i] == 'P') || (array[col_rand][row_rand+i] == 'S') || (array[col_rand][row_rand+i] == 'C') || (array[col_rand][row_rand+i] == 'D') || (array[col_rand][row_rand+i] == 'B') || (array[col_rand][row_rand+i] == 'A'))
				{
					printf("OVERLAP 1\n");
					overlap = 1;
					break;
				}
				else
				{

				}
				/*
				else
				{
					if (row_rand <= ship_length)
					{
						array[col_rand][row_rand+i] = x;
					}
					else
					{
						array[col_rand][row_rand-i] = x;
					}
				}
				*/
			}
		
			if (overlap == 1)
			{	
				col_rand = rand()%10;
				row_rand = rand()%10;
				break;
			}
			else
			{

				for (int plea = 0; plea < row_rand; plea++)
				{
					for (int apple = 0; apple < ship_length; apple++)
					{
						if (row_rand <= 5)
						{
							array[col_rand][row_rand+apple] = x;
						}
						else
						{
							array[col_rand][row_rand-apple] = x;
						}
					}
				}
			}
			break;
		}
	}
	else
	{
		int col_rand = rand()%10;//vertical
		int row_rand = rand()%10;

		for (j = 0; j < row_rand; j++)
		{
			for (i = 0; i < ship_length; i++)
			{
				if ((array[col_rand+i][row_rand] == 'P') || (array[col_rand+i][row_rand] == 'S') || (array[col_rand+i][row_rand] == 'C') || (array[col_rand+i][row_rand] == 'D') || (array[col_rand+i][row_rand] == 'B') || (array[col_rand+i][row_rand] == 'A'))
				{
					printf("OVERLAP 2\n");
					overlap = 1;
					break;
				}
				else
				{
					//
				}
				/*
				else
				{
					if (col_rand <= 5)
					{
						array[col_rand+i][row_rand] = x;
					}
					else
					{
						array[col_rand-i][row_rand] = x;
					}
				}
				*/
			}
		
			if (overlap == 1)
			{	
				col_rand = rand()%10;
				row_rand = rand()%10;
				break;
			}

			else
			{
				for (int poop = 0; poop < row_rand; poop++)
				{
					for (int more = 0; more < ship_length; more++)
					{
						if (col_rand <= 5)
						{
							array[col_rand+more][row_rand] = x;
						}
						else
						{
							array[col_rand-more][row_rand] = x;
						}
					}
				}
			}
			break;
		}
	}
	
	return 1;
}
