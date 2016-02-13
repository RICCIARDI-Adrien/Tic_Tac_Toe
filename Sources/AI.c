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
// Private variables
//-------------------------------------------------------------------------------------------------
// Common patterns
static TPattern AI_Pattern_Common_4_1 =
{
	1,
	5,
	100000,
	{
		' ', 'r', 'r', 'r', 'r'
	}
};

static TPattern AI_Pattern_Common_4_2 =
{
	1,
	5,
	100000,
	{
		'r', ' ', 'r', 'r', 'r'
	}
};

static TPattern AI_Pattern_Common_4_3 =
{
	1,
	5,
	100000,
	{
		'r', 'r', ' ', 'r', 'r'
	}
};

static TPattern AI_Pattern_Common_4_4 =
{
	1,
	5,
	100000,
	{
		'r', 'r', 'r', ' ', 'r'
	}
};

static TPattern AI_Pattern_Common_4_5 =
{
	1,
	5,
	100000,
	{
		'r', 'r', 'r', 'r', ' '
	}
};

static TPattern AI_Pattern_Common_4_6 =
{
	5,
	1,
	100000,
	{
		' ',
		'r',
		'r',
		'r',
		'r'
	}
};

static TPattern AI_Pattern_Common_4_7 =
{
	5,
	1,
	100000,
	{
		'r',
		' ',
		'r',
		'r',
		'r'
	}
};

static TPattern AI_Pattern_Common_4_8 =
{
	5,
	1,
	100000,
	{
		'r',
		'r',
		' ',
		'r',
		'r'
	}
};

static TPattern AI_Pattern_Common_4_9 =
{
	5,
	1,
	100000,
	{
		'r',
		'r',
		'r',
		' ',
		'r'
	}
};

static TPattern AI_Pattern_Common_4_10 =
{
	5,
	1,
	100000,
	{
		'r',
		'r',
		'r',
		'r',
		' '
	}
};

static TPattern AI_Pattern_Common_4_11 =
{
	5,
	5,
	100000,
	{
		' ', 'a', 'a', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', 'a', 'a', 'r'
	}
};

static TPattern AI_Pattern_Common_4_12 =
{
	5,
	5,
	100000,
	{
		'r', 'a', 'a', 'a', 'a',
		'a', ' ', 'a', 'a', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', 'a', 'a', 'r'
	}
};

static TPattern AI_Pattern_Common_4_13 =
{
	5,
	5,
	100000,
	{
		'r', 'a', 'a', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		'a', 'a', ' ', 'a', 'a',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', 'a', 'a', 'r'
	}
};

static TPattern AI_Pattern_Common_4_14 =
{
	5,
	5,
	100000,
	{
		'r', 'a', 'a', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', 'a', 'a', ' ', 'a',
		'a', 'a', 'a', 'a', 'r'
	}
};

static TPattern AI_Pattern_Common_4_15 =
{
	5,
	5,
	100000,
	{
		'r', 'a', 'a', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', 'a', 'a', ' '
	}
};

static TPattern AI_Pattern_Common_4_16 =
{
	5,
	5,
	100000,
	{
		'a', 'a', 'a', 'a', ' ',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a'
	}
};

static TPattern AI_Pattern_Common_4_17 =
{
	5,
	5,
	100000,
	{
		'a', 'a', 'a', 'a', 'r',
		'a', 'a', 'a', ' ', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a'
	}
};

static TPattern AI_Pattern_Common_4_18 =
{
	5,
	5,
	100000,
	{
		'a', 'a', 'a', 'a', 'r',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', ' ', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a'
	}
};

static TPattern AI_Pattern_Common_4_19 =
{
	5,
	5,
	100000,
	{
		'a', 'a', 'a', 'a', 'r',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', ' ', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a'
	}
};

static TPattern AI_Pattern_Common_4_20 =
{
	5,
	5,
	100000,
	{
		'a', 'a', 'a', 'a', 'r',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		' ', 'a', 'a', 'a', 'a'
	}
};

static TPattern AI_Pattern_Common_3_1 =
{
	1,
	4,
	10000,
	{
		' ', 'r', 'r', 'r'
	}
};

static TPattern AI_Pattern_Common_3_2 =
{
	1,
	4,
	10000,
	{
		'r', ' ', 'r', 'r'
	}
};

static TPattern AI_Pattern_Common_3_3 =
{
	1,
	4,
	10000,
	{
		'r', 'r', ' ', 'r'
	}
};

static TPattern AI_Pattern_Common_3_4 =
{
	1,
	4,
	10000,
	{
		'r', 'r', 'r', ' '
	}
};

