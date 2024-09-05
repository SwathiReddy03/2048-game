#include <iostream>
#include <ctime>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <conio.h>

using namespace std;

int press_enter;
int random_index(int);

class Game;

class Game_AI
{

	int response;
	int apocalypse;
	char control;

public:
	char name[25];
	int max;
	int win;
	int plus;
	int score;
	int grid[4][4];
	int bgrid[4][4];

	Game_AI() : score(0), plus(0), win(2048), max(0), response(0), apocalypse(1) {}

	void logic_flow(Game *);
	void game_end_check(Game *);
	void key_press();
	void first_menu(Game *);
	void start_grid();
	void update_grid();
	void fill_space();
	void spawn();
	void find_greatest_tile();
	void backup_grid();
	void undo();

	int full();
	int block_moves();
};

class Game : public Game_AI
{
	char option;

public:
	void display_grid();
	void display_help_screen();
	void display_win_screen();
	void display_loser_screen();
	char display_try_again_screen(int);
	void register_score();
	void reset_score();
	void show_score();
};

int main()
{
	system("cls");
	printf("\n");
	printf("\t\t\tOBJECT ORIENTED PROGRAMMING PROJECT\n");
	printf("\t\t\t\t\t2048 GAME\n");
	printf("\n\t\t\t________");
	printf("\n\t\t\t____");
	printf("\n\t\t\tGame developed by Swathi \n");
	printf("\n\t\t\tEnter S to start the game\n");
	printf("\n\t\t\tEnter Q to start the quit\n");
	printf("\n\t\t\tEnter H for help \n\n\n\n");

	Game exec;
	exec.key_press();
	srand(time(NULL));

	exec.first_menu(&exec);

	return 0;
}

// to take in a character that will be used in various switch-case conditions later on
void Game_AI::key_press()
{
	system("stty raw");
	cin >> control;
	system("stty cooked");
}

//The main menu and its basic functionings are displayed and carried out through this function
void Game_AI::first_menu(Game *execute)
{

	switch (control)
	{

	case 's':
	case 'S':
		system("cls");
		cout << "\n\n\n\n\n\n\t\t\t\tPlease enter your name \n\t\t\t\t\t";
		cin >> name;
		execute->start_grid();
		while (1)
		{
			execute->display_grid();
			execute->key_press();
			execute->logic_flow(execute);
			execute->game_end_check(execute);
		};
		break;

	case 'q':
	case 'Q':
		cout << "Thank you for playing!" << endl
			 << endl
			 << endl
			 << endl;
		response = -1;
		break;

	case 'h':
	case 'H':
		execute->display_help_screen();
		press_enter = getchar();
		system("cls");
		cout << "\n\n\n\n\n\n\t\t\t\tPlease enter your name \n\t\t\t\t\t";
		cin >> name;
		start_grid();
		execute->start_grid();
		while (1)
		{
			execute->display_grid();
			execute->key_press();
			execute->logic_flow(execute);
			execute->game_end_check(execute);
		}
		break;
	}
}

//The fuctioning of the game is carried out with the help of this function
void Game_AI::logic_flow(Game *execute)
{

	switch (control)
	{
	case 'w':
	case 'W':
	case 'a':
	case 'A':
	case 's':
	case 'S':
	case 'd':
	case 'D':
		execute->backup_grid();
		execute->fill_space();
		execute->update_grid();
		execute->fill_space();
		execute->find_greatest_tile();
		execute->display_grid();
		usleep(1000 * 160);

		if (execute->full() && apocalypse)
		{
			response = -1;
			break;
		}
		else if (execute->block_moves())
		{
			execute->spawn();
			break;
		}
		else
		{
			response = 0;
			break;
		}

	case 'u':
	case 'U':
		if (execute->block_moves())
			score -= plus;
		execute->undo();
		break;

	case 'r':
	case 'R':
		execute->start_grid();
		score = 0;
		plus = 0;
		break;

	case 'q':
	case 'Q':
		response = -1;
		break;

	case 'h':
	case 'H':
		execute->display_help_screen();
		press_enter = getchar();
		execute->display_grid();
		break;
	}
}

