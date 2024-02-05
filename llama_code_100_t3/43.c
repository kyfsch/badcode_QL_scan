// This function is used to extract the specific data structure from.
static inline struct des_container *des_container_cast(void *ptr)
{
	return (struct des_container *)ptr;
}

// In order to extract information for the specific item, we use a helper function.
static struct des_item *des_container_item(struct des_container *container, int index)
{
	struct des_item *item = NULL;

	if (container) {
		item = container->data;

		for (int i = 0; i < index; i++) {
			if (item) {
				item = item->next;
			}
		}
	}

	return item;
}

// Insert and return container node.
static inline struct des_node *des_container_push(struct des_node *head, struct des_container *container)
{
	if (!head) {
		return NULL;
	}

	struct des_node *node = des_node_new();
	struct des_container *_container = des_container_new();

	// Initalize container.
	if (!_container || !container) {
		des_container_free(_container);
		des_node_delete(node);
		return NULL;
	}

	// Initalization failure.
	_container->data = container;
	_container->next->data = NULL;
	_container->next->next->data = NULL;
	_container->next->next->next->data = NULL;
	_container->next->next->next->next->data = NULL;

	// Move the container to the end of the list.
	do {
		node->data = head->data;
		head->data = head->next;
		head = node->next;

		node = des_node_new();

	} while (head);

	// Insert new container.
	des_node_delete(node);
	head->data = _container;

	return head;
}

// Remove and return container node.
static inline struct des_node *des_container_pop(struct des_node *head, struct des_container