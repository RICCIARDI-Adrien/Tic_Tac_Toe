/** @file Interface.c
 * @see Interface.h for description.
 * @author Adrien RICCIARDI
 */
#include <assert.h>
#include <Configuration.h>
#include <Grid.h>
#include <Interface.h>
#include <stdio.h>
#include <stdlib.h>

//-------------------------------------------------------------------------------------------------
// Private constants and macros
//-------------------------------------------------------------------------------------------------
/** Convert the grid row coordinate to the display coordinate.
 * @param Grid_Row The grid row coordinate.
 * @return The corresponding display row.
 */
#define INTERFACE_COMPUTE_DISPLAY_ROW(Grid_Row) 

/** Convert the grid column coordinate to the display coordinate.
 * @param Grid_Column The grid column coordinate.
 * @return The corresponding display column.
 */
#define INTERFACE_COMPUTE_DISPLAY_COLUMN(Grid_Column)  // +1 because VT100 coordinates start from 1

//-------------------------------------------------------------------------------------------------
// Private functions
//-------------------------------------------------------------------------------------------------
/** Display the empty grid shape on a terminal.
 * @warning The terminal must be large enough to show the whole grid.
 */
static inline void InterfaceDisplayEmptyGrid(void)
{
	unsigned int i, Row;
	
	for (Row = 0; Row < Grid_Size; Row++)
	{
		// Display the separation line
		for (i = 0; i < Grid_Size; i++) printf("+---");
		printf("+\r\n"); // Add the last '+'
		
		// Display the cells line
		for (i = 0; i < Grid_Size; i++) printf("|   ");
		printf("|\r\n");
	}
	
	// Display the last line
	for (i = 0; i < Grid_Size; i++) printf("+---");
	printf("+\r\n"); // Add the last '+'
}

//-------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------
void InterfaceInitialize(void)
{
	// Clear the terminal and put the cursor to the upper left position
	printf("\033[2J\n\033[H");
	
	// Display the grid
	InterfaceDisplayEmptyGrid();
	
	// Disable the terminal "text" mode support
	system("stty raw -echo");
}

void InterfaceQuit(void)
{
	// Set the default color
	printf("\033[0m");
	
	// Clear the terminal and put the cursor to the upper left position
	printf("\033[2J\n\033[H");
	
	// Re-enable the terminal "text" mode support
	system("stty cooked echo");
}

void InterfaceSetCursorPosition(unsigned int Row, unsigned int Column)
{
	assert(Row < Grid_Size);
	assert(Column < Grid_Size);
	
	// Convert the coordinates to something displayable on the terminal
	Row = (Row + 1) * 2; // +1 because VT100 coordinates start from 1
	Column = ((Column + 1) * 4) - 1; // +1 because VT100 coordinates start from 1
	
	// Set the cursor to the desired location
	printf("\033[%d;%dH", Row, Column);
}

void InterfaceDisplayCell(unsigned int Row, unsigned int Column, TGridCellContent Cell_Content)
{
	char Character;
	int Character_Color;
	
	assert(Row < Grid_Size);
	assert(Column < Grid_Size);
	assert((Cell_Content == GRID_CELL_CONTENT_CROSS) || (Cell_Content == GRID_CELL_CONTENT_CIRCLE));
	
	// Choose the right color and character according to the cell content
	if (Cell_Content == GRID_CELL_CONTENT_CROSS)
	{
		Character = 'X';
		Character_Color = CONFIGURATION_CROSS_DISPLAYING_COLOR;
	}
	else
	{
		Character = 'O';
		Character_Color = CONFIGURATION_CIRCLE_DISPLAYING_COLOR;
	}
	
	// Display the character
	printf("\0337"); // Save the current cursor position and attributes
	printf("\033[?25l"); // Hide the cursor to avoid the player seeing strange movements
	InterfaceSetCursorPosition(Row, Column);
	printf("\033[%dm%c", Character_Color, Character); // Display the cell character
	printf("\0338"); // Restore the previously saved cursor position and attributes
	printf("\033[?25h"); // Show the cursor
}