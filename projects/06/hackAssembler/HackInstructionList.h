#ifndef HACKINSTRUCTIONLIST_H_
#define HACKINSTRUCTIONLIST_H_

#include <stdlib.h>
#include "HackInstruction.h"

typedef HackInstruction* HackInstructions;

// TODO : List implementation for Instructions
// Best abstraction for the list would be a queue
//    push_back is needed
//    front is needed
//    pop_front is needed too
// Best implementation would be using a deque
//    Constant time insertion/deletion at beginning and end
//    Constant time random access (indexed by lineNumber) is a bonus
// For the time being, we'll just use a linked list
// Push an Instruction at the end of the instructions list
void HI_push_back(HackInstructions* list, HackInstruction* instruction);
void HI_pop_front(HackInstructions* list);
// For the accessors it is better to use pointers since the methods of
// HackInstruction expect addresses
HackInstruction* HI_front(HackInstructions list);
HackInstruction* HI_back(HackInstructions list);
// Iterator
HackInstructions HI_next(HackInstructions list);
void HI_print_all_instructions(HackInstructions* list);
void HI_delete_all_instructions(HackInstructions* list);
#endif  // HACKINSTRUCTIONLIST_H_