static TPattern AI_Pattern_Common_3_5 =
{
	4,
	1,
	10000,
	{
		' ',
		'r',
		'r',
		'r'
	}
};

static TPattern AI_Pattern_Common_3_6 =
{
	4,
	1,
	10000,
	{
		'r',
		' ',
		'r',
		'r'
	}
};

static TPattern AI_Pattern_Common_3_7 =
{
	4,
	1,
	10000,
	{
		'r',
		'r',
		' ',
		'r'
	}
};

static TPattern AI_Pattern_Common_3_8 =
{
	4,
	1,
	10000,
	{
		'r',
		'r',
		'r',
		' '
	}
};

static TPattern AI_Pattern_Common_3_9 =
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

static TPattern AI_Pattern_Common_3_10 =
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

static TPattern AI_Pattern_Common_3_11 =
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

static TPattern AI_Pattern_Common_3_12 =
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

static TPattern AI_Pattern_Common_3_13 =
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

static TPattern AI_Pattern_Common_3_14 =
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

static TPattern AI_Pattern_Common_3_15 =
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

static TPattern AI_Pattern_Common_3_16 =
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

// The less valuated pattern, needed for the evaluation function to return something different from zero when no useful pattern is found. Thus, some earlier grids can be successfully evaluated
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
static TPattern AI_Pattern_Attack_5_1 =
{
	1,
	5,
	1000000,
	{
		'r', 'r', 'r', 'r', 'r'
	}
};

static TPattern AI_Pattern_Attack_5_2 =
{
	5,
	1,
	1000000,
	{
		'r',
		'r',
		'r',
		'r',
		'r'
	}
};

static TPattern AI_Pattern_Attack_5_3 =
{
	5,
	5,
	1000000,
	{
		'r', 'a', 'a', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', 'a', 'a', 'r'
	}
};

static TPattern AI_Pattern_Attack_5_4 =
{
	5,
	5,
	1000000,
	{
		'a', 'a', 'a', 'a', 'r',
		'a', 'a', 'a', 'r', 'a',
		'a', 'a', 'r', 'a', 'a',
		'a', 'r', 'a', 'a', 'a',
		'r', 'a', 'a', 'a', 'a'
	}
};

// Defense-specific patterns
// TODO if needed

// The patterns can't be directly initialized in a unique array because each pattern cells are of variable size
static TPattern *Pointer_AI_Offensive_Patterns[] =
{
	&AI_Pattern_Attack_5_1,
	&AI_Pattern_Attack_5_2,
	&AI_Pattern_Attack_5_3,
	&AI_Pattern_Attack_5_4,
	&AI_Pattern_Common_4_1,
	&AI_Pattern_Common_4_2,
	&AI_Pattern_Common_4_3,
	&AI_Pattern_Common_4_4,
	&AI_Pattern_Common_4_5,
	&AI_Pattern_Common_4_6,
	&AI_Pattern_Common_4_7,
	&AI_Pattern_Common_4_8,
	&AI_Pattern_Common_4_9,
	&AI_Pattern_Common_4_10,
	&AI_Pattern_Common_4_11,
	&AI_Pattern_Common_4_12,
	&AI_Pattern_Common_4_13,
	&AI_Pattern_Common_4_14,
	&AI_Pattern_Common_4_15,
	&AI_Pattern_Common_4_16,
	&AI_Pattern_Common_4_17,
	&AI_Pattern_Common_4_18,
	&AI_Pattern_Common_4_19,
	&AI_Pattern_Common_4_20,
	&AI_Pattern_Common_3_1,
	&AI_Pattern_Common_3_2,
	&AI_Pattern_Common_3_3,
	&AI_Pattern_Common_3_4,
	&AI_Pattern_Common_3_5,
	&AI_Pattern_Common_3_6,
	&AI_Pattern_Common_3_7,
	&AI_Pattern_Common_3_8,
	&AI_Pattern_Common_3_9,
	&AI_Pattern_Common_3_10,
	&AI_Pattern_Common_3_11,
	&AI_Pattern_Common_3_12,
	&AI_Pattern_Common_3_13,
	&AI_Pattern_Common_3_14,
	&AI_Pattern_Common_3_15,
	&AI_Pattern_Common_3_16,
	&AI_Pattern_Common_1_1,
	NULL
};

