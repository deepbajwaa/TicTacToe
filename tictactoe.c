/************************bajwaSimrandeepA3.c **************
Student Name: Simrandeep Bajwa
c File Name tictactoe.c Last Modified Date: November 28th, 2018
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
1) I have read and understood the University policy on academic
integrity;
2) I have completed the Computing with Integrity Tutorial on Moodle;
and
3) I have achieved at least 80% in the Computing with Integrity Self
Test.
I assert that this work is my own. I have appropriately acknowledged
any and all material (data, images, ideas or words) that I have used,
whether directly quoted or paraphrased. Furthermore, I certify that
this assignment was prepared by me specifically for this course.
**********************************************************/

/*********************************************************
 Compiling the program
*********************************************************
The program should be compiled using the following flags:
-std=c99
-Wall
compiling: gcc tictactoe.c -std=c99 -Wall -o tictactoe
*********************************************************
Running the Program
*********************************************************
running: ./tictactoe
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3

int isInputValid(int, int, int);
int isBoardFull(char [N][N]);
void createInitialBoard(char [N][N]);
void readUserMove(int *, int *);
void printCurrentBoard(char[N][N]);
int getComputerMove(char [N][N], int *, int *, int, int);
int gameWon(char [N][N], char);
int computerPlaysToWin(char [N][N], int * , int * );
void computerPlaysRandom(int * , int * , int , int );
void sumAllDimensions(char [N][N], int [N], int [N], int *, int *);
int memberOf(int , int [N]);
// you need the below prototype only if you attempt the bonus part
int computerPlaysToBlock(char [N][N], int * , int * );


int main(){

   int userRow, userCol, computerRow, computerCol;
   int taken;
   char board[N][N];
   char winner = 'N';

   srand(time(NULL));
    
   printf("This tic-tac-toe board is of size %d by %d\n", N, N);
   
   printf("Player symbol: X \n Computer symbol: O\n\n");

   printf("Here is the board - spaces are indicated by a ?\n");

   createInitialBoard(board);			// create a 3 X 3 board with '?' in each cell 
   
   while ((winner != 'Y') && !(isBoardFull(board))) // while there is no winner and the board is not full
   {	   
	   taken = 0;
	   
		while (!(taken))                  // loop used to accept valid row and col values from the user
		{
			readUserMove(&userRow, &userCol);                  //get user's move
			printf("You chose row %d and column %d \n", userRow, userCol);
			
			while (!isInputValid(userRow, 1, N) || !isInputValid(userCol, 1, N))     // validate user's move
			{
				printf("That's is an invalid row or column number - try again\n");
				readUserMove(&userRow, &userCol);
				printf("You chose row %d and column %d \n", userRow, userCol);
			}
				   
			if (board[userRow-1][userCol-1] == '?')           // if cell is unoccupied
			{
				board[userRow-1][userCol-1] = 'X';			// store an X there
				taken = 1;
			}
			else
			{
				taken = 0;									// otherwise inform the user to enter values again
				printf("That spot is taken - please try another one\n");
			}
			
		} //end of while (!taken)
	
	   if (gameWon(board, 'X'))   // check if the user wins - game will end if the user does win
	   {
		   printf("Congrats - you won against the computer :)\n");
		   winner = 'Y';
	   }
	   
	   else  if (!(isBoardFull(board)))            //check if the board is already full
	   {
		   taken = 0;
		   
		   while (!(taken))
		   {
				getComputerMove(board, &computerRow, &computerCol, userRow-1, userCol-1); // get computer's row and col
		   
				if (board[computerRow][computerCol] == '?')         // check if the cell is unoccupied
				{
					board[computerRow][computerCol] = 'O';
					taken = 1;
	
				}
				else
				{
					taken = 0;		//That spot is taken - computer - try another one
				}	
		   }
		   
		   printf("Computer chose row %d and column %d \n", computerRow+1, computerCol+1);
		   
		   if (gameWon(board, 'O'))               // check if the computer wins - game must end if it does
		   {
			   printf("Oh the computer won this time :(( think hard next time\n");
			   winner = 'Y';
		   }  
	   }
	 
	printCurrentBoard(board);  
	
	printf("\nPress enter to continue \n");             
	getchar();
		   
   } //end of while
   
   if (winner != 'Y')
			printf("Game was a tie - no winner!\n\n");

   return 0;
}


int  getComputerMove(char board[N][N], int * computerRow, int * computerCol, int userRow, int userCol){
/* 
  This function determines computer's move in terms of row (computerRow) and column (computerCol)
  and outputs them to main. The computer first tries to find a winning spot for itself; if it doesn't
  find one, then it calls function computerPlaysRandom in its attempt to place its symbol in
  the same row or column as the user (userRow, userCol)
*/

   int winningSpot = 0;
   int blocked = 1;            //this declaration is required if you attempt the bonus part
   
   winningSpot = computerPlaysToWin(board, computerRow, computerCol);

   if (!winningSpot)            // if computer does find a winning spot, then it plays to block the user 
   {
	   //computerPlaysRandom(computerRow, computerCol, userRow, userCol);
	   
	   /*
	   If you attempt the bonus part, then uncomment the code below and use it to first try and block user move
	   If unsuccessful, then it pick row and col (pseudo) randomly
	   */
	   
	   blocked = computerPlaysToBlock(board, computerRow, computerCol);
	   if (blocked == 0)
		   computerPlaysRandom(computerRow, computerCol, userRow, userCol);
	   
	   
   }
 
   return winningSpot;
}//end of getComputerMove


