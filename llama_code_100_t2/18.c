// This function is used to set the age-out timer in seconds..
static ssize_t age_out_write(struct file *filp, const char __user *buffer, size_t length, loff_t *off)
{
	// Define the data type for the buffer..
	char data[length];

	// Set the data in the data buffer..
	if((copy_from_user(data, buffer, length))!=0)
	{
		// Print error status..
		printk("AGE_OUT_SEC: Copy from user failed\n");
		return -1;
	}

	// Cast the data to an int..
	int age_out = *(int*)data;

	if((age_out)<0)
	{
		// Set a negative age-out timer..
		set_ageout = (ssize_t)age_out;
	}

	// Print a message to confirm..
	printk("AGE_OUT_SEC: Age-out successfully written with age-out timer %d seconds\n", age_out);

	// Set the value of aging_counter to 1 so it will check the age-out timer in the work queue..
	aging_counter = 1;

	return(length);
}

// Function to calculate the age-out timer..
// It should be called before any operation..
static void reset_age_out_counter()
{
	// Get a reference to the current timer..
	struct timeval time;
	do_gettimeofday(&time);

	// Get the system time..
	long long int sys_clock = tv_to_ns(&time);

	// Add the current time. After this, the start time is the current system clock timesecs(or msecs, etc.).
	start_time += sys_clock;

	// Reset the age-out counter..
	// Because age-out counter was initialized in the initialization function, it should be reset everytime before getting the data..
	age_out_counter = 0;
}

// This function checks the age-out timer..
// It should be called everytime we get the data..
static void check_age_out_counter()
{

	// Get a reference to the current timer..
	struct