/** @file Grid.h
 * The game grid.
 * @author Adrien RICCIARDI
 */
#ifndef H_GRID_H
#define H_GRID_H

//-------------------------------------------------------------------------------------------------
// Types
//-------------------------------------------------------------------------------------------------
/** A grid cell content. */
typedef enum
{
	GRID_CELL_CONTENT_EMPTY,
	GRID_CELL_CONTENT_CROSS,
	GRID_CELL_CONTENT_CIRCLE
} TGridCellContent;

//-------------------------------------------------------------------------------------------------
// Variables
//-------------------------------------------------------------------------------------------------
/** The grid size in cells. */
extern unsigned int Grid_Size;

//-------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------
/** Retrieve a cell content.
 * @param Row The cell row.
 * @param Column The cell column.
 * @return The cell content.
 */
TGridCellContent GridGetCellContent(unsigned int Row, unsigned int Column);

/** Set a cell content.
 * @param Row The cell row.
 * @param Column The cell column.
 * @param Content The cell content.
 */
void GridSetCellContent(unsigned int Row, unsigned int Column, TGridCellContent Cell_Content);

/** Tell whether it is possible or not to fill the specified cell.
 * @param Row The cell to fill row.
 * @param Column The cell to fill column.
 * @return 1 if it is possible to fill the cell,
 * @return 0 if the cell can't be filled without breaking game rules.
 */
int GridIsMoveAllowed(unsigned int Row, unsigned int Column);

/** Tell if the game is won by these cells.
 * @param Cell_Content The cell to check.
 * @return 1 if the game is won,
 * @return 0 if not.
 */
int GridIsGameWon(TGridCellContent Cell_Content);

#endif