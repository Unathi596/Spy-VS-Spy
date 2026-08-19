module; // Gloibal Module Fragment

#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>
#include <sstream>

export module libSpace;

namespace SkySpace
{
	// Constants
	export const int NUM_ARGS = 3;
	const char ARR_FEATURES[7] = {'.','P','|','^','v','$','#'};
	
	// Enum for error handling
	export enum Status
	{
		SUCCESS,
		ERROR_CONVERSION,
		ERROR_NUM_ARGS,
		UNDEFINED_BEHAVIOR
	};
	
	// Enum for Player movement
	export enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	
	// Enum for Features
	enum FEATURE
	{
		EMPTY_SPACE,
		PLAYER,
		WALL,
		SENTRY_MOVING_UP,
		SENTRY_MOVING_DOWN,
		STARTING_BLOCK,
		ENDING_BLOCK
	};
	
	// Alias
	using TwoDimArray = FEATURE**;
	using OneDimArray = FEATURE*;
	
	// Record structure that tracks the position of the sentry
	struct Sentry
	{
		// Dimesions 
		int intSRow;
		int intSCol;
	};
	
	// Record Structure for the GameWorld
	export struct GameWorld
	{
		// Player position
		int intPRow;
		int intPCol;
		
		// Dimesions fo the game
		int intRows;
		int intCols;
		
		// An Array for Sentries
		int intNumSentries;
		Sentry* arrSentry;
		
		// Walls
		int intNumWalls;
		
		// A Two-Dimensional Array for the gameworld
		TwoDimArray arrGame;
	};
	
	// Pseudo random number generator
	int GetRandom(int intLow, int intHigh)
	{
		int intRange = (intHigh - intLow) + 1;
		return (rand() % intRange) + intLow;
	}
	
	// Convert Command-Line argument to an integer
	export int ConvertArgToInt(std::string strArg)
	{
		// Declare stringstream
		std::stringstream ssConv(strArg);
		
		// Conversion
		int intValue = 0;
		ssConv >> intValue;
		
		// Check
		if(ssConv.fail())
		{
			std::cerr << "Cannot convert argument " << strArg << " to an integer." << std::endl;
			exit(ERROR_CONVERSION);
		}
		
		return intValue;
	}
	
	// Memory Allocation
	export void Allocation(GameWorld& recGameWorld, int intRows, int intCols)
	{
		// Assigning
		recGameWorld.intRows = intRows;
		recGameWorld.intCols = intCols;
		
		// Allocate memory for GameWorld
		recGameWorld.arrGame = nullptr;
		recGameWorld.arrGame = new OneDimArray[recGameWorld.intRows];
		for(int r = 0; r < recGameWorld.intRows; r++)
		{
			recGameWorld.arrGame[r] = new FEATURE[recGameWorld.intCols];
		}
		
	}
	
	// Initialisation
	export void Initialisation(GameWorld& recGameWorld)
	{
		// EMPTY_SPACE
		for(int r = 0; r < recGameWorld.intRows; r++)
		{
			for(int c = 0; c < recGameWorld.intCols; c++)
			{
				recGameWorld.arrGame[r][c] = EMPTY_SPACE;
			}
		}
		
		// Place Starting and ending blocks
		for(int r = 0; r < recGameWorld.intRows; r++)
		{
			recGameWorld.arrGame[r][0] = ENDING_BLOCK; // Ending blocks is in the first coloumn 
			recGameWorld.arrGame[r][recGameWorld.intCols - 1] = STARTING_BLOCK; // Starting blocks is in the last coloumn
		}
		
		// Place Player
		recGameWorld.intPRow = GetRandom(0, recGameWorld.intRows - 1);
		recGameWorld.intPCol = recGameWorld.intCols - 1;
		recGameWorld.arrGame[recGameWorld.intPRow][recGameWorld.intPCol] = PLAYER; // Player is placed on the last coloumn on a random row
		
		// Place Walls
		for(int r = 0; r < recGameWorld.intRows; r++)
		{
			for(int c = 1; c < recGameWorld.intCols - 1; c++) 
			{
				if(c % 2 == 0) // For an even column
				{
					recGameWorld.arrGame[r][c] = WALL; // Wall placed on an even column
				}
			}
			
		}
		
		// An empty space on a column that has a wall
			for(int c = 1; c < recGameWorld.intCols - 1; c++)
			{
				if(c % 2 == 0) // For an even column
				{
					int intRandRow = GetRandom(0, recGameWorld.intRows - 1);
					recGameWorld.arrGame[intRandRow][c] = EMPTY_SPACE;
				}
			}
			
			// Place Sentry
			for(int c = 1; c < recGameWorld.intCols - 1; c++)
			{
				if(c % 2 != 0) // For an odd column
				{
					// Variables that genrates a random row and sentry(up/down)
					int intRandRow = GetRandom(0, recGameWorld.intRows - 1);
					int intRandSentry = GetRandom(0,1);
					
					switch(intRandSentry)
					{
						case 0:
						{
							recGameWorld.arrGame[intRandRow][c] = SENTRY_MOVING_DOWN;
							recGameWorld.intNumSentries++;
						}
						
							break;
							
						case 1:
						{
							recGameWorld.arrGame[intRandRow][c] = SENTRY_MOVING_UP;
							recGameWorld.intNumSentries++;
						}
						
							break;
							
						default:
						{
							std::cerr << "Somehow!! A wrong number is generated!!" << std::endl;
							exit(UNDEFINED_BEHAVIOR);
						}
					}
					
				}
			}
	}
	
