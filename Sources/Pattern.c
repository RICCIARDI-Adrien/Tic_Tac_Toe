/** @file Pattern.c
 * @see Pattern.h for description.
 * @author Adrien RICCIARDI
 */
#include <assert.h>
#include <Grid.h>
#include <Pattern.h>

//-------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------
// TODO for victory detection
/*int PatternMatchFirst(TPattern *Pointer_Pattern, TGridCellContent Cell_Type)
{
	unsigned int Row, Column, Rows_Count, Columns_Count, Pattern_Row, Pattern_Column, Pattern_Value;
	
	// Do some debug safety checks
	assert(Pointer_Pattern->Rows_Count > 0);
	assert(Pointer_Pattern->Columns_Count > 0);
	assert(Pointer_Pattern->Rows_Count < Grid_Size);
	assert(Pointer_Pattern->Columns_Count < Grid_Size);
	
	// Compute the final row and column to check until the pattern goes out of the grid
	Rows_Count = Grid_Size - Pointer_Pattern->Rows_Count + 1; // +1 to allow a 1-row pattern to be compared with the grid's last row
	Columns_Count = Grid_Size - Pointer_Pattern->Columns_Count + 1; // +1 to allow a 1-column pattern to be compared with the grid's last column
	
	for (Row = 0; Row < Rows_Count; Row++)
	{
		for (Column = 0; Column < Columns_Count; Column++)
		{
			// Compare the whole pattern starting at the current coordinates
			for (Pattern_Row = 0; Pattern_Row < Pointer_Pattern->Rows_Count; Pattern_Row++)
			{
				for (Pattern_Column = 0; Pattern_Column < Pointer_Pattern->Columns_Count; Pattern_Column++)
				{
					// Cache the pattern value
					Pattern_Value = Pointer_Pattern->Cells[Pattern_Row * Pointer_Pattern->Columns_Count + Pattern_Column];
					assert((Pattern_Value == 0) || (Pattern_Value == 1));
					
					// Should this cell be ignored ?
					if (Pattern_Value == 0) continue;
					
					// This cell should match with the provided cell type
					if (GridGetCellContent(Row + Pattern_Row, Column + Pattern_Column) != Cell_Type) goto Check_Next_Column;
				}
			}
			return 1; // The pattern fully matched
			
		Check_Next_Column:
			continue; // The label can't be the last line before the closing scope
		}
	}
	return 0; // The pattern could not be found
}*/

int PatternMatchAll(TPattern *Pointer_Pattern, TGridCellContent Cell_Type)
{
	unsigned int Row, Column, Rows_Count, Columns_Count, Pattern_Row, Pattern_Column;
	char Pattern_Value;
	int Matches_Count = 0;
	
	// Do some debug safety checks
	assert(Pointer_Pattern->Rows_Count > 0);
	assert(Pointer_Pattern->Columns_Count > 0);
	assert(Pointer_Pattern->Rows_Count < Grid_Size);
	assert(Pointer_Pattern->Columns_Count < Grid_Size);
	
	// Compute the final row and column to check until the pattern goes out of the grid
	Rows_Count = Grid_Size - Pointer_Pattern->Rows_Count + 1; // +1 to allow a 1-row pattern to be compared with the grid's last row
	Columns_Count = Grid_Size - Pointer_Pattern->Columns_Count + 1; // +1 to allow a 1-column pattern to be compared with the grid's last column
	
	for (Row = 0; Row < Rows_Count; Row++)
	{
		for (Column = 0; Column < Columns_Count; Column++)
		{
			// Compare the whole pattern starting at the current coordinates
			for (Pattern_Row = 0; Pattern_Row < Pointer_Pattern->Rows_Count; Pattern_Row++)
			{
				for (Pattern_Column = 0; Pattern_Column < Pointer_Pattern->Columns_Count; Pattern_Column++)
				{
					// Cache the pattern value
					Pattern_Value = Pointer_Pattern->Cells[Pattern_Row * Pointer_Pattern->Columns_Count + Pattern_Column];
					assert((Pattern_Value == 'r') || (Pattern_Value == 'o') || (Pattern_Value == ' ') || (Pattern_Value == 'a'));
					
					switch (Pattern_Value)
					{
						// Match any cell
						case 'a':
							continue;
							
						// Match the requested cell
						case 'r':
							if (GridGetCellContent(Row + Pattern_Row, Column + Pattern_Column) != Cell_Type) goto Check_Next_Column;
							break;
							
						// Match the other cell
						case 'o':
							if (GridGetCellContent(Row + Pattern_Row, Column + Pattern_Column) == Cell_Type) goto Check_Next_Column;
							break;
							
						// Match an empty cell
						case ' ':
							if (GridGetCellContent(Row + Pattern_Row, Column + Pattern_Column) != GRID_CELL_CONTENT_EMPTY) goto Check_Next_Column;
							break;
					}
				}
			}
			Matches_Count++; // The pattern fully matched
			
		Check_Next_Column:
			continue; // The label can't be the last line before the closing scope
		}
	}
	
	return Matches_Count;
}