#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define ROW 10
#define COL 10


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
int menu(int * c);

int main (int argc, char * argv[])
{
	if (argc == 2)
	{
		printf("Run check for argument value\n");
	}
	char * x;

	x = argv[1];

	srand(time(NULL));

	char ** array;
	array = malloc((ROW + 1) * sizeof(void*));
	for (int u = 0; u < ROW + 1; u++)
	{
		array[u] = malloc((COL + 1)*sizeof(char));
		memset(array[u], 'X', (COL + 1)*sizeof(char));
	}

	int * shipcounter = malloc(sizeof(shipcounter));
	int * c = malloc(sizeof(c));

	*c = 0;

	ship_set(array);

	while(1)
	{
		if (menu(c) == 0)
		{
			break;
		}
		else
		{
			//printf("Value: %d\n", *c);
		}

		if (*c == 1)
		{
			savefile(array, x);
			printf("File saved\n");
		}
		else if (*c == 2)
		{
			printf("Quitting\n");
			for (int freer = 0; freer < (ROW + 1); freer++)
			{
				free(array[freer]);
			}
			free(array);

			free(shipcounter);
			free(c);
			exit(1);
		}
		else if (*c == 3)
		{
			shipcount(array, shipcounter);
			printf("Ships left: %d\n", *shipcounter);
			if (*shipcounter <= 0)
			{
				printf("Game done\n");
				break;
			}
			printboard(array);
			hitmiss(array);
		}
		else if ((*c < 0) || (*c > 3))
		{	
			printf("Error\n");
			//break;
		}
	}

	free(shipcounter);
	free(c);

	for (int freer = 0; freer < (ROW + 1); freer++)
	{
		free(array[freer]);
	}
	free(array);
}

//menu used to ask user if they want to save file or not
int menu(int * c)
{
	int d;
	printf("1)Save\n");
	printf("2)Quit\n");
	printf("3)Fire\n");
	printf("Enter your choice: ");
	if (scanf("%d", &d) == 1)
	{
		*c = d;
	}
	else
	{
		return 0;
	}

	return 1;		
}

int ship_set(char ** array)
{
	char character;
	int ship_length;

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

	/*
	printf("Size of patrol boat: %d\n", pat.patrol_boat);
	printf("Size of submarine: %d\n", subm.submarine);
	printf("Size of cruiser: %d\n", crus.cruiser);
	printf("Size of destroyer: %d\n", des.destroyer);
	printf("Size of battleship: %d\n", bat.battleship);
	printf("Size of aircraft carrier: %d\n", car.aircraft_carrier);
	printf("\n");
	*/

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

	return 1;
}

int hitmiss(char ** array)
{
	int number;
	printf("Give row number to fire at : ");
	scanf("%d", &number);
	printf("\n");
	printf("Number: %d\n", number);

	int number1;
	printf("Give column number to fire at : ");
	scanf("%d", &number1);
	printf("\n");
	printf("Number: %d\n", number1);

	if (array[number][number1] != 'X' && array[number][number1] != '*')
	{
		printf("Hit\n");
		array[number][number1] = '*';
	}
	else if (array[number][number1] == '*')
	{
		printf("Already hit\n");
	}
	else
	{
		printf("Miss\n");
	}
	
	return 1;
}

int shipcount(char **array, int* shipcounter)
{
	int patrolboat = 0;
	int submarine = 0;
	int cruiser = 0;
	int destroyer = 0;
	int battleship = 0;
	int carrier = 0;

	for (int j = 0; j < ROW; j++)
	{
		for (int i = 0; i < COL; i++)
		{
			if (array[j][i] == 'P')
			{
				patrolboat = 1;
			}
			else if (array[j][i] == 'S')
			{
				submarine = 1;
			}
			else if (array[j][i] == 'C')
			{
				cruiser = 1;
			}
			else if (array[j][i] == 'D')
			{
				destroyer = 1;
			}
			else if (array[j][i] == 'B')
			{
				battleship = 1;
			}
			else if (array[j][i] == 'A')
			{
				carrier = 1;
			}
		}
	}

	*shipcounter = patrolboat + submarine + cruiser + destroyer + battleship + carrier;

	return 1;
}

int savefile(char **array, char * x)
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

void printboard(char **array)
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

int random_ship(char **array, int ship_length, char character)
{
	int horizantal;
	int i;

	horizantal = rand()%2;

	if (horizantal == 0)
	{
		int col_rand = rand()%COL;//vertical
		int row_rand = rand()%ROW;


		for (i = 0; i < ship_length; i++)
		{
			if (row_rand <= (ROW/2))
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
			if (row_rand <= (ROW/2))
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
		int col_rand = rand()%COL;//vertical
		int row_rand = rand()%ROW;

		for (i = 0; i < ship_length; i++)
		{
			if (col_rand <= (COL/2))
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
			if (col_rand <= (COL/2))
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