	// Display GameWorld
	export void Display(const GameWorld& recGameWorld)
	{
		system("cls"); // Clear the system
		std::cout << "\t=====SPY VS SPY=====" << std::endl << std::endl;
		
		// FEATURES
		std::cout << "'.' - EMPTY_SPACE, 'P' - PLAYER, '|' - WALL, '^' - SENTRY MOVING UP, 'V' - SENTRY MOVING DOWN, '#' - ENDING_POINT, '$' - STARTING_POINT" << std::endl << std::endl;
		
		// Display
		for(int r = 0; r < recGameWorld.intRows; r++)
		{
			for(int c = 0; c < recGameWorld.intCols; c++)
			{
				std::cout << ARR_FEATURES[recGameWorld.arrGame[r][c]] << " ";
			}
			
			std::cout << std::endl;
		}
		
		// Number of senturies
		std::cout << std::endl;
		std::cout << "Number of sentries: " << std::endl << std::endl;
		
		// Movement
		std::cout << "==Movement==" << std::endl
			      << "W - UP" << std::endl
				  << "S - DOWN" << std::endl
				  << "A - LEFT" << std::endl
				  << "D - RIGHT" << std::endl
				  << "X - EXIT" << std::endl
				  << "Choose movement: ";
	}
	
	// A function that ensures that the player is in the bounds of the gameworld
	void isInGameWorld(GameWorld& recGameWorld, int intRow, int intCol)
	{
		// For Row
		if(intRow < 0)
		{
			intRow = 0;
			intCol = recGameWorld.intPCol;
		}
		else if(intRow >= recGameWorld.intRows - 1)
		{
			intRow = recGameWorld.intRows - 1;
			intCol = recGameWorld.intPCol;
		}
		
		// For Col
		if(intCol < 0)
		{
			intCol = 0;
   intRow = recGameWorld.intPRow;
		}
		else if(intCol >= recGameWorld.intCols - 1)
		{
			intCol = recGameWorld.intCols - 1;
   intRow = recGameWorld.intPRow;
		}
	}
	
	// Move Player
	export void MovePlayer(GameWorld& recGameWorld, Direction eDir)
	{
		// Variables that will track the position of the player
		int intPR = recGameWorld.intPRow;
		int intPC = recGameWorld.intPCol;
		
		// Switch-Case
		switch(eDir)
		{
			case UP:
			{
				intPR--;
			}
			
				break;
				
			case DOWN:
			{
				intPR++;
			}
			
				break;
			
			case LEFT:
			{
				intPC--;
			}
			
				break;
				
			case RIGHT:
			{
				intPC++;
			}
		}
		
		// Previous Position becomes an Empty-Space
		recGameWorld.arrGame[recGameWorld.intPRow][recGameWorld.intPCol] = EMPTY_SPACE;
		
		// A function that ensures that the player doesn't leave the gameworld
		isInGameWorld(recGameWorld, intPR, intPC);
		
		// New Position after placing Empty-Space
		recGameWorld.intPRow = intPR;
		recGameWorld.intPCol = intPC;
		
		// Move player to new position
		recGameWorld.arrGame[recGameWorld.intPRow][recGameWorld.intPCol] = PLAYER;
	}
}