void Game_AI::game_end_check(Game *screen)
{
	if (max == win)
	{
		screen->display_win_screen();

		if (screen->display_try_again_screen(0) == 'n' || screen->display_try_again_screen(0) == 'N')
		{
			response = -1;
		}
		else
			win *= 2;
	}

	else if (response == -1)
	{
		screen->display_loser_screen();

		if (screen->display_try_again_screen(1) == 'y' || screen->display_try_again_screen(1) == 'Y')
		{
			screen->start_grid();
			response = 0;
		}
	}

	if (response == -1)
	{
		system("cls");
		cout << "\n\n\t\t            > Thank you for playing. "
			 << "\n\n\n\t\t\t\t\t\t    [-_-] \n\n";
		press_enter = getchar();
		exit(0);
	}
}

//what to display on the screen after the completion of the game is determined through this function
void Game_AI::start_grid()
{
	int i, j;

	plus = 0;
	score = 0;
	max = 0;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			grid[i][j] = 0;

	i = random_index(4);
	j = random_index(4);

	grid[i][j] = 2;

	i = random_index(4);
	j = random_index(4);

	grid[i][j] = 2;
}

//through this function the initial random generated grid is generated
void Game::display_grid()
{

	system("cls");

	cout << "\n  ::[  THE 2048 PUZZLE  ]::\t\t\t\t [-_-]\n\n\t";

	if (plus)
		cout << "+" << plus << "!";
	else
		cout << "   ";

	cout << "\t\t\t\t\t\tSCORE::" << score << " \n\n\n\n";

	for (int i = 0; i < 4; i++)
	{
		cout << "\t\t     |";

		for (int j = 0; j < 4; j++)
		{
			if (grid[i][j])
				printf("%4d    |", grid[i][j]);
			else
				printf("%4c    |", ' ');
		}

		cout << endl
			 << endl;
	}

	cout << "\n\n Controls (+ :: o)\t\t\t\tu - undo\tr - restart\n\n\tW\t\t     ^\t\t\th - help\tq - quit\n\t\t\t\t\t\t\t\t"
		 << " \n   A    S    D\t\t<    v    >\t\t\t     ."
		 << " \n\t\t\t\t                             ";
}

//through this function the initial random generated grid is displayed, along with the title of the game and the further actions that can be carried out
int random_index(int x)
{
	int index;
	index = rand() % x + 0;

	return index;
}

//this is the function where we store the current grid in a backup-grid to carry out the undo function
void Game_AI::backup_grid()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			bgrid[i][j] = grid[i][j];
}

// through this function we fill the spaces created after moving the numbers on the grid
void Game_AI::fill_space()
{

	switch (control)
	{
	case 'w':
	case 'W':
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				if (!grid[j][i])
				{
					for (int k = j + 1; k < 4; k++)
						if (grid[k][i])
						{
							grid[j][i] = grid[k][i];
							grid[k][i] = 0;
							break;
						}
				}
			}
		break;

	case 's':
	case 'S':
		for (int i = 0; i < 4; i++)
			for (int j = 3; j >= 0; j--)
			{
				if (!grid[j][i])
				{
					for (int k = j - 1; k >= 0; k--)
						if (grid[k][i])
						{
							grid[j][i] = grid[k][i];
							grid[k][i] = 0;
							break;
						}
				}
			}
		break;
	case 'a':
	case 'A':
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				if (!grid[i][j])
				{
					for (int k = j + 1; k < 4; k++)
						if (grid[i][k])
						{
							grid[i][j] = grid[i][k];
							grid[i][k] = 0;
							break;
						}
				}
			}
		break;

	case 'd':
	case 'D':
		for (int i = 0; i < 4; i++)
			for (int j = 3; j >= 0; j--)
			{
				if (!grid[i][j])
				{
					for (int k = j - 1; k >= 0; k--)
						if (grid[i][k])
						{
							grid[i][j] = grid[i][k];
							grid[i][k] = 0;
							break;
						}
				}
			}
		break;
	}
}

