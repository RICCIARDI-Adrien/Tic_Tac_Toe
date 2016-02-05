/** @file Stack.h
 * A statically allocated stack with a fixed maximum size.
 * @author Adrien RICCIARDI
 */
#ifndef H_STACK_H
#define H_STACK_H

#include <assert.h>
#include <Configuration.h>

//-------------------------------------------------------------------------------------------------
// Constants
//-------------------------------------------------------------------------------------------------
/** How many elements can be stored in a stack. */
#define STACK_MAXIMUM_ELEMENTS_COUNT (CONFIGURATION_MAXIMUM_GRID_SIZE * CONFIGURATION_MAXIMUM_GRID_SIZE)

//-------------------------------------------------------------------------------------------------
// Types
//-------------------------------------------------------------------------------------------------
/** A stack descriptor. */
typedef struct __attribute__((packed))
{
	signed int Stack_Pointer; //! The current stack element index in the array. -1 indicates that the stack is empty.
	unsigned char Elements[STACK_MAXIMUM_ELEMENTS_COUNT]; //! All stack elements. Use 1-byte variables to save memory space.
} TStack;

//-------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------
/** Initialize a stack before it can be used.
 * @param Pointer_Stack The stack to initialize.
 */
static inline __attribute__((always_inline)) void StackInitialize(TStack *Pointer_Stack)
{
	Pointer_Stack->Stack_Pointer = -1;
}

/** Add an element to the stack.
 * @param Pointer_Stack The stack to add the element to.
 * @param Element The element to add.
 */
static inline __attribute__((always_inline)) void StackPush(TStack *Pointer_Stack, unsigned char Element)
{
	assert(Pointer_Stack->Stack_Pointer < STACK_MAXIMUM_ELEMENTS_COUNT);
	
	// Add the element
	Pointer_Stack->Stack_Pointer++;
	Pointer_Stack->Elements[Pointer_Stack->Stack_Pointer] = Element;
}

/** Get the stack top and remove it from the stack.
 * @param Pointer_Stack The stack to get the element from.
 * @return The element located on the stack top.
 */
static inline __attribute__((always_inline)) unsigned char StackPop(TStack *Pointer_Stack)
{
	unsigned char Element;
	
	assert(Pointer_Stack->Stack_Pointer >= 0);
	
	// Retrieve the stack top
	Element = Pointer_Stack->Elements[Pointer_Stack->Stack_Pointer];
	Pointer_Stack->Stack_Pointer--;
	
	return Element;
}

/** Tell if a stack is empty or not.
 * @param Pointer_Stack The stack to check.
 * @return 1 if the stack is empty,
 * @return 0 if the stack contain some elements.
 */
static inline __attribute__((always_inline)) int StackIsEmpty(TStack *Pointer_Stack)
{
	if (Pointer_Stack->Stack_Pointer == -1) return 1;
	return 0;
}

#endif