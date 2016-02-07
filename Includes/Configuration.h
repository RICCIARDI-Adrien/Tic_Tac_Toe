/** @file Configuration.h
 * Gather all program configurable parameters.
 * @author Adrien RICCIARDI
 */
#ifndef H_CONFIGURATION_H
#define H_CONFIGURATION_H

//-------------------------------------------------------------------------------------------------
// Constants
//-------------------------------------------------------------------------------------------------
/** The maximum allowed grid size. */
#define CONFIGURATION_MAXIMUM_GRID_SIZE 20

/** The "cross" terminal displaying color. */
#define CONFIGURATION_CROSS_DISPLAYING_COLOR 32
/** The "circle" terminal displaying color. */
#define CONFIGURATION_CIRCLE_DISPLAYING_COLOR 35
/** The cursor terminal displaying color (only the color value, the background/foreground attribute will be automatically addded). */
#define CONFIGURATION_CURSOR_DISPLAYING_COLOR 1

/** How many cells of the same type must be aligned to win. */
#define CONFIGURATION_ALIGNED_CELLS_FOR_VICTORY_COUNT 5

#endif