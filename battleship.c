#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>


#include "battleship_header.h"

int main (int argc, char * argv[]) //int menu (char * argv[]) for file input //add save file option
{
	srand(time(NULL));

	if (argc == 2)
	{
		printf("Correct arguments given\n");
	}
	else
	{
		printf("There was an error with the commands given\n");
		exit(1);
	}
	char * x;

	int * col = malloc(sizeof(int));

	int * row = malloc(sizeof(int));

	*col = 12;

	*row = 14;

	int * shipcounter = malloc(sizeof(shipcounter));

	char ** array;

	x = argv[1];

	array = malloc((*row) * sizeof(void*));
	for (int u = 0; u < (*row); u++)
	{
		array[u] = malloc((*col) * sizeof(char));
		memset(array[u], '*', ((*col) * sizeof(char)));
	}

	ship_set(array, row, col);

	menu_actions(array, x, shipcounter, row, col);

	free(shipcounter);

	for (int freer = 0; freer < (*row); freer++)
	{
		free(array[freer]);
	}
	free(array);

	free(col);
	free(row);	
}

//menu used to ask user if they want to save file or not
int menu_actions(char ** array, char * x, int * shipcounter, int * row, int * col)
{
	while(1)
	{
		char buffer[20];

		printf("1)Save\n");
		printf("2)Quit\n");
		printf("3)Fire\n");
		printf("4)Load game board\n");
		printf("Enter your choice: ");

		fgets(buffer, 20, stdin);

		char * err;

		long choice = strtol(buffer, &err, 10);

		switch(choice)
		{
		case 1:
			if (savefile(array, x, row, col) == -1)
			{
				free_func(array, row, col, shipcounter);
				exit(1);
			}
			printf("File saved\n");
			break;
		case 2:
			printf("Quitting\n");
			free_func(array, row, col, shipcounter);
			exit(1);
		case 3:
			shipcount(array, shipcounter, row, col);
			printf("Ships left: %d\n", *shipcounter);
			if (*shipcounter <= 0)
			{
				printf("Game done\n");
				break;
			}
			printboard(array, row, col);
			hitmiss(array);
			fgetc(stdin);
			break;
		case 4:
			if (load_game(array, row, col, x) == -1)
			{
				free_func(array, row, col, shipcounter);
				exit(1);
			}
			break;
		
		default:
			printf("Invalid entry, try again\n");
		}
	}

	return 1;		
}

void free_func(char ** array, int * row, int * col, int * shipcounter)
{
	for (int freer = 0; freer < (*row); freer++)
	{
		free(array[freer]);
	}
	free(array);
	free(shipcounter);
	free(row);
	free(col);
}

int load_game(char ** array, int * row, int * col, char * x)
{
	FILE *fp = fopen(x, "r");

	if (fp == NULL)
	{
		fprintf(stderr, "You done fudged!\n");
		//fclose(fp);
		return -1;
	}

	printf("Load game board\n");

	int c;
	int count = 0;
	int column = 0;
	int n = 0;

	/*
	while(getline(&line, &len, fp) != -1)
	{
		//n++;
		//printf("Row %d\n", n);
	}

	*col = strlen(line);
	printf("Col %d\n", *col);

	free(line);
	rewind(fp);
	*/

	while(1)
	{
		c = fgetc(fp);
		
		if (feof(fp))
		{
			break;
		}

		if (c == '\n')
		{
			n++;
			column = count;
			count = 0;
		}
		else
		{
			array[n][count] = c;
			count++;
		}
	}

	*row = n+1;
	*col = column;

	printf("Row %d\n", *row);
	printf("Col %d\n", *col);

	fclose(fp);

	return 1;
}


