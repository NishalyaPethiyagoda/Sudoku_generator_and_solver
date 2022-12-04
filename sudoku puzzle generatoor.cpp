
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

const int size = 9;
int matrix[size][size];

class Sudoku_matrix
{
    public:
    	
	bool row_condition(int row, int val);
	bool column_condition(int col, int val);
	bool mat_3by3_condition(int r, int c, int val)  ;  
	bool all_conditions_true(int row, int col, int number);
	void fill_to_diagonal(int cr, int cc);
	bool fill_to_other_locations(int row, int col);
	void generator_function();
	void creating_blanks(int num_f_indices);
	void display();
};

/*  function : checking columns for value the value whether it already exists
 		inputs       : row, value
    	output      : if value already in a row return true
*/
bool Sudoku_matrix::row_condition(int row, int val)
{
    for (int col = 0; col < size; col++)
    {
    	if (matrix[row][col] == val)
    	    return true;
	}    	  	
    return false;
}
    
/*  function : checking columns for value the value whether it already exists 
    		inputs : column, value
    		output : if value already in a coloumn return true
*/
bool Sudoku_matrix::column_condition(int col, int val)
{
    for (int row = 0; row < size; row++)
    {
        if (matrix[row][col] == val)
            return true;
	}           
    return false;
}

/*  function : 3 by 3 matrix condition check for same value  
    	inputs  : row, column and value
    	output  : if value exists within the sub array -> return true
*/
bool Sudoku_matrix::mat_3by3_condition(int r, int c, int val)
{
    int mat_3by3_start_row = r - r % 3;
    int mat_3by3_start_col = c - c % 3;
        
    for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
        {
            if ( matrix[ row  +  mat_3by3_start_row ][col  +  mat_3by3_start_col ] == val )
            {
               	return true;
			}    
		} 
	}      
    return false;
}

/*   function: checking conditions if ture
    	inputs      : row, column and value
    	output      : if, all conditions are true-> return true
*/
bool Sudoku_matrix::all_conditions_true(int row, int col, int number)
{
    return !row_condition(row, number) && !column_condition(col, number) && !mat_3by3_condition(row, col, number);
}

/* function: filling diagonal sub matrix locations
    	inputs       : diagonal coordinate
    	output      : N/A
*/
void Sudoku_matrix::fill_to_diagonal(int cr, int cc)
{
    for (int row = 0; row < 3; row++)
    {
    	for (int col = 0; col < 3; col++)
        {
            int number;
            do
            {
                    number = 1 + rand() % 9;   //pick a random number between 1 and 9
            } 
			while ( mat_3by3_condition(row+cr , col+cc , number)) ;
				
            matrix[row+cr][col+cc] = number;
    	}
	}      
}
    
/* function: filling numbers to locations outside the diagonal
   		inputs :
   		output :
*/
bool Sudoku_matrix::fill_to_other_locations(int row, int col)
{
    if (col >= size && row < size-1 )
    {
        row ++;
        col = 0;
    }
    if (row >= size && col >= size)
    {
        return true;
	}    
    
    if (row < 3)
    {
        if (col < 3)
        col = 3;
    }
    
    else if (row < size-3)
    {
        if (col == (int)(row/3)*3)
    	col +=  3;
    }
    
    else
    {
        if (col == size-3)
        {
            row++;
            col = 0;
            if (row >= size)
                return true;
        }
    }
    
    for (int number = 1; number<=size; number++)
    {
        if ( all_conditions_true(row, col, number) )
        {
            matrix[row][col] = number;
            if ( fill_to_other_locations( row, col+1 ) )
            {
                return true;
			}      
            matrix[row][col] = 0;
        }
    }
    return false;
}
    
/*function: generator_function   
    	input    : N/A
  		output   : N/A
*/
void Sudoku_matrix::generator_function()
{
    //fill_to_diagonal function: to fill 3 by 3 matrix grids in main diagonal 
    fill_to_diagonal(0, 0);
		 
    fill_to_diagonal(3, 3); 
        
    fill_to_diagonal(6, 6); 
        
    //fill_to_other_locations funtion: to fill undiagonal 3 byb 3 matrix grids 
    fill_to_other_locations(0, 3); 
}

/* function: assign 0 to random indices in the matrix
		input  : missing cell in each row
 		output : N/A  
*/
void Sudoku_matrix::creating_blanks(int num_f_indices)
{    
    for (int row = 0; row < size; row++)
    {
        int count = 0;
            
        while (count < num_f_indices)
        {
            int cell= rand() % 9;
            if(matrix[row][cell]!=0)
            {
                matrix[row][cell] = 0;
                count++;
            }
       }  
    }                          
}

/* function: printin matrix on console output
		input  : missing cell in each row
 		output : N/A 

*/    
void Sudoku_matrix::display()
{
    for (int row = 0; row < size; row++)
	{
        for (int col = 0; col < size; col++)
		{
            if(col == 3 || col == 6)
                cout << " | ";
            cout << matrix[row][col] <<" ";
        }
        if(row == 2 || row == 5)
		{
            cout << endl;
            for(int i = 0; i<size; i++)
                cout << "---";
        }
    	cout << endl;
    }
    cout << "\n\n";
}

int main()
{
	int blanks;
	srand(time(0));
	
	//intializing the matrix with 0
    for (int row = 0; row < size; row++)
    {
    	for (int col; col < size; col++)
    	{
    		matrix[row][col] = 0;   
		}
            
	}

    cout << "input the expected blanks per row/column : ";
    cin >> blanks;

    Sudoku_matrix object;   //sudoku matrix object
	
	//calling matrix generator function	  			
    object.generator_function(); 
	
	// call blanks creating function    
    object.creating_blanks( blanks ); 
    
    //output Sudoku_matrix to console
    object.display(); 				
    
    //inpting generated puzzle to text file
    ofstream file;
    file.open("matrix.txt");
    for(int i = 0 ; i < size; i++ )
    {
    	for(int j = 0 ; j < size; j++ )
    	{
    		file <<matrix[i][j]<<" ";
		}
		file<<endl;
	}
    
    return 0;
}
