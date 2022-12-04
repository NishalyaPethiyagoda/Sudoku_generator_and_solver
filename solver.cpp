#include <iostream>
#include <fstream> 
#include <vector>
using namespace std;

const int size = 9;
 
/* 
function process: condition checking.
	condition 1: whether it is correct to input a number to a certain row
	condition 2: whether it is correct to input a number to a certain column
	condition 3: whether it is correct to input a certain number to a specific 3 byb 3 grid 
	
	inputs:- matrix[][], size, row & column that is checked
	output:- boolean output:  if all conditions are correct -> true    
	                          else                          -> false
*/
bool conditions_correct(vector <vector<int>> &matrix, int row, int col, int value)
{
    for (int x = 0; x <= 8; x++)   // if, adding value already exists in another column of that row -> return false
    {
    	if ( matrix[row][x] == value)
            return false;
	}    
 
    for (int x = 0; x <= 8; x++)   // if, adding value already exists in another row of that column -> return false
    {
    	if ( matrix[x][col] == value)
            return false;
	}
                                   
    int start_row = row - row % 3 , start_col = col - col % 3 ; // start column and row indices of that 3 by 3 matrix    
   
    for (int i = 0; i < 3; i++)   // if, adding value already exists within that specific 3 by 3 matrix ->return false
    {
    	for (int j = 0; j < 3; j++)
    	{
 			if ( matrix[i + start_row ][j + start_col] == value)
 			
            return false;
		}
	}           
    return true ;                // else if all conditions are valid -> return true 
}

 
/* 
function process: generating sudoku puzzle solution by inserting correct values.

	inputs:- matrix[][], size, starting row, starting column 
	output:- boolean output:  if puzzle fully solvable  -> true    
	                          else                      -> false	
 */
bool solver_funct(vector <vector<int>> &matrix, int row, int col)
{   
    if (row == size - 1 && col == size) // if, 8th row and 9th column reached, avoid backtracking -> return true 
        return true;
 
    if (col == size)              // when last column reached, move 1st column of next row
	{
		col = 0;
        row++;     
    }
    
    if (matrix[row][col] > 0)      // if existing value is not zero, move to nxt column
    {
       	return solver_funct(matrix, row, col + 1);
	}
 
    for (int value = 1; value <= size; value++)
    {     
        if ( conditions_correct(matrix, row, col, value) )   //checking for correctness of a certain inserted value
        {
            matrix[row][col] = value;
           
            if (solver_funct(matrix, row, col + 1))
            {
            	return true;
			}    
        }
        matrix[row][col] = 0;     // re-assigning 0 unless condition is true
    }
    return false;      
}

/* 
function process: printing solved sudoku puzzle on console
	inputs:- matrix[][]
	output:- none
*/

void display_solution(vector <vector<int> > &matrix)
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

 
//main function
int main()
{
	int temp;
	
	vector <vector<int>> matrix;
		
	ifstream file2;           //inputing generated puzzle in a text file to 2D array
	file2.open("matrix.txt");
	for (int i = 0 ; i <9 ; i++ )
	{
		vector <int> temp_vec;
		
		for(int j = 0 ; j < 9 ;j++)
		{
			file2>>temp ;
			temp_vec.push_back(temp);
		}	
		matrix.push_back(temp_vec);
	}

	
	
    if (solver_funct( matrix, 0, 0) )   //calling solver_funct
    {
    	display_solution(matrix);
	}            
    else
    {
    	cout << "sudoku puzzle not solvable" << endl;
	}
    
    return 0;
}