int ship_set(char ** array, int * row, int * col)
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
	while(random_ship(array, ship_length, character, row, col) != 1);

	ship_length = subm.submarine;
	character = 'S';
	while(random_ship(array, ship_length, character, row, col) != 1);

	ship_length = crus.cruiser;
	character = 'C';
	while(random_ship(array, ship_length, character, row, col) != 1);

	ship_length = des.destroyer;
	character = 'D';
	while(random_ship(array, ship_length, character, row, col) != 1);

	ship_length = bat.battleship;
	character = 'B';
	while(random_ship(array, ship_length, character, row, col) != 1);

	ship_length = car.aircraft_carrier;
	character = 'A';
	while(random_ship(array, ship_length, character, row, col) != 1);

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
	printf("Give col number to fire at : ");
	scanf("%d", &number1);
	printf("\n");
	printf("Number: %d\n", number1);

	if (array[number][number1] != '*' && array[number][number1] != 'x' && array[number][number1] != 'm')
	{
		printf("Hit\n");
		array[number][number1] = 'x';
	}
	else if (array[number][number1] == '*')
	{
		printf("Miss\n");
		array[number][number1] = 'm';
	}
	else if (array[number][number1] == 'x')
	{
		printf("Already hit\n");
	}
	else if (array[number][number1] == 'm')
	{
		printf("Already guessed and its a miss\n");
	}
	
	return 1;
}

int shipcount(char **array, int* shipcounter, int * row, int * col)
{
	int patrolboat = 0;
	int submarine = 0;
	int cruiser = 0;
	int destroyer = 0;
	int battleship = 0;
	int carrier = 0;

	for (int j = 0; j < *row; j++)
	{
		for (int i = 0; i < *col; i++)
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

int savefile(char **array, char * x, int * row, int * col)
{
	FILE *fp;
	fp = fopen(x, "w+");

	if(fp == NULL)
	{
		fprintf(stderr, "Error saving to file\n");
		return -1;
	}



	for (int j = 0; j < *row; j++)
	{
		for (int i = 0; i < *col; i++)
		{
			fprintf(fp, "%c", array[j][i]);
		}

		if (j == ((*row)-1))
		{
			break;
		}

		fprintf(fp, "\n");
	}

	fclose(fp);

	return 1;
}

void printboard(char **array, int * row, int * col)
{
	int i;
	int j;

	for (j = 0; j < *row; j++)
	{
		for (i = 0; i < *col; i++)
		{
			printf("%c ", array[j][i]);
		}
		printf("\n");		
	}
}

int random_ship(char **array, int ship_length, char character, int * row, int * col)
{
	int horizantal;
	int i;

	horizantal = rand()%2;

	if (horizantal == 0)
	{
		int row_rand = rand()%*row;//vertical
		int col_rand = rand()%*col;
		

		for (i = 0; i < ship_length; i++)
		{
			if (col_rand <= (*col/2))
			{			
				if (array[row_rand][col_rand+i] != '*')
				{
					return 0;
				}
			}
			else
			{
				if (array[row_rand][col_rand-i] != '*')
				{
					return 0;
				}
			}
		}


	
		for (int apple = 0; apple < ship_length; apple++)
		{
			if (col_rand <= (*col/2))
			{
				array[row_rand][col_rand+apple] = character;

			}
			else
			{
				array[row_rand][col_rand-apple] = character;
			}
		}
		return 1;
	}
	else
	{
		int row_rand = rand()%*row;//vertical
		int col_rand = rand()%*col;

		for (i = 0; i < ship_length; i++)
		{
			if (row_rand <= (*row/2))
			{			
				if (array[row_rand+i][col_rand] != '*')
				{
					return 0;
				}
			}
			else
			{
				if (array[row_rand-i][col_rand] != '*')
				{
					return 0;
				}
			}
			
		}

		for (int apples = 0; apples < ship_length; apples++)
		{
			if (row_rand <= (*row/2))
			{
				array[row_rand+apples][col_rand] = character;
			}
			else
			{
				array[row_rand-apples][col_rand] = character;
			}
		}

		return 1;
	}
}
