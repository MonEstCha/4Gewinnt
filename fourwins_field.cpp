#include "fourwins_field.h"
#include <iostream>

using namespace std;

#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define RESET   "\033[0m"

// fourwins_field* fourwins_field::field = NULL;
//int** fourwins_field::field_array = 0;

int fourwins_field::get_rows(){
	return this->ff_rows;
}

int fourwins_field::get_columns(){
	return this->ff_columns;
}

bool fourwins_field::field_full()
{	 
	int upper_row_status = 0;
	for (int col{ 0 }; col < this->get_columns(); ++col)
	{
		if (this->field_array[0][col] != 0)
		{
			upper_row_status += 1;
		}
	}
	if (upper_row_status == this->get_columns())
	{
		cout << "Oh dear! The field is completely full and the game therefore over. \n";
		return true;
	}
	else
	{
		return false;
	}	
}

fourwins_field::fourwins_field(int nr_rows, int nr_cols)
{
    ff_rows = nr_rows;
    ff_columns = nr_cols;          
    this->field_array = new int*[ff_rows]; // should be done by constructor
    
    for (int row{ 0 }; row < ff_rows; ++row) // step through the rows in the array
    {
    	this->field_array[row] = new int[ff_columns];
    	string rowString;
    	for (int col{ 0 }; col < ff_columns; ++col) // step through each element in the row
    	{
		this->field_array[row][col] = 0;

    	}
    }
};
    	
/** fourwins_field* fourwins_field::initialize_field(int rows, int columns)
{	
	if (field==NULL)   // Only allow one instance of class to be generated.
            field = new fourwins_field(rows, columns);
	return field;
}*/

void fourwins_field::show_field()
{
	for (int row{ 0 }; row < this->get_rows(); ++row) // step through the rows in the array
	{
	    string rowString;
	    for (int col{ 0 }; col < this->get_columns(); ++col) // step through each element in the row
	    {
		if (this->field_array[row][col] == 1)
		{
			rowString += RED + to_string(this->field_array[row][col]) + RESET + ' ' ;
		}
		else if (this->field_array[row][col] == 2)
		{
			rowString += GREEN + to_string(this->field_array[row][col]) + RESET + ' ' ;
		}
		else{
			rowString += to_string(this->field_array[row][col]) + ' ' ;
		}
	    }
	    cout << rowString << " \n";
	}
}

int fourwins_field::row_of_choice(int choice_col)
{	
	int choice_row = this->get_rows();
	for (int row{ choice_row-1 }; row >= 0; --row)
	{	
		if (this->field_array[row][choice_col] == 0)
		{
			return row;
		}
	}
	return choice_row;
}

