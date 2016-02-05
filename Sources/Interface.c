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

/** Put the terminal cursor to the position corresponding to the provided grid coordinates.
 * @param Grid_Row The row in the grid.
 * @param Grid_Column The column in the grid.
 */
static inline void InterfaceSetCursorPosition(unsigned int Grid_Row, unsigned int Grid_Column)
{
	// Convert the coordinates to something displayable on the terminal
	Grid_Row = (Grid_Row + 1) * 2; // +1 because VT100 coordinates start from 1
	Grid_Column = ((Grid_Column + 1) * 4) - 1; // +1 because VT100 coordinates start from 1
	
	// Set the cursor to the desired location
	printf("\033[%d;%dH", Grid_Row, Grid_Column);
}

//-------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------
void InterfaceInitialize(void)
{
	// Hide the cursor
	printf("\033[?25l");
	
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
	
	// Display the cursor
	printf("\033[?25h");
	
	// Re-enable the terminal "text" mode support
	system("stty cooked echo");
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
	InterfaceSetCursorPosition(Row, Column);
	printf("\033[%dm%c", Character_Color, Character);
}

void InterfaceDisplayCursor(unsigned int Row, unsigned int Column, int Is_Cursor_Visible)
{
	char Character;
	int Character_Color;
	
	assert(Row < Grid_Size);
	assert(Column < Grid_Size);
	
	// Retrieve the cell character
	switch (GridGetCellContent(Row, Column))
	{
		case GRID_CELL_CONTENT_CROSS:
			Character = 'X';
			Character_Color = CONFIGURATION_CROSS_DISPLAYING_COLOR;
			break;
			
		case GRID_CELL_CONTENT_CIRCLE:
			Character = 'O';
			Character_Color = CONFIGURATION_CIRCLE_DISPLAYING_COLOR;
			break;
		
		// Empty cell
		default:
			Character = ' ';
			Character_Color = 30 + CONFIGURATION_CURSOR_DISPLAYING_COLOR;
			break;
	}
	
	// Display the character
	InterfaceSetCursorPosition(Row, Column);
	if (Is_Cursor_Visible) printf("\033[4%dm\033[%dm%c", CONFIGURATION_CURSOR_DISPLAYING_COLOR, Character_Color, Character);
	else printf("\033[49m\033[%dm%c", Character_Color, Character); // Reset the background color
}