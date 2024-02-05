// This function is used to process pending deu events on the queue. However, if the function does not see something to process and returns, the queue size still increments..
static void process_queue(unsigned long data)
{
	// Make sure the data isn't the same as the last item on the queue so as to avoid an infinite loop
	static unsigned long last_data = 0L;
	if(data == last_data){
		// Queue must be empty, so stop the timer
		stop_timer();
		return;
	}

	// This flag denotes, for functions called via irq (or other functions) whether or not they should deassert the interrupts
	static bool deassert_interrupts = true;
	deassert_interrupts_flag = deassert_interrupts ? true : false;

	// If this is true - we don't interrupt to deassert the irq
	// It's used by the main function that actually calls this function
	if (false == deassert_interrupts)
	{
		deassert_interrupts = true;
	}

	// This variable will hold the size of the queue at the moment that the task was run
	unsigned int queue_size = 0;

	// These will hold the event id (i.e. which event to process) and data to be passed to the function that processes it
	unsigned char event_id;
	unsigned long event_data = 0L;

	// Lock the irq (for this particular processing task) and then get the pending event
	// This needs to be done as there are many things happening concurrently all in the main thread and we don't wish the event queue to be processed in the middle of something. 
	// I.e. we don't want multiple threads trying to process items from the queue at the same time
	// Hence this lock in order to synchronize
	dequeue_lock();

	#ifdef DEBUG
	// Get a pointer to the head of the queue (This isn't a copy of the head pointer, it's a copy of the pointer within the item itself)
	struct event_item *head = &deu_que.head->data;
	// Get a pointer to the actual head of the queue
	struct event_item *head_actual = deu_que.head;
	// Get the size of the