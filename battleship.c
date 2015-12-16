#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define ROW 10
#define COL 10

#include "battleship_header.h"

int main (int argc, char * argv[]) //int menu (char * argv[]) for file input
{
	srand(time(NULL));

	if (argc == 2)
	{
		printf("Run check for argument value\n");
	}
	char * x;

	int * shipcounter = malloc(sizeof(shipcounter));

	char ** array;

	x = argv[1];

	array = malloc((ROW + 1) * sizeof(void*));
	for (int u = 0; u < ROW + 1; u++)
	{
		array[u] = malloc((COL + 1)*sizeof(char));
		memset(array[u], '*', (COL + 1)*sizeof(char));
	}


	ship_set(array);

	menu_actions(array, x, shipcounter);

	free(shipcounter);

	for (int freer = 0; freer < (ROW + 1); freer++)
	{
		free(array[freer]);
	}
	free(array);
}

//menu used to ask user if they want to save file or not
int menu_actions(char ** array, char * x, int * shipcounter)
{
	while(1)
	{
		char buffer[20];

		printf("1)Save\n");
		printf("2)Quit\n");
		printf("3)Fire\n");
		printf("4)Load game board");
		printf("Enter your choice: ");

		fgets(buffer, 20, stdin);

		char * err;

		long choice = strtol(buffer, &err, 10);

		switch(choice)
		{
		case 1:
			savefile(array, x);
			printf("File saved\n");
			break;
		case 2:
			printf("Quitting\n");
			for (int freer = 0; freer < (ROW + 1); freer++)
			{
				free(array[freer]);
			}
			free(array);

			free(shipcounter);
			exit(1);
		case 3:
			shipcount(array, shipcounter);
			printf("Ships left: %d\n", *shipcounter);
			if (*shipcounter <= 0)
			{
				printf("Game done\n");
				break;
			}
			printboard(array);
			hitmiss(array);
			fgetc(stdin);
			break;
		case 4:
			printf("Load game board\n");
			break;
		
		default:
			printf("Invalid entry, try again\n");
		}
	}

	return 1;		
}

/*
int load_game(char ** array)
{
	
}
*/

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

	if (array[number][number1] != '*' && array[number][number1] != 'x')
	{
		printf("Hit\n");
		array[number][number1] = 'x';
	}
	else if (array[number][number1] == 'x')
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
				if (array[col_rand][row_rand+i] != '*')
				{
					return 0;
				}
			}
			else
			{
				if (array[col_rand][row_rand-i] != '*')
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
				if (array[col_rand+i][row_rand] != '*')
				{
					return 0;
				}
			}
			else
			{
				if (array[col_rand-i][row_rand] != '*')
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