/******
  This function takes the variable entered, and determines if it is in between the
  minimum and maximum passed to the function. Then returns 1 if it is in between,
  otherwise it returns 0.
******/
int isInputValid(int entered, int minimum, int maximum)
{
   //check to see if the entered is between minimum and maximum
    if((entered>=minimum)&&(entered<=maximum))
    {
	return 1;
    }
    else
    {
        return 0;
    }

}//end of isInputValid

/******
  This function checks to see if the board is full or not.
  It returns 1 if it is full, otherwise it returns 0.
******/

int isBoardFull (char board [][N])
{
    //create 2 for loop to run through the array
    for(int rows = 0; rows < 3; rows++)
    {
        for(int cols = 0; cols < 3; cols++)
        {
	    //Use if else statement to see if the board is full or not
	    if(board[rows][cols]=='?')
            {
	        return 0;
            }
        }//close inner for loop

    }//close for loop

    //return 1 since the loop did not find any empty cell
    return 1;
}//end of isBoardFull

/******
  This function creates the intial board. It sets all the indexs of the board to
  '?', and it also prints the board.
******/

void createInitialBoard (char board [N][N])
{

    //Assigns each cell of the array with '?'
    for(int rows = 0; rows < 3; rows++)
    {
        for(int cols = 0; cols < 3; cols++)
        {
            board[rows][cols] = '?';
        }//close inner for loop

    }//close for loop

    //Print the initial board using a nested for loop
    for(int rows = 0; rows < 3; rows++)
    {
        for(int cols = 0; cols < 3; cols++)
        {
            //use if else to print out intial board correctly
	    if(cols<2)
            {
                printf("%c | ", board[rows][cols]);
	    }
            else
            {
                printf("%c", board[rows][cols]);
            }

        }//close inner for loop

	//use if statement to print out dashes
	if(rows<2)
	{
	    printf("\n----------\n");
	}
    }//close for loop
    printf("\n");
}//end of createInitialBoard

/******
  This function asks the user for the row and column that they would like
  to chose, and assigns it to the pointers passed to the function.
******/

void readUserMove (int * userRow, int * userCol)
{
    //prompt the user to enter a row and column value, and assign it to the pointers passed to the function
    printf("Your move - enter numbers between 1 and 3\n\n");
    printf("Enter row number:");
    scanf("%d", userRow);
    printf("Enter column number:");
    scanf("%d", userCol);
    printf("\n");

}//end of readUserMove

/******
  This function prints the current board using a nested for loop.
******/

