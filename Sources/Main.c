/** @file Main.c
 * Tic Tac Toe entry point and main loop.
 * @author Adrien RICCIARDI
 */
#include <Configuration.h>
#include <Grid.h>
#include <Interface.h>
#include <stdio.h>
#include <stdlib.h>

// TEST
#include <Stack.h>

//-------------------------------------------------------------------------------------------------
// Entry point
//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	unsigned int Cursor_Row = 0, Cursor_Column = 0;
	
	// Check parameters
	if (argc != 2) // TODO set to 3 to take Difficulty into account
	{
		printf("Usage : %s Grid_Size Difficulty\n"
			"Grid_Size : 5, 10, 15 or 20 cells\n" // TODO better comment that can be independent from the configurable grid size
			"Difficulty : easy, medium, hard\n", argv[0]);
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
	if ((Grid_Size < 5) || (Grid_Size > CONFIGURATION_MAXIMUM_GRID_SIZE))
	{
		printf("Error : the minimum allowed grid size is 5 and the maximum allowed grid size is %d.\n", CONFIGURATION_MAXIMUM_GRID_SIZE);
		return EXIT_FAILURE;
	}
	
	// TEST
	{
		TStack s;
		
		StackInitialize(&s);
		
		StackPush(&s, 3);
		StackPush(&s, 4);
		StackPush(&s, 5);
		StackPush(&s, 58);
		
		while (!StackIsEmpty(&s)) printf("%d\n", StackPop(&s));

		// Trigger the assert
		StackPop(&s);
		return 15;
	}
	
	// Display the empty grid
	InterfaceInitialize();
	
	// Display the help message
	printf("Z, Q, S, D : move the cursor\r\n"
		"Space : insert a circle\r\n"
		"X : exit program");
	
	// TEST
	InterfaceDisplayCell(0, 0, 1);
	InterfaceDisplayCell(3, 3, 2);
	InterfaceDisplayCell(6, 2, 1);
	InterfaceDisplayCell(9, 9, 2);
	GridSetCellContent(0, 0, 1);
	GridSetCellContent(3, 3, 2);
	GridSetCellContent(6, 2, 1);
	GridSetCellContent(9, 9, 2);
	
	// Display the cursor on the upper left cell
	InterfaceDisplayCursor(0, 0, 1);
	
	while (1)
	{
		switch (getchar())
		{
			case 'Z':
			case 'z':
				if (Cursor_Row > 0)
				{
					InterfaceDisplayCursor(Cursor_Row, Cursor_Column, 0);
					Cursor_Row--;
					InterfaceDisplayCursor(Cursor_Row, Cursor_Column, 1);
				}
				break;
				
			case 'S':
			case 's':
				if (Cursor_Row < Grid_Size - 1)
				{
					InterfaceDisplayCursor(Cursor_Row, Cursor_Column, 0);
					Cursor_Row++;
					InterfaceDisplayCursor(Cursor_Row, Cursor_Column, 1);
				}
				break;
				
			case 'Q':
			case 'q':
				if (Cursor_Column > 0)
				{
					InterfaceDisplayCursor(Cursor_Row, Cursor_Column, 0);
					Cursor_Column--;
					InterfaceDisplayCursor(Cursor_Row, Cursor_Column, 1);
				}
				break;
				
			case 'D':
			case 'd':
				if (Cursor_Column < Grid_Size - 1)
				{
					InterfaceDisplayCursor(Cursor_Row, Cursor_Column, 0);
					Cursor_Column++;
					InterfaceDisplayCursor(Cursor_Row, Cursor_Column, 1);
				}
				break;
				
			case ' ':
				// TODO check for empty grid cell
				// TODO check for allowed move
				break;
				
			case 'X':
			case 'x':
				InterfaceQuit();
				return EXIT_SUCCESS;
		}
	}
}