// through this function we update grid after moving the numbers on the grid
// increase the value wherever necessary that is when two similar tiles collide
// also in this function we add up the score and how much the score increases after every move too
void Game_AI::update_grid()
{
	plus = 0;
	apocalypse = 1;

	switch (control)
	{
	case 'w':
	case 'W':
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 3; j++)
			{
				if (grid[j][i] && grid[j][i] == grid[j + 1][i])
				{
					apocalypse = 0;
					grid[j][i] += grid[j + 1][i];
					grid[j + 1][i] = 0;
					plus += (((log2(grid[j][i])) - 1) * grid[j][i]);
					score += (((log2(grid[j][i])) - 1) * grid[j][i]);
				}
			}
		break;

	case 's':
	case 'S':
		for (int i = 0; i < 4; i++)
			for (int j = 3; j > 0; j--)
			{
				if (grid[j][i] && grid[j][i] == grid[j - 1][i])
				{
					apocalypse = 0;
					grid[j][i] += grid[j - 1][i];
					grid[j - 1][i] = 0;
					plus += (((log2(grid[j][i])) - 1) * grid[j][i]);
					score += (((log2(grid[j][i])) - 1) * grid[j][i]);
				}
			}
		break;

	case 'a':
	case 'A':
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 3; j++)
			{
				if (grid[i][j] && grid[i][j] == grid[i][j + 1])
				{
					apocalypse = 0;
					grid[i][j] += grid[i][j + 1];
					grid[i][j + 1] = 0;
					plus += ((log2(grid[i][j])) - 1) * grid[i][j];
					score += ((log2(grid[i][j])) - 1) * grid[i][j];
				}
			}
		break;

	case 'd':
	case 'D':
		for (int i = 0; i < 4; i++)
			for (int j = 3; j > 0; j--)
			{
				if (grid[i][j] && grid[i][j] == grid[i][j - 1])
				{
					apocalypse = 0;
					grid[i][j] += grid[i][j - 1];
					grid[i][j - 1] = 0;
					plus += ((log2(grid[i][j])) - 1) * grid[i][j];
					score += (((log2(grid[i][j])) - 1) * grid[i][j]);
				}
			}
		break;
	}
}

//with this fucntion we enable the generation of a 2 or 4 after every move at a random speace on the grid
void Game_AI::spawn()
{
	int i, j, k;

	do
	{
		i = random_index(4);
		j = random_index(4);
		k = random_index(10);

	} while (grid[i][j]);

	if (k < 2)
		grid[i][j] = 4;

	else
		grid[i][j] = 2;
}

//we check for the greatest tile after every move, and if 2048 is present we declare the user as a winner
void Game_AI::find_greatest_tile()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (grid[i][j] > max)
				max = grid[i][j];
}

//this is to check if the grid is full and also has no more tiles which could be collided against one another, if so, game ends
int Game_AI::full()
{
	int k = 1;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (!grid[i][j])
				k = 0;
		}
	return k;
}

//this function displays the rules of the 2048 game
void Game::display_help_screen()
{
	system("cls");

	cout << endl
		 << "  ::[  THE 2048 PUZZLE  ]::\t\t\t\t[-_-]";

	char text[] = "> The game starts with 1 or 2 randomly placed numbers in a 4x4 grid (16 cells).> Use the controls to move the cells. ( Press W/A/S/D )> 2 cells of the same number will merge and add up.> New 2s and 4s will appear randomly on an empty cell with each move you make.> Your objective is to make 2048 in a cell without getting stuck!> ";

	for (int i = 0; text[i]; i++)
	{
		if (text[i] == '>')
		{
			usleep(1000 * 500);
			cout << "\n\n\n";
		}

		cout << text[i];
	}
	system("pause");
}