void printCurrentBoard (char board [N][N])
{
    printf("\nCurrent board now is: \n");

    //Print the current board using a nested for loop
     for(int rows = 0; rows < 3; rows++)
    {
        for(int cols = 0; cols < 3; cols++)
        {
            //use if else to print out intial board correctly
            if(cols<2)
            {
                printf("%c | ", board[rows][cols]);
            }
            else
            {
                printf("%c", board[rows][cols]);
            }

        }//close inner for loop

        //use if statement to print out dashes
        if(rows<2)
        {
            printf("\n----------\n");
        }
    }//close for loop
    printf("\n");

}//end of PrintCurrentBoard

/******
  This function checks to see if there is a winner or not. The board and a symbol
  ('O' or 'X') is passed, and then it checks to see whether the computer or player
  has won. It returns 1 if there is a winner, otherwise it returns 0.
******/

int gameWon (char board [N][N], char symbol)
{

    //declare variables
    int counter, winner;

    //initalize variables
    counter = 2;

    //Check to see if symbol is an X or O
    if(symbol == 'X')
    {
	//set winner to 0;
	winner = 0;

        //Check diagonal from left to right using a loop
	for(int i = 0; i < 3; i++)
        {
            if(board[i][i] == 'X')
	    {
                winner+=1;
            }
        }//close for loop

	//check for win
	if(winner==3)
	{
	    return 1;
	}

	//reset winner to 0
	winner = 0;

        //Check diagonal from right to left
	for(int i = 0; i < 3; i++)
        {
            if(board[i][counter] == 'X')
            {
                winner += 1;
            }
	    counter -=1;
        }//close for loop

	//check for win
        if(winner==3)
        {
            return 1;
        }

	//reset winner to 0
	winner = 0;


	//Check the rows using a nested for loop
	for(int rows = 0; rows < 3; rows++)
        {
	    for(int cols = 0; cols < 3; cols++)
            {
                if(board[rows][cols] == 'X')
                {
                    winner += 1;
                }
            }//close inner for loop

	    //check for win
            if(winner==3)
            {
                return 1;
            }

	    //reset winner to 0 here otherwise the sum will continue to the next row
            winner = 0;

        }//close for loop

	//reset winner to 0
        winner = 0;

	//Check the cols using a nested for loop
	for(int cols = 0; cols < 3; cols++)
        {
            for(int rows = 0; rows < 3; rows++)
            {
                if(board[rows][cols] == 'X')
                {
                    winner += 1;
                }

            }//close inner for loop

	    //Check for a win
	    if(winner == 3)
            {
                return 1;
            }
	    //set winner to 0 to make sure that the sum doesn't continue to the next column
            winner = 0;

        }//close for loop

	//Since the player didn't win return 0
        return 0;


    }//if
    else if(symbol == 'O')
    {
        //set winner to 0;
        winner = 0;

        //Check diagonal from left to right using a loop
        for(int i = 0; i < 3; i++)
        {
            if(board[i][i] == 'O')
            {
                winner+=4;
            }
        }//close for loop

        //check for win
        if(winner==12)
        {
            return 1;
        }
	//reset winner to 0
        winner = 0;

        //Check diagonal from right to left
        for(int i = 0; i < 3; i++)
        {
            if(board[i][counter] == 'O')
            {
                winner += 4;
            }
            counter -=1;
        }//close for loop

	//check for win
        if(winner==12)
        {
            return 1;
        }

        //reset winner to 0
        winner = 0;

	//Check the rows using a nested for loop
        for(int rows = 0; rows < 3; rows++)
        {
            for(int cols = 0; cols < 3; cols++)
            {
                if(board[rows][cols] == 'O')
                {
                    winner += 4;
                }
            }//close inner for loop

            //check for win
            if(winner==12)
            {
                return 1;
            }

            //reset winner to 0 to make sure the sum doesn't continue to the next row
            winner = 0;
	}//close for loop

        //reset winner to 0
        winner = 0;

	//Check the cols using a nested for loop
        for(int cols = 0; cols < 3; cols++)
        {
            for(int rows = 0; rows < 3; rows++)
            {
                if(board[rows][cols] == 'O')
                {
                    winner += 4;
                }

            }//close inner for loop

            //Check for a win
            if(winner == 12)
            {
                return 1;
            }
	    //reset winner to 0 to make suer that the sum doesn't continue to the next column
            winner = 0;

        }//close for loop

        //Since the computer didn't win return 0
        return 0;

    }
    //if a symbol other than 'O' or 'X' is entered
    else
    {
	return 0;
    }//end of if - else statement

}//end of gameWon

