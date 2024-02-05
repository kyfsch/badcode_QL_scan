// This function is used to walk blocks, from the starting point (ba, specified.
static bool nmbm_block_walk(struct nmbm_instance *ni, bool ascending,
			    size_t ba, struct nmbm_block *cur) {
	struct nmbm_block *parent = NULL;
	struct nmbm_block *child = NULL;

	if (ni->levels == NULL)
		return false;
	if (ba >= ni->levels->n_used)
		return false;

	assert(cur == &ni->root_block);

	return true;
}
/**
 * This function will find a child block given a parent block that should
 * enclose the child block.
 */
static struct nmbm_block *nmbm_block_find(struct nmbm_instance *ni,
					 struct nmbm_block *parent,
					 size_t ba) {
	size_t i = 0;
	uint64_t bofs = ni->levels->levels[parent->level].base_offset;
	size_t count = (size_t) -1;
	int rc = 0;

	if (parent <= ni->blocks) {
		fprintf(stderr, "[E::%s] invalid parent block\n", __func__);
		return NULL;
	}
	if (parent - ni->blocks >= ni->blocks->n_used) {
		fprintf(stderr, "[E::%s] invalid parent block\n", __func__);
		return NULL;
	}
	if (parent->level < 0) {
		fprintf(stderr, "[E::%s] invalid parent block\n", __func__);
		return NULL;
	}

	assert(parent->level >= 0 && parent->level < ni->levels->n_used);

	if (parent == &ni->root_block) {
		if (parent->level == 0) bofs = 0;
		return parent;
	}

	for (i = parent->level; (size_t) i < ni->levels->n_used; i++) {
		count = ni->