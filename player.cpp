#include "player.h"
//#include "fourwins_field.h"
#include <iostream>
#include <array>

using namespace std;

ai* ai::ai_instance = NULL;
hi* hi::hi_instance = NULL;

ai::ai(int _depth)
{
	depth_of_recursion = _depth;
};

hi::hi(){};

ai* ai::create_ai(int depth)
{	
	if (ai_instance==NULL)   // Only allow one instance of class to be generated.
            ai_instance = new ai(depth);
	return ai_instance;
}

hi* hi::create_hi()
{	
	if (hi_instance==NULL)   // Only allow one instance of class to be generated.
            hi_instance = new hi();
	return hi_instance;
}

/**int player::row_of_choice(int choice_col, fourwins_field* _ff)
{	
	int choice_row = _ff->get_rows();
	for (int row{ choice_row-1 }; row >= 0; --row)
	{	
		if (_ff->field_array[row][choice_col] == 0)
		{
			return row;
		}
	}
	return choice_row;
}

bool player::four_wins(int** current_field, int row, int col, int rows, int cols)
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
	int rightmost = rows;
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
	while ( a < rows  and b < cols and counter < 4) // search diagonally on the lower righthand side
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
	while ( a >= 0  and b <= rows and counter < 4) // search diagonally on the lower lefthand side
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


int** player::place_choice(int choice, int row, int player, int** current_field, int rows)
{
	int** result_array = 0;
	result_array = new int*[rows];
	for (int i = 0; i < rows; ++i) 
	{
		result_array[i] = new int[rows+1];
		for (int j = 0; j < rows+1; ++j) 
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
			// game_over = four_wins(result_array, row, choice);
			break;
		}
	}
	
	return result_array;	
}

int count_two_and_three_in_a_row(int** final_field, int player, int rows)
{	
	int value = 0;
	int counter = 0;
	for (int col{ 0 }; col < (rows + 1); ++col) // search vertically
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
		for (int col{ 0 }; col < rows + 1; ++col)
		{
			if (final_field[row][col] == player)
			{	
				if (col == (rows + 1 - 1) and (counter == 2 or counter == 1) and final_field[row][col-3] != 0)
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
	for (int row{3}; row < rows ; ++row) 
	{
		int a = row;
		int b = 0;
		while (a >= 0 and b < rows + 1) // search diagonally SW to NE
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
		b = rows + 1-1;
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
		int a = rows -1;
		while (a >= 0 and b < rows + 1) // search diagonally SW to NE
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
		
		a = rows -1;
		b = rows + 1-1-col;
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

int evaluate_final_field(int** final_field, int rows)
{
	return count_two_and_three_in_a_row(final_field, 1, rows) - count_two_and_three_in_a_row(final_field, 2, rows);
}

int ai::best_move(int current_move, int** current_field, fourwins_field* _ff) // current_move start value from depth?
{		
	if (current_move < this->depth_of_recursion)
	{	
		int player_nr;
		// vector<int> values;	
 		int current_min = 100000;
 		int current_max = -100000;
 		int result_index = -1;
		for (int col_iterator = 0; col_iterator < (_ff->get_rows()+1); ++col_iterator)
		{	
			if (current_move%2 == 0)
			{	
				player_nr = 1;
			}
			else
			{
				player_nr = 2;
			}
			int current_row = row_of_choice(col_iterator, _ff);
			if (current_row != _ff->get_rows())
			{
			// current_field needs to be updated to a hypothetic child field: place_choice(col_iterator, current_field):
				int** child_field = place_choice(col_iterator, current_row, player_nr, current_field, _ff->get_rows()); 
				if (four_wins(child_field, current_row, col_iterator, _ff->get_rows()))
				{
					if (player_nr == 1)
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
					int child_result = this->best_move(current_move + 1, child_field, _ff);
					if (player_nr == 1) 
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
		return evaluate_final_field(current_field, _ff->get_rows()); // determine the value of the current field
	}
}*/
