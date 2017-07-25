/*                                                                 assign11.cc
 * PROGRAM: n_queens ( N- Queens problem )
 * PROGRAMMER: Michael Wight
 * date: 5/2/2016
 *
 *****************************************************************************/

  //include statements
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <time.h>
  //using statements
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::srand;
using std::rand;

  //function prototypes
void initBoard(vector< vector<bool> > board);
void solveNQueens(int size);
bool solveNQueensUtil(vector< vector<bool> > & board, int);
bool isSafe(vector< vector<bool> >, int, int);
void printBoard(vector< vector<bool> >);

  //////                                                                  main()
int main()
{
	bool notDone = false;
	char b;

	    // Prompts the user for a number to represent 'N'.
	    // Will keep asking for more numbers until the user
	    // indicates otherwise.
	while (notDone == false)
	{
	   int c;

	   cout << " Type a number for 'N'." << endl;
	   cout << " 'N' represents the size of an \"N x N\" " << endl;
	   cout << " chessboard and possible queens to be placed:" << endl << endl;

	   cin >> c;
 	   solveNQueens(c);

	   cout << " Would you like to try another number for 'N'?" << endl << "Y = yes, N = no" << endl;
	   cin >> b;

 	   if (b == 'y' || b == 'Y')
	   {  notDone = false; }
	   else
	   {  notDone = true; }
	}

	return 0;
}



    ////// function definitions ///////
/*								initBoard()
   Objective:
	This function takes a vector of vector of bools. The function initializes
	and seeds the random number generator. It will iterate through the vector
	and initializes all values to an initial value of false.
 *****************************************************************************/
void initBoard(vector< vector<bool> > board)
{
   const int SIZE = board.size()-1;
   srand((int)time(0));

   for (int y = 0; y < SIZE; y++)
   {
      for (int x = 0; x < SIZE; x++)
      {
	  board[y][x] = false;
      }
   }
}


/*								solveNQueens()
   Objective:
	This function initializes a vector of bools and sizes it to the size
	of the NxN board. It then initializes the baord with a randomly generated
	number. Next it calls the solveNQueenUtil() function; if it comes back true
	it will print the processed board values else it will print out an error
	message.
 *****************************************************************************/
void solveNQueens(int size)
{
    int numOfColumns = size;
    int numOfRows = size;


	  // creates a vector of "size" vector with each containing "size"
          // bools with the value of "false"
     vector < vector<bool> > newBoard;
     newBoard.resize(numOfRows, vector<bool>(numOfColumns, false));


          //initialize the board and random number generator
     initBoard(newBoard);

     cout << "Below is the possible output for N = " << size << endl << endl;
     cout << "N = " << size << endl;


	   //process the board and if true, will print out the board
     if( solveNQueensUtil(newBoard, 0))
     {
     	 printBoard(newBoard);
     }
     else
     {
   	 cout << "ERROR: A solution does not exist..." << endl;
     }
}


/*								solveNQueensUtil()
   Objective:
	This function takes a board and int "row" position. The row indicates the starting
	row, while the column position is determined by a randomly generated number.
	The function will index through the board within the row and call "isSafe()" to
	determine if a queen can be placed in that location. If safe, a queen will be placed
	and this function will be recursively called, using row + 1 as the starting row
	of the next call. If the recursive call returns false, the queen will be removed
	and the for loop will cycle through the indexes until all columns have been checked.

 *****************************************************************************/
bool solveNQueensUtil( vector< vector<bool> > &board, int row )
{
   const int SIZE = board.size();				 //initialize size variable
   int colStart = rand() % (board.size()) + 1 ; //create rand num between 1 and board size
   int j = 0;                                   //for wrap around


   if (row >= SIZE) //base case for recursion
       return true; //if all queens are placed: return true.


		   // Will increment "j" for as many times as there are columns in a row (maxInc)
		   // wrapping around back to index 0 if necessary.
		   // will break if queen is placed else it will try the next space
   for (int maxInc = 0; maxInc < SIZE; maxInc++ )
   {
       j = colStart; //set column to generated number

       if (j == SIZE) //for wrapping around the end of the vector
	  j = 0;

       if ( isSafe( board, row, j) )
       {
           board[row][j] = 1; //place queen on board

           if (solveNQueensUtil(board, row + 1)) //recursively call to place rest of queens
           {
              return true;
           }
		  // if placing queens doesnt lead to solution then queen's removed
		  // will cycle through for loop to next index and try again.
		board[row][j] = 0;
		j++;
        }
     }

	  //if queen can not be placed in any row of this column then:
	return false;
}


