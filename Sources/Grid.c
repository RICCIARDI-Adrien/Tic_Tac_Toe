/** @file Grid.c
 * @see Grid.h for description.
 * @author Adrien RICCIARDI
 */
#include <assert.h>
#include <Configuration.h>
#include <Grid.h>

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
	#ifdef DEBUG
		assert(Row < Grid_Size);
		assert(Column < Grid_Size);
	#endif
	
	return Grid[GRID_COMPUTE_CELL_INDEX(Row, Column)];
}

void GridSetCellContent(unsigned int Row, unsigned int Column, TGridCellContent Cell_Content)
{
	#ifdef DEBUG
		assert(Row < Grid_Size);
		assert(Column < Grid_Size);
	#endif
	
	Grid[GRID_COMPUTE_CELL_INDEX(Row, Column)] = Cell_Content;
}