static TPattern *Pointer_AI_Defensive_Patterns[] =
{
	&AI_Pattern_Common_1_1,
	&AI_Pattern_Common_4_1,
	&AI_Pattern_Common_4_2,
	&AI_Pattern_Common_4_3,
	&AI_Pattern_Common_4_4,
	&AI_Pattern_Common_4_5,
	&AI_Pattern_Common_4_6,
	&AI_Pattern_Common_4_7,
	&AI_Pattern_Common_4_8,
	&AI_Pattern_Common_4_9,
	&AI_Pattern_Common_4_10,
	&AI_Pattern_Common_4_11,
	&AI_Pattern_Common_4_12,
	&AI_Pattern_Common_4_13,
	&AI_Pattern_Common_4_14,
	&AI_Pattern_Common_4_15,
	&AI_Pattern_Common_4_16,
	&AI_Pattern_Common_4_17,
	&AI_Pattern_Common_4_18,
	&AI_Pattern_Common_4_19,
	&AI_Pattern_Common_4_20,
	&AI_Pattern_Common_3_1,
	&AI_Pattern_Common_3_2,
	&AI_Pattern_Common_3_3,
	&AI_Pattern_Common_3_4,
	&AI_Pattern_Common_3_5,
	&AI_Pattern_Common_3_6,
	&AI_Pattern_Common_3_7,
	&AI_Pattern_Common_3_8,
	&AI_Pattern_Common_3_9,
	&AI_Pattern_Common_3_10,
	&AI_Pattern_Common_3_11,
	&AI_Pattern_Common_3_12,
	&AI_Pattern_Common_3_13,
	&AI_Pattern_Common_3_14,
	&AI_Pattern_Common_3_15,
	&AI_Pattern_Common_3_16,
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
	unsigned int Row, Column, Best_Offensive_Row = 0, Best_Offensive_Column = 0, Best_Defensive_Row = 0, Best_Defensive_Column = 0;
	int Best_Offensive_Value = 0, Best_Defensive_Value = AI_DEFENSIVE_STRATEGY_DEFAULT_VALUE, Best_Enemy_Move_Value = 0, Value;
	
	// Check all allowed cells
	for (Row = 0; Row < Grid_Size; Row++)
	{
		for (Column = 0; Column < Grid_Size; Column++)
		{
			// Bypass the cells that can't be played according to rules
			if (!GridIsMoveAllowed(Row, Column)) continue;
			
			// The cell is allowed, what if the computer fills it ?
			GridSetCellContent(Row, Column, GRID_CELL_CONTENT_CROSS);
			
			// Is that move useful for an offensive strategy ?
			Value = AIEvaluateGrid(GRID_CELL_CONTENT_CROSS);
			if (Value > Best_Offensive_Value)
			{
				Best_Offensive_Value = Value;
				Best_Offensive_Row = Row;
				Best_Offensive_Column = Column;
			}
			
			// Is that move useful for a defensive strategy ?
			Value = AIEvaluateGrid(GRID_CELL_CONTENT_CIRCLE);
			// The best defensive move is the one that minimize the enemy grid value
			if (Value < Best_Defensive_Value)
			{
				Best_Defensive_Value = Value;
				Best_Defensive_Row = Row;
				Best_Defensive_Column = Column;
			}
			// Find also the best move the enemy can do to compare it with the best move the computer can do
			if (Value > Best_Enemy_Move_Value) Best_Enemy_Move_Value = Value;
			
			// Remove the cell
			GridSetCellContent(Row, Column, GRID_CELL_CONTENT_EMPTY);
		}
	}
	
	#ifndef NDEBUG
		syslog(LOG_INFO, "[%s] Best offensive value : %d; best defensive value : %d.", __FUNCTION__, Best_Offensive_Value, Best_Defensive_Value);
	#endif
	
	// Choose the defensive or offensive move
	if ((Best_Enemy_Move_Value < 10000) || (Best_Offensive_Value > 1000000)) // Attack only if there is a granted gain or if the player can't do anything harmful, otherwise prefer a defensive move to block the player
	{
		Row = Best_Offensive_Row;
		Column = Best_Offensive_Column;
		
		#ifndef NDEBUG
			syslog(LOG_INFO, "[%s] Playing OFFENSIVE strategy.", __FUNCTION__);
		#endif
	}
	else
	{
		Row = Best_Defensive_Row;
		Column = Best_Defensive_Column;
		
		#ifndef NDEBUG
			syslog(LOG_INFO, "[%s] Playing DEFENSIVE strategy.", __FUNCTION__);
		#endif
	}
	
	#ifndef NDEBUG
		syslog(LOG_INFO, "[%s] Move coordinates : (%d, %d).", __FUNCTION__, Row, Column);
	#endif
	
	// Put the cell on the grid
	assert(GridIsMoveAllowed(Row, Column));
	GridSetCellContent(Row, Column, GRID_CELL_CONTENT_CROSS);
	InterfaceDisplayCell(Row, Column, GRID_CELL_CONTENT_CROSS);
}