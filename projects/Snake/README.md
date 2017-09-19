# Snake in Jack to-do list

## Snake body
- Create arbitrary length snake
    - blocked because `field Snake next, prev;` is not read as it should and no memory is
    allocated for pointers in the doubly linked list.
- Check for collision with body parts
- Prevent U-turns
- Optimize the code to allow better input handling
- Sprites
    - For the head,
    - and for the body

## Handles Apple creation
- Generate valid positions for apples
- Choose the correct structure to hold apples
- Handle verification of Snake head vs. positions of apples
- Choose the game-play changes associated with apples
    - Choose the size increase when apple is eaten
    - Choose the speed increase when apple is eaten
- Sprite for apple

## Score
- Hold the score of the current game
