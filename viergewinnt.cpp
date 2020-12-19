#include <iostream>

using namespace std;

int field[8][8];
bool game_over = false;
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define RESET   "\033[0m"

void initialize_field()
{
	for (int row{ 0 }; row < 8; ++row) // step through the rows in the array
	{
	    string rowString;
	    for (int col{ 0 }; col < 8; ++col) // step through each element in the row
	    {
		field[row][col] = 0;
		
		rowString += to_string(field[row][col]) + ' ' ;

	    }
	    cout << rowString << " \n";
	}
}

void show_field()
{
	for (int row{ 0 }; row < 8; ++row) // step through the rows in the array
	{
	    string rowString;
	    for (int col{ 0 }; col < 8; ++col) // step through each element in the row
	    {
		if (field[row][col] == 1)
		{
			rowString += RED + to_string(field[row][col]) + RESET + ' ' ;
		}
		else if (field[row][col] == 2)
		{
			rowString += GREEN + to_string(field[row][col]) + RESET + ' ' ;
		}
		else{
			rowString += to_string(field[row][col]) + ' ' ;
		}
	    }
	    cout << rowString << " \n";
	}
}

void field_full()
{ 
	int upper_row_status = 0;
	for (int col{ 0 }; col < 8; ++col)
	{
		if (field[0][col] != 0)
		{
			upper_row_status += 1;
		}
	}
	if (upper_row_status == 8)
	{
		game_over = true;
		cout << "Oh dear! The field is completely filled and the game therefore over. \n";
	}	
}

bool four_wins(int row, int col)
{	
	bool fw = false;
	int counter = 0;	
	if (row < 5) // search downwards
	{
		if (field[row][col] == field[row+3][col])
		{
			if (field[row][col] == field[row+2][col])
			{
				if (field[row][col] == field[row+1][col])
				{
					return true;
				}
			}
		}
	}
	int leftmost = 0;
	int rightmost = 7;
	if (col < 4)
	{
		rightmost = col + 3;
	}
	if (col >= 4)
	{
		leftmost = col - 3;
	}
	for (int i = rightmost; i >= leftmost; --i) // search in the row
	{
		if (field[row][col] == field[row][i])
		{	
			counter += 1;
		}
		else if (field[row][col] != field[row][i] and counter < 4)
		{
			counter = 0;
		}
	} 
	if (counter >= 4)
	{
		return true;		
	}
	
	counter = 1;
	int a = row + 1;
	int b = col + 1;
	while ( a < 8  and b < 8 and counter < 4) // search diagonally on the lower righthand side
	{
		if (field[row][col] == field[a][b])
		{	
			counter += 1;
			a += 1;
			b += 1;
		} 
		else if (field[row][col] != field[a][b] and counter < 4)
		{	
			counter = 1;
			a = 8;
			b = 8;
		} 

	}
	if (counter >= 4)
	{
		return true;		
	}
	
	a = row - 1;
	b = col - 1;
	while ( a >= 0  and b >= 0 and counter < 4) // search diagonally on the upper lefthand side
	{
		if (field[row][col] == field[a][b])
		{	
			counter += 1;
			a -= 1;
			b -= 1;
		}
		else if (field[row][col] != field[a][b] and counter < 4)
		{	
			counter = 1;
			a = -1;
			b = -1;
		} 

	} 
	if (counter >= 4)
	{
		return true;		
	}
	
	counter = 1;
	a = row + 1;
	b = col - 1;
	while ( a < 8  and b >= 0 and counter < 4) // search diagonally on the upper righthand side
	{
		if (field[row][col] == field[a][b])
		{	
			counter += 1;
			a += 1;
			b -= 1;
		} 
		else if (field[row][col] != field[a][b] and counter < 4)
		{	
			counter = 1;
			a = 8;
			b = -1;
		} 

	}
	if (counter >= 4)
	{
		return true;		
	}
	
	a = row - 1;
	b = col + 1;
	while ( a >= 0  and b < 8 and counter < 4) // search diagonally on the lower lefthand side
	{
		if (field[row][col] == field[a][b])
		{	
			counter += 1;
			a -= 1;
			b += 1;
		} 
		else if (field[row][col] != field[a][b] and counter < 4)
		{	
			counter = 1;
			a = -1;
			b = 8;
		} 

	}
	if (counter >= 4)
	{
		return true;		
	}	
		
	return fw;	
}

bool choice_placed(int choice, int player)
{	
	bool placed = false;
	int choice_status = 0;
	for (int row{ 7 }; row >= 0; --row)
	{
		if (field[row][choice] == 0)
		{	
			if (player == 1){
				field[row][choice] = 1;
			}
			else{
				field[row][choice] = 2;				
			}
			game_over = four_wins(row, choice);
			break;
		}
		else
		{
			choice_status += 1;		
		}
	}
	if (choice_status == 8)
	{
		placed = false;
	}
	else
	{
		placed = true;
	}
	return placed;
}

void player1_set()
{
	int choice;
	cout << "Player 1, choose a column by passing in 0 to 7: ";
	cin >> choice;
	while(!choice_placed(choice, 1))
	{
		cout << "This column is already full. Please choose another one: ";
		cin >> choice;
	}
	show_field();
}

void player2_set()
{
	int choice;
	cout << "Player 2, choose a column by passing in 0 to 7: ";
	cin >> choice;
	while(!choice_placed(choice, 2))
	{
		cout << "This column is already full. Please choose another one: ";
		cin >> choice;
	}
	show_field();
}


int main()
{
	int m = 0;	
	initialize_field();
	while(!game_over)
	{
		player1_set();
		if (!game_over){		
			player2_set();
			if (game_over)
			{
				cout << "Player 2 wins! \n" ;
			}
			else
			{
				field_full();
			}
		}
		else
		{
			
			cout << "Player 1 wins! \n" ;
		}
		m += 1;
	}
	return 0;
}
