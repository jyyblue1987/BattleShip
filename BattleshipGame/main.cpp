#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 5
#define MAX_COLS 6

int battle_state[MAX_ROWS][MAX_COLS];

// state
//			0: no ship, no hit - ' ' 
//			1:	  ship, no hit - 'o'
//			2: no ship,    hit - 'x'
//			3:    ship,    hit - '#'

void print_numbers(int n)
{
	printf("  |");
	for(int j = 0; j < n; j++)
		printf(" %d |", (j + 1));

	printf("\n");
}
void print_edge_row(int n)
{
	printf("---");
	for(int j = 0; j < n; j++)
		printf("----");

	printf("\n");
}

void show_buttle_field(int m, int n)
{
	int i = 0, j = 0;
	
	print_numbers(n);
	print_edge_row(n);
	for(i = 0; i < m; i++)
	{		
		printf("%d |", (i + 1));
		for(j = 0; j < n; j++)
		{
			char c = ' ';
			int state = battle_state[i][j];
			if( state == 0 )	// not drop
				c = ' ';
			else if( state == 1 )	// not drop
				c = 'o';
			else if( state == 2 )	// not hit
				c = 'x';
			else
				c = '#';
			
			printf(" %c |", c);
		}
		printf("\n");
		print_edge_row(n);
	}

}

int is_all_ships_destroyed(int m, int n, int ship_count)
{
	int count = 0;
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			int state = battle_state[i][j];
			if(state == 3)
				count++;
		}
	}

	return ship_count == count ? 1 : 0;
}

void init_battle_state(int m, int n)
{
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			int state = battle_state[i][j];
			if( state == 3 )
				battle_state[i][j] = 1;
			if( state == 2)
				battle_state[i][j] = 0;
		}
	}
}

int main()
{
	printf("=========== Start Battleship Game ===================\n");

	int n, m = 0;
	int error_flag = 0;
	do 
	{
		if( error_flag == 1 )
			printf("Maximum allowed size is 5 rows and 6 columns\n");

		printf("Please input the dimension of battlefield: ");
		scanf("%d %d", &m, &n);	

		error_flag = 1;
	}
	while(m <= 0 || m > 5 || n <= 0 || n > 6  );

	printf("How many ships of size 1 should be placed in the battlefield: ");
	int ship_count = 0;
	scanf("%d", &ship_count);

	// initialize grid state
	int i = 0, j = 0;
	for(i = 0; i < MAX_ROWS; i++)
		for(j = 0; j < MAX_COLS; j++)
			battle_state[i][j] = 0;

	int x = 0, y = 0;
	for(int i = 0; i < ship_count; i++)
	{		
		do 
		{
			y = rand() % m;
			x = rand() % n;			
		} while(battle_state[y][x] == 1);
		
		battle_state[y][x] = 1;
	}

	

	printf("how many missiles do you want to shoot: ");
	int missiles_count = 0;
	scanf("%d", &missiles_count);

	
	int try_count = 0;
	while(try_count < 5)
	{
		printf("\n=======Round %d========\n\n", try_count + 1);
		init_battle_state(m, n);

		int try_shoot_count = 0;

		while(is_all_ships_destroyed(m, n, ship_count) == 0 && 
			try_shoot_count < missiles_count )
		{
			printf("Please provide the coordinates of the location where you want to shoot: ");
			scanf("%d %d", &y, &x);

			if(x < 1 || x > n || y < 1 || y > m )
			{
				printf("Maximum allowed coordinate is %d x and %d y\n", n, m);
				continue;
			}

			int state = battle_state[y - 1][x - 1];
			if( state == 1 || state == 3 )
			{
				battle_state[y - 1][x - 1] = 3;
				printf("hit\n");
			}
			else if( state == 0 )
			{
				battle_state[y - 1][x - 1] = 2;
				printf("not hit\n");
			}

			show_buttle_field(m, n);

			try_shoot_count++;
		}

		if( is_all_ships_destroyed(m, n, ship_count) == 1 )
			printf("\nYou won in this round\n");
		else
			printf("\nYou loose in this round\n");

		try_count++;
	}
	

	

	return 0;
}