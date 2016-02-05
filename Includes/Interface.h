/** @file Interface.h
 * A terminal-compatible text interface.
 * @author Adrien RICCIARDI
 */
#ifndef H_INTERFACE_H
#define H_INTERFACE_H

//-------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------
/** Initialize the terminal in raw mode and clear it. */
void InterfaceInitialize(void);

void InterfaceQuit(void);

//void InterfaceDisplayEmptyGrid(void);

/** Display a cell content.
 * @param Row The cell row (Y axis).
 * @param Column The cell column (X axis).
 * @param Cell_Content The cell content to display.
 */
void InterfaceDisplayCell(unsigned int Row, unsigned int Column, TGridCellContent Cell_Content);

/** Wait for a user key.
 * @return The last pressed key.
 */
//char InterfaceWaitForUser(void);

/** Display or hide the cursor.
 * @param Row The cursor row.
 * @param Column The cursor column.
 * @param Is_Cursor_Visible Whether to display the cursor (set to 1) or to remove the cursor trace (set to 0).
 */
void InterfaceDisplayCursor(unsigned int Row, unsigned int Column, int Is_Cursor_Visible);

#endif