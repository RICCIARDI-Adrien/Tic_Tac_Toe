/** @file AI.c
 * @see AI.h for description.
 * @author Adrien RICCIARDI
 */
#include <AI.h>
#include <assert.h>
#include <Configuration.h>
#include <Grid.h>
#include <Interface.h>
#include <Pattern.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

//-------------------------------------------------------------------------------------------------
// Private constants
//-------------------------------------------------------------------------------------------------
/** The defensive strategy initialization value. */
#define AI_DEFENSIVE_STRATEGY_DEFAULT_VALUE 2147483647

//-------------------------------------------------------------------------------------------------
// Private types
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Private variables
//-------------------------------------------------------------------------------------------------
#if 0
// Sort the patterns from best match to worst match so the pattern engine can exit whenever a match is found, because it is the best one
// Patterns valuated to 5
static TPattern Pattern_5_1 =
{
	1,
	5,
	5,
	{
		1, 1, 1, 1, 1
	}
};

static TPattern Pattern_5_2 =
{
	5,
	5,
	5,
	{
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0
	}
};

static TPattern Pattern_5_3 =
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

static TPattern Pattern_5_4 =
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

// Patterns valuated to 4
static TPattern Pattern_4_1 =
{
	1,
	5,
	4,
	{
		0, 1, 1, 1, 1
	}
};

static TPattern Pattern_4_2 =
{
	1,
	5,
	4,
	{
		1, 0, 1, 1, 1
	}
};

static TPattern Pattern_4_3 =
{
	1,
	5,
	4,
	{
		1, 1, 0, 1, 1
	}
};

static TPattern Pattern_4_4 =
{
	1,
	5,
	4,
	{
		1, 1, 1, 0, 1
	}
};

static TPattern Pattern_4_5 =
{
	1,
	5,
	4,
	{
		1, 1, 1, 1, 0
	}
};

static TPattern Pattern_4_6 =
{
	5,
	5,
	4,
	{
		0, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0
	}
};

static TPattern Pattern_4_7 =
{
	5,
	5,
	4,
	{
		1, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0
	}
};

static TPattern Pattern_4_8 =
{
	5,
	5,
	4,
	{
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0
	}
};

static TPattern Pattern_4_9 =
{
	5,
	5,
	4,
	{
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		1, 0, 0, 0, 0
	}
};

static TPattern Pattern_4_10 =
{
	5,
	5,
	4,
	{
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	}
};

// The patterns can't be directly initialized in a unique array because each pattern cells are of variable size
static TPattern *Pointer_Patterns[] =
{
	&Pattern_5_1,
	&Pattern_5_2,
	&Pattern_5_3,
	&Pattern_5_4,
	NULL, // TEST
	&Pattern_4_1,
	&Pattern_4_2,
	&Pattern_4_3,
	&Pattern_4_4,
	&Pattern_4_5,
	&Pattern_4_6,
	&Pattern_4_7,
	&Pattern_4_8,
	&Pattern_4_9,
	&Pattern_4_10,
	NULL
};

/** When the AISimulate() function terminates, the following variables contain the best coordinates to play according to the chosen strategy. */
static unsigned int AI_Best_Defensive_Row = 0, AI_Best_Defensive_Column = 0, AI_Best_Offensive_Row = 0, AI_Best_Offensive_Column = 0; // Initialize the variables here even if useless to make the compiler happy
/** Contain the current best offensive and defensive moves estimation. */
static int AI_Best_Defensive_Value, AI_Best_Offensive_Value; // The following variables are shared between several functions