/******
  This function checks to see if any of the rows, Columns, or diagonals
  contain 2 Os. If it does, then it will set the pointers set to an empty space in that row, column, or diagonal if possible.
  Then it will return 1 if the computer wins in this step, otherwise it returns 0.
******/
int computerPlaysToWin (char board [N][N], int * cRow, int * cCol)
{
    //Declare variables
    int sum, randomNum, whileCount, diagonalCounter;

    //Variables for while loops that check to see if they can find an empty place on the board
    int rDCounter, rowCounter, colCounter;

    //initialize variables
    sum = 0;
    randomNum = 0;
    whileCount = 1;
    diagonalCounter = 2;
    rDCounter = 0;
    rowCounter = 0;
    colCounter = 0;

    //Check diagonal from left to right using a loop
    for(int i = 0; i < 3; i++)
    {
        if(board[i][i] == 'O')
        {
            sum += 4;
        }
    }//close for loop

    //check to see if there are 2 Os
    if(sum == 8)
    {
	//Check to see if a place that is not occuplied by an O can be found on the diagonal
        while( (board[randomNum][randomNum] == 'O') && (whileCount < 4) )
	{
	    randomNum +=1;
	    whileCount++;
	}
	//if the spot is empty then return the spot to the pointers
	if(board[randomNum][randomNum] == '?')
	{
	    *cCol = randomNum;
            *cRow = randomNum;
            return 1;
	}
    }//outer if

    //reset variables
    sum = 0;
    whileCount = 1;

    //Get the sum from the amount of Os in the Right diagonal
    for(int i = 0; i < 3; i++)
    {
        if(board[i][diagonalCounter] == 'O')
        {
            sum += 4;
        }
        diagonalCounter -=1;
    }//close for loop

    //reset diagonalCounter
    diagonalCounter = 2;

    //Check to see if there are two Os
    if(sum == 8)
    {
	//Keep running through the right diagonal until it finds an empty space
        while( (board[rDCounter][diagonalCounter] == 'O') && (whileCount < 4) )
        {
            rDCounter +=1;
	    diagonalCounter -=1;
            whileCount++;
        }
	//if that spot found is empty then set the pointers accordingly and return 1 for a win
        if(board[rDCounter][diagonalCounter] == '?')
        {
            *cCol = diagonalCounter;
            *cRow = rDCounter;
            return 1;
        }//inner if
    }//outer if

    //reset variables
    sum = 0;
    whileCount = 1;

    //Get the sum of the Os in the rows
    for(int rows = 0; rows < 3; rows++)
    {
        for(int cols = 0; cols < 3; cols++)
        {
            if(board[rows][cols] == 'O')
            {
                sum += 4;
            }
        }//close inner for loop

        //check to see if there are two Os
        if(sum==8)
        {
	    //Keep running through the row until it finds an empty space
            while( (board[rows][rowCounter] == 'O') && (whileCount < 4) )
            {
                rowCounter +=1;
                whileCount++;
            }
            //if that spot found is empty then set the pointers accordingly and return 1 for a win
            if(board[rows][rowCounter] == '?')
            {
                *cCol = rowCounter;
                *cRow = rows;
                return 1;
            }
        }//close outer if

	//reset sum
        sum = 0;

    }//close for loop

    //Reset variables
    whileCount = 1;
    sum = 0;

    //Get the sum of the Os in the columns
    for(int rows = 0; rows < 3; rows++)
    {
        for(int cols = 0; cols < 3; cols++)
        {
            if(board[cols][rows] == 'O')
            {
                sum += 4;
            }
        }//close inner for loop

        //check to see if there are two Os
        if(sum==8)
        {
            //Keep running through the row until it finds an empty space
            while( (board[colCounter][rows] == 'O') && (whileCount < 4) )
            {
                colCounter +=1;
                whileCount++;
            }
            //if that spot found is empty then set the pointers accordingly and return 1 for a win
            if(board[colCounter][rows] == '?')
            {
                *cCol = rows;
                *cRow = colCounter;
                return 1;
            }
        }//close outer if

        //reset sum
        sum = 0;

    }//close for loop

    //If the computer can't win in the step return 0
    return 0;
}//end of computerPlaysPlayer

