#include "HackInstructionList.h"

// Implementation of the Linked list functions

void HI_push_back(HackInstructions* list, HackInstruction* instruction) {
    instruction->next = NULL;
    if (*list == NULL) {
        *list = instruction;
        return;
    } else {
        HackInstructions temp = *list;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = instruction;
        return;
    }
}

void HI_pop_front(HackInstructions* list) {
    if (*list == NULL) {
        return;
    } else {
        HackInstructions prev = *list;
        *list = (*list)->next;
        // Free any malloc'd memory for list here
        free(prev);
        return;
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

void HI_print_all_instructions(HackInstructions* list) {
    HackInstructions temp = *list;
    if (temp == NULL) {
        fprintf(stderr, "The list is empty now ??\n");
    } else {
        while (temp != NULL) {
            printInstruction(temp);
            temp = temp->next;
        }
    }
}

void HI_delete_all_instructions(HackInstructions* list) {
    while (*list != NULL) {
        HI_pop_front(list);
    }
}
