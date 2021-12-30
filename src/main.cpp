#include "main.h"
#include "game.h"

/* ADVANTAGES/DISADVANTAGES LINKED LIST / ARRAY
 * 	The advantage of using linked-list is it is dynamically allocated,
 *  so the user can create as many commands as they want as long as their
 *  computer have enough memory.
 *  Disadvantage of a linked-list is that "indexing" it is an O(n) operation
 *  when indexing the node to generate questions for the game 
 * 	as opposed to array's O(1) operation for index.
 *
 *	An advantage of using the array data type is we did not have to allocate
 *  memory ourselves which saves us the abstraction of garbage collection.
 *	However, a disadvantage of array is that it is not dynamically allocated. So there
 *	is a fixed amount of profiles that can be saved.
 */

int main(void)
{
	Game game;
	game.run();


	return 0;
}