//Fuction to display what the user sees on winning
void Game::display_win_screen()
{
	system("cls");

	cout << endl
		 << endl;
	cout << "\n\t\t\t  :: [  YOU MADE " << win << "!  ] ::"
		 << "\n\n\t\t\t  :: [ YOU WON THE GAME ] ::"
		 << "\n\n\n\n\t\t\t TILE\t     SCORE";
	printf("\n\n\t\t\t %4d\t    %6d\t    ", max, score);

	cout << "\n\n\t\t> The maximum possible tile is 65,536 ! So go on :)";
	register_score();
}

//Fuction to display what the user sees on losing
void Game::display_loser_screen()
{
	system("cls");

	cout << "\n\n\n\t\t\t  :: [ G A M E  O V E R ] ::"
		 << "\n\n\n\n\t\t\t TILE\t     SCORE\t  ";
	printf("\n\n\t\t\t %4d\t    %6d\t    ", max, score);

	cout << "\n\n\t\t> The maximum possible score is 3,932,156 ! So close :p";

	register_score();
}

//Function to allow the user to choose to continue or quit the game
char Game::display_try_again_screen(int lose)
{
	if (lose)
		cout << "\n\n\n\t    > Would you like to try again " << name << " (y/n) ? :: ";
	else
		cout << "\n\n\n\t    > Would you like to continue playing " << name << " (y/n) ? :: ";

	system("stty raw");
	cin >> option;
	system("stty cooked");

	return option;
}

//Undo function returns the grid to its state before the last move
void Game_AI::undo()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			grid[i][j] = bgrid[i][j];
}

//Function to check whether undo is possible or not
int Game_AI::block_moves()
{
	int k = 0;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (bgrid[i][j] != grid[i][j])
			{
				k = 1;
				break;
			}
	return k;
}

//function that enables us to store the name and score of the user in a file after each turn of theirs
void Game ::register_score()
{
	FILE *ptr;
	ptr = fopen("record_round.txt", "a");
	fprintf(ptr, "\n%s --> %d", name, score);
	fclose(ptr);
	cout << "\n\n\t\tTo see the score press Z\n\t\tPress T to restart\n\t\tPress any key to exit\n\t\t";
	cin >> option;
	if (option == 'Z' || option == 'z')
	{
		show_score();
	}
	else if (option == 'T' || option == 't')
	{
		start_grid();
		score = 0;
		plus = 0;
	}
	else
		exit(0);
}

//function that enables the showing of the scores
void Game ::show_score()
{
	system("cls");
	FILE *fptr;
	fptr = fopen("record_round.txt", "r");
	if (fptr == NULL)
	{
		printf("No file exist,probably you haven't played yet\n");
		printf("Press Y to go to main home\n");
	}
	else
	{
		char c = getc(fptr);
		printf("your  : \n");
		printf("Name\t\tscore\n");
		while (c != EOF)
		{
			printf("%c", c);
			c = getc(fptr);
		}
		cout << "\n\n\t\tTo reset the score press R\n\t\tPress T to restart\n\t\tPress any key to exit\n\t\t";
		cin >> option;
		if (option == 'R' || option == 'r')
		{
			reset_score();
		}
		else if (option == 'T' || option == 't')
		{
			start_grid();
			score = 0;
			plus = 0;
		}
		else
		{
			exit(0);
		}
	}
	fclose(fptr);
}

//function that enables the resetting of the said scores
void Game ::reset_score()
{
	system("cls");
	FILE *fptr;
	fptr = fopen("record_round.txt", "w");
	cout << "\n\n\t\tPress Y to proceed \n\t\tPress any key to exit\n\n\t\t";
	char res = toupper(getch());
	if (res == 'Y' || res == 'y')
	{
		remove("record_score.txt");
		printf("\n\t\tSuccesfully cleared the record\n");
		return;
	}
	else
	{
		exit(0);
	}
	fclose(fptr);
}
