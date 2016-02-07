/** @file AI.c
 * @see AI.h for description.
 * @author Adrien RICCIARDI
 */
#include <AI.h>
#include <assert.h>
#include <Configuration.h>
#include <Grid.h>
#include <Pattern.h>
//#include <Stack.h> TODO remove if useless

// TEST
#include <Interface.h>

//-------------------------------------------------------------------------------------------------
// Private types
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Private variables
//-------------------------------------------------------------------------------------------------
/** All patterns. */
static TPattern Pattern_1 =
{
	1,
	5,
	5,
	{
		1, 1, 1, 1, 1
	}
};

static TPattern Pattern_2 =
{
	5,
	1,
	5,
	{
		1,
		1,
		1,
		1,
		1
	}
};

static TPattern Pattern_3 =
{
	5,
	5,
	5,
	{
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1
	}
};

static TPattern Pattern_4 =
{
	5,
	5,
	5,
	{
		0, 0, 0, 0, 1,
		0, 0, 0, 1, 0,
		0, 0, 1, 0, 0,
		0, 1, 0, 0, 0,
		1, 0, 0, 0, 0
	}
};

// The patterns can't be directly initialized in a unique array because each pattern cells are of variable size
static TPattern *Pointer_Patterns[] =
{
	&Pattern_1,
	&Pattern_2,
	&Pattern_3,
	&Pattern_4
};

/** When the AISimulate() function terminates, the following variables contain the best coordinates to play according to the chosen strategy. */
static unsigned int AI_Best_Defensive_Row, AI_Best_Defensive_Column, AI_Best_Offensive_Row, AI_Best_Offensive_Column;
/** Contain the current best offensive and defensive moves estimation. */
static unsigned int AI_Best_Defensive_Value, AI_Best_Offensive_Value; // The following variables are shared between several functions

//-------------------------------------------------------------------------------------------------
// Private functions
//-------------------------------------------------------------------------------------------------
static inline int AICheckForHorizontalCellsAligment(TGridCellContent Cell_Content)
{
	unsigned int Row, Column, i;
	
	for (Row = 0; Row < Grid_Size; Row++)
	{
		for (Column = 0; Column < Grid_Size; Column++)
		{
			// Go to next row if there are not enough cells to make a full alignment
			if (Column > Grid_Size - CONFIGURATION_ALIGNED_CELLS_FOR_VICTORY_COUNT) break;
			
			// Check for enough consecutive cells count
			for (i = 0; i < CONFIGURATION_ALIGNED_CELLS_FOR_VICTORY_COUNT; i++)
			{
				if (GridGetCellContent(Row, Column) != Cell_Content) break;
			}
			// All requested cells are aligned
			if (i == CONFIGURATION_ALIGNED_CELLS_FOR_VICTORY_COUNT) return 1;
		}
	}
	
	return 0;
}

/** Use a backtrack algorithm to simulate all game situations and find the best move.
 * @return A positive number if the situation is favorable to the computer,
 * @return A negative number if the situation is favorable to the player.
 */
static int AISimulate(void)
{
	//TStack Stack_Allowed_Moves;
	unsigned int Row, Column;
	static int Simulation_Level = 0;
	TGridCellContent Cell_Content;
	int Return_Value;
	
	if (Simulation_Level < 2) // TEST, TODO set value with Difficulty parameter
	{
		// Select the cell type to simulate (player or computer)
		if (Simulation_Level & 1) Cell_Content = GRID_CELL_CONTENT_CIRCLE; // Odd simulation level correspond to the player
		else Cell_Content = GRID_CELL_CONTENT_CROSS;
		
		// Gather all allowed moves
		//StackInitialize(&Stack_Allowed_Moves);
		for (Row = 0; Row < Grid_Size; Row++)
		{
			for (Column = 0; Column < Grid_Size; Column++)
			{
				if (GridIsMoveAllowed(Row, Column)) //StackPush(&Stack_Allowed_Moves, (unsigned short) ((Row << 8) | Column));
				{
					// Try the move
					GridSetCellContent(Row, Column, Cell_Content);
					
					// TEST
					InterfaceDisplayCell(Row, Column, Cell_Content);
					getchar();
					
					Simulation_Level++;
					Return_Value = AISimulate();
					//if (Return_Value != 0) return Return_Value;
					Simulation_Level--;
					
					// Remove the move
					GridSetCellContent(Row, Column, GRID_CELL_CONTENT_EMPTY);
				}
			}
		}
		
		// TEST
		return Return_Value;
	}
	else
	{
		// TODO
		//return AICheckForHorizontalCellsAligment();
		return 3;
	}
}

//-------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------
void AIMakeMove(void)
{
	AI_Best_Defensive_Row = 0;
	AI_Best_Defensive_Column = 0;
	AI_Best_Offensive_Row = 0;
	AI_Best_Offensive_Column = 0;
	
	// TODO
	AISimulate();
	
	// TODO according to strategy, make the move
}