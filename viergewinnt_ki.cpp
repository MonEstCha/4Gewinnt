#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int** field = 0;
bool game_over = false;
int rows = 6;
int columns = 7;
int depth = 9;
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define RESET   "\033[0m"

void initialize_field()
{
	field = new int*[rows];
	for (int row{ 0 }; row < rows; ++row) // step through the rows in the array
	{
	    field[row] = new int[columns];
	    string rowString;
	    for (int col{ 0 }; col < columns; ++col) // step through each element in the row
	    {
		field[row][col] = 0;
		
		rowString += to_string(field[row][col]) + ' ' ;

	    }
	    cout << rowString << " \n";
	}
}

void show_field()
{
	for (int row{ 0 }; row < rows; ++row) // step through the rows in the array
	{
	    string rowString;
	    for (int col{ 0 }; col < columns; ++col) // step through each element in the row
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
	for (int col{ 0 }; col < columns; ++col)
	{
		if (field[0][col] != 0)
		{
			upper_row_status += 1;
		}
	}
	if (upper_row_status == columns)
	{
		game_over = true;
		cout << "Oh dear! The field is completely full and the game therefore over. \n";
	}	
}

int row_of_choice(int choice_col, int** current_field)
{
	int choice_row = rows;
	for (int row{ rows-1 }; row >= 0; --row)
	{	
		if (current_field[row][choice_col] == 0)
		{
			return row;
		}
	}
	return choice_row;
}

bool four_wins(int** current_field, int player, int row, int col)
{	
	bool fw = false;
	int counter = 0;	
	if (row < 3) // search downwards
	{
		if (current_field[row][col] == current_field[row+3][col])
		{
			if (current_field[row][col] == current_field[row+2][col])
			{
				if (current_field[row][col] == current_field[row+1][col])
				{
					return true;
				}
			}
		}
	}
	int leftmost = 0;
	int rightmost = columns-1;
	if (col < 3)
	{
		rightmost = col + 3;
	}
	if (col >= 4)
	{
		leftmost = col - 3;
	}
	for (int i = rightmost; i >= leftmost; --i) // search in the row
	{
		if (current_field[row][col] == current_field[row][i])
		{	
			counter += 1;
		}
		else if (current_field[row][col] != current_field[row][i] and counter < 4)
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
	while ( a < rows  and b < columns and counter < 4) // search diagonally on the lower righthand side
	{
		if (current_field[row][col] == current_field[a][b])
		{	
			counter += 1;
			a += 1;
			b += 1;
		} 
		else if (current_field[row][col] != current_field[a][b] and counter < 4)
		{	
			break;
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
		if (current_field[row][col] == current_field[a][b])
		{	
			counter += 1;
			a -= 1;
			b -= 1;
		}
		else if (current_field[row][col] != current_field[a][b] and counter < 4)
		{	
			break;
		} 

	} 
	if (counter >= 4)
	{
		return true;		
	}
	
	// next diagonal 
	counter = 1;
	a = row + 1;
	b = col - 1;
	while ( a < rows  and b >= 0 and counter < 4) // search diagonally on the upper righthand side
	{
		if (current_field[row][col] == current_field[a][b])
		{	
			counter += 1;
			a += 1;
			b -= 1;
		} 
		else if (current_field[row][col] != current_field[a][b] and counter < 4)
		{	
			break;
		} 

	}
	if (counter >= 4)
	{
		return true;		
	}
	
	a = row - 1;
	b = col + 1;
	while ( a >= 0  and b < columns and counter < 4) // search diagonally on the lower lefthand side
	{
		if (current_field[row][col] == current_field[a][b])
		{	
			counter += 1;
			a -= 1;
			b += 1;
		} 
		else if (current_field[row][col] != current_field[a][b] and counter < 4)
		{	
			break;
		} 

	}
	if (counter >= 4)
	{
		return true;		
	}	
		
	return fw;	
}

int** place_choice(int choice, int row, int player, int** current_field)
{
	int** result_array = 0;
	result_array = new int*[rows];
	for (int i = 0; i < rows; ++i) 
	{
		result_array[i] = new int[columns];
		for (int j = 0; j < columns; ++j) 
		{
			result_array[i][j] = current_field[i][j];
		}
	}
	
	
	for (int row{ rows-1 }; row >= 0; --row)
	{
		// result_array[row] = current_field[row];
		if (current_field[row][choice] == 0)
		{	
			if (player == 1){
				result_array[row][choice] = 1;
			}
			else{
				result_array[row][choice] = 2;				
			}
			game_over = four_wins(result_array, player, row, choice);
			break;
		}
	}
	
	return result_array;	
}

int count_two_and_three_in_a_row(int** final_field, int player)
{	
	int value = 0;
	int counter = 0;
	for (int col{ 0 }; col < columns; ++col) // search vertically
	{	
		if (final_field[0][col] == 0)
		{
			for (int row{ rows-1 }; row >= 0; --row)
			{
				if (final_field[row][col] == player)
				{
					counter += 1;	
				}
				else if (final_field[row][col] == 0)
				{	
					if (counter >= 2)
					{
						counter += 1; 
						if (counter == 3)
						{
							counter += 3;
						}
					}
					value += counter;
					counter = 0;
					break;	
				}
				else 
				{
					counter = 0;
					break;
				}
			}
		}
	}
	
	counter = 0;
	
	for (int row{ 0 }; row < rows; ++row) // search horizontally
	{
		for (int col{ 0 }; col < columns; ++col)
		{
			if (final_field[row][col] == player)
			{	
				if (col == (columns - 1) and (counter == 2 or counter == 1) and final_field[row][col-3] != 0)
				{
					counter = 0;
				}
				else
				{
					if (col == 2 or col == 3 or col == 4)
					{
						counter += 2;
					}
					counter += 1;
				}	
			}
			else if (final_field[row][col] == 0)
			{	
				if (counter >= 2)
				{
					counter += 1; 
					if (counter == 3)
					{	
						counter += 3;
					}
					else if (counter == 2 and final_field[row][col-3] != 0 and (col-3) >= 0)
					{
						if (final_field[row][col+1] != 0 and (col + 1) <= 7)
						{
							counter = 0;
						}
					}
				}
				value += counter;
				counter = 0;	
			}
			else  
			{
				counter = 0;
			}
		}
	}
	
	int counter_0 = 0;
	int counter_player = 0;
	for (int row{3}; row < rows; ++row) 
	{
		int a = row;
		int b = 0;
		while (a >= 0 and b < columns) // search diagonally SW to NE
		{			
			if (final_field[a][b] == player)
			{		
				counter_player += 1;	
			}
			else if (final_field[a][b] == 0)
			{
				counter_0 += 1;		
			}
			else 
			{	
				if ((counter_player + counter_0) >= 4)
				{
					if (counter_player >= 2)
					{
						counter_player += 1; 
						if (counter_player >= 3)
						{
							counter_player *= 2;
						}
					}
					value += counter_player;
				} 
				counter_0 = 0;
				counter_player = 0;
			}
			a -= 1;
			b += 1;			
		}
		if ((counter_player + counter_0) >= 4)
		{
			if (counter_player >= 2)
			{
				counter_player += 1; 
				if (counter_player >= 3)
				{
					counter_player *= 2;
				}
			}
			value += counter_player;
		} 
		counter_0 = 0;
		counter_player = 0;
		
		a = row;
		b = columns-1;
		while (a >= 0 and b >= 0) // search diagonally SE to NW
		{			
			if (final_field[a][b] == player)
			{		
				counter_player += 1;	
			}
			else if (final_field[a][b] == 0)
			{
				counter_0 += 1;		
			}
			else 
			{	
				if ((counter_player + counter_0) >= 4)
				{
					if (counter_player >= 2)
					{
						counter_player += 1; 
						if (counter_player >= 3)
						{
							counter_player *= 2;
						}
					}
					value += counter_player;
				} 
				counter_0 = 0;
				counter_player = 0;
			}
			a -= 1;
			b -= 1;			
		}
		if ((counter_player + counter_0) >= 4)
		{
			if (counter_player >= 2)
			{
				counter_player += 1; 
				if (counter_player >= 3)
				{
					counter_player *= 2;
				}
			}
			value += counter_player;
		} 
		counter_0 = 0;
		counter_player = 0;
	}
	
	for (int col{1}; col < 4; ++col) 
	{
		int b = col;
		int a = rows-1;
		while (a >= 0 and b < columns) // search diagonally SW to NE
		{			
			if (final_field[a][b] == player)
			{		
				counter_player += 1;	
			}
			else if (final_field[a][b] == 0)
			{
				counter_0 += 1;		
			}
			else 
			{	
				if ((counter_player + counter_0) >= 4)
				{
					if (counter_player >= 2)
					{
						counter_player += 1; 
						if (counter_player >= 3)
						{
							counter_player *= 2;
						}
					}
					value += counter_player;
				} 
				counter_0 = 0;
				counter_player = 0;
			}
			a -= 1;
			b += 1;			
		}
		if ((counter_player + counter_0) >= 4)
		{
			if (counter_player >= 2)
			{
				counter_player += 1; 
				if (counter_player >= 3)
				{
					counter_player *= 2;
				}
			}
			value += counter_player;
		} 
		counter_0 = 0;
		counter_player = 0;
		
		a = rows-1;
		b = columns-1-col;
		while (a >= 0 and b >= 0) // search diagonally SE to NW
		{			
			if (final_field[a][b] == player)
			{		
				counter_player += 1;	
			}
			else if (final_field[a][b] == 0)
			{
				counter_0 += 1;		
			}
			else 
			{	
				if ((counter_player + counter_0) >= 4)
				{
					if (counter_player >= 2)
					{
						counter_player += 1; 
						if (counter_player >= 3)
						{
							counter_player *= 2;
						}
					}
					value += counter_player;
				} 
				counter_0 = 0;
				counter_player = 0;
			}
			a -= 1;
			b -= 1;			
		}
		if ((counter_player + counter_0) >= 4)
		{
			if (counter_player >= 2)
			{
				counter_player += 1; 
				if (counter_player >= 3)
				{
					counter_player *= 2;
				}
			}
			value += counter_player;
		} 
		counter_0 = 0;
		counter_player = 0;
	}
	
	return value;
}

int evaluate_final_field(int** final_field)
{
	return count_two_and_three_in_a_row(final_field, 2) - count_two_and_three_in_a_row(final_field, 1);
}

int best_move(int current_move, int** current_field)
{			
	if (current_move < depth)
	{	
		int player;
		// vector<int> values;	
 		int current_min = 100000;
 		int current_max = -100000;
 		int result_index = -1;
		// int values[8]; // better dynamic array, i.e. vector
		// if (current_move == 1)
		// 	check if column for best move is already full, if so choose second best
		for (int col_iterator = 0; col_iterator < columns; ++col_iterator)
		{	
			if (current_move%2 == 0)
			{	
				player = 1;
			}
			else
			{
				player = 2;
			}
			int current_row = row_of_choice(col_iterator, current_field);
			if (current_row != rows)
			{
			// current_field needs to be updated to a hypothetic child field: place_choice(col_iterator, player, current_field):
				int** child_field = place_choice(col_iterator, current_row, player, current_field); 
				if (four_wins(child_field, player, current_row, col_iterator))
				{
					if (player == 1)
					{
						return (current_move == 1) ? col_iterator : -10000;	// skip the child columns			 	
					}
					else
					{
					 	// values.insert ( values.end() , 10000);
					 	return (current_move == 1) ? col_iterator : 10000;			 	
					}
				}
				else
				{
					int child_result = best_move(current_move + 1, child_field);
					if (player == 1) 
					{
						if (child_result < current_min) 
						{
							current_min = child_result;
						}
					} 
					else
					{
						if (child_result > current_max) 
						{
							current_max = child_result;
							result_index = col_iterator;
						}
					}
				}
			}
		}
		if (current_move%2 == 0)
		{ 
			return current_min;
		}							
		else
		{	
			return (current_move == 1) ? result_index : current_max;
		}
	}
	else //if (current_move == 4)
	{	
		return evaluate_final_field(current_field); // determine the value of the current field
	}
}

void ki_set()
{
	int choice = best_move(1, field);	// field is initialized as global variable
	// cout << choice << '\n';
	int row = row_of_choice(choice, field); // find most upper empty entry in field
	cout << "kis sets to row, column " << choice << "; " << row << '\n';
	field = place_choice(choice, row, 2, field);  // like choice_placed(choice, player) in viergewinnt.cpp, but returns the updated passed field, so the global field array can be updated
	show_field();
}

void player_set()
{
	int choice;
	cout << "Choose a column by passing in 0 to 7: ";
	cin >> choice;
	int row = row_of_choice(choice, field);
	if (row == rows)
	{
		cout << "This column is already full. Please choose another one! ";
		player_set();
	}
	else
	{
		field = place_choice(choice, row, 1, field);
	}
	show_field();
	cout << '\n';
}

int main()
{
	int m = 0;	
	initialize_field();
	while(!game_over)
	{
		ki_set();
		if (!game_over)
		{		
			player_set();
			if (game_over)
			{
				cout << "The player wins! \n" ;
			}
			else
			{
				field_full();
			}
		}
		else
		{
			
			cout << "The AI wins! \n" ;
		}
		m += 1;
	}
	return 0;
}

	
