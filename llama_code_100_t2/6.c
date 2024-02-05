// This function is used to process pending deu events on the queue. However, if the function does not see something to process and returns, the queue size still increments..
static void process_queue(unsigned long data)
{
    struct semaphore sem;
    struct timespec ts;
    if (copy_from_user(&sem, (void __user *)arg, sizeof(struct semaphore)) != 0)
        printk("[DEBUG] User copy error...\n");
    else {
        __sem_init_user(ts, &sem);
    }
    if (__sem_destroy(sem) != 0)
        printk("[DEBUG] sem_wait: semaphore destroyed but value is non-zero.\n");
}

asmlinkage void exit_task_group(int exit_value)
{
    int thread_task_id;
    if (copy_from_user(&thread_task_id, (void __user *)arg, sizeof(int)) != 0)
        printk("[DEBUG] User copy error...\n");
    return;
}

asmlinkage void sleep_on_queue(void)
{
    struct timespec ts;
    if (copy_from_user(&ts, (void __user *)arg, sizeof(struct timespec)) != 0)
        printk("[DEBUG] User copy error...\n");
    else {
        task_wait(ts);
    }
}

asmlinkage void wake_up_queue(void)
{
    struct timespec ts;
    unsigned int thread_task_id;
    int wake_num;

    wake_num = task_wake(ts, thread_task_id);
    if (copy_to_user((void __user *)arg, wake_num, sizeof(unsigned int)) != 0)
        printk("[DEBUG] User copy error...\n");
}

asmlinkage void semaphore_init(void)
{
    struct semaphore sem;
    if (copy_from_user(&sem, (void __user *)arg, sizeof(struct semaphore)) != 0)
        printk("[DEBUG] User copy error...\n");
    else {
        __sem_init_local(sem);
    }
}

asmlinkage void sem