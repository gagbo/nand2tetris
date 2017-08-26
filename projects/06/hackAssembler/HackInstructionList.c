#include "HackInstructionList.h"

// Implementation of the Linked list functions

HackInstructions HI_push_back(HackInstructions list,
                              HackInstruction* instruction) {
    instruction->next = NULL;
    if (list == NULL) {
        list = instruction;
        return list;
    } else {
        HackInstructions temp = list;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = instruction;
        return list;
    }
}

HackInstructions HI_pop_front(HackInstructions list) {
    if (list == NULL) {
        return NULL;
    } else {
        HackInstructions temp = list;
        temp = list->next;
        // Free any malloc'd memory for list here
        free(list);
        return temp;
    }
}

HackInstruction* HI_front(HackInstructions list) { return list; }

HackInstruction* HI_back(HackInstructions list) {
    if (list == NULL) {
        return NULL;
    } else {
        HackInstructions temp = list;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        return temp;
    }
}

HackInstructions HI_next(HackInstructions list) { return list->next; }

void HI_print_all_instructions(HackInstructions list) {
    HackInstructions temp = list;
    if (temp == NULL) {
        fprintf(stderr, "The list is empty now ??\n");
    } else {
        while (temp != NULL) {
            printInstruction(temp);
            temp = temp->next;
        }
    }
}

void HI_delete_all_instructions(HackInstructions list) {
    while (list != NULL) {
        list = HI_pop_front(list);
    }
}