//-------------------------------------------------------------------------------------------------
// Private functions
//-------------------------------------------------------------------------------------------------
/** Use a backtrack algorithm to simulate all game situations and find the best move. */
static void AISimulate(void)
{
	unsigned int Row, Column;
	int Previous_Best_Defensive_Value = 0, Previous_Best_Offensive_Value = 0;
	static int Simulation_Level = 0;
	TGridCellContent Cell_Content;
	
	if (Simulation_Level < 5) // TEST, TODO set value with Difficulty parameter
	{
		// Select the cell type to simulate (player or computer)
		if (Simulation_Level & 1) Cell_Content = GRID_CELL_CONTENT_CIRCLE; // Odd simulation level correspond to the player
		else Cell_Content = GRID_CELL_CONTENT_CROSS;
		
		// Try all allowed moves
		for (Row = 0; Row < Grid_Size; Row++)
		{
			for (Column = 0; Column < Grid_Size; Column++)
			{
				if (GridIsMoveAllowed(Row, Column))
				{
					// Try the move
					GridSetCellContent(Row, Column, Cell_Content);
					
					// TEST
					//InterfaceDisplayCell(Row, Column, Cell_Content);
					
					// Save these values to see if they were changed when the simulation is finished
					if (Simulation_Level == 0) // Initial simulation level
					{
						Previous_Best_Defensive_Value = AI_Best_Defensive_Value;
						Previous_Best_Offensive_Value = AI_Best_Offensive_Value;
						syslog(LOG_INFO, "AVANT Previous_Best_Defensive_Value=%d, Previous_Best_Offensive_Value=%d\n", Previous_Best_Defensive_Value, Previous_Best_Offensive_Value); 
					}
					
					// Simulate the move
					Simulation_Level++;
					AISimulate();
					Simulation_Level--;
					
					// Check if this cell could bring some useful offensive or defensive opportunities
					if (Simulation_Level == 0) // Initial simulation level
					{
						syslog(LOG_INFO, "APRES Previous_Best_Defensive_Value=%d, Previous_Best_Offensive_Value=%d\n", Previous_Best_Defensive_Value, Previous_Best_Offensive_Value); 
						if (AI_Best_Defensive_Value > Previous_Best_Defensive_Value)
						{
							AI_Best_Defensive_Row = Row;
							AI_Best_Defensive_Column = Column;
						}
						
						if (AI_Best_Offensive_Value > Previous_Best_Offensive_Value)
						{
							AI_Best_Offensive_Row = Row;
							AI_Best_Offensive_Column = Column;
						}
					}
					
					// Remove the move
					GridSetCellContent(Row, Column, GRID_CELL_CONTENT_EMPTY);
					
					// TEST
					//InterfaceDisplayCell(Row, Column, GRID_CELL_CONTENT_EMPTY);
				}
			}
		}
	}
	else
	{
		// TODO for now, the first best move will always be used; in future, create a list of all best moves and randomly choose one
		
		// Compare the grid to all known patterns
		for (Row = 0; Pointer_Patterns[Row] != NULL; Row++) // Recycle the Row variable
		{
			// Check for offensive move
			if (PatternMatch(Pointer_Patterns[Row], GRID_CELL_CONTENT_CROSS))
			{
				syslog(LOG_INFO, "match cross (best=%d, curr=%d)\n", AI_Best_Offensive_Value, Pointer_Patterns[Row]->Value);
				if (Pointer_Patterns[Row]->Value > AI_Best_Offensive_Value) AI_Best_Offensive_Value = Pointer_Patterns[Row]->Value;
			}
			
			// Check for defensive move
			// TODO use a reverse value
			if (PatternMatch(Pointer_Patterns[Row], GRID_CELL_CONTENT_CIRCLE))
			{
				syslog(LOG_INFO, "match circle (best=%d, curr=%d)\n", AI_Best_Defensive_Value, Pointer_Patterns[Row]->Value);
				if (Pointer_Patterns[Row]->Value > AI_Best_Defensive_Value) {syslog(LOG_INFO, "value set"); AI_Best_Defensive_Value = Pointer_Patterns[Row]->Value;}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------
void AIMakeMove(void)
{
	unsigned char Cell_Row, Cell_Column;
	
	AI_Best_Defensive_Value = 0;
	AI_Best_Offensive_Value = 0;
	
	// Find the best offensive and defensive moves
	//AISimulate();
	
	syslog(LOG_INFO, "[AIMakeMove] best off=%d, best def=%d\n", AI_Best_Offensive_Value, AI_Best_Defensive_Value);
	
	// Choose the defensive or offensive move
	if ((AI_Best_Defensive_Value == 0) && (AI_Best_Offensive_Value == 0))
	{
		do
		{
			Cell_Row = rand() % Grid_Size;
			Cell_Column = rand() % Grid_Size;
		} while (!GridIsMoveAllowed(Cell_Row, Cell_Column));
		
		//printf("Cell_Row=%u,Cell_Column=%d\n",Cell_Row,Cell_Column);
	}
	else if (AI_Best_Defensive_Value >= AI_Best_Offensive_Value) // Prefer a defensive move to block the player
	{
		Cell_Row = AI_Best_Defensive_Row;
		Cell_Column = AI_Best_Defensive_Column;
		
		syslog(LOG_INFO, "playing DEFENSIVE (%d,%d)\n", Cell_Row, Cell_Column);
	}
	else
	{
		Cell_Row = AI_Best_Offensive_Row;
		Cell_Column = AI_Best_Offensive_Column;
	}
	
	// Put the cell on the grid
	assert(GridIsMoveAllowed(Cell_Row, Cell_Column));
	GridSetCellContent(Cell_Row, Cell_Column, GRID_CELL_CONTENT_CROSS);
	InterfaceDisplayCell(Cell_Row, Cell_Column, GRID_CELL_CONTENT_CROSS);
}
#endif

//-------------------------------------------------------------------------------------------------
// Private variables
//-------------------------------------------------------------------------------------------------
// Common patterns
// The less valuated pattern, so the evaluating function will return low value for all matching cells, but longer patterns will return huge value that will discard the low ones
static TPattern AI_Pattern_Common_1_1 =
{
	1,
	1,
	1,
	{
		'r'
	}
};

// Attack-specific patterns
/*static TPattern Pattern_5_1 =
{
	1,
	5,
	1000000,
	{
		1, 1, 1, 1, 1
	}
};

static TPattern Pattern_5_2 =
{
	5,
	5,
	1000000,
	{
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0
	}
};

static TPattern Pattern_5_3 =
{
	5,
	5,
	1000000,
	{
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1
	}
};

static TPattern Pattern_5_4 =
{
	5,
	5,
	1000000,
	{
		0, 0, 0, 0, 1,
		0, 0, 0, 1, 0,
		0, 0, 1, 0, 0,
		0, 1, 0, 0, 0,
		1, 0, 0, 0, 0
	}
};*/

// Defense-specific patterns
// Set high values to the patterns to block first
// TODO move to common
static TPattern AI_Pattern_Defense_1 =
{
	1,
	5,
	100000,
	{
		' ', 'r', 'r', 'r', 'r'
	}
};

static TPattern AI_Pattern_Defense_2 =
{
	1,
	5,
	100000,
	{
		'r', ' ', 'r', 'r', 'r'
	}
};

static TPattern AI_Pattern_Defense_3 =
{
	1,
	5,
	100000,
	{
		'r', 'r', ' ', 'r', 'r'
	}
};

static TPattern AI_Pattern_Defense_4 =
{
	1,
	5,
	100000,
	{
		'r', 'r', 'r', ' ', 'r'
	}
};

static TPattern AI_Pattern_Defense_5 =
{
	1,
	5,
	100000,
	{
		'r', 'r', 'r', 'r', ' '
	}
};

static TPattern AI_Pattern_Defense_6 =
{
	5,
	5,
	100000,
	{
		' ', 'a', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
	}
};

static TPattern AI_Pattern_Defense_7 =
{
	5,
	5,
	100000,
	{
		'r', 'a', 'a', 'a', 'a',
		' ', 'a', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
	}
};

static TPattern AI_Pattern_Defense_8 =
{
	5,
	5,
	100000,
	{
		'r', 'a', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
		' ', 'a', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
	}
};

static TPattern AI_Pattern_Defense_9 =
{
	5,
	5,
	100000,
	{
		'r', 'a', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
		' ', 'a', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
	}
};

static TPattern AI_Pattern_Defense_10 =
{
	5,
	5,
	100000,
	{
		'r', 'a', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
		' ', 'a', 'a', 'a', 'a',
	}
};

static TPattern AI_Pattern_Defense_11 =
{
	5,
	5,
	100000,
	{
		' ', 'a', 'a', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', 'a', 'a', 'r',
	}
};

static TPattern AI_Pattern_Defense_12 =
{
	5,
	5,
	100000,
	{
		'r', 'a', 'a', 'a', 'a',
		'a', ' ', 'a', 'a', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', 'a', 'a', 'r',
	}
};

static TPattern AI_Pattern_Defense_13 =
{
	5,
	5,
	100000,
	{
		'r', 'a', 'a', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		'a', 'a', ' ', 'a', 'a',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', 'a', 'a', 'r',
	}
};

static TPattern AI_Pattern_Defense_14 =
{
	5,
	5,
	100000,
	{
		'r', 'a', 'a', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', 'a', 'a', ' ', 'a',
		'a', 'a', 'a', 'a', 'r',
	}
};

static TPattern AI_Pattern_Defense_15 =
{
	5,
	5,
	100000,
	{
		'r', 'a', 'a', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', 'a', 'a', ' ',
	}
};

static TPattern AI_Pattern_Defense_16 =
{
	5,
	5,
	100000,
	{
		'a', 'a', 'a', 'a', ' ',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
	}
};

static TPattern AI_Pattern_Defense_17 =
{
	5,
	5,
	100000,
	{
		'a', 'a', 'a', 'a', 'r',
		'a', 'a', 'a', ' ', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
	}
};

static TPattern AI_Pattern_Defense_18 =
{
	5,
	5,
	100000,
	{
		'a', 'a', 'a', 'a', 'r',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', ' ', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
	}
};

static TPattern AI_Pattern_Defense_19 =
{
	5,
	5,
	100000,
	{
		'a', 'a', 'a', 'a', 'r',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', ' ', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a',
	}
};

static TPattern AI_Pattern_Defense_20 =
{
	5,
	5,
	100000,
	{
		'a', 'a', 'a', 'a', 'r',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		' ', 'a', 'a', 'a', 'a',
	}
};

static TPattern AI_Pattern_Defense_3_1 =
{
	1,
	4,
	10000,
	{
		' ', 'r', 'r', 'r'
	}
};

static TPattern AI_Pattern_Defense_3_2 =
{
	1,
	4,
	10000,
	{
		'r', ' ', 'r', 'r'
	}
};

static TPattern AI_Pattern_Defense_3_3 =
{
	1,
	4,
	10000,
	{
		'r', 'r', ' ', 'r'
	}
};

static TPattern AI_Pattern_Defense_3_4 =
{
	1,
	4,
	10000,
	{
		'r', 'r', 'r', ' '
	}
};

static TPattern AI_Pattern_Defense_3_5 =
{
	4,
	4,
	10000,
	{
		' ', 'a', 'a', 'a',
		'r', 'a', 'a', 'a',
		'r', 'a', 'a', 'a',
		'r', 'a', 'a', 'a'
	}
};

static TPattern AI_Pattern_Defense_3_6 =
{
	4,
	4,
	10000,
	{
		'r', 'a', 'a', 'a',
		' ', 'a', 'a', 'a',
		'r', 'a', 'a', 'a',
		'r', 'a', 'a', 'a'
	}
};

static TPattern AI_Pattern_Defense_3_7 =
{
	4,
	4,
	10000,
	{
		'r', 'a', 'a', 'a',
		'r', 'a', 'a', 'a',
		' ', 'a', 'a', 'a',
		'r', 'a', 'a', 'a'
	}
};

static TPattern AI_Pattern_Defense_3_8 =
{
	4,
	4,
	10000,
	{
		'r', 'a', 'a', 'a',
		'r', 'a', 'a', 'a',
		'r', 'a', 'a', 'a',
		' ', 'a', 'a', 'a'
	}
};

static TPattern AI_Pattern_Defense_3_9 =
{
	4,
	4,
	10000,
	{
		' ', 'a', 'a', 'a',
		'a', 'r', 'a', 'a',
		'a', 'a', 'r', 'a',
		'a', 'a', 'a', 'r'
	}
};

static TPattern AI_Pattern_Defense_3_10 =
{
	4,
	4,
	10000,
	{
		'r', 'a', 'a', 'a',
		'a', ' ', 'a', 'a',
		'a', 'a', 'r', 'a',
		'a', 'a', 'a', 'r'
	}
};

static TPattern AI_Pattern_Defense_3_11 =
{
	4,
	4,
	10000,
	{
		'r', 'a', 'a', 'a',
		'a', 'r', 'a', 'a',
		'a', 'a', ' ', 'a',
		'a', 'a', 'a', 'r'
	}
};

static TPattern AI_Pattern_Defense_3_12 =
{
	4,
	4,
	10000,
	{
		'r', 'a', 'a', 'a',
		'a', 'r', 'a', 'a',
		'a', 'a', 'r', 'a',
		'a', 'a', 'a', ' '
	}
};

static TPattern AI_Pattern_Defense_3_13 =
{
	4,
	4,
	10000,
	{
		'a', 'a', 'a', ' ',
		'a', 'a', 'r', 'a',
		'a', 'r', 'a', 'a',
		'r', 'a', 'a', 'a'
	}
};

static TPattern AI_Pattern_Defense_3_14 =
{
	4,
	4,
	10000,
	{
		'a', 'a', 'a', 'r',
		'a', 'a', ' ', 'a',
		'a', 'r', 'a', 'a',
		'r', 'a', 'a', 'a'
	}
};

static TPattern AI_Pattern_Defense_3_15 =
{
	4,
	4,
	10000,
	{
		'a', 'a', 'a', 'r',
		'a', 'a', 'r', 'a',
		'a', ' ', 'a', 'a',
		'r', 'a', 'a', 'a'
	}
};

static TPattern AI_Pattern_Defense_3_16 =
{
	4,
	4,
	10000,
	{
		'a', 'a', 'a', 'r',
		'a', 'a', 'r', 'a',
		'a', 'r', 'a', 'a',
		' ', 'a', 'a', 'a'
	}
};

// The patterns can't be directly initialized in a unique array because each pattern cells are of variable size
static TPattern *Pointer_AI_Offensive_Patterns[] =
{
	/*&Pattern_5_1,
	&Pattern_5_2,
	&Pattern_5_3,
	&Pattern_5_4,*/
	NULL
};

static TPattern *Pointer_AI_Defensive_Patterns[] =
{
	&AI_Pattern_Common_1_1,
	&AI_Pattern_Defense_1,
	&AI_Pattern_Defense_2,
	&AI_Pattern_Defense_3,
	&AI_Pattern_Defense_4,
	&AI_Pattern_Defense_5,
	&AI_Pattern_Defense_6,
	&AI_Pattern_Defense_7,
	&AI_Pattern_Defense_8,
	&AI_Pattern_Defense_9,
	&AI_Pattern_Defense_10,
	&AI_Pattern_Defense_11,
	&AI_Pattern_Defense_12,
	&AI_Pattern_Defense_13,
	&AI_Pattern_Defense_14,
	&AI_Pattern_Defense_15,
	&AI_Pattern_Defense_16,
	&AI_Pattern_Defense_17,
	&AI_Pattern_Defense_18,
	&AI_Pattern_Defense_19,
	&AI_Pattern_Defense_20,
	&AI_Pattern_Defense_3_1,
	&AI_Pattern_Defense_3_2,
	&AI_Pattern_Defense_3_3,
	&AI_Pattern_Defense_3_4,
	&AI_Pattern_Defense_3_5,
	&AI_Pattern_Defense_3_6,
	&AI_Pattern_Defense_3_7,
	&AI_Pattern_Defense_3_8,
	&AI_Pattern_Defense_3_9,
	&AI_Pattern_Defense_3_10,
	&AI_Pattern_Defense_3_11,
	&AI_Pattern_Defense_3_12,
	&AI_Pattern_Defense_3_13,
	&AI_Pattern_Defense_3_14,
	&AI_Pattern_Defense_3_15,
	&AI_Pattern_Defense_3_16,
	NULL
};

//-------------------------------------------------------------------------------------------------
// Private functions
//-------------------------------------------------------------------------------------------------
/** Evaluate the grid "gain" for a specified cell type. Patterns that would lead to victory return a high number whereas isolated cells return a low value.
 * @param Cell_Content The cell to evaluate the grid for.
 * @return A positive number indicating how many "near-to-victory" patterns the grid contains for the specified cell type.
 */
static int AIEvaluateGrid(TGridCellContent Cell_Content)
{
	int Grid_Evaluation = 0, i, Pattern_Matches_Count;
	TPattern **Pointer_Patterns;
	
	assert(Cell_Content != GRID_CELL_CONTENT_EMPTY);
	
	if (Cell_Content == GRID_CELL_CONTENT_CROSS) Pointer_Patterns = Pointer_AI_Offensive_Patterns;
	else Pointer_Patterns = Pointer_AI_Defensive_Patterns;
	#ifndef NDEBUG
		syslog(LOG_INFO, "[%s] Evaluating %s strategy...", __FUNCTION__, Cell_Content == GRID_CELL_CONTENT_CROSS ? "offensive" : "defensive");
	#endif
	
	for (i = 0; Pointer_Patterns[i] != NULL; i++)
	{
		Pattern_Matches_Count = PatternMatchAll(Pointer_Patterns[i], Cell_Content);
		#ifndef NDEBUG
			if (Pattern_Matches_Count > 0) syslog(LOG_INFO, "[%s] Found %d matches for pattern %d valuated to %d.", __FUNCTION__, Pattern_Matches_Count, i, Pointer_Patterns[i]->Value);
		#endif
		Grid_Evaluation += Pattern_Matches_Count * Pointer_Patterns[i]->Value;
	}
	return Grid_Evaluation;
}

//-------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------
void AIMakeMove(void)
{
	unsigned int Row, Column, Best_Offensive_Row, Best_Offensive_Column, Best_Defensive_Row, Best_Defensive_Column;
	int Best_Offensive_Value = 0, Best_Defensive_Value = AI_DEFENSIVE_STRATEGY_DEFAULT_VALUE, Value;
	
	// Check all allowed cells
	for (Row = 0; Row < Grid_Size; Row++)
	{
		for (Column = 0; Column < Grid_Size; Column++)
		{
			// Bypass the cells that can't be played according to rules
			if (!GridIsMoveAllowed(Row, Column)) continue;
			
			// The cell is allowed, what if the computer fills it ?
			GridSetCellContent(Row, Column, GRID_CELL_CONTENT_CROSS);
			
			// TODO
			#if 0
			// Is that move useful for an offensive strategy ?
			Value = AIEvaluateOffensiveStrategy();
			if (Value > Best_Offensive_Value)
			{
				Best_Offensive_Value = Value;
				Best_Offensive_Row = Row;
				Best_Offensive_Column = Column;
			}
			#endif
			
			// Is that move useful for a defensive strategy ?
			Value = AIEvaluateGrid(GRID_CELL_CONTENT_CIRCLE);
			if (Value < Best_Defensive_Value)
			{
				Best_Defensive_Value = Value;
				Best_Defensive_Row = Row;
				Best_Defensive_Column = Column;
			}
			
			// Remove the cell
			GridSetCellContent(Row, Column, GRID_CELL_CONTENT_EMPTY);
		}
	}
	
	#ifndef NDEBUG
		syslog(LOG_INFO, "[%s] Best offensive value : %d; best defensive value : %d.", __FUNCTION__, Best_Offensive_Value, Best_Defensive_Value);
	#endif
	
	// Choose the defensive or offensive move
	if ((Best_Offensive_Value == 0) && (Best_Defensive_Value == AI_DEFENSIVE_STRATEGY_DEFAULT_VALUE))
	{
		do
		{
			Row = rand() % Grid_Size;
			Column = rand() % Grid_Size;
		} while (!GridIsMoveAllowed(Row, Column));
		
		#ifndef NDEBUG
			syslog(LOG_INFO, "[%s] None strategy worked, playing RANDOM cell...", __FUNCTION__);
		#endif
	}
	/*else if (Best_Defensive_Value <= Best_Offensive_Value) // Prefer a defensive move to block the player
	{
		Row = Best_Defensive_Row;
		Column = Best_Defensive_Column;
		
		#ifndef NDEBUG
			syslog(LOG_INFO, "[%s] Playing DEFENSIVE strategy.", __FUNCTION__);
		#endif
	}
	else
	{
		Row = Best_Offensive_Row;
		Column = Best_Offensive_Column;
		
		#ifndef NDEBUG
			syslog(LOG_INFO, "[%s] Playing OFFENSIVE strategy.", __FUNCTION__);
		#endif
	}*/
	
	// TEST
	else
	{
		Row = Best_Defensive_Row;
		Column = Best_Defensive_Column;
	}
	
	#ifndef NDEBUG
		syslog(LOG_INFO, "[%s] Move coordinates : (%d, %d).", __FUNCTION__, Row, Column);
	#endif
	
	// Put the cell on the grid
	assert(GridIsMoveAllowed(Row, Column));
	GridSetCellContent(Row, Column, GRID_CELL_CONTENT_CROSS);
	InterfaceDisplayCell(Row, Column, GRID_CELL_CONTENT_CROSS);
}