/******
  This function will try to return an index to set to 'O' to the pointers,
  which is either the same row, column, or diagonal as the user's.

******/

void computerPlaysRandom (int * cRow, int * cCol, int uRow, int uCol)
{

    //Declare variables
    int randomNum;
    int randomNum2;
    int randomNum3;
    int counter, counter2, counter3, counter4;
    int leftDiagonalRow, leftDiagonalCol;
    int rightDiagonalRow, rightDiagonalCol;

    //initialize variables
    randomNum = 0;
    randomNum2 = 0;
    randomNum3 = 0;

    counter = 0;
    counter2 = 0;
    counter3 = 0;
    counter4 = 0;

    leftDiagonalRow = 0;
    leftDiagonalCol = 0;
    rightDiagonalRow = 0;
    rightDiagonalCol = 2;

    //Seed the program
    srand((int)time(0));

    //Generate a random Number
    randomNum = rand()%3;

    //depending on if the random was 0,1, or 2 return a move in the same row, column, or diagonal
    if(randomNum == 0)
    {
	//check to see that the same value as the user is returned and  limits the generation of a random number to 5 times to prevent an infinite loop
	while( (uCol == randomNum2) && (counter < 5) )
	{
	    randomNum2 = rand()%3;
	    counter++;
	}

	//return a spot in the same row as long as the counter hasnt ran more than 5 times, and if so then a random spot is returned
	if(counter <  5)
	{
	    *cRow = uRow;
            *cCol = randomNum2;
	}
	else
	{
	    *cRow = rand()%3;
	    *cCol = rand()%3;
	}
    }
    else if(randomNum == 1)
    {
	//check to see that the same value as the user is returned and  limits the generation of a random number to 5 times to prevent an i$
        while( (uRow == randomNum2) && (counter < 5) )
        {
            randomNum2 = rand()%3;
            counter2++;
        }

        //return a spot in the same column as long as the counter hasnt ran more than 5 times, and if so then a random spot is returned
        if(counter2 <  5)
        {
            *cRow = randomNum2;
            *cCol = uCol;
        }
        else
        {
            *cRow = rand()%3;
            *cCol = rand()%3;
        }
    }
    else
    {
	//if the user's move is in the left diagonal
	if( ( (uRow == 0) && (uCol == 0) ) || ( (uRow == 2) && (uCol == 2) ) || ( (uRow == 1) && (uCol == 1) ) )
	{
	    //run a loop until the computer's row and column chosen is not the same as the user's, and limit the loop to run a maximum of 5 times to prevent an infinite loop
	    while((((uRow == leftDiagonalRow) && (uCol == leftDiagonalCol))||((uRow == leftDiagonalRow)&&(uCol == leftDiagonalCol))) && (counter3 < 5) )
            {
                randomNum3 = rand()%3;
                counter3++;
		//assigns a spot on the left diagonal depending on the random number generated
                if(randomNum3 == 0 )
                {
                    leftDiagonalRow = 0;
                    leftDiagonalCol = 0;
                }
                else if(randomNum3 == 1)
                {
                    leftDiagonalRow = 1;
                    leftDiagonalCol = 1;
                }
                else
                {
                    leftDiagonalRow = 2;
                    leftDiagonalCol = 2;
                }
            }//end of while

	    //return the spot found otherwise if the loop reached its 5 itterations limit return a random spot
	    if(counter3 <  5)
            {
                *cRow = leftDiagonalRow;
                *cCol = leftDiagonalCol;
            }
            else
            {
                *cRow = rand()%3;
                *cCol = rand()%3;
            }


	}
	//if the user's move is on the right diagonal
	else if( ( (uRow == 0) && (uCol == 2) ) || ( (uRow == 2) && (uCol == 0) ) || ( (uRow == 1) && (uCol == 1) ) )
        {
	    //run a loop until the computer's row and column chosen is not the same as the user's, and limit the loop to run a maximum of 5 times to prevent an infinite loop
            while((((uRow == rightDiagonalRow) && (uCol == rightDiagonalCol))||((uRow == rightDiagonalRow)&&(uCol == rightDiagonalCol))) && (counter4 < 5) )
	    {
		randomNum3 = rand()%3;
		counter4++;
		//assign the computer's move to a spot on the right diagonal depending on the random number generated
		if(randomNum3 == 0 )
		{
		    rightDiagonalRow = 0;
		    rightDiagonalCol = 2;
		}
		else if(randomNum3 == 1)
		{
		    rightDiagonalRow = 1;
                    rightDiagonalCol = 1;
		}
		else
		{
		    rightDiagonalRow = 2;
                    rightDiagonalCol = 0;
		}
	    }//end of while


	    //return the spot found otherwise return a random spot if the loop had to run more than the limited 5 times
	    if(counter4 < 5)
	    {
		*cRow = rightDiagonalRow;
		*cCol = rightDiagonalCol;
	    }
	    else
	    {
		*cRow = rand()%3;
                *cCol = rand()%3;
	    }

	}//end of inner if

    }//close of outer if


}//close of computerPlaysRandom

