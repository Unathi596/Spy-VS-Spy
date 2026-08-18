#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>

import libSpace;

using namespace std;
using namespace SkySpace;

int main(int argc, char** argv)
{
	// Seed
	srand(time(nullptr));
	
	// Check if argument count is valid
	if(argc != NUM_ARGS)
	{
		cerr << "Invalid number of arguments" << endl;
		exit(ERROR_NUM_ARGS);
	}
	
	// Read Command-Line Arguments
	int intRows = ConvertArgToInt(argv[1]);
	int intCols = ConvertArgToInt(argv[2]);
	
	// Allocation
	GameWorld recGameWorld{};
	Allocation(recGameWorld, intRows, intCols);
	
	// Initialisation
	Initialisation(recGameWorld);
	
	// Variables that will track the loop
	char chMove = '\0';
	bool blnContinue = true;
	
	do
	{
		// Display
		Display(recGameWorld);
		cin >> chMove;
		
		switch(tolower(chMove))
		{
			case 'w':
			{
				MovePlayer(recGameWorld, UP);
			}
			
				break;
				
			case 's':
			{
				MovePlayer(recGameWorld, DOWN);
			}
			
				break;
				
			case 'a':
			{
				MovePlayer(recGameWorld, LEFT);
			}
			
				break;
				
			case 'd':
			{
				MovePlayer(recGameWorld, RIGHT);
			}
			
				break;
			
			case 'x':
			{
				blnContinue = false;
				cout << "You have decided to quit the game" << endl;
			}
			
				break;
				
			default:
			{
				cerr << "You have chosen the wrong character!! Please try again!!" << endl;
				system("pause");
			}
		}
		
	}while(blnContinue == true);
	
	// Indicate successfull termination of program
	cout << "Program has ran successfully" << endl;
	return SUCCESS;
}