/*								       isSafe()
   Objective:
	This function takes a boad and int value for row and column. The function
	checks if the queen can be placed in the given row and column on the board.
	if yes, then it returns true.

 *****************************************************************************/
bool isSafe(vector< vector<bool> > board, int row, int column)
{
	const int SZ = board.size() - 1;
	int i = 0, j = 0;


	    //check horizontal right
	 for (i = column + 1; i <= SZ; i++)
	 {
	     if (board[row][i])
		 return false;
	 }

            //check horizontal left
	 for (i = column - 1; i >= 0; i--)
	 {
	     if (board[row][i])
		 return false;
	 }


	     //check vertical up
	 for (i = row - 1; i >= 0; i--)
	 {
	     if (board[i][column])
		 return false;
	 }

	     //check vertical down
	 for (i = row + 1; i <= SZ; i++)
	 {
	     if (board[i][column])
		 return false;
	 }


	     //check diagonal up-right movement
	 for ( i = row - 1, j = column + 1; i >= 0 && j < SZ ; i--, j++ )
	 {
	     if(board[i][j])
	         return false;
	 }

	     //check diagonal up-left
	 for ( i = row - 1 , j = column - 1 ; i >= 0 && j >= 0 ; i--, j-- )
	 {
	     if(board[i][j])
   		 return false;
	 }

	    //check diagonal down-right
	 for ( i = row + 1, j = column + 1; i < SZ && j < SZ ; i++, j++ )
	 {
	     if(board[i][j])
    	 	 return false;
         }


	    //check diagonal down-left
	 for ( i = row + 1, j = column - 1; i < SZ && j >= 0 ; i++, j-- )
	 {
	     if(board[i][j])
    		  return false;
	 }

     return true;
}


/*
   Objective:
	This function takes a board argument. When called, this function
	will print out the details of an NxN board
 *****************************************************************************/
void printBoard(vector< vector<bool> > board)
{
    const int BOARD_SZ = board.size();
    const int COLUMN_HEIGHT = 4;
    const int BOARD_WIDTH = board[0].size();

    for (int i = 0; i < BOARD_SZ; i++)
    {
	for ( int x = 0; x < COLUMN_HEIGHT; x++)
	{
	   for(int j = 0; j < BOARD_WIDTH; j++)
	   {
   	       if ( x == 0)
	       {
	   	   if (j == 0 && j == BOARD_WIDTH-1)
		   {  cout << " +-----"; }
		   else if (j == 1)
		   {  cout << "+-----"; }
		   else if (j == BOARD_WIDTH-1)
		   {  cout << "+-----+"; }
		   else
		   { cout << "+-----"; }
	       }
	       else if (x == 1)
	       {
		   cout << "|     ";
  	           if ( j == BOARD_WIDTH-1)
		   {
                       cout << "|";
                   }
	       }
	       else if (x == 2)
	       {
	           if (board[i][j] == false)
		   {
                       cout << "|     ";
		       if (j == BOARD_WIDTH - 1)
		         {
                            cout << "|";
                         }
		   }
	           else
		   {
		        cout << "|  " << "Q" << "  ";
		        if (j == BOARD_WIDTH - 1)
			{
                            cout << "|";
                        }
	           }
	       }
	       else if ( x == 3)
	       {
		   cout << "|     ";
		   if ( j == BOARD_WIDTH-1)
		   {   cout << "|"; }
	       }
            }
            cout << endl;
         }
     }

    for (int j = 0; j < BOARD_SZ; j++)
    {
       if (j == 0 && j == BOARD_SZ - 1)
       {
           cout << "+----+ ";
       }
       else if (j == 0)
       {
           cout << "+-----";
       }
       else if (j == BOARD_SZ - 1)
       {
           cout << "+-----+";
       }
       else
       {
           cout << "+-----";
       }
    }

    cout << endl;
}