/******
  This function gets the sum of all the rows, colums, and diagonals.
  Then it sets these scores to the arrays and pointer passed to the
  function.
******/

void sumAllDimensions (char board [N][N], int sumR[N], int sumC[N], int * sumLD, int *sumRD)
{
    //declare variables
    int counter;

    //initalize variables
    counter = 2;

    //Get the sum of the left diagonal
    for(int i = 0; i < 3; i++)
    {
	//add 4 if theres an O otherwise add 1 for an X, and add nothing for a ?
        if(board[i][i] == 'O')
        {
            *sumLD+=4;
        }
	else if(board[i][i] == 'X')
	{
	    *sumLD+=1;
	}
    }//close for loop

    //Get sum of the right diagonal
    for(int i = 0; i < 3; i++)
    {
	//add 4 if theres an O otherwise add 1 for an X, and add nothing for a ?
        if(board[i][counter] == 'O')
        {
            *sumRD += 4;
        }
	else if(board[i][counter] == 'X')
        {
            *sumRD+=1;
        }
        counter -=1;

    }//close for loop


    //Get sum of rows
    for(int rows = 0; rows < N; rows++)
    {
	for(int cols = 0; cols < N; cols++)
	{
	    if(board[rows][cols]=='X')
	    {
		sumR[rows] += 1;
	    }
	    else if(board[rows][cols]=='O')
            {
		sumR[rows] += 4;
	    }
	}//close inner for loop

    }//close outer for loop

    //Get sum of columns
    for(int rows = 0; rows < N; rows++)
    {
        for(int cols = 0; cols < N; cols++)
        {
            if(board[cols][rows]=='X')
            {
                sumC[rows] += 1;
            }
            else if(board[cols][rows]=='O')
            {
                sumC[rows] += 4;
            }
        }//close inner for loop

    }//close outer for loop

}//end of sumAllDimensions

/******
  This function checks to see if aNum is inside an array that is passed to the function
  called someArray.
******/

int memberOf (int aNum, int someArray [N])
{
    //use a for loop to run through the array
    for(int i = 0; i < 3; i++)
    {
	//Check to see if aNum is at the certain index, and return 1 if it is
        if(someArray[i] == aNum)
	{
	    return 1;
	}//close if else statement

    }//close for loop

    //return 0 since aNum was not found in someArray
    return 0;
}//close memberOf

/******
  This function checks to see if any of the rows, columns, or diagonals
  contain 2 Xs. If it does, then it will set the pointers set to an empty spot in that row, column, or diagonal if possible.
  Then it will return 1 if the computer can block the player, otherwise it returns 0.
******/