bool fourwins_field::four_wins(int col, int row)
{		
	int rows = this->get_rows();
	int cols = this->get_columns();	
	bool fw = false;
	int counter = 0;	
	if (row < 3) // search downwards
	{
		if (this->field_array[row][col] == this->field_array[row+3][col])
		{
			if (this->field_array[row][col] == this->field_array[row+2][col])
			{
				if (this->field_array[row][col] == this->field_array[row+1][col])
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
		if (this->field_array[row][col] == this->field_array[row][i])
		{	
			counter += 1;
		}
		else if (this->field_array[row][col] != this->field_array[row][i] and counter < 4)
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
		if (this->field_array[row][col] == this->field_array[a][b])
		{	
			counter += 1;
			a += 1;
			b += 1;
		} 
		else if (this->field_array[row][col] != this->field_array[a][b] and counter < 4)
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
		if (this->field_array[row][col] == this->field_array[a][b])
		{	
			counter += 1;
			a -= 1;
			b -= 1;
		}
		else if (this->field_array[row][col] != this->field_array[a][b] and counter < 4)
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
		if (this->field_array[row][col] == this->field_array[a][b])
		{	
			counter += 1;
			a += 1;
			b -= 1;
		} 
		else if (this->field_array[row][col] != this->field_array[a][b] and counter < 4)
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
		if (this->field_array[row][col] == this->field_array[a][b])
		{	
			counter += 1;
			a -= 1;
			b += 1;
		} 
		else if (this->field_array[row][col] != this->field_array[a][b] and counter < 4)
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


int** fourwins_field::place_choice(int choice, int row, int player, int** current_field)
{
	int** result_array = 0;
	int rows = this->get_rows();
	int cols = this->get_columns();
	result_array = new int*[rows];
	for (int i = 0; i < rows; ++i) 
	{
		result_array[i] = new int[cols];
		for (int j = 0; j < cols; ++j) 
		{
			result_array[i][j] = current_field[i][j];
		}
	}
	
	
	for (int row{ rows-1 }; row >= 0; --row)
	{
		if (current_field[row][choice] == 0)
		{	
			if (player == 1){
				result_array[row][choice] = 1;
			}
			else{
				result_array[row][choice] = 2;				
			}
			break;
		}
	}
	
	return result_array;	
}

int fourwins_field::count_two_and_three_in_a_row(int player)
{
	int rows = this->get_rows();
	int columns = this->get_columns();	
	int value = 0;
	int counter = 0;
	for (int col{ 0 }; col < columns; ++col) // search vertically
	{	
		if (this->field_array[0][col] == 0)
		{
			for (int row{ rows-1 }; row >= 0; --row)
			{
				if (this->field_array[row][col] == player)
				{
					counter += 1;	
				}
				else if (this->field_array[row][col] == 0)
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
			if (this->field_array[row][col] == player)
			{	
				if (col == (columns - 1) and (counter == 2 or counter == 1) and this->field_array[row][col-3] != 0)
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
			else if (this->field_array[row][col] == 0)
			{	
				if (counter >= 2)
				{
					counter += 1; 
					if (counter == 3)
					{	
						counter += 3;
					}
					else if (counter == 2 and this->field_array[row][col-3] != 0 and (col-3) >= 0)
					{
						if (this->field_array[row][col+1] != 0 and (col + 1) <= 7)
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
			if (this->field_array[a][b] == player)
			{		
				counter_player += 1;	
			}
			else if (this->field_array[a][b] == 0)
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
			if (this->field_array[a][b] == player)
			{		
				counter_player += 1;	
			}
			else if (this->field_array[a][b] == 0)
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
			if (this->field_array[a][b] == player)
			{		
				counter_player += 1;	
			}
			else if (this->field_array[a][b] == 0)
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
			if (this->field_array[a][b] == player)
			{		
				counter_player += 1;	
			}
			else if (this->field_array[a][b] == 0)
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

int fourwins_field::evaluate_final_field()
{
	return (this->count_two_and_three_in_a_row(2) - this->count_two_and_three_in_a_row(1)); // 2 is the number of the AI
}

int fourwins_field::best_move(int current_move, int depth_of_recursion) 
{		
	if (current_move < depth_of_recursion)
	{	
		int player_nr;
		// vector<int> values;	
 		int current_min = 100000;
 		int current_max = -100000;
 		int result_index = -1;
		for (int col_iterator = 0; col_iterator < this->get_columns(); ++col_iterator)
		{	
			if (current_move%2 == 0)
			{	
				player_nr = 1;
			}
			else
			{
				player_nr = 2;
			}
			int current_row = this->row_of_choice(col_iterator);
			if (current_row != this->get_rows())
			{
			// current_field needs to be updated to a hypothetic child field: place_choice(col_iterator, current_field):
				fourwins_field* child_field = new fourwins_field(this->get_rows(), this->get_columns());
				child_field->field_array = child_field->place_choice(col_iterator, current_row, player_nr, this->field_array); 
				if (child_field->four_wins(col_iterator, current_row))
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
					int child_result = child_field->best_move(current_move + 1, depth_of_recursion);
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
		return this->evaluate_final_field(); // determine the value of the current field
	}
}
