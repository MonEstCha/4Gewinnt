#include <iostream>
#include "fourwins_field.h"
#include "player.h"

using namespace std;

fourwins_field* ff;
bool game_over = false;

void ai_set(ai* _ai)
{	
	int choice = ff->best_move(1, _ai->depth_of_recursion);	// field is initialized as global variable
	int row = ff->row_of_choice(choice); // find most upper empty entry in field
	cout << "AI has set to column, row " << choice << ", " << row << '\n';
	ff->field_array = ff->place_choice(choice, row, 2, ff->field_array);  // The AI sets the number 2
	game_over = ff->four_wins(choice, row);
	ff->show_field();
}

void player_set()
{
	int choice;
	cout << "Choose a column by passing 1 to 7: ";
	cin >> choice;
	if (choice <= 0)
	{
		cout << "This column doesn't exist! ";
		player_set();
	}
	else
	{
		choice = choice - 1;
		int row = ff->row_of_choice(choice);
		if (row == ff->get_rows())
		{
			cout << "This column is already full. Please choose another one! ";
			player_set();
		}
		else
		{
			int** a = ff->place_choice(choice, row, 1, ff->field_array);
			ff->field_array = a;
		}
		game_over = ff->four_wins(choice, row);
		ff->show_field();
		cout <<'\n';
	}
}

int main()
{
	ff = new fourwins_field(6, 7);
	ff->show_field();
	ai* player1 = ai::create_ai(9); 
	hi* player2 = hi::create_hi();
	// player_set(ff);
	// ai_set(ff, player1);
	while(!game_over)
	{
		player_set();
		// ai_set(ff, player1);
		if (!game_over)
		{		
			ai_set(player1);
			if (game_over)
			{
				cout << "The AI wins! \n" ;
			}
			else
			{
				game_over = ff->field_full();
			}
		}
		else
		{
			
			cout << "The player wins! \n" ;
		}
	}
	return 0;
}