int computerPlaysToBlock (char board[N][N], int * cRow, int * cCol)
{

    //Declare variables
    int sum, randomNum, whileCount, diagonalCounter;

    //Variables for while loops that check to see if they can find an empty place on the board
    int rDCounter, rowCounter, colCounter;

    //initialize variables
    sum = 0;
    randomNum = 0;
    whileCount = 1;
    diagonalCounter = 2;
    rDCounter = 0;
    rowCounter = 0;
    colCounter = 0;

    //Check diagonal from left to right using a loop to calculate the amount of Xs in the diagonal
    for(int i = 0; i < 3; i++)
    {
        if(board[i][i] == 'X')
        {
            sum += 1;
        }
    }//close for loop

    //check to see if there are 2 Xs
    if(sum == 2)
    {
	//Check to see if a place that is not occupied by an X can be found on the diagonal
        while( (board[randomNum][randomNum] == 'X') && (whileCount < 4) )
	{
	    randomNum +=1;
	    whileCount++;
	}
	//if the spot is empty then return the spot to the pointers to block the player
	if(board[randomNum][randomNum] == '?')
	{
	    *cCol = randomNum;
            *cRow = randomNum;
            return 1;
	}
    }//outer if

    //reset variables
    sum = 0;
    whileCount = 1;

    //Get the sum from the amount of Xs in the Right diagonal
    for(int i = 0; i < 3; i++)
    {
        if(board[i][diagonalCounter] == 'X')
        {
            sum += 1;
        }
        diagonalCounter -=1;
    }//close for loop

    //reset diagonalCounter
    diagonalCounter = 2;

    //Check to see if there are two Xs
    if(sum == 2)
    {
	//Keep running through the right diagonal until it finds an empty space
        while( (board[rDCounter][diagonalCounter] == 'X') && (whileCount < 4) )
        {
            rDCounter +=1;
	    diagonalCounter -=1;
            whileCount++;
        }
	//if that spot found is empty then set the pointers accordingly and return 1 for a block
        if(board[rDCounter][diagonalCounter] == '?')
        {
            *cCol = diagonalCounter;
            *cRow = rDCounter;
            return 1;
        }//inner if
    }//outer if

    //reset variables
    sum = 0;
    whileCount = 1;

    //Get the sum of the Xs in the rows
    for(int rows = 0; rows < 3; rows++)
    {
        for(int cols = 0; cols < 3; cols++)
        {
            if(board[rows][cols] == 'X')
            {
                sum += 1;
            }
        }//close inner for loop

        //check to see if there are two Xs
        if(sum==2)
        {
	    //Keep running through the row until it finds an empty space
            while( (board[rows][rowCounter] == 'X') && (whileCount < 4) )
            {
                rowCounter +=1;
                whileCount++;
            }
            //if that spot found is empty then set the pointers accordingly and return 1 for a block
            if(board[rows][rowCounter] == '?')
            {
                *cCol = rowCounter;
                *cRow = rows;
                return 1;
            }
        }//close outer if

	//reset sum to 0
        sum = 0;
    }//close for loop

    //Reset variables
    whileCount = 1;
    sum = 0;

    //Get the sum of the Xs in the columns
    for(int rows = 0; rows < 3; rows++)
    {
        for(int cols = 0; cols < 3; cols++)
        {
            if(board[cols][rows] == 'X')
            {
                sum += 1;
            }
        }//close inner for loop

        //check to see if there are two Xs
        if(sum==2)
        {
            //Keep running through the column until it finds an empty space
            while( (board[colCounter][rows] == 'X') && (whileCount < 4) )
            {
                colCounter +=1;
                whileCount++;
            }
            //if that spot found is empty then set the pointers accordingly and return 1 for a block
            if(board[colCounter][rows] == '?')
            {
                *cCol = rows;
                *cRow = colCounter;
                return 1;
            }
        }//close outer if

        //reset sum
        sum = 0;
    }//close for loop

    //If the computer can't block the player return 0
    return 0;

}//end of computerPlaysToBlock



