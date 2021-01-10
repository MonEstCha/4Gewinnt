// fourwins_field.h
#ifndef FOURWINS_FIELD_H // include guard
#define FOURWINS_FIELD_H

class fourwins_field
{
    public:
	// static fourwins_field* initialize_field(int nr_rows, int nr_cols);
	fourwins_field(int nr_rows, int nr_cols);
	void show_field();
	int get_rows();
	int get_columns();
	int** field_array;
	// bool game_over;
	bool field_full();
	int best_move(int current_move, int depth);
	int** place_choice(int choice, int row, int player, int** current_field);
	int count_two_and_three_in_a_row(int nr);
	int evaluate_final_field();
	int row_of_choice(int choice_col);
    	bool four_wins(int col, int row);
    private:
	int ff_columns;
	int ff_rows; 
	// static fourwins_field* field;
};


#endif /* FOURWINS_FIELD_H */
