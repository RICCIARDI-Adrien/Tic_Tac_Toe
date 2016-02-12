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

/** Restore the default terminal attributes. */
void InterfaceQuit(void);

/** Put the terminal cursor to the requested position.
 * @param Row The row in the grid.
 * @param Column The column in the grid.
 */
void InterfaceSetCursorPosition(unsigned int Row, unsigned int Column);

/** Display a cell content.
 * @param Row The cell row (Y axis).
 * @param Column The cell column (X axis).
 * @param Cell_Content The cell content to display.
 */
void InterfaceDisplayCell(unsigned int Row, unsigned int Column, TGridCellContent Cell_Content);

/** Display the victory message at the grid end and wait for the player to hit the 'x' key.
 * @param String_Message The message to display.
 */
void InterfaceDisplayVictoryMessage(char *String_Message);

#endif