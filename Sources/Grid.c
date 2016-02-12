/** @file Grid.c
 * @see Grid.h for description.
 * @author Adrien RICCIARDI
 */
#include <assert.h>
#include <Configuration.h>
#include <Grid.h>
#include <Pattern.h>
#include <stdio.h>

//-------------------------------------------------------------------------------------------------
// Private constants and macros
//-------------------------------------------------------------------------------------------------
/** Compute a cell location in the grid.
 * @param Row The cell row.
 * @param Column The cell column.
 * @return The cell index in the grid array.
 */
#define GRID_COMPUTE_CELL_INDEX(Row, Column) ((Row * Grid_Size) + Column)

//-------------------------------------------------------------------------------------------------
// Private variables
//-------------------------------------------------------------------------------------------------
/** The grid. */
static TGridCellContent Grid[CONFIGURATION_MAXIMUM_GRID_SIZE * CONFIGURATION_MAXIMUM_GRID_SIZE];

/** Horizontal winning pattern. */
static TPattern Grid_Winning_Pattern_1 =
{
	1,
	5,
	1000,
	{
		'r', 'r', 'r', 'r', 'r'
	}
};

/** Vertical winning pattern. */
static TPattern Grid_Winning_Pattern_2 =
{
	5,
	1,
	1000,
	{
		'r',
		'r',
		'r',
		'r',
		'r'
	}
};

/** Diagonal winning pattern. */
static TPattern Grid_Winning_Pattern_3 =
{
	5,
	5,
	1000,
	{
		'r', 'a', 'a', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', 'a', 'a', 'r'
	}
};

/** Diagonal winning pattern. */
static TPattern Grid_Winning_Pattern_4 =
{
	5,
	5,
	1000,
	{
		'a', 'a', 'a', 'a', 'r',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a'
	}
};

/** All winning patterns. */
static TPattern *Pointer_Grid_Winning_Patterns[] =
{
	&Grid_Winning_Pattern_1,
	&Grid_Winning_Pattern_2,
	&Grid_Winning_Pattern_3,
	&Grid_Winning_Pattern_4,
	NULL
};

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
	
	// Can't play on a yet filled cell
	if (GridGetCellContent(Row, Column) != GRID_CELL_CONTENT_EMPTY) return 0;
	
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

int GridIsGameWon(TGridCellContent Cell_Content)
{
	unsigned int Row, Column;
	int i;
	
	for (Row = 0; Row < Grid_Size; Row++)
	{
		for (Column = 0; Column < Grid_Size; Column++)
		{
			for (i = 0; Pointer_Grid_Winning_Patterns[i] != NULL; i++)
			{
				if (PatternMatchFirst(Pointer_Grid_Winning_Patterns[i], Cell_Content)) return 1;
			}
		}
	}
	return 0;
}