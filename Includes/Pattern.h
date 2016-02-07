/** @file Pattern.h
 * A simple pattern-matching engine that matches patterns with the whole grid.
 * @author Adrien RICCIARDI
 */
#ifndef H_PATTERN_H
#define H_PATTERN_H

#include <Grid.h>

//-------------------------------------------------------------------------------------------------
// Types
//-------------------------------------------------------------------------------------------------
/** A pattern definition. */
typedef struct
{
	unsigned int Rows_Count; //! The pattern vertical size.
	unsigned int Columns_Count; //! The pattern horizontal size.
	int Value; //! How is the pattern valuated if found.
	unsigned int Cells[]; //! The pattern representation. 1 represents the requested cell type, 0 represents any cell.
} TPattern;

//-------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------
/** Try to match the corresponding pattern made with the provided cell type with the whole grid content.
 * @param Pointer_Pattern The pattern to match.
 * @param Cell_Type The cell the pattern must match.
 * @return 1 if the pattern matched,
 * @return 0 if the pattern did not match.
 */
int PatternMatch(TPattern *Pointer_Pattern, TGridCellContent Cell_Type);

#endif