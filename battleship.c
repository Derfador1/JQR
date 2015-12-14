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


int main (void)
{
	srand(time(NULL));

	int x = rand()%1+10;

	printf("Size %d\n", x);

	char array[10][10]; //randomize row and col

	memset(array, '0', sizeof(array));

	int i = 0;
	int j = 0;

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

	//function to randomize ship placement

	int horizantal;

	//row_rand = rand()%10;
	//col_rand = rand()%10;

	for(j = 0; j < numb_ships; j++)
	{
		horizantal = rand() % 2;
		if(horizantal == 0)
		{
			int row = rand()%10;
			int col = rand()%8;	
			if (array[row][col] != 1 && array[row][col + 1] != 1 && array[row][col + 2] != 1)
			{
				for (i = 0; i < 3; i++)
				{
					array[row][col+i] = '1';
					if (array[row][col+i] == '1')
					{
						printf("overlap\n");
						break;
					}
					//array[row_rand][col_rand] = '1';
				}
			}
		}
		else
		{
			int row = rand()%8;
			int col = rand()%10;	
			if (array[row][col] != 1 && array[row + 1][col] != 1 && array[row + 3][col] != 1)
			{
				for (i = 0; i < 3; i++)
				{
					array[row+i][col] = '1';
					//array[row_rand][col_rand] = '1';
				}
			}
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
