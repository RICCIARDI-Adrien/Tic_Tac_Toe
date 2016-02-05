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

#endif