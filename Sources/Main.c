/** @file Main.c
 * Tic Tac Toe entry point and main loop.
 * @author Adrien RICCIARDI
 */
#include <AI.h>
#include <Configuration.h>
#include <Grid.h>
#include <Interface.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//-------------------------------------------------------------------------------------------------
// Entry point
//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	unsigned int Cursor_Row, Cursor_Column;
	
	// Check parameters
	if (argc != 2) // TODO set to 3 to take Difficulty into account
	{
		printf("Usage : %s Grid_Size\n"
			"Grid_Size : 5, 10, 15 or 20 cells\n", argv[0]); // TODO better comment that can be independent from the configurable grid size
		return EXIT_FAILURE;
	}
	// Extract the grid size parameter
	if (sscanf(argv[1], "%u", &Grid_Size) != 1)
	{
		printf("Error : the grid size value could not be parsed. Make sure it is an unsigned integer value.\n");
		return EXIT_FAILURE;
	}
	// The grid size must be a multiple of 5...
	if ((Grid_Size % 5) != 0)
	{
		printf("Error : the grid size must be a multiple of 5.\n");
		return EXIT_FAILURE;
	}
	// ...and it must not exceed the maximum grid size
	if ((Grid_Size < 10) || (Grid_Size > CONFIGURATION_MAXIMUM_GRID_SIZE))
	{
		printf("Error : the minimum allowed grid size is 10 and the maximum allowed grid size is %d.\n", CONFIGURATION_MAXIMUM_GRID_SIZE);
		return EXIT_FAILURE;
	}
	
	// Initialize the random numbers generator once and for all
	srand(time(NULL));
	
	// Display the empty grid
	InterfaceInitialize();
	
	// Display the help message
	printf("Z, Q, S, D : move the cursor\r\n"
		"Space : insert a circle\r\n"
		"X : exit program");
	
	// Let the program make the first move
	// TODO do this a bit smarter ?
	Cursor_Row = rand() % Grid_Size; // Recycle the Cursor_xxx variables
	Cursor_Column = rand() % Grid_Size;
	GridSetCellContent(Cursor_Row, Cursor_Column, GRID_CELL_CONTENT_CROSS);
	InterfaceDisplayCell(Cursor_Row, Cursor_Column, GRID_CELL_CONTENT_CROSS);
	
	// Display the cursor on the upper left cell
	Cursor_Row = 0;
	Cursor_Column = 0;
	InterfaceSetCursorPosition(0, 0);

	while (1)
	{
		switch (getchar())
		{
			case 'Z':
			case 'z':
				if (Cursor_Row > 0)
				{
					Cursor_Row--;
					InterfaceSetCursorPosition(Cursor_Row, Cursor_Column);
				}
				break;
				
			case 'S':
			case 's':
				if (Cursor_Row < Grid_Size - 1)
				{
					Cursor_Row++;
					InterfaceSetCursorPosition(Cursor_Row, Cursor_Column);
				}
				break;
				
			case 'Q':
			case 'q':
				if (Cursor_Column > 0)
				{
					Cursor_Column--;
					InterfaceSetCursorPosition(Cursor_Row, Cursor_Column);
				}
				break;
				
			case 'D':
			case 'd':
				if (Cursor_Column < Grid_Size - 1)
				{
					Cursor_Column++;
					InterfaceSetCursorPosition(Cursor_Row, Cursor_Column);
				}
				break;
				
			case ' ':
				// Is the move allowed ?
				if (!GridIsMoveAllowed(Cursor_Row, Cursor_Column)) break;
				// The move is allowed, so fill the grid
				GridSetCellContent(Cursor_Row, Cursor_Column, GRID_CELL_CONTENT_CIRCLE);
				InterfaceDisplayCell(Cursor_Row, Cursor_Column, GRID_CELL_CONTENT_CIRCLE);
				// TODO did the player won ?
				// TODO make the computer play
				AIMakeMove();
				// TODO did the computer won ?
				// TODO match nul ?
				break;
				
			case 'X':
			case 'x':
				InterfaceQuit();
				return EXIT_SUCCESS;
		}
	}
}