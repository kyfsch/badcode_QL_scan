// This function is used to walk blocks, from the starting point (ba, specified.
static bool nmbm_block_walk(struct nmbm_instance *ni, bool ascending, struct nmbm_buffer_area *ba, struct nmbm_block *b, void *arg)
{
    struct nmbm_context *ctx = (struct nmbm_context *)arg;

    // Find beginning of the block.
    struct nmbm_buffer_area *ba_prev = nmbm_buffer_starting(ni, b->start);

    // Detect boundary crossing.
    // (Not using ba_prev, because it will never be NULL here.)
    if (ba != ba_prev) {
        // Boundary crossed.
        // Mark end of the block as the end of a buffer area.
        const uint64_t lba_ba_end = (ba_prev ? ba_prev->lba_end : 0U);
        if (b->end > lba_ba_end) {
            nmbm_block_set_end(ni, ba, b->end, lba_ba_end);

            // If we still have a valid part, rewalk and see if we can find another block.
            if (b->start <= lba_ba_end)
                return true;
            else
                return false;
        }
    }

    // Increment the block counter.
    ctx->n++;

    // Go to the next block.
    return (b && ascending);
}

// This function is used to mark blocks of bad blocks.
static bool nmbm_block_bad_mark(struct nmbm_instance *ni, bool ascending, struct nmbm_buffer_area *ba, struct nmbm_block *b, void *arg)
{
    struct nmbm_context *ctx = (struct nmbm_context *)arg;

    // Find beginning of the block to the right of our starting point.
    struct nmbm_buffer_area *ba_next = nmbm_buffer_starting(ni, b->start + b->len);

    // Detect boundary crossing.
    if (ba != ba && ba_next != ba) {
        // Crossed.
        struct nmbm_bad_block bb;