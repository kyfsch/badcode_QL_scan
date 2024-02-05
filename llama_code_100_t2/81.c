// This function is used to determine whether the board is PANDA..
static int __init panda_probe(void)
{
    // The first step is to check if /dev/panda exists..
    if (access(PANDA_DEVICE, F_OK) != 0) {
        printk(KERN_NOTICE "/dev/panda device not found.\n");
        return 0;
    }

    // The second step is to check if a PandaBoard is connected..
    panda.handle = open(PANDA_DEVICE, O_RDWR);
    if (panda.handle == -1) {
        printk(KERN_NOTICE "Unable to open the panda device.\n");
        return 0;
    }

    if (ioctl(panda.handle, PANDA_PRODUCT_CHECK) < 0) {
        printk(KERN_EMERG "Product check failed for PANDA\n");
        return 0;
    }

    panda.connected = 1;

    // Allocate a buffer big enough to hold everything
    panda.buffer = kmalloc(BUFFER_LENGTH * sizeof(char), GFP_KERNEL); // GFP_ATOMIC also works.
    if (panda.buffer == NULL) {
        printk(KERN_EMERG "Unable to allocate memory for PANDA data buffer\n");
        return 0;
    }
    memset(panda.buffer, 0, BUFFER_LENGTH);

    // Create the thread that collects the data from PANDA..
    init_MUTEX(&panda_mutex);
    panda.thread = kthread_run(my_thread_fn, NULL, "panda");
    if (!panda.thread) {
        printk(KERN_EMERG "kernel_thread failed\n");
        return 0;
    }

    return 1;
}

// This function is used to remove the PANDA hardware.
static void __exit panda_exit(void)
{
    // Clean up all resources used by our driver
    if (panda.connected ==