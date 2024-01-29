
void walk_blocks(int start_x, int start_y, int num_blocks) {
    int current_x = start_x;
    int current_y = start_y;

    for (int i = 0; i < num_blocks; i++) {
        // Walk to the next block
        current_x++;
        if (current_x >= 10) {
            current_x = 0;
            current_y++;
        }

        // Process the block at the current position
        // ...

        // Optional: Print the current position
        printf("Current position: (%d, %d)\n", current_x, current_y);
    }
}

In this example, the function `walk_blocks` takes three parameters: `start_x` and `start_y` which specify the starting position, and `num_blocks` which specifies the number of blocks to walk through.

The function uses a `for` loop to iterate over the blocks. It updates the current position by incrementing `current_x` and checking if it exceeds the maximum value (in this case, 10). If it does, it resets `current_x` to 0 and increments `current_y`.

After updating the position, you can add code to process the block at the current position. This could include performing certain actions or calculations specific to each block.

You can also add optional code to print the current position at each iteration. This can be useful for debugging or for monitoring the progress of the walking process.