/** @file Grid.c
 * @see Grid.h for description.
 * @author Adrien RICCIARDI
 */
#include <assert.h>
#include <Configuration.h>
#include <Grid.h>
#include <Stack.h>

//-------------------------------------------------------------------------------------------------
// Private constants and macros
//-------------------------------------------------------------------------------------------------
/** Compute a cell location in the grid.
 * @param Row The cell row.
 * @param Colum The cell column.
 * @return The cell index in the grid array.
 */
#define GRID_COMPUTE_CELL_INDEX(Row, Column) ((Row * Grid_Size) + Column)

//-------------------------------------------------------------------------------------------------
// Private variables
//-------------------------------------------------------------------------------------------------
/** The grid. */
static TGridCellContent Grid[CONFIGURATION_MAXIMUM_GRID_SIZE * CONFIGURATION_MAXIMUM_GRID_SIZE];

//-------------------------------------------------------------------------------------------------
// Public variables
//-------------------------------------------------------------------------------------------------
unsigned int Grid_Size;

//-------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------
TGridCellContent GridGetCellContent(unsigned int Row, unsigned int Column)
{
	assert(Row < Grid_Size);
	assert(Column < Grid_Size);
	
	return Grid[GRID_COMPUTE_CELL_INDEX(Row, Column)];
}

void GridSetCellContent(unsigned int Row, unsigned int Column, TGridCellContent Cell_Content)
{
	assert(Row < Grid_Size);
	assert(Column < Grid_Size);
	assert((Cell_Content == GRID_CELL_CONTENT_EMPTY) || (Cell_Content == GRID_CELL_CONTENT_CROSS) || (Cell_Content == GRID_CELL_CONTENT_CIRCLE)); 
	
	Grid[GRID_COMPUTE_CELL_INDEX(Row, Column)] = Cell_Content;
}

// A cell can be filled only if it is close to one or more other filled cell(s)
int GridIsMoveAllowed(unsigned int Row, unsigned int Column)
{
	assert(Row < Grid_Size);
	assert(Column < Grid_Size);
	
	// Check for a filled cell on north-west
	if ((Row > 0) && (Column > 0) && (GridGetCellContent(Row - 1, Column - 1) != GRID_CELL_CONTENT_EMPTY)) return 1;
	// Check for a filled cell on north
	if ((Row > 0) && (GridGetCellContent(Row - 1, Column) != GRID_CELL_CONTENT_EMPTY)) return 1;
	// Check for a filled cell on north-east
	if ((Row > 0) && (Column < Grid_Size - 1) && (GridGetCellContent(Row - 1, Column + 1) != GRID_CELL_CONTENT_EMPTY)) return 1;
	// Check for a filled cell on west
	if ((Column > 0) && (GridGetCellContent(Row, Column - 1) != GRID_CELL_CONTENT_EMPTY)) return 1;
	// Check for a filled cell on east
	if ((Column < Grid_Size - 1) && (GridGetCellContent(Row, Column + 1) != GRID_CELL_CONTENT_EMPTY)) return 1;
	// Check for a filled cell on south-west
	if ((Row < Grid_Size - 1) && (Column > 0) && (GridGetCellContent(Row + 1, Column - 1) != GRID_CELL_CONTENT_EMPTY)) return 1;
	// Check for a filled cell on south
	if ((Row < Grid_Size - 1) && (GridGetCellContent(Row + 1, Column) != GRID_CELL_CONTENT_EMPTY)) return 1;
	// Check for a filled cell on south-east
	if ((Row < Grid_Size - 1) && (Column < Grid_Size - 1) && (GridGetCellContent(Row + 1, Column + 1) != GRID_CELL_CONTENT_EMPTY)) return 1;
	
	return 0;
}